#include <iostream>
#include <string>

#include "rot_cipher_config.h"

#include "rot_cipher.h"

#include "common/protobuf/utility.h"
#include "envoy/registry/registry.h"

#include "gen/rot_cipher.pb.h"

namespace Envoy {
namespace Server {
namespace Configuration {

HttpFilterFactoryCb RotCipherConfig::createFilterFactory(const Json::Object&, const std::string&,
                                          FactoryContext&) {

  // in this example we manually parse the JSON since it's one field. In the
  // official Envoy source they write "translation" functions. See
  // source/common/config/filter_json.cc
  return [](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(
      Http::StreamDecoderFilterSharedPtr{new Http::RotCipherFilter()});
  };
}

HttpFilterFactoryCb RotCipherConfig::createFilterFactoryFromProto(const Protobuf::Message& proto_config,
                                                   const std::string&,
                                                   FactoryContext&) {
  
  std::cout << "wat" << std::endl;
  example::RotCipher typed_config; // = dynamic_cast<const example::RotCipher&>(proto_config);
  typed_config.CopyFrom(proto_config);
  std::cout << "no way" << std::endl;

  // const google::protobuf::Reflection* reflection = proto_config.GetReflection();
  // const google::protobuf::Descriptor* descriptor = proto_config.GetDescriptor();
  // const google::protobuf::FieldDescriptor* value_field = descriptor->FindFieldByName("rot_value");
  // const google::protobuf::FieldDescriptor* header_field = descriptor->FindFieldByName("rot_header");
  // auto idk = &proto_config;
  // std::string rot_header = reflection->GetString(*idk, header_field)
  // int rot_value = reflection->GetInt32(*proto_config, value_field)

  return [typed_config](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(
      Http::StreamDecoderFilterSharedPtr{new Http::RotCipherFilter(typed_config)});
  };
}

  

static Registry::RegisterFactory<RotCipherConfig, NamedHttpFilterConfigFactory> register_;

} // Configuration
} // Server
} // Envoy