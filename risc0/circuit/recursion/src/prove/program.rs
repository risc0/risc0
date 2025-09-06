// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::Result;

use risc0_zkp::{
    ZK_CYCLES,
    core::{digest::Digest, hash::HashSuite},
    field::baby_bear::{BabyBear, BabyBearElem},
    hal::{self, Hal},
    prove::poly_group::PolyGroup,
};

use super::RECURSION_CODE_SIZE;

/// A Program for the recursion circuit (e.g. lift_20 or join).
///
/// The recursion circuit is an application specific virtual machine with a limited instruction
/// set, no control flow operations, and a write-once memory tape. Although it is not general
/// purpose, it can load and execute a program, similar to the rv32im zkVM.
///
/// Programs for the recursion circuit are loaded into the control columns, which is a set of
/// public columns in the witness. Programs are therefore identified by their control ID, which is
/// similar but not the same as the image ID used to identify rv32im programs.
#[derive(Clone)]
pub struct Program {
    /// The code of the program, encoded as Baby Bear field elements.
    pub code: Vec<BabyBearElem>,

    /// The number of code columns.
    pub code_size: usize,

    /// 1 << po2 is the number of cycles executed.
    pub po2: usize,
}

impl Program {
    /// Create a [Program] from a stream of data encoded by Zirgen.
    pub fn from_encoded(encoded: &[u32], po2: usize) -> Self {
        let prog = Self {
            code: encoded.iter().copied().map(BabyBearElem::from).collect(),
            code_size: RECURSION_CODE_SIZE,
            po2,
        };
        assert_eq!(prog.code.len() % RECURSION_CODE_SIZE, 0);
        assert!(prog.code.len() <= (RECURSION_CODE_SIZE * ((1 << po2) - ZK_CYCLES)));
        prog
    }

    /// Total number of rows in the code group for this program.
    pub fn code_rows(&self) -> usize {
        self.code.len() / self.code_size
    }

    /// An iterator over the rows of the code group.
    pub fn code_by_row(&self) -> impl Iterator<Item = &[BabyBearElem]> {
        self.code.as_slice().chunks(self.code_size)
    }

    /// Given a [Program] for the recursion circuit, compute the control ID as the FRI Merkle root
    /// of the code group. This uniquely identifies the program running on the recursion circuit
    /// (e.g. lift_20 or join)
    pub fn compute_control_id(&self, hash_suite: HashSuite<BabyBear>) -> Result<Digest> {
        #[cfg(feature = "cuda")]
        let digest =
            self.compute_control_id_inner(&hal::cuda::CudaHal::new_from_hash_suite(hash_suite)?);

        #[cfg(not(feature = "cuda"))]
        let digest = self.compute_control_id_inner(&hal::cpu::CpuHal::new(hash_suite));

        Ok(digest)
    }

    fn compute_control_id_inner(&self, hal: &impl Hal<Elem = BabyBearElem>) -> Digest {
        let cycles = 1 << self.po2;

        let mut code = vec![BabyBearElem::default(); cycles * self.code_size];

        for (cycle, row) in self.code_by_row().enumerate() {
            for (i, elem) in row.iter().enumerate() {
                code[cycles * i + cycle] = *elem;
            }
        }
        let coeffs = hal.copy_from_elem("coeffs", &code);
        // Do interpolate & shift
        hal.batch_interpolate_ntt(&coeffs, self.code_size);
        hal.zk_shift(&coeffs, self.code_size);
        // Make the poly-group & extract the root
        let code_group = PolyGroup::new(hal, coeffs, self.code_size, cycles, "code");
        let root = *code_group.merkle.root();
        tracing::trace!("Computed recursion code: {root:?}");
        root
    }
}
