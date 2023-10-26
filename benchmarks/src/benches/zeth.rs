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

use std::time::Duration;

use risc0_zkvm::{sha::DIGEST_WORDS, ExecutorEnv, ExitCode, MemoryImage, Receipt, Session};
use zeth_lib::{
    block_builder::{EthereumStrategyBundle, NetworkStrategyBundle},
    consts::ETH_MAINNET_CHAIN_SPEC,
    input::Input,
};
use zeth_primitives::BlockHash;

use crate::{exec_compute, get_image, Benchmark};

pub struct Job<'a> {
    pub spec: u64,
    pub env: ExecutorEnv<'a>,
    pub image: MemoryImage,
    pub session: Session,
}

pub fn new_jobs() -> Vec<<Job<'static> as Benchmark>::Spec> {
    vec![16424130]
}

const METHOD_ID: [u32; DIGEST_WORDS] = zeth_guests::ETH_BLOCK_ID;
const METHOD_PATH: &'static str = zeth_guests::ETH_BLOCK_PATH;

fn cache_file_path(cache_path: &String, network: &String, block_no: u64, ext: &str) -> String {
    format!("{}/{}/{}.{}", cache_path, network, block_no, ext)
}

impl Benchmark for Job<'_> {
    const NAME: &'static str = "zeth";
    type Spec = u64;
    type ComputeOut = BlockHash;
    type ProofType = Receipt;

    fn job_size(_spec: &Self::Spec) -> u32 {
        1
    }

    fn output_size_bytes(_output: &Self::ComputeOut, proof: &Self::ProofType) -> u32 {
        proof.journal.bytes.len() as u32
    }

    fn proof_size_bytes(proof: &Self::ProofType) -> u32 {
        (proof
            .inner
            .flat()
            .unwrap()
            .iter()
            .fold(0, |acc, segment| acc + segment.get_seal_bytes().len())) as u32
    }

    fn new(spec: Self::Spec) -> Self {
        let image = get_image(METHOD_PATH);

        // Fetch all of the initial data
        let rpc_cache = Some(cache_file_path(
            &"testdata".to_string(),
            &"ethereum".to_string(),
            spec,
            "json.gz",
        ));

        let init_spec = ETH_MAINNET_CHAIN_SPEC.clone();
        let init = zeth_lib::host::get_initial_data::<EthereumStrategyBundle>(
            init_spec, rpc_cache, None, spec,
        )
        .expect("Could not init");

        let input: Input<<EthereumStrategyBundle as NetworkStrategyBundle>::TxEssence> =
            init.clone().into();

        let env = ExecutorEnv::builder()
            .write(&input)
            .unwrap()
            .build()
            .unwrap();

        let session = Session::new(vec![], vec![], ExitCode::Halted(0));

        Job {
            spec,
            env,
            image,
            session,
        }
    }

    fn spec(&self) -> &Self::Spec {
        &self.spec
    }

    fn host_compute(&mut self) -> Option<Self::ComputeOut> {
        let block_hash =
            hex::decode("caaa482d7f962e4457d2b161632667700b3047f81546528ff2ca121ff0e7f9c1")
                .unwrap();
        Some(BlockHash::from_slice(&block_hash))
    }

    fn exec_compute(&mut self) -> (u32, u32, Duration) {
        let (cycles, insn_cycles, elapsed, session) =
            exec_compute(self.image.clone(), self.env.clone());
        self.session = session;
        (cycles, insn_cycles, elapsed)
    }

    fn guest_compute(&mut self) -> (Self::ComputeOut, Self::ProofType) {
        let receipt = self.session.prove().expect("receipt");
        let result: BlockHash = receipt.journal.decode().unwrap();
        (result, receipt)
    }

    fn verify_proof(&self, _output: &Self::ComputeOut, proof: &Self::ProofType) -> bool {
        let result = proof.verify(METHOD_ID);

        match result {
            Ok(_) => true,
            Err(err) => {
                println!("{}", err);
                false
            }
        }
    }
}
