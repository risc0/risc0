load(":gcc_toolchain.bzl", "gcc_toolchain_config")

filegroup(
    name = "empty",
    srcs = [],
)

filegroup(
    name = "sysroot",
    srcs = glob(["*/**"]),
    visibility = ["//visibility:public"],
)

filegroup(
    name = "linker_files",
    srcs = glob(["*/**"]) + [
        "@byz9//bazel/toolchain/rv32im-linux:kernel.ld",
        "@byz9//bazel/toolchain/rv32im-linux:kernel_v1.ld",
    ],
)

gcc_toolchain_config(
    name = "gcc-toolchain-config",
    sysroot = "@{workspace}//:sysroot",
)

cc_toolchain(
    name = "cc-toolchain",
    all_files = ":sysroot",
    ar_files = ":sysroot",
    as_files = ":sysroot",
    compiler_files = ":sysroot",
    dwp_files = ":empty",
    linker_files = ":linker_files",
    objcopy_files = ":empty",
    strip_files = ":empty",
    supports_param_files = True,
    toolchain_config = ":gcc-toolchain-config",
)
