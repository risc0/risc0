#pragma once

#include "risc0/zkp/accel/accel.h"
#include "risc0/zkp/core/fp4.h"
#include "risc0/zkp/prove/write_iop.h"

#include <functional>

namespace risc0 {

using InnerProve = std::function<void(WriteIOP& iop, size_t idx)>;

// Make a proof that poly has degree <= poly.size().
// Additionally, for each query, any innner proof data can we written (which for verifications
// will provide the validation that the point queried is correct).  Note, evaluation is over a
// region kInvRate * poly.size().  Finally, this code may modify the coeffs sent in.
void friProve(WriteIOP& iop, AccelConstSlice<Fp> coeffs, InnerProve inner);

} // namespace risc0
