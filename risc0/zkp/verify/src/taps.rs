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

#[derive(Clone, Copy)]
pub enum RegisterGroup {
    Accum = 0,
    Code = 1,
    Data = 2,
}

pub struct Register {
    pub group: RegisterGroup,
    pub offset: usize,
    pub back: Vec<usize>,
    pub combo_id: usize,
}

pub struct Combo {
    pub back: Vec<usize>,
}

pub struct Taps {
    pub registers: Vec<Register>,
    pub combos: Vec<Combo>,
}
