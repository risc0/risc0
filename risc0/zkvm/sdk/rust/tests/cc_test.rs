use crate::support::{Execution, Test};
use serial_test::serial;

mod support;

#[test]
#[serial]
fn risc0_default_flags() {
    reset_env();

    let test = Test::gnu();
    test.gcc()
        .file("foo.c")
        .compile("foo");

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

    e.must_have("foo.c");
    check_risc0_default_flags_do_not_exist(&e);
    check_release_flags_do_not_exist(&e);
    test.cmd(1).must_have(test.td.path().join("foo.o"));
}

#[test]
#[serial]
fn no_risc0_default_flags_via_flag() {
    reset_env();
    std::env::set_var("CRATE_NO_RISC0_DEFAULTS", "TRUE");


    let test = Test::gnu();
    test.gcc()
        .file("foo.c")
        .compile("foo");

    let e = test.cmd(0);

    e.must_have("foo.c");
    check_risc0_default_flags_do_not_exist(&e);
    check_release_flags_do_not_exist(&e);
    test.cmd(1).must_have(test.td.path().join("foo.o"));
}

#[test]
#[serial]
fn release_version() {
    reset_env();

    let test = Test::gnu();
    test.gcc()
        .file("foo.c")
        .release_version(true)
        .compile("foo");

    let e = test.cmd(0);

    e.must_have("foo.c");
    check_risc0_default_flags_exist(&e);
    check_release_flags_exist(&e);
    test.cmd(1).must_have(test.td.path().join("foo.o"));
}

fn sysroot_flag() -> String {
    format!("--sysroot={}/riscv32-unknown-elf", support::RISCV_INSTALL_DIR)
}

fn gcc_toolchain_flag() -> String {
    format!("--gcc-toolchain={}", support::RISCV_INSTALL_DIR)
}

// Some tests check that a flag is *not* present.  These tests might fail if the flag is set in the
// CFLAGS or CXXFLAGS environment variables.  This function clears the CFLAGS and CXXFLAGS
// variables to make sure that the tests can run correctly.
fn reset_env() {
    std::env::set_var("CFLAGS", "");
    std::env::set_var("CXXFLAGS", "");
    std::env::set_var("CRATE_NO_RISC0_DEFAULTS", "");
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
        .must_have(sysroot_flag())
        .must_have(gcc_toolchain_flag())
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
        .must_not_have(sysroot_flag())
        .must_not_have(gcc_toolchain_flag())
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
