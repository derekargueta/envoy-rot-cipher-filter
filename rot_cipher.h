#pragma once

#include <string>

#include "gen/rot_cipher.pb.h"

#include "server/config/network/http_connection_manager.h"

namespace Envoy {
namespace Http {

class RotCipherFilter : public StreamDecoderFilter {
public:
  RotCipherFilter();
  RotCipherFilter(example::RotCipher);
  RotCipherFilter(const Json::Object&);
  RotCipherFilter(int rot_value, std::string rot_header);
  ~RotCipherFilter();

  void onDestroy() override;

  FilterHeadersStatus decodeHeaders(HeaderMap& headers, bool) override;
  FilterDataStatus decodeData(Buffer::Instance&, bool) override;
  FilterTrailersStatus decodeTrailers(HeaderMap&) override;
  void setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) override;

private:
  StreamDecoderFilterCallbacks* decoder_callbacks_;

  std::string rotateText(std::string text);

  int rot_value_;
  std::string rot_header_;
};

} // Http
} // Envoy
