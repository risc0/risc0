// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
  if (const char* level = std::getenv("RISC0_LOG")) {
    risc0::setLogLevel(std::atoi(level));
  }
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
