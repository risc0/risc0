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

//! The types required for the API.

mod h256;
mod json;

use uuid::Uuid;

/// ID of a Memory Image.
pub type ImageID = H256;

/// ID of a proof.
pub type ProofID = Uuid;

/// ID of a session.
pub type SessionID = Uuid;

pub use h256::H256;
pub use json::*;
