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

/// @file risc0.h
/// @brief The risc0 guest-side API.

#pragma once

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "risc0/zkvm/sdk/cpp/guest/env.h"
#include "risc0/zkvm/sdk/cpp/guest/fail.h"
#include "risc0/zkvm/sdk/cpp/guest/key.h"
#include "risc0/zkvm/sdk/cpp/guest/prng.h"
#include "risc0/zkvm/sdk/cpp/guest/sha.h"
