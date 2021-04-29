package(default_visibility = ["//visibility:public"])

load(
	"@envoy//bazel:envoy_build_system.bzl",
	"envoy_cc_binary",
	"envoy_cc_library",
	"envoy_cc_test",
)
load("@envoy_api//bazel:api_build_system.bzl", "api_proto_package")

envoy_cc_binary(
	name = "envoy",
	repository = "@envoy",
	deps = [
		":rot_cipher_config",
		"@envoy//source/exe:envoy_main_entry_lib",
	],
)

api_proto_package()

envoy_cc_library(
    name = "rot_cipher_lib",
    srcs = ["rot_cipher.cc"],
    hdrs = ["rot_cipher.h"],
    repository = "@envoy",
    deps = [
        "//:pkg_cc_proto",
        "@envoy//include/envoy/http:filter_interface",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_library(
    name = "rot_cipher_config",
    srcs = ["rot_cipher_config.cc"],
    hdrs = ["rot_cipher_config.h"],
    repository = "@envoy",
    deps = [
        "//:pkg_cc_proto",
        ":rot_cipher_lib",
        "@envoy//include/envoy/server:factory_context_interface",
        "@envoy//source/extensions/filters/http/common:factory_base_lib",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_test(
    name = "rot_cipher_test",
    srcs = ["rot_cipher_test.cc"],
    repository = "@envoy",
    deps = [
        "//:pkg_cc_proto",
        ":rot_cipher_config",
        "@envoy//test/integration:http_integration_lib"
    ],
)
