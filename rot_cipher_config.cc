#include <string>

#include "rot_cipher_config.h"

#include "rot_cipher.h"

#include "common/protobuf/utility.h"
#include "envoy/registry/registry.h"

#include "gen/rot_cipher.pb.h"

namespace Envoy {
namespace Server {
namespace Configuration {

HttpFilterFactoryCb RotCipherFilterConfig::createFilterFactory(const Json::Object&, const std::string&,
                                          FactoryContext&) override {

  // in this example we manually parse the JSON since it's one field. In the
  // official Envoy source they write "translation" functions. See
  // source/common/config/filter_json.cc
  return [](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(
      Http::StreamDecoderFilterSharedPtr{new Http::RotCipherFilter()});
  };
}

HttpFilterFactoryCb RotCipherFilterConfig::createFilterFactoryFromProto(const Protobuf::Message& proto_config,
                                                   const std::string&,
                                                   FactoryContext&) override {
  
  const auto& typed_config = dynamic_cast<example::RotCipher>(proto_config);
  
  return [typed_config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(
      Http::StreamDecoderFilterSharedPtr{new Http::RotCipherFilter(typed_config)});
  };
}

  

static Registry::RegisterFactory<RotCipherFilterConfig, NamedHttpFilterConfigFactory> register_;

} // Configuration
} // Server
} // Envoy