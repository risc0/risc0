# fence instruction test for risc0
.section .text
.global rvtest_entry_point

rvtest_entry_point:
    # Test 1: Basic fence
    li x31, 1        # test number
    li a0, 0x123
    li a1, 0x456
    fence            # basic fence - should not affect registers
    bne a0, a0, fail # a0 should still equal itself
    li t0, 0x123
    bne a0, t0, fail # a0 should still be 0x123
    
    # Test 2: fence iorw, iorw (full fence)
    li x31, 2
    li a2, 0x789
    fence iorw, iorw
    li t0, 0x789
    bne a2, t0, fail
    
    # Test 3: fence i, o
    li x31, 3
    li a3, 0xabc
    fence i, o
    li t0, 0xabc
    bne a3, t0, fail
    
    # Test 4: fence o, i  
    li x31, 4
    li a4, 0xdef
    fence o, i
    li t0, 0xdef
    bne a4, t0, fail
    
    # Test 5: fence w, r
    li x31, 5
    li a5, 0x111
    fence w, r
    li t0, 0x111
    bne a5, t0, fail
    
    # Test 6: fence r, w
    li x31, 6
    li a6, 0x222
    fence r, w
    li t0, 0x222
    bne a6, t0, fail
    
    # Test 7: another basic fence to ensure no corruption
    li x31, 7
    li a7, 0x333
    fence
    li t0, 0x333
    bne a7, t0, fail
    
    # All tests passed
    j pass

fail:
    fence           # use fence as trap in fail case (like other tests)
    unimp

pass:
    li t0, 0
    li a0, 0
    li a1, 1024
    li a7, 0  # Clear a7 for proper ecall
    ecall