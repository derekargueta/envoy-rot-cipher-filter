#include <string>

#include "rot_cipher.h"

#include "gen/rot_cipher.pb.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

std::string RotCipherFilter::rotateText(std::string text) {
  for (size_t i = 0; i < text.size(); i++) {
    int j = text[i];
    int new_letter = j;
    if (j >= 65 && j <= 90) {
      new_letter = j + rot_value_;
      if (new_letter > 90) {
        new_letter -= 26;
      }
    } else if (j >= 97 && j <= 122) {
      new_letter = j + rot_value_;
      if (new_letter > 122) {
        new_letter -= 26;
      }
    }

    text[i] = char(new_letter);
  }

  return text;
}

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

FilterHeadersStatus RotCipherFilter::decodeHeaders(HeaderMap& headers, bool) {
  static LowerCaseString header_key(rot_header_);
  const HeaderEntry* header_entry = headers.get(header_key);
  if (header_entry != nullptr) {
    std::string thingy(header_entry->value().c_str());
    std::string new_value = rotateText(thingy);
    headers.remove(header_key);
    headers.addCopy(header_key, new_value);
  }
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