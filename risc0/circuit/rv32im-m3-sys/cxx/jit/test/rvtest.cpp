#include "jit/jit.h"

#include "core/log.h"

using namespace risc0::rv32im;
using namespace risc0::jit;

void runTest(const std::string& testName) {
  std::string path = "rv32im/rvtest/" + testName;
  std::map<uint32_t, uint32_t> words;
  LOG(0, "Loading " << path);
  loadKernelV2(words, path);
  auto image = MemoryImage::fromWords(words);
  LOG(0, "Doing JIT");
  JitTrace trace;
  NullHostIO io;
  doJit(trace, image, io, 64*1024);
  LOG(0, "Done");
}

void runBench() {
  std::string path = "rv32im/test/asm_loop_kernel";
  std::map<uint32_t, uint32_t> words;
  LOG(0, "Loading " << path);
  loadKernelV2(words, path);
  auto image = MemoryImage::fromWords(words);
  LOG(0, "Doing JIT");
  JitTrace trace;
  NullHostIO io;
  doJit(trace, image, io, 2*1024*1024, true);
  LOG(0, "Done");
}

int main() {
  runBench();
  runTest("rvc");
  runTest("add");
  runTest("sub");
  runTest("xor");
  runTest("or");
  runTest("and");
  runTest("slt");
  runTest("sltu");
  runTest("addi");
  runTest("xori");
  runTest("ori");
  runTest("andi");
  runTest("slti");
  runTest("sltiu");
  runTest("beq");
  runTest("bne");
  runTest("blt");
  runTest("bge");
  runTest("bltu");
  runTest("bgeu");
  runTest("jal");
  runTest("jalr");
  runTest("lui");
  runTest("auipc");
  runTest("sll");
  runTest("slli");
  runTest("mul");
  runTest("mulh");
  runTest("mulhsu");
  runTest("mulhu");
  runTest("srl");
  runTest("sra");
  runTest("srli");
  runTest("srai");
  runTest("div");
  runTest("divu");
  runTest("rem");
  runTest("remu");
  runTest("lb");
  runTest("lh");
  runTest("lw");
  runTest("lbu");
  runTest("lhu");
  runTest("sb");
  runTest("sh");
  runTest("sw");
}
