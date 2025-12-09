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

uint32_t totalShards = 1;
uint32_t shardIndex = 0;
uint32_t testNum = 0;

void runTest(const std::string& name, size_t po2 = 13) {
  LOG(0, "Running test: " << name);
  if (testNum % totalShards != shardIndex) {
    testNum++;
    return;
  }
  rv32im::NullHostIO io;
  std::map<uint32_t, uint32_t> words;
  std::string testName = "rv32im/rvtest/" + name;
  rv32im::loadUserMachineV3(words, "rv32im/rvtest/emu_kernel", testName);
  auto image = rv32im::MemoryImage::fromWords(words);
  runTest(image, io, po2);
  testNum++;
}

int main() {
  if (getenv("TEST_TOTAL_SHARDS")) {
    totalShards = atoi(getenv("TEST_TOTAL_SHARDS"));
  }
  if (getenv("TEST_SHARD_INDEX")) {
    shardIndex = atoi(getenv("TEST_SHARD_INDEX"));
  }
  runTest("amoadd_w");
  runTest("amoand_w");
  runTest("amomax_w");
  runTest("amomaxu_w");
  runTest("amomin_w");
  runTest("amominu_w");
  runTest("amoor_w");
  runTest("amoswap_w");
  runTest("amoxor_w");
  //runTest("lrsc", 17);  Runs, but very slow
  return 0;
}
