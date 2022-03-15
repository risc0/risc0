// Copyright 2022 Risc0, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
