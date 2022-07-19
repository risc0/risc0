load("@risc0//bazel/rules/cc:defs.bzl", "cc_library", "cc_test")

package(default_visibility = ["//visibility:public"])

cc_library(
    name = "box2d",
    srcs = glob([
        "src/**/*.cpp",
        "src/**/*.h",
    ]),
    hdrs = glob([
        "include/box2d/*.h",
    ]),
    copts = [ "-iquote external/box2d/src/" ],
    includes = [
        "include",
    ],
    linkstatic = True,
)

cc_test(
    name = "box2d_test",
    srcs = glob([
        "unit-test/*.cpp",
        "unit-test/*.h",
    ]),
    deps = [
        ":box2d",
    ]
)
