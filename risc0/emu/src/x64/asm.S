.text

.equ REG_R8, 0
.equ REG_R9, 1
.equ REG_R10, 2
.equ REG_R11, 3
.equ REG_R12, 4
.equ REG_R13, 5
.equ REG_R14, 6
.equ REG_R15, 7
.equ REG_RDI, 8
.equ REG_RSI, 9
.equ REG_RBP, 10
.equ REG_RBX, 11
.equ REG_RDX, 12
.equ REG_RAX, 13
.equ REG_RCX, 14
.equ REG_RSP, 15
.equ REG_RIP, 16

.extern jit_fault_slow

.global jit_fault_handler
.type jit_fault_handler,@function
jit_fault_handler:
  # At entry: registers and RSP are exactly as at the faulting JIT instruction.
  # We want to:
  #   - call jit_fault_slow() with a stack that satisfies the SysV ABI
  #   - then restore full register state from vm_state.gregs and resume JIT

  # Align the stack for the call to jit_fault_slow.
  #
  # SysV wants 16-byte alignment *inside* the callee. Just before CALL,
  # RSP % 16 should be 8 (because CALL will push an 8-byte return address,
  # making RSP % 16 == 0 in the callee).
  #
  # This ensures (rsp % 16) == 8 before the call.
  sub $8, %rsp

  call jit_fault_slow

  # need to restore:
  # rax, rdi, rsi, r8, r9, r10, r11, r12, r13, r14, r15
  mov  REG_R8*8(%rax), %r8
  mov  REG_R9*8(%rax), %r9
  mov REG_R10*8(%rax), %r10
  mov REG_R11*8(%rax), %r11
  mov REG_R12*8(%rax), %r12
  mov REG_R13*8(%rax), %r13
  mov REG_R14*8(%rax), %r14
  mov REG_R15*8(%rax), %r15
  mov REG_RDI*8(%rax), %rdi
  mov REG_RSI*8(%rax), %rsi

  # Restore the stack pointer
  mov REG_RSP*8(%rax), %rsp

  # Load RIP into RDX so we can jump into it
  mov REG_RIP*8(%rax), %rdx

  # Restore RAX last since it's used as the base pointer
  mov REG_RAX*8(%rax), %rax

  # It's safe to trash RDX because this should only happen in the context of a
  # load/store and RDX is unused.
  jmp %rdx
