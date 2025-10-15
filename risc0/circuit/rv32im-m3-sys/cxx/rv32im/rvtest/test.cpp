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
#include "rv32im/test/test_prove.h"

#include <assert.h>
#include <iostream>

using namespace risc0;

void runTest(const std::string& name, size_t po2 = 12) {
  rv32im::NullHostIO io;
  runTestBinary("rv32im/rvtest/" + name, io, po2);
}

int main() {
  runTest("rvc", 14);
  runTest("add");
  runTest("sub");
  runTest("xor");
  runTest("or");
  runTest("and");
  runTest("slt");
  runTest("sltu");
  runTest("addi");
  runTest("xori");
  runTest("ori");
  runTest("andi");
  runTest("slti");
  runTest("sltiu");
  runTest("beq");
  runTest("bne");
  runTest("blt");
  runTest("bge");
  runTest("bltu");
  runTest("bgeu");
  runTest("jal");
  runTest("jalr");
  runTest("lui");
  runTest("auipc");
  runTest("sll");
  runTest("slli");
  runTest("mul");
  runTest("mulh");
  runTest("mulhsu");
  runTest("mulhu");
  runTest("srl");
  runTest("sra");
  runTest("srli");
  runTest("srai");
  runTest("div");
  runTest("divu");
  runTest("rem");
  runTest("remu");
  runTest("lb");
  runTest("lh");
  runTest("lw");
  runTest("lbu");
  runTest("lhu");
  runTest("sb");
  runTest("sh", 13);
  runTest("sw", 13);
  return 0;
}
