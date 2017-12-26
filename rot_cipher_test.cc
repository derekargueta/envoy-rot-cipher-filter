#include "gtest/gtest.h"

#include "rot_cipher.h"

#include "api/filter/network/http_connection_manager.pb.h"

#include "test/integration/http_integration.h"
#include "test/integration/utility.h"

namespace Envoy {


TEST(RotCipherFilter, BasicTest) {
  Http::RotCipherFilter filter(13, "x-rot");

  Http::TestHeaderMapImpl headers{
    {":method", "GET"},
    {":path", "/"},
    {":authority", "host"},
    {"x-rot", "asdf"}
  };

  filter.decodeHeaders(headers, false);

  std::string result = std::string(headers.get(Http::LowerCaseString("x-rot"))->value().c_str());
  EXPECT_EQ(result, "nfqs");
}

} // Envoy