#include <iostream>

#include "risc0/zkp/prove/code_id.h"

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "usage: make-id <elf_in> <id_out>" << std::endl;
    return 1;
  }
  try {
    risc0::CodeID id = risc0::makeCodeID(argv[1]);
    risc0::writeCodeID(argv[2], id);
  } catch (const std::exception& e) {
    std::cerr << "Unable to make code ID: " << e.what() << std::endl;
    return 1;
  }
  return 0;
}
