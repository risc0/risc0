// Copyright 2024 RISC Zero, Inc.
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

use jwt_core::CustomClaims;
use jwt_methods::VALIDATOR_ID;
use jwt_validator::prove_token_validation;

fn main() {
    tracing_subscriber::fmt()
        .with_env_filter(tracing_subscriber::EnvFilter::from_default_env())
        .init();

    let claims = CustomClaims {
        subject: "Hello, world!".to_string(),
    };

    let (receipt, _) = prove_token_validation(&claims);

    receipt
        .verify(VALIDATOR_ID)
        .expect("Proof of validation should successfully verify");
}
