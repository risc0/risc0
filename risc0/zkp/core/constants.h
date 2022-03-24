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

#include "risc0/zkp/core/devs.h"

namespace risc0 {

CONSTSCALAR size_t kMaxCyclesPo2 = 23;
CONSTSCALAR size_t kMaxCycles = size_t(1) << kMaxCyclesPo2;

CONSTSCALAR size_t kQueries = 50; // ~100 bits of conjectured security

CONSTSCALAR size_t kInvRate = 4;
CONSTSCALAR size_t kMaxDegree = kInvRate + 1;
CONSTSCALAR size_t kFriFold = 16;
CONSTSCALAR size_t kFriMinDegree = 256;

CONSTSCALAR size_t kExtSize = 4;
CONSTSCALAR size_t kCheckSize = kInvRate * kExtSize;

} // namespace risc0
