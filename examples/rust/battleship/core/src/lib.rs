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

#![cfg_attr(not(test), no_std)]

use core::fmt::Display;

use serde::{Deserialize, Serialize};

use risc0_zkvm_core::Digest;

pub const NUM_SHIPS: usize = 5;
pub const BOARD_SIZE: usize = 10;

pub const SHIP_SPANS: [usize; NUM_SHIPS] = [
    5, // carrier
    4, // battleship
    3, // cruiser
    3, // submarine
    2, // destroyer
];

pub const SUNK_MASKS: [u8; NUM_SHIPS] = [0x1f, 0x0f, 0x07, 0x07, 0x03];

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize, Hash)]
pub struct Position {
    pub x: u32,
    pub y: u32,
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub enum ShipDirection {
    Horizontal,
    Vertical,
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct Ship {
    pub pos: Position,
    pub dir: ShipDirection,
    pub hit_mask: u8,
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct GameState {
    pub ships: [Ship; NUM_SHIPS],
    pub salt: u32,
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct RoundParams {
    pub state: GameState,
    pub shot: Position,
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize, Hash)]
pub enum HitType {
    Miss,
    Hit,
    Sunk(u8),
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct RoundResult {
    pub state: GameState,
    pub hit: HitType,
}

#[derive(Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct RoundCommit {
    pub old_state: Digest,
    pub new_state: Digest,
    pub shot: Position,
    pub hit: HitType,
}

impl GameState {
    pub fn check(&self) -> bool {
        let mut board: [[bool; BOARD_SIZE]; BOARD_SIZE] = [[false; BOARD_SIZE]; BOARD_SIZE];
        for i in 0..NUM_SHIPS {
            let ship = &self.ships[i];
            let span = SHIP_SPANS[i];
            if !ship.check(span) {
                return false;
            }
            let x = ship.pos.x as usize;
            let y = ship.pos.y as usize;
            match ship.dir {
                ShipDirection::Horizontal => {
                    for dx in 0..span {
                        if board[y][x + dx] {
                            return false;
                        }
                        board[y][x + dx] = true;
                    }
                }
                ShipDirection::Vertical => {
                    for dy in 0..span {
                        if board[y + dy][x] {
                            return false;
                        }
                        board[y + dy][x] = true;
                    }
                }
            }
        }
        true
    }
}

impl RoundParams {
    pub fn new(state: GameState, x: u32, y: u32) -> Self {
        RoundParams {
            state,
            shot: Position::new(x, y),
        }
    }

    pub fn process(&self) -> RoundResult {
        let mut state = self.state.clone();
        let shot = &self.shot;
        assert!(shot.check());
        enum HitShift {
            Hit(u32),
            Miss,
        }
        for i in 0..NUM_SHIPS {
            let ship = &mut state.ships[i];
            let span = SHIP_SPANS[i] as u32;
            let x = ship.pos.x;
            let y = ship.pos.y;
            let hit_shift = match ship.dir {
                ShipDirection::Horizontal => {
                    if shot.y == y && shot.x >= x && shot.x <= x + span {
                        HitShift::Hit(shot.x - x)
                    } else {
                        HitShift::Miss
                    }
                }
                ShipDirection::Vertical => {
                    if shot.x == x && shot.y >= y && shot.y <= y + span {
                        HitShift::Hit(shot.y - y)
                    } else {
                        HitShift::Miss
                    }
                }
            };
            if let HitShift::Hit(shift) = hit_shift {
                ship.hit_mask |= 1 << shift;
                let hit = if ship.hit_mask == SUNK_MASKS[i] {
                    HitType::Sunk(i as u8)
                } else {
                    HitType::Hit
                };
                return RoundResult::new(state, hit);
            }
        }
        RoundResult {
            state,
            hit: HitType::Miss,
        }
    }
}

impl RoundResult {
    pub fn new(state: GameState, hit: HitType) -> Self {
        RoundResult { state, hit }
    }
}

impl Position {
    pub fn new(x: u32, y: u32) -> Self {
        Position { x, y }
    }

    pub fn check(&self) -> bool {
        self.x < BOARD_SIZE as u32 && self.y < BOARD_SIZE as u32
    }
}

impl Display for Position {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        write!(f, "({}, {})", self.x, self.y)
    }
}

impl Ship {
    pub fn new(x: u32, y: u32, dir: ShipDirection) -> Self {
        Ship {
            pos: Position::new(x, y),
            dir,
            hit_mask: 0,
        }
    }

    pub fn with_hit_mask(x: u32, y: u32, dir: ShipDirection, hit_mask: u8) -> Self {
        Ship {
            pos: Position::new(x, y),
            dir,
            hit_mask,
        }
    }

    pub fn check(&self, span: usize) -> bool {
        let limit = BOARD_SIZE - span;
        self.hit_mask == 0
            && self.pos.check()
            && match self.dir {
                ShipDirection::Horizontal => self.pos.x as usize <= limit,
                ShipDirection::Vertical => self.pos.y as usize <= limit,
            }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic() {
        let state = GameState {
            ships: [
                Ship::new(2, 3, ShipDirection::Vertical),
                Ship::new(3, 1, ShipDirection::Horizontal),
                Ship::new(4, 7, ShipDirection::Vertical),
                Ship::new(7, 5, ShipDirection::Horizontal),
                Ship::new(7, 7, ShipDirection::Horizontal),
            ],
            salt: 0xDEADBEEF,
        };

        assert!(state.check());
    }

    #[test]
    fn overlap() {
        let state = GameState {
            ships: [
                Ship::new(2, 3, ShipDirection::Vertical),
                Ship::new(3, 1, ShipDirection::Horizontal),
                Ship::new(2, 3, ShipDirection::Vertical),
                Ship::new(7, 5, ShipDirection::Horizontal),
                Ship::new(7, 7, ShipDirection::Horizontal),
            ],
            salt: 0xDEADBEEF,
        };

        assert!(!state.check());
    }

    #[test]
    fn rounds() {
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

        let salt = 0xDEADBEEF;
        let state1 = GameState {
            ships: [
                Ship::new(2, 3, ShipDirection::Vertical),
                Ship::new(3, 1, ShipDirection::Horizontal),
                Ship::new(4, 7, ShipDirection::Vertical),
                Ship::new(7, 5, ShipDirection::Horizontal),
                Ship::new(7, 7, ShipDirection::Horizontal),
            ],
            salt,
        };

        let params1 = RoundParams::new(state1.clone(), 1, 1);
        let result1 = RoundResult::new(state1.clone(), HitType::Miss);
        assert_eq!(params1.process(), result1);

        let params2 = RoundParams::new(state1.clone(), 4, 1);
        let result2 = RoundResult::new(
            GameState {
                ships: [
                    Ship::new(2, 3, ShipDirection::Vertical),
                    Ship::with_hit_mask(3, 1, ShipDirection::Horizontal, 0x02),
                    Ship::new(4, 7, ShipDirection::Vertical),
                    Ship::new(7, 5, ShipDirection::Horizontal),
                    Ship::new(7, 7, ShipDirection::Horizontal),
                ],
                salt,
            },
            HitType::Hit,
        );
        assert_eq!(params2.process(), result2);

        // Duplicate hit results in no state change
        let params3 = RoundParams::new(state1, 4, 1);
        let result3 = result2.clone();
        assert_eq!(params3.process(), result3);

        let params4 = RoundParams::new(result3.state, 3, 1);
        let result4 = RoundResult::new(
            GameState {
                ships: [
                    Ship::new(2, 3, ShipDirection::Vertical),
                    Ship::with_hit_mask(3, 1, ShipDirection::Horizontal, 0x03),
                    Ship::new(4, 7, ShipDirection::Vertical),
                    Ship::new(7, 5, ShipDirection::Horizontal),
                    Ship::new(7, 7, ShipDirection::Horizontal),
                ],
                salt,
            },
            HitType::Hit,
        );
        assert_eq!(params4.process(), result4);

        let params5 = RoundParams::new(result4.state, 6, 1);
        let result5 = RoundResult::new(
            GameState {
                ships: [
                    Ship::new(2, 3, ShipDirection::Vertical),
                    Ship::with_hit_mask(3, 1, ShipDirection::Horizontal, 0x0b),
                    Ship::new(4, 7, ShipDirection::Vertical),
                    Ship::new(7, 5, ShipDirection::Horizontal),
                    Ship::new(7, 7, ShipDirection::Horizontal),
                ],
                salt,
            },
            HitType::Hit,
        );
        assert_eq!(params5.process(), result5);

        let params6 = RoundParams::new(result5.state, 5, 1);
        let result6 = RoundResult::new(
            GameState {
                ships: [
                    Ship::new(2, 3, ShipDirection::Vertical),
                    Ship::with_hit_mask(3, 1, ShipDirection::Horizontal, 0x0f),
                    Ship::new(4, 7, ShipDirection::Vertical),
                    Ship::new(7, 5, ShipDirection::Horizontal),
                    Ship::new(7, 7, ShipDirection::Horizontal),
                ],
                salt,
            },
            HitType::Sunk(1),
        );
        assert_eq!(params6.process(), result6);
    }
}
