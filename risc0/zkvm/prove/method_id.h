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

static constexpr size_t numMethodDigests = log2Ceil(kMaxCycles / kMinCycles) + 1;

// These types are likely to change relatively soon. But, for now:
// A MethodDigest is intended for internal use in verification
// A MethodId is an intentionally opaque version of a MethodDigest for use in APIs
using MethodDigest = std::array<ShaDigest, numMethodDigests>;
using MethodId = std::array<uint8_t, sizeof(MethodDigest)>;

MethodId makeMethodId(const std::string& elfPath);
MethodId makeMethodId(const uint8_t* bytes, const size_t len);
MethodId makeMethodId(const MethodDigest& digest);

MethodDigest makeMethodDigest(const std::string& elfPath);
MethodDigest makeMethodDigest(const MethodId& id);

} // namespace risc0
