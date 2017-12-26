#include <string>

#include "rot_cipher.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

// A completely inefficient function for rotating letters. It was like 2am
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

///////////////// constructors /////////////////////////////////////////////

RotCipherFilter::RotCipherFilter(int rot_value, const std::string& rot_header) :
    rot_value_(rot_value), rot_header_(rot_header) {}
///////////////////////////////////////////////////////////////////////////////

RotCipherFilter::~RotCipherFilter() {}

void RotCipherFilter::onDestroy() {}

/**
 * Here's where the magic happens. Envoy works in ordered filter chains, based
 * on the order in the configuration file. When it's this filter's turn to 
 * process the request (going upstream), we get this call for the headers
 */
FilterHeadersStatus RotCipherFilter::decodeHeaders(HeaderMap& headers, bool) {
  // static b/c it's the same everytime, so once it's initialized let's just
  // keep it around
  static LowerCaseString header_key(rot_header_);

  // extract the header
  const HeaderEntry* header_entry = headers.get(header_key);
  
  // if it's `nullptr`, then the header value isn't defined. If we don't have
  // this check, then Envoy will segfault if the request doesn't have the header
  if (header_entry != nullptr) {
    std::string thingy(header_entry->value().c_str());
    std::string new_value = rotateText(thingy);
    
    // we have to remove the header, otherwise we'll end up with duplicate
    // headers, as adding a header with the same name only appends, doesn't
    // replace.
    headers.remove(header_key);
    headers.addCopy(header_key, new_value);
  }

  return FilterHeadersStatus::Continue;
}


////////////// these functions are required by the abstract class but we don't
////////////// use them, so just `Continue` along
FilterDataStatus RotCipherFilter::decodeData(Buffer::Instance&, bool) {
  return FilterDataStatus::Continue;
}

FilterTrailersStatus RotCipherFilter::decodeTrailers(HeaderMap&) {
  return FilterTrailersStatus::Continue;
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void RotCipherFilter::setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) {
  decoder_callbacks_ = &callbacks;
}

} // Http
} // Envoy