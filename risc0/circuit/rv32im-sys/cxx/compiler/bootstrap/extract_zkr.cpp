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

#include "compiler/bootstrap/extract_zkr.h"

#include "rv32im/circuit/verify.h"
#include "verify/rv32im.h"
#include "zirgen/circuit/predicates/predicates.h"
#include "zirgen/circuit/recursion/code.h"
#include "zirgen/circuit/verify/verify.h"

namespace {

namespace Zll = zirgen::Zll;
namespace recursion = zirgen::recursion;

namespace cl = llvm::cl;

struct ValWrap {
  zirgen::Val val;

  ValWrap() : val(uint64_t(0)) {}
  ValWrap(uint32_t c) : val(uint64_t(c)) {}
  ValWrap(risc0::Fp c) : val(uint64_t(c.asUInt32())) {}
  explicit ValWrap(zirgen::Val val) : val(val) {}
  ValWrap(ValWrap v0, ValWrap v1, ValWrap v2, ValWrap v3) {
    zirgen::Val m1({0, 1, 0, 0});
    zirgen::Val m2({0, 0, 1, 0});
    zirgen::Val m3({0, 0, 0, 1});
    val = v0.val + v1.val * m1 + v2.val * m2 + v3.val * m3;
  }
  ValWrap operator+(const ValWrap& rhs) const { return ValWrap(val + rhs.val); }
  ValWrap operator+=(const ValWrap& rhs) { return *this = *this + rhs; }
  ValWrap operator-(const ValWrap& rhs) const { return ValWrap(val - rhs.val); }
  ValWrap operator-=(const ValWrap& rhs) { return *this = *this - rhs; }
  ValWrap operator-() const { return ValWrap(-val); }
  ValWrap operator*(const ValWrap& rhs) const { return ValWrap(val * rhs.val); }
  ValWrap operator*=(const ValWrap& rhs) { return *this = *this * rhs; }
};

class RV32IMM3CircuitInterface : public zirgen::verify::CircuitInterfaceV3 {
public:
  RV32IMM3CircuitInterface() {
    setupVerifyInfo(info);
    // Translate V3 metadata to Zirgen's versions of things
    size_t curTap = 0;
    for (const risc0::Group& group : info.taps.getGroups()) {
      tapSet.groups.emplace_back();
      auto& zGroup = tapSet.groups.back();
      for (const risc0::Column& col : group.getColumns()) {
        zGroup.regs.emplace_back();
        auto& zCol = zGroup.regs.back();
        zCol.offset = col.column;
        zCol.combo = col.comboId;
        zCol.tapPos = curTap;
        for (const risc0::Tap& tap : col.getTaps()) {
          zCol.backs.push_back(tap.back);
          tapMap[tap] = curTap;
          curTap++;
        }
      }
    }
    tapSet.tapCount = curTap;
    for (const risc0::Combo& combo : info.taps.getCombos()) {
      tapSet.combos.emplace_back();
      auto& zCombo = tapSet.combos.back();
      zCombo.combo = combo.comboId;
      for (uint32_t back : combo.backs) {
        zCombo.backs.push_back(back);
      }
    }
    groupInfo.resize(info.groups.size());
    for (size_t i = 0; i < info.groups.size(); i++) {
      groupInfo[i].globalCount = info.groups[i].globalCount;
      groupInfo[i].mixCount = 4 * info.groups[i].mixCount;
    }
  }

  const Zll::TapSet& getTaps() const override { return tapSet; }
  const llvm::ArrayRef<zirgen::verify::GroupInfoV3> getGroupInfo() const override {
    return groupInfo;
  }

  struct FakeReg {
    ValWrap val;
    FakeReg(zirgen::Val val) : val(val) {}
    template <typename T, typename C> void applyInner(C& ctx) {}
    template <typename C> void applyInner(C& ctx) {}
    template <typename C> void verify(C& ctx) {}
    template <typename C> void addArguments(C& ctx) {}
    ValWrap get() { return val; }
  };

  std::vector<FakeReg>
  makeRegs(llvm::ArrayRef<zirgen::Val> u, const risc0::Group& group, uint32_t back) const {
    std::vector<FakeReg> ret;
    for (const risc0::Column& col : group.getColumns()) {
      zirgen::Val val(uint64_t(0));
      for (const risc0::Tap& tap : col.getTaps()) {
        if (tap.back == back && tapMap.count(tap)) {
          val = u[tapMap.at(tap)];
        }
      }
      ret.emplace_back(val);
    }
    return ret;
  }

  virtual zirgen::Val computePolyExt(llvm::ArrayRef<zirgen::Val> u,
                                     llvm::ArrayRef<zirgen::Val> globalsIn,
                                     llvm::ArrayRef<zirgen::Val> mixIn,
                                     zirgen::Val polyMix,
                                     zirgen::Val z) const override {
    auto data = makeRegs(u, info.taps.getGroups()[0], 0);
    auto accum = makeRegs(u, info.taps.getGroups()[1], 0);
    auto prevAccum = makeRegs(u, info.taps.getGroups()[1], 1);
    std::vector<ValWrap> globals;
    for (size_t i = 0; i < globalsIn.size(); i++) {
      globals.emplace_back(globalsIn[i]);
    }
    std::vector<ValWrap> mix;
    for (size_t i = 0; i < mixIn.size() / 4; i++) {
      mix.emplace_back(ValWrap(mixIn[i * 4]),
                       ValWrap(mixIn[i * 4 + 1]),
                       ValWrap(mixIn[i * 4 + 2]),
                       ValWrap(mixIn[i * 4 + 3]));
    }
    return verifyCircuit<FakeReg, ValWrap, ValWrap, SameTypeEqzHandler<ValWrap>>(data.data(),
                                                                                 accum.data(),
                                                                                 prevAccum.data(),
                                                                                 globals.data(),
                                                                                 mix.data(),
                                                                                 ValWrap(polyMix),
                                                                                 ValWrap(3 * z))
        .val;
  }

private:
  risc0::VerifyCircuitInfo info;
  Zll::TapSet tapSet;
  std::map<risc0::Tap, size_t> tapMap;
  llvm::SmallVector<zirgen::verify::GroupInfoV3> groupInfo;
};

} // namespace

namespace risc0 {

void addLift(zirgen::Module& module, size_t po2) {
  RV32IMM3CircuitInterface circuit;
  module.addFunc<3>("lift_rv32im_m3_" + std::to_string(po2),
                    {zirgen::gbuf(recursion::kOutSize), zirgen::ioparg(), zirgen::ioparg()},
                    [&](zirgen::Buffer out, zirgen::ReadIopVal rootIop, zirgen::ReadIopVal seal) {
                      // TODO: Consider what I need to actually commit to
                      zirgen::DigestVal root = rootIop.readDigests(1)[0];
                      auto globals = zirgen::verify::verifyV3(seal, po2, circuit);
                      llvm::ArrayRef inStream(globals);
                      auto claim = zirgen::predicates::ReceiptClaim::fromRv32imV3(inStream, po2);
                      std::vector<zirgen::Val> outStream;
                      claim.write(outStream);
                      doExtern("write", "", 0, outStream);
                      out.setDigest(0, root, "root");
                      out.setDigest(1, claim.digest(), "outDigest");
                    });
}

void addLiftPovw(zirgen::Module& module, size_t po2) {
  RV32IMM3CircuitInterface circuit;
  module.addFunc<3>("lift_rv32im_m3_povw_" + std::to_string(po2),
                    {zirgen::gbuf(recursion::kOutSize), zirgen::ioparg(), zirgen::ioparg()},
                    [&](zirgen::Buffer out, zirgen::ReadIopVal rootIop, zirgen::ReadIopVal seal) {
                      // TODO: Consider what I need to actually commit to
                      zirgen::DigestVal root = rootIop.readDigests(1)[0];
                      auto globals = zirgen::verify::verifyV3(seal, po2, circuit);
                      llvm::ArrayRef inStream(globals);
                      auto claimAndNonce =
                          zirgen::predicates::readReceiptClaimV3AndPovwNonce(inStream, po2);
                      auto workClaim = zirgen::predicates::wrap_povw(
                          po2, claimAndNonce.second, claimAndNonce.first);
                      std::vector<zirgen::Val> outStream;
                      workClaim.write(outStream);
                      doExtern("write", "", 0, outStream);
                      out.setDigest(0, root, "root");
                      out.setDigest(1, workClaim.digest(), "outDigest");
                    });
}

} // namespace risc0
