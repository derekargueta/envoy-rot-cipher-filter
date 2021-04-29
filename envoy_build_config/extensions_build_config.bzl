# See bazel/README.md for details on how this system works.
EXTENSIONS = {
    #
    # Access loggers
    #

    "envoy.access_loggers.file":                        "//source/extensions/access_loggers/file:config",

    #
    # Clusters
    #

    "envoy.clusters.aggregate":                         "//source/extensions/clusters/aggregate:cluster",
    "envoy.clusters.dynamic_forward_proxy":             "//source/extensions/clusters/dynamic_forward_proxy:cluster",
    "envoy.clusters.redis":                             "//source/extensions/clusters/redis:redis_cluster",

    #
    # Input Matchers
    #

    "envoy.matching.input_matchers.consistent_hashing":       "//source/extensions/matching/input_matchers/consistent_hashing:config",

    #
    # Generic Inputs
    #

    "envoy.matching.common_inputs.environment_variable":       "//source/extensions/matching/common_inputs/environment_variable:config",

    #
    # HTTP filters
    #

    "envoy.filters.http.router":                        "//source/extensions/filters/http/router:config",

    #
    # Listener filters
    #

    "envoy.filters.listener.http_inspector":            "//source/extensions/filters/listener/http_inspector:config",
    # NOTE: The original_dst filter is implicitly loaded if original_dst functionality is
    #       configured on the listener. Do not remove it in that case or configs will fail to load.
    "envoy.filters.listener.original_dst":              "//source/extensions/filters/listener/original_dst:config",
    "envoy.filters.listener.original_src":              "//source/extensions/filters/listener/original_src:config",
    # NOTE: The proxy_protocol filter is implicitly loaded if proxy_protocol functionality is
    #       configured on the listener. Do not remove it in that case or configs will fail to load.
    "envoy.filters.listener.proxy_protocol":            "//source/extensions/filters/listener/proxy_protocol:config",
    "envoy.filters.listener.tls_inspector":             "//source/extensions/filters/listener/tls_inspector:config",

    #
    # Network filters
    #

    "envoy.filters.network.http_connection_manager":    "//source/extensions/filters/network/http_connection_manager:config",

    #
    # Transport sockets
    #

    "envoy.transport_sockets.raw_buffer":               "//source/extensions/transport_sockets/raw_buffer:config",
    "envoy.transport_sockets.tap":                      "//source/extensions/transport_sockets/tap:config",

    #
    # Http Upstreams (excepting envoy.upstreams.http.generic which is hard-coded into the build so not registered here)
    #

    "envoy.upstreams.http.http":                        "//source/extensions/upstreams/http/http:config",
    "envoy.upstreams.http.tcp":                         "//source/extensions/upstreams/http/tcp:config",

    #
    # IO socket
    #

    "envoy.io_socket.user_space":                       "//source/extensions/io_socket/user_space:config",
    #
    # HTTP header formatters
    #

    "envoy.http.stateful_header_formatters.preserve_case":       "//source/extensions/http/header_formatters/preserve_case:preserve_case_formatter",
}

# These can be changed to ["//visibility:public"], for  downstream builds which
# need to directly reference Envoy extensions.
EXTENSION_CONFIG_VISIBILITY = ["//:extension_config"]
EXTENSION_PACKAGE_VISIBILITY = ["//:extension_library"]
