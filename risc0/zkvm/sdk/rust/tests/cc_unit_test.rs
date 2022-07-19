#![cfg(feature = "risc_cc")]

use crate::support::{Execution, Test};
use risc0_zkvm::build::rcc;
use serial_test::serial;

mod support;

#[test]
#[serial]
fn risc0_default_flags() {
    reset_env();

    let test = Test::gnu();
    test.gcc().file("foo.c").compile("foo");

    let e = test.cmd(0);

    e.must_have("foo.c");
    check_risc0_default_flags_exist(&e);
    check_release_flags_do_not_exist(&e);

    test.cmd(1).must_have(test.td.path().join("foo.o"));
}

#[test]
#[serial]
fn no_risc0_default_flags_via_function() {
    reset_env();

    let test = Test::gnu();
    test.gcc()
        .file("foo.c")
        .no_risc0_default_flags(true)
        .compile("foo");

    let e = test.cmd(0);

    check_risc0_default_flags_do_not_exist(&e);
    check_release_flags_do_not_exist(&e);
}

#[test]
#[serial]
fn no_risc0_default_flags_via_flag() {
    reset_env();
    std::env::set_var("CRATE_NO_RISC0_DEFAULTS", "TRUE");

    let test = Test::gnu();
    test.gcc().file("foo.c").compile("foo");

    let e = test.cmd(0);

    check_risc0_default_flags_do_not_exist(&e);
    check_release_flags_do_not_exist(&e);
}

#[test]
#[serial]
fn release() {
    reset_env();

    let test = Test::gnu();
    test.gcc().file("foo.c").release(true).compile("foo");

    let e = test.cmd(0);

    check_risc0_default_flags_exist(&e);
    check_release_flags_exist(&e);
}

#[test]
#[serial]
fn rv_cc_install_path_via_method() {
    reset_env();

    let some_install_path = "/stra/wqath";

    let test = Test::gnu();
    test.gcc()
        .file("foo.c")
        .rv_cc_install_path(some_install_path)
        .compile("foo");

    let e = test.cmd(0);

    e.must_have(sysroot_flag(some_install_path));
    e.must_have(gcc_toolchain_flag(some_install_path));
}

#[test]
#[serial]
fn rv_cc_install_path_via_flag() {
    reset_env();

    let install_path_via_flag = "/stra/wqath";
    std::env::set_var("RV_CC_INSTALL_PATH", install_path_via_flag);

    let install_path_via_method = "/abc";
    let test = Test::gnu();
    test.gcc()
        .file("foo.c")
        .rv_cc_install_path(install_path_via_method)
        .compile("foo");

    let e = test.cmd(0);

    e.must_have(sysroot_flag(install_path_via_flag));
    e.must_have(gcc_toolchain_flag(install_path_via_flag));

    e.must_not_have(sysroot_flag(install_path_via_method));
    e.must_not_have(gcc_toolchain_flag(install_path_via_method));
}

#[test]
#[serial]
fn compiler() {
    reset_env();

    let test = Test::gnu();

    let compiler_name: &str = "bruv";
    let compiler_path = test.td.path().join(compiler_name);
    std::env::set_var("RCC_COMPILER", compiler_path);

    let error_message = match test.gcc().file("foo.c").try_compile("foo") {
        Ok(_) => panic!(
            "{}",
            format!(
                "Should have panicd as compiler named {} does not exist",
                compiler_name
            )
        ),
        Err(e) => format!("{:?}", e),
    };

    assert!(error_message.contains(compiler_name));
    assert!(error_message.contains("ToolNotFound"));
}

#[test]
#[serial]
fn architecture_detected_via_cargo_flag() {
    reset_env();

    std::env::set_var("CARGO_CFG_TARGET_ARCH", "");

    let test = Test::gnu();
    test.gcc().file("foo.c").compile("foo");

    let e = test.cmd(0);

    check_risc0_default_flags_do_not_exist(&e);
}

fn sysroot_flag(install_path: &str) -> String {
    format!("--sysroot={}/riscv32-unknown-elf", install_path)
}

fn gcc_toolchain_flag(install_path: &str) -> String {
    format!("--gcc-toolchain={}", install_path)
}

fn reset_env() {
    // Some tests check that a flag is *not* present.  These tests might fail if the flag is set in the
    // CFLAGS or CXXFLAGS environment variables.  This function clears the CFLAGS and CXXFLAGS
    // variables to make sure that the tests can run correctly.
    std::env::set_var("CFLAGS", "");
    std::env::set_var("CXXFLAGS", "");

    std::env::set_var("CRATE_NO_RISC0_DEFAULTS", "");
    std::env::set_var("CARGO_CFG_TARGET_ARCH", "riscv32");
    std::env::set_var("RV_CC_INSTALL_PATH", "");
    std::env::set_var("RCC_COMPILER", "");
}

fn check_risc0_default_flags_exist(e: &Execution) -> &Execution {
    e.must_have("-O3")
        .must_have("--target=riscv32-unknown-none-elf")
        .must_have("-mabi=ilp32")
        .must_have("-mcmodel=medany")
        .must_have("-fdata-sections")
        .must_have("-ffunction-sections")
        .must_have("-dead_strip")
        .must_have("-flto")
        .must_have("-march=rv32im")
        .must_have("-static")
        .must_have(sysroot_flag(rcc::DEFAULT_RV_CC_INSTALL_PATH))
        .must_have(gcc_toolchain_flag(rcc::DEFAULT_RV_CC_INSTALL_PATH))
}

fn check_risc0_default_flags_do_not_exist(e: &Execution) -> &Execution {
    e.must_not_have("-O3")
        .must_not_have("--target=riscv32-unknown-none-elf")
        .must_not_have("-mabi=ilp32")
        .must_not_have("-mcmodel=medany")
        .must_not_have("-fdata-sections")
        .must_not_have("-ffunction-sections")
        .must_not_have("-dead_strip")
        .must_not_have("-flto")
        .must_not_have("-march=rv32im")
        .must_not_have("-static")
        .must_not_have(sysroot_flag(rcc::DEFAULT_RV_CC_INSTALL_PATH))
        .must_not_have(gcc_toolchain_flag(rcc::DEFAULT_RV_CC_INSTALL_PATH))
}

fn check_release_flags_exist(e: &Execution) -> &Execution {
    e.must_have("-feliminate-unused-debug-symbols")
        .must_have("-feliminate-unused-debug-types")
        .must_have("-fvirtual-function-elimination")
}

fn check_release_flags_do_not_exist(e: &Execution) -> &Execution {
    e.must_not_have("-feliminate-unused-debug-symbols")
        .must_not_have("-feliminate-unused-debug-types")
        .must_not_have("-fvirtual-function-elimination")
}
