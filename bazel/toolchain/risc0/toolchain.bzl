# https://github.com/adambreland/cpp-simple_bazel_cpp_toolchain
# https://github.com/bazelbuild/rules_cc/blob/main/cc/private/toolchain/cc_toolchain_config.bzl

load("@bazel_skylib//rules:common_settings.bzl", "BuildSettingInfo")
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool_path",
    "with_feature_set",
)
load("@bazel_tools//tools/build_defs/cc:action_names.bzl", "ACTION_NAMES")

def _impl(ctx):
    root = ctx.attr.root[BuildSettingInfo].value
    tool_paths = [tool_path(name = tool, path = "{}/bin/riscv64-unknown-elf-{}".format(root, tool)) for tool in [
        "ar",
        "cpp",
        "gcc",
        "gcov",
        "ld",
        "nm",
        "objdump",
        "strip",
    ]]

    compile_actions = [
        ACTION_NAMES.assemble,
        ACTION_NAMES.preprocess_assemble,
        ACTION_NAMES.linkstamp_compile,
        ACTION_NAMES.c_compile,
        ACTION_NAMES.cpp_compile,
        ACTION_NAMES.cpp_header_parsing,
        ACTION_NAMES.cpp_module_compile,
        ACTION_NAMES.cpp_module_codegen,
        ACTION_NAMES.lto_backend,
        ACTION_NAMES.clif_match,
    ]

    link_actions = [
        ACTION_NAMES.cpp_link_executable,
    ]

    common_flags = [
        "-DRISCV=1",
        "-mabi=ilp32",
        "-march=rv32im",
        "-nostdlib",
        "-ffreestanding",
        "-fno-common",
        "-fno-exceptions",
        "-fno-non-call-exceptions",
        "-fno-rtti",
        "-fno-strict-aliasing",
        "-fno-threadsafe-statics",
        "-fno-use-cxa-atexit",
    ]

    default_compile_flags_feature = feature(
        name = "default_compile_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = compile_actions,
                flag_groups = [
                    flag_group(
                        flags = common_flags + [
                            "-Wall",
                            "-Wunused-but-set-parameter",
                            "-Wno-free-nonheap-object",
                            "-Wno-error=pragmas",
                            "-Wno-unknown-pragmas",
                        ],
                    ),
                ],
            ),
            flag_set(
                actions = compile_actions,
                flag_groups = [flag_group(flags = ["-g"])],
                with_features = [with_feature_set(features = ["dbg"])],
            ),
            flag_set(
                actions = compile_actions,
                flag_groups = [flag_group(flags = [
                    "-fdata-sections",
                    "-ffunction-sections",
                    "-g0",
                    "-O2",
                ])],
                with_features = [with_feature_set(features = ["opt"])],
            ),
        ],
    )

    unfiltered_compile_flags_feature = feature(
        name = "unfiltered_compile_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = compile_actions,
                flag_groups = [
                    flag_group(
                        flags = [
                            "-fno-canonical-system-headers",
                            "-Wno-builtin-macro-redefined",
                            '-D__DATE__="redacted"',
                            '-D__TIMESTAMP__="redacted"',
                            '-D__TIME__="redacted"',
                        ],
                    ),
                ],
            ),
        ],
    )

    user_compile_flags_feature = feature(
        name = "user_compile_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = compile_actions,
                flag_groups = [
                    flag_group(
                        flags = ["%{user_compile_flags}"],
                        iterate_over = "user_compile_flags",
                        expand_if_available = "user_compile_flags",
                    ),
                ],
            ),
        ],
    )

    default_link_flags_feature = feature(
        name = "default_link_flags",
        enabled = True,
        flag_sets = [
            flag_set(
                actions = link_actions,
                flag_groups = [
                    flag_group(
                        flags = common_flags + [
                            "-Wl,--orphan-handling=warn",
                            "-pass-exit-codes",
                        ],
                    ),
                ],
            ),
            flag_set(
                actions = link_actions,
                flag_groups = [flag_group(flags = ["-Wl,--gc-sections"])],
                with_features = [with_feature_set(features = ["opt"])],
            ),
        ],
    )

    cxx_builtin_include_directories = [
        root + "/riscv64-unknown-elf/include/c++/11.1.0",
        root + "/riscv64-unknown-elf/include/c++/11.1.0/riscv64-unknown-elf",
        root + "/riscv64-unknown-elf/include/c++/11.1.0/backward",
        root + "/lib/gcc/riscv64-unknown-elf/11.1.0/include",
        root + "/lib/gcc/riscv64-unknown-elf/11.1.0/include-fixed",
        root + "/riscv64-unknown-elf/include",
    ]

    dbg_feature = feature(name = "dbg")
    opt_feature = feature(name = "opt")

    features = [
        default_compile_flags_feature,
        default_link_flags_feature,
        dbg_feature,
        opt_feature,
        user_compile_flags_feature,
        unfiltered_compile_flags_feature,
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        abi_libc_version = "unknown",
        abi_version = "unknown",
        compiler = "riscv64-unknown-elf-gcc (GCC) 11.1.0",
        cxx_builtin_include_directories = cxx_builtin_include_directories,
        features = features,
        host_system_name = "local",
        target_cpu = "riscv32",
        target_libc = "unknown",
        target_system_name = "riscv64-unknown-elf",
        tool_paths = tool_paths,
        toolchain_identifier = "riscv64-unknown-elf-gcc",
    )

gcc_toolchain_config = rule(
    attrs = {
        "root": attr.label(),
    },
    provides = [CcToolchainConfigInfo],
    implementation = _impl,
)
