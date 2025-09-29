load("@rules_cuda//cuda:defs.bzl", "cuda_library", "requires_cuda")

cuda_library(
    name = "sppark",
    srcs = glob([
        "util/*.cpp",
        "util/*.cu",
    ]),
    hdrs = glob([
        "**/*.hpp",
        "**/*.cuh",
        "**/*.h",
    ]),
    target_compatible_with = requires_cuda(),
    visibility = ["//visibility:public"],
)
