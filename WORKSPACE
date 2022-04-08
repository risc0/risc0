workspace(name = "risc0")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "rules_rust",
    patch_args = ["-p1"],
    patches = ["//bazel/third_party/rules_rust:urls.patch"],
    sha256 = "42248201c518960307ff256e75adc1a7d34d398acbe6118b207905ca4d045706",
    strip_prefix = "rules_rust-4144ddeb9c5290a15e5ec1cf8df31393744f6005",
    url = "https://github.com/bazelbuild/rules_rust/archive/4144ddeb9c5290a15e5ec1cf8df31393744f6005.zip",
)

load("@rules_rust//rust:repositories.bzl", "rules_rust_dependencies")

rules_rust_dependencies()

load("@rules_rust//tools/rust_analyzer:deps.bzl", "rust_analyzer_deps")

rust_analyzer_deps()

load("@rules_rust//wasm_bindgen:repositories.bzl", "rust_wasm_bindgen_repositories")

rust_wasm_bindgen_repositories()

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
