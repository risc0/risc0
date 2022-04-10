load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@rules_conda//:defs.bzl", "conda_create")
load("@rules_conda//:toolchain.bzl", "toolchain_rule")
load("//bazel/toolchain/risc0:repo.bzl", "risc0_toolchain")

def _workspace_impl(module_ctx):
    http_archive(
        name = "riscv_tests",
        build_file = "//bazel/third_party:riscv_tests.BUILD",
        sha256 = "a475f6a9a766cfeb467fa10bc8c006274bffe8673dea357a4d61bdb1067d2c64",
        strip_prefix = "riscv-tests-e30978a71921159aec38eeefd848fca4ed39a826",
        url = "https://github.com/riscv/riscv-tests/archive/e30978a71921159aec38eeefd848fca4ed39a826.zip",
    )

    http_archive(
        name = "bazel_clang_tidy",
        sha256 = "502fb0ea88e28965986851566f0c42330cf31f4289478d6399790b25644b811c",
        strip_prefix = "bazel_clang_tidy-9871a95dbb150dc595aa91355fe99c500196cf3c",
        url = "https://github.com/erenon/bazel_clang_tidy/archive/9871a95dbb150dc595aa91355fe99c500196cf3c.zip",
    )

    http_archive(
        name = "oneTBB",
        build_file = "//bazel/third_party:oneTBB.BUILD",
        sha256 = "e5b57537c741400cf6134b428fc1689a649d7d38d9bb9c1b6d64f092ea28178a",
        strip_prefix = "oneTBB-2021.5.0",
        url = "https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.5.0.tar.gz",
    )

    risc0_toolchain(name = "risc0_toolchain")

    conda_create(
        name = "py3_env",
        environment = "@//:environment.yml",
        quiet = False,
        use_mamba = True,
    )

    toolchain_rule(
        name = "conda_tools",
        py3_runtime = "@py3_env//:python_runtime",
        toolchain_name = "python_toolchain",
    )

workspace = module_extension(implementation = _workspace_impl)
