# buildifier: disable=module-docstring
load("@rules_rust//rust/private:common.bzl", "rust_common")
load("@rules_rust//rust/private:rustc.bzl", "rustc_compile_action")
load(
    "@rules_rust//rust/private:utils.bzl",
    "compute_crate_name",
    "find_toolchain",
    "transform_deps",
)
load("//bazel/platform:transitions.bzl", "risc0_transition")

def get_edition(attr, toolchain):
    if getattr(attr, "edition"):
        return attr.edition
    else:
        return toolchain.default_edition

def _assert_correct_dep_mapping(ctx):
    """Forces a failure if proc_macro_deps and deps are mixed inappropriately

    Args:
        ctx (ctx): The current rule's context object
    """
    for dep in ctx.attr.deps:
        if rust_common.crate_info in dep:
            if dep[rust_common.crate_info].type == "proc-macro":
                fail(
                    "{} listed {} in its deps, but it is a proc-macro. It should instead be in the bazel property proc_macro_deps.".format(
                        ctx.label,
                        dep.label,
                    ),
                )
    for dep in ctx.attr.proc_macro_deps:
        type = dep[rust_common.crate_info].type
        if type != "proc-macro":
            fail(
                "{} listed {} in its proc_macro_deps, but it is not proc-macro, it is a {}. It should probably instead be listed in deps.".format(
                    ctx.label,
                    dep.label,
                    type,
                ),
            )

def _crate_root_src(attr, srcs, crate_type):
    default_crate_root_filename = "main.rs" if crate_type == "bin" else "lib.rs"

    crate_root = None
    if hasattr(attr, "crate_root"):
        if attr.crate_root:
            crate_root = attr.crate_root.files.to_list()[0]

    if not crate_root:
        crate_root = (
            (srcs[0] if len(srcs) == 1 else None) or
            _shortest_src_with_basename(srcs, default_crate_root_filename) or
            _shortest_src_with_basename(srcs, attr.name + ".rs")
        )
    if not crate_root:
        file_names = [default_crate_root_filename, attr.name + ".rs"]
        fail("No {} source file found.".format(" or ".join(file_names)), "srcs")
    return crate_root

def _shortest_src_with_basename(srcs, basename):
    shortest = None
    for f in srcs:
        if f.basename == basename:
            if not shortest or len(f.dirname) < len(shortest.dirname):
                shortest = f
    return shortest

def _rust_binary_impl(ctx):
    toolchain = find_toolchain(ctx)
    crate_name = compute_crate_name(ctx.label, toolchain, ctx.attr.crate_name)
    _assert_correct_dep_mapping(ctx)

    output = ctx.actions.declare_file(ctx.label.name + toolchain.binary_ext)

    deps = transform_deps(ctx.attr.deps)
    proc_macro_deps = transform_deps(ctx.attr.proc_macro_deps)

    return rustc_compile_action(
        ctx = ctx,
        attr = ctx.attr,
        toolchain = toolchain,
        crate_info = rust_common.create_crate_info(
            name = crate_name,
            type = ctx.attr.crate_type,
            root = _crate_root_src(ctx.attr, ctx.files.srcs, ctx.attr.crate_type),
            srcs = depset(ctx.files.srcs),
            deps = depset(deps),
            proc_macro_deps = depset(proc_macro_deps),
            aliases = ctx.attr.aliases,
            output = output,
            edition = get_edition(ctx.attr, toolchain),
            rustc_env = ctx.attr.rustc_env,
            is_test = False,
            compile_data = depset(ctx.files.compile_data),
            owner = ctx.label,
        ),
    )

_common_providers = [
    rust_common.crate_info,
    rust_common.dep_info,
    DefaultInfo,
]

_common_attrs = {
    "aliases": attr.label_keyed_string_dict(),
    "compile_data": attr.label_list(allow_files = True),
    "crate_features": attr.string_list(),
    "crate_name": attr.string(),
    "crate_root": attr.label(allow_single_file = [".rs"]),
    "data": attr.label_list(allow_files = True),
    "deps": attr.label_list(),
    "edition": attr.string(),
    "proc_macro_deps": attr.label_list(
        cfg = "exec",
        providers = [rust_common.crate_info],
    ),
    "rustc_env": attr.string_dict(),
    "rustc_env_files": attr.label_list(allow_files = True),
    "rustc_flags": attr.string_list(),
    "srcs": attr.label_list(allow_files = [".rs"]),
    "stamp": attr.int(
        default = -1,
        values = [1, 0, -1],
    ),
    "version": attr.string(default = "0.0.0"),
    "_cc_toolchain": attr.label(default = "@bazel_tools//tools/cpp:current_cc_toolchain"),
    "_error_format": attr.label(default = "@rules_rust//:error_format"),
    "_extra_rustc_flags": attr.label(default = "@rules_rust//:extra_rustc_flags"),
    "_process_wrapper": attr.label(
        default = Label("@rules_rust//util/process_wrapper"),
        executable = True,
        allow_single_file = True,
        cfg = "exec",
    ),
    "_stamp_flag": attr.label(default = Label("@rules_rust//rust/private:stamp")),
}

_rust_binary_attrs = {
    "crate_type": attr.string(default = "bin"),
    "linker_script": attr.label(
        cfg = "exec",
        allow_single_file = True,
        default = Label("//risc0/zkvm/platform:risc0.ld"),
    ),
    "out_binary": attr.bool(default = False),
    "_grep_includes": attr.label(
        allow_single_file = True,
        cfg = "exec",
        default = Label("@bazel_tools//tools/cpp:grep-includes"),
        executable = True,
    ),
    "_allowlist_function_transition": attr.label(
        default = "@bazel_tools//tools/allowlists/function_transition_allowlist",
    ),
}

risc0_rust_binary = rule(
    implementation = _rust_binary_impl,
    provides = _common_providers,
    attrs = dict(_common_attrs.items() + _rust_binary_attrs.items()),
    executable = True,
    fragments = ["cpp"],
    host_fragments = ["cpp"],
    toolchains = [
        str(Label("@rules_rust//rust:toolchain")),
        "@bazel_tools//tools/cpp:toolchain_type",
    ],
    incompatible_use_toolchain_transition = True,
    cfg = risc0_transition,
)
