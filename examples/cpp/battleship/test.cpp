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
#include "protocol.h"
#include "risc0/core/log.h"
#include "risc0/zkp/accel/accel.h"
#include "risc0/zkp/prove/prove.h"
#include "risc0/zkp/verify/verify.h"
#include "risc0/zkvm/platform/io.h"
#include "risc0/zkvm/platform/memory.h"

#include <gtest/gtest.h>

TEST(Battleship, Basic) {
  GameState state{{
                      {{2, 3}, Vertical, 0x0000},
                      {{3, 1}, Horizontal, 0x0000},
                      {{4, 7}, Vertical, 0x0000},
                      {{7, 5}, Horizontal, 0x0000},
                      {{7, 7}, Horizontal, 0x0000},
                  },
                  0xDEADBEEF};

  ASSERT_TRUE(check_board(state));
}

TEST(Battleship, Overlap) {
  GameState state{{
                      {{2, 3}, Vertical, 0x0000},
                      {{3, 1}, Horizontal, 0x0000},
                      {{2, 3}, Vertical, 0x0000},
                      {{7, 5}, Horizontal, 0x0000},
                      {{7, 7}, Horizontal, 0x0000},
                  },
                  0xDEADBEEF};

  ASSERT_FALSE(check_board(state));
}

TEST(Battleship, Rounds) {
  // Board
  //  | 0 1 2 3 4 5 6 7 8 9 |
  // 0|                     |
  // 1|       B B B B       |
  // 2|                     |
  // 3|     A               |
  // 4|     A               |
  // 5|     A         D D D |
  // 6|     A               |
  // 7|     A   C     E E   |
  // 8|         C           |
  // 9|         C           |

  GameState state1{{
                       {{2, 3}, Vertical, 0x0000},
                       {{3, 1}, Horizontal, 0x0000},
                       {{4, 7}, Vertical, 0x0000},
                       {{7, 5}, Horizontal, 0x0000},
                       {{7, 7}, Horizontal, 0x0000},
                   },
                   0xDEADBEEF};
  RoundParams params1{state1, {1, 1}};
  RoundResult result1{state1, Miss};
  ASSERT_EQ(process_round(params1), result1);

  RoundParams params2{state1, {4, 1}};
  RoundResult result2{GameState{{
                                    {{2, 3}, Vertical, 0x0000},
                                    {{3, 1}, Horizontal, 0x0002},
                                    {{4, 7}, Vertical, 0x0000},
                                    {{7, 5}, Horizontal, 0x0000},
                                    {{7, 7}, Horizontal, 0x0000},
                                },
                                0xDEADBEEF},
                      Hit};
  ASSERT_EQ(process_round(params2), result2);

  // Duplicate hit results in no state change
  RoundParams params3{state1, {4, 1}};
  RoundResult result3 = result2;
  ASSERT_EQ(process_round(params3), result3);

  RoundParams params4{result3.state, {3, 1}};
  RoundResult result4{GameState{{
                                    {{2, 3}, Vertical, 0x0000},
                                    {{3, 1}, Horizontal, 0x0003},
                                    {{4, 7}, Vertical, 0x0000},
                                    {{7, 5}, Horizontal, 0x0000},
                                    {{7, 7}, Horizontal, 0x0000},
                                },
                                0xDEADBEEF},
                      Hit};
  ASSERT_EQ(process_round(params4), result4);

  RoundParams params5{result4.state, {6, 1}};
  RoundResult result5{GameState{{
                                    {{2, 3}, Vertical, 0x0000},
                                    {{3, 1}, Horizontal, 0x000b},
                                    {{4, 7}, Vertical, 0x0000},
                                    {{7, 5}, Horizontal, 0x0000},
                                    {{7, 7}, Horizontal, 0x0000},
                                },
                                0xDEADBEEF},
                      Hit};
  ASSERT_EQ(process_round(params5), result5);

  RoundParams params6{result5.state, {5, 1}};
  RoundResult result6{GameState{{
                                    {{2, 3}, Vertical, 0x0000},
                                    {{3, 1}, Horizontal, 0x000f},
                                    {{4, 7}, Vertical, 0x0000},
                                    {{7, 5}, Horizontal, 0x0000},
                                    {{7, 7}, Horizontal, 0x0000},
                                },
                                0xDEADBEEF},
                      SunkBattleship};
  ASSERT_EQ(process_round(params6), result6);
}

TEST(Battleship, Protocol) {
  risc0::accelStartup();

  // Player Alice
  //  | 0 1 2 3 4 5 6 7 8 9 |
  // 0|                     |
  // 1|       B B B B       |
  // 2|                     |
  // 3|     A               |
  // 4|     A               |
  // 5|     A         D D D |
  // 6|     A               |
  // 7|     A   C     E E   |
  // 8|         C           |
  // 9|         C           |
  GameState alice_state{
      {
          {{2, 3}, Vertical, 0x0000},   // A: Carrier
          {{3, 1}, Horizontal, 0x0000}, // B: Battleship
          {{4, 7}, Vertical, 0x0000},   // C: Cruiser
          {{7, 5}, Horizontal, 0x0000}, // D: Submarine
          {{7, 7}, Horizontal, 0x0000}, // E: Destroyer
      },
      0xDEADBEEF // salt
  };

  // Player Bob
  //  | 0 1 2 3 4 5 6 7 8 9 |
  // 0| B B B B           A |
  // 1| C                 A |
  // 2| C                 A |
  // 3| C                 A |
  // 4| D                 A |
  // 5| D                   |
  // 6| D                   |
  // 7| E                   |
  // 8| E                   |
  // 9|                     |
  GameState bob_state{
      {
          {{9, 0}, Vertical, 0x0000},   // A: Carrier
          {{0, 0}, Horizontal, 0x0000}, // B: Battleship
          {{0, 1}, Vertical, 0x0000},   // C: Cruiser
          {{0, 4}, Vertical, 0x0000},   // D: Submarine
          {{0, 7}, Vertical, 0x0000},   // E: Destroyer
      },
      0xCAFECAFE // salt
  };

  Battleship alice("alice", alice_state);
  Battleship bob("bob", bob_state);

  bob.onInitMsg(alice.init());
  LOG(0, "Bob  : " << bob.getState());
  alice.onInitMsg(bob.init());
  LOG(0, "Alice: " << alice.getState());

  alice.onRoundMsg(bob.onTurnMsg(alice.turn({1, 1})));
  LOG(0, "Bob  : " << bob.getState());
  bob.onRoundMsg(alice.onTurnMsg(bob.turn({3, 1})));
  LOG(0, "Alice: " << alice.getState());

  alice.onRoundMsg(bob.onTurnMsg(alice.turn({0, 0})));
  LOG(0, "Bob  : " << bob.getState());
  bob.onRoundMsg(alice.onTurnMsg(bob.turn({4, 1})));
  LOG(0, "Alice: " << alice.getState());

  alice.onRoundMsg(bob.onTurnMsg(alice.turn({0, 1})));
  LOG(0, "Bob  : " << bob.getState());
  bob.onRoundMsg(alice.onTurnMsg(bob.turn({5, 1})));
  LOG(0, "Alice: " << alice.getState());

  alice.onRoundMsg(bob.onTurnMsg(alice.turn({0, 2})));
  LOG(0, "Bob  : " << bob.getState());
  bob.onRoundMsg(alice.onTurnMsg(bob.turn({6, 1})));
  LOG(0, "Alice: " << alice.getState());
}

TEST(Battleship, Fail) {
  risc0::accelStartup();
  GameState state{{
                      {{2, 3}, Vertical, 0x0000},
                      {{2, 3}, Horizontal, 0x0000},
                      {{4, 7}, Vertical, 0x0000},
                      {{7, 5}, Horizontal, 0x0000},
                      {{7, 7}, Horizontal, 0x0000},
                  },
                  0xDEADBEEF};

  Battleship player("player", state);
  ASSERT_THROW(player.init(), std::runtime_error);
}
