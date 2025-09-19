// Copyright 2025 RISC Zero, Inc.
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

#include "platform.h"
#include <assert.h>
#include <stdint.h>

union u32_cast {
  uint32_t value;
  uint8_t buffer[4];
};

int main() {
  // TODO introduce entropy into memory image (for zk)
  sha256_state* hasher = init_sha256();

  // Read two u32 values from the host, assuming LE byte order.
  union u32_cast a;
  union u32_cast b;
  assert(env_read(a.buffer, 4) == 4);
  assert(env_read(b.buffer, 4) == 4);

  a.value *= b.value;

  env_commit(hasher, a.buffer, sizeof(a.buffer));
  env_exit(hasher, 0);

  return 0;
}
