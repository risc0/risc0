// Copyright 2022 Risc0, Inc.
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

#include "risc0/core/log.h"
#include "risc0/zkp/accel/accel.h"
#include "risc0/zkp/core/sha256.h"
#include "risc0/zkp/prove/prove.h"
#include "risc0/zkvm/prove/riscv.h"
#include "risc0/zkvm/sdk/cpp/host/receipt.h"

#include <gtest/gtest.h>

using namespace risc0;

struct TestParam {
  std::string lang;
  std::string prefix;
};

class CoreTests : public testing::TestWithParam<TestParam> {
protected:
  ShaDigest testSHA(const std::string& str) {
    Prover prover(GetParam().prefix + "test_sha");
    prover.writeInput(static_cast<uint32_t>(str.size()));
    prover.writeInput(str.data(), str.size());
    Receipt receipt = prover.run();
    receipt.verify(GetParam().prefix + "test_sha");
    return receipt.read<ShaDigest>();
  }

  void testMemIO(const std::vector<std::pair<uint32_t, uint32_t>>& in) {
    Prover prover(GetParam().prefix + "test_mem");
    prover.writeInput(static_cast<uint32_t>(in.size()));
    for (auto pair : in) {
      prover.writeInput(pair.first);
      prover.writeInput(pair.second);
    }
    Receipt receipt = prover.run();
    receipt.verify(GetParam().prefix + "test_mem");
  }
};

TEST_P(CoreTests, SHA) {
  accelStartup();
  ASSERT_EQ(testSHA(""),
            ShaDigest({0xe3b0c442,
                       0x98fc1c14,
                       0x9afbf4c8,
                       0x996fb924,
                       0x27ae41e4,
                       0x649b934c,
                       0xa495991b,
                       0x7852b855}));
  ASSERT_EQ(testSHA("a"),
            ShaDigest({
                0xca978112,
                0xca1bbdca,
                0xfac231b3,
                0x9a23dc4d,
                0xa786eff8,
                0x147c4e72,
                0xb9807785,
                0xafee48bb,
            }));
  ASSERT_EQ(testSHA("abc"),
            ShaDigest({0xba7816bf,
                       0x8f01cfea,
                       0x414140de,
                       0x5dae2223,
                       0xb00361a3,
                       0x96177a9c,
                       0xb410ff61,
                       0xf20015ad}));
  ASSERT_EQ(testSHA("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"),
            ShaDigest({0x248d6a61,
                       0xd20638b8,
                       0xe5c02693,
                       0x0c3e6039,
                       0xa33ce459,
                       0x64ff2167,
                       0xf6ecedd4,
                       0x19db06c1}));
}

TEST_P(CoreTests, Align) {
  ASSERT_EQ(align(0, 64), 0);
  ASSERT_EQ(align(1, 64), 64);
  ASSERT_EQ(align(63, 64), 64);
  ASSERT_EQ(align(64, 64), 64);
  ASSERT_EQ(align(65, 64), 128);
  ASSERT_EQ(align(127, 64), 128);
  ASSERT_EQ(align(128, 64), 128);
}

TEST_P(CoreTests, MemoryIO) {
  // Double write to WOM are fine
  testMemIO({
      {kMemCommitStart, 1},
      {kMemCommitStart, 1},
  });
  // Double write to WOM with different values throw
  EXPECT_THROW(testMemIO({
                   {kMemCommitStart, 1},
                   {kMemCommitStart, 2},
               }),
               std::runtime_error);
  // But they are OK at different addresses
  testMemIO({
      {kMemCommitStart, 1},
      {kMemCommitStart + 4, 2},
  });
  // Aligned write is fine
  testMemIO({{kMemHeapStart, 1}});
  // Unaligned write is bad
  EXPECT_THROW(testMemIO({{kMemHeapStart + 1, 1}}), std::runtime_error);
  // Aligned read is fine
  testMemIO({{kMemHeapStart, 0}});
  // Unaligned read is bad
  EXPECT_THROW(testMemIO({{kMemHeapStart + 1, 0}}), std::runtime_error);
}

TEST_P(CoreTests, Fail) {
  std::string elfPath = GetParam().prefix + "test_fail";

  // Check that a compliant host will fault.
  Prover prover(elfPath);
  EXPECT_THROW(prover.run(), std::runtime_error);

  // Check that a host that does not implement onFault will still fault.
  MemoryHandler handler;
  std::unique_ptr<ProveCircuit> circuit = getRiscVProveCircuit(elfPath, handler);
  EXPECT_THROW(prove(*circuit), std::runtime_error);
}

void doMemcpyTest(uint32_t srcOffset, uint32_t destOffset, uint32_t size) {
  // Make src + dest buffers of test patterns
  std::vector<uint8_t> srcBuf(1024);
  std::vector<uint8_t> destBuf(1024);
  // Make fill patterns that are unlikely to be accidentially right
  for (size_t i = 0; i < 1024; i++) {
    if (i % 2 == 0) {
      srcBuf[i] = i % 256;
      destBuf[i] = 0xa5 - i % 256;
    } else {
      srcBuf[i] = (i >> 8);
      destBuf[i] = (i >> 8) * 33;
    }
  }
  // Make an prover and have it do a memcpy
  Prover prover("risc0/zkvm/sdk/cpp/guest/test/test_memcpy");
  prover.writeInput(srcBuf.data(), 1024);
  prover.writeInput(destBuf.data(), 1024);
  prover.writeInput(srcOffset);
  prover.writeInput(destOffset);
  prover.writeInput(size);
  Receipt receipt = prover.run();
  receipt.verify("risc0/zkvm/sdk/cpp/guest/test/test_memcpy");
  // Do the memcpy/memset on the host
  if (srcOffset == 1024) {
    memset(destBuf.data() + destOffset, 0xff, size);
  } else {
    memcpy(destBuf.data() + destOffset, srcBuf.data() + srcOffset, size);
  }
  // Compare results
  EXPECT_EQ(memcmp(destBuf.data(), prover.getOutput().data(), 1024), 0);
}

void doMemsetTest(uint32_t destOffset, uint32_t size) {
  doMemcpyTest(1024, destOffset, size);
}

TEST(CoreTests, Memcpy) {
  // Nice easy aligned words
  doMemcpyTest(16, 100, 32);
  // Both unaligned to the same offset
  doMemcpyTest(17, 101, 32);
  // Also, a non-even size
  doMemcpyTest(17, 101, 53);
  // Two different alignments
  doMemcpyTest(17, 103, 32);
  // Two different alignments, random size
  doMemcpyTest(17, 103, 31);
  // Bigger test case, matching alignment
  doMemcpyTest(17, 101, 153);
}

TEST(CoreTests, Memset) {
  doMemsetTest(17, 173);
}

INSTANTIATE_TEST_SUITE_P(All,
                         CoreTests,
                         testing::Values(TestParam{"cpp", "risc0/zkvm/sdk/cpp/guest/test/"},
                                         TestParam{"rust", "risc0/zkvm/sdk/rust/guest/"}),
                         [](const testing::TestParamInfo<TestParam>& info) {
                           return info.param.lang;
                         });
