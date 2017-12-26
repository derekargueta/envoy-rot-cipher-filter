package(default_visibility = ["//visibility:public"])

load(
	"@envoy//bazel:envoy_build_system.bzl",
	"envoy_cc_binary",
	"envoy_cc_library",
	"envoy_cc_test",
    "envoy_proto_library",
)

envoy_cc_binary(
	name = "envoy",
	repository = "@envoy",
	deps = [
		":rot_cipher_config",
		"@envoy//source/exe:envoy_main_entry_lib",
	],
)

envoy_proto_library(
    name = "rot_cipher_proto",
    srcs = ["rot_cipher.proto"],
)

envoy_cc_library(
    name = "rot_cipher_lib",
    srcs = ["rot_cipher.cc"],
    hdrs = ["rot_cipher.h"],
    repository = "@envoy",
    deps = [
        "//:rot_cipher_proto",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_library(
    name = "rot_cipher_config",
    srcs = ["rot_cipher_config.cc"],
    hdrs = ["rot_cipher_config.h"],
    repository = "@envoy",
    deps = [
        "//:rot_cipher_proto",
        ":rot_cipher_lib",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_test(
    name = "rot_cipher_test",
    srcs = ["rot_cipher_test.cc"],
    repository = "@envoy",
    deps = [
        "//:rot_cipher_proto",
        ":rot_cipher_config",
        "@envoy//test/integration:http_integration_lib"
    ],
)

