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

#include "compiler/extractor/RecordingVal.h"
#include "core/log.h"
#include "rv32im/circuit/verify.h"
#include "rv32im/emu/blocks.h"

#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"

void emitTaps(const std::string path);
void emitPolyExt(const std::string path);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    LOG(0, "usage: " << argv[0] << " <output_path>");
    return 1;
  }
  std::string path = argv[1];
  try {
    emitTaps(path + "/taps.rs");
    emitPolyExt(path + "/poly_ext.rs");
  } catch (const std::exception& err) {
    LOG(0, "Caught exception: " << err.what());
    return 1;
  }
  return 0;
}
