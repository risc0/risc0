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

#include <cstdint>

#ifndef RISCV
#include <iostream>
#endif

const uint32_t NUM_SHIPS = 5;
const uint32_t BOARD_SIZE = 10;

struct Position {
  uint32_t x;
  uint32_t y;

  template <typename Archive> void transfer(Archive& ar) {
    ar.transfer(x);
    ar.transfer(y);
  }

  bool operator==(const Position& rhs) const;
  bool operator!=(const Position& rhs) const;
};

enum ShipDirection : uint16_t {
  Horizontal,
  Vertical,
};

enum HitType : uint32_t {
  Miss,
  Hit,
  SunkCarrier,
  SunkBattleship,
  SunkCruiser,
  SunkSubmarine,
  SunkDestroyer,
};

struct Ship {
  Position pos;
  ShipDirection dir;
  uint16_t hit_mask;

  template <typename Archive> void transfer(Archive& ar) {
    ar.transfer(pos);
    ar.transfer(reinterpret_cast<uint16_t&>(dir));
    ar.transfer(hit_mask);
  }

  bool operator==(const Ship& rhs) const;
};

const uint32_t SHIP_SPANS[NUM_SHIPS] = {
    5, // carrier
    4, // battleship
    3, // cruiser
    3, // submarine
    2, // destroyer
};

const uint32_t SUNK_MASKS[NUM_SHIPS] = {
    0x00000001f,
    0x00000000f,
    0x000000007,
    0x000000007,
    0x000000003,
};

struct GameState {
  Ship ships[NUM_SHIPS];
  uint32_t salt;

  template <typename Archive> void transfer(Archive& ar) {
    for (Ship& ship : ships) {
      ar.transfer(ship);
    }
    ar.transfer(salt);
  }

  bool operator==(const GameState& rhs) const;
};

struct RoundParams {
  GameState state;
  Position shot;

  template <typename Archive> void transfer(Archive& ar) {
    ar.transfer(state);
    ar.transfer(shot);
  }
};

struct RoundResult {
  GameState state;
  HitType hit;

  template <typename Archive> void transfer(Archive& ar) {
    ar.transfer(state);
    ar.transfer(reinterpret_cast<uint32_t&>(hit));
  }

  bool operator==(const RoundResult& rhs) const;
};

bool check_board(const GameState& state);

RoundResult process_round(const RoundParams& params);

#ifndef RISCV

std::ostream& operator<<(std::ostream& os, const ShipDirection& dir);
std::ostream& operator<<(std::ostream& os, const Position& pos);
std::ostream& operator<<(std::ostream& os, const GameState& state);
std::ostream& operator<<(std::ostream& os, const RoundResult& result);

#endif
