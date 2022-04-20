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
use yew_agent::{Bridge, Bridged};

use crate::bus::EventBus;

pub struct Journal {
    _bridge: Box<dyn Bridge<EventBus<String>>>,
    lines: Vec<String>,
}

pub enum Msg {
    AddLine(String),
}

impl Component for Journal {
    type Message = Msg;
    type Properties = ();

    fn create(ctx: &Context<Self>) -> Self {
        Journal {
            _bridge: EventBus::bridge(ctx.link().callback(Msg::AddLine)),
            lines: Vec::new(),
        }
    }

    fn update(&mut self, _ctx: &Context<Self>, msg: Self::Message) -> bool {
        match msg {
            Msg::AddLine(line) => {
                self.lines.push(line);
                true
            }
        }
    }

    fn view(&self, _ctx: &Context<Self>) -> Html {
        html! {
            <div>
                <h4>{"Log"}</h4>
                <div class="list-group">
                    {
                        for self.lines.iter().map(|line| html! {
                            <div class="list-group-item list-group-item-action">
                                {line.clone()}
                            </div>
                        })
                    }
                </div>
            </div>
        }
    }
}
