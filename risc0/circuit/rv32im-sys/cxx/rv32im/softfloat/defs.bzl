load("//bazel/toolchain/risc0:defs.bzl", "risc0_cc_library")

def compile_softfloat():
    """Build the Berkeley SoftFloat 3 library for riscv32im."""
    risc0_cc_library(
        name = "softfloat",
        srcs = [
            "@berkeley_softfloat_3//:root_sources",
            "@berkeley_softfloat_3//:other_sources_1",
            "@berkeley_softfloat_3//:other_sources_2",
            "@berkeley_softfloat_3//:other_sources_3",
            "@berkeley_softfloat_3//:other_sources_4",
            "@berkeley_softfloat_3//:other_sources_5",
            "@berkeley_softfloat_3//:other_sources_6",
            "@berkeley_softfloat_3//:other_sources_7",
            "@berkeley_softfloat_3//:other_sources_8",
            "@berkeley_softfloat_3//:riscv_sources",
            "@softfloat_sys//:helper.c",
        ],
        hdrs = [
            "@berkeley_softfloat_3//:headers",
        ],
        # Use copts with -I flags to add include directories for external repository
        # Include order matches build.rs: build/Linux-386-GCC, source/RISCV, source/include
        # risc0_cc_library always builds for riscv32im, so we only need riscv32im includes
        copts = [
            "-Wno-unused-parameter",
            "-Wno-unused-variable",
            "-Iexternal/berkeley_softfloat_3/build/Linux-386-GCC",
            "-Iexternal/berkeley_softfloat_3/source/RISCV",
            "-Iexternal/berkeley_softfloat_3/source/include",
        ],
        defines = [
            "SOFTFLOAT_ROUND_ODD",
            "INLINE_LEVEL=5",
            "SOFTFLOAT_FAST_DIV32TO16",
            "SOFTFLOAT_FAST_DIV64TO32",
            "SOFTFLOAT_FAST_INT64",
            "THREAD_LOCAL=",
        ],
        visibility = ["//visibility:public"],
    )

    # Expose the .a file for extraction to softfloat-sys directory
    native.filegroup(
        name = "libsoftfloat_a",
        srcs = [":softfloat"],
        output_group = "archive",
        visibility = ["//visibility:public"],
    )
