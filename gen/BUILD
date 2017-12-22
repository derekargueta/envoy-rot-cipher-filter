package(default_visibility = ["//visibility:public"])

load(
  "@envoy//bazel:envoy_build_system.bzl",
  "envoy_cc_library",
)

envoy_cc_library(
    name = "rot_cipher_protos",
    srcs = ["rot_cipher.pb.cc"],
    hdrs = ["rot_cipher.pb.h"],
    repository = "@envoy",
    external_deps = [
        "protobuf",
    ],
)
