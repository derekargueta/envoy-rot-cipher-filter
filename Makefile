compile:
	bazel build //:envoy

test:
	bazel test //:rot_cipher_test

static-check:
	cppcheck --enable=all --language=c++ --std=c++14 --std=c++11 rot_cipher*

valgrind:
	valgrind ./bazel-bin/envoy -c examples/example.v2.yaml --v2-config-only

clean:
	rm -rf gen/*
	rm -rf bazel-*
