// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

#pragma once

#include <functional>

#include "hal/hal.h"
#include "prove/merkle.h"
#include "zkp/params.h"

namespace risc0 {

class FriProverRound {
public:
  FriProverRound(IHalPtr hal, HalMatrix<Fp> coeffsIn);

  void compute(WriteIop& iop);
  void query(WriteIop& iop, size_t& pos);

  IHalPtr hal;
  HalMatrix<Fp> coeffsIn;
  HalMatrix<Fp> evaluated;
  MerkleProver merkle;
  HalMatrix<Fp> coeffsOut;
};

using ProvePointFunction = std::function<void(WriteIop&, size_t)>;

class FriProver {
public:
  FriProver(IHalPtr hal, HalMatrix<Fp> coeffs);

  void compute(WriteIop& iop, ProvePointFunction func);

private:
  IHalPtr hal;
  size_t degree;
  size_t domain;
  std::vector<FriProverRound> rounds;
  HalMatrix<Fp> last;
  HalMatrix<Fp> finalCoeffs;
};

} // namespace risc0
