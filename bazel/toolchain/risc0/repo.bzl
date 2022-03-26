TOOLCHAINS = [
    struct(
        archive = "riscv32im-osx-arm64",
        host_arch = "@platforms//cpu:arm64",
        host_os = "@platforms//os:osx",
        sha256 = "740c69bbad8accc97477cbbb2e720593ee14350fc73a4409f0c10880f288ed1a",
        version = "2022.03.25",
    ),
    struct(
        archive = "riscv32im-osx-x86_64",
        host_arch = "@platforms//cpu:x86_64",
        host_os = "@platforms//os:osx",
        sha256 = "3ed786e06a15a398ef0ee6689ef4b2a49ef48f5a500a9bb5c24bdf876aae5cac",
        version = "2022.03.25",
    ),
    struct(
        archive = "riscv32im-linux-x86_64",
        host_arch = "@platforms//cpu:x86_64",
        host_os = "@platforms//os:linux",
        sha256 = "5c9ca976be5410c371d37f8b42ee2a5c86e8b6fb31eedb755e9ee2cac2ccf53b",
        version = "2022.03.25",
    ),
    struct(
        archive = "riscv32im-windows-x86_64",
        host_arch = "@platforms//cpu:x86_64",
        host_os = "@platforms//os:windows",
        sha256 = "8ec9208f108e79dfbf341d020fc0c49833200b7eac49f1dcae5e33a6028de38a",
        version = "2022.03.25",
    ),
]

def _repo_impl(rctx):
    rctx.template(
        "BUILD.bazel",
        Label("//bazel/toolchain/risc0:repo.tpl.BUILD"),
        {
            "{workspace}": rctx.name,
        },
    )

    rctx.file(
        "gcc_toolchain.bzl",
        content = rctx.read(Label("//bazel/toolchain/risc0:gcc_toolchain.bzl")),
        executable = False,
    )

    rctx.download_and_extract(
        url = "https://github.com/risc0/toolchain/releases/download/{version}/{archive}.tar.xz".format(
            archive = rctx.attr.archive,
            version = rctx.attr.version,
        ),
        sha256 = rctx.attr.sha256,
        stripPrefix = rctx.attr.archive,
    )

risc0_toolchain_repo = repository_rule(
    attrs = {
        "version": attr.string(
            mandatory = True,
            doc = "One of the versions of the RISC-V toolchain from https://github.com/risc0/toolchain",
        ),
        "archive": attr.string(mandatory = True),
        "sha256": attr.string(mandatory = True),
    },
    implementation = _repo_impl,
)

def _proxy_impl(rctx):
    rctx.template(
        "BUILD.bazel",
        Label("//bazel/toolchain/risc0:proxy.tpl.BUILD"),
        {
            "{host_arch}": rctx.attr.host_arch,
            "{host_os}": rctx.attr.host_os,
            "{toolchain}": rctx.attr.toolchain,
        },
    )

risc0_toolchain_proxy = repository_rule(
    attrs = {
        "host_arch": attr.string(mandatory = True),
        "host_os": attr.string(mandatory = True),
        "toolchain": attr.string(mandatory = True),
    },
    implementation = _proxy_impl,
)

def risc0_toolchain(name):
    toolchain_names = []
    for toolchain in TOOLCHAINS:
        repo_name = "{name}_{suffix}".format(name = name, suffix = toolchain.archive)
        risc0_toolchain_repo(
            name = repo_name,
            version = toolchain.version,
            archive = toolchain.archive,
            sha256 = toolchain.sha256,
        )

        proxy_name = repo_name + "_toolchain"
        risc0_toolchain_proxy(
            name = proxy_name,
            host_arch = toolchain.host_arch,
            host_os = toolchain.host_os,
            toolchain = "@{repo_name}//:cc-toolchain".format(repo_name = repo_name),
        )

        toolchain_names.append("@{name}//:toolchain".format(name = proxy_name))
    native.register_toolchains(*toolchain_names)
