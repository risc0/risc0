.text
.intel_syntax noprefix

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
  sub rsp, 8

  call jit_fault_slow

  # need to restore:
  # rax, rdi, rsi, r8, r9, r10, r11, r12, r13, r14, r15
  mov r8, QWORD PTR [rax + REG_R8 * 8]
  mov r9, QWORD PTR [rax + REG_R9 * 8]
  mov r10, [rax + REG_R10 * 8]
  mov r11, [rax + REG_R11 * 8]
  mov r12, [rax + REG_R12 * 8]
  mov r13, [rax + REG_R13 * 8]
  mov r14, [rax + REG_R14 * 8]
  mov r15, [rax + REG_R15 * 8]
  mov rdi, [rax + REG_RDI * 8]
  mov rsi, [rax + REG_RSI * 8]

  # Restore the stack pointer
  mov rsp, [rax + REG_RSP * 8]

  # Load RIP into RDX so we can jump into it
  mov rdx, [rax + REG_RIP * 8]

  # Restore RAX last since it's used as the base pointer
  mov rax, [rax + REG_RAX * 8]

  # It's safe to trash RDX because this should only happen in the context of a
  # load/store and RDX is unused.
  jmp rdx
