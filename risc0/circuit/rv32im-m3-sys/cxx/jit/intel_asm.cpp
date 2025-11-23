#include "jit/intel_asm.h"

#include <sys/mman.h>
#include <cstring>

namespace risc0::rv32im::jit {

Assembler::Assembler(size_t pages) {
  size_t size = pages * 4096;
  begin = (uint8_t*) mmap(NULL, size, PROT_READ | PROT_WRITE | PROT_EXEC,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (begin == MAP_FAILED) {
    throw std::runtime_error("Allocation of Jit region failed");
  }
  cur = begin;
  end = cur + size;
}

Assembler::~Assembler() {
  if (begin != MAP_FAILED) {
    munmap(begin, end - begin);
  }
}

uint32_t Assembler::getOffset() {
  return (cur - begin);
}

void Assembler::addBuiltins(const uint8_t* data, size_t size) {
  memcpy(cur, data, size);
  cur += size;
}


void Assembler::doLoadImm32(Reg reg, uint32_t imm) {
  if (isExtended(reg)) {
    writeByte(0x41);
  }
  // Move RAX, imm
  writeByte(0xb8 + (uint8_t(reg) & 7));
  writeU32(imm);
}

void Assembler::doLoadImm64(Reg reg, uint64_t imm) {
  if (isExtended(reg)) {
    writeByte(0x49);
  } else {
    writeByte(0x48);
  }
  // Rex prefix for 64 bit mode
  writeByte(0xb8 + (uint8_t(reg) & 7));
  writeU64(imm);
}

uint32_t Assembler::doLocalJump(uint32_t offset) {
  uint32_t curOffset = (cur - begin);
  uint32_t diff = offset - (curOffset + 5);
  if (offset == 0xffffffff) {
    diff = 0;
  }
  // Write PC local jump
  writeByte(0xe9);
  writeU32(diff);
  return curOffset + 1;
}

uint32_t Assembler::doBranch(CmpOp cmp, uint32_t offset) {
  // cmp %eax, %ecx
  writeByte(0x39);  // Opcode
  writeByte(0xC8);  // ModRM
  uint32_t curOffset = (cur - begin);
  uint32_t diff = offset - (curOffset + 6);
  writeByte(0x0f);
  writeByte(uint8_t(cmp));
  writeU32(diff);
  return curOffset + 2;
}

void Assembler::fixup(uint32_t fixupOffset, uint32_t newDest) {
  uint8_t* code = begin + fixupOffset;
  uint32_t diff = newDest - (fixupOffset + 4);
  code[0] = diff & 0xff;
  code[1] = (diff >> 8) & 0xff;
  code[2] = (diff >> 16) & 0xff;
  code[3] = (diff >> 24) & 0xff;
}

void Assembler::doCall(uint32_t offset) {
  uint32_t self = (cur - begin) + 5;
  writeByte(0xe8);
  int32_t diff = offset - self;
  writeU32(diff);
}

void Assembler::doRet() {
  writeByte(0xc3);
}

uint64_t Assembler::getAddr(uint64_t offset) {
  return reinterpret_cast<uint64_t>(begin + offset);
}

uint64_t Assembler::call(uint32_t offset, uint64_t arg1, uint64_t arg2) {
  FuncPtr2 fptr = reinterpret_cast<FuncPtr2>(begin + offset);
  return fptr(arg1, arg2); 
}

}  // namespace risc0::rv32im::jit
