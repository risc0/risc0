# buildifier: disable=module-docstring
def _risc0_impl(settings, attr):
    return {
        "//command_line_option:platforms": str(Label("//bazel/platform:risc0")),
        "@rules_rust//:extra_rustc_flags": settings["//bazel/rules/rust:extra_guest_rustc_flags"],
    }

risc0_transition = transition(
    implementation = _risc0_impl,
    inputs = ["//bazel/rules/rust:extra_guest_rustc_flags"],
    outputs = ["//command_line_option:platforms", "@rules_rust//:extra_rustc_flags"],
)
