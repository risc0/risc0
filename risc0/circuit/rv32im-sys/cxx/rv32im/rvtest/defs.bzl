load("//bazel/toolchain/risc0:defs.bzl", "risc0_cc_binary")
load("@bazel_tools//tools/build_defs/pkg:pkg.bzl", "pkg_tar")

INST_TESTS = {
    ("rv32ui", "rv64ui"): [
        ("add", 16),
        ("addi", 16),
        ("and", 16),
        ("andi", 16),
        ("auipc", 16),
        ("beq", 16),
        ("bge", 16),
        ("bgeu", 16),
        ("blt", 16),
        ("bltu", 16),
        ("bne", 16),
        #("fence_i", 16),
        ("jal", 16),
        ("jalr", 16),
        ("lb", 32),
        ("lbu", 32),
        ("lh", 32),
        ("lhu", 32),
        ("lui", 16),
        ("lw", 32),
        ("or", 16),
        ("ori", 16),
        ("sb", 32),
        ("sh", 32),
        ("simple", 16),
        ("sll", 16),
        ("slli", 16),
        ("slt", 16),
        ("slti", 16),
        ("sltiu", 16),
        ("sltu", 16),
        ("sra", 16),
        ("srai", 16),
        ("srl", 16),
        ("srli", 16),
        ("sub", 16),
        ("sw", 32),
        ("xor", 16),
        ("xori", 16),
    ],
    ("rv32um", "rv64um"): [
        ("div", 16),
        ("divu", 16),
        ("mul", 16),
        ("mulh", 16),
        ("mulhsu", 16),
        ("mulhu", 16),
        ("rem", 16),
        ("remu", 16),
    ],
    ("rv32uc", "rv64uc"): [
        ("rvc", 16),
    ],
    ("rv32ua", "rv64ua"): [
        ("amoadd_w", 16),
        ("amoand_w", 16),
        ("amomax_w", 16),
        ("amomaxu_w", 16),
        ("amomin_w", 16),
        ("amominu_w", 16),
        ("amoor_w", 16),
        ("amoswap_w", 16),
        ("amoxor_w", 16),
        ("lrsc", 16),
    ],
}

def compile_riscv_tests():
    all_bins = []
    for (first, second), tests in INST_TESTS.items():
        for (test, cycles) in tests:
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
                    "-Iexternal/riscv_tests",
                    "-Iexternal/riscv_tests/isa/macros/scalar",
                    "-Irv32im/rvtest",
                    "-Iexternal/rv32im/rvtest"
                ],
            )
            all_bins = all_bins + [test]
    native.filegroup(
        name = "riscv_test_bins", 
        srcs = all_bins,
        visibility = ["//visibility:public"],
    )
