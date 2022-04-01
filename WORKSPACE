workspace(name = "risc0")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

register_toolchains(
    "//:clang_format_toolchain",
)

http_archive(
    name = "bazel_skylib",
    sha256 = "c6966ec828da198c5d9adbaa94c05e3a1c7f21bd012a0b29ba8ddbccb2c93b0d",
    urls = [
        "https://github.com/bazelbuild/bazel-skylib/releases/download/1.1.1/bazel-skylib-1.1.1.tar.gz",
        "https://mirror.bazel.build/github.com/bazelbuild/bazel-skylib/releases/download/1.1.1/bazel-skylib-1.1.1.tar.gz",
    ],
)

load("@bazel_skylib//:workspace.bzl", "bazel_skylib_workspace")

bazel_skylib_workspace()

load("//bazel/toolchain/risc0:repo.bzl", "risc0_toolchain")

risc0_toolchain(name = "risc0_toolchain")

http_archive(
    name = "com_google_googletest",
    sha256 = "5cf189eb6847b4f8fc603a3ffff3b0771c08eec7dd4bd961bfd45477dd13eb73",
    strip_prefix = "googletest-609281088cfefc76f9d0ce82e1ff6c30cc3591e5",
    urls = ["https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip"],
)

http_archive(
    name = "build_bazel_apple_support",
    sha256 = "76df040ade90836ff5543888d64616e7ba6c3a7b33b916aa3a4b68f342d1b447",
    url = "https://github.com/bazelbuild/apple_support/releases/download/0.11.0/apple_support.0.11.0.tar.gz",
)

load(
    "@build_bazel_apple_support//lib:repositories.bzl",
    "apple_support_dependencies",
)

apple_support_dependencies()

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
    name = "rules_rust",
    sha256 = "ab397b26e75597df5cc0c0fa2e0506bdf0c140c79045145a88a0c32745246352",
    strip_prefix = "rules_rust-5225e23c9f545c2e990691afcdb6744927a49eeb",
    url = "https://github.com/bazelbuild/rules_rust/archive/5225e23c9f545c2e990691afcdb6744927a49eeb.tar.gz",
)

load("@rules_rust//rust:repositories.bzl", "rules_rust_dependencies")

rules_rust_dependencies()

load("//bazel/rules/rust:repositories.bzl", "rust_repositories")

RUST_ISO_DATE = "2022-01-20"

RUST_VERSION = "nightly"

rust_repositories(
    edition = "2021",
    iso_date = RUST_ISO_DATE,
    rustfmt_version = "nightly",
    version = RUST_VERSION,
)

load("@rules_rust//crate_universe:bootstrap.bzl", "crate_universe_bootstrap")

crate_universe_bootstrap()

load("@rules_rust//crate_universe:defs.bzl", "crate_universe")

crate_universe(
    name = "crates",
    cargo_toml_files = [
        "//risc0/core:Cargo.toml",
        "//risc0/zkvm/sdk/rust/core:Cargo.toml",
        "//risc0/zkvm/sdk/rust/guest:Cargo.toml",
        "//risc0/zkvm/sdk/rust/host:Cargo.toml",
        "//risc0/zkvm/sdk/rust/serde:Cargo.toml",
        "//examples/rust/battleship:Cargo.toml",
        "//examples/rust/battleship/core:Cargo.toml",
        "//examples/rust/digital_signature:Cargo.toml",
        "//examples/rust/digital_signature/core:Cargo.toml",
    ],
    resolver = "@rules_rust_crate_universe_bootstrap//:crate_universe_resolver",
    supported_targets = [
        "i686-pc-windows-msvc",
        "x86_64-pc-windows-msvc",
        "aarch64-apple-darwin",
        "x86_64-apple-darwin",
        "x86_64-unknown-linux-gnu",
        "riscv32im-unknown-none-elf",
    ],
)

load("@crates//:defs.bzl", "pinned_rust_install")

pinned_rust_install()

http_archive(
    name = "oneTBB",
    build_file = "//bazel/third_party:oneTBB.BUILD",
    sha256 = "e5b57537c741400cf6134b428fc1689a649d7d38d9bb9c1b6d64f092ea28178a",
    strip_prefix = "oneTBB-2021.5.0",
    url = "https://github.com/oneapi-src/oneTBB/archive/refs/tags/v2021.5.0.tar.gz",
)

http_archive(
    name = "rules_python",
    sha256 = "a30abdfc7126d497a7698c29c46ea9901c6392d6ed315171a6df5ce433aa4502",
    strip_prefix = "rules_python-0.6.0",
    url = "https://github.com/bazelbuild/rules_python/archive/0.6.0.tar.gz",
)

http_archive(
    name = "rules_conda",
    sha256 = "9793f86162ec5cfb32a1f1f13f5bf776e2c06b243c4f1ee314b9ec870144220d",
    url = "https://github.com/spietras/rules_conda/releases/download/0.1.0/rules_conda-0.1.0.zip",
)

load("@rules_conda//:defs.bzl", "conda_create", "load_conda", "register_toolchain")

load_conda(
    install_mamba = True,
    installer = "miniforge",
    quiet = False,
)

conda_create(
    name = "py3_env",
    environment = "@//:environment.yml",
    quiet = False,
    use_mamba = True,
)

register_toolchain(py3_env = "py3_env")
