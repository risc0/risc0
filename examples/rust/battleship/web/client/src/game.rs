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

use yew::prelude::*;

use crate::near::NearContract;
use battleship_core::{GameState, HitType, Position, Ship, ShipDirection};

// const WAIT_TURN_INTERVAL: u32 = 5_000;

#[derive(Debug, Clone, Copy, PartialEq)]
pub enum Side {
    Local,
    Remote,
}

pub enum GameAction {
    // NewGame { receipt: String },
// JoinGame { receipt: String },
// WaitTurn,
// ProcessTurn { contract_state: ContractState },
// UpdateState { receipt: String, state: GameState },
// SelectShot { pos: Position },
// Error(String)
}

// Start -> NewGame, JoinGame
// NewGame -> WaitTurn(1)
// JoinGame -> WaitTurn(2)
// WaitTurn(x) -> WaitTurn(x), ProcessTurn
// ProcessTurn -> UpdateState
// SelectShot -> WaitTurn(x)

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
}

impl Reducible for GameSession {
    type Action = GameAction;

    fn reduce(self: Rc<Self>, _action: Self::Action) -> Rc<Self> {
        // let contract = self.contract.clone();
        // let state = GameState {
        //     ships: [
        //         Ship::new(2, 3, ShipDirection::Vertical),
        //         Ship::new(3, 1, ShipDirection::Horizontal),
        //         Ship::new(4, 7, ShipDirection::Vertical),
        //         Ship::new(7, 5, ShipDirection::Horizontal),
        //         Ship::new(7, 7, ShipDirection::Horizontal),
        //     ],
        //     salt: 0xDEADBEEF,
        // };
        // let body = serde_json::to_string(&state).unwrap();
        // ctx.link().send_future(async move {
        //     let response = Request::post("/prove/init")
        //         .header("Content-Type", "application/json")
        //         .body(body)
        //         .send()
        //         .await
        //         .unwrap();
        //     let receipt = response.text().await.unwrap();
        //     log::info!("name: {}, receipt: {}", name, receipt.len());
        //     contract.new_game(&name, &receipt).await.unwrap();
        //     Msg::ListGames(contract.list_games().await.unwrap())
        // });
        GameSession {
            name: self.name.clone(),
            state: self.state.clone(),
            contract: self.contract.clone(),
            local_shots: self.local_shots.clone(),
            remote_shots: self.remote_shots.clone(),
        }
        .into()
    }
}

pub type GameContext = UseReducerHandle<GameSession>;

#[derive(Properties, PartialEq)]
pub struct GameProviderProps {
    pub name: String,
    pub contract: Rc<NearContract>,
    #[prop_or_default]
    pub children: Children,
}

#[function_component(GameProvider)]
pub fn game_provider(props: &GameProviderProps) -> Html {
    let game = use_reducer(|| {
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
        GameSession {
            state,
            name: props.name.clone(),
            contract: props.contract.clone(),
            local_shots: HashSet::new(),
            remote_shots: HashSet::new(),
        }
    });

    html! {
        <ContextProvider<GameContext> context={game}>
            {props.children.clone()}
        </ContextProvider<GameContext>>
    }
}

// let contract = self.contract.clone();
// let game_id = self.game_id.clone();
// match msg {
//     Msg::NewGame { receipt } => {
//         self.lines.push(format!("NewGame: {}", receipt.len()));
//         ctx.link().send_future(async move {
//             match contract.new_game(&game_id, &receipt).await {
//                 Ok(()) => Msg::WaitTurn,
//                 Err(err) => {
//                     console_log!(&err);
//                     Msg::Error(format!("{:?}", err))
//                 }
//             }
//         });
//         true
//     }
//     Msg::JoinGame { receipt } => {
//         self.lines.push(format!("JoinGame: {}", receipt.len()));
//         ctx.link().send_future(async move {
//             contract.join_game(&game_id, &receipt, 5, 5).await.unwrap();
//             Msg::WaitTurn
//         });
//         true
//     }
//     Msg::WaitTurn => {
//         self.lines.push(format!("WaitTurn"));
//         let side = self.side;
//         ctx.link().send_future(async move {
//             let contract_state = contract.get_state(&game_id).await.unwrap();
//             log::info!("contract_state: {:?}", contract_state);
//             if contract_state.next_turn == side {
//                 Msg::ProcessTurn { contract_state }
//             } else {
//                 TimeoutFuture::new(WAIT_TURN_INTERVAL).await;
//                 Msg::WaitTurn
//             }
//         });
//         true
//     }
//     Msg::ProcessTurn { contract_state } => {
//         self.lines.push(format!("ProcessTurn"));
//         let state = self.state.clone();
//         let side = self.side;
//         ctx.link().send_future(async move {
//             let player = if side == 1 {
//                 contract_state.p1
//             } else {
//                 contract_state.p2
//             };
//             let params = RoundParams {
//                 state: state.clone(),
//                 shot: Position::new(player.shot_x, player.shot_y),
//             };
//             let body = serde_json::to_string(&params).unwrap();
//             let response = Request::post("/prove/turn")
//                 .header("Content-Type", "application/json")
//                 .body(body)
//                 .send()
//                 .await;
//             // TODO: /prove/turn needs to return a RoundResult
//             match response {
//                 Ok(response) => {
//                     log::info!("{:?}", response);
//                     let receipt = response.text().await.unwrap();
//                     Msg::UpdateState { receipt, state }
//                 }
//                 Err(err) => {
//                     log::info!("Error: {:?}", err);
//                     let msg = format!("Error: {}", err);
//                     Msg::Error(msg)
//                 }
//             }
//         });
//         true
//     }
//     Msg::UpdateState { receipt, state } => {
//         self.lines.push(format!("UpdateState: {:?}", state));
//         self.state = state;
//         self.last_receipt = receipt;
//         // TODO: replace bot with human
//         let pos = Position::new(self.rng.gen_range(0..=9), self.rng.gen_range(0..=9));
//         ctx.link().send_message(Msg::SelectShot { pos });
//         true
//     }
//     Msg::SelectShot { pos } => {
//         self.lines.push(format!("SelectShot: {:?}", pos));
//         let last_receipt = self.last_receipt.clone();
//         ctx.link().send_future(async move {
//             contract
//                 .turn(&game_id, &last_receipt, pos.x, pos.y)
//                 .await
//                 .unwrap();
//             Msg::WaitTurn
//         });
//         true
//     }
//     Msg::Error(msg) => {
//         self.lines.push(format!("Error: {}", msg));
//         true
//     }
// }
