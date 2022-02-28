toolchain(
    name = "toolchain",
    exec_compatible_with = [
        "{host_arch}",
        "{host_os}",
    ],
    target_compatible_with = [
        "@risc0//bazel/platform/cpu:riscv32im",
        "@risc0//bazel/platform/os:risc0",
    ],
    toolchain = "{toolchain}",
    toolchain_type = "@bazel_tools//tools/cpp:toolchain_type",
    visibility = ["//visibility:public"],
)
