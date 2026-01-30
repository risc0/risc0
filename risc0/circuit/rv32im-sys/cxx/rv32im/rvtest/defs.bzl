load("@rules_pkg//pkg:pkg.bzl", "pkg_zip")
load("//bazel/toolchain/risc0:defs.bzl", "risc0_cc_binary")

INST_TESTS = {
    ("rv32ui", "rv64ui"): [
        "add",
        "addi",
        "and",
        "andi",
        "auipc",
        "beq",
        "bge",
        "bgeu",
        "blt",
        "bltu",
        "bne",
        "fence_i",
        "jal",
        "jalr",
        "lb",
        "lbu",
        "lh",
        "lhu",
        "lui",
        "lw",
        "or",
        "ori",
        "sb",
        "sh",
        "simple",
        "sll",
        "slli",
        "slt",
        "slti",
        "sltiu",
        "sltu",
        "sra",
        "srai",
        "srl",
        "srli",
        "sub",
        "sw",
        "xor",
        "xori",
    ],
    ("rv32um", "rv64um"): [
        "div",
        "divu",
        "mul",
        "mulh",
        "mulhsu",
        "mulhu",
        "rem",
        "remu",
    ],
    ("rv32uc", "rv64uc"): [
        "rvc",
    ],
    ("rv32ua", "rv64ua"): [
        "amoadd_w",
        "amoand_w",
        "amomax_w",
        "amomaxu_w",
        "amomin_w",
        "amominu_w",
        "amoor_w",
        "amoswap_w",
        "amoxor_w",
        "lrsc",
    ],
}

def compile_riscv_tests():
    all_bins = []
    for (first, second), tests in INST_TESTS.items():
        for test in tests:
            src = Label("@riscv_tests//:isa/{}/{}.S".format(first, test))
            aux = Label("@riscv_tests//:isa/{}/{}.S".format(second, test))
            risc0_cc_binary(
                name = test,
                srcs = [src],
                hdrs = ["riscv_test.h"],
                aux_srcs = [
                    aux,
                    Label("@riscv_tests//:isa/macros/scalar/test_macros.h"),
                ],
                copts = [
                    "-march=rv32g",
                    "-Wa,-march=rv32g",  # Explicitly pass -march to assembler for .S files
                    "-Iexternal/riscv_tests",
                    "-Iexternal/riscv_tests/isa/macros/scalar",
                    "-Irv32im/rvtest",
                    "-Iexternal/rv32im/rvtest",
                ],
            )
            all_bins = all_bins + [test]
    native.filegroup(
        name = "riscv_test_bins",
        srcs = all_bins,
        visibility = ["//visibility:public"],
    )
    pkg_zip(name = "riscv-tests", srcs = all_bins)
