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

//! Host-side pre-computation of NTT twiddle factor tables.
//!
//! These tables are computed on the CPU using the existing Baby Bear field
//! implementation and uploaded to the GPU as cubecl Array buffers.
//!
//! All values are stored in raw Montgomery form (matching the GPU representation).

use risc0_core::field::{
    Elem, RootsOfUnity,
    baby_bear::BabyBearElem,
};

/// Maximum log2 domain size for Baby Bear NTT.
pub const MAX_LG_DOMAIN_SIZE: u32 = 27;

/// Log2 of the twiddle window size: (27 + 4) / 5 = 6
pub const LG_WINDOW_SIZE: u32 = 6;

/// Twiddle window size: 2^6 = 64
pub const WINDOW_SIZE: u32 = 1 << LG_WINDOW_SIZE;

/// Number of windows: ceil(27 / 6) = 5
pub const WINDOW_NUM: u32 = (MAX_LG_DOMAIN_SIZE + LG_WINDOW_SIZE - 1) / LG_WINDOW_SIZE;

/// Extract the raw Montgomery-form u32 from a BabyBearElem.
///
/// This returns the internal representation, NOT the decoded value.
/// `u32::from(elem)` would decode from Montgomery form, which is wrong
/// for GPU twiddle tables that operate in Montgomery form.
fn raw_mont(elem: BabyBearElem) -> u32 {
    elem.to_u32_words()[0]
}

/// Generate partial twiddle tables for windowed root-of-unity computation.
///
/// Returns a flat array of WINDOW_NUM * WINDOW_SIZE (5 * 64 = 320) elements
/// in raw Montgomery form.
///
/// Window `i` contains: root^(j * 2^(i * LG_WINDOW_SIZE)) for j in 0..WINDOW_SIZE,
/// where root is the principal 2^MAX_LG_DOMAIN_SIZE-th root of unity.
pub fn generate_partial_twiddles(inverse: bool) -> Vec<u32> {
    let roots = if inverse {
        BabyBearElem::ROU_REV
    } else {
        BabyBearElem::ROU_FWD
    };

    let root_of_unity = roots[MAX_LG_DOMAIN_SIZE as usize];
    let mut table = vec![0u32; (WINDOW_NUM * WINDOW_SIZE) as usize];

    for tid in 0..WINDOW_SIZE {
        // root = root_of_unity ^ tid
        let mut root = root_of_unity.pow(tid as usize);

        // Window 0
        table[tid as usize] = raw_mont(root);

        // Subsequent windows: square LG_WINDOW_SIZE times per window
        for off in 1..WINDOW_NUM {
            for _ in 0..LG_WINDOW_SIZE {
                root = root * root;
            }
            table[(off * WINDOW_SIZE + tid) as usize] = raw_mont(root);
        }
    }

    table
}

/// Generate radix twiddle tables (radix 6 through 10).
///
/// Returns a flat array of 512 + 256 + 128 + 64 + 32 = 992 elements in raw
/// Montgomery form, laid out as:
///   [radix10(512), radix9(256), radix8(128), radix7(64), radix6(32)]
///
/// The radix-10 twiddles use roots[10] (the principal 1024th root of unity).
pub fn generate_radix_twiddles(inverse: bool) -> Vec<u32> {
    let roots = if inverse {
        BabyBearElem::ROU_REV
    } else {
        BabyBearElem::ROU_FWD
    };

    let root10 = roots[10]; // 1024th root of unity
    let mut blob = vec![0u32; 992];

    // Generate 512 entries for radix-10: root10^i for i in 0..512
    for i in 0..512u32 {
        let root = root10.pow(i as usize);
        blob[i as usize] = raw_mont(root);
    }

    // Decimate for smaller radices:
    // radix9 (256 entries at offset 512): every 2nd element
    for i in 0..256u32 {
        blob[(512 + i) as usize] = blob[(i * 2) as usize];
    }
    // radix8 (128 entries at offset 768): every 4th element
    for i in 0..128u32 {
        blob[(768 + i) as usize] = blob[(i * 4) as usize];
    }
    // radix7 (64 entries at offset 896): every 8th element
    for i in 0..64u32 {
        blob[(896 + i) as usize] = blob[(i * 8) as usize];
    }
    // radix6 (32 entries at offset 960): every 16th element
    for i in 0..32u32 {
        blob[(960 + i) as usize] = blob[(i * 16) as usize];
    }

    blob
}

/// Number of plus-one twiddle rows: MAX_LG_DOMAIN_SIZE - 10 + 1 = 18
/// Row index `off` is used when nbits = off + 10 (nbits = MAX_LG_DOMAIN_SIZE - stage).
pub const PLUS_ONE_ROWS: u32 = MAX_LG_DOMAIN_SIZE - 10 + 1;

/// Number of columns per plus-one twiddle row.
pub const PLUS_ONE_COLS: u32 = 1024;

/// Generate plus-one twiddle tables for z_count>1 correction.
///
/// Returns a flat array of PLUS_ONE_ROWS * PLUS_ONE_COLS (12 * 1024 = 12288)
/// elements in raw Montgomery form.
///
/// Row 0: root_of_unity ^ bit_rev(tid, 10) for tid in 0..1024
/// Row k: successive squarings of row 0 (k times)
///
/// These correct for the position offset between the z_count elements
/// that each thread processes.
pub fn generate_plus_one_twiddles(inverse: bool) -> Vec<u32> {
    let roots = if inverse {
        BabyBearElem::ROU_REV
    } else {
        BabyBearElem::ROU_FWD
    };

    let root_of_unity = roots[MAX_LG_DOMAIN_SIZE as usize];
    let total = (PLUS_ONE_ROWS * PLUS_ONE_COLS) as usize;
    let mut table = vec![0u32; total];

    for tid in 0..PLUS_ONE_COLS {
        let rev = (tid as u32).reverse_bits() >> (32 - 10);
        let mut root = root_of_unity.pow(rev as usize);

        table[tid as usize] = raw_mont(root);

        for off in 1..PLUS_ONE_ROWS {
            root = root * root; // square
            table[(off * PLUS_ONE_COLS + tid) as usize] = raw_mont(root);
        }
    }

    table
}

/// Generate domain size inverse table.
///
/// Returns an array of MAX_LG_DOMAIN_SIZE + 1 = 28 elements in raw Montgomery
/// form, where index `i` contains (2^i)^{-1} mod P.
pub fn generate_domain_size_inverses() -> Vec<u32> {
    let mut inverses = vec![0u32; (MAX_LG_DOMAIN_SIZE + 1) as usize];

    for i in 0..=MAX_LG_DOMAIN_SIZE {
        let domain_size = BabyBearElem::new(1u32 << i);
        let inv = domain_size.inv();
        inverses[i as usize] = raw_mont(inv);
    }

    inverses
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_partial_twiddles_identity() {
        let twiddles = generate_partial_twiddles(false);
        // Window 0, index 0 should be root^0 = 1 (in Montgomery form)
        assert_eq!(twiddles[0], raw_mont(BabyBearElem::ONE));
    }

    #[test]
    fn test_radix_twiddles_identity() {
        let twiddles = generate_radix_twiddles(false);
        // Index 0 should be root10^0 = 1
        assert_eq!(twiddles[0], raw_mont(BabyBearElem::ONE));
    }

    #[test]
    fn test_domain_size_inverses() {
        let inverses = generate_domain_size_inverses();
        // 2^0 = 1, inverse = 1
        assert_eq!(inverses[0], raw_mont(BabyBearElem::ONE));

        // Verify: (2^i) * (2^i)^{-1} = 1 for each i
        for i in 0..=MAX_LG_DOMAIN_SIZE {
            let domain_size = BabyBearElem::new(1u32 << i);
            let inv = BabyBearElem::from_u32_words(&[inverses[i as usize]]);
            let product = domain_size * inv;
            assert_eq!(product, BabyBearElem::ONE, "Failed for i={i}");
        }
    }

    #[test]
    fn test_plus_one_twiddles() {
        let twiddles = generate_plus_one_twiddles(false);
        assert_eq!(twiddles.len(), (PLUS_ONE_ROWS * PLUS_ONE_COLS) as usize);
        // bit_rev(0, 10) = 0, so root^0 = 1
        assert_eq!(twiddles[0], raw_mont(BabyBearElem::ONE));

        // Row 1 should be the square of row 0
        let row0_1 = BabyBearElem::from_u32_words(&[twiddles[1]]);
        let row1_1 = BabyBearElem::from_u32_words(&[twiddles[PLUS_ONE_COLS as usize + 1]]);
        assert_eq!(row1_1, row0_1 * row0_1);
    }

    #[test]
    fn test_partial_twiddles_roundtrip() {
        // Verify that forward and inverse roots are inverses of each other
        let fwd = generate_partial_twiddles(false);
        let inv = generate_partial_twiddles(true);

        // Window 0, index 1: fwd_root * inv_root should equal 1
        let fwd_root = BabyBearElem::from_u32_words(&[fwd[1]]);
        let inv_root = BabyBearElem::from_u32_words(&[inv[1]]);
        let product = fwd_root * inv_root;
        assert_eq!(product, BabyBearElem::ONE);
    }
}
