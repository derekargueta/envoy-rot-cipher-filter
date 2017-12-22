Envoy Rot Cipher Filter
===========================

A simple filter that probably (hopefully) isn't of much production value, but demonstrates how to write a third-party [Envoy](https://github.com/envoyproxy/envoy) filter that is compatible with both the v1 and v2 API. I hope that this repository serves as a nice guide for people who maybe don't want to dive into the internals of Envoy too deeply, but want to be able to build custom Envoy filters _outside_ of the main source code.

I wanted to write this because the [current defacto example](https://github.com/envoyproxy/envoy-filter-example) doesn't use any configuration data, which is one of the parts I wrestled with the most in building this filter. As a young whippersnapper new-grad, I thought that this "outside perspective" might be helpful for others getting started with C++/Envoy development.

FYI The code here is not the greatest and isn't meant to be, but I do plan on coming back here and cleaning up somewhat.

If you don't understand the explanations here, please open an issue/PR.
Also, the filter's source code should be well-documented (actually over-documented) to provide further explanations.


## Compiling & Running
```bash
git submodule update --init  # we need the envoy source to compile/test
make compile
```

The `compile` target should call the `compile/proto` target to generate the protobuf classes in the `gen/` directory.

I've included a basic `app.py` web server that just prints the headers it receives. To run the whole thing:

terminal pane 1:
```bash
./bazel-bin/envoy -c examples/example.v2.yaml --v2-config-only
```

terminal pane 2:
```
python examples/app.py
```

terminal pane 3:
```
curl -H "x-rot: asdf" localhost:8000
```

and in pane 2 you should see something like
```
user-agent: curl/7.54.0
accept: */*
x-forwarded-proto: http
x-request-id: 5a16b07d-d811-4fdf-b9bc-790efdd1d97b
x-rot: nopq
content-length: 0
```
where you can see the letters of `x-rot` have been rotated.


## Usage
This filter accepts two configuration options:
- `rot_value`: an integer describing how much to rotate each letter by. For example, 13 would be the classic Caesar Cipher
- `rot_header`: a string that names which header to apply the cipher to. If the header is not found, no action is taken and the filter continues.

v2 Example
```
  http_filters:
  - name: rot_cipher
    config: { rot_value: 13, rot_header: x-rot }
  - name: envoy.router
```

Full example configurations are in the `examples/` directory.


## Filter Development

Every filter has 2 main components:
- The config, which for HTTP filters should be a subclass of [`NamedHttpFilterConfigFactory`](https://github.com/envoyproxy/envoy/blob/b01b13865ac86c6b5716e128137afd29ef3147d0/include/envoy/server/filter_config.h#L196)
- The filter implementation, which for HTTP filters would be a subclass of either [`StreamDecoderFilter`](https://github.com/envoyproxy/envoy/blob/3599784052e75ac1b18b5342aa711d987a852bf0/include/envoy/http/filter.h#L289), [`StreamEncoderFilter`](https://github.com/envoyproxy/envoy/blob/3599784052e75ac1b18b5342aa711d987a852bf0/include/envoy/http/filter.h#L402), or [`StreamFilter`](https://github.com/envoyproxy/envoy/blob/3599784052e75ac1b18b5342aa711d987a852bf0/include/envoy/http/filter.h#L438) for filters that do encoding and decoding.

To support the [v2 API](https://www.envoyproxy.io/docs/envoy/latest/api-v2/api), you'll additionally need a `.proto` file.
Simply put, if your config is v1, then Envoy will call `createFilterFactory` with a [`Json::Object`](https://github.com/envoyproxy/envoy/blob/master/include/envoy/json/json_object.h) which you can then pick apart and validate.
If your config is v2, then it will call `createFilterFactoryFromProto` with a [`Protobuf::Message`](https://developers.google.com/protocol-buffers/docs/reference/cpp/google.protobuf.message), which you can just cast to your protobuf-generated class. 
The details of how/why this procedure works is worthy of a separate write-up, but I believe it has a lot to do with how the v2 API can use [gRPC](https://grpc.io/) streaming.
(More on Envoy's use of gRPC in the [Envoy docs](https://www.envoyproxy.io/docs/envoy/latest/intro/arch_overview/grpc.html))

If you look at filters in the main Envoy source code they have a lot more pieces due to the complexity, for example they have intermediate `config` classes that the Json and protobuf data get converted to so that the filters only need 1 constructor. But if you strip it all down, these are the bare minimums.

I started with `rot_cipher.proto` to define what the configuration would look like.
That file then produces `rot_cipher.pb.(cc|h)` in `gen/`.
This is a pretty ad-hoc procedure that I constructed, and quite frankly the bazel `BUILD` file could be improved to use the native Bazel support for protobufs instead of calling the protobuf compiler in the `Makefile`.


_But is using a `.proto` necessary?_

_For the v2 API, yes. You might be able to hack something weird using [Protobuf Reflection](https://developers.google.com/protocol-buffers/docs/reference/cpp/google.protobuf.message#Reflection) but that's a scary path._


After wrapping my head around how the protobufs integrate into Envoy filter configs (first-time protobuf user here), the rest was pretty straight forward to achieve based on the [envoy-filter-example](https://github.com/envoyproxy/envoy-filter-example). Some important classes to look at are [HeaderMap](https://github.com/envoyproxy/envoy/blob/master/include/envoy/http/header_map.h) for manipulating headers and [Object](https://github.com/envoyproxy/envoy/blob/master/include/envoy/json/json_object.h) for manipulating Json Objects. Additionally, [json_loader.cc](https://github.com/envoyproxy/envoy/blob/master/source/common/json/json_loader.cc), [config/utility.h](https://github.com/envoyproxy/envoy/blob/master/source/common/config/utility.h), and [protobuf/utility.h](https://github.com/envoyproxy/envoy/blob/master/source/common/protobuf/utility.h) were pretty helpful.

As an aside, before starting this filter I went through the [Protobuf C++ Tutorial](https://developers.google.com/protocol-buffers/docs/cpptutorial), substituting proto3 syntax for proto2.

## Problems I ran Into
(this part is still kind of mumble-y and under revision)

I had an issue with the v2 API config where each time I tried to start Envoy I got the error below:
```
[2017-12-22 13:55:03.124][4915417][debug][config] external/envoy/source/server/listener_manager_impl.cc:29]   filter #0:
[2017-12-22 13:55:03.124][4915417][debug][config] external/envoy/source/server/listener_manager_impl.cc:30]     name: envoy.http_connection_manager
[2017-12-22 13:55:03.195][4915417][debug][config] external/envoy/source/server/config/network/http_connection_manager.cc:226]     filter #0
[2017-12-22 13:55:03.195][4915417][debug][config] external/envoy/source/server/config/network/http_connection_manager.cc:227]       name: rot_cipher
[2017-12-22 13:55:03.195][4915417][critical][main] external/envoy/source/server/server.cc:72] error initializing configuration 'examples/example.v2.yaml': Unable to parse JSON as proto (INVALID_ARGUMENT:: Cannot find field.): {"rot_value":13,"rot_header":"x-rot"}
[2017-12-22 13:55:03.195][4915417][debug][upstream] external/envoy/source/common/upstream/cluster_manager_impl.cc:523] shutting down thread local cluster manager
```

I had managed to narrow it down to this line in my code:

```cpp
const auto& typed_config = dynamic_cast<const example::RotCipher&>(proto_config);
```

All generated protobuf messages subclass `Protobuf::Message` (which is the type of `proto_config`) so this dynamic cast shouldn't be a problem. I actually found this snippet in the [Envoy source](https://github.com/envoyproxy/envoy/blob/bbe6618b90d87500e7ed4304996881c4be4abb09/source/common/protobuf/utility.h#L149).

I had gone over the configuration multiple times and knew it was correct based on playing with other filters.
At the end my wits, I started throwing print statements into the Envoy source code, thinking maybe there was a bug somewhere in the JSON parsing?
I started with the `HttpConnectionManagerConfig` right after it logs what filter it's processing, since the debug log kindly outputs what line it is at :)
This is at the [end of the constructor](https://github.com/envoyproxy/envoy/blob/9ed62923a8ff6745407046c4451ce757348d966f/source/server/config/network/http_connection_manager.cc#L221) which has the following code.

```cpp
const auto& filters = config.http_filters();
for (int32_t i = 0; i < filters.size(); i++) {
  const ProtobufTypes::String& string_name = filters[i].name();
  const auto& proto_config = filters[i];

  ENVOY_LOG(debug, "    filter #{}", i);
  ENVOY_LOG(debug, "      name: {}", string_name);

  const Json::ObjectSharedPtr filter_config =
      MessageUtil::getJsonObjectFromMessage(proto_config.config());

  // Now see if there is a factory that will accept the config.
  auto& factory = Config::Utility::getAndCheckFactory<NamedHttpFilterConfigFactory>(string_name);
  HttpFilterFactoryCb callback;
  if (filter_config->getBoolean("deprecated_v1", false)) {
    callback = factory.createFilterFactory(*filter_config->getObject("value", true),
                                           stats_prefix_, context);
  } else {
    ProtobufTypes::MessagePtr message =
        Config::Utility::translateToFactoryConfig(proto_config, factory);
    callback = factory.createFilterFactoryFromProto(*message, stats_prefix_, context);
  }
  filter_factories_.push_back(callback);
}

```

I inspected the `filter_config` JSON object and it had the `rot_value` and `rot_header` as expected, so then I looked inside the call to [`Config::Utility::translateToFactoryConfig(...)`](https://github.com/envoyproxy/envoy/blob/6b2823da5006e92bc4b365e9e8804a4f6a2eba37/source/common/config/utility.h#L190) which contains the following code.

```cpp
template <class ProtoMessage, class Factory>
static ProtobufTypes::MessagePtr translateToFactoryConfig(const ProtoMessage& enclosing_message,
                                                          Factory& factory) {
  ProtobufTypes::MessagePtr config = factory.createEmptyConfigProto();

  if (config == nullptr) {
    throw EnvoyException(fmt::format(
        "{} factory returned nullptr instead of empty config message.", factory.name()));
  }

  if (enclosing_message.has_config()) {
    MessageUtil::jsonConvert(enclosing_message.config(), *config);
  }

  return config;
}
```

I wasn't getting the nullptr error message so the config wasn't coming back null... WAIT. `createEmptyConfigProto`? That function is required by the abstract class and I remember pasting in some code for it... I hadn't thought much of that function and just pasted what the `envoy-example-filter` code had, which is `return ProtobufTypes::MessagePtr{new Envoy::ProtobufWkt::Empty()}`. If the empty message is _not_ of type `example::RotCipher`, then yeah there would be issues in casting it to a `Protobuf::Message` and then to an `example::RotCipher`. I checked some built-in Envoy filters that had non-emtpy configurations and sure enough, they return an empty instance of the generated protobuf config.

RateLimit config
```cpp
ProtobufTypes::MessagePtr createEmptyConfigProto() override {
  return ProtobufTypes::MessagePtr{new envoy::api::v2::filter::http::RateLimit()};
}
```

So once I changed the RotCipher config's `createEmtpyConfigProto` to 
```cpp
ProtobufTypes::MessagePtr createEmptyConfigProto() override {
  return ProtobufTypes::MessagePtr{new example::RotCipher()};
}
```

all was well! The error message was a little cryptic (yet correct), but sure enough it was a user-error.

## Thoughts/Reflections

This was mostly an exercise in gaining familiarity with Envoy filter development so here's some thoughts on how the whole thing went.
- There is very little internal documentation of how the mechanics work. This is no secret, but the documentation from Envoy could use some love and help from the community (low-hanging fruit for new Envoy contributors!)
- The organization of the Envoy code made it a little difficult to piece this project together. For example, _all_ the Envoy filter configs are in one directoy ([`server/config/http/`](https://github.com/envoyproxy/envoy/tree/master/source/server/config/http)), and _all_ the Envoy filter implementations are in a different directory ([`source/common/`](https://github.com/envoyproxy/envoy/tree/master/source/common)), and there's multiple `config` directories for [non-filter config stuff](https://github.com/envoyproxy/envoy/tree/master/source/common/config), etc. so it felt like a scavenger hunt to get the complete image of what all 1 filter needs. This organization makes sense for the size of Envoy's project, but again makes it difficult to piece together everything that, for example, the buffer filter does.
- Despite the above 2 "complaints", Envoy does provide a very clean API to work with. I found this to be a much easier exercise than implementing an Nginx module, which took a day-long workshop and I'm still not confident in my Nginx module development.
- I noticed there's some scripts in `envoy/tools/` such as `stack_decode.py` that may have been helpful in debugging but I couldn't figure out how to get them to work.
- The bazel build procedure is pretty slick. Props to the Envoy team!
- If you want to write Envoy filters, you can't shy away from reading a lot of C++ :)
