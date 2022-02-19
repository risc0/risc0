#include <string>

namespace risc0 {

std::string allKernelNames() {
  std::string out;
#define GPU_KERNEL(name, args, launch, impl) out += #name "\n";
#define PARALLEL_KERNEL(name, args, impl) out += #name "\n";
#include "risc0/zkp/accel/kernels/all.h"
  return out;
}

} // namespace risc0
