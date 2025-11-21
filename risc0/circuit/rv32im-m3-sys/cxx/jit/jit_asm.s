  .file	"foo.c"
	.text

# Declare which registers we asign to which logical values 

# EAX - EDX as # basically scratch, but typically we use EAX as RS1 and RD, and
# ECX as RS2

CTX = %rdi  # Context pointer back to c++ code
LOG = %rsi  # Head of instruction log
RDN = %r8  # Which register is RD (i.e. RD number)
RS1N = %r9  # Which register is RS1
RS2N = %r10  # Which register is RS2
IMM = %r11d  # What was the 32 bit version of the immediate in the instruction
PC = %r12d  # What PC was this instruction original on
CYCLE = %r13  # The current cycle is in the high 32 bits of this number
CYCLE_INC_VAL = %r14  # The value 2^32 used to 'increment' the cycle
PAGES = %r15

# Information about where various variables live in the C+++ code

# Offsets for the JitContext structure, when given a pointer to start of registers
CTX_CYCLE_OFF = -8
CTX_QUOTA_OFF = -16
CTX_LOG_OFF = -24
CTX_PAGES_OFF = -32
CTX_PAGE_MISS_OFF = 1024;

# Offsets in the log
LOG_RD_OFF = 8
LOG_RS1_OFF = 16
LOG_RS2_OFF = 24 

# Next we have common 'parts' of instructions (getting RS1 + RS2, logging
# RD's original state, etc).  When then use these to build instruction
# categories (3-reg, imm, etc), and finally instructions

.macro WRITE_INST, INST  # Write instruction info to the loga
  movb \INST, (LOG)  # Write opcode
  movb %r8b, 1(LOG)  # Write RD
  movb %r9b, 2(LOG)  # Write RS1
  movb %r10b, 3(LOG)  # Write RS2
  movl IMM, 4(LOG)  # Write IMM
.endm

.macro INC_CYCLE  # Incement cycle #
  addq CYCLE_INC_VAL, CYCLE  # Inc cycle
.endm

.macro LOG_OLD_RD  # Log orignal RD value (for things that write to RD)
  movq (CTX, RDN, 8), %rax  # Load RD
  movq %rax, LOG_RD_OFF(LOG)  # Save to log
.endm

.macro LOAD_RS1_EAX  # Log original RS1 value, and load RS1 into EAX
  movq (CTX, RS1N, 8), %rax  # Load RS1 into %rax
  movq %rax, LOG_RS1_OFF(LOG)  # Save to log
  movl %eax, %eax  # Clear high 32 bits
  orq CYCLE, %rax  # Add cycle
  movq %rax, (CTX, RS1N, 8)  # Write back
.endm

.macro LOAD_RS2_ECX  # Log original RS2 value, and load RS2 into ECX
  movq (CTX, RS2N, 8), %rcx  # Load RS2 into %rcx
  movq %rcx, LOG_RS2_OFF(LOG)  # Save to log
  movl %ecx, %ecx  # Clear high 32 bits
  orq CYCLE, %rcx  # Add cycle
  movq %rcx, (CTX, RS2N, 8)  # Write back
  test $0x40, RS2N  # Check if RS2 is a 'trash address'
  cmovnz %eax, %ecx  # If so, copy over eax
.endm

.macro WRITE_EAX_RD
  orq CYCLE, %rax  # Add cycle
  movq %rax, (CTX, RDN, 8)  # Write to RD
.endm

.macro INST_END
  INC_CYCLE  # Add final cycle
  add $32, LOG  # Move log forward
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

resolve_page:
  # Get function pointer to jump to
  movq CTX_PAGE_MISS_OFF(CTX), %rcx
  # Save critival data back to context
  movq LOG, CTX_LOG_OFF(CTX)
  movq CYCLE, CTX_CYCLE_OFF(CTX)
  push RDN  # Save RDN since I still need to write RD
  push %rax  # Save rax since it holds the full address
  push CTX  # Save CTX
  movq %rbx, %rsi  # Pass page up to c++
  call *%rcx
  movq %rax, %rcx  # Move return value to ecx
  pop CTX # Restore things
  pop %rax
  pop RDN
  # Reload things I need
  movq CTX_LOG_OFF(CTX), LOG
  movq CTX_CYCLE_OFF(CTX), CYCLE
  movq $0x100000000, CYCLE_INC_VAL
  movq CTX_PAGES_OFF(CTX), PAGES
  ret
  
do_LB:
  ud2

do_LH:
  ud2

do_LW:
  DO_IMM_PRE $21
  add IMM, %eax  # EAX is now the address to load from
  test $3, %eax  # Check for alignment
  jnz alignment_trap  # Fail not aligned
  mov %eax, %ebx  # Copy address to ebx
  shr $10, %ebx  # Shift, now we have the page #
  mov (PAGES, %rbx, 8), %rcx  # Load page pointer
  cmp $0, %rcx  # Check if it's NULL
  jne do_LW_skip  # if not, we are good to go
  call resolve_page  # Otherwise, resolve page
do_LW_skip:
  # Now, eax is the address, %rcx is the page pointer
  mov %eax, %ebx
  and $0x3ff, %ebx  # Clear low bit
  mov (%rcx, %rbx, 2), %rax  # Load the page data + cycle
  mov %rax, LOG_RS2_OFF(LOG)  # Log memory transaction
  mov %eax, %eax  # Clear top bits
  orq CYCLE, %rax  # Update cycle #
  mov %rax, (%rcx, %rbx, 2)  # Write back to memory
  DO_IMM_POST

do_LBU:
  ud2

do_LHU:
  ud2

do_SB:
  ud2

do_SH:
  ud2

do_SW:
  ud2

handle_alignment_trap:
  ud2

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

do_JAL:
  WRITE_INST $35  # Write opcode data to log
  LOG_OLD_RD  # Log the current RD value before it is overwritten
  movl PC, %eax  # Write PC to eax
  # TODO: Need to fix for compressed instructions
  addl $4, %eax  # Inc PC by 4
  DO_IMM_POST  # Tail half of LUI looks like IMM

do_JALR:
  ud2

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
  ud2

do_MULH:
  ud2

do_MULHSU:
  ud2

do_MULHU:
  ud2

do_DIV:
  ud2

do_DIVU:
  ud2

do_REM:
  ud2

do_REMU:
  ud2

do_ECALL:
  # We don't do anything, and the BB actually terminates with PC @ ECALL
  # No cycles pass, no logging happens, so we can do trap handling or
  # whatever we want
  ret 


do_MRET:
  ud2

enter:
  # Save caller save registers
  push %rbx
  push %r12
  push %r13
  push %r14
  push %r15
  # Save address to jump do (entry block)
  movq %rsi, %rax
  # Initialize local registers I care about
  movq CTX_LOG_OFF(CTX), LOG
  movq CTX_CYCLE_OFF(CTX), CYCLE
  movq $0x100000000, CYCLE_INC_VAL
  movq CTX_PAGES_OFF(CTX), PAGES
  # Call into basic block, which will jump around + return
  call %rax 
  # Save data back to context
  movq LOG, CTX_LOG_OFF(CTX)
  movq CYCLE, CTX_CYCLE_OFF(CTX)
  # Undo stack manipulations
  pop %r15
  pop %r14
  pop %r13
  pop %r12
  pop %rbx
  ret
