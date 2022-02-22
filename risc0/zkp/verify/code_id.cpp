#include "risc0/zkp/verify/code_id.h"

#include <fstream>

namespace risc0 {

CodeID readCodeID(const std::string& filename) {
  std::ifstream file(filename, std::ios::in | std::ios::binary);
  if (!file) {
    throw std::runtime_error("Unable to open file: " + filename);
  }
  CodeID id;
  file.read(reinterpret_cast<char*>(&id), sizeof(CodeID));
  file.close();
  if (!file.good()) {
    throw std::runtime_error("Error reading code id file: " + filename);
  }
  return id;
}

} // namespace risc0
