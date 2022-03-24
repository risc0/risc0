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

#include "risc0/zkp/prove/poly_group.h"

#include "risc0/zkp/core/constants.h"

namespace risc0 {

PolyGroup::PolyGroup(AccelSlice<Fp> coeffs, size_t count, size_t size)
    : coeffs(coeffs), count(count), size(coeffs.size() / count), domain(size * kInvRate) {
  REQUIRE(coeffs.size() == count * size);
  evaluated = AccelSlice<Fp>::allocate(count * domain);
  batchExpand(evaluated, coeffs, count);
  batchEvaluateNTT(evaluated, count, log2Ceil(kInvRate));
  batchBitReverse(coeffs, count);
  merkle = std::make_unique<MerkleTreeProver>(evaluated, domain, count, kQueries);
}

} // namespace risc0
