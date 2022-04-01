def _impl(ctx):
    out_file = ctx.outputs.out
    ctx.actions.run(
        mnemonic = "MakeCircuit",
        executable = ctx.executable._tool,
        arguments = [out_file.path],
        outputs = [out_file],
        tools = [ctx.executable._tool],
    )
    return [DefaultInfo(files = depset([out_file]))]

make_circuit = rule(
    attrs = {
        "_tool": attr.label(
            default = Label("//risc0/zkvm/circuit/make-circuit"),
            allow_single_file = True,
            executable = True,
            cfg = "exec",
        ),
        "out": attr.output(mandatory = True),
    },
    implementation = _impl,
)
