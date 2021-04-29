#include <iostream>
#include <string>

#include "rot_cipher_config.h"

#include "rot_cipher.h"

#include "common/protobuf/utility.h"
#include "envoy/registry/registry.h"

#include "rot_cipher.pb.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace RotCipher {

Http::FilterFactoryCb RotCipherConfig::createFilterFactoryFromProtoTyped(const example::RotCipher& proto_config,
                                                                  const std::string& /*stats_prefix*/,
                                                                  Server::Configuration::FactoryContext& /*context*/) {

  int rot_value = proto_config.rot_value();
  std::string rot_header = proto_config.rot_header();
  return [rot_value, rot_header](Http::FilterChainFactoryCallbacks& callbacks) -> void {
    callbacks.addStreamDecoderFilter(
      Http::StreamDecoderFilterSharedPtr{new Http::RotCipherFilter(rot_value, rot_header)});
  };
}

REGISTER_FACTORY(RotCipherConfig, Server::Configuration::NamedHttpFilterConfigFactory);

} // RotCipher
} // HttpFilters
} // Extensions
} // Envoy
