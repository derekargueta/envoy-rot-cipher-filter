package(default_visibility = ["//visibility:public"])

load(
	"@envoy//bazel:envoy_build_system.bzl",
	"envoy_cc_binary",
	"envoy_cc_library",
	"envoy_cc_test",
)

envoy_cc_binary(
	name = "envoy",
	repository = "@envoy",
	deps = [
		":rot_cipher_config",
		"@envoy//source/exe:envoy_main_entry_lib",
	],
)

envoy_cc_library(
    name = "rot_cipher_lib",
    srcs = ["rot_cipher.cc"],
    hdrs = ["rot_cipher.h"],
    repository = "@envoy",
    deps = [
        "//gen:rot_cipher_protos",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_library(
    name = "rot_cipher_config",
    srcs = ["rot_cipher_config.cc"],
    hdrs = ["rot_cipher_config.h"],
    repository = "@envoy",
    deps = [
        "//gen:rot_cipher_protos",
        ":rot_cipher_lib",
        "@envoy//source/exe:envoy_common_lib",
    ],
)

envoy_cc_test(
    name = "rot_cipher_integration_test",
    srcs = ["rot_cipher_integration_test.cc"],
    data = [":envoy.conf"],
    repository = "@envoy",
    deps = [
        "//gen:rot_cipher_protos",
        ":rot_cipher_config",
        "@envoy//test/integration:http_integration_lib"
    ],
)

