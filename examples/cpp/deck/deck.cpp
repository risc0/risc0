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

#include "deck.h"

using namespace risc0;

Deck::Deck(KeyPtr key, size_t size) {
  REQUIRE(size <= 256);
  cards.resize(size);
  for (size_t i = 0; i < size; i++) {
    cards[i] = i;
  }
  PRNG prng(key);
  // Fisher and Yates shuffle
  for (size_t i = 0; i < size - 1; i++) {
    uint32_t j = prng.generate(size - i) + i;
    std::swap(cards[i], cards[j]);
  }
}

const DigestPtr Deck::mac(KeyPtr key) {
  return shaMAC(key, cards.data(), cards.size());
}
