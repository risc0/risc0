TOOLCHAINS = [
    struct(
        archive = "riscv32im-osx-arm64",
        host_arch = "@platforms//cpu:arm64",
        host_os = "@platforms//os:osx",
        sha256 = "d4f985fba0d7de315750168453cffaa4db9bea344e7e2bc3163b07e6d113ccd6",
        version = "2024.01.05",
    ),
    struct(
        archive = "riscv32im-linux-x86_64",
        host_arch = "@platforms//cpu:x86_64",
        host_os = "@platforms//os:linux",
        sha256 = "cc19497db5fd1ccd92fa3d315a33cacd4ba480f8d21b3c84dfb5493cfd68da0d",
        version = "2024.01.05",
    ),
]

def _repo_impl(rctx):
    rctx.template(
        "BUILD.bazel",
        Label("//bazel/toolchain/rv32im-linux:repo.tpl.BUILD"),
        {
            "{workspace}": rctx.name,
        },
    )

    rctx.file(
        "gcc_toolchain.bzl",
        content = rctx.read(Label("//bazel/toolchain/rv32im-linux:gcc_toolchain.bzl")),
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
        Label("//bazel/toolchain/rv32im-linux:proxy.tpl.BUILD"),
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

def rv32im_linux_toolchain(name):
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
