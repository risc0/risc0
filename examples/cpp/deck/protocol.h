#pragma once

#include "risc0/core/key.h"
#include "risc0/zkp/core/sha256_cpu.h"
#include "risc0/zkp/prove/proof.h"

// Deck protocol:
// 1) Deal picks a random key K_d, and sends a commitment to player: H(K_d)
// 2) Player picks a random key K_p, and send it to the dealer
// 3) Dealer makes a PRNG using (K_d xor K_p), and shuffles a deck.
//    Dealer produces a proof asserting: H(K_d), K_p, MAC(K_d, D).
//    Note, we use a MAC to blind the deck so that player can't brute force
//    the last few cards if most of them are dealt.
// 4) Player requests a card at position P:
// 5) The dealer reveals the card: proving: MAC(K_d, D),  P, C
// 4 + 5 can be done as many times as required.  Game specific logic should check the
// player requests are valid.

// The initial message, send from dealer to player, to ensure dealer shuffles fairly
struct DealerCommitMessage {
  risc0::ShaDigest dealerKeyDigest;
  uint32_t deckSize;
};

struct PlayerCommitMessage {
  risc0::Key playerKey;
};

struct ShuffleProofContents {
  risc0::ShaDigest dealerKeyDigest;
  risc0::Key playerKey;
  risc0::ShaDigest deckDigest;
  uint32_t deckSize;
};

struct ShuffleProofMessage {
  risc0::Proof proof;
};

struct CardRequestMessage {
  uint32_t pos;
};

struct CardResponseContents {
  risc0::ShaDigest deckDigest;
  uint32_t pos;
  uint32_t card;
};

struct CardResponseMessage {
  risc0::Proof proof;
};

class Dealer {
public:
  // Make a new dealer.
  Dealer();

  // Make a new key and return a commitment to it
  DealerCommitMessage getCommit(uint32_t deckSize);

  // Make a shuffle proof
  ShuffleProofMessage shuffle(const PlayerCommitMessage& msg);

  // Handle a card request
  CardResponseMessage revealCard(const CardRequestMessage& msg);

  // Direct access to cards for testing
  const std::vector<uint8_t> getCards() const { return cards; }

private:
  risc0::Key dealerKey;
  risc0::Key playerKey;
  risc0::ShaDigest deckDigest;
  std::vector<uint8_t> cards;
  uint32_t deckSize;
};

class Player {
public:
  // Make a new player
  Player();

  // Get commit and send new key
  PlayerCommitMessage getCommit(const DealerCommitMessage& msg);

  // Verify shuffle proof
  void verifyShuffleProof(const ShuffleProofMessage& msg);

  // Make a request to reveal a certain card
  CardRequestMessage makeRequest(uint32_t pos);

  // Verify the response to the request and get the card value out
  uint32_t verifyResponse(const CardResponseMessage& msg);

private:
  risc0::ShaDigest dealerKeyDigest;
  risc0::Key playerKey;
  risc0::ShaDigest deckDigest;
  uint32_t deckSize;
  uint32_t lastRequest;
};
