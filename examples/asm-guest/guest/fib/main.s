/*
  Copyright 2024 Risc0, Inc.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

.section .text.main
.global main
main:
  # Init operations
  .option push;
  .option norelax
  la gp, __global_pointer$
  .option pop
  la sp, _stack_top

  add  sp, sp, -8    # Allocate 8 bytes on the stack (increase if saving ra and s0/fp)

  # NOTE: don't actually care to save these, as this function will not return
  # sw	 ra,28(sp)    # Save the return address (ra) at offset 28 from the stack pointer (sp)
  # sw	 s0,24(sp)    # Save the frame pointer (s0) at offset 24 from the stack pointer (sp)

  add  s0, sp, 8     # Set the frame pointer (s0) to the current stack pointer (sp) plus 4
  call init_sha256
  sw   a0, 0(s0)     # Save the sha256_state ptr (returned in a0) to the frame pointer (s0)

  # env_read expects a0 buffer_ptr, a1 buffer_len
  addi a0, s0, -4    # Store the pointer to the fp-4 for where input will be read to on the stack
  li   a1, 4         # Reading four bytes
  call env_read
  li t0, 4                      # Load immediate value 4 into temporary register t0
  bne a0, t0, assertion_failed  # Assert that exactly 4 bytes read.

  # Call fib with the read 32 bit integer
  lw   a0, -4(s0) # Load input value into a0 register.
  call fibonacci
  sw   a0, -4(s0) # Overwrite input buffer with calculated fib value.

  # env_commit expects a0 sha256, a1 bytes_ptr, a2 bytes_len
  lw	 a0, 0(s0) # Load the saved sha256_state ptr into register a0 from the frame pointer (s0)
  addi a1, s0, -4 # Store pointer to output value in a1
  addi a2, s0, -4 # Committing 4 bytes to journal.
  call env_commit

  # env exit expects the sha256 pointer as a0 and the exit code in a1
  lw	 a0, 0(s0) # Load the saved sha256_state ptr into register a0 from the frame pointer (s0)
  li 	 a1, 0     # Load immediate value 0 into register a1
  call env_exit
  # Not cleaning up stack and frame pointers, as env_exit will exit or issue an illegal instruction

assertion_failed:
  unimp # This could be an exit with some message, keeping minimal by just executing illegal instr

fibonacci:
    # Prologue
    addi sp, sp, -16     # Allocate 16 bytes on stack
    sw ra, 12(sp)        # Save return address
    sw s0, 8(sp)         # Save s0
    sw s1, 4(sp)         # Save s1

    # Check if n <= 1
    li t0, 1
    ble a0, t0, base_case

    # Initialize variables
    li s0, 0             # fib(n-2)
    li s1, 1             # fib(n-1)
    li t0, 1             # Counter i

loop:
    # Check if we've calculated enough terms
    beq t0, a0, done

    # Calculate next Fibonacci number
    add t1, s0, s1       # t1 = fib(n-2) + fib(n-1)
    mv s0, s1            # fib(n-2) = fib(n-1)
    mv s1, t1            # fib(n-1) = new fib(n)

    # Increment counter
    addi t0, t0, 1
    j loop

base_case:
    # If n <= 1, return n
    mv a0, a0
    j exit

done:
    # Return the calculated Fibonacci number
    mv a0, s1

exit:
    # Epilogue
    lw s1, 4(sp)         # Restore s1
    lw s0, 8(sp)         # Restore s0
    lw ra, 12(sp)        # Restore return address
    addi sp, sp, 16      # Deallocate stack space
    ret
