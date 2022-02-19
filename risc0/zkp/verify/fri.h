#pragma once

#include "risc0/zkp/accel/accel.h"
#include "risc0/zkp/core/fp4.h"
#include "risc0/zkp/verify/read_iop.h"

#include <functional>

namespace risc0 {

using InnerVerify = std::function<Fp4(ReadIOP& iop, size_t idx)>;

// Verify a polynomial of degree 'deg', whose values at idx are returned by the inner verifier
void friVerify(ReadIOP& iop, size_t deg, InnerVerify inner);

} // namespace risc0
