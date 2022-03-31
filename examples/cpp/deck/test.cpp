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

#include "protocol.h"

#include "risc0/core/log.h"

#include <gtest/gtest.h>

TEST(Deck, Protocol) {
  Dealer alice;
  Player bob;

  LOG(0, "Making initial commitments");
  DealerCommitMessage dealerCommit = alice.getCommit(52);
  PlayerCommitMessage playerCommit = bob.getCommit(dealerCommit);
  LOG(0, "Shuffling deck");
  ShuffleMessage shuffleMsg = alice.shuffle(playerCommit);
  std::string cardStr = "";
  for (size_t i = 0; i < 52; i++) {
    cardStr += " " + std::to_string(alice.getCards()[i]);
  }
  LOG(0, "Cards: " << cardStr);
  LOG(0, "Verifying shuffle");
  bob.verifyShuffleMessage(shuffleMsg);
  LOG(0, "Reading card # 3");
  CardRequestMessage cardRequest = bob.makeRequest(3);
  CardResponseMessage cardResponse = alice.revealCard(cardRequest);
  uint32_t card = bob.verifyResponse(cardResponse);
  LOG(0, "Card = " << card);
  ASSERT_EQ(card, alice.getCards()[3]);
}
