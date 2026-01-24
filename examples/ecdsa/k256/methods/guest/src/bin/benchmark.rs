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

use core::{hint::black_box, ops::Add};

use hex_literal::hex;
use k256::{
    FieldElement, ProjectivePoint, Scalar,
    elliptic_curve::{
        bigint::{Encoding, U256},
        ops::{Invert, LinearCombination, Reduce},
    },
};
use risc0_zkvm::guest::env;

/// Basic function for benchmarking an operation.
fn bench<T>(name: &str, func: impl Fn() -> T) {
    // Run the inner function twice, only logging the cycles in the second run, in
    // order to exclude paged-in operations from the benchmark count.
    black_box(func());

    let start = env::cycle_count();

    black_box(func());

    let end = env::cycle_count();
    println!("{}: {} cycles", name, end - start)
}

/// Benchmark key operations in the secp256k1 base field.
fn benchmark_field() {
    println!("Field operations:");
    let x = black_box(
        FieldElement::from_bytes(
            &hex!("EC08EAC2CBCEFE58E61038DCA45BA2B4A56BDF05A3595EBEE1BCFC488889C1CF").into(),
        )
        .unwrap(),
    );
    let y = black_box(
        FieldElement::from_bytes(
            &hex!("9FC3E90D2FAD03C8669F437A26374FA694CA76A7913C5E016322EBAA5C7616C5").into(),
        )
        .unwrap(),
    );

    bench("add", || x.add(&y));
    bench("mul", || x.mul(&y));
    bench("mul_single", || x.mul_single(42));
    bench("square", || x.square());
    bench("negate", || x.negate(0));
    bench("invert", || x.invert().unwrap());
}

/// Benchmark operations in the secp256k1 scalar field.
fn benchmark_scalar() {
    println!();
    println!("Scalar operations:");
    let x = black_box(Scalar::reduce(U256::from_be_bytes(hex!(
        "2A3F714FCDDEA4984F228C4D1DBD41A79B470B1546C68F6BB268A04AA0394BAC"
    ))));
    let y = black_box(Scalar::reduce(U256::from_be_bytes(hex!(
        "98973615F3B819529D885BBED9A69BC66A678D00289A8B1F3A0FF19801C10CDD"
    ))));

    bench("add", || x.add(&y));
    bench("mul", || x.mul(&y));
    bench("square", || x.square());
    bench("negate", || x.negate());
    bench("invert", || x.invert().unwrap());
    bench("invert_vartime", || x.invert_vartime().unwrap());
}

/// Benchmark secp256k1 elliptic curve group operations.
fn benchmark_group() {
    println!();
    println!("Group operations:");
    let x = black_box(Scalar::reduce(U256::from_be_bytes(hex!(
        "2a3f714fcddea4984f228c4d1dbd41a79b470b1546c68f6bb268a04aa0394bac"
    ))));
    let y = black_box(Scalar::reduce(U256::from_be_bytes(hex!(
        "98973615f3b819529d885bbed9a69bc66a678d00289a8b1f3a0ff19801c10cdd"
    ))));

    // NOTE: Accounts for >95% of the total cycle count for ECDSA verification.
    bench("lincomb", || {
        ProjectivePoint::lincomb(
            &ProjectivePoint::GENERATOR,
            &x,
            &ProjectivePoint::GENERATOR,
            &y,
        )
        .to_affine()
    });
}

fn main() {
    benchmark_field();
    benchmark_scalar();
    benchmark_group();
}
