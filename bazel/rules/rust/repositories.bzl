# buildifier: disable=module-docstring
load("@rules_rust//rust/private:common.bzl", "rust_common")
load(
    "@rules_rust//rust/private:repository_utils.bzl",
    "BUILD_for_toolchain",
    "DEFAULT_STATIC_RUST_URL_TEMPLATES",
    "DEFAULT_TOOLCHAIN_NAME_PREFIX",
    "check_version_valid",
    "load_llvm_tools",
    "load_rust_compiler",
    "load_rust_src",
    "load_rust_stdlib",
    "load_rustc_dev_nightly",
    "load_rustfmt",
    "serialized_constraint_set_from_triple",
)

DEFAULT_TOOLCHAIN_TRIPLES = {
    "aarch64-apple-darwin": "rust_darwin_aarch64",
    "x86_64-apple-darwin": "rust_darwin_x86_64",
    "x86_64-pc-windows-msvc": "rust_windows_x86_64",
    "x86_64-unknown-linux-gnu": "rust_linux_x86_64",
}

def _build_sysroot(ctx, target_triple, target_json):
    target_json = ctx.path(Label(target_json))
    out_dir = "lib/rustlib/{}/lib".format(target_triple)

    ctx.download_and_extract(
        url = "https://github.com/rust-lang/compiler-builtins/archive/refs/tags/0.1.69.tar.gz",
        output = "compiler-builtins",
        sha256 = "8a1ee7a73db97d66a5e3c3f30b03c88280ca2d3be475f434e5c62df9f44718fb",
        stripPrefix = "compiler-builtins-0.1.69",
    )

    ctx.execute([
        "bin/rustc",
        "lib/rustlib/src/library/core/src/lib.rs",
        "--crate-name=core",
        "--crate-type=lib",
        "--edition=2021",
        "--codegen=opt-level=3",
        "--target={}".format(target_json),
        "--out-dir={}".format(out_dir),
    ], quiet = False)

    ctx.execute([
        "bin/rustc",
        "compiler-builtins/src/lib.rs",
        "--crate-name=compiler_builtins",
        "--crate-type=lib",
        "--codegen=opt-level=3",
        "--cfg",
        "feature=\"compiler-builtins\"",
        "--cfg",
        "feature=\"default\"",
        "--cfg",
        "feature=\"mem\"",
        "--target={}".format(target_json),
        "--out-dir={}".format(out_dir),
    ], quiet = False)

    ctx.execute([
        "bin/rustc",
        "lib/rustlib/src/library/alloc/src/lib.rs",
        "--crate-name=alloc",
        "--crate-type=lib",
        "--edition=2021",
        "--codegen=opt-level=3",
        "--target={}".format(target_json),
        "--out-dir={}".format(out_dir),
    ], quiet = False)

def _rust_toolchain_repository_impl(ctx):
    """The implementation of the rust toolchain repository rule."""

    check_version_valid(ctx.attr.version, ctx.attr.iso_date)

    # Conditionally download rustc sources. Generally used for `rust-analyzer`
    load_rust_src(ctx)

    build_components = [load_rust_compiler(ctx)]

    if ctx.attr.rustfmt_version:
        build_components.append(load_rustfmt(ctx))

    # Rust 1.45.0 and nightly builds after 2020-05-22 need the llvm-tools gzip to get the libLLVM dylib
    if ctx.attr.version >= "1.45.0" or (ctx.attr.version == "nightly" and ctx.attr.iso_date > "2020-05-22"):
        load_llvm_tools(ctx, ctx.attr.exec_triple)

    build_components.append(load_rust_stdlib(ctx, ctx.attr.exec_triple))
    if ctx.attr.dev_components:
        load_rustc_dev_nightly(ctx, ctx.attr.exec_triple)

    for target_triple, toolchain in ctx.attr.extra_toolchains.items():
        target_json = toolchain[0]
        _build_sysroot(ctx, target_triple, target_json)

        build_components.append(toolchain[1].format(
            toolchain_name = "{toolchain_prefix}_{target_triple}".format(
                toolchain_prefix = ctx.attr.toolchain_name_prefix,
                target_triple = target_triple,
            ),
            exec_triple = ctx.attr.exec_triple,
            target_triple = target_triple,
            target_json = target_json,
            workspace_name = ctx.attr.name,
            default_edition = ctx.attr.edition,
        ))

    ctx.file("WORKSPACE.bazel", "")
    ctx.file("BUILD.bazel", "\n".join(build_components))

def _rust_toolchain_repository_proxy_impl(ctx):
    build_components = [
        BUILD_for_toolchain(
            name = "{toolchain_prefix}_{target_triple}".format(
                toolchain_prefix = ctx.attr.toolchain_name_prefix,
                target_triple = ctx.attr.exec_triple,
            ),
            exec_triple = ctx.attr.exec_triple,
            parent_workspace_name = ctx.attr.parent_workspace_name,
            target_triple = ctx.attr.exec_triple,
        ),
    ]

    for target_triple, toolchain in ctx.attr.extra_toolchains.items():
        build_components.append(toolchain.format(
            name = "{toolchain_prefix}_{target_triple}".format(
                toolchain_prefix = ctx.attr.toolchain_name_prefix,
                target_triple = target_triple,
            ),
            exec_constraint_sets_serialized = serialized_constraint_set_from_triple(ctx.attr.exec_triple),
            parent_workspace_name = ctx.attr.parent_workspace_name,
        ))

    ctx.file("WORKSPACE.bazel", "")
    ctx.file("BUILD.bazel", "\n".join(build_components))

rust_toolchain_repository = repository_rule(
    attrs = {
        "dev_components": attr.bool(default = False),
        "edition": attr.string(default = rust_common.default_edition),
        "exec_triple": attr.string(mandatory = True),
        "extra_toolchains": attr.string_list_dict(),
        "iso_date": attr.string(),
        "rustfmt_version": attr.string(),
        "sha256s": attr.string_dict(),
        "toolchain_name_prefix": attr.string(),
        "urls": attr.string_list(default = DEFAULT_STATIC_RUST_URL_TEMPLATES),
        "version": attr.string(mandatory = True),
    },
    implementation = _rust_toolchain_repository_impl,
)

rust_toolchain_repository_proxy = repository_rule(
    attrs = {
        "exec_triple": attr.string(mandatory = True),
        "extra_toolchains": attr.string_dict(),
        "parent_workspace_name": attr.string(mandatory = True),
        "toolchain_name_prefix": attr.string(),
    },
    implementation = _rust_toolchain_repository_proxy_impl,
)

def _rust_repository_set(
        name,
        version,
        exec_triple,
        iso_date = None,
        rustfmt_version = None,
        edition = None,
        dev_components = False,
        urls = DEFAULT_STATIC_RUST_URL_TEMPLATES,
        register_toolchain = True):
    extra_toolchains = {
        "riscv32im-unknown-none-elf": [
            "@risc0//bazel/rules/rust:riscv32im-unknown-none-elf.json",
            """
load("@rules_rust//rust:toolchain.bzl", "rust_stdlib_filegroup")

rust_stdlib_filegroup(
    name = "rust_std-{target_triple}",
    srcs = glob(["lib/rustlib/{target_triple}/lib/*.rlib"]),
    visibility = ["//visibility:public"],
)

rust_toolchain(
    name = "{toolchain_name}_impl",
    rust_doc = "@{workspace_name}//:rustdoc",
    rust_std = "@{workspace_name}//:rust_std-{target_triple}",
    rustc = "@{workspace_name}//:rustc",
    rustfmt = "@{workspace_name}//:rustfmt_bin",
    cargo = "@{workspace_name}//:cargo",
    clippy_driver = "@{workspace_name}//:clippy_driver_bin",
    rustc_lib = "@{workspace_name}//:rustc_lib",
    rustc_srcs = "@{workspace_name}//lib/rustlib/src:rustc_srcs",
    binary_ext = "",
    staticlib_ext = ".a",
    dylib_ext = ".so",
    stdlib_linkflags = [],
    os = "none",
    default_edition = "{default_edition}",
    exec_triple = "{exec_triple}",
    target_json = "{target_json}",
    visibility = ["//visibility:public"],
)
""",
        ],
    }

    rust_toolchain_repository(
        name = name,
        exec_triple = exec_triple,
        extra_toolchains = extra_toolchains,
        iso_date = iso_date,
        toolchain_name_prefix = DEFAULT_TOOLCHAIN_NAME_PREFIX,
        version = version,
        rustfmt_version = rustfmt_version,
        edition = edition,
        dev_components = dev_components,
        urls = urls,
    )

    extra_toolchains = {
        "riscv32im-unknown-none-elf": """
toolchain(
    name = "{name}",
    exec_compatible_with = {exec_constraint_sets_serialized},
    target_compatible_with = [
        "@risc0//bazel/platform/cpu:riscv32im",
        "@risc0//bazel/platform/os:risc0"
    ],
    toolchain = "@{parent_workspace_name}//:{name}_impl",
    toolchain_type = "@rules_rust//rust:toolchain",
)
""",
    }

    rust_toolchain_repository_proxy(
        name = name + "_toolchains",
        exec_triple = exec_triple,
        extra_toolchains = extra_toolchains,
        parent_workspace_name = name,
        toolchain_name_prefix = DEFAULT_TOOLCHAIN_NAME_PREFIX,
    )

    all_toolchain_names = []
    for target_triple in [exec_triple] + extra_toolchains.keys():
        all_toolchain_names.append("@{name}_toolchains//:{toolchain_name_prefix}_{triple}".format(
            name = name,
            toolchain_name_prefix = DEFAULT_TOOLCHAIN_NAME_PREFIX,
            triple = target_triple,
        ))

    # Register toolchains
    if register_toolchain:
        native.register_toolchains(*all_toolchain_names)

def rust_repositories(
        version = rust_common.default_version,
        iso_date = None,
        rustfmt_version = None,
        edition = None,
        dev_components = False,
        urls = DEFAULT_STATIC_RUST_URL_TEMPLATES):
    for exec_triple, name in DEFAULT_TOOLCHAIN_TRIPLES.items():
        _rust_repository_set(
            name = name,
            dev_components = dev_components,
            edition = edition,
            exec_triple = exec_triple,
            iso_date = iso_date,
            rustfmt_version = rustfmt_version,
            urls = urls,
            version = version,
        )
