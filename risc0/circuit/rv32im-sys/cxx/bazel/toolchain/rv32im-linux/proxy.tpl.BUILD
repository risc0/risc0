toolchain(
    name = "toolchain",
    exec_compatible_with = [
        "{host_arch}",
        "{host_os}",
    ],
    target_compatible_with = [
        "@byz9//bazel/platform/cpu:riscv32im",
        "@byz9//bazel/platform/os:linux",
    ],
    toolchain = "{toolchain}",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
    visibility = ["//visibility:public"],
)
