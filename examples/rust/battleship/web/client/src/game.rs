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

extern crate wasm_bindgen;
use gloo::storage::{LocalStorage, Storage};
use wasm_bindgen::prelude::*;

#[wasm_bindgen]
extern "C" {
    fn alert(s: &str);
}

use serde_with::serde_as;

use rand::{thread_rng, Rng};
use std::{collections::HashMap, rc::Rc};

use gloo::timers::future::TimeoutFuture;
use reqwasm::http::Request;
use serde::{Deserialize, Serialize};
use yew::prelude::*;
use yew_agent::{Bridge, Bridged, Dispatched, Dispatcher};

use crate::{
    bus::EventBus,
    contract::{Contract, ContractState},
    near::NearContract,
    wallet::WalletContext,
};
use battleship_core::{
    GameState, Position, RoundParams, RoundResult, Ship, ShipDirection, BOARD_SIZE, SHIP_SPANS,
};

pub type CoreHitType = battleship_core::HitType;

const WAIT_TURN_INTERVAL: u32 = 5_000;

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Side {
    Local,
    Remote,
}

#[derive(Deserialize, Serialize)]
pub struct TurnResult {
    state: RoundResult,
    receipt: String,
}

#[derive(Clone, PartialEq)]
pub enum GameMsg {
    Init,
    Shot(Position),
    ClearShot(Position),
    WaitTurn,
    ProcessTurn(ContractState),
    UpdateState(String, RoundResult, Position),
    Error(String),
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize, Hash)]
pub enum HitType {
    Core(CoreHitType),
    Pending,
}

#[serde_as]
#[derive(PartialEq, Clone, Serialize, Deserialize)]
pub struct GameSession {
    pub name: String,
    pub state: GameState,
    #[serde_as(as = "Vec<(_, _)>")]
    pub local_shots: HashMap<Position, HitType>,
    #[serde_as(as = "Vec<(_, _)>")]
    pub remote_shots: HashMap<Position, HitType>,
    pub last_receipt: String,
    pub last_shot: Option<Position>,
    pub is_first: bool,
    pub status: String,
    pub og_until: usize,
}

type Taken = [[bool; BOARD_SIZE]; BOARD_SIZE];

fn check_bounds(x: usize, y: usize, span: usize, dir: usize) -> bool {
    if dir == 0 {
        x + span <= BOARD_SIZE - 1
    } else {
        y + span <= BOARD_SIZE - 1
    }
}

fn check_taken(x: usize, y: usize, span: usize, dir: usize, taken: Taken) -> bool {
    let mut is_taken = false;
    for i in 0..span {
        let mut try_again = false;
        if dir == 0 {
            if taken[x + i][y] {
                try_again = true
            }
        } else {
            if taken[x][y + i] {
                try_again = true
            }
        }
        if try_again {
            is_taken = true;
            break;
        }
    }
    is_taken
}

fn create_random_ships() -> [Ship; 5] {
    // randomly place 5 ships on the board
    let mut rng = thread_rng();
    let mut ships: [Ship; 5] = array_init::array_init(|_| Ship::default());
    let mut taken = [[false; BOARD_SIZE]; BOARD_SIZE];
    let mut i = 0;

    for ship in ships.iter_mut() {
        loop {
            // pick a random starting point on the board
            let x: usize = rng.gen_range(0..BOARD_SIZE - 1);
            let y: usize = rng.gen_range(0..BOARD_SIZE - 1);
            if taken[x][y] {
                continue;
            }
            // pick between 0 and 1 for randomized ship placement
            let rdir: bool = rng.gen();
            let ship_dir_int;
            if rdir {
                ship_dir_int = 0
            } else {
                ship_dir_int = 1
            }
            if ship_dir_int == 0 {
                ship.dir = ShipDirection::Horizontal;
            } else {
                ship.dir = ShipDirection::Vertical;
            }

            // does it fit on the board
            let span = SHIP_SPANS[i];
            if !check_bounds(x, y, span, ship_dir_int) {
                continue;
            }

            // does it cross any other ship
            if check_taken(x, y, span, ship_dir_int, taken) {
                continue;
            } else {
                // mark the ship as taken
                for i in 0..span {
                    if ship_dir_int == 0 {
                        taken[x + i][y] = true;
                    } else {
                        taken[x][y + i] = true;
                    }
                }
            }

            ship.pos = Position {
                x: x as u32,
                y: y as u32,
            };
            i += 1;
            break;
        }
    }
    ships
}

#[derive(Properties, PartialEq)]
pub struct Props {
    pub name: String,
    pub until: usize,
    #[prop_or_else(create_random_ships)]
    pub ships: [Ship; 5],
    #[prop_or_default]
    pub children: Children,
}

pub struct GameProvider {
    _bridge: Box<dyn Bridge<EventBus<GameMsg>>>,
    journal: Dispatcher<EventBus<String>>,
    game: GameSession,
    contract: Rc<NearContract>,
}

impl Component for GameProvider {
    type Message = GameMsg;
    type Properties = Props;

    fn create(ctx: &Context<Self>) -> Self {
        log::info!("CREATE");
        let (wallet, _) = ctx
            .link()
            .context::<WalletContext>(Callback::noop())
            .unwrap();
        let state = GameState {
            ships: ctx.props().ships.clone(),
            salt: 0xDEADBEEF,
        };
        let res: Result<GameSession, _> = LocalStorage::get(ctx.props().name.clone());
        let game_exists = match res {
            Ok(_) => true,
            Err(_) => false,
        };
        log::info!("game_exists? {}", game_exists);
        log::info!("until? {}", ctx.props().until);
        let game;
        if game_exists {
            game = LocalStorage::get(ctx.props().name.clone()).unwrap();
            ctx.link().send_message(GameMsg::WaitTurn);
        } else {
            log::info!("No local storage exists for this game until? {}", ctx.props().until);
            game = GameSession {
                name: ctx.props().name.clone(),
                state,
                local_shots: HashMap::new(),
                remote_shots: HashMap::new(),
                last_receipt: String::new(),
                last_shot: None,
                is_first: ctx.props().until == 2,
                status: format!("Ready!"),
                og_until: ctx.props().until,
            };

            if ctx.props().until == 1 {
                ctx.link().send_message(GameMsg::Init);
            }
        }
        // let game = match res {
        //     Ok(game) => game,
        //     Err(_) => GameSession {
        //         name: ctx.props().name.clone(),
        //         state,
        //         local_shots: HashMap::new(),
        //         remote_shots: HashMap::new(),
        //         last_receipt: String::new(),
        //         last_shot: None,
        //         is_first: true,
        //         status: String::new(),
        //     },
        // };

        // let game = LocalStorage::get(ctx.props().name.clone()).unwrap_or(GameSession {
        //     state,
        //     name: ctx.props().name.clone(),
        //     local_shots: HashMap::new(),
        //     remote_shots: HashMap::new(),
        //     last_receipt: String::new(),
        //     last_shot: None,
        //     is_first: ctx.props().until == 2,
        //     status: format!("Ready!"),
        // });

        log::info!("Save the game to local storage {:?}", game.name);
        LocalStorage::set(game.name.clone(), game.clone()).unwrap();
        let contract = wallet.contract.clone();

        GameProvider {
            _bridge: EventBus::bridge(ctx.link().callback(|msg| msg)),
            journal: EventBus::dispatcher(),
            game: game,
            contract: contract,
        }
    }

    fn update(&mut self, ctx: &Context<Self>, msg: Self::Message) -> bool {
        match msg {
            GameMsg::Init => {
                self.game.status = format!("Init");
                let game = self.game.clone();
                let contract = self.contract.clone();
                let body = serde_json::to_string(&game.state).unwrap();
                ctx.link().send_future(async move {
                    let response = match Request::post("/prove/init")
                        .header("Content-Type", "application/json")
                        .body(body)
                        .send()
                        .await
                    {
                        Ok(response) => response,
                        Err(err) => {
                            return GameMsg::Error(format!("POST /prove/init failed: {}", err));
                        }
                    };
                    let receipt = match response.text().await {
                        Ok(receipt) => receipt,
                        Err(err) => {
                            return GameMsg::Error(format!("receipt: {}", err));
                        }
                    };
                    match contract.new_game(&game.name, &receipt).await {
                        Ok(()) => GameMsg::WaitTurn,
                        Err(err) => GameMsg::Error(format!("new_game: {:?}", err)),
                    }
                });
                true
            }
            GameMsg::Shot(pos) => {
                self.game.remote_shots.insert(pos.clone(), HitType::Pending);
                if self.game.status == "Ready!" {
                    log::info!(
                        "Only happens if game.status is Ready GameMsg::Shot {:?}",
                        pos
                    );
                    self.game.status = format!("Shot: {}", pos);
                    self.journal.send("GameMsg::Shot".into());
                    self.game.last_shot = Some(pos.clone());
                    let game = self.game.clone();
                    let is_first = self.game.is_first;
                    log::info!("GameMsg::Shot is_first {}", is_first);
                    self.game.is_first = false;
                    log::info!("GameMsg::Shot self.game.is_first will be set to false");
                    let contract = self.contract.clone();
                    ctx.link().send_future(async move {
                        if is_first {
                            let body = serde_json::to_string(&game.state).unwrap();
                            let response = match Request::post("/prove/init")
                                .header("Content-Type", "application/json")
                                .body(body)
                                .send()
                                .await
                            {
                                Ok(response) => response,
                                Err(err) => {
                                    return GameMsg::Error(format!("POST /prove/init: {}", err));
                                }
                            };
                            let receipt = match response.text().await {
                                Ok(receipt) => receipt,
                                Err(err) => {
                                    return GameMsg::Error(format!("receipt: {}", err));
                                }
                            };
                            match contract.join_game(&game.name, &receipt, pos.x, pos.y).await {
                                Ok(()) => GameMsg::WaitTurn,
                                Err(err) => {
                                    return GameMsg::Error(format!("join_game: {:?}", err));
                                }
                            }
                        } else {
                            match contract
                                .turn(&game.name, &game.last_receipt, pos.x, pos.y)
                                .await
                            {
                                Ok(()) => GameMsg::WaitTurn,
                                Err(err) => {
                                    return GameMsg::Error(format!("turn: {:?}", err));
                                }
                            }
                        }
                    });
                    true
                } else {
                    alert("Game is not ready!");
                    ctx.link().send_message(GameMsg::ClearShot(pos));
                    false
                }
            }
            GameMsg::ClearShot(pos) => {
                log::info!("GameMsg::ClearShot {:?}", pos);
                self.game.remote_shots.remove(&pos);
                true
            }
            GameMsg::WaitTurn => {
                self.game.status = format!("Waiting for other player.");
                self.journal.send("GameMsg::WaitTurn".into());
                let until = self.game.og_until as u32; //ctx.props().until as u32;
                let game = self.game.clone();
                let contract = self.contract.clone();
                LocalStorage::set(self.game.name.clone(), self.game.clone()).unwrap();
                ctx.link().send_future(async move {
                    let contract_state = match contract.get_state(&game.name).await {
                        Ok(state) => state,
                        Err(err) => {
                            return GameMsg::Error(format!("get_state: {:?}", err));
                        }
                    };
                    if contract_state.next_turn == until {
                        GameMsg::ProcessTurn(contract_state)
                    } else {
                        TimeoutFuture::new(WAIT_TURN_INTERVAL).await;
                        GameMsg::WaitTurn
                    }
                });
                true
            }
            GameMsg::ProcessTurn(contract_state) => {
                self.game.status = format!("ProcessTurn");
                self.journal.send("GameMsg::ProcessTurn".into());
                let state = self.game.state.clone();
                if let Some(last_shot) = self.game.last_shot.clone() {
                    self.game.remote_shots.insert(
                        last_shot,
                        match contract_state.last_hit.unwrap() {
                            0 => HitType::Core(CoreHitType::Miss),
                            1 => {
                                alert("You scored a hit!");
                                HitType::Core(CoreHitType::Hit)
                            }
                            2 => {
                                alert("You sunk an opponent's ship!");
                                HitType::Core(CoreHitType::Sunk(contract_state.sunk_what.unwrap()))
                            }
                            _ => unreachable!(),
                        },
                    );
                }
                let until = self.game.og_until; //ctx.props().until;
                ctx.link().send_future(async move {
                    let player = if until == 2 {
                        contract_state.p1
                    } else {
                        contract_state.p2
                    };
                    let shot = Position::new(player.shot_x, player.shot_y);
                    let params = RoundParams {
                        state: state.clone(),
                        shot: shot.clone(),
                    };
                    let body = serde_json::to_string(&params).unwrap();
                    let response = match Request::post("/prove/turn")
                        .header("Content-Type", "application/json")
                        .body(body)
                        .send()
                        .await
                    {
                        Ok(response) => response,
                        Err(err) => {
                            return GameMsg::Error(format!("POST /prove/turn: {}", err));
                        }
                    };
                    let result = match response.text().await {
                        Ok(result) => result,
                        Err(err) => {
                            return GameMsg::Error(format!("result: {}", err));
                        }
                    };
                    match serde_json::from_str::<TurnResult>(&result) {
                        Ok(result) => GameMsg::UpdateState(result.receipt, result.state, shot),
                        Err(err) => GameMsg::Error(format!("json fail: {}", err)),
                    }
                });
                true
            }
            GameMsg::UpdateState(receipt, state, shot) => {
                self.game.status = format!("Ready!");
                self.journal.send("GameMsg::UpdateState".into());
                self.game.state = state.state;
                self.game.last_receipt = receipt;
                self.game.local_shots.insert(shot, HitType::Core(state.hit));
                log::info!("GameMsg::UpdateState {:?}", self.game.name.clone());
                let res = LocalStorage::set(self.game.name.clone(), self.game.clone());
                if let Err(err) = res {
                    log::error!("There was an error setting local storage {:?}", err);
                }
                true
            }
            GameMsg::Error(msg) => {
                self.game.status = msg;
                true
            }
        }
    }

    fn view(&self, ctx: &Context<Self>) -> Html {
        html! {
            <ContextProvider<GameSession> context={self.game.clone()}>
                {ctx.props().children.clone()}
            </ContextProvider<GameSession>>
        }
    }
}
