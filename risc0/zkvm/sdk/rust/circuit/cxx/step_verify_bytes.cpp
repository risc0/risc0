// This code is automatically generated

#include "ffi.h"
#include "fp.h"

#include <array>
#include <stdexcept>

// clang-format off
namespace risc0::circuit::rv32im {

Fp step_verify_bytes(void* ctx, HostBridge host, size_t steps, size_t cycle, Fp** args) {
  size_t mask = steps - 1;
  std::array<Fp, 32> host_args;
  std::array<Fp, 5> host_outs;
  Fp x0(1);
  return x0;
}

} // namespace risc0::circuit::rv32im
// clang-format on
