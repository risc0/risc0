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

// TODO: WIP

use risc0_zkp::core::fp::Fp;

use super::{io::MemoryState, GLOBAL_SIZE};

struct StepContext {
    // MemoryHandler* io;
    mem: MemoryState,
    cur_step: u32,
    num_steps: u32,
    globals: [Fp; GLOBAL_SIZE],
}
