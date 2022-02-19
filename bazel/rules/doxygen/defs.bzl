def _impl(ctx):
    output_dir = ctx.actions.declare_directory("doxygen")
    doxyfile = ctx.actions.declare_file("Doxyfile")

    outs = [
        output_dir,
        ctx.actions.declare_file("doxygen/html/index.html"),
    ]

    ctx.actions.expand_template(
        template = ctx.file.doxyfile,
        output = doxyfile,
        substitutions = {
            "${INPUT}": ctx.attr.anchor.label.package,
            "${OUTPUT_DIRECTORY}": output_dir.path,
            "${WARN_AS_ERROR}": "YES",
        },
    )

    ctx.actions.run(
        mnemonic = "doxygen",
        executable = ctx.executable._tool,
        arguments = [doxyfile.path],
        inputs = depset(
            direct = [doxyfile] + ctx.files.srcs,
        ),
        outputs = outs,
        tools = [ctx.executable._tool],
    )

    return [DefaultInfo(files = depset(outs))]

doxygen = rule(
    implementation = _impl,
    attrs = {
        "doxyfile": attr.label(allow_single_file = True),
        "srcs": attr.label_list(allow_files = True),
        "anchor": attr.label(mandatory = True),
        "_tool": attr.label(
            default = Label("@py3_env//:py3_env/bin/doxygen"),
            executable = True,
            allow_files = True,
            cfg = "host",
        ),
    },
)
