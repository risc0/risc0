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

//! Generated create containing the image ID and ELF binary of the build guest.

include!(concat!(env!("OUT_DIR"), "/methods.rs"));

#[cfg(test)]
mod tests {
    use ethabi::{ethereum_types::U256, Token};
    use risc0_zkvm::{Executor, ExecutorEnv};

    use super::FIBONACCI_ELF;

    #[test]
    fn fibonacci() {
        let env = ExecutorEnv::builder()
            .add_input(&ethabi::encode(&[Token::Uint(U256::from(10))]))
            .build();
        let mut exec = Executor::from_elf(env, FIBONACCI_ELF).unwrap();
        let session = exec.run().unwrap();
        assert_eq!(
            &session.journal,
            &ethabi::encode(&[Token::Uint(U256::from(10)), Token::Uint(U256::from(89))])
        );
    }
}
