#include <cstdint>
#include <map>
#include <string>

namespace risc0 {

// Loads an ELF file and collects the memory that would be written on loading in memOut
// All writes are 32 bit wide and aligned (i.e. addr % 4 == 0).  Throws
// std::runtime_error on any errors (file, type, misalignment, addr >= maxMem, etc).  Returns
// the entry point address.

uint32_t loadElf(const std::string& name, uint32_t maxMem, std::map<uint32_t, uint32_t>& memOut);

} // namespace risc0
