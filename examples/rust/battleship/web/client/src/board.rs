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

use std::collections::HashSet;

use battleship_core::{GameState, HitType, ShipDirection, NUM_SHIPS, SHIP_SPANS};
use yew::{context::ContextHandle, prelude::*};

use crate::game::{GameContext, Shot, Side};

pub enum Msg {
    GameUpdate(GameContext),
}

#[derive(Copy, Clone)]
enum Foreground {
    Blank,
    Miss,
    Hit,
}

#[derive(Copy, Clone)]
enum Background {
    Vacant,
    Occupied,
}

#[derive(Copy, Clone)]
struct Cell {
    fg: Foreground,
    bg: Background,
}

impl Default for Cell {
    fn default() -> Self {
        Self {
            fg: Foreground::Blank,
            bg: Background::Vacant,
        }
    }
}

impl Into<Classes> for &Cell {
    fn into(self) -> Classes {
        let mut ret = Classes::new();
        match self.bg {
            Background::Occupied => ret.push("ship"),
            Background::Vacant => {}
        }
        match self.fg {
            Foreground::Blank => {}
            Foreground::Hit => ret.push("hit"),
            Foreground::Miss => ret.push("miss"),
        };
        ret
    }
}

const BOARD_SIZE: usize = 10;

type Cells = [[Cell; BOARD_SIZE]; BOARD_SIZE];

struct Grid {
    pub cells: Cells,
}

impl Grid {
    pub fn render_local(shots: &HashSet<Shot>, state: &GameState) -> Self {
        let mut cells = [[Cell::default(); BOARD_SIZE]; BOARD_SIZE];
        for i in 0..NUM_SHIPS {
            let ship = &state.ships[i];
            let span = SHIP_SPANS[i];
            let x = ship.pos.x as usize;
            let y = ship.pos.y as usize;
            match ship.dir {
                ShipDirection::Horizontal => {
                    for dx in 0..span {
                        cells[y][x + dx].bg = Background::Occupied;
                    }
                }
                ShipDirection::Vertical => {
                    for dy in 0..span {
                        cells[y + dy][x].bg = Background::Occupied;
                    }
                }
            }
        }
        Grid::render_shots(&mut cells, shots)
    }

    pub fn render_remote(shots: &HashSet<Shot>) -> Self {
        let mut cells = [[Cell::default(); BOARD_SIZE]; BOARD_SIZE];
        Grid::render_shots(&mut cells, shots)
    }

    fn render_shots(cells: &mut Cells, shots: &HashSet<Shot>) -> Self {
        for shot in shots {
            let fg = match shot.hit {
                HitType::Hit => Foreground::Hit,
                HitType::Miss => Foreground::Miss,
                HitType::Sunk(_) => Foreground::Hit,
            };
            cells[shot.pos.y as usize][shot.pos.x as usize].fg = fg;
        }
        Grid { cells: *cells }
    }
}

#[derive(Properties, PartialEq)]
pub struct Props {
    pub side: Side,
}

pub struct Board {
    _game_handle: ContextHandle<GameContext>,
    grid: Grid,
}

impl Component for Board {
    type Message = Msg;
    type Properties = Props;

    fn create(ctx: &Context<Self>) -> Self {
        let (game, _game_handle) = ctx
            .link()
            .context(ctx.link().callback(Msg::GameUpdate))
            .unwrap();

        let grid = match ctx.props().side {
            Side::Local => Grid::render_local(&game.local_shots, &game.state),
            Side::Remote => Grid::render_remote(&game.remote_shots),
        };

        Board { _game_handle, grid }
    }

    fn update(&mut self, ctx: &Context<Self>, msg: Self::Message) -> bool {
        match msg {
            Msg::GameUpdate(game) => {
                self.grid = match ctx.props().side {
                    Side::Local => Grid::render_local(&game.local_shots, &game.state),
                    Side::Remote => Grid::render_remote(&game.remote_shots),
                };
                true
            }
        }
    }

    fn view(&self, _ctx: &Context<Self>) -> Html {
        html! {
            <div>
                <table class="table table-bordered">
                    <tbody>
                        {
                            self.grid.cells.iter().map(|row| {
                                html! {
                                    <tr>
                                    {
                                        row.iter().map(|cell| {
                                            html! {
                                                <td class={classes!("cell", cell)}>
                                                    <div></div>
                                                </td>
                                            }
                                        }).collect::<Html>()
                                    }
                                    </tr>
                                }
                            }).collect::<Html>()
                        }
                    </tbody>
                </table>
                <p class="p-2 text-center border">
                    {"This is a progress message!"}
                </p>
            </div>
        }
    }
}
