load("@bazel_skylib//rules:common_settings.bzl", "BuildSettingInfo")

_TOOLCHAIN_TYPE = "//bazel/rules/clang_format:toolchain_type"

def _clang_format_toolchain_impl(ctx):
    return platform_common.ToolchainInfo(
        clang_format = ctx.executable.clang_format,
        diff_tool = ctx.executable.diff_tool,
    )

clang_format_toolchain = rule(
    doc = "A toolchain providing binaries required for `clang-format` rules.",
    implementation = _clang_format_toolchain_impl,
    attrs = {
        "clang_format": attr.label(
            doc = "A `clang-format` binary",
            allow_single_file = True,
            cfg = "exec",
            executable = True,
            mandatory = True,
        ),
        "diff_tool": attr.label(
            doc = (
                "A diff binary used to produce diffs. Thus must conform to " +
                "the `{diff_tool} {src1} {src2}` api"
            ),
            allow_single_file = True,
            cfg = "exec",
            executable = True,
        ),
    },
)

def _find_formattable_srcs(target, aspect_ctx):
    """Parse a target for clang-format formattable sources.

    Args:
        target (Target): The target the aspect is running on.
        aspect_ctx (ctx, optional): The aspect's context object.

    Returns:
        list: A list of formattable sources (`File`).
    """
    if CcInfo not in target:
        return []

    # Ignore external targets
    if target.label.workspace_root.startswith("external"):
        return []

    # Targets annotated with `noformat` will not be formatted
    if aspect_ctx and "noformat" in aspect_ctx.rule.attr.tags:
        return []

    # Collect all source files
    srcs = []
    for attr in aspect_ctx.attr._source_attrs[BuildSettingInfo].value:
        srcs.extend(getattr(aspect_ctx.rule.files, attr, list()))

    # Filter out any duplicate or generated files
    srcs = [src for src in depset(srcs).to_list() if src.is_source]

    # Filter out any sources that don't match the correct extension
    srcs = [src for src in srcs if src.extension in aspect_ctx.attr._extensions[BuildSettingInfo].value]

    return sorted(srcs)

def _perform_check(ctx, target, srcs):
    """Run `clang-format` and errors out if a defect is detected

    Args:
        ctx (ctx): The rule's or aspect's context object
        target (target): The aspect target
        srcs (list): A list of File objects

    Returns:
        path: An indicator that `clang-format` ran successfully.
    """
    toolchain = ctx.toolchains[Label(_TOOLCHAIN_TYPE)]

    marker = ctx.actions.declare_file(ctx.label.name + ".clang_format.ok")
    config = ctx.file._config

    tools = [toolchain.clang_format]
    args = ctx.actions.args()
    args.add("--touch-file", marker)

    args.add("--config-file", config)
    for src in srcs:
        args.add("--source-file", src)

    if toolchain.diff_tool:
        tools.append(toolchain.diff_tool)
        args.add("--diff-tool-file", toolchain.diff_tool)
        args.add("--")
        args.add(toolchain.clang_format)
        args.add("-style=file")
        args.add("-i")
    else:
        args.add("--")
        args.add(toolchain.clang_format)
        args.add("-style=file")
        args.add("-Werror")
        args.add("-dry-run")

    ctx.actions.run(
        executable = ctx.executable._process_wrapper,
        inputs = srcs + [config],
        outputs = [marker],
        tools = tools,
        arguments = [args],
        mnemonic = "ClangFormat",
        progress_message = "Running clang-format on '{}'".format(
            target.label,
        ),
        use_default_shell_env = True,
    )

    return marker

def _generate_manifest(ctx, srcs):
    """Create a `clang_format_manifest` output file

    Args:
        ctx (ctx): The rule's or aspect's context object
        srcs (list): A list of File objects

    Returns:
        File: The manifest
    """
    manifest = ctx.actions.declare_file(ctx.label.name + ".clang_format.manifest")
    ctx.actions.write(
        manifest,
        content = "\n".join([src.short_path for src in srcs]),
    )

    return manifest

def _clang_format_aspect_impl(target, ctx):
    srcs = _find_formattable_srcs(target, ctx)

    # If there are no formattable sources, do nothing.
    if not srcs:
        return []

    marker = _perform_check(ctx, target, srcs)
    manifest = _generate_manifest(ctx, srcs)

    return [
        OutputGroupInfo(
            clang_format_checks = depset([marker]),
            clang_format_manifest = depset([manifest]),
        ),
    ]

clang_format_aspect = aspect(
    implementation = _clang_format_aspect_impl,
    attrs = {
        "_config": attr.label(
            doc = "The `.clang-format` file used for formatting",
            allow_single_file = True,
            default = Label("//bazel/rules/clang_format:config"),
        ),
        "_extensions": attr.label(
            doc = (
                "A list of file extensions to formattable sources. This " +
                "flag enables accommodations for other rules which consume " +
                "C/C++ source files."
            ),
            default = Label("//bazel/rules/clang_format:extensions"),
        ),
        "_process_wrapper": attr.label(
            doc = "A process wrapper for running clang-format on all platforms",
            cfg = "exec",
            executable = True,
            default = Label("//bazel/rules/clang_format:wrapper"),
        ),
        "_source_attrs": attr.label(
            doc = (
                "A list of attributes on the target that contain " +
                "formattable sources. These attributes must satisfy the " +
                "`files` api (meaning `allow_files = True` is set). This " +
                "flag enables accommodations for other rules which consume " +
                "C/C++ source files."
            ),
            default = Label("//bazel/rules/clang_format:source_attrs"),
        ),
    },
    incompatible_use_toolchain_transition = True,
    fragments = ["cpp"],
    host_fragments = ["cpp"],
    toolchains = [
        str(Label(_TOOLCHAIN_TYPE)),
    ],
)
