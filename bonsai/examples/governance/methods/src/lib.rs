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

//! Generated crate containing the image ID and ELF binary of the build guest.
include!(concat!(env!("OUT_DIR"), "/methods.rs"));

#[cfg(test)]
mod test {
    use hex_literal::hex;
    use risc0_zkvm::{Executor, ExecutorEnv};

    use crate::FINALIZE_VOTES_ELF;

    const TEST_INPUT: &'static [u8] = &hex!(
    "123ef2afce66c417062d3d2c69ca0a612c95de6ae9331e5e9640a361b787c1c8"
    "000001004f81992fce2e1846dd528ec0102e6ee1f61ed3e20000000000000000000000000000000000000000000000000000"
    "0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000"
    "0001001bf6aa43f8d7be0bb024a5c78f3306de98255be17d70a6c6a55af54bb15a21301d41b6777aec47f9cf191533f0c351"
    "eca97fde3756db8dd50882a26dcfa5ea0465615a2bd0468e6a715cf9378e9b28ba4314d567dd731e083c4b3d6f44e8f03bfb"
    );

    const TEST_OUTPUT: &'static [u8] = &hex!(
    "123ef2afce66c417062d3d2c69ca0a612c95de6ae9331e5e9640a361b787c1c8"
    "2b45288717bd1179cdda9be4ae9cb416e4e42028537046902c3a173596b4d623"
    "000000014f81992fce2e1846dd528ec0102e6ee1f61ed3e2"
    "00000000fbf974a059aa2e376f258d6c3238ad6c2bdb58ca"
    );

    #[test]
    fn process_basic_finalization_input() {
        let env = ExecutorEnv::builder()
            .add_input(&TEST_INPUT)
            .build()
            .unwrap();
        let mut exec = Executor::from_elf(env, FINALIZE_VOTES_ELF).unwrap();
        let session = exec.run().unwrap();
        assert_eq!(&session.journal, TEST_OUTPUT);
    }
}
