package(
    # copybara:uncomment default_applicable_licenses = ["//tensorflow:license"],
    default_visibility = [
        "//tensorflow:__subpackages__",
    ],
    licenses = ["notice"],
)

py_library(
    name = "profiler",
    srcs = ["__init__.py"],
    srcs_version = "PY3",
    deps = [
        "//tensorflow/core/profiler:profiler_analysis_proto_py",
        "//tensorflow/python/util:all_util",
        "//tensorflow/tsl/profiler/protobuf:trace_events_proto_py",
    ],
)

py_library(
    name = "profiler_analysis_pb2_grpc",
    srcs = ["profiler_analysis_pb2_grpc.py"],
    srcs_version = "PY3",
    visibility = ["//visibility:public"],
    deps = ["//tensorflow/core/profiler:profiler_analysis_proto_py"],
)

py_library(
    name = "capture_tpu_profile_lib",
    srcs = [
        "capture_tpu_profile.py",
        "version.py",
    ],
    srcs_version = "PY3",
    deps = [
        "//tensorflow/python:client",
        "//tensorflow/python:errors",
        "//tensorflow/python:versions",
        "//tensorflow/python/distribute/cluster_resolver:cluster_resolver_lib",
        "//tensorflow/python/platform:gfile",
        "//tensorflow/python/platform:tf_logging",
        "//tensorflow/python/profiler:profiler_client",
        "//tensorflow/python/profiler:profiler_v2",
        "@absl_py//absl:app",
        "@absl_py//absl/flags",
    ],
)

py_binary(
    name = "capture_tpu_profile_bin",
    srcs = ["capture_tpu_profile.py"],
    main = "capture_tpu_profile.py",
    python_version = "PY3",
    deps = [
        ":capture_tpu_profile_lib",
        "@absl_py//absl/flags",
    ],
)
