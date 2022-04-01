load("//bazel/rules/rust:defs.bzl", "risc0_rust_binary")
load("//bazel/toolchain/risc0:defs.bzl", "risc0_cc_binary")

def _impl(ctx):
    out = ctx.actions.declare_file(ctx.attr.name)
    ctx.actions.run(
        mnemonic = "MakeMethodID",
        executable = ctx.executable._tool,
        arguments = [ctx.file.elf.path, out.path],
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
        "_tool": attr.label(
            default = "//risc0/zkvm/prove/make-id",
            executable = True,
            allow_single_file = True,
            cfg = "host",
        ),
    },
)

def risc0_cc_method(name, **kwargs):
    risc0_cc_binary(
        name = name,
        **kwargs
    )
    risc0_method_id(
        name = name + ".id",
        elf = name,
        visibility = ["//visibility:public"],
    )

def risc0_rust_method(name, **kwargs):
    risc0_rust_binary(
        name = name,
        **kwargs
    )
    risc0_method_id(
        name = name + ".id",
        elf = name,
        visibility = ["//visibility:public"],
    )
