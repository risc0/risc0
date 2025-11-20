  .file	"foo.c"
	.text

// Scratch: rax- rdx
CTX = %rdi
LOG = %rsi
RDN = %r8
RS1N = %r9
RS2N = %r10
IMM = %r11d
CYCLE = %r12
CYCLE_INC_VAL = %r13

CTX_CYCLE_OFF = -8
CTX_QUOTA_OFF = -16
CTX_LOG_OFF = -24

LOG_RD_OFF = 8
LOG_RS1_OFF = 16
LOG_RS2_OFF = 16

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
.endm

.macro WRITE_EAX_RD
  orq CYCLE, %rax  # Add cycle
  movq %rax, (CTX, RDN, 8)  # Write to RD
.endm

.macro INST_END
  INC_CYCLE
  add $32, LOG
  ret
.endm

.macro DO_IMM opcode, op
  WRITE_INST \opcode
  LOG_OLD_RD
  LOAD_RS1_EAX
  \op IMM, %eax
  INC_CYCLE
  WRITE_EAX_RD
  INST_END
.endm

do_ADDI:
  DO_IMM $10, addl

.macro DO_BRANCH opcode
  WRITE_INST \opcode
  LOAD_RS1_EAX
  LOAD_RS2_ECX
  INC_CYCLE
  INST_END
.endm

do_BNE:
  DO_BRANCH $28

do_LUI:
  WRITE_INST $35
  LOG_OLD_RD
  movl IMM, %eax
  INC_CYCLE
  WRITE_EAX_RD
  INST_END

enter:
  # Save caller save registers (that I touch)
  push %rbx
  push %r12
  push %r13
  # Save address to jump do (entry block)
  movq %rsi, %rax
  # Initialize local registers I care about
  movq CTX_LOG_OFF(CTX), LOG
  movq CTX_CYCLE_OFF(CTX), CYCLE
  movq $0x100000000, CYCLE_INC_VAL
  # Call into basic block, which will jump around + return
  call %rax 
  # Save data back to context
  movq LOG, CTX_LOG_OFF(CTX)
  movq CYCLE, CTX_CYCLE_OFF(CTX)
  # Undo stack manipulations
  pop %r13
  pop %r12
  pop %rbx
  ret
