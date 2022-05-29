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

#pragma once

#include <array>
#include <memory>

#include "risc0/core/util.h"
#include "risc0/zkp/core/sha256.h"
#include "risc0/zkvm/circuit/constants.h"

namespace risc0 {

static constexpr size_t kCodeDigestCount = log2Ceil(kMaxCycles / kMinCycles) + 1;
using MethodDigests = std::array<ShaDigest, kCodeDigestCount>;
static constexpr size_t digestBytes = sizeof(MethodDigests);

class MethodID {
public:
  MethodID(const MethodDigests& methodDigests);
  static MethodID fromElf(const std::string& elfPath);
  static MethodID fromBytes(const std::array<uint8_t, 384>& bytes);
  static MethodID fromBytes(const uint8_t* bytes);
  std::array<uint8_t, digestBytes> toBytes() const;

private:
  const MethodDigests _digests;
};

// cxx doesn't support constructors or static methods...https://github.com/dtolnay/cxx/issues/280
std::unique_ptr<MethodID> method_id_from_elf(const std::string& path);
std::unique_ptr<MethodID> method_id_from_bytes(const std::array<uint8_t, digestBytes>& bytes);

} // namespace risc0
