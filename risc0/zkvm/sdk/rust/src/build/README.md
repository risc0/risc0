# risc0-build

This crate contains helper functions to assist with building guest side code,
and using it in host side code.

`risc0_zkvm::build::rcc::Build` is a wrapper for the `cc` crate that compiles to `riscv32im` 
if the `CARGO_CFG_TARGET_ARCH` is set to `riscv32` with no boilerplate and reasonable defaults.

If you want to change the defaults you can check out the methods for the given object, or set 
via the environment flags below. Environment flags supersede the methods.

- `RV_CC_INSTALL_PATH` sets the riscv32im cross-compiler gnu toolchain path. This can otherwise be set with the `Build::rv_cc_install_path` method. The default is `/opt/riscv`.
- `RCC_COMPILER` sets the compiler that will be used for the build. This can otherwise be set with the `Build::compiler` method.
- `CRATE_COMPILER_DEFAULTS` sets the compiler default flags. These default flags are turned off by default as compiler defaults usually don't account compiling for `riscv32im` architecture. This can otherwise be set with the `Build::compiler_default_flags` method.
- `CRATE_NO_RISC0_DEFAULTS` allows you to turn off all the reasonable default flags set for `riscv32im`. This can otherwise be set with the `Build::no_risc0_default_flags` method.