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

#include "zirgen/circuit/predicates/predicates.h"
#include "zirgen/circuit/recursion/code.h"
#include "zirgen/circuit/verify/verify.h"
#include "zirgen/compiler/codegen/codegen.h"

using namespace risc0;
using namespace zirgen;
using namespace zirgen::verify;
using namespace zirgen::predicates;

namespace cl = llvm::cl;

static cl::opt<std::string>
    outputDir("output-dir", cl::desc("Output directory"), cl::value_desc("dir"), cl::Required);

class HelloCircuitInterface : public CircuitInterfaceV3 {
public:
  HelloCircuitInterface() {
    // We could automatically extract the tapSet and groupInfo from the circuit
    // info, but it's easier to just do it by hand for now.
    tapSet.groups.resize(3);
    tapSet.groups[0].regs.push_back({0, 0, 0, {0}});
    tapSet.groups[1].regs.push_back({0, 0, 1, {0}});
    tapSet.groups[2].regs.push_back({0, 0, 2, {0}});
    tapSet.combos.push_back({0, {0}});
    tapSet.tapCount = 3;

    groupInfo.push_back({0, 0});
    groupInfo.push_back({0, 0});
    groupInfo.push_back({0, 0});
  }

  const Zll::TapSet& getTaps() const override { return tapSet; }
  const llvm::ArrayRef<GroupInfoV3> getGroupInfo() const override { return groupInfo; }

  virtual Val computePolyExt(llvm::ArrayRef<Val> u,
                             llvm::ArrayRef<Val> out,
                             llvm::ArrayRef<Val> accumMix,
                             Val polyMix,
                             Val z) const override {
    Val tot({0, 0, 0, 0});
    Val mul({1, 0, 0, 0});
    auto eqz = [&](Val inner) {
      tot = tot + mul * inner;
      mul = mul * polyMix;
    };
    eqz(u[0]);
    eqz(u[1]);
    eqz(u[2] * (u[2] - Val(1)));
    return tot;
  }

private:
  Zll::TapSet tapSet;
  llvm::SmallVector<GroupInfoV3> groupInfo;
};

int main(int argc, char* argv[]) {
  llvm::InitLLVM y(argc, argv);
  registerEdslCLOptions();
  llvm::cl::ParseCommandLineOptions(argc, argv, "keccak predicates");

  Module module;
  size_t po2 = 12;
  HelloCircuitInterface circuit;
  module.addFunc<3>("hello_lift_12",
                    {gbuf(recursion::kOutSize), ioparg(), ioparg()},
                    [&](Buffer out, ReadIopVal rootIop, ReadIopVal seal) {
                      // DigestVal root = rootIop.readDigests(1)[0];
                      zirgen::verify::verifyV3(seal, po2, circuit);
                      // out.setDigest(0, root, "root");
                    });

  module.optimize();
  module.dump(true);
  module.getModule().walk([&](mlir::func::FuncOp func) { zirgen::emitRecursion(outputDir, func); });
}
