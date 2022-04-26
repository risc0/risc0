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

use std::collections::HashMap;

use battleship_core::{GameState, Position, ShipDirection, NUM_SHIPS, SHIP_SPANS};
use yew::{context::ContextHandle, prelude::*};
use yew_agent::{Dispatched, Dispatcher};

use crate::{
    bus::EventBus,
    game::{CoreHitType, GameMsg, GameSession, HitType, Side},
};

const BOARD_SIZE: usize = 10;

const SHIP_NAMES: [&str; NUM_SHIPS] =
    ["carrier", "battleship", "cruiser", "submarine", "destroyer"];

pub enum Msg {
    GameUpdate(GameSession),
    Shot(Position),
}

#[derive(Copy, Clone)]
enum Foreground {
    Blank,
    Miss,
    Hit,
    Pending,
}

#[derive(Copy, Clone)]
enum Background {
    Vacant,
    Occupied {
        ship: &'static str,
        dir: &'static str,
        idx: usize,
    },
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
        match self.fg {
            Foreground::Blank => {}
            Foreground::Hit => ret.push("hit"),
            Foreground::Miss => ret.push("miss"),
            Foreground::Pending => ret.push("pending"),
        };
        ret
    }
}

impl Cell {
    fn img(&self) -> Option<String> {
        match &self.bg {
            Background::Vacant => None,
            Background::Occupied { ship, dir, idx } => {
                Some(format!("/assets/ships/{}/{}/{}.png", ship, dir, idx).into())
            }
        }
    }
}

type Cells = [[Cell; BOARD_SIZE]; BOARD_SIZE];

struct Grid {
    pub cells: Cells,
}

impl Grid {
    pub fn render(game: &GameSession, side: Side) -> Self {
        match side {
            Side::Local => Grid::render_local(&game.local_shots, &game.state),
            Side::Remote => Grid::render_remote(&game.remote_shots),
        }
    }

    pub fn render_local(shots: &HashMap<Position, HitType>, state: &GameState) -> Self {
        let mut cells = [[Cell::default(); BOARD_SIZE]; BOARD_SIZE];
        for i in 0..NUM_SHIPS {
            let ship = &state.ships[i];
            let span = SHIP_SPANS[i];
            let x = ship.pos.x as usize;
            let y = ship.pos.y as usize;
            match ship.dir {
                ShipDirection::Horizontal => {
                    for dx in 0..span {
                        cells[y][x + dx].bg = Background::Occupied {
                            ship: SHIP_NAMES[i].into(),
                            dir: "h".into(),
                            idx: dx,
                        };
                    }
                }
                ShipDirection::Vertical => {
                    for dy in 0..span {
                        cells[y + dy][x].bg = Background::Occupied {
                            ship: SHIP_NAMES[i].into(),
                            dir: "v".into(),
                            idx: dy,
                        }
                    }
                }
            }
        }
        Grid::render_shots(&mut cells, shots)
    }

    pub fn render_remote(shots: &HashMap<Position, HitType>) -> Self {
        let mut cells = [[Cell::default(); BOARD_SIZE]; BOARD_SIZE];
        Grid::render_shots(&mut cells, shots)
    }

    fn render_shots(cells: &mut Cells, shots: &HashMap<Position, HitType>) -> Self {
        for (pos, hit) in shots {
            let fg = match hit {
                &HitType::Core(CoreHitType::Hit) => Foreground::Hit,
                &HitType::Core(CoreHitType::Miss) => Foreground::Miss,
                &HitType::Core(CoreHitType::Sunk(_)) => Foreground::Hit,
                &HitType::Pending => Foreground::Pending,
            };
            cells[pos.y as usize][pos.x as usize].fg = fg;
        }
        Grid { cells: *cells }
    }
}

#[derive(Properties, PartialEq)]
pub struct Props {
    pub side: Side,
}

pub struct Board {
    game_agent: Dispatcher<EventBus<GameMsg>>,
    _game_handle: ContextHandle<GameSession>,
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

        Board {
            game_agent: EventBus::dispatcher(),
            _game_handle,
            grid: Grid::render(&game, ctx.props().side),
        }
    }

    fn update(&mut self, ctx: &Context<Self>, msg: Self::Message) -> bool {
        match msg {
            Msg::GameUpdate(game) => {
                self.grid = Grid::render(&game, ctx.props().side);
                true
            }
            Msg::Shot(pos) => match ctx.props().side {
                Side::Local => false,
                Side::Remote => {
                    self.grid.cells[pos.y as usize][pos.x as usize].fg = Foreground::Pending;
                    self.game_agent.send(GameMsg::Shot(pos));
                    true
                }
            },
        }
    }

    fn view(&self, ctx: &Context<Self>) -> Html {
        html! {
            <table class="table table-bordered">
                <tbody>{self.render_table(ctx)}</tbody>
            </table>
        }
    }
}

impl Board {
    fn render_table(&self, ctx: &Context<Self>) -> Html {
        self.grid
            .cells
            .iter()
            .enumerate()
            .map(|(y, row)| self.render_row(ctx, y, row))
            .collect::<Html>()
    }

    fn render_row(&self, ctx: &Context<Self>, y: usize, row: &[Cell]) -> Html {
        html! {
            <tr>
                {row
                    .iter()
                    .enumerate()
                    .map(|(x, cell)| { self.render_cell(ctx, x, y, cell) })
                    .collect::<Html>()}
            </tr>
        }
    }

    fn render_cell(&self, ctx: &Context<Self>, x: usize, y: usize, cell: &Cell) -> Html {
        let onclick = ctx
            .link()
            .callback(move |_| Msg::Shot(Position::new(x as u32, y as u32)));
        html! {
            <td class={classes!("cell", cell)} {onclick}>
                {
                    match cell.img() {
                        None => html! {
                            <div></div>
                        },
                        Some(url) => {
                            let style = format!("background-image: url({});", url);
                            html! {
                                <div {style}></div>
                            }
                        }
                    }
                }
            </td>
        }
    }
}
