# Cryptographic deck of cards (C++)

This example is implements a cryptographic deck of cards.

Specifically, there are two parties, a dealer and a player.  Both parties
provide random data, which is combined to shuffle the deck in such a way that
neither party can control the output.  Additionally, the player is unable to
see the state of the deck, aside from cards that they are explicitly dealt.
We use zero knowledge proofs to allow the player to verify that the dealer is
not cheating (i.e. controlling the shuffling, misdealing, etc.).  However, note
that unlike a real deck of cards, the dealer can see the state of the entire
deck.
