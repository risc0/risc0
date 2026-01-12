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

use rand::Rng;
use risc0_zkp::{
    INV_RATE,
    adapter::CircuitInfo as _,
    field::{
        Elem, ExtElem,
        baby_bear::{BabyBearElem, BabyBearExtElem},
    },
    hal::{Buffer, CircuitHal, Hal},
};

use crate::{
    prove::CircuitImpl,
    zirgen::{
        circuit::{REGISTER_GROUP_ACCUM, REGISTER_GROUP_CODE, REGISTER_GROUP_DATA},
        taps::TAPSET,
    },
};

use super::KeccakState;

pub struct EvalCheckParams {
    pub po2: usize,
    pub steps: usize,
    pub domain: usize,
    pub code: Vec<BabyBearElem>,
    pub data: Vec<BabyBearElem>,
    pub accum: Vec<BabyBearElem>,
    pub mix: Vec<BabyBearElem>,
    pub out: Vec<BabyBearElem>,
    pub poly_mix: BabyBearExtElem,
}

impl EvalCheckParams {
    pub fn new(po2: usize) -> Self {
        let mut rng = rand::rng();
        let steps = 1 << po2;
        let domain = steps * INV_RATE;
        let code_size = TAPSET.group_size(REGISTER_GROUP_CODE);
        let data_size = TAPSET.group_size(REGISTER_GROUP_DATA);
        let accum_size = TAPSET.group_size(REGISTER_GROUP_ACCUM);
        let code = random_fps(&mut rng, code_size * domain);
        let data = random_fps(&mut rng, data_size * domain);
        let accum = random_fps(&mut rng, accum_size * domain);
        let mix = random_fps(&mut rng, CircuitImpl::MIX_SIZE);
        let out = random_fps(&mut rng, CircuitImpl::OUTPUT_SIZE);
        let poly_mix = BabyBearExtElem::random(&mut rng);
        tracing::debug!("code: {} bytes", code.len() * 4);
        tracing::debug!("data: {} bytes", data.len() * 4);
        tracing::debug!("accum: {} bytes", accum.len() * 4);
        tracing::debug!("mix: {} bytes", mix.len() * 4);
        tracing::debug!("out: {} bytes", out.len() * 4);
        Self {
            po2,
            steps,
            domain,
            code,
            data,
            accum,
            mix,
            out,
            poly_mix,
        }
    }
}

fn random_fps<E: Elem>(rng: &mut impl Rng, size: usize) -> Vec<E> {
    let mut ret = Vec::new();
    for _ in 0..size {
        ret.push(E::random(rng));
    }
    ret
}

#[allow(unused)]
pub(crate) fn eval_check<H1, H2, C1, C2>(hal1: &H1, eval1: C1, hal2: &H2, eval2: C2, po2: usize)
where
    H1: Hal<Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    H2: Hal<Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C1: CircuitHal<H1>,
    C2: CircuitHal<H2>,
{
    let params = EvalCheckParams::new(po2);
    let check1 = eval_check_impl(&params, hal1, &eval1);
    let check2 = eval_check_impl(&params, hal2, &eval2);
    assert_eq!(check1, check2);
}

pub fn eval_check_impl<H, C>(params: &EvalCheckParams, hal: &H, circuit_hal: &C) -> Vec<H::Elem>
where
    H: Hal<Elem = BabyBearElem, ExtElem = BabyBearExtElem>,
    C: CircuitHal<H>,
{
    let check = hal.alloc_elem("check", BabyBearExtElem::EXT_SIZE * params.domain);
    let code = hal.copy_from_elem("code", &params.code);
    let data = hal.copy_from_elem("data", &params.data);
    let accum = hal.copy_from_elem("accum", &params.accum);
    let mix = hal.copy_from_elem("mix", &params.mix);
    let out = hal.copy_from_elem("out", &params.out);
    circuit_hal.eval_check(
        &check,
        &[&accum, &code, &data],
        &[&mix, &out],
        params.poly_mix,
        params.po2,
        params.steps,
    );
    let mut ret = vec![H::Elem::ZERO; check.size()];
    check.view(|view| {
        ret.clone_from_slice(view);
    });
    ret
}

pub fn test_inputs(po2: usize) -> Vec<KeccakState> {
    let mut state = KeccakState::default();
    let mut pows = 987654321_u64;
    for part in state.as_mut_slice() {
        *part = pows;
        pows = pows.wrapping_mul(123456789);
    }

    let cycles = 1 << po2;
    let count = cycles / 200; // roughly 200 cycles per keccakf
    vec![state; count]
}
