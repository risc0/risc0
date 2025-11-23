#include <stddef.h>
#include <stdint.h>
#include <stdexcept>

namespace risc0::rv32im::jit {

// Define intel registers
enum class Reg : uint8_t {
  RAX = 0,
  RCX = 1,
  RDX = 2,
  RBX = 3,
  RSP = 4,
  RBP = 5,
  RSI = 6,
  RDI = 7,
  R8 = 8,
  R9 = 9,
  R10 = 10,
  R11 = 11,
  R12 = 12,
  R13 = 13,
  R14 = 14,
  R15 = 15,
};

enum class CmpOp : uint8_t {
  JO   = 0x80,  // Jump if overflow
  JNO  = 0x81,  // Jump if not overflow
  JB   = 0x82,  // Jump if below (unsigned) / carry
  JNB  = 0x83,  // Jump if not below
  JE   = 0x84,  // Jump if equal / zero
  JNE  = 0x85,  // Jump if not equal
  JBE  = 0x86,  // Jump if below or equal (unsigned)
  JNBE = 0x87,  // Jump if not below or equal
  JS   = 0x88,  // Jump if sign
  JNS  = 0x89,  // Jump if not sign
  JP   = 0x8A,  // Jump if parity
  JNP  = 0x8B,  // Jump if not parity
  JL   = 0x8C,  // Jump if less (signed)
  JNL  = 0x8D,  // Jump if not less (signed)
  JLE  = 0x8E,  // Jump if less or equal (signed)
  JNLE = 0x8F,  // Jump if not less or equal (signed)
};

typedef uint64_t (*FuncPtr2)(uint64_t, uint64_t);

class Assembler {
private:
  // Memory region to JIT to
  uint8_t* begin;
  uint8_t* cur;
  uint8_t* end;

  // Some code to write to the current buffer
  inline void writeByte(uint8_t val) {
    *cur = val;
    cur++;
  }

  inline void writeU32(uint32_t val) {
    writeByte(val);
    writeByte(val >> 8);
    writeByte(val >> 16);
    writeByte(val >> 24);
  }

  inline void writeU64(uint64_t val) {
    writeU32(val);
    writeU32(val >> 32);
  }

  inline constexpr bool isExtended(Reg reg) {
    return uint8_t(reg) >= 8;
  }

public:
  Assembler(size_t pages);
  ~Assembler();

  // Get the offset at which the next instruction will be written
  uint32_t getOffset();

  // Add any pre-compiled code
  void addBuiltins(const uint8_t* data, size_t size);

  // Emit code to load immediates into registre
  void doLoadImm32(Reg reg, uint32_t imm);
  void doLoadImm64(Reg reg, uint64_t imm);

  // Jump to a given offset: -1 means jump to end of this instruction which
  // is used to put a NO-op that can later be retargeted.  Returns the offset
  // of the immediate to allow later adjustment
  uint32_t doLocalJump(uint32_t offset = 0xffffffff);

  // Branch to a location, returns an offset to allow rewriting of the destination
  // Presume we need to cmp %eax, %ecx first
  uint32_t doBranch(CmpOp cmp, uint32_t offset);

  // Modify existing local jump to point to a new destination
  void fixup(uint32_t fixupOffset, uint32_t newDest);

  // Emit a call to a given offset
  void doCall(uint32_t offset);

  // Emit a return
  void doRet();

  // Convert an offset into a full pointer value
  uint64_t getAddr(uint64_t offset);

  // Call into generated code at a given offset
  uint64_t call(uint32_t offset, uint64_t arg1, uint64_t arg2);
};

}  // namespace risc0::rv32im::jit
