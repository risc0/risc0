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

pub mod exec;
pub mod loader;
pub mod memory_argument;
pub mod opcode;

use anyhow::Result;
use risc0_binfmt::SegmentRecord;
use risc0_core::field::baby_bear::{BabyBear, BabyBearElem, BabyBearExtElem};
use risc0_zkp::{
    adapter::TapsProvider,
    hal::{CircuitHal, Hal},
    layout::Buffer,
    prove::{adapter::ProveAdapter, executor::Executor},
};

use crate::{
    layout::{OutBuffer, LAYOUT},
    CIRCUIT, REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA,
};

use self::{exec::MachineContext, loader::Loader};

pub fn prove_segment<H, C>(
    hal: &H,
    circuit_hal: &C,
    segment: SegmentRecord,
    po2: usize,
    io: &[BabyBearElem],
) -> Result<Vec<u32>>
where
    H: Hal<Field = BabyBear, Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H>,
{
    let machine = MachineContext::new(segment);
    let mut executor = Executor::new(&CIRCUIT, machine, po2, po2, &io);

    let loader = Loader::new();
    loader.load(|chunk, fini| executor.step(chunk, fini))?;
    executor.finalize();

    let mut adapter = ProveAdapter::new(&mut executor);
    let mut prover = risc0_zkp::prove::Prover::new(hal, CIRCUIT.get_taps());

    adapter.execute(prover.iop());

    prover.set_po2(adapter.po2() as usize);

    prover.commit_group(
        REGISTER_GROUP_CODE,
        hal.copy_from_elem("code", &adapter.get_code().as_slice()),
    );
    prover.commit_group(
        REGISTER_GROUP_DATA,
        hal.copy_from_elem("data", &adapter.get_data().as_slice()),
    );
    adapter.accumulate(prover.iop());
    prover.commit_group(
        REGISTER_GROUP_ACCUM,
        hal.copy_from_elem("accum", &adapter.get_accum().as_slice()),
    );

    let mix = hal.copy_from_elem("mix", &adapter.get_mix().as_slice());
    let out_slice = &adapter.get_io().as_slice();

    tracing::debug!("Globals: {:?}", OutBuffer(out_slice).tree(&LAYOUT));
    let out = hal.copy_from_elem("out", &adapter.get_io().as_slice());

    Ok(prover.finalize(&[&mix, &out], circuit_hal))
}
