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

#include "risc0/zkp/verify/fri.h"

#include <memory>

#include "risc0/core/log.h"
#include "risc0/core/util.h"
#include "risc0/zkp/core/constants.h"
#include "risc0/zkp/core/ntt.h"
#include "risc0/zkp/core/rou.h"
#include "risc0/zkp/verify/merkle.h"

namespace risc0 {

namespace {

// Given polynomial coefficents for f(x) of degree D, there are N unique polynomials g_i, of degree
// D/N such that f(x) = sum_i g_i(x^N) x^i.

// Given N coeffients m_i, one can compute a 'folded' polynomial h of degree D/N, such that h(x) =
// sum_i m_i * g_i(x).

// Given an the evaluation of a polynomial f(x) as above over a set of N points x_i, where x_i =
// w^(i*S + j), 0 <= i < N, and w^S*N == 1, and given m_i as per above, we need a way to
// compute h(w^(j*N)).

// Begin with the identity defined by the folding
// f(x) = sum_i g_i(x^N) x^i
//
// Plug is the values of w^(j*S + k), 0 <= j < N (basically reindexing our assumption).
// f(w^(j*S + k)) = sum_i g_i(w^(j*S*N + k*N)) * w^(j*S+k)^i
// f(w^(j*S + k)) = sum_i g_i(w^(k*N)) * w^(j*S+k)^i
//
// Treating w, S, and k as a constants above, and calling
// F_j = f(w^(j*S + k))
// G_i = g_i(w^(k*N))
// We basically get the set of linear relations:
// For all j: F_j = sum_i G_i * w^(i*j*S+k*i)
//
// Rearranging slightly, we have
// For all j: F_j = sum_i w^(i*j*S) w^(k*i) * G_i
//
// This in turn looks like multiplying each element of G_i by w^(k*i) and doing a fourier transform.
// Thus to reverse it (from F_j -> G_i) we do a reverse fourier transform and than an eltwise
// multiply by w^(-k*i).
//
// Finally, we have all the g_i(w^(k*N)), we just need to mix them via m_i and we are done
// h(w^(k*N)) = sum_i m_i G_i
//
// We replace k by j in the above since j is no longer used.  Also, N is fixed to kFriFold, and we
// set m_i = m^i for m='mix' below.

Fp4 foldEval(Fp4* values, Fp4 mix, size_t S, size_t j) {
  size_t N = kFriFold;
  interpolateNTT(values, kFriFold);
  bitReverse(values, kFriFold);
  size_t rootPo2 = log2Ceil(N * S);
  Fp invWK = pow(kRouRev[rootPo2], j);
  Fp mul(1);
  Fp4 tot;
  Fp4 mixPow(1);
  for (size_t i = 0; i < N; i++) {
    tot += values[i] * mul * mixPow;
    mul *= invWK;
    mixPow *= mix;
  }
  return tot;
}

struct VerifyRoundInfo {
  size_t domain;
  MerkleTreeVerifier merkle;
  Fp4 mix;

  VerifyRoundInfo(ReadIOP& iop, size_t inDomain)
      : domain(inDomain / kFriFold)
      , merkle(iop, domain, kFriFold * 4, kQueries)
      , mix(Fp4::random(iop)) {}

  void verifyQuery(ReadIOP& iop, size_t* pos, Fp4* goal) const {
    // Compute which group we are in
    size_t quot = *pos / domain;
    size_t group = *pos % domain;
    // Get the column data
    auto data = merkle.verify(iop, group);
    std::vector<Fp4> data4(kFriFold);
    for (size_t i = 0; i < kFriFold; i++) {
      data4[i] = Fp4(data[0 * kFriFold + i],
                     data[1 * kFriFold + i],
                     data[2 * kFriFold + i],
                     data[3 * kFriFold + i]);
    }
    // Check the existing goal
    REQUIRE(data4[quot] == *goal);
    // Compute the new goal + pos
    *goal = foldEval(data4.data(), mix, domain, group);
    *pos = group;
  }
};

} // namespace

// Verify a FRI proof,
void friVerify(ReadIOP& iop, size_t deg, InnerVerify inner) {
  size_t domain = deg * kInvRate;
  size_t origDomain = domain;
  std::vector<VerifyRoundInfo> rounds;
  // Prep the folding verfiers
  while (deg > kFriMinDegree) {
    rounds.emplace_back(iop, domain);
    domain /= kFriFold;
    deg /= kFriFold;
  }
  // Grab the final coeffs + commit
  std::vector<Fp> finalCoeffs(deg * 4);
  iop.read(finalCoeffs.data(), finalCoeffs.size());
  auto digest = shaHash(finalCoeffs.data(), finalCoeffs.size(), 1, false);
  iop.commit(digest);
  // Get the generator for the final polynomial evaluations
  Fp gen = kRouFwd[log2Ceil(domain)];
  // Do queries
  for (size_t q = 0; q < kQueries; q++) {
    // Get a 'random' index.
    uint32_t rng = iop.generate();
    size_t pos = rng % origDomain;
    // Do the 'inner' verification for this index
    Fp4 goal = inner(iop, pos);
    // Verify the per-round proofs
    for (auto& round : rounds) {
      round.verifyQuery(iop, &pos, &goal);
    }
    // Do final verification
    Fp x = pow(gen, pos);
    Fp4 fx;
    Fp cur(1);
    for (size_t i = 0; i < deg; i++) {
      for (size_t j = 0; j < 4; j++) {
        fx.elems[j] += cur * finalCoeffs[j * deg + i];
      }
      cur *= x;
    }
    REQUIRE(fx == goal);
  }
}

} // namespace risc0
