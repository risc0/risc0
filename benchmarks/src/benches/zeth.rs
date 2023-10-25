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

use std::time::{Instant, Duration};

use risc0_zkvm::{
    serde::from_slice, sha::DIGEST_WORDS, ExecutorEnv, ExecutorImpl, MemoryImage, Receipt, Session,
};
use zeth_lib::{
    block_builder::{EthereumStrategyBundle, NetworkStrategyBundle},
    consts::ETH_MAINNET_CHAIN_SPEC,
    input::Input,
};
use zeth_primitives::BlockHash;

use crate::{get_cycles, get_image, Benchmark};

pub struct Job {
    pub spec: u64,
    pub input: Input<<EthereumStrategyBundle as NetworkStrategyBundle>::TxEssence>,
    pub image: MemoryImage,
    pub session: Option<Session>,
}

pub fn new_jobs() -> Vec<<Job as Benchmark>::Spec> {
    vec![16424130]
}

const METHOD_ID: [u32; DIGEST_WORDS] = zeth_guests::ETH_BLOCK_ID;
const METHOD_PATH: &'static str = zeth_guests::ETH_BLOCK_PATH;

fn cache_file_path(cache_path: &String, network: &String, block_no: u64, ext: &str) -> String {
    format!("{}/{}/{}.{}", cache_path, network, block_no, ext)
}

impl Benchmark for Job {
    const NAME: &'static str = "zeth";
    type Spec = u64;
    type ComputeOut = BlockHash;
    type ProofType = Receipt;

    fn job_size(_spec: &Self::Spec) -> u32 {
        1
    }

    fn output_size_bytes(_output: &Self::ComputeOut, proof: &Self::ProofType) -> u32 {
        (proof.journal.len()) as u32
    }

    fn proof_size_bytes(proof: &Self::ProofType) -> u32 {
        (proof
            .inner
            .composite()
            .unwrap()
            .segments
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

        let session = None;

        Job {
            spec,
            input,
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
       let env = ExecutorEnv::builder()
            .write(&self.input)
            .unwrap()
            .build()
            .unwrap();
        let mut exec = ExecutorImpl::new(env, self.image.clone()).unwrap();
        let start = Instant::now();
        let session = exec.run().unwrap();
        let elapsed = start.elapsed();
        let segments = session.resolve().unwrap();
        let (exec_cycles, prove_cycles) = get_cycles(segments);
        self.session = Some(session);
        (prove_cycles as u32, exec_cycles as u32, elapsed)
    }

    fn guest_compute(&mut self) -> (Self::ComputeOut, Self::ProofType) {
        let receipt = self.session.as_ref().unwrap().prove().expect("receipt");
        let result: BlockHash = from_slice(&receipt.journal).unwrap();
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
