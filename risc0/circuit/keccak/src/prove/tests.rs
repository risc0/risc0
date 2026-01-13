// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use std::rc::Rc;

use cfg_if::cfg_if;
use risc0_zkp::hal::{Buffer as _, Hal as _};
use test_log::test;

use super::testutil::test_inputs;
use crate::{
    prove::{
        CircuitWitnessGenerator as _, MetaBuffer, PreflightTrace, StepMode, keccak_prover,
        preflight::ForwardPreflightOrder,
    },
    zirgen::circuit::*,
};

#[test]
#[cfg_attr(feature = "cuda", gpu_guard::gpu_guard)]
fn basic() {
    let po2 = 8; // 256
    let inputs = test_inputs(po2);
    let prover = keccak_prover().unwrap();
    let seal = prover.prove(&inputs, po2).unwrap();
    prover.verify(&seal).expect("Verification failed");
}

#[test]
#[cfg_attr(feature = "cuda", gpu_guard::gpu_guard)]
fn fwd_rev_ab() {
    cfg_if! {
        if #[cfg(feature = "cuda")] {
            use risc0_zkp::hal::cuda::CudaHalPoseidon2;
            use crate::prove::hal::cuda::CudaCircuitHalPoseidon2;
            let hal = Rc::new(CudaHalPoseidon2::new());
            let circuit_hal = CudaCircuitHalPoseidon2::new(hal.clone());
        } else {
            use risc0_zkp::{core::hash::sha::Sha256HashSuite, hal::cpu::CpuHal};
            use crate::prove::hal::cpu::CpuCircuitHal;
            let suite = Sha256HashSuite::new_suite();
            let hal = Rc::new(CpuHal::new(suite));
            let circuit_hal = CpuCircuitHal;
        }
    }

    let po2 = 8;
    let inputs = test_inputs(po2);
    let cycles: usize = 1 << po2;
    let preflight = PreflightTrace::<ForwardPreflightOrder>::new(&inputs, cycles);

    let fwd_data = {
        let global = MetaBuffer::new("global", hal.as_ref(), 1, REGCOUNT_GLOBAL, true);
        let data = MetaBuffer::new("data", hal.as_ref(), cycles, REGCOUNT_DATA, true);
        circuit_hal
            .generate_witness(StepMode::SeqForward, &preflight, &global, &data)
            .unwrap();
        hal.eltwise_zeroize_elem(&data.buf);
        data.buf.to_vec()
    };

    let rev_data = {
        let global = MetaBuffer::new("global", hal.as_ref(), 1, REGCOUNT_GLOBAL, true);
        let data = MetaBuffer::new("data", hal.as_ref(), cycles, REGCOUNT_DATA, true);
        circuit_hal
            .scatter_preflight(&data, &preflight.scatter, &preflight.data)
            .unwrap();
        circuit_hal
            .generate_witness(StepMode::SeqReverse, &preflight, &global, &data)
            .unwrap();
        hal.eltwise_zeroize_elem(&data.buf);
        data.buf.to_vec()
    };

    assert_eq!(fwd_data, rev_data);
}
