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

extern "C" void risc0_main(Env* env) {
  // Read the size of the deck from the user
  uint32_t deckSize = env->read<uint32_t>();
  // Get the dealer shuffle key
  KeyPtr dealerKey = env->getKey("dealer", KeyMode::EXISTING);
  // Get the player shuffle key
  KeyPtr playerKey = env->getKey("player", KeyMode::EXISTING);
  // Mix them
  Key jointKey(*dealerKey, *playerKey);
  // Build a deck of the right size
  Deck deck(&jointKey, deckSize);
  // Send an output with the full deck state
  env->write(deck.cards.data(), deck.cards.size());
  // Commit to all the relevant bits
  env->commit(dealerKey->commit());
  env->commit(*playerKey);
  env->commit(deck.mac(dealerKey));
  env->commit(deckSize);
}
