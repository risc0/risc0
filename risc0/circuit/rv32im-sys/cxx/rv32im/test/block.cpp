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

#include "core/log.h"

#define CONSTANT constexpr
#define FDEV /**/

#include "rv32im/circuit/circuit.ipp"

namespace {
// Local test version of context

struct Context;

struct Reg {
  Fp data;

  Fp get() { return data; }
  void set(const Context& ctx, Fp val) { data = val; }
  template <typename T> void applyInner(Context& ctx) {}
  void verify(Context& ctx) {}
  void addArguments(Context& ctx) {}
};

struct Context {
  using ValImpl = Fp;
  using ValExtImpl = FpExt;
  using RegImpl = Reg;
  using ArgCountRegImpl = Reg;

  void eqz(Fp val) {
    if (val != Fp(0)) {
      throw std::runtime_error("Invalid EQZ");
    }
  }
};

};

int main() {
  Context ctx;

  // Set up a valid witness
  Option opts = EncodeOptions(UnitKind::UNIT_BIT, BitKind::BIT_XOR);
  UnitBitWitness wit;
  wit.count = 17;
  wit.opts = opts.val;
  wit.a = 0b1010;
  wit.b = 0b1100;
  wit.out0 = 0b0110;
  wit.out1 = 0;

  // Set the based on that 
  UnitBitBlock<Context> block;
  block.set(ctx, wit);

  // Print a specific register by name
  LOG(0, "block.aBits[1] = " << block.aBits[1].get());

  // Print the actual full set of interal registers via a cast to Fp
  const Fp* fps = reinterpret_cast<const Fp*>(&block);
  for (size_t i = 0; i < sizeof(block) / sizeof(Fp); i++) {
    LOG(0, "Reg " << i << " = " << fps[i]);
  }

  // Verify constraints
  LOG(0, "Doing verify");
  block.verify(ctx);

  // Make invalid witness + update block
  // Or you could directly manipulate via:
  // block.out.low.set(0)
  wit.out0 = 0;
  block.set(ctx, wit);

  LOG(0, "Doing verify that should fail");
  bool failed = false;
  try {
    block.verify(ctx);
  } catch(const std::exception& ex) {
    failed = true;
  }
  if (!failed) {
    throw std::runtime_error("Should have failed");
  }
  LOG(0, "Yup, failed");

}
