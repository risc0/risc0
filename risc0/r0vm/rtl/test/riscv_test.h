#define __riscv_xlen 32
#define TESTNUM x31

#define RVTEST_RV32U                                                                               \
  .macro init;                                                                                     \
  .endm

#define RVTEST_FAIL                                                                                \
  fence;                                                                                           \
  unimp
#define RVTEST_PASS ecall

#define RVTEST_CODE_BEGIN                                                                          \
  .text;                                                                                           \
  .globl _start;                                                                                   \
  _start:                                                                                          \
  .option push;                                                                                    \
  .option norelax;                                                                                 \
  la gp, __global_pointer$;                                                                        \
  .option pop;

#define RVTEST_CODE_END

#define RVTEST_DATA_BEGIN .data
#define RVTEST_DATA_END
