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

#include "core/log.h"
#include "core/util.h"

#include "rv32im/ffi.h"

struct RawWrapper {
  RawProver* raw;

  RawWrapper(RawProver* raw) : raw(raw) {}
  ~RawWrapper() { risc0_circuit_rv32im_m3_prover_free(raw); }
};

void runTest(const std::string& name) {
  auto fullname = "rv32im/rvtest/" + name;
  auto elf = risc0::loadFile(fullname);

  RawWrapper wrapper(risc0_circuit_rv32im_m3_prover_new_cpu(14));

  const char* err = risc0_circuit_rv32im_m3_preflight(wrapper.raw, elf.data(), elf.size());
  if (err != nullptr) {
    throw std::runtime_error(err);
  }

  err = risc0_circuit_rv32im_m3_prove(wrapper.raw);
  if (err != nullptr) {
    throw std::runtime_error(err);
  }
}

int main() {
  LOG(0, "Hello world");
  runTest("add");
  runTest("addi");
}
