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

#include "battleship.h"

#ifndef RISCV
#include "risc0/core/log.h"
#endif

static bool check_position(const Ship& ship, uint32_t span) {
  if (ship.pos.x > 9 || ship.pos.y > 9 ||
      (ship.dir != ShipDirection::Horizontal && ship.dir != ShipDirection::Vertical))
    return false;

  uint32_t limit = BOARD_SIZE - span;
  return (ship.dir == ShipDirection::Horizontal && ship.pos.x <= limit) ||
         (ship.dir == ShipDirection::Vertical && ship.pos.y <= limit);
}

bool check_board(const GameState& state) {
  bool board[BOARD_SIZE][BOARD_SIZE];
  for (uint32_t y = 0; y < BOARD_SIZE; y++) {
    for (uint32_t x = 0; x < BOARD_SIZE; x++) {
      board[y][x] = false;
    }
  }

  for (uint32_t i = 0; i < NUM_SHIPS; i++) {
    const Ship& ship = state.ships[i];
    uint32_t span = SHIP_SPANS[i];
    if (!check_position(ship, span))
      return false;
    if (ship.hit_mask != 0)
      return false;

    uint32_t x = ship.pos.x;
    uint32_t y = ship.pos.y;
    if (ship.dir == ShipDirection::Horizontal) {
      for (uint32_t dx = 0; dx < span; dx++) {
        if (board[y][x + dx])
          return false;
        board[y][x + dx] = true;
      }
    } else {
      for (uint32_t dy = 0; dy < span; dy++) {
        if (board[y + dy][x])
          return false;
        board[y + dy][x] = true;
      }
    }
  }

#ifndef RISCV
  LOG(0, " | 0 1 2 3 4 5 6 7 8 9 |");
  for (uint32_t y = 0; y < BOARD_SIZE; y++) {
    LOG(0,
        y << "| " << board[y][0] << " " << board[y][1] << " " << board[y][2] << " " << board[y][3]
          << " " << board[y][4] << " " << board[y][5] << " " << board[y][6] << " " << board[y][7]
          << " " << board[y][8] << " " << board[y][9] << " |");
  }
#endif

  return true;
}

RoundResult process_round(const RoundParams& params) {
  GameState state = params.state;
  const Position& shot = params.shot;
  for (uint32_t i = 0; i < NUM_SHIPS; i++) {
    Ship& ship = state.ships[i];
    uint32_t span = SHIP_SPANS[i];
    uint32_t x = ship.pos.x;
    uint32_t y = ship.pos.y;
    if (ship.dir == ShipDirection::Horizontal && shot.y == y &&
        (shot.x >= x && shot.x <= x + span)) {
      ship.hit_mask |= 1 << (shot.x - x);
      if (ship.hit_mask == SUNK_MASKS[i]) {
        return RoundResult{state, static_cast<HitType>(SunkCarrier + i)};
      }
      return RoundResult{state, Hit};
    } else if (ship.dir == ShipDirection::Vertical && shot.x == x &&
               (shot.y >= y && shot.y <= y + span)) {
      ship.hit_mask |= 1 << (shot.y - y);
      if (ship.hit_mask == SUNK_MASKS[i]) {
        return RoundResult{state, static_cast<HitType>(SunkCarrier + i)};
      }
      return RoundResult{state, Hit};
    }
  }
  return RoundResult{state, Miss};
}

bool Position::operator==(const Position& rhs) const {
  return x == rhs.x && y == rhs.y;
}

bool Position::operator!=(const Position& rhs) const {
  return x != rhs.x && y != rhs.y;
}

bool Ship::operator==(const Ship& rhs) const {
  return pos == rhs.pos && dir == rhs.dir && hit_mask == rhs.hit_mask;
}

bool GameState::operator==(const GameState& rhs) const {
  return ships[0] == rhs.ships[0] && //
         ships[1] == rhs.ships[1] && //
         ships[2] == rhs.ships[2] && //
         ships[3] == rhs.ships[3] && //
         ships[4] == rhs.ships[4] && //
         salt == rhs.salt;
}

bool RoundResult::operator==(const RoundResult& rhs) const {
  return state == rhs.state && hit == rhs.hit;
}

#ifndef RISCV

std::ostream& operator<<(std::ostream& os, const ShipDirection& dir) {
  switch (dir) {
  case ShipDirection::Horizontal:
    os << "H";
    break;
  case ShipDirection::Vertical:
    os << "V";
    break;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os, const Position& pos) {
  os << "{" << pos.x << ", " << pos.y << "}";
  return os;
}

std::ostream& operator<<(std::ostream& os, const GameState& state) {
  os << "GameState{";
  for (uint32_t i = 0; i < NUM_SHIPS; i++) {
    const Ship& ship = state.ships[i];
    if (i > 0) {
      os << ", ";
    }
    os << "{" << ship.pos << ", " << ship.dir << ", ";
    for (unsigned j = 0; j < SHIP_SPANS[i]; j++) {
      if (ship.hit_mask & (1 << j)) {
        os << 'X';
      } else {
        os << 'O';
      }
    }
    os << "}";
  }
  os << "}";
  return os;
}

std::ostream& operator<<(std::ostream& os, const RoundResult& result) {
  os << "RoundResult{" << result.state << ", " << result.hit << "}";
  return os;
}

#endif
