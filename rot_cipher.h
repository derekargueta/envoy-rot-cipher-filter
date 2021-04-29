#pragma once

#include <string>

#include "envoy/http/filter.h"

namespace Envoy {
namespace Http {

class RotCipherFilter : public StreamDecoderFilter {
public:
  RotCipherFilter(int rot_value, const std::string& rot_header);
  ~RotCipherFilter();

  void onDestroy() override;

  FilterHeadersStatus decodeHeaders(RequestHeaderMap& headers, bool) override;
  FilterDataStatus decodeData(Buffer::Instance&, bool) override;
  FilterTrailersStatus decodeTrailers(RequestTrailerMap&) override;
  void setDecoderFilterCallbacks(StreamDecoderFilterCallbacks& callbacks) override;

private:
  StreamDecoderFilterCallbacks* decoder_callbacks_{};

  std::string rotateText(std::string text);

  int rot_value_;
  std::string rot_header_;
};

} // Http
} // Envoy
