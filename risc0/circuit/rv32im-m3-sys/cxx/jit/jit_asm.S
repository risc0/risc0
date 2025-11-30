.section .note.GNU-stack,"",@progbits
.text

# Declare which registers we asign to which logical values 

# EAX - EDX as # basically scratch, but typically we use EAX as RS1 and RD, and
# ECX as RS2

CTX = %rdi  # Context pointer back to c++ code
LOG = %rsi  # Head of instruction log
REGS = %rbp  # Pointer to registers
RDN = %r8  # Which register is RD (i.e. RD number)
RS1N = %r9  # Which register is RS1
RS2N = %r10  # Which register is RS2
IMM = %r11d  # What was the 32 bit version of the immediate in the instruction
PC = %r12d  # What PC was this instruction original on
OINST = %edx  # Reuse eax as instruction
CYCLE = %r13  # The current cycle is in the high 32 bits of this number
CYCLE_INC_VAL = %r14  # The value 2^32 used to 'increment' the cycle
PAGES = %r15

# Information about where various variables live in the C+++ code

# Offsets for the JitContext structure, when given a pointer to start of registers
CTX_REGS_OFF = 0
CTX_PAGES_OFF = 8
CTX_LOG_OFF = 16
CTX_QUOTA_OFF = 24
CTX_CYCLE_OFF = 32
CTX_STOP_CYCLE_OFF = 40
CTX_EXIT_CAUSE_OFF = 48
CTX_PAGE_MISS_OFF = 56
CTX_LOAD_KEY_OFF = 72
CTX_STORE_KEY_OFF = 80

# Offsets in the log
LOG_PC_OFF = 8
LOG_OINST_OFF = 12
LOG_RD_OFF = 24 
LOG_RS1_OFF = 32
LOG_RS2_OFF = 40 

LOG_SIZE = 48

EXIT_CAUSE_QUOTA_OUT = 0
EXIT_CAUSE_CYCLES_OUT = 1
EXIT_CAUSE_ECALL = 2
EXIT_CAUSE_ALIGNMENT = 3
EXIT_CAUSE_MRET = 4
EXIT_CAUSE_JALR = 5
EXIT_CAUSE_ANY = 6
EXIT_CAUSE_FETCH = 7

# A friendly macro to lookup map entries
.macro MAP_LOOKUP_64 PO2
  # Input:
  #   %rbx = key (uint64, non-zero)
  #   PAGES = table base (array of { u64 key; u64 value; }, 16B each)
  # Output:
  #   %rdx = value, or 0 if key not found
  # Clobbers:
  #  %r9, %r10, flags

  .set MAP_SHIFT\@, 64 - \PO2 
  .set MAP_MASK\@, ((1 << \PO2) - 1)

  # r10 = key * HASH_CONST 
  movabs  $0x9e3779b97f4a7c15, %r9
  mov %rbx, %r10
  imul %r9, %r10
  # index = high bits of hash
  shr $MAP_SHIFT\@, %r10

.L_map_lookup_loop\@:
  # load key at slot: slot_key = table[index].key
  lea (PAGES, %r10, 8), %r9
  mov (%r9, %r10, 8), %rdx

  # first check for match (hot path)
  cmp %rbx, %rdx
  je .L_map_found\@

  # is slot_key == 0? => not found
  test %rdx, %rdx
  je .L_map_not_found\@

  # linear probe: index = (index + 1) & ((1<<PO2)-1)
  inc %r10
  and $MAP_MASK\@, %r10
  jmp .L_map_lookup_loop\@

.L_map_found\@:
  # load value: table[index].value
  mov 8(%r9, %r10, 8), %rdx
  jmp .L_map_done\@

.L_map_not_found\@:
  xor %rdx, %rdx # return 0 

.L_map_done\@:
.endm

# Next we have common 'parts' of instructions (getting RS1 + RS2, logging
# RD's original state, etc).  When then use these to build instruction
# categories (3-reg, imm, etc), and finally instructions

.macro WRITE_INST, INST  # Write instruction info to the loga
  cmpq CTX_STOP_CYCLE_OFF(CTX), CYCLE
  jae .Lcycles_empty
#if PREFLIGHT 
  movb \INST, (LOG)  # Write opcode
  movb %r8b, 1(LOG)  # Write RD
  movb %r9b, 2(LOG)  # Write RS1
  movb %r10b, 3(LOG)  # Write RS2
  movl IMM, 4(LOG)  # Write IMM
  movl PC, LOG_PC_OFF(LOG) # Write PC
  movl OINST, LOG_OINST_OFF(LOG) # Write original inst
#endif
.endm

.macro INC_CYCLE  # Incement cycle #
#if PREFLIGHT
  addq CYCLE_INC_VAL, CYCLE  # Inc cycle
#endif
.endm

.macro LOG_OLD_RD  # Log orignal RD value (for things that write to RD)
#if PREFLIGHT
  movq (REGS, RDN, 8), %rax  # Load RD
  movq %rax, LOG_RD_OFF(LOG)  # Save to log
#endif
.endm

.macro LOAD_RS1_EAX  # Log original RS1 value, and load RS1 into EAX
  movq (REGS, RS1N, 8), %rax  # Load RS1 into %rax
#if PREFLIGHT
  movq %rax, LOG_RS1_OFF(LOG)  # Save to log
  movl %eax, %eax  # Clear high 32 bits
  orq CYCLE, %rax  # Add cycle
  movq %rax, (REGS, RS1N, 8)  # Write back
#endif
.endm

.macro LOAD_RS2_ECX  # Log original RS2 value, and load RS2 into ECX
  movq (REGS, RS2N, 8), %rcx  # Load RS2 into %rcx
#if PREFLIGHT
  movq %rcx, LOG_RS2_OFF(LOG)  # Save to log
  movl %ecx, %ecx  # Clear high 32 bits
  orq CYCLE, %rcx  # Add cycle
  movq %rcx, (REGS, RS2N, 8)  # Write back
  test $0x40, RS2N  # Check if RS2 is a 'trash address'
  cmovnz %eax, %ecx  # If so, copy over eax
#endif
.endm

.macro WRITE_EAX_RD
#if PREFLIGHT
  orq CYCLE, %rax  # Add cycle
#endif
  movq %rax, (REGS, RDN, 8)  # Write to RD
.endm

.macro INST_END
#if PREFLIGHT
  INC_CYCLE  # Add final cycle
  add $LOG_SIZE, LOG  # Move log forward
#else
  addq CYCLE_INC_VAL, CYCLE  # Inc cycle
#endif
  ret  # Return from instruction
.endm

# Three register instructions
# We divide this into pre/post work, to allow special handling for
# multiply/div, shift, etc, which are all slightly irregular
# We basically presume RS1 + RS2 are in eax and ecx, and compute
# RD into eax
.macro DO_REG_PRE opcode
  WRITE_INST \opcode  # Write opcode data to log
  LOG_OLD_RD  # Log the current RD value before it is overwritten
  LOAD_RS1_EAX  # Load RS1 into EAX (and log)
  LOAD_RS2_ECX  # Load RS2 into ECX (and log)
.endm

.macro DO_REG_POST 
  INC_CYCLE  # Move to the 'write' cycle
  WRITE_EAX_RD  # Write EAX to RD
  INST_END  # Finish instruction
.endm

# Immediate instructions, also split for similar reasons (shifts, SLT)
.macro DO_IMM_PRE opcode
  WRITE_INST \opcode  # Write opcode data to log
  LOG_OLD_RD  # Log the current RD value before it is overwritten
  LOAD_RS1_EAX  # Load RS1 into EAX
.endm

.macro DO_IMM_POST
  INC_CYCLE  # Move to the 'write' cycle
  WRITE_EAX_RD  # Write EAX to RD
  INST_END  # Finish instruction
.endm

# Banch instructions are actually all exactly the same, actual
# branch happens at the C++ JIT level
.macro DO_BRANCH opcode
  WRITE_INST \opcode  # Write opcode data to log
  LOAD_RS1_EAX  # Load RS1 into EAX (and log)
  LOAD_RS2_ECX  # Load RS2 into ECX (and log)
  INC_CYCLE  # Skip to write cycle, but don't write anything
  INST_END
.endm

# Helper macros for memory ops

# Check aligment and fail if wrong
# Address in EAX
.macro CHECK_ALIGNMENT mask
  test \mask, %eax  # Check for alignment
  jnz .Lalignment_trap  # Fail not aligned
.endm

.Lresolve_page:
  # Get function pointer to jump to
  movq CTX_PAGE_MISS_OFF(CTX), %rdx
  # Save critival data back to context
#if PREFLIGHT
  movq LOG, CTX_LOG_OFF(CTX)
#endif
  movq CYCLE, CTX_CYCLE_OFF(CTX)
  push RDN  # Save RDN since I still need to write RD
  push %rax  # Save rax since it holds the full address
  push CTX  # Save CTX
  movq %rbx, %rsi  # Pass page up to c++
  call *%rdx
  movq %rax, %rdx  # Move return value to rdx
  pop CTX # Restore things
  pop %rax
  pop RDN
  # Reload things I need
  movq CTX_REGS_OFF(CTX), REGS
  movq CTX_LOG_OFF(CTX), LOG
  movq CTX_CYCLE_OFF(CTX), CYCLE
#if PREFLIGHT
  movq $0x100000000, CYCLE_INC_VAL
#else
  movq $0x200000000, CYCLE_INC_VAL
#endif
  movq CTX_PAGES_OFF(CTX), PAGES
  ret

# Given an address in %eax, puts the page ptr in %edx
# Makes sure to not mess with %ecx since we need it
# for SW (which reads RS2 there).  Trash rbx
.macro RESOLVE_PAGE label_prefix off
  mov %eax, %ebx  # Copy address to ebx
  shr $10, %ebx  # Shift, now we have the page #
  orl \off(CTX), %ebx # Make into key
  # Do map lookup
  MAP_LOOKUP_64 18
  cmp $0, %rdx  # Check if it's NULL
  jne .L\label_prefix\()_skip  # if not, we are good to go
  call .Lresolve_page  # Otherwise, resolve page via c++
  cmp $0, %edx  # Check if still null and trap
  je .Lpage_fault_trap
.L\label_prefix\()_skip:
.endm

# Given address in %eax, page in %rdx, compute offset into %ebx
# and load word data and cycle into %rax
.macro LOAD_WORD
  mov %eax, %ebx  # Copy address
  and $0x3fc, %ebx  # Clear high bits + aligne, EBX is now offset
  mov (%rdx, %rbx, 2), %rax  # Load the page data + cycle
.endm

.macro DO_LOAD_PRE opcode label_prefix align_mask
  DO_IMM_PRE \opcode  # LOG rd, load RS1
  add IMM, %eax  # EAX is now the address to load from
  CHECK_ALIGNMENT \align_mask  # Jump to error if misaligned
  RESOLVE_PAGE \label_prefix CTX_LOAD_KEY_OFF # Load page ptr into %rdx
  mov %eax, %ecx  # Save address to ecx
  LOAD_WORD  # Load word into %eax
#if PREFLIGHT
  mov %rax, LOG_RS2_OFF(LOG)  # Log memory transaction into RS2
  mov %eax, %eax  # Clear top bits
  orq CYCLE, %rax  # Update cycle #
  mov %rax, (%rdx, %rbx, 2)  # Write back to memory
#endif
.endm

.macro DO_STORE_PRE opcode label_prefix align_mask
  WRITE_INST \opcode  # Write opcode data to log
  LOAD_RS1_EAX  # Load RS1 into EAX (and log)
  LOAD_RS2_ECX  # Load RS2 into ECX (and log)
  mov %ecx, %r12d  # Squirel away in r12d (which is caller saved)
  add IMM, %eax  # EAX is now the address to load from
  CHECK_ALIGNMENT \align_mask  # Jump to error if misaligned
  RESOLVE_PAGE \label_prefix CTX_STORE_KEY_OFF # Load page ptr into %rdx
  mov %eax, %ecx  # Save address to ecx
  LOAD_WORD  # Load word into %eax
#if PREFLIGHT
  mov %rax, LOG_RD_OFF(LOG)  # Log memory transaction into RD
#endif
.endm

.macro DO_STORE_POST
#if PREFLIGHT
  INC_CYCLE  # Move to the 'write' cycle
  mov %eax, %eax  # Clear top bits
  orq CYCLE, %rax  # Update cycle #
#endif
  movq %rax, (%rdx, %rbx, 2)  # Write back to memory
  INST_END  # Finish instruction
.endm

# Actual instructions

do_ADD:
  DO_REG_PRE $0
  addl %ecx, %eax
  DO_REG_POST

do_SUB:
  DO_REG_PRE $1
  subl %ecx, %eax
  DO_REG_POST

do_XOR:
  DO_REG_PRE $2
  xorl %ecx, %eax
  DO_REG_POST

do_OR:
  DO_REG_PRE $3
  orl %ecx, %eax
  DO_REG_POST

do_AND:
  DO_REG_PRE $4
  andl %ecx, %eax
  DO_REG_POST

do_SLL:
  DO_REG_PRE $5
  shl %cl, %eax
  DO_REG_POST

do_SRL:
  DO_REG_PRE $6
  shr %cl, %eax
  DO_REG_POST

do_SRA:
  DO_REG_PRE $7
  sar %cl, %eax
  DO_REG_POST

do_SLT:
  DO_REG_PRE $8
  cmpl %ecx, %eax  # compare eax - ecx
  mov $0, %eax  # default = 0
  setl %al  # set AL = 1 if (eax < ecx) signed
  DO_REG_POST

do_SLTU:
  DO_REG_PRE $9
  cmpl %ecx, %eax  # compare eax - ecx
  mov $0, %eax  # default = 0
  setb %al  # set AL = 1 if (eax < ecx) unsigned
  DO_REG_POST

do_ADDI:
  DO_IMM_PRE $10
  addl IMM, %eax
  DO_IMM_POST

do_XORI:
  DO_IMM_PRE $11
  xorl IMM, %eax
  DO_IMM_POST

do_ORI:
  DO_IMM_PRE $12
  orl IMM, %eax
  DO_IMM_POST

do_ANDI:
  DO_IMM_PRE $13
  andl IMM, %eax
  DO_IMM_POST

do_SLLI:
  DO_IMM_PRE $14
  movl IMM, %ecx
  shl %cl, %eax
  DO_IMM_POST

do_SRLI:
  DO_IMM_PRE $15
  movl IMM, %ecx
  shr %cl, %eax
  DO_IMM_POST

do_SRAI:
  DO_IMM_PRE $16
  movl IMM, %ecx
  sar %cl, %eax
  DO_IMM_POST

do_SLTI:
  DO_IMM_PRE $17
  cmpl IMM, %eax  # compare eax - ecx
  mov $0, %eax  # default = 0
  setl %al  # set AL = 1 if (eax < ecx) signed
  DO_IMM_POST

do_SLTIU:
  DO_IMM_PRE $18
  cmpl IMM, %eax  # compare eax - ecx
  mov $0, %eax  # default = 0
  setb %al  # set AL = 1 if (eax < ecx) unsigned
  DO_IMM_POST

do_LB:
  DO_LOAD_PRE $19 do_LB $0  # Put addr in %eax, page in %rdx
  andl $3, %ecx  # Get lower bits from address
  shll $3, %ecx  # Multiply by 8
  shrl %cl, %eax  # Shift right byte into lower byte
  movsbl %al, %eax
  DO_IMM_POST

do_LH:
  DO_LOAD_PRE $20 do_LH $1  # Put addr in %eax, page in %rdx
  andl $3, %ecx  # Get lower bits from address
  shll $3, %ecx  # Multiply by 8
  shrl %cl, %eax  # Shift right byte into lower short
  movswl %ax, %eax
  DO_IMM_POST

do_LW:
  DO_LOAD_PRE $21 do_LW $3  # Put addr in %eax, page in %rdx
  DO_IMM_POST  # Data now in EAX, just write back

do_LBU:
  DO_LOAD_PRE $22 do_LBU $0  # Put addr in %eax, page in %rdx
  andl $3, %ecx  # Get lower bits from address
  shll $3, %ecx  # Multiply by 8
  shrl %cl, %eax  # Shift right byte into lower byte
  andl $0x000000ff, %eax
  DO_IMM_POST

do_LHU:
  DO_LOAD_PRE $23 do_LHU $1  # Put addr in %eax, page in %rdx
  andl $3, %ecx  # Get lower bits from address
  shll $3, %ecx  # Multiply by 8
  shrl %cl, %eax  # Shift right byte into lower short
  andl $0x0000ffff, %eax
  DO_IMM_POST

do_SB:
  DO_STORE_PRE $24 do_SB $0 # eax = old value, r9d = new
  andl $3, %ecx  # Get lower bits from address
  shll $3, %ecx  # Multiply by 8
  mov $0xff, %r10d  # Load mask into r10d
  shll %cl, %r10d  # Move mask to right position
  notl %r10d  # Invert
  andl %r10d, %eax  # Mask out EAX bits
  andl $0xff, %r12d  # Make sure we are only writing a byte
  shll %cl, %r12d  # Shift byte into place
  orl %r12d, %eax  # Or it in
  DO_STORE_POST

do_SH:
  DO_STORE_PRE $25 do_SH $0 # eax = old value, r9d = new
  andl $3, %ecx  # Get lower bits from address
  shll $3, %ecx  # Multiply by 8
  mov $0xffff, %r10d  # Load mask into r10d
  shll %cl, %r10d  # Move mask to right position
  notl %r10d  # Invert
  andl %r10d, %eax  # Mask out EAX bits
  andl $0xffff, %r12d  # Make sure we are only writing a byte
  shll %cl, %r12d  # Shift byte into place
  orl %r12d, %eax  # Or it in
  DO_STORE_POST

do_SW:
  DO_STORE_PRE $26 do_SW $3 # eax = old value, r9d = new
  mov %r12d, %eax
  DO_STORE_POST

do_BEQ:
  DO_BRANCH $27

do_BNE:
  DO_BRANCH $28

do_BLT:
  DO_BRANCH $29

do_BGE:
  DO_BRANCH $30

do_BLTU:
  DO_BRANCH $31

do_BGEU:
  DO_BRANCH $32

# Given that EDX still holds original instruction
# If low two bits 11, add 4, else add 2
.macro ADD_INST_LEN
  and $3, %edx  # Get low two bits
  cmp $3, %edx  # See if they are 11
  sete %dl  # If so set dl + 1, i.e. 11 -> 1, anything else to 0
  lea 2(%rax, %rdx, 2), %rax
.endm

do_JAL:
  WRITE_INST $33  # Write opcode data to log
  LOG_OLD_RD  # Log the current RD value before it is overwritten
  movl PC, %eax  # Write PC to eax
  ADD_INST_LEN  # Add 2 or 4 to PC
  DO_IMM_POST  # Tail half of LUI looks like IMM

do_JALR:
  WRITE_INST $34  # Write opcode data to log
  LOG_OLD_RD  # Log the current RD value before it is overwritten
  LOAD_RS1_EAX  # Load RS1 into EAX (and log)
  movl %eax, %ecx
  addl IMM, %ecx
  movl PC, %eax  # Write PC to eax
  ADD_INST_LEN  # Add 2 or 4 to PC
  INC_CYCLE  # Move to the 'write' cycle
  WRITE_EAX_RD  # Write EAX to RD
  mov %ecx, %eax
  movq $EXIT_CAUSE_JALR, CTX_EXIT_CAUSE_OFF(CTX)
  INST_END  # Finish instruction

do_LUI:
  WRITE_INST $35  # Write opcode data to log
  LOG_OLD_RD  # Log the current RD value before it is overwritten
  movl IMM, %eax  # Write IMM to eax
  DO_IMM_POST  # Tail half of LUI looks like IMM

do_AUIPC:
  WRITE_INST $36  # Write opcode data to log
  LOG_OLD_RD  # Log the current RD value before it is overwritten
  movl PC, %eax  # Write PC to eax
  addl IMM, %eax  # Add IMM to it
  DO_IMM_POST  # Tail half of LUI looks like IMM

do_MUL:
  DO_REG_PRE $37
  imull %ecx, %eax
  DO_REG_POST

do_MULH:
  DO_REG_PRE $38
  imull %ecx
  movl %edx, %eax
  DO_REG_POST

do_MULHSU:
  DO_REG_PRE $39
  movl %eax, %ebx # EBX = a
  sarl $31, %ebx  # EBX = 0xffffffff if a < 0, else 0
  mull %ecx  # unsigned mul: edx:eax = (uint32)a * (uint32)b
  andl %ecx, %ebx  # EBX = (a < 0 ? ECX : 0)
  subl %ebx, %edx  # adjust high word for signed×unsigned
  movl %edx, %eax  # result → eax
  DO_REG_POST

do_MULHU:
  DO_REG_PRE $40
  mull %ecx
  movl %edx, %eax
  DO_REG_POST

do_DIV:
  DO_REG_PRE $41
  cmpl $0, %ecx  # divisor == 0 ?
  je .Ldiv_zero  # yes -> result = -1
  cmpl $0x80000000, %eax  # dividend == INT_MIN ?
  jne .Ldiv_do
  cmpl $-1, %ecx  # divisor == -1 ?
  je .Ldiv_done  # In overflow case, we already have the right answer (0x80000000) 
.Ldiv_do:
  cdq  # sign-extend EAX into EDX:EAX
  idivl %ecx  # signed divide: EDX:EAX / ECX, quotient -> EAX, remainder -> EDX
  jmp .Ldiv_done
.Ldiv_zero:
  movl $-1, %eax  # 0xffffffff
.Ldiv_done:
  DO_REG_POST

do_DIVU:
  DO_REG_PRE $42
  cmpl $0, %ecx
  je .Ldivu_zero  # divisor == 0 → 0xffffffff
  xorl %edx, %edx  # zero-extend dividend into EDX:EAX
  divl %ecx  # unsigned divide, quotient -> EAX, remainder -> EDX
  jmp .Ldivu_done
.Ldivu_zero:
  movl $-1, %eax  # 0xffffffff
.Ldivu_done:
  DO_REG_POST

do_REM:
  DO_REG_PRE $43
  cmpl $0, %ecx
  je .Lrem_done  # divisor == 0 → result = dividend (already in eax)
  cmpl $0x80000000, %eax  # dividend == INT_MIN ?
  jne .Lrem_do
  cmpl $-1, %ecx  # divisor == -1 ?
  jne .Lrem_do
  # Special overflow case: INT_MIN / -1 -> quotient INT_MIN, remainder 0
  xorl %eax, %eax  # remainder = 0
  jmp .Lrem_done
.Lrem_do:
  cdq  # sign-extend EAX → EDX:EAX
  idivl %ecx  # signed divide, quotient -> EAX, remainder -> EDX
  movl %edx, %eax  # return remainder in EAX
.Lrem_done:
  DO_REG_POST

do_REMU:
  DO_REG_PRE $44
  cmpl $0, %ecx
  je .Lremu_done  # divisor == 0 → result = dividend
  xorl %edx, %edx  # zero-extend dividend into EDX:EAX
  divl %ecx  # unsigned divide, quotient -> EAX, remainder -> EDX
  movl %edx, %eax  # result = remainder
.Lremu_done:
  DO_REG_POST

do_ECALL:
  # Log the instruction, but don't actually increment the cycle #
  # Do all the real work in the emulator
  WRITE_INST $45
  movl PC, %eax
  movq $EXIT_CAUSE_ECALL, CTX_EXIT_CAUSE_OFF(CTX)
  ret 

do_MRET:
  # Also handle MRET in emulator
  WRITE_INST $46
  movl PC, %eax
  movq $EXIT_CAUSE_MRET, CTX_EXIT_CAUSE_OFF(CTX)
  ret 

do_ANY:
  # Also handle ANY in emulator
  WRITE_INST $47
#if !PREFLIGHT 
  movl OINST, LOG_OINST_OFF(LOG) # Write original inst
#endif
  movl PC, %eax
  movq $EXIT_CAUSE_ANY, CTX_EXIT_CAUSE_OFF(CTX)
  ret 

fetch_fault:
  movq $EXIT_CAUSE_FETCH, CTX_EXIT_CAUSE_OFF(CTX)
  ret 

block_header:
  subq %r8, CTX_QUOTA_OFF(CTX)
  js .Lquota_empty
  ret

# Handle misalignment
.Lalignment_trap:
  movq $EXIT_CAUSE_ALIGNMENT, CTX_EXIT_CAUSE_OFF(CTX)
  jmp .Lexit_exception

.Lpage_fault_trap:
  # Technically, we should maybe use a different code
  # but the efect is the same
  movq $EXIT_CAUSE_ALIGNMENT, CTX_EXIT_CAUSE_OFF(CTX)
  movl LOG_PC_OFF(LOG), %r12d
  jmp .Lexit_exception

.Lcycles_empty:
  movq $EXIT_CAUSE_CYCLES_OUT, CTX_EXIT_CAUSE_OFF(CTX)  # Set cause
  jmp .Lexit_exception  # Exit with exception

.Lquota_empty:
  addq %r8, CTX_QUOTA_OFF(CTX)  # Undo effect
  movq $EXIT_CAUSE_QUOTA_OUT, CTX_EXIT_CAUSE_OFF(CTX)
  jmp .Lexit_exception

.Lexit_exception:
#if PREFLIGHT
  movq LOG, CTX_LOG_OFF(CTX)
#endif
  movq CYCLE, CTX_CYCLE_OFF(CTX)
  add $24, %rsp  # Drop two stack frames + padding
  movq %r12, %rax  # Specify which IP we failed at
  # Restore callee save registers
  pop %r15
  pop %r14
  pop %r13
  pop %r12
  pop %rbp
  pop %rbx
  ret  # Exit back to c+++

enter:
  # Save caller save registers
  push %rbx
  push %rbp
  push %r12
  push %r13
  push %r14
  push %r15
  sub $8, %rsp  # Alignment
  # Save address to jump do (entry block)
  movq %rsi, %rax
  # Initialize local registers I care about
  movq CTX_REGS_OFF(CTX), REGS
  movq CTX_LOG_OFF(CTX), LOG
  movq CTX_CYCLE_OFF(CTX), CYCLE
#if PREFLIGHT
  movq $0x100000000, CYCLE_INC_VAL
#else
  movq $0x200000000, CYCLE_INC_VAL
#endif
  movq CTX_PAGES_OFF(CTX), PAGES
  # Call into basic block, which will jump around + return
  call *%rax 
  # Save data back to context
#if PREFLIGHT
  movq LOG, CTX_LOG_OFF(CTX)
#endif
  movq CYCLE, CTX_CYCLE_OFF(CTX)
  # Undo stack manipulations
  add $8, %rsp
  pop %r15
  pop %r14
  pop %r13
  pop %r12
  pop %rbp
  pop %rbx
  ret
