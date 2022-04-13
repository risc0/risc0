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
        # "fence_i",
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
}

def riscv_test_suite():
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
                    "@riscv_tests//:isa/macros/scalar/test_macros.h",
                ],
                copts = [
                    "-Iexternal/riscv_tests",
                    "-Iexternal/riscv_tests/isa/macros/scalar",
                    "-Irisc0/zkvm/circuit/test",
                ],
            )

            native.py_test(
                name = test + "_test",
                srcs = ["run_test.py"],
                main = "run_test.py",
                args = [test],
                data = [
                    test,
                    ":risc0-simulate",
                ],
            )
