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

#include "hal/hal.h"

#include <iostream>
#include <vector>

using namespace risc0;

int main() {
  IHalPtr hal = getGpuHal();
  auto out = hal->allocateArray<Digest>(5);
  auto in = hal->allocateMatrix<Fp>(5, 10);
  {
    PinnedMatrixWO<Fp> pIn(hal, in);
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 10; j++) {
        pIn(i, j) = i * 101 + j;
      }
    }
  }
  hal->hashRows(out, in);
  {
    PinnedArrayRO<Digest> pOut(hal, out);
    for (size_t i = 0; i < 5; i++) {
      std::cerr << "Hey: " << pOut[i] << "\n";
    }
  }
  std::cerr << "Done\n";
}
