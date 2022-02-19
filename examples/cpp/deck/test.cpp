#include "protocol.h"

#include "risc0/core/log.h"

#include <gtest/gtest.h>

TEST(Deck, Protocol) {
  Dealer alice;
  Player bob;

  LOG(0, "Making initial commitments");
  auto dealerCommit = alice.getCommit(52);
  auto playerCommit = bob.getCommit(dealerCommit);
  LOG(0, "Shuffling deck");
  auto shuffleProof = alice.shuffle(playerCommit);
  std::string cardStr = "";
  for (size_t i = 0; i < 52; i++) {
    cardStr += " " + std::to_string(alice.getCards()[i]);
  }
  LOG(0, "Cards: " << cardStr);
  LOG(0, "Verifying shuffle");
  bob.verifyShuffleProof(shuffleProof);
  LOG(0, "Reading card # 3");
  auto cardRequest = bob.makeRequest(3);
  auto cardResponse = alice.revealCard(cardRequest);
  auto card = bob.verifyResponse(cardResponse);
  LOG(0, "Card = " << card);
  ASSERT_EQ(card, alice.getCards()[3]);
}
