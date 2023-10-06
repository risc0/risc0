// Copyright 2023 RISC Zero, Inc.
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

#[cfg(any(feature = "client", feature = "prove"))]
pub(crate) mod api;
#[cfg(feature = "client")]
pub(crate) mod client;
pub(crate) mod control_id;
pub(crate) mod receipt;
pub(crate) mod recursion;
#[cfg(feature = "prove")]
pub(crate) mod server;

#[cfg(any(feature = "client", feature = "prove"))]
mod protos {
    pub(crate) mod api {
        #![allow(non_snake_case)]
        include!(concat!(env!("OUT_DIR"), "/protos.api.rs"));
    }

    pub(crate) mod base {
        #![allow(non_snake_case)]
        include!(concat!(env!("OUT_DIR"), "/protos.base.rs"));
    }

    pub(crate) mod core {
        #![allow(non_snake_case)]
        include!(concat!(env!("OUT_DIR"), "/protos.core.rs"));
    }
}

const CIRCUIT: risc0_circuit_rv32im::CircuitImpl = risc0_circuit_rv32im::CircuitImpl::new();
