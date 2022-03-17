def _impl(ctx):
    tool_file = ctx.executable._tool
    out_file = ctx.outputs.out
    ctx.actions.run_shell(
        command = "$1 > $2",
        inputs = [tool_file],
        outputs = [out_file],
        arguments = [tool_file.path, out_file.path],
    )
    return [DefaultInfo(files = depset([out_file]))]

make_circuit = rule(
    attrs = {
        "_tool": attr.label(
            default = Label("//risc0/zkp/circuit/make-circuit"),
            allow_single_file = True,
            executable = True,
            cfg = "exec",
        ),
        "out": attr.output(mandatory = True),
    },
    implementation = _impl,
)
