#include <string>

#include "rot_cipher.h"

#include "gen/rot_cipher.pb.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

RotCipherFilter::RotCipherFilter() {
  rot_value_ = 13;  // caesar cipher
  rot_header_ = "x-rot";  // default rotation header
}

RotCipherFilter::RotCipherFilter(example::RotCipher config) {
  rot_value_ = config.rot_value();
  rot_header_ = config.rot_header();
}

RotCipherFilter::RotCipherFilter(const Json::Object& config) {
  rot_value_ = config.getInteger("rot_value");
  rot_header_ = config.getString("rot_header");
}

RotCipherFilter::~RotCipherFilter() {}

void RotCipherFilter::onDestroy() {}

FilterHeadersStatus RotCipherFilter::decodeHeaders(HeaderMap&, bool) {
  return FilterHeadersStatus::Continue;
}

FilterDataStatus RotCipherFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus RotCipherFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}

void RotCipherFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

} // Http
} // Envoy