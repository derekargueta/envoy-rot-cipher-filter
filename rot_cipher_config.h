#pragma once

#include <string>

#include "envoy/server/factory_context.h"

#include "extensions/filters/http/common/factory_base.h"

#include "rot_cipher.pb.h"
#include "rot_cipher.pb.validate.h"

namespace Envoy {
namespace Extensions {
namespace HttpFilters {
namespace RotCipher {

class RotCipherConfig : public Common::FactoryBase<example::RotCipher> {
public:
  RotCipherConfig() : FactoryBase("rot_cipher") {}

private:
  Http::FilterFactoryCb createFilterFactoryFromProtoTyped(const example::RotCipher&,
                                                   const std::string&,
                                                   Server::Configuration::FactoryContext&) override;
};

} // namespace RotCipher
} // namespace HttpFilters
} // namespace Extensions
} // namespace Envoy
