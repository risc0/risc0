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

use merkletree::{merkle::MerkleTree, store::VecStore};
use risc0_benchmark::{exec_compute, get_image, Benchmark};
use risc0_benchmark_lib::{generate_vector_of_elements, Item, Sha256Hasher};
use risc0_zkvm::{
    serde::{from_slice, to_vec},
    sha::DIGEST_WORDS,
    ExecutorEnv, ExitCode, MemoryImage, Receipt, Session,
};
use std::time::Duration;

pub struct Job<'a> {
    pub spec: u32,
    pub env: ExecutorEnv<'a>,
    pub image: MemoryImage,
    pub session: Session,
}

pub fn new_jobs() -> Vec<<Job<'static> as Benchmark>::Spec> {
    vec![1024, 32768, 1048576]
}

const METHOD_ID: [u32; DIGEST_WORDS] = risc0_benchmark_methods::MERKLE_TREE_ID;
const METHOD_PATH: &'static str = risc0_benchmark_methods::MERKLE_TREE_PATH;

impl Benchmark for Job<'_> {
    const NAME: &'static str = "merkle_tree";
    type Spec = u32;
    type ComputeOut = (Item, Item);
    type ProofType = Receipt;

    fn job_size(spec: &Self::Spec) -> u32 {
        *spec
    }

    fn output_size_bytes(_output: &Self::ComputeOut, proof: &Self::ProofType) -> u32 {
        (proof.journal.len()) as u32
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

        let data = generate_vector_of_elements::<Item>(spec.try_into().unwrap());
        let tree = MerkleTree::<Item, Sha256Hasher, VecStore<Item>>::new(data).unwrap();
        let proof = tree.gen_proof(0).unwrap();
        let lemma = proof.lemma();
        let path = proof.path();

        let env = ExecutorEnv::builder()
            .add_input(&to_vec(&(lemma, path)).unwrap())
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
        let data = generate_vector_of_elements::<Item>(self.spec.try_into().unwrap());
        let tree = MerkleTree::<Item, Sha256Hasher, VecStore<Item>>::new(data).unwrap();
        let proof = tree.gen_proof(0).unwrap();
        assert!(proof.validate::<Sha256Hasher>().unwrap());
        Some((proof.item(), proof.root()))
    }

    fn exec_compute(&mut self) -> (u32, u32, Duration) {
        let (cycles, insn_cycles, elapsed, session) =
            exec_compute(self.image.clone(), self.env.clone());
        self.session = session;
        (cycles, insn_cycles, elapsed)
    }

    fn guest_compute(&mut self) -> (Self::ComputeOut, Self::ProofType) {
        let receipt = self.session.prove().expect("receipt");
        let (index, root) = from_slice::<(Item, Item), _>(&receipt.journal)
            .unwrap()
            .try_into()
            .unwrap();
        ((index, root), receipt)
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
