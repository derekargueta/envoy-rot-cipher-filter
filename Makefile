
compile/proto:
	mkdir -p gen
	protoc --cpp_out=gen rot_cipher.proto

compile: compile/proto
	bazel build //:envoy

test:
	bazel test //:rot_cipher_integration_test
