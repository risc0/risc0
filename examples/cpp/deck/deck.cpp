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
