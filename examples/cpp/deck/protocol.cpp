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

#include "risc0/core/util.h"

using namespace risc0;

template <typename T> ShaDigest shaDigest(const T& t) {
  // TODO: Fix mismatch between host & guest SHA API.
  std::string str(reinterpret_cast<const char*>(&t), sizeof(T));
  return shaHash(str);
}

Dealer::Dealer() = default;

DealerCommitMessage Dealer::getCommit(uint32_t deckSize) {
  this->deckSize = deckSize;
  return DealerCommitMessage{shaDigest(dealerKey), deckSize};
}

ShuffleMessage Dealer::shuffle(const PlayerCommitMessage& msg) {
  playerKey = msg.playerKey;
  Prover prover("examples/cpp/deck/shuffle_method");
  prover.writeInput(deckSize);
  prover.setKey("dealer", dealerKey);
  prover.setKey("player", playerKey);
  Receipt receipt = prover.run();
  cards = prover.getOutput();
  return ShuffleMessage{receipt};
}

CardResponseMessage Dealer::revealCard(const CardRequestMessage& msg) {
  Prover prover("examples/cpp/deck/card_method");
  prover.writeInput(deckSize);
  prover.writeInput(msg.pos);
  prover.writeInput(cards.data(), cards.size());
  prover.setKey("dealer", dealerKey);
  prover.setKey("player", playerKey);
  Receipt receipt = prover.run();
  return CardResponseMessage{receipt};
}

Player::Player() = default;

PlayerCommitMessage Player::getCommit(const DealerCommitMessage& msg) {
  dealerKeyDigest = msg.dealerKeyDigest;
  deckSize = msg.deckSize;
  return PlayerCommitMessage{playerKey};
}

void Player::verifyShuffleMessage(const ShuffleMessage& msg) {
  msg.receipt.verify("examples/cpp/deck/shuffle_method");
  ShuffleContent data = msg.receipt.read<ShuffleContent>();
  REQUIRE(data.playerKey == playerKey);
  REQUIRE(data.dealerKeyDigest == dealerKeyDigest);
  deckDigest = data.deckDigest;
}

CardRequestMessage Player::makeRequest(uint32_t pos) {
  lastRequest = pos;
  return CardRequestMessage{pos};
}

uint32_t Player::verifyResponse(const CardResponseMessage& msg) {
  msg.receipt.verify("examples/cpp/deck/card_method");
  CardResponseContent data = msg.receipt.read<CardResponseContent>();
  REQUIRE(data.deckDigest == deckDigest);
  REQUIRE(data.pos == lastRequest);
  return data.card;
}
