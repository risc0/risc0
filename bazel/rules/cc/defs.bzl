DEFAULT_CXX_STD = "c++17"

def _copts(std):
    return select({
        "@risc0//bazel/rules/cc:msvc-cl": [
            "/std:" + std,
            "/Zc:preprocessor",
        ],
        "//conditions:default": [
            "-std=" + std,
            "-Werror",
        ],
    })

def cc_binary(name, std = DEFAULT_CXX_STD, copts = [], **kwargs):
    native.cc_binary(
        name = name,
        copts = copts + _copts(std),
        **kwargs
    )

def cc_library(name, std = DEFAULT_CXX_STD, copts = [], **kwargs):
    native.cc_library(
        name = name,
        copts = copts + _copts(std),
        **kwargs
    )

def cc_test(name, std = DEFAULT_CXX_STD, copts = [], **kwargs):
    native.cc_test(
        name = name,
        copts = copts + _copts(std),
        **kwargs
    )

def cc_gtest(name, std = DEFAULT_CXX_STD, copts = [], deps = [], **kwargs):
    native.cc_test(
        name = name,
        copts = copts + _copts(std),
        deps = deps + ["//risc0/core/test:gtest_main"],
        **kwargs
    )
