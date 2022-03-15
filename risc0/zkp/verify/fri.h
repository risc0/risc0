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
#include "risc0/zkp/verify/read_iop.h"

#include <functional>

namespace risc0 {

using InnerVerify = std::function<Fp4(ReadIOP& iop, size_t idx)>;

// Verify a polynomial of degree 'deg', whose values at idx are returned by the inner verifier
void friVerify(ReadIOP& iop, size_t deg, InnerVerify inner);

} // namespace risc0
