#pragma once

#include <string>

#include "envoy/server/filter_config.h"

#include "rot_cipher.pb.h"

namespace Envoy {
namespace Server {
namespace Configuration {

class RotCipherConfig : public NamedHttpFilterConfigFactory {
public:
  HttpFilterFactoryCb createFilterFactory(const Json::Object&, const std::string&,
                                          FactoryContext&) override;

  HttpFilterFactoryCb createFilterFactoryFromProto(const Protobuf::Message&,
                                                   const std::string&,
                                                   FactoryContext&) override;

  // this is important! if you just use Envoy::ProtobufWkt::Empty()
  // then the config won't be able to get cast to your protobuf type and you'll
  // get an error message like:
  // "Unable to parse JSON as proto (INVALID_ARGUMENT:: Cannot find field.):"
  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new example::RotCipher()};
  }

  std::string name() override { return "rot_cipher"; }

};

} // Configuration
} // Server
} // Envoy