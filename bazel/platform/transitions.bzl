# buildifier: disable=module-docstring
def _risc0_impl(settings, attr):
    return {"//command_line_option:platforms": str(Label("//bazel/platform:risc0"))}

risc0_transition = transition(
    implementation = _risc0_impl,
    inputs = [],
    outputs = ["//command_line_option:platforms"],
)

def _wasm_impl(settings, attr):
    return {"//command_line_option:platforms": str(Label("@rules_rust//rust/platform:wasm"))}

wasm_transition = transition(
    implementation = _wasm_impl,
    inputs = [],
    outputs = ["//command_line_option:platforms"],
)
