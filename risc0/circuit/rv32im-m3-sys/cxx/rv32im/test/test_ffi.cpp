#include "core/log.h"
#include "core/util.h"

extern "C" const char* risc0_circuit_rv32im_m3_prove(const uint8_t* elf_ptr, size_t elf_len);

void runTest(const std::string& name) {
  auto fullname = "rv32im/rvtest/" + name;
  auto elf = risc0::loadFile(fullname);
  risc0_circuit_rv32im_m3_prove(elf.data(), elf.size());
}

int main() {
  LOG(0, "Hello world");
  runTest("add");
  runTest("addi");
}
