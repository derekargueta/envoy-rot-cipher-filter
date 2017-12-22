#pragma once

#include <string>

#include "envoy/server/filter_config.h"

#include "gen/rot_cipher.pb.h"

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

  ProtobufTypes::MessagePtr createEmptyConfigProto() override {
    return ProtobufTypes::MessagePtr{new Envoy::ProtobufWkt::Empty()};
  }

  std::string name() override { return "rot_cipher"; }

};

} // Configuration
} // Server
} // Envoy