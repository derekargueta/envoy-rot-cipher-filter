Envoy Rot Cipher Filter
===========================

A simple and filter that probably isn't of much production value, but demonstrates how to write a third-party Envoy filter that is compatible with both the v1 and v2 API.

## Usage
It accepts two configuration options:
- `rot_value`: an integer describing how much to rotate each letter by. For example, 13 would be the classic Caesar Cipher
- `rot_header`: a string that names which header to apply the cipher to. If the header is not found, no action is taken and the filter continues.

v2 Example
```
  http_filters:
  - name: rot_cipher
    config: { rot_value: 13, rot_header: x-rot }
  - name: envoy.router
```


## Filter Development

I started with `rot_cipher.proto` to define what the configuration would look like.
That file the produces `rot_cipher.pb.(cc|h)` in `gen/`.
This is a pretty ad-hoc procedure, and quite frankly the bazel `BUILD` file could be improved to use the native Bazel support for protobufs instead of calling the protobuf compiler in the `Makefile`.


_But is using a `.proto` necessary?_

_For the v2 API, yes. You might be able to hack something weird using [Protobuf Reflection](https://developers.google.com/protocol-buffers/docs/reference/cpp/google.protobuf.message#Reflection) but that's a scary path._


After wrapping my head around how the protobufs integrate into Envoy filter configs, the rest was pretty straight forward to achieve. Some important classes to look at are [HeaderMap](https://github.com/envoyproxy/envoy/blob/master/include/envoy/http/header_map.h), 

## Problems I ran Into

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

```
const auto& typed_config = dynamic_cast<const example::RotCipher&>(proto_config);
```

All generated protobuf messages subclass `Protobuf::Message` (which is the type of `proto_config`) so this dynamic cast shouldn't be a problem. I actually found this snippet in the [Envoy source](https://github.com/envoyproxy/envoy/blob/bbe6618b90d87500e7ed4304996881c4be4abb09/source/common/protobuf/utility.h#L149).

I had gone over the configuration multiple times and knew it was correct based on playing with other filters.
At the end my wits, I started throwing print statements into the Envoy source code.
I started with the HTTPConnectionManager right after it logs what filter it's processing, since the debug log kindly outputs what line it is at :)
This is at the end of the constructor, `HttpConnectionManagerConfig::HttpConnectionManagerConfig(const envoy::api::v2::filter::network::HttpConnectionManager&, FactoryContext&, Http::DateProvider&, Router::RouteConfigProviderManager&)` which has the following code.

```
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

I inspected the `filter_config` JSON object and it had the `rot_value` and `rot_header`, so then I looked inside the call to `Config::Utility::translateToFactoryConfig(...)` which contains the following code.

```
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

WAIT. `createEmptyConfigProto`? I hadn't thought much of that function and just pasted what the `envoy-example-filter` code had, which is `ProtobufTypes::MessagePtr{new Envoy::ProtobufWkt::Empty()}`. If the original message is _not_ of type `example::RotCipher`, then yeah there would be issues in casting it to a `Protobuf::Message` and then to an `example::RotCipher`. I checked some built-in Envoy filters that had non-emtpy configurations and sure enough, they return an empty instance of the generated protobuf config.

RateLimit config
```
ProtobufTypes::MessagePtr createEmptyConfigProto() override {
  return ProtobufTypes::MessagePtr{new envoy::api::v2::filter::http::RateLimit()};
}
```

So once I changed the RotCipher config's `createEmtpyConfigProto` to 
```

```

## Thoughts/Reflections

This was mostly an exercise in gaining familiarity with Envoy filter development so here's some thoughts on how the whole thing went.
- There is very little internal documentation of how the mechanics work. This is no secret, but the documentation from Envoy could use some love and help from the community (low-hanging fruit for new Envoy contributors!)
- The organization of the Envoy made it a little difficult to piece this project together. For example, _all_ the Envoy filter configs are in one directoy, and _all_ the Envoy filter implementations are in a different directory, etc. instead of having the code organized by module where each module has all of its pieces in one directory. This organization makes sense for the size of Envoy's project, but again makes it difficult to piece together everything that, for example, the buffer filter does.
- Despite the above 2 "complaints", Envoy does provide a very clean API to work with. I found this to be a much easier exercise than implementing an Nginx module, which took a day-long workshop and I'm still not confident in my Nginx module development.
