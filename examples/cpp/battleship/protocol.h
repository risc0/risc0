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

#pragma once

#include "battleship.h"

#include "risc0/zkp/core/sha256.h"
#include "risc0/zkvm/sdk/cpp/host/receipt.h"

#include <vector>

struct InitMessage {
  risc0::Receipt receipt;

  struct Content {
    risc0::ShaDigest state;

    template <typename Archive> void transfer(Archive& ar) { ar.transfer(state); }
  };

  Content decode() const;
};

struct TurnMessage {
  Position shot;
};

struct RoundMessage {
  risc0::Receipt receipt;

  struct Content {
    risc0::ShaDigest old_state;
    risc0::ShaDigest new_state;
    Position shot;
    HitType hit;

    template <typename Archive> void transfer(Archive& ar) {
      ar.transfer(old_state);
      ar.transfer(new_state);
      ar.transfer(shot);
      ar.transfer(reinterpret_cast<uint32_t&>(hit));
    }
  };

  Content decode() const;
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
