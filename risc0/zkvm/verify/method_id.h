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

#include "risc0/core/util.h"
#include "risc0/zkp/core/sha256.h"
#include "risc0/zkvm/circuit/constants.h"

namespace risc0 {

constexpr size_t kCodeDigestCount = log2Ceil(kMaxCycles / kMinCycles) + 1;

using MethodID = std::array<ShaDigest, kCodeDigestCount>;

MethodID readMethodID(const std::string& filename);

} // namespace risc0
