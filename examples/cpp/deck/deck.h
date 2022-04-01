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

#include "risc0/zkvm/sdk/cpp/guest/risc0.h"

#include <vector>

struct Deck {
public:
  // Make a deck of cards of a particular size, shuffled by a key
  Deck(risc0::KeyPtr key, size_t size);

  // Get it's digest
  const risc0::DigestPtr mac(risc0::KeyPtr key);

  // The cards themselves
  std::vector<uint8_t> cards;
};
