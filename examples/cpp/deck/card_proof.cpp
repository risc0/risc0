#include "deck.h"

using namespace risc0;

extern "C" void risc0_main(Env* env) {
  // Read the deck size
  uint32_t deckSize = env->read<uint32_t>();
  // Read the card position
  uint32_t pos = env->read<uint32_t>();
  // Sanity check
  REQUIRE(deckSize <= 256);
  REQUIRE(pos < deckSize);
  // Read the deck as cards
  const uint8_t* cards = static_cast<uint8_t*>(env->read(deckSize));
  // Get the card the user wants
  uint32_t card = cards[pos];
  // Get the dealer shuffle key
  KeyPtr dealerKey = env->getKey("dealer", KeyMode::EXISTING);
  // Commit to all the relevant bits
  env->commit(shaMAC(dealerKey, cards, deckSize));
  env->commit(pos);
  env->commit(card);
}
