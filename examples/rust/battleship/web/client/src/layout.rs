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

use yew::prelude::*;

use crate::{
    board::Board,
    game::{GameSession, Side},
};

pub enum Msg {
    Game(GameSession),
}

#[derive(Clone, PartialEq, Properties)]
pub struct Props {
    pub name: String,
}

pub struct Layout {
    name: String,
}

impl Component for Layout {
    type Message = Msg;
    type Properties = ();

    fn create(ctx: &Context<Self>) -> Self {
        let (game, _) = ctx.link().context(ctx.link().callback(Msg::Game)).unwrap();
        Layout {
            name: game.name.clone(),
        }
    }

    fn view(&self, _ctx: &Context<Self>) -> Html {
        html! {
            <>
                <div class="container">
                    <p class="text-center">{"Game: "} {&self.name}</p>
                </div>
                <div class="row">
                    <div class="col-5">
                        <Board side={Side::Local} />
                    </div>
                    <div class="col">
                    </div>
                    <div class="col-5">
                        <Board side={Side::Remote} />
                    </div>
                </div>
            </>
        }
    }
}
