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
use battleship_core::{GameState, Position, RoundParams, RoundResult, Ship, ShipDirection};

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

#[derive(PartialEq, Clone)]
pub struct GameSession {
    pub name: String,
    pub state: GameState,
    pub contract: Rc<NearContract>,
    pub local_shots: HashMap<Position, HitType>,
    pub remote_shots: HashMap<Position, HitType>,
    pub last_receipt: String,
    pub last_shot: Option<Position>,
    pub is_first: bool,
    pub status: String,
}

#[derive(Properties, PartialEq)]
pub struct Props {
    pub name: String,
    pub until: usize,
    #[prop_or_default]
    pub children: Children,
}

pub struct GameProvider {
    _bridge: Box<dyn Bridge<EventBus<GameMsg>>>,
    journal: Dispatcher<EventBus<String>>,
    game: GameSession,
}

impl Component for GameProvider {
    type Message = GameMsg;
    type Properties = Props;

    fn create(ctx: &Context<Self>) -> Self {
        let (wallet, _) = ctx
            .link()
            .context::<WalletContext>(Callback::noop())
            .unwrap();
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
        let game = GameSession {
            state,
            name: ctx.props().name.clone(),
            contract: wallet.contract.clone(),
            local_shots: HashMap::new(),
            remote_shots: HashMap::new(),
            last_receipt: String::new(),
            last_shot: None,
            is_first: ctx.props().until == 2,
            status: format!("Ready!"),
        };
        if ctx.props().until == 1 {
            ctx.link().send_message(GameMsg::Init);
        }
        GameProvider {
            _bridge: EventBus::bridge(ctx.link().callback(|msg| msg)),
            journal: EventBus::dispatcher(),
            game,
        }
    }

    fn update(&mut self, ctx: &Context<Self>, msg: Self::Message) -> bool {
        match msg {
            GameMsg::Init => {
                self.game.status = format!("Init");
                let game = self.game.clone();
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
                    match game.contract.new_game(&game.name, &receipt).await {
                        Ok(()) => GameMsg::WaitTurn,
                        Err(err) => GameMsg::Error(format!("new_game: {:?}", err)),
                    }
                });
                true
            }
            GameMsg::Shot(pos) => {
                self.game.status = format!("Shot: {}", pos);
                self.journal.send("GameMsg::Shot".into());
                self.game.last_shot = Some(pos.clone());
                self.game.remote_shots.insert(pos.clone(), HitType::Pending);
                let game = self.game.clone();
                let is_first = self.game.is_first;
                self.game.is_first = false;
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
                        match game
                            .contract
                            .join_game(&game.name, &receipt, pos.x, pos.y)
                            .await
                        {
                            Ok(()) => GameMsg::WaitTurn,
                            Err(err) => {
                                return GameMsg::Error(format!("join_game: {:?}", err));
                            }
                        }
                    } else {
                        match game
                            .contract
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
            }
            GameMsg::WaitTurn => {
                self.game.status = format!("Waiting for other player.");
                self.journal.send("GameMsg::WaitTurn".into());
                let until = ctx.props().until as u32;
                let game = self.game.clone();
                ctx.link().send_future(async move {
                    let contract_state = match game.contract.get_state(&game.name).await {
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
                            1 => HitType::Core(CoreHitType::Hit),
                            2 => {
                                HitType::Core(CoreHitType::Sunk(contract_state.sunk_what.unwrap()))
                            }
                            _ => unreachable!(),
                        },
                    );
                }
                let until = ctx.props().until;
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
