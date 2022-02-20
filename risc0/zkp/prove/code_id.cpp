#include "risc0/zkp/prove/code_id.h"

#include <map>
#include <fstream>

#include "risc0/core/elf.h"
#include "risc0/zkp/prove/poly_group.h"
#include "risc0/zkp/prove/step/step.h"

namespace risc0 {

CodeID makeCodeID(const std::string& elfFile) {
  // Load the ELF file into an image
  std::map<uint32_t, uint32_t> image;
  uint32_t startAddr = loadElf(elfFile, kMemSize, image);
 
  // Start with an empty return value 
  CodeID ret;

  // Make the digest for each level
  for(size_t i = 0; i < kCodeDigestCount; i++) {
    size_t cycles = kMinCycles * (1 << i);
    if (cycles < image.size() + 3 + kZkCycles) {
      // Can't even fit the program in this cycle size, just set to zero
      ret[i] = ShaDigest::zero();
      continue;
    }
    // Make a vector + set it up with the elf data
    std::vector<Fp> code(cycles * kCodeSize);
    setupCode(code.data(), cycles, startAddr, image);
    // Copy into accel buffer
    auto coeffs = AccelSlice<Fp>::copy(code);
    // Do interpolate + shift
    batchInterpolateNTT(coeffs, kCodeSize);
    zkShiftAccel(coeffs, kCodeSize);
    // Make the poly-group + extract the root
    PolyGroup codeGroup(coeffs, kCodeSize, cycles);
    ret[i] = codeGroup.getMerkle().getRoot();
  }
  return ret;
}

void writeCodeID(const std::string& filename, const CodeID& id) {
  std::ofstream file(filename, std::ios::out | std::ios::binary );
  if (!file) {
    throw std::runtime_error("Unable to open file: " + filename);
  }
  file.write(reinterpret_cast<const char*>(&id), sizeof(CodeID));
  file.close();
  if (!file.good()) {
    throw std::runtime_error("Error writing code id file: " + filename);
  }
}

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

}  // namespace risc0
