#include <iostream>
#include <string>

#include "rot_cipher_config.h"

#include "rot_cipher.h"

#include "common/protobuf/utility.h"
#include "envoy/registry/registry.h"

#include "rot_cipher.pb.h"

namespace Envoy {
namespace Server {
namespace Configuration {

HttpFilterFactoryCb RotCipherConfig::createFilterFactory(const Json::Object& obj,
                                                         const std::string&,
                                                         FactoryContext&) {

  // in this example we manually parse the JSON since it's two fields. In the
  // official Envoy source they write "translation" functions. See
  // source/common/config/filter_json.cc
  int rot_value = obj.getInteger("rot_value", 13);
  std::string rot_header = obj.getString("rot_header", "x-rot");
  return [rot_value, rot_header](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(
      Http::StreamDecoderFilterSharedPtr{new Http::RotCipherFilter(rot_value, rot_header)});
  };
}

HttpFilterFactoryCb RotCipherConfig::createFilterFactoryFromProto(const Protobuf::Message& proto_config,
                                                                  const std::string&,
                                                                  FactoryContext&) {
  
  const auto& typed_config = dynamic_cast<const example::RotCipher&>(proto_config);

  int rot_value = typed_config.rot_value();
  std::string rot_header = typed_config.rot_header();
  return [rot_value, rot_header](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(
      Http::StreamDecoderFilterSharedPtr{new Http::RotCipherFilter(rot_value, rot_header)});
  };
}

  
// this is required for the filter to get registered with the Http connection
// manager, though I'm not sure how the internals of this works.
static Registry::RegisterFactory<RotCipherConfig, NamedHttpFilterConfigFactory> register_;

} // Configuration
} // Server
} // Envoy