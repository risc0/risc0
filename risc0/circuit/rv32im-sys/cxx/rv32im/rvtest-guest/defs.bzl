load("//bazel/toolchain/risc0:defs.bzl", "risc0_cc_binary")
load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

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
    ("rv32uf", "rv64uf"): [
        "fadd",
        "fclass",
        "fcmp",
        "fcvt",
        "fcvt_w",
        "fdiv",
        "fmadd",
        "fmin",
        "ldst",
        "move",
        "recoding",
    ],
    ("rv32ud", "rv64ud"): [
        "fadd",
        "fclass",
        "fcmp",
        "fcvt",
        "fcvt_w",
        "fdiv",
        "fmadd",
        "fmin",
        "ldst",
        "recoding",
    ],
}

def compile_riscv_tests():
    all_bins = []
    for (first, second), tests in INST_TESTS.items():
        for test  in tests:
            src = Label("@riscv_tests//:isa/{}/{}.S".format(first, test))
            aux = Label("@riscv_tests//:isa/{}/{}.S".format(second, test))
            
            # Add prefix for floating-point tests to avoid name conflicts
            # rv32uf and rv32ud both have tests with the same names (fadd, fdiv, etc.)
            if first in ["rv32uf", "rv32ud"]:
                target_name = "{}_{}".format(first, test)
            else:
                target_name = test
            
            risc0_cc_binary(
                name = target_name,
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
                    "-Irv32im/rvtest-guest",
                    "-Iexternal/rv32im/rvtest-guest"
                ],
            )
            all_bins = all_bins + [target_name]
    native.filegroup(
        name = "riscv_test_guest_bins", 
        srcs = all_bins,
        visibility = ["//visibility:public"],
    )

