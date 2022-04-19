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

use std::{collections::HashSet, rc::Rc};

use gloo::timers::future::TimeoutFuture;
use reqwasm::http::Request;
use yew::prelude::*;
use yew_agent::{Agent, AgentLink, Bridge, Bridged, Dispatched, Dispatcher, HandlerId};

use crate::{
    bus::EventBus,
    contract::{Contract, ContractState},
    near::NearContract,
};
use battleship_core::{GameState, HitType, Position, RoundParams, Ship, ShipDirection};

const WAIT_TURN_INTERVAL: u32 = 5_000;

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Side {
    Local,
    Remote,
}

#[derive(Clone, PartialEq)]
pub enum GameMsg {
    Init,
    Shot(Position),
    WaitTurn,
    ProcessTurn(ContractState),
    UpdateState(String, GameState),
}

#[derive(PartialEq, Clone, Eq, Hash)]
pub struct Shot {
    pub pos: Position,
    pub hit: HitType,
}

#[derive(PartialEq, Clone)]
pub struct GameSession {
    pub name: String,
    pub state: GameState,
    pub contract: Rc<NearContract>,
    pub local_shots: HashSet<Shot>,
    pub remote_shots: HashSet<Shot>,
    pub last_receipt: String,
    pub is_first: bool,
}

pub struct GameAgent {
    link: AgentLink<GameAgent>,
    subscribers: HashSet<HandlerId>,
}

impl Agent for GameAgent {
    type Reach = yew_agent::Context<Self>;
    type Message = ();
    type Input = GameMsg;
    type Output = GameMsg;

    fn create(link: AgentLink<Self>) -> Self {
        GameAgent {
            link,
            subscribers: HashSet::new(),
        }
    }

    fn update(&mut self, _msg: Self::Message) {}

    fn handle_input(&mut self, msg: Self::Input, _id: HandlerId) {
        for sub in self.subscribers.iter() {
            self.link.respond(*sub, msg.clone());
        }
    }

    fn connected(&mut self, id: HandlerId) {
        self.subscribers.insert(id);
    }

    fn disconnected(&mut self, id: HandlerId) {
        self.subscribers.remove(&id);
    }
}

#[derive(Properties, PartialEq)]
pub struct Props {
    pub name: String,
    pub contract: Rc<NearContract>,
    pub until: usize,
    #[prop_or_default]
    pub children: Children,
}

pub struct GameProvider {
    _bridge: Box<dyn Bridge<GameAgent>>,
    event_bus: Dispatcher<EventBus>,
    game: GameSession,
}

impl Component for GameProvider {
    type Message = GameMsg;
    type Properties = Props;

    fn create(ctx: &Context<Self>) -> Self {
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
            contract: ctx.props().contract.clone(),
            local_shots: HashSet::new(),
            remote_shots: HashSet::new(),
            last_receipt: String::new(),
            is_first: ctx.props().until == 2,
        };
        if ctx.props().until == 1 {
            ctx.link().send_message(GameMsg::Init);
        }
        GameProvider {
            _bridge: GameAgent::bridge(ctx.link().callback(|msg| msg)),
            event_bus: EventBus::dispatcher(),
            game,
        }
    }

    fn update(&mut self, ctx: &Context<Self>, msg: Self::Message) -> bool {
        match msg {
            GameMsg::Init => {
                let game = self.game.clone();
                let body = serde_json::to_string(&game.state).unwrap();
                ctx.link().send_future(async move {
                    let response = Request::post("/prove/init")
                        .header("Content-Type", "application/json")
                        .body(body)
                        .send()
                        .await
                        .unwrap();
                    let receipt = response.text().await.unwrap();
                    game.contract.new_game(&game.name, &receipt).await.unwrap();
                    GameMsg::WaitTurn
                });
                true
            }
            GameMsg::Shot(pos) => {
                self.event_bus.send("GameMsg::Shot".into());
                let game = self.game.clone();
                let is_first = self.game.is_first;
                self.game.is_first = false;
                ctx.link().send_future(async move {
                    if is_first {
                        let body = serde_json::to_string(&game.state).unwrap();
                        let response = Request::post("/prove/init")
                            .header("Content-Type", "application/json")
                            .body(body)
                            .send()
                            .await
                            .unwrap();
                        let receipt = response.text().await.unwrap();
                        game.contract
                            .join_game(&game.name, &receipt, pos.x, pos.y)
                            .await
                            .unwrap();
                    } else {
                        game.contract
                            .turn(&game.name, &game.last_receipt, pos.x, pos.y)
                            .await
                            .unwrap();
                    }
                    GameMsg::WaitTurn
                });
                true
            }
            GameMsg::WaitTurn => {
                self.event_bus.send("GameMsg::WaitTurn".into());
                let until = ctx.props().until as u32;
                let game = self.game.clone();
                ctx.link().send_future(async move {
                    let contract_state = game.contract.get_state(&game.name).await.unwrap();
                    log::info!("contract_state: {:?}", contract_state);
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
                self.event_bus.send("GameMsg::ProcessTurn".into());
                let state = self.game.state.clone();
                let until = ctx.props().until;
                ctx.link().send_future(async move {
                    let player = if until == 1 {
                        contract_state.p1
                    } else {
                        contract_state.p2
                    };
                    let params = RoundParams {
                        state: state.clone(),
                        shot: Position::new(player.shot_x, player.shot_y),
                    };
                    let body = serde_json::to_string(&params).unwrap();
                    let response = Request::post("/prove/turn")
                        .header("Content-Type", "application/json")
                        .body(body)
                        .send()
                        .await
                        .unwrap();
                    // TODO: /prove/turn needs to return a RoundResult
                    let receipt = response.text().await.unwrap();
                    GameMsg::UpdateState(receipt, state)
                });
                true
            }
            GameMsg::UpdateState(receipt, state) => {
                self.event_bus.send("GameMsg::UpdateState".into());
                self.game.state = state;
                self.game.last_receipt = receipt;
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
