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

struct ProofResult {
  bool isError;
  uint32_t* data;
  uint8_t* error;
  size_t len;
};

extern "C" ProofResult* risc0_circuit_rv32im_m3_prove(const uint8_t* elf_ptr, size_t elf_len);
extern "C" void proof_dealloc(ProofResult* result);

void runTest(const std::string& name) {
  auto fullname = "rv32im/rvtest/" + name;
  auto elf = risc0::loadFile(fullname);
  ProofResult* res = risc0_circuit_rv32im_m3_prove(elf.data(), elf.size());
  if (res->isError) {
    throw std::runtime_error(std::string(reinterpret_cast<const char*>(res->error), res->len));
  } 
  proof_dealloc(res);
}

int main() {
  LOG(0, "Hello world");
  runTest("add");
  runTest("addi");
}
