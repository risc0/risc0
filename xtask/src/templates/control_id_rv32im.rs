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

const CONTROL_ID_ENTRIES: usize = risc0_zkp::MAX_CYCLES_PO2 - risc0_zkp::MIN_CYCLES_PO2;

pub type RawControlId = [&'static str; CONTROL_ID_ENTRIES];

/// Control ID for SHA-256
pub const SHA256_CONTROL_ID: RawControlId = [
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
];

/// Control ID for Poseidon
pub const POSEIDON_CONTROL_ID: RawControlId = [
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
];

/// Control ID for Blake2b
pub const BLAKE2B_CONTROL_ID: RawControlId = [
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
    "{}", //
];
