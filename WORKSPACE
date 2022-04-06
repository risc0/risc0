workspace(name = "risc0")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_rust",
    sha256 = "b58c63a6d8221f408f8852b4f74f81bc8c7aac9273f3899a74e32e6168a2c624",
    url = "https://github.com/bazelbuild/rules_rust/releases/download/0.2.1/rules_rust-v0.2.1.tar.gz",
)

load("@rules_rust//rust:repositories.bzl", "rules_rust_dependencies")

rules_rust_dependencies()

load("@rules_rust//tools/rust_analyzer:deps.bzl", "rust_analyzer_deps")

rust_analyzer_deps()

load("//bazel/rules/rust:repositories.bzl", "rust_repositories")

RUST_ISO_DATE = "2022-01-20"

RUST_VERSION = "nightly"

rust_repositories(
    edition = "2021",
    iso_date = RUST_ISO_DATE,
    rustfmt_version = "nightly",
    version = RUST_VERSION,
)

load("@rules_rust//crate_universe:repositories.bzl", "crate_universe_dependencies")

crate_universe_dependencies()

load("@rules_rust//crate_universe:defs.bzl", "crate", "crates_repository")

crates_repository(
    name = "crates_host",
    lockfile = "//:Cargo-host.Bazel.lock",
    packages = {
        "clap": crate.spec(version = "3.1"),
        "ctor": crate.spec(version = "0.1"),
        "env_logger": crate.spec(version = "0.8"),
        "log": crate.spec(version = "0.4"),
        "serde": crate.spec(version = "1.0"),
        "sha2": crate.spec(version = "0.10"),
        "yew": crate.spec(version = "0.19"),
    },
    quiet = False,
)

load("@crates_host//:defs.bzl", "crate_repositories")

crate_repositories()

crates_repository(
    name = "crates_guest",
    lockfile = "//:Cargo-guest.Bazel.lock",
    packages = {
        "serde": crate.spec(
            default_features = False,
            features = [
                "alloc",
                "derive",
            ],
            version = "1.0",
        ),
    },
    quiet = False,
)

load("@crates_guest//:defs.bzl", crate_repositories_guest = "crate_repositories")

crate_repositories_guest()
