# fence instruction test for risc0
.section .text
.global rvtest_entry_point

rvtest_entry_point:
    li x31, 1        # test number
    li a0, 0x123
    li a1, 0x456
    fence            # check that a basic fence can be executed
    bne a0, a0, fail # a0 should still equal itself
    li t0, 0x123
    fence iorw, iorw # check that another fence can executed
    bne a0, t0, fail # a0 should still be 0x123

   # All tests passed
    j pass

fail:
    fence           # use fence as trap in fail case (like other tests)
    unimp

pass:
    li t0, 0
    li a0, 0
    li a1, 1024
    ecall
