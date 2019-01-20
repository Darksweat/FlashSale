package(default_visibility = ["//visibility:public"])

#with_grpc = True,cc_proto_library

#load("//tools/build_rules:grpc.bzl", "cc_grpc_library")

#load("@org_pubref_rules_protobuf", "cc_proto_library")

#load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cc_proto_library")

#load("//bazel:grpc_build_system.bzl", "grpc_proto_library")



#load("//cpp:cpp_grpc_library.bzl", "cpp_grpc_library")

load("@build_stack_rules_proto//cpp:cpp_grpc_library.bzl", "cpp_grpc_library")

#grpc_proto_library(
#    name = "cc_seckill_proto",
#    srcs = ["seckill.proto"],
#)

#cc_proto_library(
#   name = "cc_seckill_proto",
#   protos = [":seckill_proto"],
#   with_grpc = True,
#)


cpp_grpc_library(
    name = "cc_seckill_proto",
    deps = ["//proto:seckill_proto"],
)

cc_library(
    name = "Md5",
    srcs = ["Md5.cc"],
    hdrs = ["Md5.h"],
)

cpp_grpc_library(
    name = "cc_flashsale_proto",
    deps = ["//proto:flashsale_proto"],
)

cc_binary(
    name = "flashsale_client",
    srcs = ["flashsale_client.cc"],
    deps = [
        ":cc_flashsale_proto",
        ":Md5",
    ],
)

cc_binary(
    name = "flashsale_server",
    srcs = ["flashsale_server.cc"],
    defines = ["BAZEL_BUILD"],
    deps = [
        ":cc_flashsale_proto",
        ":Md5",
        "@mysql_local//:mysql",
        "@hiredis_local//:hiredis",
    ],
)