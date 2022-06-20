load("@rules_rust//rust:defs.bzl", "rust_library")
load("//bazel/rules/rust:defs.bzl", "risc0_rust_binary")
load("//bazel/toolchain/risc0:defs.bzl", "risc0_cc_binary")

DEFAULT_METHOD_ID_LIMIT = 12

def _impl(ctx):
    out = ctx.actions.declare_file(ctx.attr.name)
    ctx.actions.run(
        mnemonic = "MakeMethodID",
        executable = ctx.executable._tool,
        arguments = [ctx.file.elf.path, out.path, "--limit", str(ctx.attr.limit)],
        inputs = depset(direct = ctx.files.elf),
        outputs = [out],
        tools = [ctx.executable._tool],
    )
    runfiles = ctx.runfiles(files = [out])
    return [DefaultInfo(files = depset([out]), runfiles = runfiles)]

risc0_method_id = rule(
    implementation = _impl,
    attrs = {
        "elf": attr.label(
            mandatory = True,
            allow_single_file = True,
        ),
        "limit": attr.int(default = DEFAULT_METHOD_ID_LIMIT),
        "_tool": attr.label(
            default = "//risc0/zkvm/prove/make-id",
            executable = True,
            allow_single_file = True,
            cfg = "host",
        ),
    },
)

def risc0_cc_method(name, limit = DEFAULT_METHOD_ID_LIMIT, **kwargs):
    risc0_cc_binary(
        name = name,
        **kwargs
    )
    risc0_method_id(
        name = name + ".id",
        elf = name,
        limit = limit,
        visibility = ["//visibility:public"],
    )

def risc0_rust_method(name, limit = DEFAULT_METHOD_ID_LIMIT, **kwargs):
    risc0_rust_binary(
        name = name,
        **kwargs
    )
    risc0_method_id(
        name = name + ".id",
        elf = name,
        limit = limit,
        visibility = ["//visibility:public"],
    )

def risc0_rust_library_pair(
        name,
        deps = [],
        crate_features = [],
        proc_macro_deps = [],
        host_deps = [],
        guest_deps = [],
        host_features = [],
        guest_features = [],
        host_proc_macro_deps = [],
        guest_proc_macro_deps = [],
        **kwargs):
    rust_library(
        name = name + "_host",
        crate_features = crate_features + host_features,
        deps = deps + host_deps,
        proc_macro_deps = proc_macro_deps + host_proc_macro_deps,
        **kwargs
    )

    rust_library(
        name = name + "_guest",
        crate_features = crate_features + guest_features,
        deps = deps + guest_deps,
        proc_macro_deps = proc_macro_deps + guest_proc_macro_deps,
        **kwargs
    )
