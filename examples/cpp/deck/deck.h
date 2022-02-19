#pragma once

#include "risc0/r0vm/cpp/device/risc0.h"
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
