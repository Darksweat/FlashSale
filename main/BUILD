licenses(["notice"])  # 3-clause BSD

package(default_visibility = ["//visibility:public"])

load("//bazel:grpc_build_system.bzl", "grpc_proto_library")

grpc_proto_library(
    name = "flashsale",
    srcs = ["proto/flashsale.proto"],
)

cc_import(
    name = "mysql",
    hdrs = glob([
        "include/*.h",
        "include/mysql/*.h",
    ]),
    shared_library = "include/libmysqlclient.21.dylib",
    visibility = ["//main:__pkg__"],
)

cc_import(
    name = "hiredis",
    hdrs = glob([
        "hiredis/*.h",
        "hiredis/adapters/*.h"
    ]),
    shared_library = "hiredis/libhiredis.0.14.dylib",
    visibility = ["//main:__pkg__"],
)

cc_library(
    name = "Md5",
    srcs = ["src/Md5.cc"],
    hdrs = ["src/Md5.h"],
)

cc_binary(
    name = "flashsale_client",
    srcs = ["src/flashsale_client.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":flashsale",
        "//:grpc++",
        "Md5"
    ],
)

cc_binary(
    name = "flashsale_server",
    srcs = ["src/flashsale_server.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":flashsale",
        "//:grpc++",
        ":mysql",
        ":hiredis",
        "Md5"
    ],
)