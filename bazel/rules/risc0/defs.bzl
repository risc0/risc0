load("//bazel/rules/rust:defs.bzl", "risc0_rust_binary")
load("//bazel/toolchain/risc0:defs.bzl", "risc0_cc_binary")

def _impl(ctx):
    out = ctx.actions.declare_file(ctx.attr.name)
    ctx.actions.run(
        mnemonic = "MakeCodeID",
        executable = ctx.executable._tool,
        arguments = [ctx.file.elf.path, out.path],
        inputs = depset(direct = ctx.files.elf),
        outputs = [out],
        tools = [ctx.executable._tool],
    )
    return [DefaultInfo(files = depset([out]))]

risc0_codeid = rule(
    implementation = _impl,
    attrs = {
        "elf": attr.label(
            mandatory = True,
            allow_single_file = True,
        ),
        "_tool": attr.label(
            default = "//risc0/zkp/prove/make-id",
            executable = True,
            allow_single_file = True,
            cfg = "host",
        ),
    },
)

def risc0_cc_proof(name, **kwargs):
    risc0_cc_binary(
        name = name,
        **kwargs
    )
    risc0_codeid(
        name = name + ".id",
        elf = name,
        visibility = ["//visibility:public"],
    )

def risc0_rust_proof(name, **kwargs):
    risc0_rust_binary(
        name = name,
        **kwargs
    )
    risc0_codeid(
        name = name + ".id",
        elf = name,
        visibility = ["//visibility:public"],
    )
