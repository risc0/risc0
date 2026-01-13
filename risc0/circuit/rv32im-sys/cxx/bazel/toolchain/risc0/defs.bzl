# buildifier: disable=module-docstring
load("//bazel/platform:transitions.bzl", "risc0_transition")

# https://github.com/bazelbuild/bazel/blob/master/src/main/starlark/builtins_bzl/common/cc/cc_library.bzl

CC_TOOLCHAIN_TYPE = "@bazel_tools//tools/cpp:toolchain_type"

def _get_compilation_contexts_from_deps(deps):
    compilation_contexts = []
    for dep in deps:
        if CcInfo in dep:
            compilation_contexts.append(dep[CcInfo].compilation_context)
    return compilation_contexts

def _get_linking_contexts_from_deps(deps):
    linking_contexts = []
    for dep in deps:
        if CcInfo in dep:
            linking_contexts.append(dep[CcInfo].linking_context)
    return linking_contexts

def _compile(ctx, cc_toolchain, feature_configuration):
    compilation_contexts = _get_compilation_contexts_from_deps(ctx.attr.deps)
    return cc_common.compile(
        name = ctx.label.name,
        actions = ctx.actions,
        cc_toolchain = cc_toolchain,
        feature_configuration = feature_configuration,
        srcs = ctx.files.srcs,
        user_compile_flags = ctx.attr.copts,
        defines = ctx.attr.defines,
        local_defines = ctx.attr.local_defines,
        compilation_contexts = compilation_contexts,
        public_hdrs = ctx.files.hdrs,
        additional_inputs = ctx.files.aux_srcs,
        includes = ctx.attr.includes,
        include_prefix = ctx.attr.include_prefix,
        strip_include_prefix = ctx.attr.strip_include_prefix,
    )

def _risc0_cc_library_impl(ctx):
    cc_toolchain = ctx.toolchains[CC_TOOLCHAIN_TYPE].cc
    feature_configuration = cc_common.configure_features(
        ctx = ctx,
        cc_toolchain = cc_toolchain,
        requested_features = ctx.features,
        unsupported_features = ctx.disabled_features,
    )
    (compile_context, compilation_outputs) = _compile(ctx, cc_toolchain, feature_configuration)
    linking_contexts = _get_linking_contexts_from_deps(ctx.attr.deps)
    (linking_context, linking_outputs) = cc_common.create_linking_context_from_compilation_outputs(
        actions = ctx.actions,
        name = ctx.label.name,
        compilation_outputs = compilation_outputs,
        cc_toolchain = cc_toolchain,
        feature_configuration = feature_configuration,
        linking_contexts = linking_contexts,
        user_link_flags = ctx.attr.linkopts,
        alwayslink = ctx.attr.alwayslink,
        disallow_dynamic_library = True,
    )
    files_builder = []
    if linking_outputs.library_to_link != None:
        artifacts_to_build = linking_outputs.library_to_link
        if artifacts_to_build.static_library != None:
            files_builder.append(artifacts_to_build.static_library)
        if artifacts_to_build.pic_static_library != None:
            files_builder.append(artifacts_to_build.pic_static_library)
    return [
        DefaultInfo(files = depset(files_builder)),
        CcInfo(
            compilation_context = compile_context,
            linking_context = linking_context,
        ),
    ]

def _risc0_cc_binary_impl(ctx):
    cc_toolchain = ctx.toolchains[CC_TOOLCHAIN_TYPE].cc
    feature_configuration = cc_common.configure_features(
        ctx = ctx,
        cc_toolchain = cc_toolchain,
        requested_features = ctx.features,
        unsupported_features = ctx.disabled_features,
    )
    (compile_context, compilation_outputs) = _compile(ctx, cc_toolchain, feature_configuration)
    linking_contexts = _get_linking_contexts_from_deps(ctx.attr.deps)
    linking_outputs = cc_common.link(
        name = ctx.label.name,
        actions = ctx.actions,
        feature_configuration = feature_configuration,
        cc_toolchain = cc_toolchain,
        compilation_outputs = compilation_outputs,
        linking_contexts = linking_contexts,
        user_link_flags = ["-T", ctx.file._linker_script.path] + ctx.attr.linkopts,
        output_type = "executable",
    )
    runfiles = ctx.runfiles(files = [linking_outputs.executable])
    for data_dep in ctx.attr.data:
        runfiles = runfiles.merge(ctx.runfiles(transitive_files = data_dep[DefaultInfo].files))
        runfiles = runfiles.merge(data_dep[DefaultInfo].data_runfiles)
    for src in ctx.attr.srcs:
        runfiles = runfiles.merge(src[DefaultInfo].default_runfiles)
    for dep in ctx.attr.deps:
        runfiles = runfiles.merge(dep[DefaultInfo].default_runfiles)
    return [DefaultInfo(
        files = depset([linking_outputs.executable]),
        runfiles = runfiles,
    )]

attrs = {
    "srcs": attr.label_list(allow_files = True),
    "hdrs": attr.label_list(allow_files = True),
    "aux_srcs": attr.label_list(allow_files = True),
    "includes": attr.string_list(),
    "defines": attr.string_list(),
    "copts": attr.string_list(),
    "linkopts": attr.string_list(),
    "local_defines": attr.string_list(),
    "alwayslink": attr.bool(default = False),
    "strip_include_prefix": attr.string(),
    "include_prefix": attr.string(),
    "deps": attr.label_list(providers = [CcInfo]),
    "data": attr.label_list(allow_files = True),
    "_linker_script": attr.label(
        allow_single_file = True,
        default = Label("//bazel/toolchain/risc0:risc0.ld"),
    ),
    "_allowlist_function_transition": attr.label(
        default = "@bazel_tools//tools/allowlists/function_transition_allowlist",
    ),
}

risc0_cc_library = rule(
    implementation = _risc0_cc_library_impl,
    attrs = attrs,
    toolchains = [CC_TOOLCHAIN_TYPE],
    fragments = ["cpp"],
    incompatible_use_toolchain_transition = True,
    cfg = risc0_transition,
)

risc0_cc_binary = rule(
    implementation = _risc0_cc_binary_impl,
    attrs = attrs,
    toolchains = [CC_TOOLCHAIN_TYPE],
    fragments = ["cpp"],
    incompatible_use_toolchain_transition = True,
    cfg = risc0_transition,
)
