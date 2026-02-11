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

// This code is automatically generated

#include "extern.h"

kernel void step_compute_accum(
    device void* ctx, const device uint32_t& steps, uint cycle [[thread_position_in_grid]], device Fp* arg0, device Fp* arg1, device Fp* arg2, device Fp* arg3, device Fp* arg4) {
  uint32_t mask = steps - 1;
  Fp extern_args[96];
  Fp extern_outs[32];
  // loc(unknown)
  Fp x0(2013265910);
  // loc(unknown)
  Fp x1(11);
  // loc(unknown)
  Fp x2(1);
  // loc(unknown)
  Fp x3(0);
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/micro_ops(Reg)"("./zirgen/components/mux.h":59:25))
  auto x4 = arg0[1 * steps + ((cycle - 0) & mask)];
  assert(x4 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/macro_ops(Reg)"("./zirgen/components/mux.h":59:25))
  auto x5 = arg0[2 * steps + ((cycle - 0) & mask)];
  assert(x5 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_load(Reg)"("./zirgen/components/mux.h":59:25))
  auto x6 = arg0[3 * steps + ((cycle - 0) & mask)];
  assert(x6 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_full(Reg)"("./zirgen/components/mux.h":59:25))
  auto x7 = arg0[4 * steps + ((cycle - 0) & mask)];
  assert(x7 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_partial(Reg)"("./zirgen/components/mux.h":59:25))
  auto x8 = arg0[5 * steps + ((cycle - 0) & mask)];
  assert(x8 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/poseidon2_store(Reg)"("./zirgen/components/mux.h":59:25))
  auto x9 = arg0[6 * steps + ((cycle - 0) & mask)];
  assert(x9 != Fp::invalid());
  // loc("top(recursion::Top)/code(recursion::Code)/select(OneHot)/checked_bytes(Reg)"("./zirgen/components/mux.h":59:25))
  auto x10 = arg0[7 * steps + ((cycle - 0) & mask)];
  assert(x10 != Fp::invalid());
  if (x4 != 0) {
    {
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x11 = arg3[0];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x12 = arg3[1];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x13 = arg3[10];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x14 = arg3[11];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x15 = arg3[12];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x16 = arg3[13];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x17 = arg3[14];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x18 = arg3[15];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x19 = arg3[16];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x20 = arg3[17];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x21 = arg3[18];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x22 = arg3[19];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x23 = arg3[2];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x24 = arg3[3];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x25 = arg3[4];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x26 = arg3[5];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x27 = arg3[6];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x28 = arg3[7];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x29 = arg3[8];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x30 = arg3[9];
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x31 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x31 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x32 = arg2[1 * steps + ((cycle - 0) & mask)];
      assert(x32 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x33 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x33 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x34 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x34 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x35 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x35 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x36 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x36 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x37 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x37 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x38 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x38 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x39 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x39 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x40 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x40 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x41 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x41 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x42 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x42 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x43 = arg2[2 * steps + ((cycle - 0) & mask)];
      assert(x43 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x44 = arg2[20 * steps + ((cycle - 0) & mask)];
      assert(x44 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x45 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x45 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x46 = arg2[22 * steps + ((cycle - 0) & mask)];
      assert(x46 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x47 = arg2[23 * steps + ((cycle - 0) & mask)];
      assert(x47 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x48 = arg2[24 * steps + ((cycle - 0) & mask)];
      assert(x48 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x49 = arg2[25 * steps + ((cycle - 0) & mask)];
      assert(x49 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x50 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x50 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x51 = arg2[27 * steps + ((cycle - 0) & mask)];
      assert(x51 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x52 = arg2[28 * steps + ((cycle - 0) & mask)];
      assert(x52 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x53 = arg2[29 * steps + ((cycle - 0) & mask)];
      assert(x53 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x54 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x54 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x55 = arg2[30 * steps + ((cycle - 0) & mask)];
      assert(x55 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x56 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x56 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x57 = arg2[32 * steps + ((cycle - 0) & mask)];
      assert(x57 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x58 = arg2[33 * steps + ((cycle - 0) & mask)];
      assert(x58 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x59 = arg2[34 * steps + ((cycle - 0) & mask)];
      assert(x59 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x60 = arg2[35 * steps + ((cycle - 0) & mask)];
      assert(x60 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x61 = arg2[36 * steps + ((cycle - 0) & mask)];
      assert(x61 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x62 = arg2[37 * steps + ((cycle - 0) & mask)];
      assert(x62 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x63 = arg2[38 * steps + ((cycle - 0) & mask)];
      assert(x63 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x64 = arg2[39 * steps + ((cycle - 0) & mask)];
      assert(x64 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x65 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x65 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x66 = arg2[40 * steps + ((cycle - 0) & mask)];
      assert(x66 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x67 = arg2[41 * steps + ((cycle - 0) & mask)];
      assert(x67 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x68 = arg2[42 * steps + ((cycle - 0) & mask)];
      assert(x68 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x69 = arg2[43 * steps + ((cycle - 0) & mask)];
      assert(x69 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x70 = arg2[44 * steps + ((cycle - 0) & mask)];
      assert(x70 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x71 = arg2[45 * steps + ((cycle - 0) & mask)];
      assert(x71 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x72 = arg2[46 * steps + ((cycle - 0) & mask)];
      assert(x72 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x73 = arg2[47 * steps + ((cycle - 0) & mask)];
      assert(x73 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x74 = arg2[48 * steps + ((cycle - 0) & mask)];
      assert(x74 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x75 = arg2[49 * steps + ((cycle - 0) & mask)];
      assert(x75 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x76 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x76 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x77 = arg2[50 * steps + ((cycle - 0) & mask)];
      assert(x77 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x78 = arg2[51 * steps + ((cycle - 0) & mask)];
      assert(x78 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x79 = arg2[52 * steps + ((cycle - 0) & mask)];
      assert(x79 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x80 = arg2[53 * steps + ((cycle - 0) & mask)];
      assert(x80 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x81 = arg2[54 * steps + ((cycle - 0) & mask)];
      assert(x81 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x82 = arg2[55 * steps + ((cycle - 0) & mask)];
      assert(x82 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x83 = arg2[56 * steps + ((cycle - 0) & mask)];
      assert(x83 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x84 = arg2[57 * steps + ((cycle - 0) & mask)];
      assert(x84 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x85 = arg2[58 * steps + ((cycle - 0) & mask)];
      assert(x85 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x86 = arg2[59 * steps + ((cycle - 0) & mask)];
      assert(x86 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x87 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x87 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x88 = arg2[60 * steps + ((cycle - 0) & mask)];
      assert(x88 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x89 = arg2[61 * steps + ((cycle - 0) & mask)];
      assert(x89 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x90 = arg2[62 * steps + ((cycle - 0) & mask)];
      assert(x90 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x91 = arg2[63 * steps + ((cycle - 0) & mask)];
      assert(x91 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x92 = arg2[64 * steps + ((cycle - 0) & mask)];
      assert(x92 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x93 = arg2[65 * steps + ((cycle - 0) & mask)];
      assert(x93 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x94 = arg2[66 * steps + ((cycle - 0) & mask)];
      assert(x94 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x95 = arg2[67 * steps + ((cycle - 0) & mask)];
      assert(x95 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x96 = arg2[68 * steps + ((cycle - 0) & mask)];
      assert(x96 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x97 = arg2[69 * steps + ((cycle - 0) & mask)];
      assert(x97 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x98 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x98 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x99 = arg2[70 * steps + ((cycle - 0) & mask)];
      assert(x99 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x100 = arg2[71 * steps + ((cycle - 0) & mask)];
      assert(x100 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x101 = arg2[72 * steps + ((cycle - 0) & mask)];
      assert(x101 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x102 = arg2[73 * steps + ((cycle - 0) & mask)];
      assert(x102 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x103 = arg2[74 * steps + ((cycle - 0) & mask)];
      assert(x103 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x104 = arg2[75 * steps + ((cycle - 0) & mask)];
      assert(x104 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x105 = arg2[76 * steps + ((cycle - 0) & mask)];
      assert(x105 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x106 = arg2[77 * steps + ((cycle - 0) & mask)];
      assert(x106 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x107 = arg2[78 * steps + ((cycle - 0) & mask)];
      assert(x107 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x108 = arg2[79 * steps + ((cycle - 0) & mask)];
      assert(x108 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x109 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x109 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x110 = arg2[80 * steps + ((cycle - 0) & mask)];
      assert(x110 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x111 = arg2[81 * steps + ((cycle - 0) & mask)];
      assert(x111 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x112 = arg2[82 * steps + ((cycle - 0) & mask)];
      assert(x112 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x113 = arg2[83 * steps + ((cycle - 0) & mask)];
      assert(x113 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x114 = arg2[84 * steps + ((cycle - 0) & mask)];
      assert(x114 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x115 = arg2[85 * steps + ((cycle - 0) & mask)];
      assert(x115 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x116 = arg2[86 * steps + ((cycle - 0) & mask)];
      assert(x116 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x117 = arg2[87 * steps + ((cycle - 0) & mask)];
      assert(x117 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x118 = arg2[88 * steps + ((cycle - 0) & mask)];
      assert(x118 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x119 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x119 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/micro_ops(recursion::MicroOps)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x120 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x120 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":230:23)
      auto x121 = x11 * x31;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x122 = x11 * x33;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x123 = x11 * x38;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x124 = x11 * x44;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x125 = x11 * x49;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x126 = x11 * x55;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x127 = x11 * x60;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x128 = x11 * x66;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x129 = x11 * x71;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x130 = x11 * x76;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x131 = x11 * x77;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x132 = x11 * x82;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x133 = x11 * x88;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x134 = x11 * x93;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x135 = x11 * x99;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x136 = x11 * x104;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x137 = x11 * x110;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x138 = x11 * x115;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x139 = x12 * x31;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x140 = x12 * x33;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x141 = x12 * x38;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x142 = x12 * x44;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x143 = x12 * x49;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x144 = x12 * x55;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x145 = x12 * x60;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x146 = x12 * x66;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x147 = x12 * x71;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x148 = x12 * x76;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x149 = x12 * x77;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x150 = x12 * x82;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x151 = x12 * x88;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x152 = x12 * x93;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x153 = x12 * x99;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x154 = x12 * x104;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x155 = x12 * x110;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x156 = x12 * x115;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x157 = x13 * x35;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x158 = x13 * x40;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x159 = x13 * x43;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x160 = x13 * x46;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x161 = x13 * x51;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x162 = x13 * x57;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x163 = x13 * x62;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x164 = x13 * x68;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x165 = x13 * x73;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x166 = x13 * x79;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x167 = x13 * x84;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x168 = x13 * x90;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x169 = x13 * x95;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x170 = x13 * x98;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x171 = x13 * x101;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x172 = x13 * x106;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x173 = x13 * x112;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x174 = x13 * x117;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x175 = x14 * x35;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x176 = x14 * x40;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x177 = x14 * x43;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x178 = x14 * x46;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x179 = x14 * x51;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x180 = x14 * x57;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x181 = x14 * x62;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x182 = x14 * x68;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x183 = x14 * x73;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x184 = x14 * x79;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x185 = x14 * x84;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x186 = x14 * x90;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x187 = x14 * x95;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x188 = x14 * x98;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x189 = x14 * x101;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x190 = x14 * x106;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x191 = x14 * x112;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x192 = x14 * x117;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x193 = x16 * x36;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x194 = x16 * x41;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x195 = x16 * x47;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x196 = x16 * x52;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x197 = x16 * x54;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x198 = x16 * x58;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x199 = x16 * x63;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x200 = x16 * x69;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x201 = x16 * x74;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x202 = x16 * x80;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x203 = x16 * x85;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x204 = x16 * x91;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x205 = x16 * x96;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x206 = x16 * x102;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x207 = x16 * x107;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x208 = x16 * x109;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x209 = x16 * x113;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x210 = x16 * x118;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x211 = x17 * x36;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x212 = x17 * x41;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x213 = x17 * x47;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x214 = x17 * x52;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x215 = x17 * x54;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x216 = x17 * x58;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x217 = x17 * x63;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x218 = x17 * x69;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x219 = x17 * x74;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x220 = x17 * x80;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x221 = x17 * x85;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x222 = x17 * x91;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x223 = x17 * x96;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x224 = x17 * x102;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x225 = x17 * x107;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x226 = x17 * x109;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x227 = x17 * x113;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x228 = x17 * x118;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x229 = x18 * x36;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x230 = x18 * x41;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x231 = x18 * x47;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x232 = x18 * x52;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x233 = x18 * x54;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x234 = x18 * x58;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x235 = x18 * x63;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x236 = x18 * x69;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x237 = x18 * x74;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x238 = x18 * x80;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x239 = x18 * x85;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x240 = x18 * x91;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x241 = x18 * x96;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x242 = x18 * x102;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x243 = x18 * x107;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x244 = x18 * x109;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x245 = x18 * x113;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x246 = x18 * x118;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x247 = x20 * x37;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x248 = x20 * x42;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x249 = x20 * x48;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x250 = x20 * x53;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x251 = x20 * x59;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x252 = x20 * x64;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x253 = x20 * x65;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x254 = x20 * x70;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x255 = x20 * x75;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x256 = x20 * x81;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x257 = x20 * x86;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x258 = x20 * x92;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x259 = x20 * x97;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x260 = x20 * x103;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x261 = x20 * x108;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x262 = x20 * x114;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x263 = x20 * x119;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x264 = x20 * x120;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x265 = x21 * x37;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x266 = x21 * x42;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x267 = x21 * x48;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x268 = x21 * x53;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x269 = x21 * x59;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x270 = x21 * x64;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x271 = x21 * x65;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x272 = x21 * x70;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x273 = x21 * x75;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x274 = x21 * x81;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x275 = x21 * x86;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x276 = x21 * x92;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x277 = x21 * x97;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x278 = x21 * x103;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x279 = x21 * x108;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x280 = x21 * x114;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x281 = x21 * x119;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x282 = x21 * x120;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x283 = x22 * x37;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x284 = x22 * x42;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x285 = x22 * x48;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x286 = x22 * x53;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x287 = x22 * x59;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x288 = x22 * x64;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x289 = x22 * x65;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x290 = x22 * x70;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x291 = x22 * x75;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x292 = x22 * x81;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x293 = x22 * x86;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x294 = x22 * x92;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x295 = x22 * x97;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x296 = x22 * x103;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x297 = x22 * x108;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x298 = x22 * x114;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x299 = x22 * x119;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x300 = x22 * x120;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x301 = x23 * x31;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x302 = x23 * x33;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x303 = x23 * x38;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x304 = x23 * x44;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x305 = x23 * x49;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x306 = x23 * x55;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x307 = x23 * x60;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x308 = x23 * x66;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x309 = x23 * x71;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x310 = x23 * x76;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x311 = x23 * x77;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x312 = x23 * x82;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x313 = x23 * x88;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x314 = x23 * x93;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x315 = x23 * x99;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x316 = x23 * x104;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x317 = x23 * x110;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x318 = x23 * x115;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x319 = x24 * x31;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x320 = x24 * x33;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x321 = x24 * x38;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x322 = x24 * x44;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x323 = x24 * x49;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x324 = x24 * x55;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x325 = x24 * x60;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x326 = x24 * x66;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x327 = x24 * x71;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x328 = x24 * x76;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x329 = x24 * x77;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x330 = x24 * x82;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x331 = x24 * x88;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x332 = x24 * x93;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x333 = x24 * x99;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x334 = x24 * x104;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x335 = x24 * x110;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x336 = x24 * x115;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x337 = x26 * x32;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x338 = x26 * x34;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x339 = x26 * x39;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x340 = x26 * x45;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x341 = x26 * x50;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x342 = x26 * x56;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x343 = x26 * x61;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x344 = x26 * x67;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x345 = x26 * x72;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x346 = x26 * x78;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x347 = x26 * x83;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x348 = x26 * x87;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x349 = x26 * x89;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x350 = x26 * x94;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x351 = x26 * x100;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x352 = x26 * x105;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x353 = x26 * x111;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x354 = x26 * x116;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x355 = x27 * x32;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x356 = x27 * x34;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x357 = x27 * x39;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x358 = x27 * x45;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x359 = x27 * x50;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x360 = x27 * x56;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x361 = x27 * x61;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x362 = x27 * x67;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x363 = x27 * x72;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x364 = x27 * x78;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x365 = x27 * x83;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x366 = x27 * x87;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x367 = x27 * x89;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x368 = x27 * x94;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x369 = x27 * x100;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x370 = x27 * x105;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x371 = x27 * x111;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x372 = x27 * x116;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x373 = x28 * x32;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x374 = x28 * x34;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x375 = x28 * x39;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x376 = x28 * x45;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x377 = x28 * x50;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x378 = x28 * x56;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x379 = x28 * x61;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x380 = x28 * x67;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x381 = x28 * x72;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x382 = x28 * x78;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x383 = x28 * x83;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x384 = x28 * x87;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x385 = x28 * x89;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x386 = x28 * x94;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x387 = x28 * x100;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x388 = x28 * x105;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x389 = x28 * x111;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x390 = x28 * x116;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x391 = x30 * x35;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x392 = x30 * x40;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x393 = x30 * x43;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x394 = x30 * x46;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x395 = x30 * x51;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x396 = x30 * x57;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x397 = x30 * x62;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x398 = x30 * x68;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x399 = x30 * x73;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x400 = x30 * x79;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x401 = x30 * x84;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x402 = x30 * x90;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x403 = x30 * x95;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x404 = x30 * x98;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x405 = x30 * x101;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x406 = x30 * x106;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x407 = x30 * x112;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x408 = x30 * x117;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x409 = x15 * x36;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x410 = x15 * x41;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x411 = x15 * x47;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x412 = x15 * x52;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x413 = x15 * x54;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x414 = x15 * x58;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x415 = x15 * x63;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x416 = x15 * x69;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x417 = x15 * x74;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x418 = x15 * x80;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x419 = x15 * x85;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x420 = x15 * x91;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x421 = x15 * x96;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x422 = x15 * x102;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x423 = x15 * x107;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x424 = x15 * x109;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x425 = x15 * x113;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x426 = x15 * x118;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x427 = x19 * x37;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x428 = x19 * x42;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x429 = x19 * x48;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x430 = x19 * x53;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x431 = x19 * x59;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x432 = x19 * x64;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x433 = x19 * x65;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x434 = x19 * x70;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x435 = x19 * x75;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x436 = x19 * x81;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x437 = x19 * x86;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x438 = x19 * x92;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x439 = x19 * x97;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x440 = x19 * x103;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x441 = x19 * x108;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x442 = x19 * x114;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x443 = x19 * x119;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x444 = x19 * x120;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x445 = x25 * x32;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x446 = x25 * x34;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x447 = x25 * x39;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x448 = x25 * x45;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x449 = x25 * x50;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x450 = x25 * x56;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x451 = x25 * x61;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x452 = x25 * x67;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x453 = x25 * x72;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x454 = x25 * x78;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x455 = x25 * x83;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x456 = x25 * x87;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x457 = x25 * x89;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x458 = x25 * x94;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x459 = x25 * x100;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x460 = x25 * x105;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x461 = x25 * x111;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x462 = x25 * x116;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x463 = x29 * x35;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x464 = x29 * x40;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x465 = x29 * x43;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x466 = x29 * x46;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x467 = x29 * x51;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x468 = x29 * x57;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x469 = x29 * x62;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x470 = x29 * x68;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x471 = x29 * x73;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x472 = x29 * x79;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x473 = x29 * x84;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x474 = x29 * x90;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x475 = x29 * x95;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x476 = x29 * x98;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x477 = x29 * x101;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x478 = x29 * x106;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x479 = x29 * x112;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x480 = x29 * x117;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x481 = x121 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x482 = x122 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x483 = x123 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x484 = x124 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x485 = x125 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x486 = x126 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x487 = x127 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x488 = x128 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x489 = x129 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x490 = x130 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x491 = x131 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x492 = x132 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x493 = x133 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x494 = x134 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x495 = x135 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x496 = x136 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x497 = x137 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x498 = x138 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x499 = x481 + x445;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x500 = x482 + x446;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x501 = x483 + x447;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x502 = x484 + x448;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x503 = x485 + x449;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x504 = x486 + x450;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x505 = x487 + x451;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x506 = x488 + x452;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x507 = x489 + x453;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x508 = x490 + x456;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x509 = x491 + x454;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x510 = x492 + x455;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x511 = x493 + x457;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x512 = x494 + x458;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x513 = x495 + x459;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x514 = x496 + x460;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x515 = x497 + x461;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x516 = x498 + x462;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x517 = x499 + x465;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x518 = x500 + x463;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x519 = x501 + x464;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x520 = x502 + x466;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x521 = x503 + x467;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x522 = x504 + x468;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x523 = x505 + x469;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x524 = x506 + x470;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x525 = x507 + x471;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x526 = x508 + x476;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x527 = x509 + x472;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x528 = x510 + x473;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x529 = x511 + x474;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x530 = x512 + x475;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x531 = x513 + x477;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x532 = x514 + x478;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x533 = x515 + x479;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x534 = x516 + x480;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x535 = x139 + x337;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x536 = x140 + x338;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x537 = x141 + x339;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x538 = x142 + x340;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x539 = x143 + x341;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x540 = x144 + x342;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x541 = x145 + x343;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x542 = x146 + x344;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x543 = x147 + x345;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x544 = x148 + x348;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x545 = x149 + x346;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x546 = x150 + x347;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x547 = x151 + x349;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x548 = x152 + x350;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x549 = x153 + x351;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x550 = x154 + x352;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x551 = x155 + x353;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x552 = x156 + x354;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x553 = x301 + x355;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x554 = x302 + x356;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x555 = x303 + x357;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x556 = x304 + x358;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x557 = x305 + x359;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x558 = x306 + x360;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x559 = x307 + x361;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x560 = x308 + x362;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x561 = x309 + x363;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x562 = x310 + x366;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x563 = x311 + x364;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x564 = x312 + x365;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x565 = x313 + x367;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x566 = x314 + x368;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x567 = x315 + x369;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x568 = x316 + x370;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x569 = x317 + x371;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x570 = x318 + x372;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x571 = x319 + x373;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x572 = x320 + x374;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x573 = x321 + x375;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x574 = x322 + x376;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x575 = x323 + x377;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x576 = x324 + x378;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x577 = x325 + x379;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x578 = x326 + x380;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x579 = x327 + x381;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x580 = x328 + x384;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x581 = x329 + x382;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x582 = x330 + x383;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x583 = x331 + x385;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x584 = x332 + x386;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x585 = x333 + x387;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x586 = x334 + x388;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x587 = x335 + x389;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x588 = x336 + x390;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x589 = x517 + x413;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x590 = x518 + x409;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x591 = x519 + x410;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x592 = x520 + x411;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x593 = x521 + x412;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x594 = x522 + x414;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x595 = x523 + x415;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x596 = x524 + x416;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x597 = x525 + x417;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x598 = x526 + x424;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x599 = x527 + x418;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x600 = x528 + x419;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x601 = x529 + x420;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x602 = x530 + x421;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x603 = x531 + x422;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x604 = x532 + x423;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x605 = x533 + x425;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x606 = x534 + x426;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x607 = x535 + x393;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x608 = x536 + x391;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x609 = x537 + x392;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x610 = x538 + x394;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x611 = x539 + x395;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x612 = x540 + x396;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x613 = x541 + x397;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x614 = x542 + x398;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x615 = x543 + x399;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x616 = x544 + x404;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x617 = x545 + x400;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x618 = x546 + x401;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x619 = x547 + x402;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x620 = x548 + x403;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x621 = x549 + x405;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x622 = x550 + x406;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x623 = x551 + x407;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x624 = x552 + x408;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x625 = x553 + x159;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x626 = x554 + x157;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x627 = x555 + x158;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x628 = x556 + x160;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x629 = x557 + x161;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x630 = x558 + x162;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x631 = x559 + x163;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x632 = x560 + x164;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x633 = x561 + x165;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x634 = x562 + x170;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x635 = x563 + x166;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x636 = x564 + x167;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x637 = x565 + x168;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x638 = x566 + x169;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x639 = x567 + x171;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x640 = x568 + x172;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x641 = x569 + x173;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x642 = x570 + x174;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x643 = x571 + x177;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x644 = x572 + x175;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x645 = x573 + x176;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x646 = x574 + x178;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x647 = x575 + x179;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x648 = x576 + x180;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x649 = x577 + x181;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x650 = x578 + x182;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x651 = x579 + x183;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x652 = x580 + x188;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x653 = x581 + x184;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x654 = x582 + x185;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x655 = x583 + x186;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x656 = x584 + x187;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x657 = x585 + x189;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x658 = x586 + x190;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x659 = x587 + x191;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x660 = x588 + x192;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x661 = x589 + x433;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x662 = x590 + x427;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x663 = x591 + x428;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x664 = x593 + x430;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x665 = x594 + x431;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x666 = x596 + x434;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x667 = x597 + x435;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x668 = x600 + x437;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x669 = x601 + x438;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x670 = x603 + x440;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x671 = x604 + x441;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x672 = x606 + x443;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x673 = x592 + x429;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x674 = x595 + x432;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x675 = x598 + x444;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x676 = x599 + x436;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x677 = x602 + x439;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x678 = x605 + x442;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x679 = x607 + x197;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x680 = x608 + x193;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x681 = x609 + x194;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x682 = x610 + x195;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x683 = x611 + x196;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x684 = x612 + x198;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x685 = x613 + x199;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x686 = x614 + x200;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x687 = x615 + x201;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x688 = x616 + x208;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x689 = x617 + x202;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x690 = x618 + x203;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x691 = x619 + x204;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x692 = x620 + x205;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x693 = x621 + x206;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x694 = x622 + x207;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x695 = x623 + x209;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x696 = x624 + x210;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x697 = x625 + x215;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x698 = x626 + x211;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x699 = x627 + x212;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x700 = x628 + x213;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x701 = x629 + x214;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x702 = x630 + x216;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x703 = x631 + x217;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x704 = x632 + x218;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x705 = x633 + x219;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x706 = x634 + x226;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x707 = x635 + x220;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x708 = x636 + x221;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x709 = x637 + x222;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x710 = x638 + x223;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x711 = x639 + x224;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x712 = x640 + x225;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x713 = x641 + x227;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x714 = x642 + x228;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x715 = x643 + x233;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x716 = x644 + x229;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x717 = x645 + x230;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x718 = x646 + x231;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x719 = x647 + x232;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x720 = x648 + x234;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x721 = x649 + x235;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x722 = x650 + x236;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x723 = x651 + x237;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x724 = x652 + x244;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x725 = x653 + x238;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x726 = x654 + x239;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x727 = x655 + x240;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x728 = x656 + x241;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x729 = x657 + x242;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x730 = x658 + x243;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x731 = x659 + x245;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x732 = x660 + x246;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x733 = x679 + x253;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x734 = x680 + x247;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x735 = x681 + x248;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x736 = x683 + x250;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x737 = x684 + x251;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x738 = x686 + x254;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x739 = x687 + x255;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x740 = x690 + x257;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x741 = x691 + x258;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x742 = x693 + x260;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x743 = x694 + x261;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x744 = x696 + x263;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x745 = x697 + x271;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x746 = x698 + x265;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x747 = x699 + x266;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x748 = x701 + x268;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x749 = x702 + x269;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x750 = x704 + x272;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x751 = x705 + x273;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x752 = x708 + x275;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x753 = x709 + x276;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x754 = x711 + x278;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x755 = x712 + x279;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x756 = x714 + x281;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x757 = x715 + x289;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x758 = x716 + x283;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x759 = x717 + x284;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x760 = x719 + x286;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x761 = x720 + x287;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x762 = x722 + x290;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x763 = x723 + x291;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x764 = x726 + x293;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x765 = x727 + x294;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x766 = x729 + x296;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x767 = x730 + x297;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x768 = x732 + x299;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x769 = x682 + x249;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x770 = x685 + x252;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x771 = x688 + x264;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x772 = x689 + x256;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x773 = x692 + x259;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x774 = x695 + x262;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x775 = x700 + x267;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x776 = x703 + x270;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x777 = x706 + x282;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x778 = x707 + x274;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x779 = x710 + x277;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x780 = x713 + x280;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x781 = x718 + x285;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x782 = x721 + x288;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x783 = x724 + x300;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x784 = x725 + x292;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x785 = x728 + x295;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x786 = x731 + x298;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x787 = x769 * x760;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x788 = x770 * x762;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x789 = x771 * x758;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x790 = x772 * x764;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x791 = x773 * x766;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x792 = x774 * x768;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x793 = x769 * x736;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x794 = x769 * x748;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x795 = x769 * x664;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x796 = x770 * x738;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x797 = x770 * x750;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x798 = x770 * x666;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x799 = x771 * x734;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x800 = x771 * x746;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x801 = x771 * x662;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x802 = x772 * x740;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x803 = x772 * x752;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x804 = x772 * x668;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x805 = x773 * x742;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x806 = x773 * x754;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x807 = x773 * x670;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x808 = x774 * x744;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x809 = x774 * x756;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x810 = x774 * x672;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x811 = x775 * x760;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x812 = x776 * x762;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x813 = x777 * x758;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x814 = x778 * x764;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x815 = x779 * x766;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x816 = x780 * x768;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x817 = x781 * x760;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x818 = x782 * x762;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x819 = x783 * x758;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x820 = x784 * x764;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x821 = x785 * x766;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x822 = x786 * x768;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x823 = x673 * x736;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x824 = x673 * x748;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x825 = x673 * x760;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x826 = x673 * x664;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x827 = x674 * x738;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x828 = x674 * x750;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x829 = x674 * x762;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x830 = x674 * x666;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x831 = x675 * x734;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x832 = x675 * x746;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x833 = x675 * x758;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x834 = x675 * x662;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x835 = x676 * x740;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x836 = x676 * x752;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x837 = x676 * x764;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x838 = x676 * x668;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x839 = x677 * x742;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x840 = x677 * x754;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x841 = x677 * x766;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x842 = x677 * x670;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x843 = x678 * x744;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x844 = x678 * x756;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x845 = x678 * x768;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x846 = x678 * x672;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x847 = x775 * x736;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x848 = x775 * x748;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x849 = x775 * x664;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x850 = x776 * x738;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x851 = x776 * x750;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x852 = x776 * x666;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x853 = x777 * x734;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x854 = x777 * x746;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x855 = x777 * x662;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x856 = x778 * x740;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x857 = x778 * x752;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x858 = x778 * x668;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x859 = x779 * x742;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x860 = x779 * x754;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x861 = x779 * x670;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x862 = x780 * x744;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x863 = x780 * x756;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x864 = x780 * x672;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x865 = x781 * x736;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x866 = x781 * x748;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x867 = x781 * x664;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x868 = x782 * x738;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x869 = x782 * x750;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x870 = x782 * x666;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x871 = x783 * x734;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x872 = x783 * x746;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x873 = x783 * x662;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x874 = x784 * x740;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x875 = x784 * x752;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x876 = x784 * x668;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x877 = x785 * x742;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x878 = x785 * x754;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x879 = x785 * x670;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x880 = x786 * x744;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x881 = x786 * x756;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x882 = x786 * x672;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x883 = x817 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x884 = x818 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x885 = x819 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x886 = x820 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x887 = x821 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x888 = x822 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x889 = x811 + x866;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x890 = x812 + x869;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x891 = x813 + x872;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x892 = x814 + x875;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x893 = x815 + x878;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x894 = x816 + x881;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x895 = x787 + x848;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x896 = x788 + x851;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x897 = x789 + x854;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x898 = x790 + x857;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x899 = x791 + x860;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x900 = x792 + x863;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x901 = x823 + x795;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x902 = x824 + x793;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x903 = x825 + x794;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x904 = x827 + x798;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x905 = x828 + x796;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x906 = x829 + x797;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x907 = x831 + x801;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x908 = x832 + x799;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x909 = x833 + x800;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x910 = x835 + x804;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x911 = x836 + x802;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x912 = x837 + x803;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x913 = x839 + x807;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x914 = x840 + x805;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x915 = x841 + x806;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x916 = x843 + x810;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x917 = x844 + x808;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x918 = x845 + x809;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x919 = x889 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x920 = x890 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x921 = x891 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x922 = x892 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x923 = x893 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x924 = x894 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x925 = x895 + x865;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x926 = x896 + x868;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x927 = x897 + x871;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x928 = x898 + x874;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x929 = x899 + x877;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x930 = x900 + x880;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x931 = x901 + x919;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x932 = x902 + x849;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x933 = x903 + x847;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x934 = x904 + x920;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x935 = x905 + x852;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x936 = x906 + x850;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x937 = x907 + x921;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x938 = x908 + x855;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x939 = x909 + x853;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x940 = x910 + x922;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x941 = x911 + x858;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x942 = x912 + x856;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x943 = x913 + x923;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x944 = x914 + x861;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x945 = x915 + x859;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x946 = x916 + x924;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x947 = x917 + x864;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x948 = x918 + x862;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x949 = x931 * x761;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x950 = x934 * x763;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x951 = x937 * x759;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x952 = x940 * x765;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x953 = x943 * x767;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x954 = x946 * x757;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x955 = x925 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x956 = x926 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x957 = x927 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x958 = x928 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x959 = x929 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x960 = x930 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x961 = x931 * x737;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x962 = x931 * x749;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x963 = x931 * x665;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x964 = x934 * x739;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x965 = x934 * x751;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x966 = x934 * x667;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x967 = x937 * x735;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x968 = x937 * x747;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x969 = x937 * x663;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x970 = x940 * x741;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x971 = x940 * x753;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x972 = x940 * x669;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x973 = x943 * x743;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x974 = x943 * x755;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x975 = x943 * x671;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x976 = x946 * x733;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x977 = x946 * x745;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x978 = x946 * x661;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x979 = x932 + x883;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x980 = x933 + x867;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x981 = x935 + x884;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x982 = x936 + x870;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x983 = x938 + x885;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x984 = x939 + x873;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x985 = x941 + x886;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x986 = x942 + x876;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x987 = x944 + x887;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x988 = x945 + x879;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x989 = x947 + x888;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x990 = x948 + x882;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x991 = x826 + x955;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x992 = x830 + x956;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x993 = x834 + x957;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x994 = x838 + x958;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x995 = x842 + x959;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x996 = x846 + x960;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x997 = x979 * x761;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x998 = x980 * x761;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x999 = x981 * x763;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1000 = x982 * x763;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1001 = x983 * x759;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1002 = x984 * x759;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1003 = x985 * x765;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1004 = x986 * x765;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1005 = x987 * x767;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1006 = x988 * x767;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1007 = x989 * x757;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1008 = x990 * x757;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1009 = x991 * x737;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1010 = x991 * x749;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1011 = x991 * x761;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1012 = x991 * x665;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1013 = x992 * x739;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1014 = x992 * x751;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1015 = x992 * x763;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1016 = x992 * x667;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1017 = x993 * x735;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1018 = x993 * x747;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1019 = x993 * x759;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1020 = x993 * x663;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1021 = x994 * x741;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1022 = x994 * x753;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1023 = x994 * x765;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1024 = x994 * x669;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1025 = x995 * x743;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1026 = x995 * x755;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1027 = x995 * x767;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1028 = x995 * x671;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1029 = x996 * x733;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1030 = x996 * x745;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1031 = x996 * x757;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1032 = x996 * x661;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1033 = x979 * x737;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1034 = x979 * x749;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1035 = x979 * x665;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1036 = x980 * x737;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1037 = x980 * x749;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1038 = x980 * x665;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1039 = x981 * x739;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1040 = x981 * x751;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1041 = x981 * x667;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1042 = x982 * x739;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1043 = x982 * x751;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1044 = x982 * x667;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1045 = x983 * x735;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1046 = x983 * x747;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1047 = x983 * x663;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1048 = x984 * x735;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1049 = x984 * x747;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1050 = x984 * x663;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1051 = x985 * x741;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1052 = x985 * x753;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1053 = x985 * x669;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1054 = x986 * x741;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1055 = x986 * x753;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1056 = x986 * x669;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1057 = x987 * x743;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1058 = x987 * x755;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1059 = x987 * x671;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1060 = x988 * x743;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1061 = x988 * x755;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1062 = x988 * x671;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1063 = x989 * x733;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1064 = x989 * x745;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1065 = x989 * x661;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1066 = x990 * x733;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1067 = x990 * x745;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1068 = x990 * x661;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1069 = x998 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1070 = x1000 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1071 = x1002 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1072 = x1004 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1073 = x1006 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1074 = x1008 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1075 = x997 + x1037;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1076 = x999 + x1043;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1077 = x1001 + x1049;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1078 = x1003 + x1055;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1079 = x1005 + x1061;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1080 = x1007 + x1067;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1081 = x949 + x1034;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1082 = x950 + x1040;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1083 = x951 + x1046;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1084 = x952 + x1052;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1085 = x953 + x1058;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1086 = x954 + x1064;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1087 = x1009 + x963;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1088 = x1010 + x961;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1089 = x1011 + x962;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1090 = x1013 + x966;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1091 = x1014 + x964;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1092 = x1015 + x965;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1093 = x1017 + x969;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1094 = x1018 + x967;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1095 = x1019 + x968;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1096 = x1021 + x972;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1097 = x1022 + x970;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1098 = x1023 + x971;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1099 = x1025 + x975;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1100 = x1026 + x973;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1101 = x1027 + x974;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1102 = x1029 + x978;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1103 = x1030 + x976;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1104 = x1031 + x977;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1105 = x1075 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1106 = x1076 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1107 = x1077 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1108 = x1078 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1109 = x1079 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1110 = x1080 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1111 = x1081 + x1036;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1112 = x1082 + x1042;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1113 = x1083 + x1048;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1114 = x1084 + x1054;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1115 = x1085 + x1060;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1116 = x1086 + x1066;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1117 = x1088 + x1035;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1118 = x1089 + x1033;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1119 = x1091 + x1041;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1120 = x1092 + x1039;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1121 = x1093 + x1107;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1122 = x1094 + x1047;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1123 = x1095 + x1045;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1124 = x1097 + x1053;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1125 = x1098 + x1051;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1126 = x1100 + x1059;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1127 = x1101 + x1057;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1128 = x1103 + x1065;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1129 = x1104 + x1063;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1130 = x1096 + x1108;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1131 = x1099 + x1109;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1132 = x1102 + x1110;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1133 = x1124 + x1072;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1134 = x1125 + x1056;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1135 = x1126 + x1073;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1136 = x1127 + x1062;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1137 = x1128 + x1074;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1138 = x1129 + x1068;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1139 = x1117 + x1069;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1140 = x1118 + x1038;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1141 = x1119 + x1070;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1142 = x1120 + x1044;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1143 = x1087 + x1105;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1144 = x1090 + x1106;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1145 = x1133 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1146 = x1134 * x1134;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1147 = x1134 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1148 = x1135 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1149 = x1136 * x1136;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1150 = x1136 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1151 = x1137 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1152 = x1138 * x1138;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1153 = x1138 * x1;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1154 = x1111 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1155 = x1112 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1156 = x1113 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1157 = x1114 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1158 = x1115 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1159 = x1116 * x0;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1160 = x1130 * x1130;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1161 = x1131 * x1131;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1162 = x1132 * x1132;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1163 = x1133 * x1133;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1164 = x1135 * x1135;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1165 = x1137 * x1137;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1166 = x1146 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1167 = x1149 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1168 = x1152 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1169 = -x1130;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1170 = -x1131;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1171 = -x1132;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1172 = x1122 + x1071;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1173 = x1123 + x1050;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1174 = x1020 + x1156;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1175 = x1133 + x1133;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1176 = x1134 + x1134;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1177 = x1135 + x1135;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1178 = x1136 + x1136;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1179 = x1137 + x1137;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1180 = x1138 + x1138;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1181 = x1024 + x1157;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1182 = x1028 + x1158;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1183 = x1032 + x1159;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1184 = x1012 + x1154;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x1185 = x1016 + x1155;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1186 = x1130 * x1176;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1187 = x1131 * x1178;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1188 = x1132 * x1180;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1189 = x1181 * x1175;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1190 = x1181 * x1181;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1191 = x1182 * x1177;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1192 = x1182 * x1182;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1193 = x1183 * x1179;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1194 = x1183 * x1183;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1195 = -x1181;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1196 = -x1182;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1197 = -x1183;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1198 = x1186 - x1163;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1199 = x1187 - x1164;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1200 = x1188 - x1165;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1201 = x1189 - x1160;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1202 = x1191 - x1161;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1203 = x1193 - x1162;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1204 = x1201 + x1166;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1205 = x1202 + x1167;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1206 = x1203 + x1168;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1207 = x1204 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1208 = x1205 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1209 = x1206 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1210 = x1207 * x1204;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1211 = x1208 * x1205;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1212 = x1209 * x1206;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1213 = x1198 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1214 = x1199 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1215 = x1200 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1216 = x1190 + x1213;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1217 = x1192 + x1214;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1218 = x1194 + x1215;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1219 = x1216 * x1216;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1220 = x1217 * x1217;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1221 = x1218 * x1218;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1222 = x1219 + x1210;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1223 = x1220 + x1211;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1224 = x1221 + x1212;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1225 = inv(x1222);
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1226 = inv(x1223);
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1227 = inv(x1224);
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1228 = x1216 * x1225;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1229 = x1217 * x1226;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1230 = x1218 * x1227;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1231 = x1204 * x1225;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1232 = x1205 * x1226;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1233 = x1206 * x1227;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1234 = x1130 * x1231;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1235 = x1131 * x1232;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1236 = x1132 * x1233;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1237 = x1181 * x1228;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1238 = x1182 * x1229;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1239 = x1183 * x1230;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1240 = x1169 * x1228;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1241 = x1170 * x1229;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1242 = x1171 * x1230;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1243 = x1195 * x1231;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1244 = x1196 * x1232;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1245 = x1197 * x1233;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1246 = x1133 * x1228;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1247 = x1134 * x1228;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1248 = x1135 * x1229;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1249 = x1136 * x1229;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1250 = x1137 * x1230;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1251 = x1138 * x1230;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1252 = x1145 * x1231;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1253 = x1147 * x1231;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1254 = x1148 * x1232;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1255 = x1150 * x1232;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1256 = x1151 * x1233;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1257 = x1153 * x1233;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1258 = x1234 - x1247;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1259 = x1235 - x1249;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1260 = x1236 - x1251;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1261 = x1240 - x1253;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1262 = x1241 - x1255;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1263 = x1242 - x1257;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1264 = x1237 + x1252;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1265 = x1238 + x1254;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1266 = x1239 + x1256;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1267 = x1243 + x1246;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1268 = x1244 + x1248;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x1269 = x1245 + x1250;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1270 = x1172 * x1258;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1271 = x1173 * x1258;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1272 = x1121 * x1258;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1273 = x1174 * x1264;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1274 = x1174 * x1267;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1275 = x1174 * x1258;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1276 = x1174 * x1261;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1277 = x1172 * x1264;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1278 = x1172 * x1267;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1279 = x1172 * x1261;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1280 = x1173 * x1264;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1281 = x1173 * x1267;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1282 = x1173 * x1261;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1283 = x1121 * x1264;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1284 = x1121 * x1267;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1285 = x1121 * x1261;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1286 = x1271 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1287 = x1270 + x1281;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1288 = x1272 + x1278;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1289 = x1274 + x1285;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1290 = x1275 + x1284;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1291 = x1276 + x1283;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1292 = x1287 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1293 = x1288 + x1282;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1294 = x1289 + x1277;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1295 = x1290 + x1279;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1296 = x1291 + x1292;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1297 = x1296 * x1140;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1298 = x1293 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1299 = x1296 * x1139;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1300 = x1296 * x1143;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1301 = x1296 * x1184;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1302 = x1294 + x1286;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1303 = x1295 + x1280;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1304 = x1273 + x1298;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1305 = x1302 * x1140;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1306 = x1303 * x1140;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1307 = x1304 * x1139;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1308 = x1304 * x1140;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1309 = x1304 * x1143;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1310 = x1304 * x1184;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1311 = x1302 * x1139;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1312 = x1302 * x1143;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1313 = x1302 * x1184;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1314 = x1303 * x1139;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1315 = x1303 * x1143;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1316 = x1303 * x1184;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1317 = x1306 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1318 = x1305 + x1314;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1319 = x1297 + x1311;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1320 = x1307 + x1300;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1321 = x1308 + x1299;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1322 = x1309 + x1301;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1323 = x1318 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1324 = x1319 + x1315;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1325 = x1320 + x1313;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1326 = x1321 + x1312;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1327 = x1322 + x1323;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1328 = x1327 * x1259;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1329 = x1324 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1330 = x1327 * x1265;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1331 = x1327 * x1268;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1332 = x1327 * x1262;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1333 = x1325 + x1317;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1334 = x1326 + x1316;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1335 = x1310 + x1329;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1336 = x1333 * x1259;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1337 = x1334 * x1259;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1338 = x1335 * x1265;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1339 = x1335 * x1268;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1340 = x1335 * x1259;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1341 = x1335 * x1262;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1342 = x1333 * x1265;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1343 = x1333 * x1268;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1344 = x1333 * x1262;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1345 = x1334 * x1265;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1346 = x1334 * x1268;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1347 = x1334 * x1262;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1348 = x1337 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1349 = x1336 + x1346;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1350 = x1328 + x1343;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1351 = x1339 + x1332;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1352 = x1340 + x1331;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1353 = x1341 + x1330;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1354 = x1349 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1355 = x1350 + x1347;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1356 = x1351 + x1342;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1357 = x1352 + x1344;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1358 = x1353 + x1354;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1359 = x1358 * x1142;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1360 = x1355 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1361 = x1358 * x1141;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1362 = x1358 * x1144;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1363 = x1358 * x1185;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1364 = x1356 + x1348;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1365 = x1357 + x1345;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1366 = x1338 + x1360;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1367 = x1364 * x1142;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1368 = x1365 * x1142;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1369 = x1366 * x1141;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1370 = x1366 * x1142;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1371 = x1366 * x1144;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1372 = x1366 * x1185;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1373 = x1364 * x1141;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1374 = x1364 * x1144;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1375 = x1364 * x1185;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1376 = x1365 * x1141;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1377 = x1365 * x1144;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1378 = x1365 * x1185;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1379 = x1368 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1380 = x1367 + x1376;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1381 = x1359 + x1373;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1382 = x1369 + x1362;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1383 = x1370 + x1361;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1384 = x1371 + x1363;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1385 = x1380 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1386 = x1381 + x1377;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1387 = x1382 + x1375;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1388 = x1383 + x1374;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1389 = x1384 + x1385;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1390 = x1389 * x1260;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1391 = x1386 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1392 = x1389 * x1266;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1393 = x1389 * x1269;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1394 = x1389 * x1263;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1395 = x1387 + x1379;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1396 = x1388 + x1378;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1397 = x1372 + x1391;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1398 = x1395 * x1260;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1399 = x1396 * x1260;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1400 = x1397 * x1266;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1401 = x1397 * x1269;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1402 = x1397 * x1260;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1403 = x1397 * x1263;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1404 = x1395 * x1266;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1405 = x1395 * x1269;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1406 = x1395 * x1263;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1407 = x1396 * x1266;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1408 = x1396 * x1269;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1409 = x1396 * x1263;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1410 = x1399 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1411 = x1398 + x1408;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1412 = x1390 + x1405;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1413 = x1401 + x1394;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1414 = x1402 + x1393;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1415 = x1403 + x1392;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1416 = x1411 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1417 = x1412 + x1409;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1418 = x1413 + x1404;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1419 = x1414 + x1406;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1420 = x1415 + x1416;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1421 = x1418 + x1410;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1422 = x1419 + x1407;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1423 = x1417 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x1424 = x1400 + x1423;
      extern_args[0] = x1424;
      extern_args[1] = x1420;
      extern_args[2] = x1421;
      extern_args[3] = x1422;
      extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
    }
  }
  if (x5 != 0) {
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x1425 = arg0[11 * steps + ((cycle - 0) & mask)];
    assert(x1425 != Fp::invalid());
    if (x1425 != 0) {
      {
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1426 = arg3[0];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1427 = arg3[1];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1428 = arg3[10];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1429 = arg3[11];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1430 = arg3[12];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1431 = arg3[13];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1432 = arg3[14];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1433 = arg3[15];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1434 = arg3[16];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1435 = arg3[17];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1436 = arg3[18];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1437 = arg3[19];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1438 = arg3[2];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1439 = arg3[3];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1440 = arg3[4];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1441 = arg3[5];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1442 = arg3[6];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1443 = arg3[7];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1444 = arg3[8];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1445 = arg3[9];
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1446 = arg2[0 * steps + ((cycle - 0) & mask)];
        assert(x1446 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1447 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x1447 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1448 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x1448 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1449 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x1449 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1450 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x1450 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1451 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x1451 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1452 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x1452 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1453 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x1453 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1454 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x1454 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1455 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x1455 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1456 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x1456 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1457 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x1457 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1458 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x1458 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1459 = arg2[21 * steps + ((cycle - 0) & mask)];
        assert(x1459 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1460 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x1460 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1461 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x1461 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1462 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x1462 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1463 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x1463 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1464 = arg2[26 * steps + ((cycle - 0) & mask)];
        assert(x1464 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1465 = arg2[27 * steps + ((cycle - 0) & mask)];
        assert(x1465 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1466 = arg2[28 * steps + ((cycle - 0) & mask)];
        assert(x1466 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1467 = arg2[29 * steps + ((cycle - 0) & mask)];
        assert(x1467 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1468 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x1468 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1469 = arg2[30 * steps + ((cycle - 0) & mask)];
        assert(x1469 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1470 = arg2[31 * steps + ((cycle - 0) & mask)];
        assert(x1470 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1471 = arg2[32 * steps + ((cycle - 0) & mask)];
        assert(x1471 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1472 = arg2[33 * steps + ((cycle - 0) & mask)];
        assert(x1472 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1473 = arg2[34 * steps + ((cycle - 0) & mask)];
        assert(x1473 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_and_elem(recursion::BitAndElem)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1474 = arg2[35 * steps + ((cycle - 0) & mask)];
        assert(x1474 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1475 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x1475 != Fp::invalid());
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1476 = x1426 * x1446;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1477 = x1426 * x1448;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1478 = x1426 * x1453;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1479 = x1426 * x1459;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1480 = x1426 * x1464;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1481 = x1426 * x1470;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1482 = x1427 * x1446;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1483 = x1427 * x1448;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1484 = x1427 * x1453;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1485 = x1427 * x1459;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1486 = x1427 * x1464;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1487 = x1427 * x1470;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1488 = x1428 * x1450;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1489 = x1428 * x1455;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1490 = x1428 * x1457;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1491 = x1428 * x1461;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1492 = x1428 * x1466;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1493 = x1428 * x1472;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1494 = x1429 * x1450;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1495 = x1429 * x1455;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1496 = x1429 * x1457;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1497 = x1429 * x1461;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1498 = x1429 * x1466;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1499 = x1429 * x1472;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1500 = x1431 * x1451;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1501 = x1431 * x1456;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1502 = x1431 * x1462;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1503 = x1431 * x1467;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1504 = x1431 * x1468;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1505 = x1431 * x1473;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1506 = x1432 * x1451;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1507 = x1432 * x1456;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1508 = x1432 * x1462;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1509 = x1432 * x1467;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1510 = x1432 * x1468;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1511 = x1432 * x1473;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1512 = x1433 * x1451;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1513 = x1433 * x1456;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1514 = x1433 * x1462;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1515 = x1433 * x1467;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1516 = x1433 * x1468;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1517 = x1433 * x1473;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1518 = x1435 * x1452;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1519 = x1435 * x1458;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1520 = x1435 * x1463;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1521 = x1435 * x1469;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1522 = x1435 * x1474;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1523 = x1435 * x1475;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1524 = x1436 * x1452;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1525 = x1436 * x1458;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1526 = x1436 * x1463;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1527 = x1436 * x1469;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1528 = x1436 * x1474;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1529 = x1436 * x1475;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1530 = x1437 * x1452;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1531 = x1437 * x1458;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1532 = x1437 * x1463;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1533 = x1437 * x1469;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1534 = x1437 * x1474;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1535 = x1437 * x1475;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1536 = x1438 * x1446;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1537 = x1438 * x1448;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1538 = x1438 * x1453;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1539 = x1438 * x1459;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1540 = x1438 * x1464;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1541 = x1438 * x1470;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1542 = x1439 * x1446;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1543 = x1439 * x1448;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1544 = x1439 * x1453;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1545 = x1439 * x1459;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1546 = x1439 * x1464;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1547 = x1439 * x1470;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1548 = x1441 * x1447;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1549 = x1441 * x1449;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1550 = x1441 * x1454;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1551 = x1441 * x1460;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1552 = x1441 * x1465;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1553 = x1441 * x1471;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1554 = x1442 * x1447;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1555 = x1442 * x1449;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1556 = x1442 * x1454;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1557 = x1442 * x1460;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1558 = x1442 * x1465;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1559 = x1442 * x1471;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1560 = x1443 * x1447;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1561 = x1443 * x1449;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1562 = x1443 * x1454;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1563 = x1443 * x1460;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1564 = x1443 * x1465;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1565 = x1443 * x1471;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1566 = x1445 * x1450;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1567 = x1445 * x1455;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1568 = x1445 * x1457;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1569 = x1445 * x1461;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1570 = x1445 * x1466;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1571 = x1445 * x1472;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1572 = x1430 * x1451;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1573 = x1430 * x1456;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1574 = x1430 * x1462;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1575 = x1430 * x1467;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1576 = x1430 * x1468;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1577 = x1430 * x1473;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1578 = x1434 * x1452;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1579 = x1434 * x1458;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1580 = x1434 * x1463;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1581 = x1434 * x1469;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1582 = x1434 * x1474;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1583 = x1434 * x1475;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1584 = x1440 * x1447;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1585 = x1440 * x1449;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1586 = x1440 * x1454;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1587 = x1440 * x1460;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1588 = x1440 * x1465;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1589 = x1440 * x1471;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1590 = x1444 * x1450;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1591 = x1444 * x1455;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1592 = x1444 * x1457;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1593 = x1444 * x1461;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1594 = x1444 * x1466;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1595 = x1444 * x1472;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1596 = x1476 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1597 = x1477 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1598 = x1478 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1599 = x1479 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1600 = x1480 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1601 = x1481 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1602 = x1596 + x1584;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1603 = x1597 + x1585;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1604 = x1598 + x1586;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1605 = x1599 + x1587;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1606 = x1600 + x1588;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1607 = x1601 + x1589;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1608 = x1602 + x1592;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1609 = x1603 + x1590;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1610 = x1604 + x1591;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1611 = x1605 + x1593;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1612 = x1606 + x1594;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1613 = x1607 + x1595;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1614 = x1482 + x1548;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1615 = x1483 + x1549;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1616 = x1484 + x1550;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1617 = x1485 + x1551;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1618 = x1486 + x1552;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1619 = x1487 + x1553;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1620 = x1536 + x1554;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1621 = x1537 + x1555;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1622 = x1538 + x1556;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1623 = x1539 + x1557;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1624 = x1540 + x1558;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1625 = x1541 + x1559;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1626 = x1542 + x1560;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1627 = x1543 + x1561;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1628 = x1544 + x1562;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1629 = x1545 + x1563;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1630 = x1546 + x1564;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1631 = x1547 + x1565;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1632 = x1608 + x1576;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1633 = x1609 + x1572;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1634 = x1610 + x1573;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1635 = x1611 + x1574;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1636 = x1612 + x1575;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1637 = x1613 + x1577;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1638 = x1614 + x1568;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1639 = x1615 + x1566;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1640 = x1616 + x1567;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1641 = x1617 + x1569;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1642 = x1618 + x1570;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1643 = x1619 + x1571;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1644 = x1620 + x1490;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1645 = x1621 + x1488;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1646 = x1622 + x1489;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1647 = x1623 + x1491;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1648 = x1624 + x1492;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1649 = x1625 + x1493;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1650 = x1626 + x1496;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1651 = x1627 + x1494;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1652 = x1628 + x1495;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1653 = x1629 + x1497;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1654 = x1630 + x1498;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1655 = x1631 + x1499;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1656 = x1634 + x1579;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1657 = x1637 + x1582;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1658 = x1632 + x1583;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1659 = x1633 + x1578;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1660 = x1635 + x1580;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1661 = x1636 + x1581;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1662 = x1638 + x1504;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1663 = x1639 + x1500;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1664 = x1640 + x1501;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1665 = x1641 + x1502;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1666 = x1642 + x1503;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1667 = x1643 + x1505;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1668 = x1644 + x1510;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1669 = x1645 + x1506;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1670 = x1646 + x1507;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1671 = x1647 + x1508;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1672 = x1648 + x1509;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1673 = x1649 + x1511;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1674 = x1650 + x1516;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1675 = x1651 + x1512;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1676 = x1652 + x1513;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1677 = x1653 + x1514;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1678 = x1654 + x1515;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1679 = x1655 + x1517;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1680 = x1664 + x1519;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1681 = x1667 + x1522;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1682 = x1670 + x1525;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1683 = x1673 + x1528;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1684 = x1676 + x1531;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1685 = x1679 + x1534;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1686 = x1662 + x1523;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1687 = x1663 + x1518;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1688 = x1665 + x1520;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1689 = x1666 + x1521;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1690 = x1668 + x1529;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1691 = x1669 + x1524;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1692 = x1671 + x1526;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1693 = x1672 + x1527;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1694 = x1674 + x1535;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1695 = x1675 + x1530;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1696 = x1677 + x1532;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x1697 = x1678 + x1533;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1698 = x1687 * x1684;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1699 = x1689 * x1685;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1700 = x1690 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1701 = x1694 * x1694;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1702 = x1694 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1703 = x1687 * x1680;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1704 = x1687 * x1682;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1705 = x1687 * x1656;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1706 = x1689 * x1681;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1707 = x1689 * x1683;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1708 = x1689 * x1657;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1709 = x1686 * x1686;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1710 = x1690 * x1690;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1711 = x1701 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1712 = -x1686;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1713 = x1690 + x1690;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1714 = x1694 + x1694;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1715 = x1691 * x1684;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1716 = x1693 * x1685;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1717 = x1695 * x1684;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1718 = x1697 * x1685;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1719 = x1659 * x1680;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1720 = x1659 * x1682;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1721 = x1659 * x1684;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1722 = x1659 * x1656;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1723 = x1661 * x1681;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1724 = x1661 * x1683;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1725 = x1661 * x1685;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1726 = x1661 * x1657;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1727 = x1686 * x1714;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1728 = x1658 * x1713;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1729 = x1658 * x1658;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1730 = x1691 * x1680;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1731 = x1691 * x1682;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1732 = x1691 * x1656;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1733 = x1693 * x1681;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1734 = x1693 * x1683;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1735 = x1693 * x1657;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1736 = x1695 * x1680;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1737 = x1695 * x1682;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1738 = x1695 * x1656;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1739 = x1697 * x1681;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1740 = x1697 * x1683;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1741 = x1697 * x1657;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1742 = x1717 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1743 = x1718 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1744 = -x1658;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1745 = x1727 - x1710;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1746 = x1728 - x1709;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1747 = x1715 + x1737;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1748 = x1716 + x1740;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1749 = x1698 + x1731;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1750 = x1699 + x1734;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1751 = x1719 + x1705;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1752 = x1720 + x1703;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1753 = x1721 + x1704;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1754 = x1723 + x1708;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1755 = x1724 + x1706;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1756 = x1725 + x1707;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1757 = x1746 + x1711;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1758 = x1757 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1759 = x1747 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1760 = x1748 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1761 = x1758 * x1757;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1762 = x1745 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1763 = x1749 + x1736;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1764 = x1750 + x1739;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1765 = x1751 + x1759;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1766 = x1752 + x1732;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1767 = x1753 + x1730;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1768 = x1755 + x1735;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1769 = x1756 + x1733;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1770 = x1754 + x1760;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1771 = x1729 + x1762;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1772 = x1768 + x1743;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1773 = x1769 + x1741;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1774 = x1771 * x1771;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1775 = x1772 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1776 = x1773 * x1773;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1777 = x1773 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1778 = x1763 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1779 = x1764 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1780 = x1770 * x1770;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1781 = x1772 * x1772;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1782 = x1776 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1783 = -x1770;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1784 = x1766 + x1742;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1785 = x1767 + x1738;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1786 = x1722 + x1778;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1787 = x1774 + x1761;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1788 = x1772 + x1772;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1789 = x1773 + x1773;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x1790 = x1726 + x1779;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1791 = inv(x1787);
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1792 = x1770 * x1789;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1793 = x1790 * x1788;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1794 = x1790 * x1790;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1795 = x1771 * x1791;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1796 = x1757 * x1791;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1797 = -x1790;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1798 = x1792 - x1781;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1799 = x1793 - x1780;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1800 = x1799 + x1782;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1801 = x1686 * x1796;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1802 = x1658 * x1795;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1803 = x1800 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1804 = x1712 * x1795;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1805 = x1744 * x1796;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1806 = x1690 * x1795;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1807 = x1694 * x1795;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1808 = x1803 * x1800;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1809 = x1700 * x1796;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1810 = x1702 * x1796;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1811 = x1798 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1812 = x1801 - x1807;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1813 = x1804 - x1810;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1814 = x1794 + x1811;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1815 = x1802 + x1809;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1816 = x1805 + x1806;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1817 = x1814 * x1814;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1818 = x1817 + x1808;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1819 = inv(x1818);
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1820 = x1814 * x1819;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1821 = x1800 * x1819;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1822 = x1770 * x1821;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1823 = x1790 * x1820;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1824 = x1783 * x1820;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1825 = x1797 * x1821;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1826 = x1772 * x1820;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1827 = x1773 * x1820;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1828 = x1775 * x1821;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1829 = x1777 * x1821;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1830 = x1822 - x1827;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1831 = x1824 - x1829;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1832 = x1823 + x1828;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x1833 = x1825 + x1826;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1834 = x1784 * x1830;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1835 = x1785 * x1830;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1836 = x1765 * x1830;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1837 = x1786 * x1832;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1838 = x1786 * x1833;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1839 = x1786 * x1830;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1840 = x1786 * x1831;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1841 = x1784 * x1832;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1842 = x1784 * x1833;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1843 = x1784 * x1831;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1844 = x1785 * x1832;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1845 = x1785 * x1833;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1846 = x1785 * x1831;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1847 = x1765 * x1832;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1848 = x1765 * x1833;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1849 = x1765 * x1831;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1850 = x1835 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1851 = x1834 + x1845;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1852 = x1836 + x1842;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1853 = x1838 + x1849;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1854 = x1839 + x1848;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1855 = x1840 + x1847;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1856 = x1851 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1857 = x1852 + x1846;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1858 = x1853 + x1841;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1859 = x1854 + x1843;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1860 = x1855 + x1856;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1861 = x1860 * x1696;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1862 = x1857 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1863 = x1860 * x1692;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1864 = x1860 * x1688;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1865 = x1860 * x1660;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1866 = x1858 + x1850;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1867 = x1859 + x1844;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1868 = x1837 + x1862;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1869 = x1866 * x1696;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1870 = x1867 * x1696;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1871 = x1868 * x1692;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1872 = x1868 * x1696;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1873 = x1868 * x1688;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1874 = x1868 * x1660;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1875 = x1866 * x1692;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1876 = x1866 * x1688;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1877 = x1866 * x1660;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1878 = x1867 * x1692;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1879 = x1867 * x1688;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1880 = x1867 * x1660;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1881 = x1870 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1882 = x1869 + x1878;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1883 = x1861 + x1875;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1884 = x1871 + x1864;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1885 = x1872 + x1863;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1886 = x1873 + x1865;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1887 = x1882 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1888 = x1883 + x1879;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1889 = x1884 + x1877;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1890 = x1885 + x1876;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1891 = x1886 + x1887;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1892 = x1891 * x1812;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1893 = x1888 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1894 = x1891 * x1815;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1895 = x1891 * x1816;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1896 = x1891 * x1813;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1897 = x1889 + x1881;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1898 = x1890 + x1880;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1899 = x1874 + x1893;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1900 = x1897 * x1812;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1901 = x1898 * x1812;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1902 = x1899 * x1815;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1903 = x1899 * x1816;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1904 = x1899 * x1812;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1905 = x1899 * x1813;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1906 = x1897 * x1815;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1907 = x1897 * x1816;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1908 = x1897 * x1813;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1909 = x1898 * x1815;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1910 = x1898 * x1816;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1911 = x1898 * x1813;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1912 = x1901 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1913 = x1900 + x1910;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1914 = x1892 + x1907;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1915 = x1903 + x1896;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1916 = x1904 + x1895;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1917 = x1905 + x1894;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1918 = x1913 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1919 = x1914 + x1911;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1920 = x1915 + x1906;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1921 = x1916 + x1908;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1922 = x1917 + x1918;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1923 = x1920 + x1912;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1924 = x1921 + x1909;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1925 = x1919 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x1926 = x1902 + x1925;
        extern_args[0] = x1926;
        extern_args[1] = x1922;
        extern_args[2] = x1923;
        extern_args[3] = x1924;
        extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x1927 = arg0[12 * steps + ((cycle - 0) & mask)];
    assert(x1927 != Fp::invalid());
    if (x1927 != 0) {
      {
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1928 = arg3[0];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1929 = arg3[1];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1930 = arg3[10];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1931 = arg3[11];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1932 = arg3[12];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1933 = arg3[13];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1934 = arg3[14];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1935 = arg3[15];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1936 = arg3[16];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1937 = arg3[17];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1938 = arg3[18];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1939 = arg3[19];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1940 = arg3[2];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1941 = arg3[3];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1942 = arg3[4];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1943 = arg3[5];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1944 = arg3[6];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1945 = arg3[7];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1946 = arg3[8];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x1947 = arg3[9];
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1948 = arg2[0 * steps + ((cycle - 0) & mask)];
        assert(x1948 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1949 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x1949 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1950 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x1950 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1951 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x1951 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1952 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x1952 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1953 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x1953 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1954 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x1954 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1955 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x1955 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1956 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x1956 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1957 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x1957 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1958 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x1958 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1959 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x1959 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1960 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x1960 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1961 = arg2[21 * steps + ((cycle - 0) & mask)];
        assert(x1961 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1962 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x1962 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1963 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x1963 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1964 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x1964 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1965 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x1965 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1966 = arg2[26 * steps + ((cycle - 0) & mask)];
        assert(x1966 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1967 = arg2[27 * steps + ((cycle - 0) & mask)];
        assert(x1967 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1968 = arg2[28 * steps + ((cycle - 0) & mask)];
        assert(x1968 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1969 = arg2[29 * steps + ((cycle - 0) & mask)];
        assert(x1969 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1970 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x1970 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1971 = arg2[30 * steps + ((cycle - 0) & mask)];
        assert(x1971 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x1972 = arg2[31 * steps + ((cycle - 0) & mask)];
        assert(x1972 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1973 = arg2[32 * steps + ((cycle - 0) & mask)];
        assert(x1973 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1974 = arg2[33 * steps + ((cycle - 0) & mask)];
        assert(x1974 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1975 = arg2[34 * steps + ((cycle - 0) & mask)];
        assert(x1975 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/bit_op_shorts(recursion::BitOpShorts)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1976 = arg2[35 * steps + ((cycle - 0) & mask)];
        assert(x1976 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x1977 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x1977 != Fp::invalid());
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1978 = x1928 * x1948;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1979 = x1928 * x1950;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1980 = x1928 * x1955;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1981 = x1928 * x1961;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1982 = x1928 * x1966;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1983 = x1928 * x1972;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1984 = x1929 * x1948;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1985 = x1929 * x1950;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1986 = x1929 * x1955;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1987 = x1929 * x1961;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1988 = x1929 * x1966;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1989 = x1929 * x1972;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1990 = x1930 * x1952;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1991 = x1930 * x1957;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1992 = x1930 * x1959;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1993 = x1930 * x1963;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1994 = x1930 * x1968;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1995 = x1930 * x1974;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1996 = x1931 * x1952;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1997 = x1931 * x1957;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1998 = x1931 * x1959;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x1999 = x1931 * x1963;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2000 = x1931 * x1968;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2001 = x1931 * x1974;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2002 = x1933 * x1953;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2003 = x1933 * x1958;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2004 = x1933 * x1964;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2005 = x1933 * x1969;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2006 = x1933 * x1970;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2007 = x1933 * x1975;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2008 = x1934 * x1953;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2009 = x1934 * x1958;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2010 = x1934 * x1964;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2011 = x1934 * x1969;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2012 = x1934 * x1970;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2013 = x1934 * x1975;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2014 = x1935 * x1953;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2015 = x1935 * x1958;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2016 = x1935 * x1964;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2017 = x1935 * x1969;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2018 = x1935 * x1970;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2019 = x1935 * x1975;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2020 = x1937 * x1954;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2021 = x1937 * x1960;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2022 = x1937 * x1965;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2023 = x1937 * x1971;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2024 = x1937 * x1976;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2025 = x1937 * x1977;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2026 = x1938 * x1954;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2027 = x1938 * x1960;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2028 = x1938 * x1965;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2029 = x1938 * x1971;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2030 = x1938 * x1976;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2031 = x1938 * x1977;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2032 = x1939 * x1954;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2033 = x1939 * x1960;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2034 = x1939 * x1965;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2035 = x1939 * x1971;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2036 = x1939 * x1976;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2037 = x1939 * x1977;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2038 = x1940 * x1948;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2039 = x1940 * x1950;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2040 = x1940 * x1955;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2041 = x1940 * x1961;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2042 = x1940 * x1966;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2043 = x1940 * x1972;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2044 = x1941 * x1948;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2045 = x1941 * x1950;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2046 = x1941 * x1955;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2047 = x1941 * x1961;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2048 = x1941 * x1966;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2049 = x1941 * x1972;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2050 = x1943 * x1949;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2051 = x1943 * x1951;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2052 = x1943 * x1956;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2053 = x1943 * x1962;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2054 = x1943 * x1967;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2055 = x1943 * x1973;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2056 = x1944 * x1949;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2057 = x1944 * x1951;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2058 = x1944 * x1956;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2059 = x1944 * x1962;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2060 = x1944 * x1967;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2061 = x1944 * x1973;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2062 = x1945 * x1949;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2063 = x1945 * x1951;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2064 = x1945 * x1956;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2065 = x1945 * x1962;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2066 = x1945 * x1967;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2067 = x1945 * x1973;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2068 = x1947 * x1952;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2069 = x1947 * x1957;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2070 = x1947 * x1959;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2071 = x1947 * x1963;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2072 = x1947 * x1968;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2073 = x1947 * x1974;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2074 = x1932 * x1953;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2075 = x1932 * x1958;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2076 = x1932 * x1964;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2077 = x1932 * x1969;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2078 = x1932 * x1970;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2079 = x1932 * x1975;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2080 = x1936 * x1954;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2081 = x1936 * x1960;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2082 = x1936 * x1965;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2083 = x1936 * x1971;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2084 = x1936 * x1976;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2085 = x1936 * x1977;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2086 = x1942 * x1949;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2087 = x1942 * x1951;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2088 = x1942 * x1956;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2089 = x1942 * x1962;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2090 = x1942 * x1967;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2091 = x1942 * x1973;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2092 = x1946 * x1952;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2093 = x1946 * x1957;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2094 = x1946 * x1959;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2095 = x1946 * x1963;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2096 = x1946 * x1968;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2097 = x1946 * x1974;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2098 = x1978 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2099 = x1979 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2100 = x1980 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2101 = x1981 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2102 = x1982 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2103 = x1983 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2104 = x2098 + x2086;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2105 = x2099 + x2087;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2106 = x2100 + x2088;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2107 = x2101 + x2089;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2108 = x2102 + x2090;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2109 = x2103 + x2091;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2110 = x2104 + x2094;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2111 = x2105 + x2092;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2112 = x2106 + x2093;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2113 = x2107 + x2095;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2114 = x2108 + x2096;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2115 = x2109 + x2097;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2116 = x1984 + x2050;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2117 = x1985 + x2051;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2118 = x1986 + x2052;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2119 = x1987 + x2053;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2120 = x1988 + x2054;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2121 = x1989 + x2055;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2122 = x2038 + x2056;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2123 = x2039 + x2057;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2124 = x2040 + x2058;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2125 = x2041 + x2059;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2126 = x2042 + x2060;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2127 = x2043 + x2061;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2128 = x2044 + x2062;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2129 = x2045 + x2063;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2130 = x2046 + x2064;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2131 = x2047 + x2065;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2132 = x2048 + x2066;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2133 = x2049 + x2067;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2134 = x2110 + x2078;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2135 = x2111 + x2074;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2136 = x2112 + x2075;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2137 = x2113 + x2076;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2138 = x2114 + x2077;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2139 = x2115 + x2079;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2140 = x2116 + x2070;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2141 = x2117 + x2068;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2142 = x2118 + x2069;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2143 = x2119 + x2071;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2144 = x2120 + x2072;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2145 = x2121 + x2073;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2146 = x2122 + x1992;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2147 = x2123 + x1990;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2148 = x2124 + x1991;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2149 = x2125 + x1993;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2150 = x2126 + x1994;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2151 = x2127 + x1995;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2152 = x2128 + x1998;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2153 = x2129 + x1996;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2154 = x2130 + x1997;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2155 = x2131 + x1999;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2156 = x2132 + x2000;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2157 = x2133 + x2001;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2158 = x2136 + x2081;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2159 = x2139 + x2084;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2160 = x2134 + x2085;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2161 = x2135 + x2080;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2162 = x2137 + x2082;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2163 = x2138 + x2083;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2164 = x2140 + x2006;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2165 = x2141 + x2002;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2166 = x2142 + x2003;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2167 = x2143 + x2004;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2168 = x2144 + x2005;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2169 = x2145 + x2007;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2170 = x2146 + x2012;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2171 = x2147 + x2008;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2172 = x2148 + x2009;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2173 = x2149 + x2010;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2174 = x2150 + x2011;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2175 = x2151 + x2013;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2176 = x2152 + x2018;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2177 = x2153 + x2014;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2178 = x2154 + x2015;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2179 = x2155 + x2016;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2180 = x2156 + x2017;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2181 = x2157 + x2019;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2182 = x2166 + x2021;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2183 = x2169 + x2024;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2184 = x2172 + x2027;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2185 = x2175 + x2030;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2186 = x2178 + x2033;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2187 = x2181 + x2036;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2188 = x2164 + x2025;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2189 = x2165 + x2020;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2190 = x2167 + x2022;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2191 = x2168 + x2023;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2192 = x2170 + x2031;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2193 = x2171 + x2026;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2194 = x2173 + x2028;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2195 = x2174 + x2029;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2196 = x2176 + x2037;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2197 = x2177 + x2032;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2198 = x2179 + x2034;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2199 = x2180 + x2035;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2200 = x2189 * x2186;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2201 = x2191 * x2187;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2202 = x2192 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2203 = x2196 * x2196;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2204 = x2196 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2205 = x2189 * x2182;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2206 = x2189 * x2184;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2207 = x2189 * x2158;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2208 = x2191 * x2183;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2209 = x2191 * x2185;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2210 = x2191 * x2159;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2211 = x2188 * x2188;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2212 = x2192 * x2192;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2213 = x2203 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2214 = -x2188;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2215 = x2192 + x2192;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2216 = x2196 + x2196;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2217 = x2193 * x2186;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2218 = x2195 * x2187;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2219 = x2197 * x2186;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2220 = x2199 * x2187;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2221 = x2161 * x2182;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2222 = x2161 * x2184;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2223 = x2161 * x2186;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2224 = x2161 * x2158;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2225 = x2163 * x2183;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2226 = x2163 * x2185;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2227 = x2163 * x2187;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2228 = x2163 * x2159;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2229 = x2188 * x2216;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2230 = x2160 * x2215;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2231 = x2160 * x2160;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2232 = x2193 * x2182;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2233 = x2193 * x2184;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2234 = x2193 * x2158;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2235 = x2195 * x2183;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2236 = x2195 * x2185;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2237 = x2195 * x2159;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2238 = x2197 * x2182;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2239 = x2197 * x2184;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2240 = x2197 * x2158;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2241 = x2199 * x2183;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2242 = x2199 * x2185;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2243 = x2199 * x2159;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2244 = x2219 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2245 = x2220 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2246 = -x2160;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2247 = x2229 - x2212;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2248 = x2230 - x2211;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2249 = x2217 + x2239;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2250 = x2218 + x2242;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2251 = x2200 + x2233;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2252 = x2201 + x2236;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2253 = x2221 + x2207;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2254 = x2222 + x2205;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2255 = x2223 + x2206;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2256 = x2225 + x2210;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2257 = x2226 + x2208;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2258 = x2227 + x2209;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2259 = x2248 + x2213;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2260 = x2259 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2261 = x2249 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2262 = x2250 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2263 = x2260 * x2259;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2264 = x2247 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2265 = x2251 + x2238;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2266 = x2252 + x2241;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2267 = x2253 + x2261;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2268 = x2254 + x2234;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2269 = x2255 + x2232;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2270 = x2257 + x2237;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2271 = x2258 + x2235;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2272 = x2256 + x2262;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2273 = x2231 + x2264;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2274 = x2270 + x2245;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2275 = x2271 + x2243;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2276 = x2273 * x2273;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2277 = x2274 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2278 = x2275 * x2275;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2279 = x2275 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2280 = x2265 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2281 = x2266 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2282 = x2272 * x2272;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2283 = x2274 * x2274;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2284 = x2278 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2285 = -x2272;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2286 = x2268 + x2244;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2287 = x2269 + x2240;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2288 = x2224 + x2280;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2289 = x2276 + x2263;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2290 = x2274 + x2274;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2291 = x2275 + x2275;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2292 = x2228 + x2281;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2293 = inv(x2289);
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2294 = x2272 * x2291;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2295 = x2292 * x2290;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2296 = x2292 * x2292;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2297 = x2273 * x2293;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2298 = x2259 * x2293;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2299 = -x2292;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2300 = x2294 - x2283;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2301 = x2295 - x2282;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2302 = x2301 + x2284;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2303 = x2188 * x2298;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2304 = x2160 * x2297;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2305 = x2302 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2306 = x2214 * x2297;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2307 = x2246 * x2298;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2308 = x2192 * x2297;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2309 = x2196 * x2297;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2310 = x2305 * x2302;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2311 = x2202 * x2298;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2312 = x2204 * x2298;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2313 = x2300 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2314 = x2303 - x2309;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2315 = x2306 - x2312;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2316 = x2296 + x2313;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2317 = x2304 + x2311;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2318 = x2307 + x2308;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2319 = x2316 * x2316;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2320 = x2319 + x2310;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2321 = inv(x2320);
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2322 = x2316 * x2321;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2323 = x2302 * x2321;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2324 = x2272 * x2323;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2325 = x2292 * x2322;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2326 = x2285 * x2322;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2327 = x2299 * x2323;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2328 = x2274 * x2322;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2329 = x2275 * x2322;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2330 = x2277 * x2323;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2331 = x2279 * x2323;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2332 = x2324 - x2329;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2333 = x2326 - x2331;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2334 = x2325 + x2330;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2335 = x2327 + x2328;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2336 = x2286 * x2332;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2337 = x2287 * x2332;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2338 = x2267 * x2332;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2339 = x2288 * x2334;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2340 = x2288 * x2335;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2341 = x2288 * x2332;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2342 = x2288 * x2333;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2343 = x2286 * x2334;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2344 = x2286 * x2335;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2345 = x2286 * x2333;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2346 = x2287 * x2334;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2347 = x2287 * x2335;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2348 = x2287 * x2333;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2349 = x2267 * x2334;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2350 = x2267 * x2335;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2351 = x2267 * x2333;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2352 = x2337 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2353 = x2336 + x2347;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2354 = x2338 + x2344;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2355 = x2340 + x2351;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2356 = x2341 + x2350;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2357 = x2342 + x2349;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2358 = x2353 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2359 = x2354 + x2348;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2360 = x2355 + x2343;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2361 = x2356 + x2345;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2362 = x2357 + x2358;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2363 = x2362 * x2198;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2364 = x2359 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2365 = x2362 * x2194;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2366 = x2362 * x2190;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2367 = x2362 * x2162;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2368 = x2360 + x2352;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2369 = x2361 + x2346;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2370 = x2339 + x2364;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2371 = x2368 * x2198;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2372 = x2369 * x2198;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2373 = x2370 * x2194;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2374 = x2370 * x2198;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2375 = x2370 * x2190;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2376 = x2370 * x2162;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2377 = x2368 * x2194;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2378 = x2368 * x2190;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2379 = x2368 * x2162;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2380 = x2369 * x2194;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2381 = x2369 * x2190;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2382 = x2369 * x2162;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2383 = x2372 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2384 = x2371 + x2380;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2385 = x2363 + x2377;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2386 = x2373 + x2366;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2387 = x2374 + x2365;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2388 = x2375 + x2367;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2389 = x2384 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2390 = x2385 + x2381;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2391 = x2386 + x2379;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2392 = x2387 + x2378;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2393 = x2388 + x2389;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2394 = x2393 * x2314;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2395 = x2390 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2396 = x2393 * x2317;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2397 = x2393 * x2318;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2398 = x2393 * x2315;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2399 = x2391 + x2383;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2400 = x2392 + x2382;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2401 = x2376 + x2395;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2402 = x2399 * x2314;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2403 = x2400 * x2314;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2404 = x2401 * x2317;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2405 = x2401 * x2318;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2406 = x2401 * x2314;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2407 = x2401 * x2315;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2408 = x2399 * x2317;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2409 = x2399 * x2318;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2410 = x2399 * x2315;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2411 = x2400 * x2317;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2412 = x2400 * x2318;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2413 = x2400 * x2315;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2414 = x2403 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2415 = x2402 + x2412;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2416 = x2394 + x2409;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2417 = x2405 + x2398;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2418 = x2406 + x2397;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2419 = x2407 + x2396;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2420 = x2415 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2421 = x2416 + x2413;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2422 = x2417 + x2408;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2423 = x2418 + x2410;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2424 = x2419 + x2420;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2425 = x2422 + x2414;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2426 = x2423 + x2411;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2427 = x2421 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2428 = x2404 + x2427;
        extern_args[0] = x2428;
        extern_args[1] = x2424;
        extern_args[2] = x2425;
        extern_args[3] = x2426;
        extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x2429 = arg0[13 * steps + ((cycle - 0) & mask)];
    assert(x2429 != Fp::invalid());
    if (x2429 != 0) {
      {
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2430 = arg3[0];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2431 = arg3[1];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2432 = arg3[10];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2433 = arg3[11];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2434 = arg3[12];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2435 = arg3[13];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2436 = arg3[14];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2437 = arg3[15];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2438 = arg3[16];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2439 = arg3[17];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2440 = arg3[18];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2441 = arg3[19];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2442 = arg3[2];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2443 = arg3[3];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2444 = arg3[4];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2445 = arg3[5];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2446 = arg3[6];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2447 = arg3[7];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2448 = arg3[8];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2449 = arg3[9];
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x2450 = arg2[0 * steps + ((cycle - 0) & mask)];
        assert(x2450 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2451 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x2451 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x2452 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x2452 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2453 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x2453 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2454 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x2454 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2455 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x2455 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2456 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x2456 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x2457 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x2457 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2458 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x2458 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2459 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x2459 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2460 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x2460 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2461 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x2461 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2462 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x2462 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x2463 = arg2[21 * steps + ((cycle - 0) & mask)];
        assert(x2463 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2464 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x2464 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2465 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x2465 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2466 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x2466 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_init(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2467 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x2467 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2468 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x2468 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2469 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x2469 != Fp::invalid());
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2470 = x2430 * x2450;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2471 = x2430 * x2452;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2472 = x2430 * x2457;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2473 = x2430 * x2463;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2474 = x2431 * x2450;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2475 = x2431 * x2452;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2476 = x2431 * x2457;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2477 = x2431 * x2463;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2478 = x2432 * x2454;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2479 = x2432 * x2459;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2480 = x2432 * x2461;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2481 = x2432 * x2465;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2482 = x2433 * x2454;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2483 = x2433 * x2459;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2484 = x2433 * x2461;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2485 = x2433 * x2465;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2486 = x2435 * x2455;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2487 = x2435 * x2460;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2488 = x2435 * x2466;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2489 = x2435 * x2468;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2490 = x2436 * x2455;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2491 = x2436 * x2460;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2492 = x2436 * x2466;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2493 = x2436 * x2468;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2494 = x2437 * x2455;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2495 = x2437 * x2460;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2496 = x2437 * x2466;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2497 = x2437 * x2468;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2498 = x2439 * x2456;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2499 = x2439 * x2462;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2500 = x2439 * x2467;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2501 = x2439 * x2469;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2502 = x2440 * x2456;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2503 = x2440 * x2462;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2504 = x2440 * x2467;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2505 = x2440 * x2469;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2506 = x2441 * x2456;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2507 = x2441 * x2462;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2508 = x2441 * x2467;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2509 = x2441 * x2469;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2510 = x2442 * x2450;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2511 = x2442 * x2452;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2512 = x2442 * x2457;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2513 = x2442 * x2463;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2514 = x2443 * x2450;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2515 = x2443 * x2452;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2516 = x2443 * x2457;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2517 = x2443 * x2463;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2518 = x2445 * x2451;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2519 = x2445 * x2453;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2520 = x2445 * x2458;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2521 = x2445 * x2464;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2522 = x2446 * x2451;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2523 = x2446 * x2453;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2524 = x2446 * x2458;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2525 = x2446 * x2464;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2526 = x2447 * x2451;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2527 = x2447 * x2453;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2528 = x2447 * x2458;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2529 = x2447 * x2464;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2530 = x2449 * x2454;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2531 = x2449 * x2459;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2532 = x2449 * x2461;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2533 = x2449 * x2465;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2534 = x2434 * x2455;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2535 = x2434 * x2460;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2536 = x2434 * x2466;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2537 = x2434 * x2468;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2538 = x2438 * x2456;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2539 = x2438 * x2462;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2540 = x2438 * x2467;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2541 = x2438 * x2469;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2542 = x2444 * x2451;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2543 = x2444 * x2453;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2544 = x2444 * x2458;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2545 = x2444 * x2464;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2546 = x2448 * x2454;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2547 = x2448 * x2459;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2548 = x2448 * x2461;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2549 = x2448 * x2465;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2550 = x2470 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2551 = x2471 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2552 = x2472 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2553 = x2473 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2554 = x2550 + x2542;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2555 = x2551 + x2543;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2556 = x2552 + x2544;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2557 = x2553 + x2545;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2558 = x2554 + x2548;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2559 = x2555 + x2546;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2560 = x2556 + x2547;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2561 = x2557 + x2549;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2562 = x2474 + x2518;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2563 = x2475 + x2519;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2564 = x2476 + x2520;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2565 = x2477 + x2521;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2566 = x2510 + x2522;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2567 = x2511 + x2523;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2568 = x2512 + x2524;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2569 = x2513 + x2525;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2570 = x2514 + x2526;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2571 = x2515 + x2527;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2572 = x2516 + x2528;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2573 = x2517 + x2529;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2574 = x2558 + x2537;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2575 = x2559 + x2534;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2576 = x2560 + x2535;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2577 = x2561 + x2536;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2578 = x2562 + x2532;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2579 = x2563 + x2530;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2580 = x2564 + x2531;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2581 = x2565 + x2533;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2582 = x2566 + x2480;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2583 = x2567 + x2478;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2584 = x2568 + x2479;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2585 = x2569 + x2481;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2586 = x2570 + x2484;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2587 = x2571 + x2482;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2588 = x2572 + x2483;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2589 = x2573 + x2485;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2590 = x2574 + x2541;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2591 = x2576 + x2539;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2592 = x2575 + x2538;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2593 = x2577 + x2540;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2594 = x2578 + x2489;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2595 = x2579 + x2486;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2596 = x2580 + x2487;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2597 = x2581 + x2488;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2598 = x2582 + x2493;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2599 = x2583 + x2490;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2600 = x2584 + x2491;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2601 = x2585 + x2492;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2602 = x2586 + x2497;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2603 = x2587 + x2494;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2604 = x2588 + x2495;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2605 = x2589 + x2496;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2606 = x2594 + x2501;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2607 = x2596 + x2499;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2608 = x2598 + x2505;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2609 = x2600 + x2503;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2610 = x2602 + x2509;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2611 = x2604 + x2507;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2612 = x2595 + x2498;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2613 = x2597 + x2500;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2614 = x2599 + x2502;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2615 = x2601 + x2504;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2616 = x2603 + x2506;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2617 = x2605 + x2508;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2618 = x2612 * x2611;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2619 = x2613 * x2610;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2620 = x2612 * x2607;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2621 = x2612 * x2609;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2622 = x2612 * x2591;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2623 = x2613 * x2606;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2624 = x2613 * x2608;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2625 = x2613 * x2590;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2626 = x2614 * x2611;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2627 = x2615 * x2610;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2628 = x2616 * x2611;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2629 = x2617 * x2610;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2630 = x2592 * x2607;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2631 = x2592 * x2609;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2632 = x2592 * x2611;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2633 = x2592 * x2591;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2634 = x2593 * x2606;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2635 = x2593 * x2608;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2636 = x2593 * x2610;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2637 = x2593 * x2590;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2638 = x2614 * x2607;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2639 = x2614 * x2609;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2640 = x2614 * x2591;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2641 = x2615 * x2606;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2642 = x2615 * x2608;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2643 = x2615 * x2590;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2644 = x2616 * x2607;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2645 = x2616 * x2609;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2646 = x2616 * x2591;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2647 = x2617 * x2606;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2648 = x2617 * x2608;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2649 = x2617 * x2590;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2650 = x2628 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2651 = x2629 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2652 = x2626 + x2645;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2653 = x2627 + x2648;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2654 = x2618 + x2639;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2655 = x2619 + x2642;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2656 = x2630 + x2622;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2657 = x2631 + x2620;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2658 = x2632 + x2621;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2659 = x2634 + x2625;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2660 = x2635 + x2623;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2661 = x2636 + x2624;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2662 = x2652 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2663 = x2653 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2664 = x2654 + x2644;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2665 = x2655 + x2647;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2666 = x2656 + x2662;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2667 = x2657 + x2640;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2668 = x2658 + x2638;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2669 = x2660 + x2643;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2670 = x2661 + x2641;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2671 = x2659 + x2663;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2672 = x2669 + x2651;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2673 = x2670 + x2649;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2674 = x2672 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2675 = x2673 * x2673;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2676 = x2673 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2677 = x2664 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2678 = x2665 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2679 = x2671 * x2671;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2680 = x2672 * x2672;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2681 = x2675 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2682 = -x2671;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2683 = x2667 + x2650;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2684 = x2668 + x2646;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2685 = x2633 + x2677;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2686 = x2672 + x2672;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2687 = x2673 + x2673;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2688 = x2637 + x2678;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2689 = x2671 * x2687;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2690 = x2688 * x2686;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2691 = x2688 * x2688;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2692 = -x2688;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2693 = x2689 - x2680;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2694 = x2690 - x2679;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2695 = x2694 + x2681;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2696 = x2695 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2697 = x2696 * x2695;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2698 = x2693 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2699 = x2691 + x2698;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2700 = x2699 * x2699;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2701 = x2700 + x2697;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2702 = inv(x2701);
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2703 = x2699 * x2702;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2704 = x2695 * x2702;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2705 = x2671 * x2704;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2706 = x2688 * x2703;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2707 = x2682 * x2703;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2708 = x2692 * x2704;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2709 = x2672 * x2703;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2710 = x2673 * x2703;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2711 = x2674 * x2704;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2712 = x2676 * x2704;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2713 = x2705 - x2710;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2714 = x2707 - x2712;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2715 = x2706 + x2711;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2716 = x2708 + x2709;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2717 = x2683 * x2713;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2718 = x2684 * x2713;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2719 = x2666 * x2713;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2720 = x2685 * x2715;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2721 = x2685 * x2716;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2722 = x2685 * x2713;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2723 = x2685 * x2714;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2724 = x2683 * x2715;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2725 = x2683 * x2716;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2726 = x2683 * x2714;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2727 = x2684 * x2715;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2728 = x2684 * x2716;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2729 = x2684 * x2714;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2730 = x2666 * x2715;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2731 = x2666 * x2716;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2732 = x2666 * x2714;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2733 = x2718 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2734 = x2717 + x2728;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2735 = x2719 + x2725;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2736 = x2721 + x2732;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2737 = x2722 + x2731;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2738 = x2723 + x2730;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2739 = x2734 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2740 = x2735 + x2729;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2741 = x2736 + x2724;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2742 = x2737 + x2726;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2743 = x2738 + x2739;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2744 = x2741 + x2733;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2745 = x2742 + x2727;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2746 = x2740 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x2747 = x2720 + x2746;
        extern_args[0] = x2747;
        extern_args[1] = x2743;
        extern_args[2] = x2744;
        extern_args[3] = x2745;
        extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x2748 = arg0[14 * steps + ((cycle - 0) & mask)];
    assert(x2748 != Fp::invalid());
    if (x2748 != 0) {
      {
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2749 = arg3[0];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2750 = arg3[1];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2751 = arg3[10];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2752 = arg3[11];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2753 = arg3[12];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2754 = arg3[13];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2755 = arg3[14];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2756 = arg3[15];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2757 = arg3[16];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2758 = arg3[17];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2759 = arg3[18];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2760 = arg3[19];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2761 = arg3[2];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2762 = arg3[3];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2763 = arg3[4];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2764 = arg3[5];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2765 = arg3[6];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2766 = arg3[7];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2767 = arg3[8];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x2768 = arg3[9];
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x2769 = arg2[0 * steps + ((cycle - 0) & mask)];
        assert(x2769 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2770 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x2770 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x2771 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x2771 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2772 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x2772 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2773 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x2773 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2774 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x2774 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2775 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x2775 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x2776 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x2776 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2777 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x2777 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2778 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x2778 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2779 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x2779 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2780 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x2780 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2781 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x2781 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x2782 = arg2[21 * steps + ((cycle - 0) & mask)];
        assert(x2782 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2783 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x2783 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2784 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x2784 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2785 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x2785 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_fini(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2786 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x2786 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2787 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x2787 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x2788 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x2788 != Fp::invalid());
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2789 = x2749 * x2769;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2790 = x2749 * x2771;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2791 = x2749 * x2776;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2792 = x2749 * x2782;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2793 = x2750 * x2769;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2794 = x2750 * x2771;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2795 = x2750 * x2776;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2796 = x2750 * x2782;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2797 = x2751 * x2773;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2798 = x2751 * x2778;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2799 = x2751 * x2780;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2800 = x2751 * x2784;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2801 = x2752 * x2773;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2802 = x2752 * x2778;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2803 = x2752 * x2780;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2804 = x2752 * x2784;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2805 = x2754 * x2774;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2806 = x2754 * x2779;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2807 = x2754 * x2785;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2808 = x2754 * x2787;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2809 = x2755 * x2774;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2810 = x2755 * x2779;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2811 = x2755 * x2785;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2812 = x2755 * x2787;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2813 = x2756 * x2774;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2814 = x2756 * x2779;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2815 = x2756 * x2785;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2816 = x2756 * x2787;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2817 = x2758 * x2775;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2818 = x2758 * x2781;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2819 = x2758 * x2786;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2820 = x2758 * x2788;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2821 = x2759 * x2775;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2822 = x2759 * x2781;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2823 = x2759 * x2786;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2824 = x2759 * x2788;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2825 = x2760 * x2775;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2826 = x2760 * x2781;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2827 = x2760 * x2786;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2828 = x2760 * x2788;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2829 = x2761 * x2769;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2830 = x2761 * x2771;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2831 = x2761 * x2776;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2832 = x2761 * x2782;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2833 = x2762 * x2769;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2834 = x2762 * x2771;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2835 = x2762 * x2776;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2836 = x2762 * x2782;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2837 = x2764 * x2770;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2838 = x2764 * x2772;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2839 = x2764 * x2777;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2840 = x2764 * x2783;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2841 = x2765 * x2770;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2842 = x2765 * x2772;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2843 = x2765 * x2777;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2844 = x2765 * x2783;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2845 = x2766 * x2770;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2846 = x2766 * x2772;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2847 = x2766 * x2777;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2848 = x2766 * x2783;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2849 = x2768 * x2773;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2850 = x2768 * x2778;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2851 = x2768 * x2780;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2852 = x2768 * x2784;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2853 = x2753 * x2774;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2854 = x2753 * x2779;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2855 = x2753 * x2785;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2856 = x2753 * x2787;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2857 = x2757 * x2775;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2858 = x2757 * x2781;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2859 = x2757 * x2786;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2860 = x2757 * x2788;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2861 = x2763 * x2770;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2862 = x2763 * x2772;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2863 = x2763 * x2777;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2864 = x2763 * x2783;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2865 = x2767 * x2773;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2866 = x2767 * x2778;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2867 = x2767 * x2780;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x2868 = x2767 * x2784;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2869 = x2789 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2870 = x2790 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2871 = x2791 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2872 = x2792 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2873 = x2869 + x2861;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2874 = x2870 + x2862;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2875 = x2871 + x2863;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2876 = x2872 + x2864;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2877 = x2873 + x2867;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2878 = x2874 + x2865;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2879 = x2875 + x2866;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2880 = x2876 + x2868;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2881 = x2793 + x2837;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2882 = x2794 + x2838;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2883 = x2795 + x2839;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2884 = x2796 + x2840;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2885 = x2829 + x2841;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2886 = x2830 + x2842;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2887 = x2831 + x2843;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2888 = x2832 + x2844;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2889 = x2833 + x2845;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2890 = x2834 + x2846;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2891 = x2835 + x2847;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2892 = x2836 + x2848;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2893 = x2877 + x2856;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2894 = x2878 + x2853;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2895 = x2879 + x2854;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2896 = x2880 + x2855;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2897 = x2881 + x2851;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2898 = x2882 + x2849;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2899 = x2883 + x2850;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2900 = x2884 + x2852;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2901 = x2885 + x2799;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2902 = x2886 + x2797;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2903 = x2887 + x2798;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2904 = x2888 + x2800;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2905 = x2889 + x2803;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2906 = x2890 + x2801;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2907 = x2891 + x2802;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2908 = x2892 + x2804;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2909 = x2893 + x2860;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2910 = x2895 + x2858;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2911 = x2894 + x2857;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2912 = x2896 + x2859;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2913 = x2897 + x2808;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2914 = x2898 + x2805;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2915 = x2899 + x2806;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2916 = x2900 + x2807;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2917 = x2901 + x2812;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2918 = x2902 + x2809;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2919 = x2903 + x2810;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2920 = x2904 + x2811;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2921 = x2905 + x2816;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2922 = x2906 + x2813;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2923 = x2907 + x2814;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2924 = x2908 + x2815;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2925 = x2913 + x2820;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2926 = x2915 + x2818;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2927 = x2917 + x2824;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2928 = x2919 + x2822;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2929 = x2921 + x2828;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2930 = x2923 + x2826;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2931 = x2914 + x2817;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2932 = x2916 + x2819;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2933 = x2918 + x2821;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2934 = x2920 + x2823;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2935 = x2922 + x2825;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x2936 = x2924 + x2827;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2937 = x2931 * x2930;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2938 = x2932 * x2929;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2939 = x2931 * x2926;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2940 = x2931 * x2928;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2941 = x2931 * x2910;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2942 = x2932 * x2925;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2943 = x2932 * x2927;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2944 = x2932 * x2909;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2945 = x2933 * x2930;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2946 = x2934 * x2929;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2947 = x2935 * x2930;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2948 = x2936 * x2929;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2949 = x2911 * x2926;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2950 = x2911 * x2928;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2951 = x2911 * x2930;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2952 = x2911 * x2910;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2953 = x2912 * x2925;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2954 = x2912 * x2927;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2955 = x2912 * x2929;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2956 = x2912 * x2909;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2957 = x2933 * x2926;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2958 = x2933 * x2928;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2959 = x2933 * x2910;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2960 = x2934 * x2925;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2961 = x2934 * x2927;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2962 = x2934 * x2909;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2963 = x2935 * x2926;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2964 = x2935 * x2928;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2965 = x2935 * x2910;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2966 = x2936 * x2925;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2967 = x2936 * x2927;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2968 = x2936 * x2909;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2969 = x2947 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2970 = x2948 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2971 = x2945 + x2964;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2972 = x2946 + x2967;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2973 = x2937 + x2958;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2974 = x2938 + x2961;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2975 = x2949 + x2941;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2976 = x2950 + x2939;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2977 = x2951 + x2940;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2978 = x2953 + x2944;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2979 = x2954 + x2942;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2980 = x2955 + x2943;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2981 = x2971 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2982 = x2972 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2983 = x2973 + x2963;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2984 = x2974 + x2966;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2985 = x2975 + x2981;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2986 = x2976 + x2959;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2987 = x2977 + x2957;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2988 = x2979 + x2962;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2989 = x2980 + x2960;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2990 = x2978 + x2982;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2991 = x2988 + x2970;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2992 = x2989 + x2968;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2993 = x2991 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2994 = x2992 * x2992;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2995 = x2992 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2996 = x2983 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x2997 = x2984 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2998 = x2990 * x2990;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x2999 = x2991 * x2991;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3000 = x2994 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3001 = -x2990;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3002 = x2986 + x2969;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3003 = x2987 + x2965;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3004 = x2952 + x2996;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3005 = x2991 + x2991;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3006 = x2992 + x2992;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3007 = x2956 + x2997;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3008 = x2990 * x3006;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3009 = x3007 * x3005;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3010 = x3007 * x3007;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3011 = -x3007;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3012 = x3008 - x2999;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3013 = x3009 - x2998;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3014 = x3013 + x3000;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3015 = x3014 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3016 = x3015 * x3014;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3017 = x3012 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3018 = x3010 + x3017;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3019 = x3018 * x3018;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3020 = x3019 + x3016;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3021 = inv(x3020);
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3022 = x3018 * x3021;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3023 = x3014 * x3021;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3024 = x2990 * x3023;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3025 = x3007 * x3022;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3026 = x3001 * x3022;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3027 = x3011 * x3023;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3028 = x2991 * x3022;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3029 = x2992 * x3022;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3030 = x2993 * x3023;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3031 = x2995 * x3023;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3032 = x3024 - x3029;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3033 = x3026 - x3031;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3034 = x3025 + x3030;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3035 = x3027 + x3028;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3036 = x3002 * x3032;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3037 = x3003 * x3032;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3038 = x2985 * x3032;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3039 = x3004 * x3034;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3040 = x3004 * x3035;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3041 = x3004 * x3032;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3042 = x3004 * x3033;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3043 = x3002 * x3034;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3044 = x3002 * x3035;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3045 = x3002 * x3033;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3046 = x3003 * x3034;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3047 = x3003 * x3035;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3048 = x3003 * x3033;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3049 = x2985 * x3034;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3050 = x2985 * x3035;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3051 = x2985 * x3033;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3052 = x3037 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3053 = x3036 + x3047;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3054 = x3038 + x3044;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3055 = x3040 + x3051;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3056 = x3041 + x3050;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3057 = x3042 + x3049;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3058 = x3053 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3059 = x3054 + x3048;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3060 = x3055 + x3043;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3061 = x3056 + x3045;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3062 = x3057 + x3058;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3063 = x3060 + x3052;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3064 = x3061 + x3046;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3065 = x3059 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3066 = x3039 + x3065;
        extern_args[0] = x3066;
        extern_args[1] = x3062;
        extern_args[2] = x3063;
        extern_args[3] = x3064;
        extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x3067 = arg0[15 * steps + ((cycle - 0) & mask)];
    assert(x3067 != Fp::invalid());
    if (x3067 != 0) {
      {
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3068 = arg3[0];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3069 = arg3[1];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3070 = arg3[10];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3071 = arg3[11];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3072 = arg3[12];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3073 = arg3[13];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3074 = arg3[14];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3075 = arg3[15];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3076 = arg3[16];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3077 = arg3[17];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3078 = arg3[18];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3079 = arg3[19];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3080 = arg3[2];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3081 = arg3[3];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3082 = arg3[4];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3083 = arg3[5];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3084 = arg3[6];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3085 = arg3[7];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3086 = arg3[8];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3087 = arg3[9];
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3088 = arg2[0 * steps + ((cycle - 0) & mask)];
        assert(x3088 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3089 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x3089 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3090 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3090 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3091 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x3091 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3092 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x3092 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3093 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x3093 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3094 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x3094 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3095 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x3095 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3096 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x3096 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3097 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x3097 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3098 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x3098 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3099 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x3099 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3100 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x3100 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3101 = arg2[21 * steps + ((cycle - 0) & mask)];
        assert(x3101 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3102 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x3102 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3103 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x3103 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3104 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x3104 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_load(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3105 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x3105 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3106 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3106 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3107 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3107 != Fp::invalid());
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3108 = x3068 * x3088;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3109 = x3068 * x3090;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3110 = x3068 * x3095;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3111 = x3068 * x3101;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3112 = x3069 * x3088;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3113 = x3069 * x3090;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3114 = x3069 * x3095;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3115 = x3069 * x3101;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3116 = x3070 * x3092;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3117 = x3070 * x3097;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3118 = x3070 * x3099;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3119 = x3070 * x3103;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3120 = x3071 * x3092;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3121 = x3071 * x3097;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3122 = x3071 * x3099;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3123 = x3071 * x3103;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3124 = x3073 * x3093;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3125 = x3073 * x3098;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3126 = x3073 * x3104;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3127 = x3073 * x3106;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3128 = x3074 * x3093;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3129 = x3074 * x3098;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3130 = x3074 * x3104;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3131 = x3074 * x3106;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3132 = x3075 * x3093;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3133 = x3075 * x3098;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3134 = x3075 * x3104;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3135 = x3075 * x3106;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3136 = x3077 * x3094;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3137 = x3077 * x3100;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3138 = x3077 * x3105;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3139 = x3077 * x3107;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3140 = x3078 * x3094;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3141 = x3078 * x3100;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3142 = x3078 * x3105;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3143 = x3078 * x3107;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3144 = x3079 * x3094;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3145 = x3079 * x3100;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3146 = x3079 * x3105;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3147 = x3079 * x3107;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3148 = x3080 * x3088;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3149 = x3080 * x3090;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3150 = x3080 * x3095;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3151 = x3080 * x3101;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3152 = x3081 * x3088;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3153 = x3081 * x3090;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3154 = x3081 * x3095;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3155 = x3081 * x3101;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3156 = x3083 * x3089;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3157 = x3083 * x3091;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3158 = x3083 * x3096;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3159 = x3083 * x3102;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3160 = x3084 * x3089;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3161 = x3084 * x3091;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3162 = x3084 * x3096;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3163 = x3084 * x3102;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3164 = x3085 * x3089;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3165 = x3085 * x3091;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3166 = x3085 * x3096;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3167 = x3085 * x3102;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3168 = x3087 * x3092;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3169 = x3087 * x3097;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3170 = x3087 * x3099;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3171 = x3087 * x3103;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3172 = x3072 * x3093;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3173 = x3072 * x3098;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3174 = x3072 * x3104;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3175 = x3072 * x3106;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3176 = x3076 * x3094;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3177 = x3076 * x3100;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3178 = x3076 * x3105;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3179 = x3076 * x3107;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3180 = x3082 * x3089;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3181 = x3082 * x3091;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3182 = x3082 * x3096;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3183 = x3082 * x3102;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3184 = x3086 * x3092;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3185 = x3086 * x3097;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3186 = x3086 * x3099;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3187 = x3086 * x3103;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3188 = x3108 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3189 = x3109 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3190 = x3110 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3191 = x3111 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3192 = x3188 + x3180;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3193 = x3189 + x3181;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3194 = x3190 + x3182;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3195 = x3191 + x3183;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3196 = x3192 + x3186;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3197 = x3193 + x3184;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3198 = x3194 + x3185;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3199 = x3195 + x3187;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3200 = x3112 + x3156;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3201 = x3113 + x3157;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3202 = x3114 + x3158;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3203 = x3115 + x3159;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3204 = x3148 + x3160;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3205 = x3149 + x3161;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3206 = x3150 + x3162;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3207 = x3151 + x3163;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3208 = x3152 + x3164;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3209 = x3153 + x3165;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3210 = x3154 + x3166;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3211 = x3155 + x3167;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3212 = x3196 + x3175;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3213 = x3197 + x3172;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3214 = x3198 + x3173;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3215 = x3199 + x3174;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3216 = x3200 + x3170;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3217 = x3201 + x3168;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3218 = x3202 + x3169;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3219 = x3203 + x3171;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3220 = x3204 + x3118;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3221 = x3205 + x3116;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3222 = x3206 + x3117;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3223 = x3207 + x3119;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3224 = x3208 + x3122;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3225 = x3209 + x3120;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3226 = x3210 + x3121;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3227 = x3211 + x3123;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3228 = x3212 + x3179;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3229 = x3214 + x3177;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3230 = x3213 + x3176;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3231 = x3215 + x3178;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3232 = x3216 + x3127;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3233 = x3217 + x3124;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3234 = x3218 + x3125;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3235 = x3219 + x3126;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3236 = x3220 + x3131;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3237 = x3221 + x3128;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3238 = x3222 + x3129;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3239 = x3223 + x3130;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3240 = x3224 + x3135;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3241 = x3225 + x3132;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3242 = x3226 + x3133;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3243 = x3227 + x3134;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3244 = x3232 + x3139;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3245 = x3234 + x3137;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3246 = x3236 + x3143;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3247 = x3238 + x3141;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3248 = x3240 + x3147;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3249 = x3242 + x3145;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3250 = x3233 + x3136;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3251 = x3235 + x3138;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3252 = x3237 + x3140;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3253 = x3239 + x3142;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3254 = x3241 + x3144;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3255 = x3243 + x3146;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3256 = x3250 * x3249;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3257 = x3251 * x3248;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3258 = x3250 * x3245;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3259 = x3250 * x3247;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3260 = x3250 * x3229;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3261 = x3251 * x3244;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3262 = x3251 * x3246;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3263 = x3251 * x3228;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3264 = x3252 * x3249;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3265 = x3253 * x3248;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3266 = x3254 * x3249;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3267 = x3255 * x3248;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3268 = x3230 * x3245;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3269 = x3230 * x3247;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3270 = x3230 * x3249;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3271 = x3230 * x3229;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3272 = x3231 * x3244;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3273 = x3231 * x3246;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3274 = x3231 * x3248;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3275 = x3231 * x3228;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3276 = x3252 * x3245;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3277 = x3252 * x3247;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3278 = x3252 * x3229;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3279 = x3253 * x3244;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3280 = x3253 * x3246;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3281 = x3253 * x3228;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3282 = x3254 * x3245;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3283 = x3254 * x3247;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3284 = x3254 * x3229;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3285 = x3255 * x3244;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3286 = x3255 * x3246;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3287 = x3255 * x3228;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3288 = x3266 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3289 = x3267 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3290 = x3264 + x3283;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3291 = x3265 + x3286;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3292 = x3256 + x3277;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3293 = x3257 + x3280;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3294 = x3268 + x3260;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3295 = x3269 + x3258;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3296 = x3270 + x3259;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3297 = x3272 + x3263;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3298 = x3273 + x3261;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3299 = x3274 + x3262;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3300 = x3290 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3301 = x3291 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3302 = x3292 + x3282;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3303 = x3293 + x3285;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3304 = x3294 + x3300;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3305 = x3295 + x3278;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3306 = x3296 + x3276;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3307 = x3298 + x3281;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3308 = x3299 + x3279;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3309 = x3297 + x3301;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3310 = x3307 + x3289;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3311 = x3308 + x3287;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3312 = x3310 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3313 = x3311 * x3311;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3314 = x3311 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3315 = x3302 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3316 = x3303 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3317 = x3309 * x3309;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3318 = x3310 * x3310;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3319 = x3313 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3320 = -x3309;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3321 = x3305 + x3288;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3322 = x3306 + x3284;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3323 = x3271 + x3315;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3324 = x3310 + x3310;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3325 = x3311 + x3311;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3326 = x3275 + x3316;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3327 = x3309 * x3325;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3328 = x3326 * x3324;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3329 = x3326 * x3326;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3330 = -x3326;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3331 = x3327 - x3318;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3332 = x3328 - x3317;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3333 = x3332 + x3319;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3334 = x3333 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3335 = x3334 * x3333;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3336 = x3331 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3337 = x3329 + x3336;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3338 = x3337 * x3337;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3339 = x3338 + x3335;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3340 = inv(x3339);
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3341 = x3337 * x3340;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3342 = x3333 * x3340;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3343 = x3309 * x3342;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3344 = x3326 * x3341;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3345 = x3320 * x3341;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3346 = x3330 * x3342;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3347 = x3310 * x3341;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3348 = x3311 * x3341;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3349 = x3312 * x3342;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3350 = x3314 * x3342;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3351 = x3343 - x3348;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3352 = x3345 - x3350;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3353 = x3344 + x3349;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3354 = x3346 + x3347;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3355 = x3321 * x3351;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3356 = x3322 * x3351;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3357 = x3304 * x3351;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3358 = x3323 * x3353;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3359 = x3323 * x3354;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3360 = x3323 * x3351;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3361 = x3323 * x3352;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3362 = x3321 * x3353;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3363 = x3321 * x3354;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3364 = x3321 * x3352;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3365 = x3322 * x3353;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3366 = x3322 * x3354;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3367 = x3322 * x3352;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3368 = x3304 * x3353;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3369 = x3304 * x3354;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3370 = x3304 * x3352;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3371 = x3356 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3372 = x3355 + x3366;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3373 = x3357 + x3363;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3374 = x3359 + x3370;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3375 = x3360 + x3369;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3376 = x3361 + x3368;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3377 = x3372 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3378 = x3373 + x3367;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3379 = x3374 + x3362;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3380 = x3375 + x3364;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3381 = x3376 + x3377;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3382 = x3379 + x3371;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3383 = x3380 + x3365;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3384 = x3378 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3385 = x3358 + x3384;
        extern_args[0] = x3385;
        extern_args[1] = x3381;
        extern_args[2] = x3382;
        extern_args[3] = x3383;
        extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x3386 = arg0[16 * steps + ((cycle - 0) & mask)];
    assert(x3386 != Fp::invalid());
    if (x3386 != 0) {
      {
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3387 = arg3[0];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3388 = arg3[1];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3389 = arg3[10];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3390 = arg3[11];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3391 = arg3[12];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3392 = arg3[13];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3393 = arg3[14];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3394 = arg3[15];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3395 = arg3[16];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3396 = arg3[17];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3397 = arg3[18];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3398 = arg3[19];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3399 = arg3[2];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3400 = arg3[3];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3401 = arg3[4];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3402 = arg3[5];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3403 = arg3[6];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3404 = arg3[7];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3405 = arg3[8];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3406 = arg3[9];
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3407 = arg2[0 * steps + ((cycle - 0) & mask)];
        assert(x3407 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3408 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x3408 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3409 = arg2[11 * steps + ((cycle - 0) & mask)];
        assert(x3409 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3410 = arg2[12 * steps + ((cycle - 0) & mask)];
        assert(x3410 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3411 = arg2[13 * steps + ((cycle - 0) & mask)];
        assert(x3411 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3412 = arg2[14 * steps + ((cycle - 0) & mask)];
        assert(x3412 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3413 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x3413 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3414 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x3414 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3415 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x3415 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3416 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x3416 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3417 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x3417 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3418 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x3418 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3419 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x3419 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3420 = arg2[21 * steps + ((cycle - 0) & mask)];
        assert(x3420 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3421 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x3421 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3422 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x3422 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3423 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x3423 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/sha_mix(recursion::ShaWrap)/sha_cycle(recursion::ShaCycle)/recursion::WomBody/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3424 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x3424 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3425 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3425 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3426 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3426 != Fp::invalid());
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3427 = x3387 * x3407;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3428 = x3387 * x3409;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3429 = x3387 * x3414;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3430 = x3387 * x3420;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3431 = x3388 * x3407;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3432 = x3388 * x3409;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3433 = x3388 * x3414;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3434 = x3388 * x3420;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3435 = x3389 * x3411;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3436 = x3389 * x3416;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3437 = x3389 * x3418;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3438 = x3389 * x3422;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3439 = x3390 * x3411;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3440 = x3390 * x3416;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3441 = x3390 * x3418;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3442 = x3390 * x3422;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3443 = x3392 * x3412;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3444 = x3392 * x3417;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3445 = x3392 * x3423;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3446 = x3392 * x3425;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3447 = x3393 * x3412;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3448 = x3393 * x3417;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3449 = x3393 * x3423;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3450 = x3393 * x3425;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3451 = x3394 * x3412;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3452 = x3394 * x3417;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3453 = x3394 * x3423;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3454 = x3394 * x3425;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3455 = x3396 * x3413;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3456 = x3396 * x3419;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3457 = x3396 * x3424;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3458 = x3396 * x3426;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3459 = x3397 * x3413;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3460 = x3397 * x3419;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3461 = x3397 * x3424;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3462 = x3397 * x3426;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3463 = x3398 * x3413;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3464 = x3398 * x3419;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3465 = x3398 * x3424;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3466 = x3398 * x3426;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3467 = x3399 * x3407;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3468 = x3399 * x3409;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3469 = x3399 * x3414;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3470 = x3399 * x3420;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3471 = x3400 * x3407;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3472 = x3400 * x3409;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3473 = x3400 * x3414;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3474 = x3400 * x3420;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3475 = x3402 * x3408;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3476 = x3402 * x3410;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3477 = x3402 * x3415;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3478 = x3402 * x3421;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3479 = x3403 * x3408;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3480 = x3403 * x3410;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3481 = x3403 * x3415;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3482 = x3403 * x3421;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3483 = x3404 * x3408;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3484 = x3404 * x3410;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3485 = x3404 * x3415;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3486 = x3404 * x3421;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3487 = x3406 * x3411;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3488 = x3406 * x3416;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3489 = x3406 * x3418;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3490 = x3406 * x3422;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3491 = x3391 * x3412;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3492 = x3391 * x3417;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3493 = x3391 * x3423;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3494 = x3391 * x3425;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3495 = x3395 * x3413;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3496 = x3395 * x3419;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3497 = x3395 * x3424;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3498 = x3395 * x3426;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3499 = x3401 * x3408;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3500 = x3401 * x3410;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3501 = x3401 * x3415;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3502 = x3401 * x3421;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3503 = x3405 * x3411;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3504 = x3405 * x3416;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3505 = x3405 * x3418;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3506 = x3405 * x3422;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3507 = x3427 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3508 = x3428 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3509 = x3429 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3510 = x3430 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3511 = x3507 + x3499;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3512 = x3508 + x3500;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3513 = x3509 + x3501;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3514 = x3510 + x3502;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3515 = x3511 + x3505;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3516 = x3512 + x3503;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3517 = x3513 + x3504;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3518 = x3514 + x3506;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3519 = x3431 + x3475;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3520 = x3432 + x3476;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3521 = x3433 + x3477;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3522 = x3434 + x3478;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3523 = x3467 + x3479;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3524 = x3468 + x3480;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3525 = x3469 + x3481;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3526 = x3470 + x3482;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3527 = x3471 + x3483;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3528 = x3472 + x3484;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3529 = x3473 + x3485;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3530 = x3474 + x3486;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3531 = x3515 + x3494;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3532 = x3516 + x3491;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3533 = x3517 + x3492;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3534 = x3518 + x3493;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3535 = x3519 + x3489;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3536 = x3520 + x3487;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3537 = x3521 + x3488;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3538 = x3522 + x3490;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3539 = x3523 + x3437;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3540 = x3524 + x3435;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3541 = x3525 + x3436;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3542 = x3526 + x3438;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3543 = x3527 + x3441;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3544 = x3528 + x3439;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3545 = x3529 + x3440;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3546 = x3530 + x3442;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3547 = x3531 + x3498;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3548 = x3533 + x3496;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3549 = x3532 + x3495;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3550 = x3534 + x3497;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3551 = x3535 + x3446;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3552 = x3536 + x3443;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3553 = x3537 + x3444;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3554 = x3538 + x3445;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3555 = x3539 + x3450;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3556 = x3540 + x3447;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3557 = x3541 + x3448;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3558 = x3542 + x3449;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3559 = x3543 + x3454;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3560 = x3544 + x3451;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3561 = x3545 + x3452;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3562 = x3546 + x3453;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3563 = x3551 + x3458;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3564 = x3553 + x3456;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3565 = x3555 + x3462;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3566 = x3557 + x3460;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3567 = x3559 + x3466;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3568 = x3561 + x3464;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3569 = x3552 + x3455;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3570 = x3554 + x3457;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3571 = x3556 + x3459;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3572 = x3558 + x3461;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3573 = x3560 + x3463;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3574 = x3562 + x3465;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3575 = x3569 * x3568;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3576 = x3570 * x3567;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3577 = x3569 * x3564;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3578 = x3569 * x3566;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3579 = x3569 * x3548;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3580 = x3570 * x3563;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3581 = x3570 * x3565;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3582 = x3570 * x3547;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3583 = x3571 * x3568;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3584 = x3572 * x3567;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3585 = x3573 * x3568;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3586 = x3574 * x3567;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3587 = x3549 * x3564;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3588 = x3549 * x3566;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3589 = x3549 * x3568;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3590 = x3549 * x3548;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3591 = x3550 * x3563;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3592 = x3550 * x3565;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3593 = x3550 * x3567;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3594 = x3550 * x3547;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3595 = x3571 * x3564;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3596 = x3571 * x3566;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3597 = x3571 * x3548;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3598 = x3572 * x3563;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3599 = x3572 * x3565;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3600 = x3572 * x3547;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3601 = x3573 * x3564;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3602 = x3573 * x3566;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3603 = x3573 * x3548;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3604 = x3574 * x3563;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3605 = x3574 * x3565;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3606 = x3574 * x3547;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3607 = x3585 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3608 = x3586 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3609 = x3583 + x3602;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3610 = x3584 + x3605;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3611 = x3575 + x3596;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3612 = x3576 + x3599;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3613 = x3587 + x3579;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3614 = x3588 + x3577;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3615 = x3589 + x3578;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3616 = x3591 + x3582;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3617 = x3592 + x3580;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3618 = x3593 + x3581;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3619 = x3609 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3620 = x3610 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3621 = x3611 + x3601;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3622 = x3612 + x3604;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3623 = x3613 + x3619;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3624 = x3614 + x3597;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3625 = x3615 + x3595;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3626 = x3617 + x3600;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3627 = x3618 + x3598;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3628 = x3616 + x3620;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3629 = x3626 + x3608;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3630 = x3627 + x3606;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3631 = x3629 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3632 = x3630 * x3630;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3633 = x3630 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3634 = x3621 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3635 = x3622 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3636 = x3628 * x3628;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3637 = x3629 * x3629;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3638 = x3632 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3639 = -x3628;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3640 = x3624 + x3607;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3641 = x3625 + x3603;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3642 = x3590 + x3634;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3643 = x3629 + x3629;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3644 = x3630 + x3630;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x3645 = x3594 + x3635;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3646 = x3628 * x3644;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3647 = x3645 * x3643;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3648 = x3645 * x3645;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3649 = -x3645;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3650 = x3646 - x3637;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3651 = x3647 - x3636;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3652 = x3651 + x3638;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3653 = x3652 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3654 = x3653 * x3652;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3655 = x3650 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3656 = x3648 + x3655;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3657 = x3656 * x3656;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3658 = x3657 + x3654;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3659 = inv(x3658);
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3660 = x3656 * x3659;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3661 = x3652 * x3659;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3662 = x3628 * x3661;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3663 = x3645 * x3660;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3664 = x3639 * x3660;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3665 = x3649 * x3661;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3666 = x3629 * x3660;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3667 = x3630 * x3660;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3668 = x3631 * x3661;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3669 = x3633 * x3661;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3670 = x3662 - x3667;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3671 = x3664 - x3669;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3672 = x3663 + x3668;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x3673 = x3665 + x3666;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3674 = x3640 * x3670;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3675 = x3641 * x3670;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3676 = x3623 * x3670;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3677 = x3642 * x3672;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3678 = x3642 * x3673;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3679 = x3642 * x3670;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3680 = x3642 * x3671;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3681 = x3640 * x3672;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3682 = x3640 * x3673;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3683 = x3640 * x3671;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3684 = x3641 * x3672;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3685 = x3641 * x3673;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3686 = x3641 * x3671;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3687 = x3623 * x3672;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3688 = x3623 * x3673;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3689 = x3623 * x3671;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3690 = x3675 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3691 = x3674 + x3685;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3692 = x3676 + x3682;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3693 = x3678 + x3689;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3694 = x3679 + x3688;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3695 = x3680 + x3687;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3696 = x3691 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3697 = x3692 + x3686;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3698 = x3693 + x3681;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3699 = x3694 + x3683;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3700 = x3695 + x3696;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3701 = x3698 + x3690;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3702 = x3699 + x3684;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3703 = x3697 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x3704 = x3677 + x3703;
        extern_args[0] = x3704;
        extern_args[1] = x3700;
        extern_args[2] = x3701;
        extern_args[3] = x3702;
        extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
      }
    }
    // loc("zirgen/compiler/edsl/component.cpp":49:15)
    auto x3705 = arg0[17 * steps + ((cycle - 0) & mask)];
    assert(x3705 != Fp::invalid());
    if (x3705 != 0) {
      {
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3706 = arg3[0];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3707 = arg3[1];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3708 = arg3[10];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3709 = arg3[11];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3710 = arg3[12];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3711 = arg3[13];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3712 = arg3[14];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3713 = arg3[15];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3714 = arg3[16];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3715 = arg3[17];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3716 = arg3[18];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3717 = arg3[19];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3718 = arg3[2];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3719 = arg3[3];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3720 = arg3[4];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3721 = arg3[5];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3722 = arg3[6];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3723 = arg3[7];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3724 = arg3[8];
        // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
        auto x3725 = arg3[9];
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3726 = arg2[0 * steps + ((cycle - 0) & mask)];
        assert(x3726 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3727 = arg2[1 * steps + ((cycle - 0) & mask)];
        assert(x3727 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3728 = arg2[15 * steps + ((cycle - 0) & mask)];
        assert(x3728 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3729 = arg2[16 * steps + ((cycle - 0) & mask)];
        assert(x3729 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3730 = arg2[17 * steps + ((cycle - 0) & mask)];
        assert(x3730 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3731 = arg2[18 * steps + ((cycle - 0) & mask)];
        assert(x3731 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3732 = arg2[19 * steps + ((cycle - 0) & mask)];
        assert(x3732 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3733 = arg2[2 * steps + ((cycle - 0) & mask)];
        assert(x3733 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3734 = arg2[20 * steps + ((cycle - 0) & mask)];
        assert(x3734 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3735 = arg2[21 * steps + ((cycle - 0) & mask)];
        assert(x3735 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3736 = arg2[22 * steps + ((cycle - 0) & mask)];
        assert(x3736 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3737 = arg2[23 * steps + ((cycle - 0) & mask)];
        assert(x3737 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3738 = arg2[24 * steps + ((cycle - 0) & mask)];
        assert(x3738 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3739 = arg2[25 * steps + ((cycle - 0) & mask)];
        assert(x3739 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3740 = arg2[26 * steps + ((cycle - 0) & mask)];
        assert(x3740 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3741 = arg2[27 * steps + ((cycle - 0) & mask)];
        assert(x3741 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3742 = arg2[28 * steps + ((cycle - 0) & mask)];
        assert(x3742 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3743 = arg2[29 * steps + ((cycle - 0) & mask)];
        assert(x3743 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3744 = arg2[3 * steps + ((cycle - 0) & mask)];
        assert(x3744 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3745 = arg2[30 * steps + ((cycle - 0) & mask)];
        assert(x3745 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3746 = arg2[31 * steps + ((cycle - 0) & mask)];
        assert(x3746 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3747 = arg2[32 * steps + ((cycle - 0) & mask)];
        assert(x3747 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3748 = arg2[33 * steps + ((cycle - 0) & mask)];
        assert(x3748 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3749 = arg2[34 * steps + ((cycle - 0) & mask)];
        assert(x3749 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3750 = arg2[35 * steps + ((cycle - 0) & mask)];
        assert(x3750 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3751 = arg2[36 * steps + ((cycle - 0) & mask)];
        assert(x3751 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3752 = arg2[37 * steps + ((cycle - 0) & mask)];
        assert(x3752 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3753 = arg2[38 * steps + ((cycle - 0) & mask)];
        assert(x3753 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3754 = arg2[39 * steps + ((cycle - 0) & mask)];
        assert(x3754 != Fp::invalid());
        // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3755 = arg2[4 * steps + ((cycle - 0) & mask)];
        assert(x3755 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3756 = arg2[40 * steps + ((cycle - 0) & mask)];
        assert(x3756 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3757 = arg2[41 * steps + ((cycle - 0) & mask)];
        assert(x3757 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3758 = arg2[42 * steps + ((cycle - 0) & mask)];
        assert(x3758 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3759 = arg2[43 * steps + ((cycle - 0) & mask)];
        assert(x3759 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3760 = arg2[44 * steps + ((cycle - 0) & mask)];
        assert(x3760 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
        auto x3761 = arg2[45 * steps + ((cycle - 0) & mask)];
        assert(x3761 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3762 = arg2[46 * steps + ((cycle - 0) & mask)];
        assert(x3762 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3763 = arg2[47 * steps + ((cycle - 0) & mask)];
        assert(x3763 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3764 = arg2[48 * steps + ((cycle - 0) & mask)];
        assert(x3764 != Fp::invalid());
        // loc("top(recursion::Top)/mux(Mux)/macro_ops(recursion::MacroOp)/mux(Mux)/set_global(recursion::SetGlobal)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
        auto x3765 = arg2[49 * steps + ((cycle - 0) & mask)];
        assert(x3765 != Fp::invalid());
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3766 = x3706 * x3726;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3767 = x3706 * x3728;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3768 = x3706 * x3734;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3769 = x3706 * x3739;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3770 = x3706 * x3745;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3771 = x3706 * x3750;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3772 = x3706 * x3756;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3773 = x3706 * x3761;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3774 = x3707 * x3726;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3775 = x3707 * x3728;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3776 = x3707 * x3734;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3777 = x3707 * x3739;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3778 = x3707 * x3745;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3779 = x3707 * x3750;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3780 = x3707 * x3756;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3781 = x3707 * x3761;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3782 = x3708 * x3730;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3783 = x3708 * x3733;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3784 = x3708 * x3736;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3785 = x3708 * x3741;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3786 = x3708 * x3747;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3787 = x3708 * x3752;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3788 = x3708 * x3758;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3789 = x3708 * x3763;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3790 = x3709 * x3730;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3791 = x3709 * x3733;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3792 = x3709 * x3736;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3793 = x3709 * x3741;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3794 = x3709 * x3747;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3795 = x3709 * x3752;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3796 = x3709 * x3758;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3797 = x3709 * x3763;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3798 = x3711 * x3731;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3799 = x3711 * x3737;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3800 = x3711 * x3742;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3801 = x3711 * x3744;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3802 = x3711 * x3748;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3803 = x3711 * x3753;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3804 = x3711 * x3759;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3805 = x3711 * x3764;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3806 = x3712 * x3731;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3807 = x3712 * x3737;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3808 = x3712 * x3742;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3809 = x3712 * x3744;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3810 = x3712 * x3748;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3811 = x3712 * x3753;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3812 = x3712 * x3759;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3813 = x3712 * x3764;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3814 = x3713 * x3731;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3815 = x3713 * x3737;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3816 = x3713 * x3742;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3817 = x3713 * x3744;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3818 = x3713 * x3748;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3819 = x3713 * x3753;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3820 = x3713 * x3759;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3821 = x3713 * x3764;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3822 = x3715 * x3732;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3823 = x3715 * x3738;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3824 = x3715 * x3743;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3825 = x3715 * x3749;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3826 = x3715 * x3754;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3827 = x3715 * x3755;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3828 = x3715 * x3760;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3829 = x3715 * x3765;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3830 = x3716 * x3732;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3831 = x3716 * x3738;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3832 = x3716 * x3743;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3833 = x3716 * x3749;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3834 = x3716 * x3754;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3835 = x3716 * x3755;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3836 = x3716 * x3760;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3837 = x3716 * x3765;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3838 = x3717 * x3732;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3839 = x3717 * x3738;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3840 = x3717 * x3743;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3841 = x3717 * x3749;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3842 = x3717 * x3754;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3843 = x3717 * x3755;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3844 = x3717 * x3760;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3845 = x3717 * x3765;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3846 = x3718 * x3726;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3847 = x3718 * x3728;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3848 = x3718 * x3734;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3849 = x3718 * x3739;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3850 = x3718 * x3745;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3851 = x3718 * x3750;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3852 = x3718 * x3756;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3853 = x3718 * x3761;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3854 = x3719 * x3726;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3855 = x3719 * x3728;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3856 = x3719 * x3734;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3857 = x3719 * x3739;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3858 = x3719 * x3745;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3859 = x3719 * x3750;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3860 = x3719 * x3756;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3861 = x3719 * x3761;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3862 = x3721 * x3727;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3863 = x3721 * x3729;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3864 = x3721 * x3735;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3865 = x3721 * x3740;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3866 = x3721 * x3746;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3867 = x3721 * x3751;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3868 = x3721 * x3757;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3869 = x3721 * x3762;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3870 = x3722 * x3727;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3871 = x3722 * x3729;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3872 = x3722 * x3735;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3873 = x3722 * x3740;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3874 = x3722 * x3746;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3875 = x3722 * x3751;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3876 = x3722 * x3757;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3877 = x3722 * x3762;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3878 = x3723 * x3727;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3879 = x3723 * x3729;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3880 = x3723 * x3735;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3881 = x3723 * x3740;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3882 = x3723 * x3746;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3883 = x3723 * x3751;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3884 = x3723 * x3757;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3885 = x3723 * x3762;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3886 = x3725 * x3730;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3887 = x3725 * x3733;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3888 = x3725 * x3736;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3889 = x3725 * x3741;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3890 = x3725 * x3747;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3891 = x3725 * x3752;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3892 = x3725 * x3758;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3893 = x3725 * x3763;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3894 = x3710 * x3731;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3895 = x3710 * x3737;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3896 = x3710 * x3742;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3897 = x3710 * x3744;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3898 = x3710 * x3748;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3899 = x3710 * x3753;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3900 = x3710 * x3759;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3901 = x3710 * x3764;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3902 = x3714 * x3732;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3903 = x3714 * x3738;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3904 = x3714 * x3743;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3905 = x3714 * x3749;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3906 = x3714 * x3754;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3907 = x3714 * x3755;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3908 = x3714 * x3760;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3909 = x3714 * x3765;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3910 = x3720 * x3727;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3911 = x3720 * x3729;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3912 = x3720 * x3735;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3913 = x3720 * x3740;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3914 = x3720 * x3746;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3915 = x3720 * x3751;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3916 = x3720 * x3757;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3917 = x3720 * x3762;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3918 = x3724 * x3730;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3919 = x3724 * x3733;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3920 = x3724 * x3736;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3921 = x3724 * x3741;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3922 = x3724 * x3747;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3923 = x3724 * x3752;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3924 = x3724 * x3758;
        // loc("./zirgen/components/plonk.h":230:23)
        auto x3925 = x3724 * x3763;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3926 = x3766 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3927 = x3767 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3928 = x3768 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3929 = x3769 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3930 = x3770 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3931 = x3771 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3932 = x3772 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3933 = x3773 + x2;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3934 = x3926 + x3910;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3935 = x3927 + x3911;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3936 = x3928 + x3912;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3937 = x3929 + x3913;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3938 = x3930 + x3914;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3939 = x3931 + x3915;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3940 = x3932 + x3916;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3941 = x3933 + x3917;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3942 = x3934 + x3919;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3943 = x3935 + x3918;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3944 = x3936 + x3920;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3945 = x3937 + x3921;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3946 = x3938 + x3922;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3947 = x3939 + x3923;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3948 = x3940 + x3924;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3949 = x3941 + x3925;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3950 = x3774 + x3862;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3951 = x3775 + x3863;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3952 = x3776 + x3864;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3953 = x3777 + x3865;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3954 = x3778 + x3866;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3955 = x3779 + x3867;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3956 = x3780 + x3868;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3957 = x3781 + x3869;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3958 = x3846 + x3870;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3959 = x3847 + x3871;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3960 = x3848 + x3872;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3961 = x3849 + x3873;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3962 = x3850 + x3874;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3963 = x3851 + x3875;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3964 = x3852 + x3876;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3965 = x3853 + x3877;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3966 = x3854 + x3878;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3967 = x3855 + x3879;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3968 = x3856 + x3880;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3969 = x3857 + x3881;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3970 = x3858 + x3882;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3971 = x3859 + x3883;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3972 = x3860 + x3884;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3973 = x3861 + x3885;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3974 = x3942 + x3897;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3975 = x3943 + x3894;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3976 = x3944 + x3895;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3977 = x3945 + x3896;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3978 = x3946 + x3898;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3979 = x3947 + x3899;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3980 = x3948 + x3900;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3981 = x3949 + x3901;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3982 = x3950 + x3887;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3983 = x3951 + x3886;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3984 = x3952 + x3888;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3985 = x3953 + x3889;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3986 = x3954 + x3890;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3987 = x3955 + x3891;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3988 = x3956 + x3892;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3989 = x3957 + x3893;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3990 = x3958 + x3783;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3991 = x3959 + x3782;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3992 = x3960 + x3784;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3993 = x3961 + x3785;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3994 = x3962 + x3786;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3995 = x3963 + x3787;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3996 = x3964 + x3788;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3997 = x3965 + x3789;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3998 = x3966 + x3791;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x3999 = x3967 + x3790;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4000 = x3968 + x3792;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4001 = x3969 + x3793;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4002 = x3970 + x3794;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4003 = x3971 + x3795;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4004 = x3972 + x3796;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4005 = x3973 + x3797;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4006 = x3974 + x3907;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4007 = x3976 + x3903;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4008 = x3978 + x3905;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4009 = x3980 + x3908;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4010 = x3975 + x3902;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4011 = x3977 + x3904;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4012 = x3979 + x3906;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4013 = x3981 + x3909;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4014 = x3982 + x3801;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4015 = x3983 + x3798;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4016 = x3984 + x3799;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4017 = x3985 + x3800;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4018 = x3986 + x3802;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4019 = x3987 + x3803;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4020 = x3988 + x3804;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4021 = x3989 + x3805;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4022 = x3990 + x3809;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4023 = x3991 + x3806;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4024 = x3992 + x3807;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4025 = x3993 + x3808;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4026 = x3994 + x3810;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4027 = x3995 + x3811;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4028 = x3996 + x3812;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4029 = x3997 + x3813;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4030 = x3998 + x3817;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4031 = x3999 + x3814;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4032 = x4000 + x3815;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4033 = x4001 + x3816;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4034 = x4002 + x3818;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4035 = x4003 + x3819;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4036 = x4004 + x3820;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4037 = x4005 + x3821;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4038 = x4014 + x3827;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4039 = x4016 + x3823;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4040 = x4018 + x3825;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4041 = x4020 + x3828;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4042 = x4022 + x3835;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4043 = x4024 + x3831;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4044 = x4026 + x3833;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4045 = x4028 + x3836;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4046 = x4030 + x3843;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4047 = x4032 + x3839;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4048 = x4034 + x3841;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4049 = x4036 + x3844;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4050 = x4015 + x3822;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4051 = x4017 + x3824;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4052 = x4019 + x3826;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4053 = x4021 + x3829;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4054 = x4023 + x3830;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4055 = x4025 + x3832;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4056 = x4027 + x3834;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4057 = x4029 + x3837;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4058 = x4031 + x3838;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4059 = x4033 + x3840;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4060 = x4035 + x3842;
        // loc("./zirgen/components/plonk.h":230:17)
        auto x4061 = x4037 + x3845;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4062 = x4050 * x4047;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4063 = x4051 * x4048;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4064 = x4052 * x4049;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4065 = x4053 * x4046;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4066 = x4050 * x4039;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4067 = x4050 * x4043;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4068 = x4050 * x4007;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4069 = x4051 * x4040;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4070 = x4051 * x4044;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4071 = x4051 * x4008;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4072 = x4052 * x4041;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4073 = x4052 * x4045;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4074 = x4052 * x4009;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4075 = x4053 * x4038;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4076 = x4053 * x4042;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4077 = x4053 * x4006;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4078 = x4054 * x4047;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4079 = x4055 * x4048;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4080 = x4056 * x4049;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4081 = x4057 * x4046;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4082 = x4058 * x4047;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4083 = x4059 * x4048;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4084 = x4060 * x4049;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4085 = x4061 * x4046;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4086 = x4010 * x4039;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4087 = x4010 * x4043;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4088 = x4010 * x4047;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4089 = x4010 * x4007;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4090 = x4011 * x4040;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4091 = x4011 * x4044;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4092 = x4011 * x4048;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4093 = x4011 * x4008;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4094 = x4012 * x4041;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4095 = x4012 * x4045;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4096 = x4012 * x4049;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4097 = x4012 * x4009;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4098 = x4013 * x4038;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4099 = x4013 * x4042;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4100 = x4013 * x4046;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4101 = x4013 * x4006;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4102 = x4054 * x4039;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4103 = x4054 * x4043;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4104 = x4054 * x4007;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4105 = x4055 * x4040;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4106 = x4055 * x4044;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4107 = x4055 * x4008;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4108 = x4056 * x4041;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4109 = x4056 * x4045;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4110 = x4056 * x4009;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4111 = x4057 * x4038;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4112 = x4057 * x4042;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4113 = x4057 * x4006;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4114 = x4058 * x4039;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4115 = x4058 * x4043;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4116 = x4058 * x4007;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4117 = x4059 * x4040;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4118 = x4059 * x4044;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4119 = x4059 * x4008;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4120 = x4060 * x4041;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4121 = x4060 * x4045;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4122 = x4060 * x4009;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4123 = x4061 * x4038;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4124 = x4061 * x4042;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4125 = x4061 * x4006;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4126 = x4082 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4127 = x4083 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4128 = x4084 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4129 = x4085 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4130 = x4078 + x4115;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4131 = x4079 + x4118;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4132 = x4080 + x4121;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4133 = x4081 + x4124;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4134 = x4062 + x4103;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4135 = x4063 + x4106;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4136 = x4064 + x4109;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4137 = x4065 + x4112;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4138 = x4086 + x4068;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4139 = x4087 + x4066;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4140 = x4088 + x4067;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4141 = x4090 + x4071;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4142 = x4091 + x4069;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4143 = x4092 + x4070;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4144 = x4094 + x4074;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4145 = x4095 + x4072;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4146 = x4096 + x4073;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4147 = x4098 + x4077;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4148 = x4099 + x4075;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4149 = x4100 + x4076;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4150 = x4130 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4151 = x4131 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4152 = x4132 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4153 = x4133 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4154 = x4134 + x4114;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4155 = x4135 + x4117;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4156 = x4136 + x4120;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4157 = x4137 + x4123;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4158 = x4138 + x4150;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4159 = x4139 + x4104;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4160 = x4140 + x4102;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4161 = x4142 + x4107;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4162 = x4143 + x4105;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4163 = x4145 + x4110;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4164 = x4146 + x4108;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4165 = x4148 + x4113;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4166 = x4149 + x4111;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4167 = x4144 + x4152;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4168 = x4147 + x4153;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4169 = x4163 + x4128;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4170 = x4164 + x4122;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4171 = x4165 + x4129;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4172 = x4166 + x4125;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4173 = x4161 + x4127;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4174 = x4162 + x4119;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4175 = x4141 + x4151;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4176 = x4169 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4177 = x4170 * x4170;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4178 = x4170 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4179 = x4171 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4180 = x4172 * x4172;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4181 = x4172 * x1;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4182 = x4154 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4183 = x4155 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4184 = x4156 * x0;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4185 = x4157 * x0;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4186 = x4167 * x4167;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4187 = x4168 * x4168;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4188 = x4169 * x4169;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4189 = x4171 * x4171;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4190 = x4177 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4191 = x4180 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4192 = -x4167;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4193 = -x4168;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4194 = x4159 + x4126;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4195 = x4160 + x4116;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4196 = x4089 + x4182;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4197 = x4169 + x4169;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4198 = x4170 + x4170;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4199 = x4171 + x4171;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4200 = x4172 + x4172;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4201 = x4097 + x4184;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4202 = x4101 + x4185;
        // loc("./zirgen/components/plonk.h":232:16)
        auto x4203 = x4093 + x4183;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4204 = x4167 * x4198;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4205 = x4168 * x4200;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4206 = x4201 * x4197;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4207 = x4201 * x4201;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4208 = x4202 * x4199;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4209 = x4202 * x4202;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4210 = -x4201;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4211 = -x4202;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4212 = x4204 - x4188;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4213 = x4205 - x4189;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4214 = x4206 - x4186;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4215 = x4208 - x4187;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4216 = x4214 + x4190;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4217 = x4215 + x4191;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4218 = x4216 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4219 = x4217 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4220 = x4218 * x4216;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4221 = x4219 * x4217;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4222 = x4212 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4223 = x4213 * x1;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4224 = x4207 + x4222;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4225 = x4209 + x4223;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4226 = x4224 * x4224;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4227 = x4225 * x4225;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4228 = x4226 + x4220;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4229 = x4227 + x4221;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4230 = inv(x4228);
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4231 = inv(x4229);
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4232 = x4224 * x4230;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4233 = x4225 * x4231;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4234 = x4216 * x4230;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4235 = x4217 * x4231;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4236 = x4167 * x4234;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4237 = x4168 * x4235;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4238 = x4201 * x4232;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4239 = x4202 * x4233;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4240 = x4192 * x4232;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4241 = x4193 * x4233;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4242 = x4210 * x4234;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4243 = x4211 * x4235;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4244 = x4169 * x4232;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4245 = x4170 * x4232;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4246 = x4171 * x4233;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4247 = x4172 * x4233;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4248 = x4176 * x4234;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4249 = x4178 * x4234;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4250 = x4179 * x4235;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4251 = x4181 * x4235;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4252 = x4236 - x4245;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4253 = x4237 - x4247;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4254 = x4240 - x4249;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4255 = x4241 - x4251;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4256 = x4238 + x4248;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4257 = x4239 + x4250;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4258 = x4242 + x4244;
        // loc("./zirgen/components/plonk.h":274:42)
        auto x4259 = x4243 + x4246;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4260 = x4194 * x4252;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4261 = x4195 * x4252;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4262 = x4158 * x4252;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4263 = x4196 * x4256;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4264 = x4196 * x4258;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4265 = x4196 * x4252;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4266 = x4196 * x4254;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4267 = x4194 * x4256;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4268 = x4194 * x4258;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4269 = x4194 * x4254;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4270 = x4195 * x4256;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4271 = x4195 * x4258;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4272 = x4195 * x4254;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4273 = x4158 * x4256;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4274 = x4158 * x4258;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4275 = x4158 * x4254;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4276 = x4261 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4277 = x4260 + x4271;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4278 = x4262 + x4268;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4279 = x4264 + x4275;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4280 = x4265 + x4274;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4281 = x4266 + x4273;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4282 = x4277 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4283 = x4278 + x4272;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4284 = x4279 + x4267;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4285 = x4280 + x4269;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4286 = x4281 + x4282;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4287 = x4286 * x4174;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4288 = x4283 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4289 = x4286 * x4173;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4290 = x4286 * x4175;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4291 = x4286 * x4203;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4292 = x4284 + x4276;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4293 = x4285 + x4270;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4294 = x4263 + x4288;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4295 = x4292 * x4174;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4296 = x4293 * x4174;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4297 = x4294 * x4173;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4298 = x4294 * x4174;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4299 = x4294 * x4175;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4300 = x4294 * x4203;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4301 = x4292 * x4173;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4302 = x4292 * x4175;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4303 = x4292 * x4203;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4304 = x4293 * x4173;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4305 = x4293 * x4175;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4306 = x4293 * x4203;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4307 = x4296 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4308 = x4295 + x4304;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4309 = x4287 + x4301;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4310 = x4297 + x4290;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4311 = x4298 + x4289;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4312 = x4299 + x4291;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4313 = x4308 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4314 = x4309 + x4305;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4315 = x4310 + x4303;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4316 = x4311 + x4302;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4317 = x4312 + x4313;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4318 = x4317 * x4253;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4319 = x4314 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4320 = x4317 * x4257;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4321 = x4317 * x4259;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4322 = x4317 * x4255;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4323 = x4315 + x4307;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4324 = x4316 + x4306;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4325 = x4300 + x4319;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4326 = x4323 * x4253;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4327 = x4324 * x4253;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4328 = x4325 * x4257;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4329 = x4325 * x4259;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4330 = x4325 * x4253;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4331 = x4325 * x4255;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4332 = x4323 * x4257;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4333 = x4323 * x4259;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4334 = x4323 * x4255;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4335 = x4324 * x4257;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4336 = x4324 * x4259;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4337 = x4324 * x4255;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4338 = x4327 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4339 = x4326 + x4336;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4340 = x4318 + x4333;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4341 = x4329 + x4322;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4342 = x4330 + x4321;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4343 = x4331 + x4320;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4344 = x4339 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4345 = x4340 + x4337;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4346 = x4341 + x4332;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4347 = x4342 + x4334;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4348 = x4343 + x4344;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4349 = x4346 + x4338;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4350 = x4347 + x4335;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4351 = x4345 * x0;
        // loc("./zirgen/components/plonk.h":274:16)
        auto x4352 = x4328 + x4351;
        extern_args[0] = x4352;
        extern_args[1] = x4348;
        extern_args[2] = x4349;
        extern_args[3] = x4350;
        extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
      }
    }
  }
  if (x6 != 0) {
    {
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4353 = arg3[0];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4354 = arg3[1];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4355 = arg3[10];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4356 = arg3[11];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4357 = arg3[12];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4358 = arg3[13];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4359 = arg3[14];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4360 = arg3[15];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4361 = arg3[16];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4362 = arg3[17];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4363 = arg3[18];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4364 = arg3[19];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4365 = arg3[2];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4366 = arg3[3];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4367 = arg3[4];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4368 = arg3[5];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4369 = arg3[6];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4370 = arg3[7];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4371 = arg3[8];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x4372 = arg3[9];
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4373 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x4373 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4374 = arg2[1 * steps + ((cycle - 0) & mask)];
      assert(x4374 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4375 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x4375 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4376 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x4376 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4377 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x4377 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4378 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x4378 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4379 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x4379 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4380 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x4380 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4381 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x4381 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4382 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x4382 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4383 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x4383 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4384 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x4384 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4385 = arg2[2 * steps + ((cycle - 0) & mask)];
      assert(x4385 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4386 = arg2[20 * steps + ((cycle - 0) & mask)];
      assert(x4386 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4387 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x4387 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4388 = arg2[22 * steps + ((cycle - 0) & mask)];
      assert(x4388 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4389 = arg2[23 * steps + ((cycle - 0) & mask)];
      assert(x4389 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4390 = arg2[24 * steps + ((cycle - 0) & mask)];
      assert(x4390 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4391 = arg2[25 * steps + ((cycle - 0) & mask)];
      assert(x4391 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4392 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x4392 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4393 = arg2[27 * steps + ((cycle - 0) & mask)];
      assert(x4393 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4394 = arg2[28 * steps + ((cycle - 0) & mask)];
      assert(x4394 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4395 = arg2[29 * steps + ((cycle - 0) & mask)];
      assert(x4395 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4396 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x4396 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4397 = arg2[30 * steps + ((cycle - 0) & mask)];
      assert(x4397 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4398 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x4398 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4399 = arg2[32 * steps + ((cycle - 0) & mask)];
      assert(x4399 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4400 = arg2[33 * steps + ((cycle - 0) & mask)];
      assert(x4400 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4401 = arg2[34 * steps + ((cycle - 0) & mask)];
      assert(x4401 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4402 = arg2[35 * steps + ((cycle - 0) & mask)];
      assert(x4402 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4403 = arg2[36 * steps + ((cycle - 0) & mask)];
      assert(x4403 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4404 = arg2[37 * steps + ((cycle - 0) & mask)];
      assert(x4404 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4405 = arg2[38 * steps + ((cycle - 0) & mask)];
      assert(x4405 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4406 = arg2[39 * steps + ((cycle - 0) & mask)];
      assert(x4406 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4407 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x4407 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4408 = arg2[40 * steps + ((cycle - 0) & mask)];
      assert(x4408 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4409 = arg2[41 * steps + ((cycle - 0) & mask)];
      assert(x4409 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4410 = arg2[42 * steps + ((cycle - 0) & mask)];
      assert(x4410 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4411 = arg2[43 * steps + ((cycle - 0) & mask)];
      assert(x4411 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4412 = arg2[44 * steps + ((cycle - 0) & mask)];
      assert(x4412 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4413 = arg2[45 * steps + ((cycle - 0) & mask)];
      assert(x4413 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4414 = arg2[46 * steps + ((cycle - 0) & mask)];
      assert(x4414 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4415 = arg2[47 * steps + ((cycle - 0) & mask)];
      assert(x4415 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4416 = arg2[48 * steps + ((cycle - 0) & mask)];
      assert(x4416 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4417 = arg2[49 * steps + ((cycle - 0) & mask)];
      assert(x4417 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4418 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x4418 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4419 = arg2[50 * steps + ((cycle - 0) & mask)];
      assert(x4419 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4420 = arg2[51 * steps + ((cycle - 0) & mask)];
      assert(x4420 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4421 = arg2[52 * steps + ((cycle - 0) & mask)];
      assert(x4421 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4422 = arg2[53 * steps + ((cycle - 0) & mask)];
      assert(x4422 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4423 = arg2[54 * steps + ((cycle - 0) & mask)];
      assert(x4423 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4424 = arg2[55 * steps + ((cycle - 0) & mask)];
      assert(x4424 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4425 = arg2[56 * steps + ((cycle - 0) & mask)];
      assert(x4425 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4426 = arg2[57 * steps + ((cycle - 0) & mask)];
      assert(x4426 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4427 = arg2[58 * steps + ((cycle - 0) & mask)];
      assert(x4427 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4428 = arg2[59 * steps + ((cycle - 0) & mask)];
      assert(x4428 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4429 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x4429 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4430 = arg2[60 * steps + ((cycle - 0) & mask)];
      assert(x4430 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4431 = arg2[61 * steps + ((cycle - 0) & mask)];
      assert(x4431 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4432 = arg2[62 * steps + ((cycle - 0) & mask)];
      assert(x4432 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4433 = arg2[63 * steps + ((cycle - 0) & mask)];
      assert(x4433 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4434 = arg2[64 * steps + ((cycle - 0) & mask)];
      assert(x4434 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4435 = arg2[65 * steps + ((cycle - 0) & mask)];
      assert(x4435 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4436 = arg2[66 * steps + ((cycle - 0) & mask)];
      assert(x4436 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4437 = arg2[67 * steps + ((cycle - 0) & mask)];
      assert(x4437 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4438 = arg2[68 * steps + ((cycle - 0) & mask)];
      assert(x4438 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4439 = arg2[69 * steps + ((cycle - 0) & mask)];
      assert(x4439 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4440 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x4440 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4441 = arg2[70 * steps + ((cycle - 0) & mask)];
      assert(x4441 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4442 = arg2[71 * steps + ((cycle - 0) & mask)];
      assert(x4442 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4443 = arg2[72 * steps + ((cycle - 0) & mask)];
      assert(x4443 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4444 = arg2[73 * steps + ((cycle - 0) & mask)];
      assert(x4444 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4445 = arg2[74 * steps + ((cycle - 0) & mask)];
      assert(x4445 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4446 = arg2[75 * steps + ((cycle - 0) & mask)];
      assert(x4446 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4447 = arg2[76 * steps + ((cycle - 0) & mask)];
      assert(x4447 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4448 = arg2[77 * steps + ((cycle - 0) & mask)];
      assert(x4448 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4449 = arg2[78 * steps + ((cycle - 0) & mask)];
      assert(x4449 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4450 = arg2[79 * steps + ((cycle - 0) & mask)];
      assert(x4450 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4451 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x4451 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4452 = arg2[80 * steps + ((cycle - 0) & mask)];
      assert(x4452 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4453 = arg2[81 * steps + ((cycle - 0) & mask)];
      assert(x4453 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4454 = arg2[82 * steps + ((cycle - 0) & mask)];
      assert(x4454 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4455 = arg2[83 * steps + ((cycle - 0) & mask)];
      assert(x4455 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4456 = arg2[84 * steps + ((cycle - 0) & mask)];
      assert(x4456 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x4457 = arg2[85 * steps + ((cycle - 0) & mask)];
      assert(x4457 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4458 = arg2[86 * steps + ((cycle - 0) & mask)];
      assert(x4458 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4459 = arg2[87 * steps + ((cycle - 0) & mask)];
      assert(x4459 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4460 = arg2[88 * steps + ((cycle - 0) & mask)];
      assert(x4460 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4461 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x4461 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_load(recursion::Poseidon2Load)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x4462 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x4462 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4463 = x4353 * x4373;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4464 = x4353 * x4375;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4465 = x4353 * x4380;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4466 = x4353 * x4386;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4467 = x4353 * x4391;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4468 = x4353 * x4397;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4469 = x4353 * x4402;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4470 = x4353 * x4408;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4471 = x4353 * x4413;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4472 = x4353 * x4418;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4473 = x4353 * x4419;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4474 = x4353 * x4424;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4475 = x4353 * x4430;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4476 = x4353 * x4435;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4477 = x4353 * x4441;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4478 = x4353 * x4446;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4479 = x4353 * x4452;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4480 = x4353 * x4457;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4481 = x4354 * x4373;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4482 = x4354 * x4375;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4483 = x4354 * x4380;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4484 = x4354 * x4386;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4485 = x4354 * x4391;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4486 = x4354 * x4397;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4487 = x4354 * x4402;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4488 = x4354 * x4408;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4489 = x4354 * x4413;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4490 = x4354 * x4418;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4491 = x4354 * x4419;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4492 = x4354 * x4424;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4493 = x4354 * x4430;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4494 = x4354 * x4435;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4495 = x4354 * x4441;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4496 = x4354 * x4446;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4497 = x4354 * x4452;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4498 = x4354 * x4457;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4499 = x4355 * x4377;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4500 = x4355 * x4382;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4501 = x4355 * x4385;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4502 = x4355 * x4388;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4503 = x4355 * x4393;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4504 = x4355 * x4399;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4505 = x4355 * x4404;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4506 = x4355 * x4410;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4507 = x4355 * x4415;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4508 = x4355 * x4421;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4509 = x4355 * x4426;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4510 = x4355 * x4432;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4511 = x4355 * x4437;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4512 = x4355 * x4440;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4513 = x4355 * x4443;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4514 = x4355 * x4448;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4515 = x4355 * x4454;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4516 = x4355 * x4459;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4517 = x4356 * x4377;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4518 = x4356 * x4382;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4519 = x4356 * x4385;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4520 = x4356 * x4388;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4521 = x4356 * x4393;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4522 = x4356 * x4399;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4523 = x4356 * x4404;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4524 = x4356 * x4410;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4525 = x4356 * x4415;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4526 = x4356 * x4421;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4527 = x4356 * x4426;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4528 = x4356 * x4432;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4529 = x4356 * x4437;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4530 = x4356 * x4440;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4531 = x4356 * x4443;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4532 = x4356 * x4448;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4533 = x4356 * x4454;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4534 = x4356 * x4459;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4535 = x4358 * x4378;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4536 = x4358 * x4383;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4537 = x4358 * x4389;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4538 = x4358 * x4394;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4539 = x4358 * x4396;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4540 = x4358 * x4400;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4541 = x4358 * x4405;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4542 = x4358 * x4411;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4543 = x4358 * x4416;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4544 = x4358 * x4422;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4545 = x4358 * x4427;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4546 = x4358 * x4433;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4547 = x4358 * x4438;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4548 = x4358 * x4444;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4549 = x4358 * x4449;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4550 = x4358 * x4451;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4551 = x4358 * x4455;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4552 = x4358 * x4460;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4553 = x4359 * x4378;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4554 = x4359 * x4383;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4555 = x4359 * x4389;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4556 = x4359 * x4394;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4557 = x4359 * x4396;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4558 = x4359 * x4400;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4559 = x4359 * x4405;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4560 = x4359 * x4411;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4561 = x4359 * x4416;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4562 = x4359 * x4422;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4563 = x4359 * x4427;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4564 = x4359 * x4433;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4565 = x4359 * x4438;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4566 = x4359 * x4444;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4567 = x4359 * x4449;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4568 = x4359 * x4451;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4569 = x4359 * x4455;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4570 = x4359 * x4460;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4571 = x4360 * x4378;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4572 = x4360 * x4383;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4573 = x4360 * x4389;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4574 = x4360 * x4394;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4575 = x4360 * x4396;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4576 = x4360 * x4400;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4577 = x4360 * x4405;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4578 = x4360 * x4411;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4579 = x4360 * x4416;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4580 = x4360 * x4422;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4581 = x4360 * x4427;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4582 = x4360 * x4433;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4583 = x4360 * x4438;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4584 = x4360 * x4444;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4585 = x4360 * x4449;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4586 = x4360 * x4451;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4587 = x4360 * x4455;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4588 = x4360 * x4460;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4589 = x4362 * x4379;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4590 = x4362 * x4384;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4591 = x4362 * x4390;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4592 = x4362 * x4395;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4593 = x4362 * x4401;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4594 = x4362 * x4406;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4595 = x4362 * x4407;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4596 = x4362 * x4412;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4597 = x4362 * x4417;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4598 = x4362 * x4423;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4599 = x4362 * x4428;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4600 = x4362 * x4434;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4601 = x4362 * x4439;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4602 = x4362 * x4445;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4603 = x4362 * x4450;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4604 = x4362 * x4456;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4605 = x4362 * x4461;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4606 = x4362 * x4462;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4607 = x4363 * x4379;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4608 = x4363 * x4384;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4609 = x4363 * x4390;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4610 = x4363 * x4395;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4611 = x4363 * x4401;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4612 = x4363 * x4406;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4613 = x4363 * x4407;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4614 = x4363 * x4412;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4615 = x4363 * x4417;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4616 = x4363 * x4423;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4617 = x4363 * x4428;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4618 = x4363 * x4434;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4619 = x4363 * x4439;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4620 = x4363 * x4445;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4621 = x4363 * x4450;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4622 = x4363 * x4456;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4623 = x4363 * x4461;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4624 = x4363 * x4462;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4625 = x4364 * x4379;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4626 = x4364 * x4384;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4627 = x4364 * x4390;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4628 = x4364 * x4395;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4629 = x4364 * x4401;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4630 = x4364 * x4406;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4631 = x4364 * x4407;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4632 = x4364 * x4412;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4633 = x4364 * x4417;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4634 = x4364 * x4423;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4635 = x4364 * x4428;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4636 = x4364 * x4434;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4637 = x4364 * x4439;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4638 = x4364 * x4445;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4639 = x4364 * x4450;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4640 = x4364 * x4456;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4641 = x4364 * x4461;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4642 = x4364 * x4462;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4643 = x4365 * x4373;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4644 = x4365 * x4375;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4645 = x4365 * x4380;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4646 = x4365 * x4386;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4647 = x4365 * x4391;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4648 = x4365 * x4397;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4649 = x4365 * x4402;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4650 = x4365 * x4408;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4651 = x4365 * x4413;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4652 = x4365 * x4418;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4653 = x4365 * x4419;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4654 = x4365 * x4424;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4655 = x4365 * x4430;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4656 = x4365 * x4435;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4657 = x4365 * x4441;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4658 = x4365 * x4446;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4659 = x4365 * x4452;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4660 = x4365 * x4457;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4661 = x4366 * x4373;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4662 = x4366 * x4375;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4663 = x4366 * x4380;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4664 = x4366 * x4386;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4665 = x4366 * x4391;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4666 = x4366 * x4397;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4667 = x4366 * x4402;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4668 = x4366 * x4408;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4669 = x4366 * x4413;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4670 = x4366 * x4418;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4671 = x4366 * x4419;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4672 = x4366 * x4424;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4673 = x4366 * x4430;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4674 = x4366 * x4435;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4675 = x4366 * x4441;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4676 = x4366 * x4446;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4677 = x4366 * x4452;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4678 = x4366 * x4457;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4679 = x4368 * x4374;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4680 = x4368 * x4376;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4681 = x4368 * x4381;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4682 = x4368 * x4387;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4683 = x4368 * x4392;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4684 = x4368 * x4398;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4685 = x4368 * x4403;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4686 = x4368 * x4409;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4687 = x4368 * x4414;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4688 = x4368 * x4420;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4689 = x4368 * x4425;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4690 = x4368 * x4429;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4691 = x4368 * x4431;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4692 = x4368 * x4436;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4693 = x4368 * x4442;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4694 = x4368 * x4447;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4695 = x4368 * x4453;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4696 = x4368 * x4458;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4697 = x4369 * x4374;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4698 = x4369 * x4376;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4699 = x4369 * x4381;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4700 = x4369 * x4387;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4701 = x4369 * x4392;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4702 = x4369 * x4398;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4703 = x4369 * x4403;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4704 = x4369 * x4409;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4705 = x4369 * x4414;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4706 = x4369 * x4420;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4707 = x4369 * x4425;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4708 = x4369 * x4429;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4709 = x4369 * x4431;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4710 = x4369 * x4436;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4711 = x4369 * x4442;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4712 = x4369 * x4447;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4713 = x4369 * x4453;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4714 = x4369 * x4458;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4715 = x4370 * x4374;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4716 = x4370 * x4376;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4717 = x4370 * x4381;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4718 = x4370 * x4387;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4719 = x4370 * x4392;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4720 = x4370 * x4398;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4721 = x4370 * x4403;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4722 = x4370 * x4409;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4723 = x4370 * x4414;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4724 = x4370 * x4420;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4725 = x4370 * x4425;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4726 = x4370 * x4429;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4727 = x4370 * x4431;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4728 = x4370 * x4436;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4729 = x4370 * x4442;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4730 = x4370 * x4447;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4731 = x4370 * x4453;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4732 = x4370 * x4458;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4733 = x4372 * x4377;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4734 = x4372 * x4382;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4735 = x4372 * x4385;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4736 = x4372 * x4388;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4737 = x4372 * x4393;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4738 = x4372 * x4399;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4739 = x4372 * x4404;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4740 = x4372 * x4410;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4741 = x4372 * x4415;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4742 = x4372 * x4421;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4743 = x4372 * x4426;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4744 = x4372 * x4432;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4745 = x4372 * x4437;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4746 = x4372 * x4440;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4747 = x4372 * x4443;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4748 = x4372 * x4448;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4749 = x4372 * x4454;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4750 = x4372 * x4459;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4751 = x4357 * x4378;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4752 = x4357 * x4383;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4753 = x4357 * x4389;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4754 = x4357 * x4394;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4755 = x4357 * x4396;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4756 = x4357 * x4400;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4757 = x4357 * x4405;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4758 = x4357 * x4411;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4759 = x4357 * x4416;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4760 = x4357 * x4422;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4761 = x4357 * x4427;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4762 = x4357 * x4433;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4763 = x4357 * x4438;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4764 = x4357 * x4444;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4765 = x4357 * x4449;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4766 = x4357 * x4451;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4767 = x4357 * x4455;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4768 = x4357 * x4460;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4769 = x4361 * x4379;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4770 = x4361 * x4384;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4771 = x4361 * x4390;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4772 = x4361 * x4395;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4773 = x4361 * x4401;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4774 = x4361 * x4406;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4775 = x4361 * x4407;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4776 = x4361 * x4412;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4777 = x4361 * x4417;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4778 = x4361 * x4423;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4779 = x4361 * x4428;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4780 = x4361 * x4434;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4781 = x4361 * x4439;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4782 = x4361 * x4445;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4783 = x4361 * x4450;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4784 = x4361 * x4456;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4785 = x4361 * x4461;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4786 = x4361 * x4462;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4787 = x4367 * x4374;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4788 = x4367 * x4376;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4789 = x4367 * x4381;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4790 = x4367 * x4387;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4791 = x4367 * x4392;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4792 = x4367 * x4398;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4793 = x4367 * x4403;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4794 = x4367 * x4409;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4795 = x4367 * x4414;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4796 = x4367 * x4420;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4797 = x4367 * x4425;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4798 = x4367 * x4429;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4799 = x4367 * x4431;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4800 = x4367 * x4436;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4801 = x4367 * x4442;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4802 = x4367 * x4447;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4803 = x4367 * x4453;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4804 = x4367 * x4458;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4805 = x4371 * x4377;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4806 = x4371 * x4382;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4807 = x4371 * x4385;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4808 = x4371 * x4388;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4809 = x4371 * x4393;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4810 = x4371 * x4399;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4811 = x4371 * x4404;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4812 = x4371 * x4410;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4813 = x4371 * x4415;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4814 = x4371 * x4421;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4815 = x4371 * x4426;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4816 = x4371 * x4432;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4817 = x4371 * x4437;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4818 = x4371 * x4440;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4819 = x4371 * x4443;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4820 = x4371 * x4448;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4821 = x4371 * x4454;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x4822 = x4371 * x4459;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4823 = x4463 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4824 = x4464 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4825 = x4465 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4826 = x4466 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4827 = x4467 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4828 = x4468 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4829 = x4469 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4830 = x4470 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4831 = x4471 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4832 = x4472 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4833 = x4473 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4834 = x4474 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4835 = x4475 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4836 = x4476 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4837 = x4477 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4838 = x4478 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4839 = x4479 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4840 = x4480 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4841 = x4823 + x4787;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4842 = x4824 + x4788;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4843 = x4825 + x4789;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4844 = x4826 + x4790;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4845 = x4827 + x4791;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4846 = x4828 + x4792;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4847 = x4829 + x4793;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4848 = x4830 + x4794;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4849 = x4831 + x4795;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4850 = x4832 + x4798;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4851 = x4833 + x4796;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4852 = x4834 + x4797;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4853 = x4835 + x4799;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4854 = x4836 + x4800;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4855 = x4837 + x4801;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4856 = x4838 + x4802;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4857 = x4839 + x4803;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4858 = x4840 + x4804;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4859 = x4841 + x4807;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4860 = x4842 + x4805;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4861 = x4843 + x4806;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4862 = x4844 + x4808;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4863 = x4845 + x4809;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4864 = x4846 + x4810;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4865 = x4847 + x4811;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4866 = x4848 + x4812;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4867 = x4849 + x4813;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4868 = x4850 + x4818;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4869 = x4851 + x4814;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4870 = x4852 + x4815;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4871 = x4853 + x4816;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4872 = x4854 + x4817;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4873 = x4855 + x4819;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4874 = x4856 + x4820;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4875 = x4857 + x4821;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4876 = x4858 + x4822;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4877 = x4481 + x4679;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4878 = x4482 + x4680;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4879 = x4483 + x4681;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4880 = x4484 + x4682;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4881 = x4485 + x4683;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4882 = x4486 + x4684;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4883 = x4487 + x4685;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4884 = x4488 + x4686;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4885 = x4489 + x4687;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4886 = x4490 + x4690;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4887 = x4491 + x4688;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4888 = x4492 + x4689;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4889 = x4493 + x4691;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4890 = x4494 + x4692;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4891 = x4495 + x4693;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4892 = x4496 + x4694;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4893 = x4497 + x4695;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4894 = x4498 + x4696;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4895 = x4643 + x4697;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4896 = x4644 + x4698;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4897 = x4645 + x4699;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4898 = x4646 + x4700;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4899 = x4647 + x4701;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4900 = x4648 + x4702;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4901 = x4649 + x4703;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4902 = x4650 + x4704;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4903 = x4651 + x4705;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4904 = x4652 + x4708;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4905 = x4653 + x4706;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4906 = x4654 + x4707;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4907 = x4655 + x4709;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4908 = x4656 + x4710;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4909 = x4657 + x4711;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4910 = x4658 + x4712;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4911 = x4659 + x4713;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4912 = x4660 + x4714;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4913 = x4661 + x4715;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4914 = x4662 + x4716;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4915 = x4663 + x4717;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4916 = x4664 + x4718;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4917 = x4665 + x4719;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4918 = x4666 + x4720;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4919 = x4667 + x4721;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4920 = x4668 + x4722;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4921 = x4669 + x4723;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4922 = x4670 + x4726;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4923 = x4671 + x4724;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4924 = x4672 + x4725;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4925 = x4673 + x4727;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4926 = x4674 + x4728;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4927 = x4675 + x4729;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4928 = x4676 + x4730;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4929 = x4677 + x4731;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4930 = x4678 + x4732;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4931 = x4859 + x4755;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4932 = x4860 + x4751;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4933 = x4861 + x4752;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4934 = x4862 + x4753;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4935 = x4863 + x4754;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4936 = x4864 + x4756;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4937 = x4865 + x4757;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4938 = x4866 + x4758;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4939 = x4867 + x4759;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4940 = x4868 + x4766;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4941 = x4869 + x4760;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4942 = x4870 + x4761;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4943 = x4871 + x4762;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4944 = x4872 + x4763;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4945 = x4873 + x4764;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4946 = x4874 + x4765;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4947 = x4875 + x4767;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4948 = x4876 + x4768;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4949 = x4877 + x4735;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4950 = x4878 + x4733;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4951 = x4879 + x4734;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4952 = x4880 + x4736;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4953 = x4881 + x4737;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4954 = x4882 + x4738;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4955 = x4883 + x4739;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4956 = x4884 + x4740;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4957 = x4885 + x4741;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4958 = x4886 + x4746;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4959 = x4887 + x4742;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4960 = x4888 + x4743;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4961 = x4889 + x4744;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4962 = x4890 + x4745;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4963 = x4891 + x4747;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4964 = x4892 + x4748;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4965 = x4893 + x4749;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4966 = x4894 + x4750;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4967 = x4895 + x4501;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4968 = x4896 + x4499;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4969 = x4897 + x4500;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4970 = x4898 + x4502;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4971 = x4899 + x4503;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4972 = x4900 + x4504;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4973 = x4901 + x4505;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4974 = x4902 + x4506;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4975 = x4903 + x4507;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4976 = x4904 + x4512;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4977 = x4905 + x4508;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4978 = x4906 + x4509;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4979 = x4907 + x4510;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4980 = x4908 + x4511;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4981 = x4909 + x4513;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4982 = x4910 + x4514;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4983 = x4911 + x4515;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4984 = x4912 + x4516;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4985 = x4913 + x4519;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4986 = x4914 + x4517;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4987 = x4915 + x4518;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4988 = x4916 + x4520;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4989 = x4917 + x4521;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4990 = x4918 + x4522;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4991 = x4919 + x4523;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4992 = x4920 + x4524;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4993 = x4921 + x4525;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4994 = x4922 + x4530;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4995 = x4923 + x4526;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4996 = x4924 + x4527;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4997 = x4925 + x4528;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4998 = x4926 + x4529;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x4999 = x4927 + x4531;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5000 = x4928 + x4532;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5001 = x4929 + x4533;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5002 = x4930 + x4534;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5003 = x4931 + x4775;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5004 = x4932 + x4769;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5005 = x4933 + x4770;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5006 = x4935 + x4772;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5007 = x4936 + x4773;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5008 = x4938 + x4776;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5009 = x4939 + x4777;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5010 = x4942 + x4779;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5011 = x4943 + x4780;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5012 = x4945 + x4782;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5013 = x4946 + x4783;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5014 = x4948 + x4785;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5015 = x4934 + x4771;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5016 = x4937 + x4774;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5017 = x4940 + x4786;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5018 = x4941 + x4778;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5019 = x4944 + x4781;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5020 = x4947 + x4784;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5021 = x4949 + x4539;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5022 = x4950 + x4535;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5023 = x4951 + x4536;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5024 = x4952 + x4537;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5025 = x4953 + x4538;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5026 = x4954 + x4540;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5027 = x4955 + x4541;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5028 = x4956 + x4542;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5029 = x4957 + x4543;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5030 = x4958 + x4550;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5031 = x4959 + x4544;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5032 = x4960 + x4545;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5033 = x4961 + x4546;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5034 = x4962 + x4547;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5035 = x4963 + x4548;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5036 = x4964 + x4549;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5037 = x4965 + x4551;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5038 = x4966 + x4552;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5039 = x4967 + x4557;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5040 = x4968 + x4553;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5041 = x4969 + x4554;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5042 = x4970 + x4555;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5043 = x4971 + x4556;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5044 = x4972 + x4558;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5045 = x4973 + x4559;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5046 = x4974 + x4560;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5047 = x4975 + x4561;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5048 = x4976 + x4568;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5049 = x4977 + x4562;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5050 = x4978 + x4563;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5051 = x4979 + x4564;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5052 = x4980 + x4565;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5053 = x4981 + x4566;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5054 = x4982 + x4567;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5055 = x4983 + x4569;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5056 = x4984 + x4570;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5057 = x4985 + x4575;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5058 = x4986 + x4571;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5059 = x4987 + x4572;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5060 = x4988 + x4573;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5061 = x4989 + x4574;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5062 = x4990 + x4576;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5063 = x4991 + x4577;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5064 = x4992 + x4578;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5065 = x4993 + x4579;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5066 = x4994 + x4586;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5067 = x4995 + x4580;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5068 = x4996 + x4581;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5069 = x4997 + x4582;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5070 = x4998 + x4583;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5071 = x4999 + x4584;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5072 = x5000 + x4585;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5073 = x5001 + x4587;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5074 = x5002 + x4588;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5075 = x5021 + x4595;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5076 = x5022 + x4589;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5077 = x5023 + x4590;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5078 = x5025 + x4592;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5079 = x5026 + x4593;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5080 = x5028 + x4596;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5081 = x5029 + x4597;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5082 = x5032 + x4599;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5083 = x5033 + x4600;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5084 = x5035 + x4602;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5085 = x5036 + x4603;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5086 = x5038 + x4605;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5087 = x5039 + x4613;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5088 = x5040 + x4607;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5089 = x5041 + x4608;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5090 = x5043 + x4610;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5091 = x5044 + x4611;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5092 = x5046 + x4614;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5093 = x5047 + x4615;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5094 = x5050 + x4617;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5095 = x5051 + x4618;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5096 = x5053 + x4620;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5097 = x5054 + x4621;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5098 = x5056 + x4623;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5099 = x5057 + x4631;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5100 = x5058 + x4625;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5101 = x5059 + x4626;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5102 = x5061 + x4628;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5103 = x5062 + x4629;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5104 = x5064 + x4632;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5105 = x5065 + x4633;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5106 = x5068 + x4635;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5107 = x5069 + x4636;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5108 = x5071 + x4638;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5109 = x5072 + x4639;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5110 = x5074 + x4641;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5111 = x5024 + x4591;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5112 = x5027 + x4594;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5113 = x5030 + x4606;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5114 = x5031 + x4598;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5115 = x5034 + x4601;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5116 = x5037 + x4604;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5117 = x5042 + x4609;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5118 = x5045 + x4612;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5119 = x5048 + x4624;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5120 = x5049 + x4616;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5121 = x5052 + x4619;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5122 = x5055 + x4622;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5123 = x5060 + x4627;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5124 = x5063 + x4630;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5125 = x5066 + x4642;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5126 = x5067 + x4634;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5127 = x5070 + x4637;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x5128 = x5073 + x4640;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5129 = x5111 * x5102;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5130 = x5112 * x5104;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5131 = x5113 * x5100;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5132 = x5114 * x5106;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5133 = x5115 * x5108;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5134 = x5116 * x5110;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5135 = x5111 * x5078;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5136 = x5111 * x5090;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5137 = x5111 * x5006;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5138 = x5112 * x5080;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5139 = x5112 * x5092;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5140 = x5112 * x5008;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5141 = x5113 * x5076;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5142 = x5113 * x5088;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5143 = x5113 * x5004;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5144 = x5114 * x5082;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5145 = x5114 * x5094;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5146 = x5114 * x5010;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5147 = x5115 * x5084;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5148 = x5115 * x5096;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5149 = x5115 * x5012;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5150 = x5116 * x5086;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5151 = x5116 * x5098;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5152 = x5116 * x5014;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5153 = x5117 * x5102;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5154 = x5118 * x5104;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5155 = x5119 * x5100;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5156 = x5120 * x5106;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5157 = x5121 * x5108;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5158 = x5122 * x5110;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5159 = x5123 * x5102;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5160 = x5124 * x5104;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5161 = x5125 * x5100;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5162 = x5126 * x5106;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5163 = x5127 * x5108;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5164 = x5128 * x5110;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5165 = x5015 * x5078;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5166 = x5015 * x5090;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5167 = x5015 * x5102;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5168 = x5015 * x5006;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5169 = x5016 * x5080;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5170 = x5016 * x5092;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5171 = x5016 * x5104;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5172 = x5016 * x5008;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5173 = x5017 * x5076;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5174 = x5017 * x5088;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5175 = x5017 * x5100;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5176 = x5017 * x5004;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5177 = x5018 * x5082;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5178 = x5018 * x5094;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5179 = x5018 * x5106;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5180 = x5018 * x5010;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5181 = x5019 * x5084;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5182 = x5019 * x5096;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5183 = x5019 * x5108;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5184 = x5019 * x5012;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5185 = x5020 * x5086;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5186 = x5020 * x5098;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5187 = x5020 * x5110;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5188 = x5020 * x5014;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5189 = x5117 * x5078;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5190 = x5117 * x5090;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5191 = x5117 * x5006;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5192 = x5118 * x5080;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5193 = x5118 * x5092;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5194 = x5118 * x5008;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5195 = x5119 * x5076;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5196 = x5119 * x5088;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5197 = x5119 * x5004;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5198 = x5120 * x5082;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5199 = x5120 * x5094;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5200 = x5120 * x5010;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5201 = x5121 * x5084;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5202 = x5121 * x5096;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5203 = x5121 * x5012;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5204 = x5122 * x5086;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5205 = x5122 * x5098;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5206 = x5122 * x5014;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5207 = x5123 * x5078;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5208 = x5123 * x5090;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5209 = x5123 * x5006;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5210 = x5124 * x5080;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5211 = x5124 * x5092;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5212 = x5124 * x5008;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5213 = x5125 * x5076;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5214 = x5125 * x5088;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5215 = x5125 * x5004;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5216 = x5126 * x5082;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5217 = x5126 * x5094;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5218 = x5126 * x5010;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5219 = x5127 * x5084;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5220 = x5127 * x5096;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5221 = x5127 * x5012;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5222 = x5128 * x5086;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5223 = x5128 * x5098;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5224 = x5128 * x5014;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5225 = x5159 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5226 = x5160 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5227 = x5161 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5228 = x5162 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5229 = x5163 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5230 = x5164 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5231 = x5153 + x5208;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5232 = x5154 + x5211;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5233 = x5155 + x5214;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5234 = x5156 + x5217;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5235 = x5157 + x5220;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5236 = x5158 + x5223;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5237 = x5129 + x5190;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5238 = x5130 + x5193;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5239 = x5131 + x5196;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5240 = x5132 + x5199;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5241 = x5133 + x5202;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5242 = x5134 + x5205;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5243 = x5165 + x5137;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5244 = x5166 + x5135;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5245 = x5167 + x5136;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5246 = x5169 + x5140;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5247 = x5170 + x5138;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5248 = x5171 + x5139;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5249 = x5173 + x5143;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5250 = x5174 + x5141;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5251 = x5175 + x5142;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5252 = x5177 + x5146;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5253 = x5178 + x5144;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5254 = x5179 + x5145;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5255 = x5181 + x5149;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5256 = x5182 + x5147;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5257 = x5183 + x5148;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5258 = x5185 + x5152;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5259 = x5186 + x5150;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5260 = x5187 + x5151;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5261 = x5231 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5262 = x5232 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5263 = x5233 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5264 = x5234 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5265 = x5235 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5266 = x5236 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5267 = x5237 + x5207;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5268 = x5238 + x5210;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5269 = x5239 + x5213;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5270 = x5240 + x5216;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5271 = x5241 + x5219;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5272 = x5242 + x5222;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5273 = x5243 + x5261;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5274 = x5244 + x5191;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5275 = x5245 + x5189;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5276 = x5246 + x5262;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5277 = x5247 + x5194;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5278 = x5248 + x5192;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5279 = x5249 + x5263;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5280 = x5250 + x5197;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5281 = x5251 + x5195;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5282 = x5252 + x5264;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5283 = x5253 + x5200;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5284 = x5254 + x5198;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5285 = x5255 + x5265;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5286 = x5256 + x5203;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5287 = x5257 + x5201;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5288 = x5258 + x5266;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5289 = x5259 + x5206;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5290 = x5260 + x5204;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5291 = x5273 * x5103;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5292 = x5276 * x5105;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5293 = x5279 * x5101;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5294 = x5282 * x5107;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5295 = x5285 * x5109;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5296 = x5288 * x5099;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5297 = x5267 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5298 = x5268 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5299 = x5269 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5300 = x5270 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5301 = x5271 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5302 = x5272 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5303 = x5273 * x5079;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5304 = x5273 * x5091;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5305 = x5273 * x5007;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5306 = x5276 * x5081;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5307 = x5276 * x5093;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5308 = x5276 * x5009;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5309 = x5279 * x5077;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5310 = x5279 * x5089;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5311 = x5279 * x5005;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5312 = x5282 * x5083;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5313 = x5282 * x5095;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5314 = x5282 * x5011;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5315 = x5285 * x5085;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5316 = x5285 * x5097;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5317 = x5285 * x5013;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5318 = x5288 * x5075;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5319 = x5288 * x5087;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5320 = x5288 * x5003;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5321 = x5274 + x5225;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5322 = x5275 + x5209;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5323 = x5277 + x5226;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5324 = x5278 + x5212;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5325 = x5280 + x5227;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5326 = x5281 + x5215;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5327 = x5283 + x5228;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5328 = x5284 + x5218;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5329 = x5286 + x5229;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5330 = x5287 + x5221;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5331 = x5289 + x5230;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5332 = x5290 + x5224;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5333 = x5168 + x5297;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5334 = x5172 + x5298;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5335 = x5176 + x5299;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5336 = x5180 + x5300;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5337 = x5184 + x5301;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5338 = x5188 + x5302;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5339 = x5321 * x5103;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5340 = x5322 * x5103;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5341 = x5323 * x5105;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5342 = x5324 * x5105;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5343 = x5325 * x5101;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5344 = x5326 * x5101;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5345 = x5327 * x5107;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5346 = x5328 * x5107;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5347 = x5329 * x5109;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5348 = x5330 * x5109;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5349 = x5331 * x5099;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5350 = x5332 * x5099;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5351 = x5333 * x5079;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5352 = x5333 * x5091;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5353 = x5333 * x5103;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5354 = x5333 * x5007;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5355 = x5334 * x5081;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5356 = x5334 * x5093;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5357 = x5334 * x5105;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5358 = x5334 * x5009;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5359 = x5335 * x5077;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5360 = x5335 * x5089;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5361 = x5335 * x5101;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5362 = x5335 * x5005;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5363 = x5336 * x5083;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5364 = x5336 * x5095;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5365 = x5336 * x5107;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5366 = x5336 * x5011;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5367 = x5337 * x5085;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5368 = x5337 * x5097;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5369 = x5337 * x5109;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5370 = x5337 * x5013;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5371 = x5338 * x5075;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5372 = x5338 * x5087;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5373 = x5338 * x5099;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5374 = x5338 * x5003;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5375 = x5321 * x5079;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5376 = x5321 * x5091;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5377 = x5321 * x5007;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5378 = x5322 * x5079;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5379 = x5322 * x5091;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5380 = x5322 * x5007;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5381 = x5323 * x5081;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5382 = x5323 * x5093;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5383 = x5323 * x5009;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5384 = x5324 * x5081;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5385 = x5324 * x5093;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5386 = x5324 * x5009;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5387 = x5325 * x5077;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5388 = x5325 * x5089;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5389 = x5325 * x5005;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5390 = x5326 * x5077;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5391 = x5326 * x5089;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5392 = x5326 * x5005;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5393 = x5327 * x5083;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5394 = x5327 * x5095;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5395 = x5327 * x5011;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5396 = x5328 * x5083;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5397 = x5328 * x5095;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5398 = x5328 * x5011;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5399 = x5329 * x5085;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5400 = x5329 * x5097;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5401 = x5329 * x5013;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5402 = x5330 * x5085;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5403 = x5330 * x5097;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5404 = x5330 * x5013;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5405 = x5331 * x5075;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5406 = x5331 * x5087;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5407 = x5331 * x5003;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5408 = x5332 * x5075;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5409 = x5332 * x5087;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5410 = x5332 * x5003;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5411 = x5340 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5412 = x5342 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5413 = x5344 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5414 = x5346 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5415 = x5348 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5416 = x5350 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5417 = x5339 + x5379;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5418 = x5341 + x5385;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5419 = x5343 + x5391;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5420 = x5345 + x5397;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5421 = x5347 + x5403;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5422 = x5349 + x5409;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5423 = x5291 + x5376;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5424 = x5292 + x5382;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5425 = x5293 + x5388;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5426 = x5294 + x5394;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5427 = x5295 + x5400;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5428 = x5296 + x5406;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5429 = x5351 + x5305;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5430 = x5352 + x5303;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5431 = x5353 + x5304;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5432 = x5355 + x5308;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5433 = x5356 + x5306;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5434 = x5357 + x5307;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5435 = x5359 + x5311;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5436 = x5360 + x5309;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5437 = x5361 + x5310;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5438 = x5363 + x5314;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5439 = x5364 + x5312;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5440 = x5365 + x5313;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5441 = x5367 + x5317;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5442 = x5368 + x5315;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5443 = x5369 + x5316;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5444 = x5371 + x5320;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5445 = x5372 + x5318;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5446 = x5373 + x5319;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5447 = x5417 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5448 = x5418 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5449 = x5419 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5450 = x5420 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5451 = x5421 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5452 = x5422 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5453 = x5423 + x5378;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5454 = x5424 + x5384;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5455 = x5425 + x5390;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5456 = x5426 + x5396;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5457 = x5427 + x5402;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5458 = x5428 + x5408;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5459 = x5430 + x5377;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5460 = x5431 + x5375;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5461 = x5433 + x5383;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5462 = x5434 + x5381;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5463 = x5435 + x5449;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5464 = x5436 + x5389;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5465 = x5437 + x5387;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5466 = x5439 + x5395;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5467 = x5440 + x5393;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5468 = x5442 + x5401;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5469 = x5443 + x5399;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5470 = x5445 + x5407;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5471 = x5446 + x5405;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5472 = x5438 + x5450;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5473 = x5441 + x5451;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5474 = x5444 + x5452;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5475 = x5466 + x5414;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5476 = x5467 + x5398;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5477 = x5468 + x5415;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5478 = x5469 + x5404;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5479 = x5470 + x5416;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5480 = x5471 + x5410;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5481 = x5459 + x5411;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5482 = x5460 + x5380;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5483 = x5461 + x5412;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5484 = x5462 + x5386;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5485 = x5429 + x5447;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5486 = x5432 + x5448;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5487 = x5475 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5488 = x5476 * x5476;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5489 = x5476 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5490 = x5477 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5491 = x5478 * x5478;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5492 = x5478 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5493 = x5479 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5494 = x5480 * x5480;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5495 = x5480 * x1;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5496 = x5453 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5497 = x5454 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5498 = x5455 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5499 = x5456 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5500 = x5457 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5501 = x5458 * x0;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5502 = x5472 * x5472;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5503 = x5473 * x5473;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5504 = x5474 * x5474;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5505 = x5475 * x5475;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5506 = x5477 * x5477;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5507 = x5479 * x5479;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5508 = x5488 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5509 = x5491 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5510 = x5494 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5511 = -x5472;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5512 = -x5473;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5513 = -x5474;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5514 = x5464 + x5413;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5515 = x5465 + x5392;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5516 = x5362 + x5498;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5517 = x5475 + x5475;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5518 = x5476 + x5476;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5519 = x5477 + x5477;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5520 = x5478 + x5478;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5521 = x5479 + x5479;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5522 = x5480 + x5480;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5523 = x5366 + x5499;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5524 = x5370 + x5500;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5525 = x5374 + x5501;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5526 = x5354 + x5496;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x5527 = x5358 + x5497;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5528 = x5472 * x5518;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5529 = x5473 * x5520;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5530 = x5474 * x5522;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5531 = x5523 * x5517;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5532 = x5523 * x5523;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5533 = x5524 * x5519;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5534 = x5524 * x5524;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5535 = x5525 * x5521;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5536 = x5525 * x5525;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5537 = -x5523;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5538 = -x5524;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5539 = -x5525;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5540 = x5528 - x5505;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5541 = x5529 - x5506;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5542 = x5530 - x5507;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5543 = x5531 - x5502;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5544 = x5533 - x5503;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5545 = x5535 - x5504;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5546 = x5543 + x5508;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5547 = x5544 + x5509;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5548 = x5545 + x5510;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5549 = x5546 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5550 = x5547 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5551 = x5548 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5552 = x5549 * x5546;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5553 = x5550 * x5547;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5554 = x5551 * x5548;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5555 = x5540 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5556 = x5541 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5557 = x5542 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5558 = x5532 + x5555;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5559 = x5534 + x5556;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5560 = x5536 + x5557;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5561 = x5558 * x5558;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5562 = x5559 * x5559;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5563 = x5560 * x5560;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5564 = x5561 + x5552;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5565 = x5562 + x5553;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5566 = x5563 + x5554;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5567 = inv(x5564);
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5568 = inv(x5565);
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5569 = inv(x5566);
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5570 = x5558 * x5567;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5571 = x5559 * x5568;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5572 = x5560 * x5569;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5573 = x5546 * x5567;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5574 = x5547 * x5568;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5575 = x5548 * x5569;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5576 = x5472 * x5573;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5577 = x5473 * x5574;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5578 = x5474 * x5575;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5579 = x5523 * x5570;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5580 = x5524 * x5571;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5581 = x5525 * x5572;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5582 = x5511 * x5570;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5583 = x5512 * x5571;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5584 = x5513 * x5572;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5585 = x5537 * x5573;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5586 = x5538 * x5574;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5587 = x5539 * x5575;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5588 = x5475 * x5570;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5589 = x5476 * x5570;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5590 = x5477 * x5571;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5591 = x5478 * x5571;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5592 = x5479 * x5572;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5593 = x5480 * x5572;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5594 = x5487 * x5573;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5595 = x5489 * x5573;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5596 = x5490 * x5574;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5597 = x5492 * x5574;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5598 = x5493 * x5575;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5599 = x5495 * x5575;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5600 = x5576 - x5589;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5601 = x5577 - x5591;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5602 = x5578 - x5593;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5603 = x5582 - x5595;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5604 = x5583 - x5597;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5605 = x5584 - x5599;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5606 = x5579 + x5594;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5607 = x5580 + x5596;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5608 = x5581 + x5598;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5609 = x5585 + x5588;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5610 = x5586 + x5590;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x5611 = x5587 + x5592;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5612 = x5514 * x5600;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5613 = x5515 * x5600;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5614 = x5463 * x5600;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5615 = x5516 * x5606;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5616 = x5516 * x5609;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5617 = x5516 * x5600;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5618 = x5516 * x5603;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5619 = x5514 * x5606;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5620 = x5514 * x5609;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5621 = x5514 * x5603;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5622 = x5515 * x5606;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5623 = x5515 * x5609;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5624 = x5515 * x5603;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5625 = x5463 * x5606;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5626 = x5463 * x5609;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5627 = x5463 * x5603;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5628 = x5613 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5629 = x5612 + x5623;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5630 = x5614 + x5620;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5631 = x5616 + x5627;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5632 = x5617 + x5626;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5633 = x5618 + x5625;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5634 = x5629 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5635 = x5630 + x5624;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5636 = x5631 + x5619;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5637 = x5632 + x5621;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5638 = x5633 + x5634;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5639 = x5638 * x5482;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5640 = x5635 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5641 = x5638 * x5481;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5642 = x5638 * x5485;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5643 = x5638 * x5526;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5644 = x5636 + x5628;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5645 = x5637 + x5622;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5646 = x5615 + x5640;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5647 = x5644 * x5482;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5648 = x5645 * x5482;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5649 = x5646 * x5481;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5650 = x5646 * x5482;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5651 = x5646 * x5485;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5652 = x5646 * x5526;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5653 = x5644 * x5481;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5654 = x5644 * x5485;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5655 = x5644 * x5526;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5656 = x5645 * x5481;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5657 = x5645 * x5485;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5658 = x5645 * x5526;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5659 = x5648 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5660 = x5647 + x5656;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5661 = x5639 + x5653;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5662 = x5649 + x5642;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5663 = x5650 + x5641;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5664 = x5651 + x5643;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5665 = x5660 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5666 = x5661 + x5657;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5667 = x5662 + x5655;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5668 = x5663 + x5654;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5669 = x5664 + x5665;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5670 = x5669 * x5601;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5671 = x5666 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5672 = x5669 * x5607;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5673 = x5669 * x5610;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5674 = x5669 * x5604;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5675 = x5667 + x5659;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5676 = x5668 + x5658;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5677 = x5652 + x5671;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5678 = x5675 * x5601;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5679 = x5676 * x5601;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5680 = x5677 * x5607;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5681 = x5677 * x5610;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5682 = x5677 * x5601;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5683 = x5677 * x5604;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5684 = x5675 * x5607;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5685 = x5675 * x5610;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5686 = x5675 * x5604;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5687 = x5676 * x5607;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5688 = x5676 * x5610;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5689 = x5676 * x5604;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5690 = x5679 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5691 = x5678 + x5688;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5692 = x5670 + x5685;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5693 = x5681 + x5674;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5694 = x5682 + x5673;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5695 = x5683 + x5672;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5696 = x5691 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5697 = x5692 + x5689;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5698 = x5693 + x5684;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5699 = x5694 + x5686;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5700 = x5695 + x5696;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5701 = x5700 * x5484;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5702 = x5697 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5703 = x5700 * x5483;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5704 = x5700 * x5486;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5705 = x5700 * x5527;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5706 = x5698 + x5690;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5707 = x5699 + x5687;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5708 = x5680 + x5702;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5709 = x5706 * x5484;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5710 = x5707 * x5484;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5711 = x5708 * x5483;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5712 = x5708 * x5484;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5713 = x5708 * x5486;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5714 = x5708 * x5527;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5715 = x5706 * x5483;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5716 = x5706 * x5486;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5717 = x5706 * x5527;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5718 = x5707 * x5483;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5719 = x5707 * x5486;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5720 = x5707 * x5527;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5721 = x5710 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5722 = x5709 + x5718;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5723 = x5701 + x5715;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5724 = x5711 + x5704;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5725 = x5712 + x5703;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5726 = x5713 + x5705;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5727 = x5722 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5728 = x5723 + x5719;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5729 = x5724 + x5717;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5730 = x5725 + x5716;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5731 = x5726 + x5727;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5732 = x5731 * x5602;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5733 = x5728 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5734 = x5731 * x5608;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5735 = x5731 * x5611;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5736 = x5731 * x5605;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5737 = x5729 + x5721;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5738 = x5730 + x5720;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5739 = x5714 + x5733;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5740 = x5737 * x5602;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5741 = x5738 * x5602;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5742 = x5739 * x5608;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5743 = x5739 * x5611;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5744 = x5739 * x5602;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5745 = x5739 * x5605;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5746 = x5737 * x5608;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5747 = x5737 * x5611;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5748 = x5737 * x5605;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5749 = x5738 * x5608;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5750 = x5738 * x5611;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5751 = x5738 * x5605;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5752 = x5741 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5753 = x5740 + x5750;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5754 = x5732 + x5747;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5755 = x5743 + x5736;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5756 = x5744 + x5735;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5757 = x5745 + x5734;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5758 = x5753 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5759 = x5754 + x5751;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5760 = x5755 + x5746;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5761 = x5756 + x5748;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5762 = x5757 + x5758;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5763 = x5760 + x5752;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5764 = x5761 + x5749;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5765 = x5759 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x5766 = x5742 + x5765;
      extern_args[0] = x5766;
      extern_args[1] = x5762;
      extern_args[2] = x5763;
      extern_args[3] = x5764;
      extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
    }
  }
  if (x7 != 0) {
    {
      extern_args[0] = x2;
      extern_args[1] = x3;
      extern_args[2] = x3;
      extern_args[3] = x3;
      extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
    }
  }
  if (x8 != 0) {
    {
      extern_args[0] = x2;
      extern_args[1] = x3;
      extern_args[2] = x3;
      extern_args[3] = x3;
      extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
    }
  }
  if (x9 != 0) {
    {
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5767 = arg3[0];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5768 = arg3[1];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5769 = arg3[10];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5770 = arg3[11];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5771 = arg3[12];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5772 = arg3[13];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5773 = arg3[14];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5774 = arg3[15];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5775 = arg3[16];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5776 = arg3[17];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5777 = arg3[18];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5778 = arg3[19];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5779 = arg3[2];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5780 = arg3[3];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5781 = arg3[4];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5782 = arg3[5];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5783 = arg3[6];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5784 = arg3[7];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5785 = arg3[8];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x5786 = arg3[9];
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5787 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x5787 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5788 = arg2[1 * steps + ((cycle - 0) & mask)];
      assert(x5788 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5789 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x5789 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5790 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x5790 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5791 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x5791 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5792 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x5792 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5793 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x5793 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5794 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x5794 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5795 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x5795 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5796 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x5796 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5797 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x5797 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5798 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x5798 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5799 = arg2[2 * steps + ((cycle - 0) & mask)];
      assert(x5799 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5800 = arg2[20 * steps + ((cycle - 0) & mask)];
      assert(x5800 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5801 = arg2[21 * steps + ((cycle - 0) & mask)];
      assert(x5801 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5802 = arg2[22 * steps + ((cycle - 0) & mask)];
      assert(x5802 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5803 = arg2[23 * steps + ((cycle - 0) & mask)];
      assert(x5803 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5804 = arg2[24 * steps + ((cycle - 0) & mask)];
      assert(x5804 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5805 = arg2[25 * steps + ((cycle - 0) & mask)];
      assert(x5805 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5806 = arg2[26 * steps + ((cycle - 0) & mask)];
      assert(x5806 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5807 = arg2[27 * steps + ((cycle - 0) & mask)];
      assert(x5807 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5808 = arg2[28 * steps + ((cycle - 0) & mask)];
      assert(x5808 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5809 = arg2[29 * steps + ((cycle - 0) & mask)];
      assert(x5809 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5810 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x5810 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5811 = arg2[30 * steps + ((cycle - 0) & mask)];
      assert(x5811 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5812 = arg2[31 * steps + ((cycle - 0) & mask)];
      assert(x5812 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5813 = arg2[32 * steps + ((cycle - 0) & mask)];
      assert(x5813 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5814 = arg2[33 * steps + ((cycle - 0) & mask)];
      assert(x5814 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5815 = arg2[34 * steps + ((cycle - 0) & mask)];
      assert(x5815 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5816 = arg2[35 * steps + ((cycle - 0) & mask)];
      assert(x5816 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5817 = arg2[36 * steps + ((cycle - 0) & mask)];
      assert(x5817 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5818 = arg2[37 * steps + ((cycle - 0) & mask)];
      assert(x5818 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5819 = arg2[38 * steps + ((cycle - 0) & mask)];
      assert(x5819 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5820 = arg2[39 * steps + ((cycle - 0) & mask)];
      assert(x5820 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5821 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x5821 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5822 = arg2[40 * steps + ((cycle - 0) & mask)];
      assert(x5822 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5823 = arg2[41 * steps + ((cycle - 0) & mask)];
      assert(x5823 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5824 = arg2[42 * steps + ((cycle - 0) & mask)];
      assert(x5824 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5825 = arg2[43 * steps + ((cycle - 0) & mask)];
      assert(x5825 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5826 = arg2[44 * steps + ((cycle - 0) & mask)];
      assert(x5826 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5827 = arg2[45 * steps + ((cycle - 0) & mask)];
      assert(x5827 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5828 = arg2[46 * steps + ((cycle - 0) & mask)];
      assert(x5828 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5829 = arg2[47 * steps + ((cycle - 0) & mask)];
      assert(x5829 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5830 = arg2[48 * steps + ((cycle - 0) & mask)];
      assert(x5830 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5831 = arg2[49 * steps + ((cycle - 0) & mask)];
      assert(x5831 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5832 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x5832 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5833 = arg2[50 * steps + ((cycle - 0) & mask)];
      assert(x5833 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5834 = arg2[51 * steps + ((cycle - 0) & mask)];
      assert(x5834 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5835 = arg2[52 * steps + ((cycle - 0) & mask)];
      assert(x5835 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5836 = arg2[53 * steps + ((cycle - 0) & mask)];
      assert(x5836 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5837 = arg2[54 * steps + ((cycle - 0) & mask)];
      assert(x5837 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5838 = arg2[55 * steps + ((cycle - 0) & mask)];
      assert(x5838 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5839 = arg2[56 * steps + ((cycle - 0) & mask)];
      assert(x5839 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5840 = arg2[57 * steps + ((cycle - 0) & mask)];
      assert(x5840 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5841 = arg2[58 * steps + ((cycle - 0) & mask)];
      assert(x5841 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5842 = arg2[59 * steps + ((cycle - 0) & mask)];
      assert(x5842 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5843 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x5843 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5844 = arg2[60 * steps + ((cycle - 0) & mask)];
      assert(x5844 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5845 = arg2[61 * steps + ((cycle - 0) & mask)];
      assert(x5845 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5846 = arg2[62 * steps + ((cycle - 0) & mask)];
      assert(x5846 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5847 = arg2[63 * steps + ((cycle - 0) & mask)];
      assert(x5847 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5848 = arg2[64 * steps + ((cycle - 0) & mask)];
      assert(x5848 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5849 = arg2[65 * steps + ((cycle - 0) & mask)];
      assert(x5849 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5850 = arg2[66 * steps + ((cycle - 0) & mask)];
      assert(x5850 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5851 = arg2[67 * steps + ((cycle - 0) & mask)];
      assert(x5851 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5852 = arg2[68 * steps + ((cycle - 0) & mask)];
      assert(x5852 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5853 = arg2[69 * steps + ((cycle - 0) & mask)];
      assert(x5853 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5854 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x5854 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5855 = arg2[70 * steps + ((cycle - 0) & mask)];
      assert(x5855 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5856 = arg2[71 * steps + ((cycle - 0) & mask)];
      assert(x5856 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5857 = arg2[72 * steps + ((cycle - 0) & mask)];
      assert(x5857 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5858 = arg2[73 * steps + ((cycle - 0) & mask)];
      assert(x5858 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5859 = arg2[74 * steps + ((cycle - 0) & mask)];
      assert(x5859 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5860 = arg2[75 * steps + ((cycle - 0) & mask)];
      assert(x5860 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5861 = arg2[76 * steps + ((cycle - 0) & mask)];
      assert(x5861 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5862 = arg2[77 * steps + ((cycle - 0) & mask)];
      assert(x5862 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5863 = arg2[78 * steps + ((cycle - 0) & mask)];
      assert(x5863 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5864 = arg2[79 * steps + ((cycle - 0) & mask)];
      assert(x5864 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5865 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x5865 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5866 = arg2[80 * steps + ((cycle - 0) & mask)];
      assert(x5866 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5867 = arg2[81 * steps + ((cycle - 0) & mask)];
      assert(x5867 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5868 = arg2[82 * steps + ((cycle - 0) & mask)];
      assert(x5868 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5869 = arg2[83 * steps + ((cycle - 0) & mask)];
      assert(x5869 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5870 = arg2[84 * steps + ((cycle - 0) & mask)];
      assert(x5870 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x5871 = arg2[85 * steps + ((cycle - 0) & mask)];
      assert(x5871 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5872 = arg2[86 * steps + ((cycle - 0) & mask)];
      assert(x5872 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5873 = arg2[87 * steps + ((cycle - 0) & mask)];
      assert(x5873 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5874 = arg2[88 * steps + ((cycle - 0) & mask)];
      assert(x5874 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5875 = arg2[89 * steps + ((cycle - 0) & mask)];
      assert(x5875 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/poseidon2_store(recursion::Poseidon2Store)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x5876 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x5876 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5877 = x5767 * x5787;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5878 = x5767 * x5789;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5879 = x5767 * x5794;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5880 = x5767 * x5800;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5881 = x5767 * x5805;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5882 = x5767 * x5811;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5883 = x5767 * x5816;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5884 = x5767 * x5822;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5885 = x5767 * x5827;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5886 = x5767 * x5832;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5887 = x5767 * x5833;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5888 = x5767 * x5838;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5889 = x5767 * x5844;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5890 = x5767 * x5849;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5891 = x5767 * x5855;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5892 = x5767 * x5860;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5893 = x5767 * x5866;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5894 = x5767 * x5871;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5895 = x5768 * x5787;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5896 = x5768 * x5789;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5897 = x5768 * x5794;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5898 = x5768 * x5800;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5899 = x5768 * x5805;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5900 = x5768 * x5811;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5901 = x5768 * x5816;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5902 = x5768 * x5822;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5903 = x5768 * x5827;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5904 = x5768 * x5832;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5905 = x5768 * x5833;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5906 = x5768 * x5838;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5907 = x5768 * x5844;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5908 = x5768 * x5849;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5909 = x5768 * x5855;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5910 = x5768 * x5860;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5911 = x5768 * x5866;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5912 = x5768 * x5871;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5913 = x5769 * x5791;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5914 = x5769 * x5796;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5915 = x5769 * x5799;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5916 = x5769 * x5802;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5917 = x5769 * x5807;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5918 = x5769 * x5813;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5919 = x5769 * x5818;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5920 = x5769 * x5824;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5921 = x5769 * x5829;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5922 = x5769 * x5835;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5923 = x5769 * x5840;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5924 = x5769 * x5846;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5925 = x5769 * x5851;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5926 = x5769 * x5854;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5927 = x5769 * x5857;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5928 = x5769 * x5862;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5929 = x5769 * x5868;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5930 = x5769 * x5873;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5931 = x5770 * x5791;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5932 = x5770 * x5796;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5933 = x5770 * x5799;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5934 = x5770 * x5802;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5935 = x5770 * x5807;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5936 = x5770 * x5813;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5937 = x5770 * x5818;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5938 = x5770 * x5824;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5939 = x5770 * x5829;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5940 = x5770 * x5835;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5941 = x5770 * x5840;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5942 = x5770 * x5846;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5943 = x5770 * x5851;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5944 = x5770 * x5854;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5945 = x5770 * x5857;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5946 = x5770 * x5862;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5947 = x5770 * x5868;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5948 = x5770 * x5873;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5949 = x5772 * x5792;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5950 = x5772 * x5797;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5951 = x5772 * x5803;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5952 = x5772 * x5808;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5953 = x5772 * x5810;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5954 = x5772 * x5814;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5955 = x5772 * x5819;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5956 = x5772 * x5825;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5957 = x5772 * x5830;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5958 = x5772 * x5836;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5959 = x5772 * x5841;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5960 = x5772 * x5847;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5961 = x5772 * x5852;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5962 = x5772 * x5858;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5963 = x5772 * x5863;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5964 = x5772 * x5865;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5965 = x5772 * x5869;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5966 = x5772 * x5874;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5967 = x5773 * x5792;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5968 = x5773 * x5797;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5969 = x5773 * x5803;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5970 = x5773 * x5808;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5971 = x5773 * x5810;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5972 = x5773 * x5814;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5973 = x5773 * x5819;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5974 = x5773 * x5825;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5975 = x5773 * x5830;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5976 = x5773 * x5836;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5977 = x5773 * x5841;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5978 = x5773 * x5847;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5979 = x5773 * x5852;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5980 = x5773 * x5858;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5981 = x5773 * x5863;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5982 = x5773 * x5865;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5983 = x5773 * x5869;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5984 = x5773 * x5874;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5985 = x5774 * x5792;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5986 = x5774 * x5797;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5987 = x5774 * x5803;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5988 = x5774 * x5808;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5989 = x5774 * x5810;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5990 = x5774 * x5814;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5991 = x5774 * x5819;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5992 = x5774 * x5825;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5993 = x5774 * x5830;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5994 = x5774 * x5836;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5995 = x5774 * x5841;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5996 = x5774 * x5847;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5997 = x5774 * x5852;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5998 = x5774 * x5858;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x5999 = x5774 * x5863;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6000 = x5774 * x5865;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6001 = x5774 * x5869;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6002 = x5774 * x5874;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6003 = x5776 * x5793;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6004 = x5776 * x5798;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6005 = x5776 * x5804;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6006 = x5776 * x5809;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6007 = x5776 * x5815;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6008 = x5776 * x5820;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6009 = x5776 * x5821;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6010 = x5776 * x5826;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6011 = x5776 * x5831;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6012 = x5776 * x5837;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6013 = x5776 * x5842;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6014 = x5776 * x5848;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6015 = x5776 * x5853;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6016 = x5776 * x5859;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6017 = x5776 * x5864;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6018 = x5776 * x5870;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6019 = x5776 * x5875;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6020 = x5776 * x5876;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6021 = x5777 * x5793;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6022 = x5777 * x5798;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6023 = x5777 * x5804;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6024 = x5777 * x5809;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6025 = x5777 * x5815;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6026 = x5777 * x5820;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6027 = x5777 * x5821;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6028 = x5777 * x5826;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6029 = x5777 * x5831;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6030 = x5777 * x5837;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6031 = x5777 * x5842;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6032 = x5777 * x5848;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6033 = x5777 * x5853;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6034 = x5777 * x5859;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6035 = x5777 * x5864;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6036 = x5777 * x5870;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6037 = x5777 * x5875;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6038 = x5777 * x5876;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6039 = x5778 * x5793;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6040 = x5778 * x5798;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6041 = x5778 * x5804;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6042 = x5778 * x5809;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6043 = x5778 * x5815;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6044 = x5778 * x5820;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6045 = x5778 * x5821;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6046 = x5778 * x5826;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6047 = x5778 * x5831;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6048 = x5778 * x5837;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6049 = x5778 * x5842;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6050 = x5778 * x5848;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6051 = x5778 * x5853;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6052 = x5778 * x5859;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6053 = x5778 * x5864;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6054 = x5778 * x5870;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6055 = x5778 * x5875;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6056 = x5778 * x5876;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6057 = x5779 * x5787;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6058 = x5779 * x5789;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6059 = x5779 * x5794;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6060 = x5779 * x5800;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6061 = x5779 * x5805;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6062 = x5779 * x5811;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6063 = x5779 * x5816;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6064 = x5779 * x5822;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6065 = x5779 * x5827;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6066 = x5779 * x5832;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6067 = x5779 * x5833;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6068 = x5779 * x5838;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6069 = x5779 * x5844;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6070 = x5779 * x5849;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6071 = x5779 * x5855;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6072 = x5779 * x5860;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6073 = x5779 * x5866;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6074 = x5779 * x5871;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6075 = x5780 * x5787;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6076 = x5780 * x5789;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6077 = x5780 * x5794;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6078 = x5780 * x5800;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6079 = x5780 * x5805;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6080 = x5780 * x5811;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6081 = x5780 * x5816;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6082 = x5780 * x5822;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6083 = x5780 * x5827;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6084 = x5780 * x5832;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6085 = x5780 * x5833;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6086 = x5780 * x5838;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6087 = x5780 * x5844;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6088 = x5780 * x5849;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6089 = x5780 * x5855;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6090 = x5780 * x5860;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6091 = x5780 * x5866;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6092 = x5780 * x5871;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6093 = x5782 * x5788;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6094 = x5782 * x5790;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6095 = x5782 * x5795;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6096 = x5782 * x5801;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6097 = x5782 * x5806;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6098 = x5782 * x5812;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6099 = x5782 * x5817;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6100 = x5782 * x5823;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6101 = x5782 * x5828;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6102 = x5782 * x5834;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6103 = x5782 * x5839;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6104 = x5782 * x5843;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6105 = x5782 * x5845;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6106 = x5782 * x5850;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6107 = x5782 * x5856;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6108 = x5782 * x5861;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6109 = x5782 * x5867;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6110 = x5782 * x5872;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6111 = x5783 * x5788;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6112 = x5783 * x5790;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6113 = x5783 * x5795;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6114 = x5783 * x5801;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6115 = x5783 * x5806;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6116 = x5783 * x5812;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6117 = x5783 * x5817;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6118 = x5783 * x5823;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6119 = x5783 * x5828;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6120 = x5783 * x5834;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6121 = x5783 * x5839;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6122 = x5783 * x5843;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6123 = x5783 * x5845;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6124 = x5783 * x5850;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6125 = x5783 * x5856;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6126 = x5783 * x5861;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6127 = x5783 * x5867;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6128 = x5783 * x5872;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6129 = x5784 * x5788;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6130 = x5784 * x5790;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6131 = x5784 * x5795;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6132 = x5784 * x5801;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6133 = x5784 * x5806;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6134 = x5784 * x5812;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6135 = x5784 * x5817;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6136 = x5784 * x5823;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6137 = x5784 * x5828;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6138 = x5784 * x5834;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6139 = x5784 * x5839;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6140 = x5784 * x5843;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6141 = x5784 * x5845;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6142 = x5784 * x5850;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6143 = x5784 * x5856;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6144 = x5784 * x5861;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6145 = x5784 * x5867;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6146 = x5784 * x5872;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6147 = x5786 * x5791;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6148 = x5786 * x5796;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6149 = x5786 * x5799;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6150 = x5786 * x5802;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6151 = x5786 * x5807;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6152 = x5786 * x5813;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6153 = x5786 * x5818;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6154 = x5786 * x5824;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6155 = x5786 * x5829;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6156 = x5786 * x5835;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6157 = x5786 * x5840;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6158 = x5786 * x5846;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6159 = x5786 * x5851;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6160 = x5786 * x5854;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6161 = x5786 * x5857;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6162 = x5786 * x5862;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6163 = x5786 * x5868;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6164 = x5786 * x5873;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6165 = x5771 * x5792;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6166 = x5771 * x5797;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6167 = x5771 * x5803;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6168 = x5771 * x5808;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6169 = x5771 * x5810;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6170 = x5771 * x5814;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6171 = x5771 * x5819;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6172 = x5771 * x5825;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6173 = x5771 * x5830;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6174 = x5771 * x5836;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6175 = x5771 * x5841;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6176 = x5771 * x5847;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6177 = x5771 * x5852;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6178 = x5771 * x5858;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6179 = x5771 * x5863;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6180 = x5771 * x5865;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6181 = x5771 * x5869;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6182 = x5771 * x5874;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6183 = x5775 * x5793;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6184 = x5775 * x5798;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6185 = x5775 * x5804;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6186 = x5775 * x5809;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6187 = x5775 * x5815;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6188 = x5775 * x5820;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6189 = x5775 * x5821;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6190 = x5775 * x5826;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6191 = x5775 * x5831;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6192 = x5775 * x5837;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6193 = x5775 * x5842;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6194 = x5775 * x5848;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6195 = x5775 * x5853;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6196 = x5775 * x5859;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6197 = x5775 * x5864;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6198 = x5775 * x5870;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6199 = x5775 * x5875;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6200 = x5775 * x5876;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6201 = x5781 * x5788;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6202 = x5781 * x5790;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6203 = x5781 * x5795;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6204 = x5781 * x5801;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6205 = x5781 * x5806;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6206 = x5781 * x5812;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6207 = x5781 * x5817;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6208 = x5781 * x5823;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6209 = x5781 * x5828;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6210 = x5781 * x5834;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6211 = x5781 * x5839;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6212 = x5781 * x5843;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6213 = x5781 * x5845;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6214 = x5781 * x5850;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6215 = x5781 * x5856;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6216 = x5781 * x5861;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6217 = x5781 * x5867;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6218 = x5781 * x5872;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6219 = x5785 * x5791;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6220 = x5785 * x5796;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6221 = x5785 * x5799;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6222 = x5785 * x5802;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6223 = x5785 * x5807;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6224 = x5785 * x5813;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6225 = x5785 * x5818;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6226 = x5785 * x5824;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6227 = x5785 * x5829;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6228 = x5785 * x5835;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6229 = x5785 * x5840;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6230 = x5785 * x5846;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6231 = x5785 * x5851;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6232 = x5785 * x5854;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6233 = x5785 * x5857;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6234 = x5785 * x5862;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6235 = x5785 * x5868;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x6236 = x5785 * x5873;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6237 = x5877 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6238 = x5878 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6239 = x5879 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6240 = x5880 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6241 = x5881 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6242 = x5882 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6243 = x5883 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6244 = x5884 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6245 = x5885 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6246 = x5886 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6247 = x5887 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6248 = x5888 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6249 = x5889 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6250 = x5890 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6251 = x5891 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6252 = x5892 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6253 = x5893 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6254 = x5894 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6255 = x6237 + x6201;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6256 = x6238 + x6202;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6257 = x6239 + x6203;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6258 = x6240 + x6204;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6259 = x6241 + x6205;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6260 = x6242 + x6206;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6261 = x6243 + x6207;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6262 = x6244 + x6208;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6263 = x6245 + x6209;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6264 = x6246 + x6212;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6265 = x6247 + x6210;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6266 = x6248 + x6211;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6267 = x6249 + x6213;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6268 = x6250 + x6214;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6269 = x6251 + x6215;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6270 = x6252 + x6216;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6271 = x6253 + x6217;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6272 = x6254 + x6218;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6273 = x6255 + x6221;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6274 = x6256 + x6219;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6275 = x6257 + x6220;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6276 = x6258 + x6222;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6277 = x6259 + x6223;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6278 = x6260 + x6224;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6279 = x6261 + x6225;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6280 = x6262 + x6226;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6281 = x6263 + x6227;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6282 = x6264 + x6232;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6283 = x6265 + x6228;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6284 = x6266 + x6229;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6285 = x6267 + x6230;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6286 = x6268 + x6231;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6287 = x6269 + x6233;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6288 = x6270 + x6234;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6289 = x6271 + x6235;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6290 = x6272 + x6236;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6291 = x5895 + x6093;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6292 = x5896 + x6094;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6293 = x5897 + x6095;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6294 = x5898 + x6096;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6295 = x5899 + x6097;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6296 = x5900 + x6098;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6297 = x5901 + x6099;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6298 = x5902 + x6100;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6299 = x5903 + x6101;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6300 = x5904 + x6104;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6301 = x5905 + x6102;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6302 = x5906 + x6103;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6303 = x5907 + x6105;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6304 = x5908 + x6106;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6305 = x5909 + x6107;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6306 = x5910 + x6108;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6307 = x5911 + x6109;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6308 = x5912 + x6110;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6309 = x6057 + x6111;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6310 = x6058 + x6112;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6311 = x6059 + x6113;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6312 = x6060 + x6114;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6313 = x6061 + x6115;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6314 = x6062 + x6116;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6315 = x6063 + x6117;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6316 = x6064 + x6118;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6317 = x6065 + x6119;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6318 = x6066 + x6122;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6319 = x6067 + x6120;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6320 = x6068 + x6121;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6321 = x6069 + x6123;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6322 = x6070 + x6124;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6323 = x6071 + x6125;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6324 = x6072 + x6126;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6325 = x6073 + x6127;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6326 = x6074 + x6128;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6327 = x6075 + x6129;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6328 = x6076 + x6130;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6329 = x6077 + x6131;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6330 = x6078 + x6132;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6331 = x6079 + x6133;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6332 = x6080 + x6134;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6333 = x6081 + x6135;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6334 = x6082 + x6136;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6335 = x6083 + x6137;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6336 = x6084 + x6140;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6337 = x6085 + x6138;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6338 = x6086 + x6139;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6339 = x6087 + x6141;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6340 = x6088 + x6142;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6341 = x6089 + x6143;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6342 = x6090 + x6144;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6343 = x6091 + x6145;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6344 = x6092 + x6146;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6345 = x6273 + x6169;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6346 = x6274 + x6165;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6347 = x6275 + x6166;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6348 = x6276 + x6167;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6349 = x6277 + x6168;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6350 = x6278 + x6170;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6351 = x6279 + x6171;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6352 = x6280 + x6172;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6353 = x6281 + x6173;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6354 = x6282 + x6180;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6355 = x6283 + x6174;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6356 = x6284 + x6175;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6357 = x6285 + x6176;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6358 = x6286 + x6177;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6359 = x6287 + x6178;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6360 = x6288 + x6179;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6361 = x6289 + x6181;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6362 = x6290 + x6182;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6363 = x6291 + x6149;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6364 = x6292 + x6147;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6365 = x6293 + x6148;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6366 = x6294 + x6150;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6367 = x6295 + x6151;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6368 = x6296 + x6152;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6369 = x6297 + x6153;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6370 = x6298 + x6154;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6371 = x6299 + x6155;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6372 = x6300 + x6160;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6373 = x6301 + x6156;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6374 = x6302 + x6157;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6375 = x6303 + x6158;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6376 = x6304 + x6159;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6377 = x6305 + x6161;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6378 = x6306 + x6162;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6379 = x6307 + x6163;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6380 = x6308 + x6164;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6381 = x6309 + x5915;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6382 = x6310 + x5913;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6383 = x6311 + x5914;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6384 = x6312 + x5916;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6385 = x6313 + x5917;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6386 = x6314 + x5918;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6387 = x6315 + x5919;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6388 = x6316 + x5920;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6389 = x6317 + x5921;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6390 = x6318 + x5926;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6391 = x6319 + x5922;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6392 = x6320 + x5923;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6393 = x6321 + x5924;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6394 = x6322 + x5925;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6395 = x6323 + x5927;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6396 = x6324 + x5928;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6397 = x6325 + x5929;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6398 = x6326 + x5930;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6399 = x6327 + x5933;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6400 = x6328 + x5931;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6401 = x6329 + x5932;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6402 = x6330 + x5934;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6403 = x6331 + x5935;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6404 = x6332 + x5936;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6405 = x6333 + x5937;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6406 = x6334 + x5938;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6407 = x6335 + x5939;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6408 = x6336 + x5944;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6409 = x6337 + x5940;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6410 = x6338 + x5941;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6411 = x6339 + x5942;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6412 = x6340 + x5943;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6413 = x6341 + x5945;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6414 = x6342 + x5946;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6415 = x6343 + x5947;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6416 = x6344 + x5948;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6417 = x6345 + x6189;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6418 = x6346 + x6183;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6419 = x6347 + x6184;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6420 = x6349 + x6186;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6421 = x6350 + x6187;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6422 = x6352 + x6190;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6423 = x6353 + x6191;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6424 = x6356 + x6193;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6425 = x6357 + x6194;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6426 = x6359 + x6196;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6427 = x6360 + x6197;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6428 = x6362 + x6199;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6429 = x6348 + x6185;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6430 = x6351 + x6188;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6431 = x6354 + x6200;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6432 = x6355 + x6192;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6433 = x6358 + x6195;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6434 = x6361 + x6198;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6435 = x6363 + x5953;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6436 = x6364 + x5949;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6437 = x6365 + x5950;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6438 = x6366 + x5951;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6439 = x6367 + x5952;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6440 = x6368 + x5954;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6441 = x6369 + x5955;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6442 = x6370 + x5956;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6443 = x6371 + x5957;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6444 = x6372 + x5964;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6445 = x6373 + x5958;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6446 = x6374 + x5959;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6447 = x6375 + x5960;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6448 = x6376 + x5961;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6449 = x6377 + x5962;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6450 = x6378 + x5963;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6451 = x6379 + x5965;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6452 = x6380 + x5966;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6453 = x6381 + x5971;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6454 = x6382 + x5967;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6455 = x6383 + x5968;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6456 = x6384 + x5969;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6457 = x6385 + x5970;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6458 = x6386 + x5972;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6459 = x6387 + x5973;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6460 = x6388 + x5974;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6461 = x6389 + x5975;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6462 = x6390 + x5982;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6463 = x6391 + x5976;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6464 = x6392 + x5977;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6465 = x6393 + x5978;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6466 = x6394 + x5979;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6467 = x6395 + x5980;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6468 = x6396 + x5981;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6469 = x6397 + x5983;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6470 = x6398 + x5984;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6471 = x6399 + x5989;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6472 = x6400 + x5985;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6473 = x6401 + x5986;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6474 = x6402 + x5987;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6475 = x6403 + x5988;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6476 = x6404 + x5990;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6477 = x6405 + x5991;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6478 = x6406 + x5992;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6479 = x6407 + x5993;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6480 = x6408 + x6000;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6481 = x6409 + x5994;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6482 = x6410 + x5995;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6483 = x6411 + x5996;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6484 = x6412 + x5997;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6485 = x6413 + x5998;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6486 = x6414 + x5999;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6487 = x6415 + x6001;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6488 = x6416 + x6002;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6489 = x6435 + x6009;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6490 = x6436 + x6003;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6491 = x6437 + x6004;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6492 = x6439 + x6006;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6493 = x6440 + x6007;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6494 = x6442 + x6010;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6495 = x6443 + x6011;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6496 = x6446 + x6013;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6497 = x6447 + x6014;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6498 = x6449 + x6016;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6499 = x6450 + x6017;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6500 = x6452 + x6019;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6501 = x6453 + x6027;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6502 = x6454 + x6021;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6503 = x6455 + x6022;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6504 = x6457 + x6024;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6505 = x6458 + x6025;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6506 = x6460 + x6028;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6507 = x6461 + x6029;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6508 = x6464 + x6031;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6509 = x6465 + x6032;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6510 = x6467 + x6034;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6511 = x6468 + x6035;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6512 = x6470 + x6037;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6513 = x6471 + x6045;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6514 = x6472 + x6039;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6515 = x6473 + x6040;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6516 = x6475 + x6042;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6517 = x6476 + x6043;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6518 = x6478 + x6046;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6519 = x6479 + x6047;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6520 = x6482 + x6049;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6521 = x6483 + x6050;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6522 = x6485 + x6052;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6523 = x6486 + x6053;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6524 = x6488 + x6055;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6525 = x6438 + x6005;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6526 = x6441 + x6008;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6527 = x6444 + x6020;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6528 = x6445 + x6012;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6529 = x6448 + x6015;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6530 = x6451 + x6018;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6531 = x6456 + x6023;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6532 = x6459 + x6026;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6533 = x6462 + x6038;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6534 = x6463 + x6030;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6535 = x6466 + x6033;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6536 = x6469 + x6036;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6537 = x6474 + x6041;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6538 = x6477 + x6044;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6539 = x6480 + x6056;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6540 = x6481 + x6048;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6541 = x6484 + x6051;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x6542 = x6487 + x6054;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6543 = x6525 * x6516;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6544 = x6526 * x6518;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6545 = x6527 * x6514;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6546 = x6528 * x6520;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6547 = x6529 * x6522;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6548 = x6530 * x6524;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6549 = x6525 * x6492;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6550 = x6525 * x6504;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6551 = x6525 * x6420;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6552 = x6526 * x6494;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6553 = x6526 * x6506;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6554 = x6526 * x6422;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6555 = x6527 * x6490;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6556 = x6527 * x6502;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6557 = x6527 * x6418;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6558 = x6528 * x6496;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6559 = x6528 * x6508;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6560 = x6528 * x6424;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6561 = x6529 * x6498;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6562 = x6529 * x6510;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6563 = x6529 * x6426;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6564 = x6530 * x6500;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6565 = x6530 * x6512;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6566 = x6530 * x6428;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6567 = x6531 * x6516;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6568 = x6532 * x6518;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6569 = x6533 * x6514;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6570 = x6534 * x6520;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6571 = x6535 * x6522;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6572 = x6536 * x6524;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6573 = x6537 * x6516;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6574 = x6538 * x6518;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6575 = x6539 * x6514;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6576 = x6540 * x6520;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6577 = x6541 * x6522;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6578 = x6542 * x6524;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6579 = x6429 * x6492;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6580 = x6429 * x6504;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6581 = x6429 * x6516;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6582 = x6429 * x6420;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6583 = x6430 * x6494;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6584 = x6430 * x6506;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6585 = x6430 * x6518;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6586 = x6430 * x6422;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6587 = x6431 * x6490;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6588 = x6431 * x6502;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6589 = x6431 * x6514;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6590 = x6431 * x6418;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6591 = x6432 * x6496;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6592 = x6432 * x6508;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6593 = x6432 * x6520;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6594 = x6432 * x6424;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6595 = x6433 * x6498;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6596 = x6433 * x6510;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6597 = x6433 * x6522;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6598 = x6433 * x6426;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6599 = x6434 * x6500;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6600 = x6434 * x6512;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6601 = x6434 * x6524;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6602 = x6434 * x6428;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6603 = x6531 * x6492;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6604 = x6531 * x6504;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6605 = x6531 * x6420;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6606 = x6532 * x6494;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6607 = x6532 * x6506;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6608 = x6532 * x6422;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6609 = x6533 * x6490;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6610 = x6533 * x6502;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6611 = x6533 * x6418;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6612 = x6534 * x6496;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6613 = x6534 * x6508;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6614 = x6534 * x6424;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6615 = x6535 * x6498;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6616 = x6535 * x6510;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6617 = x6535 * x6426;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6618 = x6536 * x6500;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6619 = x6536 * x6512;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6620 = x6536 * x6428;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6621 = x6537 * x6492;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6622 = x6537 * x6504;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6623 = x6537 * x6420;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6624 = x6538 * x6494;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6625 = x6538 * x6506;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6626 = x6538 * x6422;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6627 = x6539 * x6490;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6628 = x6539 * x6502;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6629 = x6539 * x6418;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6630 = x6540 * x6496;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6631 = x6540 * x6508;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6632 = x6540 * x6424;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6633 = x6541 * x6498;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6634 = x6541 * x6510;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6635 = x6541 * x6426;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6636 = x6542 * x6500;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6637 = x6542 * x6512;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6638 = x6542 * x6428;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6639 = x6573 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6640 = x6574 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6641 = x6575 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6642 = x6576 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6643 = x6577 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6644 = x6578 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6645 = x6567 + x6622;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6646 = x6568 + x6625;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6647 = x6569 + x6628;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6648 = x6570 + x6631;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6649 = x6571 + x6634;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6650 = x6572 + x6637;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6651 = x6543 + x6604;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6652 = x6544 + x6607;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6653 = x6545 + x6610;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6654 = x6546 + x6613;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6655 = x6547 + x6616;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6656 = x6548 + x6619;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6657 = x6579 + x6551;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6658 = x6580 + x6549;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6659 = x6581 + x6550;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6660 = x6583 + x6554;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6661 = x6584 + x6552;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6662 = x6585 + x6553;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6663 = x6587 + x6557;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6664 = x6588 + x6555;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6665 = x6589 + x6556;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6666 = x6591 + x6560;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6667 = x6592 + x6558;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6668 = x6593 + x6559;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6669 = x6595 + x6563;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6670 = x6596 + x6561;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6671 = x6597 + x6562;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6672 = x6599 + x6566;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6673 = x6600 + x6564;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6674 = x6601 + x6565;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6675 = x6645 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6676 = x6646 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6677 = x6647 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6678 = x6648 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6679 = x6649 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6680 = x6650 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6681 = x6651 + x6621;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6682 = x6652 + x6624;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6683 = x6653 + x6627;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6684 = x6654 + x6630;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6685 = x6655 + x6633;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6686 = x6656 + x6636;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6687 = x6657 + x6675;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6688 = x6658 + x6605;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6689 = x6659 + x6603;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6690 = x6660 + x6676;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6691 = x6661 + x6608;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6692 = x6662 + x6606;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6693 = x6663 + x6677;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6694 = x6664 + x6611;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6695 = x6665 + x6609;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6696 = x6666 + x6678;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6697 = x6667 + x6614;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6698 = x6668 + x6612;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6699 = x6669 + x6679;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6700 = x6670 + x6617;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6701 = x6671 + x6615;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6702 = x6672 + x6680;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6703 = x6673 + x6620;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6704 = x6674 + x6618;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6705 = x6687 * x6517;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6706 = x6690 * x6519;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6707 = x6693 * x6515;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6708 = x6696 * x6521;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6709 = x6699 * x6523;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6710 = x6702 * x6513;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6711 = x6681 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6712 = x6682 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6713 = x6683 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6714 = x6684 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6715 = x6685 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6716 = x6686 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6717 = x6687 * x6493;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6718 = x6687 * x6505;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6719 = x6687 * x6421;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6720 = x6690 * x6495;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6721 = x6690 * x6507;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6722 = x6690 * x6423;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6723 = x6693 * x6491;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6724 = x6693 * x6503;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6725 = x6693 * x6419;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6726 = x6696 * x6497;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6727 = x6696 * x6509;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6728 = x6696 * x6425;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6729 = x6699 * x6499;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6730 = x6699 * x6511;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6731 = x6699 * x6427;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6732 = x6702 * x6489;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6733 = x6702 * x6501;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6734 = x6702 * x6417;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6735 = x6688 + x6639;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6736 = x6689 + x6623;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6737 = x6691 + x6640;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6738 = x6692 + x6626;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6739 = x6694 + x6641;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6740 = x6695 + x6629;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6741 = x6697 + x6642;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6742 = x6698 + x6632;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6743 = x6700 + x6643;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6744 = x6701 + x6635;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6745 = x6703 + x6644;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6746 = x6704 + x6638;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6747 = x6582 + x6711;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6748 = x6586 + x6712;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6749 = x6590 + x6713;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6750 = x6594 + x6714;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6751 = x6598 + x6715;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6752 = x6602 + x6716;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6753 = x6735 * x6517;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6754 = x6736 * x6517;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6755 = x6737 * x6519;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6756 = x6738 * x6519;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6757 = x6739 * x6515;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6758 = x6740 * x6515;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6759 = x6741 * x6521;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6760 = x6742 * x6521;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6761 = x6743 * x6523;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6762 = x6744 * x6523;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6763 = x6745 * x6513;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6764 = x6746 * x6513;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6765 = x6747 * x6493;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6766 = x6747 * x6505;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6767 = x6747 * x6517;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6768 = x6747 * x6421;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6769 = x6748 * x6495;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6770 = x6748 * x6507;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6771 = x6748 * x6519;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6772 = x6748 * x6423;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6773 = x6749 * x6491;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6774 = x6749 * x6503;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6775 = x6749 * x6515;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6776 = x6749 * x6419;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6777 = x6750 * x6497;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6778 = x6750 * x6509;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6779 = x6750 * x6521;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6780 = x6750 * x6425;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6781 = x6751 * x6499;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6782 = x6751 * x6511;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6783 = x6751 * x6523;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6784 = x6751 * x6427;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6785 = x6752 * x6489;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6786 = x6752 * x6501;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6787 = x6752 * x6513;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6788 = x6752 * x6417;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6789 = x6735 * x6493;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6790 = x6735 * x6505;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6791 = x6735 * x6421;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6792 = x6736 * x6493;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6793 = x6736 * x6505;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6794 = x6736 * x6421;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6795 = x6737 * x6495;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6796 = x6737 * x6507;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6797 = x6737 * x6423;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6798 = x6738 * x6495;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6799 = x6738 * x6507;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6800 = x6738 * x6423;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6801 = x6739 * x6491;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6802 = x6739 * x6503;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6803 = x6739 * x6419;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6804 = x6740 * x6491;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6805 = x6740 * x6503;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6806 = x6740 * x6419;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6807 = x6741 * x6497;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6808 = x6741 * x6509;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6809 = x6741 * x6425;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6810 = x6742 * x6497;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6811 = x6742 * x6509;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6812 = x6742 * x6425;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6813 = x6743 * x6499;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6814 = x6743 * x6511;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6815 = x6743 * x6427;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6816 = x6744 * x6499;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6817 = x6744 * x6511;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6818 = x6744 * x6427;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6819 = x6745 * x6489;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6820 = x6745 * x6501;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6821 = x6745 * x6417;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6822 = x6746 * x6489;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6823 = x6746 * x6501;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6824 = x6746 * x6417;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6825 = x6754 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6826 = x6756 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6827 = x6758 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6828 = x6760 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6829 = x6762 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6830 = x6764 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6831 = x6753 + x6793;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6832 = x6755 + x6799;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6833 = x6757 + x6805;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6834 = x6759 + x6811;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6835 = x6761 + x6817;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6836 = x6763 + x6823;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6837 = x6705 + x6790;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6838 = x6706 + x6796;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6839 = x6707 + x6802;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6840 = x6708 + x6808;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6841 = x6709 + x6814;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6842 = x6710 + x6820;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6843 = x6765 + x6719;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6844 = x6766 + x6717;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6845 = x6767 + x6718;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6846 = x6769 + x6722;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6847 = x6770 + x6720;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6848 = x6771 + x6721;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6849 = x6773 + x6725;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6850 = x6774 + x6723;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6851 = x6775 + x6724;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6852 = x6777 + x6728;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6853 = x6778 + x6726;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6854 = x6779 + x6727;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6855 = x6781 + x6731;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6856 = x6782 + x6729;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6857 = x6783 + x6730;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6858 = x6785 + x6734;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6859 = x6786 + x6732;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6860 = x6787 + x6733;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6861 = x6831 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6862 = x6832 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6863 = x6833 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6864 = x6834 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6865 = x6835 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6866 = x6836 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6867 = x6837 + x6792;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6868 = x6838 + x6798;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6869 = x6839 + x6804;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6870 = x6840 + x6810;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6871 = x6841 + x6816;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6872 = x6842 + x6822;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6873 = x6844 + x6791;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6874 = x6845 + x6789;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6875 = x6847 + x6797;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6876 = x6848 + x6795;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6877 = x6849 + x6863;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6878 = x6850 + x6803;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6879 = x6851 + x6801;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6880 = x6853 + x6809;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6881 = x6854 + x6807;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6882 = x6856 + x6815;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6883 = x6857 + x6813;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6884 = x6859 + x6821;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6885 = x6860 + x6819;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6886 = x6852 + x6864;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6887 = x6855 + x6865;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6888 = x6858 + x6866;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6889 = x6880 + x6828;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6890 = x6881 + x6812;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6891 = x6882 + x6829;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6892 = x6883 + x6818;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6893 = x6884 + x6830;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6894 = x6885 + x6824;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6895 = x6873 + x6825;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6896 = x6874 + x6794;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6897 = x6875 + x6826;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6898 = x6876 + x6800;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6899 = x6843 + x6861;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6900 = x6846 + x6862;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6901 = x6889 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6902 = x6890 * x6890;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6903 = x6890 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6904 = x6891 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6905 = x6892 * x6892;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6906 = x6892 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6907 = x6893 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6908 = x6894 * x6894;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6909 = x6894 * x1;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6910 = x6867 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6911 = x6868 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6912 = x6869 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6913 = x6870 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6914 = x6871 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6915 = x6872 * x0;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6916 = x6886 * x6886;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6917 = x6887 * x6887;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6918 = x6888 * x6888;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6919 = x6889 * x6889;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6920 = x6891 * x6891;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6921 = x6893 * x6893;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6922 = x6902 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6923 = x6905 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6924 = x6908 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6925 = -x6886;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6926 = -x6887;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6927 = -x6888;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6928 = x6878 + x6827;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6929 = x6879 + x6806;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6930 = x6776 + x6912;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6931 = x6889 + x6889;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6932 = x6890 + x6890;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6933 = x6891 + x6891;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6934 = x6892 + x6892;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6935 = x6893 + x6893;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6936 = x6894 + x6894;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6937 = x6780 + x6913;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6938 = x6784 + x6914;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6939 = x6788 + x6915;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6940 = x6768 + x6910;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x6941 = x6772 + x6911;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6942 = x6886 * x6932;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6943 = x6887 * x6934;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6944 = x6888 * x6936;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6945 = x6937 * x6931;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6946 = x6937 * x6937;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6947 = x6938 * x6933;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6948 = x6938 * x6938;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6949 = x6939 * x6935;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6950 = x6939 * x6939;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6951 = -x6937;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6952 = -x6938;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6953 = -x6939;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6954 = x6942 - x6919;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6955 = x6943 - x6920;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6956 = x6944 - x6921;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6957 = x6945 - x6916;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6958 = x6947 - x6917;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6959 = x6949 - x6918;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6960 = x6957 + x6922;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6961 = x6958 + x6923;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6962 = x6959 + x6924;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6963 = x6960 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6964 = x6961 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6965 = x6962 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6966 = x6963 * x6960;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6967 = x6964 * x6961;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6968 = x6965 * x6962;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6969 = x6954 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6970 = x6955 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6971 = x6956 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6972 = x6946 + x6969;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6973 = x6948 + x6970;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6974 = x6950 + x6971;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6975 = x6972 * x6972;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6976 = x6973 * x6973;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6977 = x6974 * x6974;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6978 = x6975 + x6966;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6979 = x6976 + x6967;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6980 = x6977 + x6968;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6981 = inv(x6978);
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6982 = inv(x6979);
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6983 = inv(x6980);
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6984 = x6972 * x6981;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6985 = x6973 * x6982;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6986 = x6974 * x6983;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6987 = x6960 * x6981;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6988 = x6961 * x6982;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6989 = x6962 * x6983;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6990 = x6886 * x6987;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6991 = x6887 * x6988;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6992 = x6888 * x6989;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6993 = x6937 * x6984;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6994 = x6938 * x6985;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6995 = x6939 * x6986;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6996 = x6925 * x6984;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6997 = x6926 * x6985;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6998 = x6927 * x6986;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x6999 = x6951 * x6987;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7000 = x6952 * x6988;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7001 = x6953 * x6989;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7002 = x6889 * x6984;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7003 = x6890 * x6984;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7004 = x6891 * x6985;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7005 = x6892 * x6985;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7006 = x6893 * x6986;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7007 = x6894 * x6986;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7008 = x6901 * x6987;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7009 = x6903 * x6987;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7010 = x6904 * x6988;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7011 = x6906 * x6988;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7012 = x6907 * x6989;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7013 = x6909 * x6989;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7014 = x6990 - x7003;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7015 = x6991 - x7005;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7016 = x6992 - x7007;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7017 = x6996 - x7009;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7018 = x6997 - x7011;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7019 = x6998 - x7013;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7020 = x6993 + x7008;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7021 = x6994 + x7010;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7022 = x6995 + x7012;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7023 = x6999 + x7002;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7024 = x7000 + x7004;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7025 = x7001 + x7006;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7026 = x6928 * x7014;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7027 = x6929 * x7014;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7028 = x6877 * x7014;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7029 = x6930 * x7020;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7030 = x6930 * x7023;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7031 = x6930 * x7014;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7032 = x6930 * x7017;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7033 = x6928 * x7020;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7034 = x6928 * x7023;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7035 = x6928 * x7017;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7036 = x6929 * x7020;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7037 = x6929 * x7023;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7038 = x6929 * x7017;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7039 = x6877 * x7020;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7040 = x6877 * x7023;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7041 = x6877 * x7017;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7042 = x7027 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7043 = x7026 + x7037;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7044 = x7028 + x7034;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7045 = x7030 + x7041;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7046 = x7031 + x7040;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7047 = x7032 + x7039;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7048 = x7043 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7049 = x7044 + x7038;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7050 = x7045 + x7033;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7051 = x7046 + x7035;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7052 = x7047 + x7048;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7053 = x7052 * x6896;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7054 = x7049 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7055 = x7052 * x6895;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7056 = x7052 * x6899;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7057 = x7052 * x6940;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7058 = x7050 + x7042;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7059 = x7051 + x7036;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7060 = x7029 + x7054;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7061 = x7058 * x6896;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7062 = x7059 * x6896;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7063 = x7060 * x6895;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7064 = x7060 * x6896;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7065 = x7060 * x6899;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7066 = x7060 * x6940;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7067 = x7058 * x6895;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7068 = x7058 * x6899;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7069 = x7058 * x6940;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7070 = x7059 * x6895;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7071 = x7059 * x6899;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7072 = x7059 * x6940;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7073 = x7062 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7074 = x7061 + x7070;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7075 = x7053 + x7067;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7076 = x7063 + x7056;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7077 = x7064 + x7055;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7078 = x7065 + x7057;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7079 = x7074 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7080 = x7075 + x7071;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7081 = x7076 + x7069;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7082 = x7077 + x7068;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7083 = x7078 + x7079;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7084 = x7083 * x7015;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7085 = x7080 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7086 = x7083 * x7021;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7087 = x7083 * x7024;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7088 = x7083 * x7018;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7089 = x7081 + x7073;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7090 = x7082 + x7072;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7091 = x7066 + x7085;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7092 = x7089 * x7015;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7093 = x7090 * x7015;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7094 = x7091 * x7021;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7095 = x7091 * x7024;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7096 = x7091 * x7015;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7097 = x7091 * x7018;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7098 = x7089 * x7021;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7099 = x7089 * x7024;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7100 = x7089 * x7018;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7101 = x7090 * x7021;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7102 = x7090 * x7024;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7103 = x7090 * x7018;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7104 = x7093 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7105 = x7092 + x7102;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7106 = x7084 + x7099;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7107 = x7095 + x7088;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7108 = x7096 + x7087;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7109 = x7097 + x7086;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7110 = x7105 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7111 = x7106 + x7103;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7112 = x7107 + x7098;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7113 = x7108 + x7100;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7114 = x7109 + x7110;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7115 = x7114 * x6898;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7116 = x7111 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7117 = x7114 * x6897;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7118 = x7114 * x6900;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7119 = x7114 * x6941;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7120 = x7112 + x7104;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7121 = x7113 + x7101;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7122 = x7094 + x7116;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7123 = x7120 * x6898;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7124 = x7121 * x6898;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7125 = x7122 * x6897;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7126 = x7122 * x6898;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7127 = x7122 * x6900;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7128 = x7122 * x6941;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7129 = x7120 * x6897;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7130 = x7120 * x6900;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7131 = x7120 * x6941;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7132 = x7121 * x6897;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7133 = x7121 * x6900;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7134 = x7121 * x6941;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7135 = x7124 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7136 = x7123 + x7132;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7137 = x7115 + x7129;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7138 = x7125 + x7118;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7139 = x7126 + x7117;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7140 = x7127 + x7119;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7141 = x7136 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7142 = x7137 + x7133;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7143 = x7138 + x7131;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7144 = x7139 + x7130;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7145 = x7140 + x7141;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7146 = x7145 * x7016;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7147 = x7142 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7148 = x7145 * x7022;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7149 = x7145 * x7025;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7150 = x7145 * x7019;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7151 = x7143 + x7135;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7152 = x7144 + x7134;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7153 = x7128 + x7147;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7154 = x7151 * x7016;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7155 = x7152 * x7016;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7156 = x7153 * x7022;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7157 = x7153 * x7025;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7158 = x7153 * x7016;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7159 = x7153 * x7019;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7160 = x7151 * x7022;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7161 = x7151 * x7025;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7162 = x7151 * x7019;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7163 = x7152 * x7022;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7164 = x7152 * x7025;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7165 = x7152 * x7019;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7166 = x7155 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7167 = x7154 + x7164;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7168 = x7146 + x7161;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7169 = x7157 + x7150;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7170 = x7158 + x7149;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7171 = x7159 + x7148;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7172 = x7167 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7173 = x7168 + x7165;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7174 = x7169 + x7160;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7175 = x7170 + x7162;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7176 = x7171 + x7172;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7177 = x7174 + x7166;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7178 = x7175 + x7163;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7179 = x7173 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7180 = x7156 + x7179;
      extern_args[0] = x7180;
      extern_args[1] = x7176;
      extern_args[2] = x7177;
      extern_args[3] = x7178;
      extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
    }
  }
  if (x10 != 0) {
    {
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7181 = arg3[0];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7182 = arg3[1];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7183 = arg3[10];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7184 = arg3[11];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7185 = arg3[12];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7186 = arg3[13];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7187 = arg3[14];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[3](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7188 = arg3[15];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7189 = arg3[16];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7190 = arg3[17];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7191 = arg3[18];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[4](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7192 = arg3[19];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7193 = arg3[2];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[0](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7194 = arg3[3];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7195 = arg3[4];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7196 = arg3[5];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[2](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7197 = arg3[6];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[1](FpExtReg)/elem[3](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7198 = arg3[7];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[0](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7199 = arg3[8];
      // loc("top(recursion::Top)/recursion::WomHeader/mix[2](FpExtReg)/elem[1](Reg)"("./zirgen/components/plonk.h":230:23))
      auto x7200 = arg3[9];
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x7201 = arg2[0 * steps + ((cycle - 0) & mask)];
      assert(x7201 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7202 = arg2[1 * steps + ((cycle - 0) & mask)];
      assert(x7202 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x7203 = arg2[10 * steps + ((cycle - 0) & mask)];
      assert(x7203 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7204 = arg2[11 * steps + ((cycle - 0) & mask)];
      assert(x7204 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7205 = arg2[12 * steps + ((cycle - 0) & mask)];
      assert(x7205 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7206 = arg2[13 * steps + ((cycle - 0) & mask)];
      assert(x7206 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7207 = arg2[14 * steps + ((cycle - 0) & mask)];
      assert(x7207 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x7208 = arg2[15 * steps + ((cycle - 0) & mask)];
      assert(x7208 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7209 = arg2[16 * steps + ((cycle - 0) & mask)];
      assert(x7209 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7210 = arg2[17 * steps + ((cycle - 0) & mask)];
      assert(x7210 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7211 = arg2[18 * steps + ((cycle - 0) & mask)];
      assert(x7211 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7212 = arg2[19 * steps + ((cycle - 0) & mask)];
      assert(x7212 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7213 = arg2[2 * steps + ((cycle - 0) & mask)];
      assert(x7213 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7214 = arg2[3 * steps + ((cycle - 0) & mask)];
      assert(x7214 != Fp::invalid());
      // loc("top(recursion::Top)/recursion::WomHeader/element(recursion::impl::WomPlonkElement)/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7215 = arg2[4 * steps + ((cycle - 0) & mask)];
      assert(x7215 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/addr(Reg)"("zirgen/circuit/recursion/wom.cpp":32:27))
      auto x7216 = arg2[5 * steps + ((cycle - 0) & mask)];
      assert(x7216 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[0](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7217 = arg2[6 * steps + ((cycle - 0) & mask)];
      assert(x7217 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[1](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7218 = arg2[7 * steps + ((cycle - 0) & mask)];
      assert(x7218 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[2](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7219 = arg2[8 * steps + ((cycle - 0) & mask)];
      assert(x7219 != Fp::invalid());
      // loc("top(recursion::Top)/mux(Mux)/checked_bytes(recursion::CheckedBytes)/wom_body(recursion::WomBody)/plonk_body(PlonkBody)/recursion::impl::WomPlonkElement/data[3](Reg)"("zirgen/circuit/recursion/wom.cpp":54:14))
      auto x7220 = arg2[9 * steps + ((cycle - 0) & mask)];
      assert(x7220 != Fp::invalid());
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7221 = x7181 * x7201;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7222 = x7181 * x7203;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7223 = x7181 * x7208;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7224 = x7181 * x7216;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7225 = x7182 * x7201;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7226 = x7182 * x7203;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7227 = x7182 * x7208;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7228 = x7182 * x7216;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7229 = x7183 * x7205;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7230 = x7183 * x7210;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7231 = x7183 * x7213;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7232 = x7183 * x7218;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7233 = x7184 * x7205;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7234 = x7184 * x7210;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7235 = x7184 * x7213;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7236 = x7184 * x7218;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7237 = x7186 * x7206;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7238 = x7186 * x7211;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7239 = x7186 * x7214;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7240 = x7186 * x7219;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7241 = x7187 * x7206;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7242 = x7187 * x7211;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7243 = x7187 * x7214;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7244 = x7187 * x7219;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7245 = x7188 * x7206;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7246 = x7188 * x7211;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7247 = x7188 * x7214;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7248 = x7188 * x7219;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7249 = x7190 * x7207;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7250 = x7190 * x7212;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7251 = x7190 * x7215;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7252 = x7190 * x7220;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7253 = x7191 * x7207;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7254 = x7191 * x7212;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7255 = x7191 * x7215;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7256 = x7191 * x7220;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7257 = x7192 * x7207;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7258 = x7192 * x7212;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7259 = x7192 * x7215;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7260 = x7192 * x7220;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7261 = x7193 * x7201;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7262 = x7193 * x7203;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7263 = x7193 * x7208;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7264 = x7193 * x7216;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7265 = x7194 * x7201;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7266 = x7194 * x7203;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7267 = x7194 * x7208;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7268 = x7194 * x7216;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7269 = x7196 * x7202;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7270 = x7196 * x7204;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7271 = x7196 * x7209;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7272 = x7196 * x7217;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7273 = x7197 * x7202;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7274 = x7197 * x7204;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7275 = x7197 * x7209;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7276 = x7197 * x7217;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7277 = x7198 * x7202;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7278 = x7198 * x7204;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7279 = x7198 * x7209;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7280 = x7198 * x7217;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7281 = x7200 * x7205;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7282 = x7200 * x7210;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7283 = x7200 * x7213;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7284 = x7200 * x7218;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7285 = x7185 * x7206;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7286 = x7185 * x7211;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7287 = x7185 * x7214;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7288 = x7185 * x7219;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7289 = x7189 * x7207;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7290 = x7189 * x7212;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7291 = x7189 * x7215;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7292 = x7189 * x7220;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7293 = x7195 * x7202;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7294 = x7195 * x7204;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7295 = x7195 * x7209;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7296 = x7195 * x7217;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7297 = x7199 * x7205;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7298 = x7199 * x7210;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7299 = x7199 * x7213;
      // loc("./zirgen/components/plonk.h":230:23)
      auto x7300 = x7199 * x7218;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7301 = x7221 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7302 = x7222 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7303 = x7223 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7304 = x7224 + x2;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7305 = x7301 + x7293;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7306 = x7302 + x7294;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7307 = x7303 + x7295;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7308 = x7304 + x7296;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7309 = x7305 + x7299;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7310 = x7306 + x7297;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7311 = x7307 + x7298;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7312 = x7308 + x7300;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7313 = x7225 + x7269;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7314 = x7226 + x7270;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7315 = x7227 + x7271;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7316 = x7228 + x7272;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7317 = x7261 + x7273;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7318 = x7262 + x7274;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7319 = x7263 + x7275;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7320 = x7264 + x7276;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7321 = x7265 + x7277;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7322 = x7266 + x7278;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7323 = x7267 + x7279;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7324 = x7268 + x7280;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7325 = x7309 + x7287;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7326 = x7310 + x7285;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7327 = x7311 + x7286;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7328 = x7312 + x7288;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7329 = x7313 + x7283;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7330 = x7314 + x7281;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7331 = x7315 + x7282;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7332 = x7316 + x7284;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7333 = x7317 + x7231;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7334 = x7318 + x7229;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7335 = x7319 + x7230;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7336 = x7320 + x7232;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7337 = x7321 + x7235;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7338 = x7322 + x7233;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7339 = x7323 + x7234;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7340 = x7324 + x7236;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7341 = x7325 + x7291;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7342 = x7326 + x7289;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7343 = x7327 + x7290;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7344 = x7328 + x7292;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7345 = x7329 + x7239;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7346 = x7330 + x7237;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7347 = x7331 + x7238;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7348 = x7332 + x7240;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7349 = x7333 + x7243;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7350 = x7334 + x7241;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7351 = x7335 + x7242;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7352 = x7336 + x7244;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7353 = x7337 + x7247;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7354 = x7338 + x7245;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7355 = x7339 + x7246;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7356 = x7340 + x7248;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7357 = x7345 + x7251;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7358 = x7346 + x7249;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7359 = x7349 + x7255;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7360 = x7350 + x7253;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7361 = x7353 + x7259;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7362 = x7354 + x7257;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7363 = x7347 + x7250;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7364 = x7348 + x7252;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7365 = x7351 + x7254;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7366 = x7352 + x7256;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7367 = x7355 + x7258;
      // loc("./zirgen/components/plonk.h":230:17)
      auto x7368 = x7356 + x7260;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7369 = x7363 * x7361;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7370 = x7364 * x7362;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7371 = x7363 * x7357;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7372 = x7363 * x7359;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7373 = x7363 * x7341;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7374 = x7364 * x7358;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7375 = x7364 * x7360;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7376 = x7364 * x7342;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7377 = x7365 * x7361;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7378 = x7366 * x7362;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7379 = x7367 * x7361;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7380 = x7368 * x7362;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7381 = x7343 * x7357;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7382 = x7343 * x7359;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7383 = x7343 * x7361;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7384 = x7343 * x7341;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7385 = x7344 * x7358;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7386 = x7344 * x7360;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7387 = x7344 * x7362;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7388 = x7344 * x7342;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7389 = x7365 * x7357;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7390 = x7365 * x7359;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7391 = x7365 * x7341;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7392 = x7366 * x7358;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7393 = x7366 * x7360;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7394 = x7366 * x7342;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7395 = x7367 * x7357;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7396 = x7367 * x7359;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7397 = x7367 * x7341;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7398 = x7368 * x7358;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7399 = x7368 * x7360;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7400 = x7368 * x7342;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7401 = x7379 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7402 = x7380 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7403 = x7377 + x7396;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7404 = x7378 + x7399;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7405 = x7369 + x7390;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7406 = x7370 + x7393;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7407 = x7381 + x7373;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7408 = x7382 + x7371;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7409 = x7383 + x7372;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7410 = x7385 + x7376;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7411 = x7386 + x7374;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7412 = x7387 + x7375;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7413 = x7403 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7414 = x7404 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7415 = x7405 + x7395;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7416 = x7406 + x7398;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7417 = x7408 + x7391;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7418 = x7409 + x7389;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7419 = x7410 + x7414;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7420 = x7411 + x7394;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7421 = x7412 + x7392;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7422 = x7407 + x7413;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7423 = x7417 + x7401;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7424 = x7418 + x7397;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7425 = x7423 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7426 = x7424 * x7424;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7427 = x7424 * x1;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7428 = x7415 * x0;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7429 = x7416 * x0;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7430 = x7422 * x7422;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7431 = x7423 * x7423;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7432 = x7426 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7433 = -x7422;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7434 = x7420 + x7402;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7435 = x7421 + x7400;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7436 = x7388 + x7429;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7437 = x7423 + x7423;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7438 = x7424 + x7424;
      // loc("./zirgen/components/plonk.h":232:16)
      auto x7439 = x7384 + x7428;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7440 = x7422 * x7438;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7441 = x7439 * x7437;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7442 = x7439 * x7439;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7443 = -x7439;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7444 = x7440 - x7431;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7445 = x7441 - x7430;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7446 = x7445 + x7432;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7447 = x7446 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7448 = x7447 * x7446;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7449 = x7444 * x1;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7450 = x7442 + x7449;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7451 = x7450 * x7450;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7452 = x7451 + x7448;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7453 = inv(x7452);
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7454 = x7450 * x7453;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7455 = x7446 * x7453;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7456 = x7422 * x7455;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7457 = x7439 * x7454;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7458 = x7433 * x7454;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7459 = x7443 * x7455;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7460 = x7423 * x7454;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7461 = x7424 * x7454;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7462 = x7425 * x7455;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7463 = x7427 * x7455;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7464 = x7456 - x7461;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7465 = x7458 - x7463;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7466 = x7457 + x7462;
      // loc("./zirgen/components/plonk.h":274:42)
      auto x7467 = x7459 + x7460;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7468 = x7434 * x7464;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7469 = x7435 * x7464;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7470 = x7419 * x7464;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7471 = x7436 * x7466;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7472 = x7436 * x7467;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7473 = x7436 * x7464;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7474 = x7436 * x7465;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7475 = x7434 * x7466;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7476 = x7434 * x7467;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7477 = x7434 * x7465;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7478 = x7435 * x7466;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7479 = x7435 * x7467;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7480 = x7435 * x7465;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7481 = x7419 * x7466;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7482 = x7419 * x7467;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7483 = x7419 * x7465;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7484 = x7469 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7485 = x7468 + x7479;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7486 = x7470 + x7476;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7487 = x7472 + x7483;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7488 = x7473 + x7482;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7489 = x7474 + x7481;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7490 = x7485 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7491 = x7486 + x7480;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7492 = x7487 + x7475;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7493 = x7488 + x7477;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7494 = x7489 + x7490;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7495 = x7492 + x7484;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7496 = x7493 + x7478;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7497 = x7491 * x0;
      // loc("./zirgen/components/plonk.h":274:16)
      auto x7498 = x7471 + x7497;
      extern_args[0] = x7498;
      extern_args[1] = x7494;
      extern_args[2] = x7495;
      extern_args[3] = x7496;
      extern_plonkWriteAccum_wom(ctx, cycle, "wom", extern_args, extern_outs);
    }
  }
}
