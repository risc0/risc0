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

#![cfg_attr(not(test), no_std)]

use core::fmt::{Debug, Display, Formatter};

use risc0_zkvm::sha::Digest;
use serde::{Deserialize, Serialize};

#[derive(Clone, Deserialize, Eq, PartialEq, Serialize)]
pub struct Message {
    pub msg: [u8; 32],
}

impl Display for Message {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        for word in self.msg {
            core::write!(f, "{:02x?}", word)?;
        }
        Ok(())
    }
}

impl Debug for Message {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        for word in self.msg {
            core::write!(f, "{:02x?}", word)?;
        }
        Ok(())
    }
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct Passphrase {
    pub pass: [u8; 32],
}

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct SigningRequest {
    pub passphrase: Passphrase,
    pub msg: Message,
}

#[derive(Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct SignMessageCommit {
    pub identity: Digest,
    pub msg: Message,
}
