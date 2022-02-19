#pragma once

#include "battleship.h"

#include "risc0/zkp/core/sha256.h"
#include "risc0/zkp/prove/proof.h"

#include <vector>

struct InitMessage {
  risc0::Proof proof;

  struct Parts {
    risc0::ShaDigest state;
  };

  const Parts& getParts() const;
};

struct TurnMessage {
  Position shot;
};

struct RoundMessage {
  risc0::Proof proof;

  struct Parts {
    risc0::ShaDigest old_state;
    risc0::ShaDigest new_state;
    Position shot;
    HitType hit;
  };

  const Parts& getParts() const;
};

class Battleship {
public:
  Battleship(const char* name, const GameState& state) : name(name), state(state) {}

  InitMessage init();

  void onInitMsg(const InitMessage& msg);

  TurnMessage turn(const Position& shot);

  RoundMessage onTurnMsg(const TurnMessage& msg);

  void onRoundMsg(const RoundMessage& msg);

  const GameState& getState() { return state; }

private:
  std::string name;
  GameState state;
  Position last_shot;
  risc0::ShaDigest peer_state;
};
