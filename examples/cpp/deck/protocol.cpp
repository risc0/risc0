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
  // This is super lame, we really need to fix the mismatch between host/dev SHA
  std::string dataStr(reinterpret_cast<const char*>(&t), sizeof(T));
  return shaHash(dataStr);
}

Dealer::Dealer() = default;

DealerCommitMessage Dealer::getCommit(uint32_t deckSize) {
  DealerCommitMessage out;
  this->deckSize = deckSize;
  out.dealerKeyDigest = shaDigest(dealerKey);
  out.deckSize = deckSize;
  return out;
}

ShuffleProofMessage Dealer::shuffle(const PlayerCommitMessage& msg) {
  playerKey = msg.playerKey;
  Prover prover("examples/cpp/deck/shuffle_proof");
  prover.addInput(deckSize);
  prover.getKeyStore()["dealer"] = dealerKey;
  prover.getKeyStore()["player"] = playerKey;
  ShuffleProofMessage out;
  out.proof = prover.run();
  const uint8_t* outPtr = static_cast<const uint8_t*>(prover.getOutput(0, deckSize));
  cards.insert(cards.begin(), outPtr, outPtr + deckSize);
  return out;
}

CardResponseMessage Dealer::revealCard(const CardRequestMessage& msg) {
  Prover prover("examples/cpp/deck/card_proof");
  prover.addInput(deckSize);
  prover.addInput(msg.pos);
  prover.addInput(cards.data(), cards.size());
  prover.getKeyStore()["dealer"] = dealerKey;
  prover.getKeyStore()["player"] = playerKey;
  CardResponseMessage out;
  out.proof = prover.run();
  return out;
}

Player::Player() {}

PlayerCommitMessage Player::getCommit(const DealerCommitMessage& msg) {
  dealerKeyDigest = msg.dealerKeyDigest;
  deckSize = msg.deckSize;
  PlayerCommitMessage out;
  out.playerKey = playerKey;
  return out;
}

void Player::verifyShuffleProof(const ShuffleProofMessage& msg) {
  msg.proof.verify("examples/cpp/deck/shuffle_proof");
  REQUIRE(msg.proof.message.size() == sizeof(ShuffleProofContents));
  const ShuffleProofContents* data =
      reinterpret_cast<const ShuffleProofContents*>(msg.proof.message.data());
  REQUIRE(data->playerKey == playerKey);
  REQUIRE(data->dealerKeyDigest == dealerKeyDigest);
  deckDigest = data->deckDigest;
}

CardRequestMessage Player::makeRequest(uint32_t pos) {
  CardRequestMessage out;
  out.pos = pos;
  lastRequest = pos;
  return out;
}

uint32_t Player::verifyResponse(const CardResponseMessage& msg) {
  msg.proof.verify("examples/cpp/deck/card_proof");
  REQUIRE(msg.proof.message.size() == sizeof(CardResponseContents));
  const CardResponseContents* data =
      reinterpret_cast<const CardResponseContents*>(msg.proof.message.data());
  REQUIRE(data->deckDigest == deckDigest);
  REQUIRE(data->pos == lastRequest);
  return data->card;
}
