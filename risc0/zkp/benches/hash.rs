// Copyright 2025 RISC Zero, Inc.
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

use criterion::{Criterion, criterion_group, criterion_main};
use p3_field::PackedValue;
use p3_symmetric::Permutation;
use rand::Rng;
use risc0_core::field::{Elem, baby_bear::BabyBearElem};
use risc0_zkp::core::hash::poseidon2::{CELLS as POSEIDON2_CELLS, poseidon2_mix};

fn benchmark_poseidon2_mix(c: &mut Criterion) {
    let mut rng = rand::rng();
    let mut cells = [BabyBearElem::random(&mut rng); POSEIDON2_CELLS];
    c.bench_function("poseidon2_mix", |b| b.iter(|| poseidon2_mix(&mut cells)));
}

fn benchmark_poseidon2_p3_mix_x8(c: &mut Criterion) {
    let hasher = p3_baby_bear::default_babybear_poseidon2_24();
    let mut rng = rand::rng();
    let mut cells: [<p3_baby_bear::BabyBear as p3_field::Field>::Packing; 24] = rng.random();
    c.bench_function("poseidon2_p3_mix", |b| {
        b.iter(|| hasher.permute_mut(&mut cells))
    });
    assert_eq!(
        <p3_baby_bear::BabyBear as p3_field::Field>::Packing::unpack_slice(cells.as_slice()).len(),
        24 * 8
    );
}

criterion_group!(
    benches,
    benchmark_poseidon2_mix,
    benchmark_poseidon2_p3_mix_x8
);
criterion_main!(benches);
