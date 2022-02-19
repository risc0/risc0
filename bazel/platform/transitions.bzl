# buildifier: disable=module-docstring
def _impl(settings, attr):
    return {"//command_line_option:platforms": str(Label("//bazel/platform:risc0"))}

risc0_transition = transition(
    implementation = _impl,
    inputs = [],
    outputs = ["//command_line_option:platforms"],
)
