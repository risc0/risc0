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

#include "risc0/core/log.h"
#include "risc0/zkp/accel/accel.h"

#include "battleship.h"
#include "protocol.h"

using risc0::hex;

int main(int argc, char* argv[]) {
  if (const char* env = std::getenv("RISC0_LOG")) {
    risc0::setLogLevel(std::atoi(env));
  }
  risc0::accelStartup();

  // prompt user for initial positions

  GameState state{
      {
          {{2, 3}, Vertical, 0x0000},   // A: Carrier
          {{3, 1}, Horizontal, 0x0000}, // B: Battleship
          {{4, 7}, Vertical, 0x0000},   // C: Cruiser
          {{7, 5}, Horizontal, 0x0000}, // D: Submarine
          {{7, 7}, Horizontal, 0x0000}, // E: Destroyer
      },
      0xDEADBEEF // salt
  };

  Battleship player("name", state);

  InitMessage init = player.init();

  // send InitMessage to peer

  // TODO: determine who is the first player

  // while game hasn't halted
  //   prompt user for next turn
  //   create TurnMessage: turn()
  //   send TurnMessage to peer
  //   recv RoundMessage from peer
  //   process RoundMessage: onRoundMsg()
  //   recv TurnMessage from peer
  //   process TurnMessage: onturnMsg()

  return 0;
}
