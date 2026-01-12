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

#include <unistd.h>

int main() {
  uint32_t x = 0;
  uint32_t tot = 0;
  read(0, &x, sizeof(uint32_t));
  for (uint32_t i = 0; i < x; i++) {
    for (uint32_t j = 0; j < x; j++) {
      tot += i * j % 17;
      tot %= 107;
    }
  }
  write(1, &tot, sizeof(uint32_t));
  return 0;
}
