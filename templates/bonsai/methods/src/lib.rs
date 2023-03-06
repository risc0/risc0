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
    use std::error::Error;

    use ethabi::ethereum_types::U256;
    use ethabi::Token;
    use risc0_zkvm::{Prover, ProverOpts};

    use super::{FIBONACCI_ID, FIBONACCI_PATH};

    #[test]
    fn fibonacci() -> Result<(), Box<dyn Error>> {
        // Skip seal as it is not needed to test the guest code.
        let mut prover = Prover::new_with_opts(
            &std::fs::read(FIBONACCI_PATH)?,
            FIBONACCI_ID,
            ProverOpts::default().with_skip_seal(true),
        )?;

        prover.add_input_u8_slice(&ethabi::encode(&[Token::Uint(U256::from(10))]));

        let receipt = prover.run()?;

        assert_eq!(
            &receipt.journal,
            &ethabi::encode(&[Token::Uint(U256::from(10)), Token::Uint(U256::from(89))])
        );
        Ok(())
    }
}
