# buildifier: disable=module-docstring

def _risc0_impl(_settings, _attr):
    return {
        "//command_line_option:platforms": str(Label("//bazel/platform:risc0")),
    }

risc0_transition = transition(
    implementation = _risc0_impl,
    inputs = [],
    outputs = ["//command_line_option:platforms"],
)

def _rv32im_linux_impl(_settings, _attr):
    return {
        "//command_line_option:platforms": str(Label("//bazel/platform:rv32im-linux")),
    }

rv32im_linux_transition = transition(
    implementation = _rv32im_linux_impl,
    inputs = [],
    outputs = ["//command_line_option:platforms"],
)
