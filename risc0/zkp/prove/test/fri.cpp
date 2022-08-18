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

#include "risc0/zkp/prove/fri.h"
#include "risc0/core/log.h"
#include "risc0/core/rng.h"
#include "risc0/core/util.h"
#include "risc0/zkp/core/constants.h"
#include "risc0/zkp/core/rou.h"
#include "risc0/zkp/verify/fri.h"

#include <gtest/gtest.h>

namespace risc0 {

static Fp4 splitPolyEval(const Fp* poly, size_t deg, Fp x) {
  Fp4 fx;
  Fp cur(1);
  for (size_t i = 0; i < deg; i++) {
    for (size_t j = 0; j < 4; j++) {
      fx.elems[j] += cur * poly[j * deg + i];
    }
    cur *= x;
  }
  return fx;
}

TEST(Prove, FRI) {
  size_t deg = 8192;
  size_t domain = deg * kInvRate;
  // Make a random polynomial
  PseudoRng rng(3);
  LOG(1, "Making random poly, in 'colwise' Fp4");
  auto poly = AccelSlice<Fp>::allocate(deg * 4);
  {
    AccelWriteOnlyLock lock(poly);
    for (size_t i = 0; i < lock.size(); i++) {
      lock[i] = Fp::random(rng);
    }
  }
  WriteIOP wiop;
  // Generate the proof
  LOG(1, "Doing proof");
  friProve(wiop, poly, [&](WriteIOP& iop, size_t idx) {});
  auto proof = wiop.getProof();
  LOG(1, "Proof size = " << proof.size());
  // Verify it normallly
  batchBitReverse(poly, 4);
  AccelReadLock polyView(poly);
  ReadIOP riop(proof.data(), proof.size());
  Fp gen = kRouFwd[log2Ceil(domain)];
  LOG(1, "Doing verification");
  friVerify(riop, deg, [&](ReadIOP& iop, size_t idx) {
    return splitPolyEval(polyView.data(), deg, pow(gen, idx));
  });

  /*
  // Verify it fails when the proof is modified
  for (size_t i = 0; i < proof.size(); i++) {
    LOG(1, "Validating change to " << i << " breaks things");
    proof[i] += 1_fp;
    ReadIOP riop2(verifier, proof);
    ASSERT_THROW((friVerify(params,
                            riop2,
                            size,
                            deg,
                            [&](auto& iop, Fp idx) { return polyEval(polyView, pow(gen, idx)); }),
                  verifier.finalize()),
                 std::runtime_error);
    proof[i] -= 1_fp;
  }
  */
}

} // namespace risc0
