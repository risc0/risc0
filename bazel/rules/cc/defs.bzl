def _copts(std):
    return select({
        "@bazel_tools//platforms:windows": [
            "/std:" + std,
            "/Zc:preprocessor",
        ],
        "//conditions:default": ["-std=" + std],
    })

def cc_binary(name, std = "c++17", copts = [], **kwargs):
    native.cc_binary(
        name = name,
        copts = copts + _copts(std),
        **kwargs
    )

def cc_library(name, std = "c++17", copts = [], **kwargs):
    native.cc_library(
        name = name,
        copts = copts + _copts(std),
        **kwargs
    )

def cc_test(name, std = "c++17", copts = [], **kwargs):
    native.cc_test(
        name = name,
        copts = copts + _copts(std),
        **kwargs
    )
