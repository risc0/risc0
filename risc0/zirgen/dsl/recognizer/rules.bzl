def _flex_impl(ctx):
    args = ctx.actions.args()
    args.add("-o", ctx.outputs.out)
    args.add_all(ctx.attr.flags)
    args.add_all(ctx.files.src)
    outputs = [ctx.outputs.out]
    ctx.actions.run(
        inputs = ctx.files.src,
        outputs = outputs,
        arguments = [args],
        env = {"PATH": "external/py3_env/py3_env/bin"},
        tools = [ctx.executable._flex, ctx.executable._m4],
        executable = ctx.executable._flex,
        mnemonic = "flex",
    )
    return [DefaultInfo(files = depset(outputs))]

flex = rule(
    attrs = {
        "src": attr.label(
            mandatory = True,
            allow_single_file = True,
        ),
        "out": attr.output(mandatory = True),
        "flags": attr.string_list(),
        "_flex": attr.label(
            default = "@py3_env//:py3_env/bin/flex",
            allow_single_file = True,
            executable = True,
            cfg = "exec",
        ),
        "_m4": attr.label(
            default = "@py3_env//:py3_env/bin/m4",
            allow_single_file = True,
            executable = True,
            cfg = "exec",
        ),
    },
    implementation = _flex_impl,
)

def _bison_impl(ctx):
    args = ctx.actions.args()
    args.add("-o", ctx.outputs.out)
    args.add("--defines={}".format(ctx.outputs.defines.path))
    args.add("--verbose")
    args.add_all(ctx.files.src)
    outputs = [ctx.outputs.out, ctx.outputs.defines]
    ctx.actions.run(
        inputs = ctx.files.src,
        outputs = outputs,
        arguments = [args],
        env = {"PATH": "external/py3_env/py3_env/bin"},
        tools = [ctx.executable._bison, ctx.executable._m4],
        executable = ctx.executable._bison,
        mnemonic = "bison",
    )
    return [DefaultInfo(files = depset(outputs))]

bison = rule(
    attrs = {
        "src": attr.label(
            mandatory = True,
            allow_single_file = True,
        ),
        "defines": attr.output(mandatory = True),
        "out": attr.output(mandatory = True),
        "_bison": attr.label(
            default = "@py3_env//:py3_env/bin/bison",
            allow_single_file = True,
            executable = True,
            cfg = "exec",
        ),
        "_m4": attr.label(
            default = "@py3_env//:py3_env/bin/m4",
            allow_single_file = True,
            executable = True,
            cfg = "exec",
        ),
    },
    implementation = _bison_impl,
)
