// Copyright 2024 RISC Zero, Inc.
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

#[cfg(test)]
mod tests;

use include_bytes_aligned::include_bytes_aligned;

use crate::ffi::sys_bigint2_2;
#[cfg(not(feature = "num-bigint-dig"))]
use num_bigint::BigUint;
#[cfg(feature = "num-bigint-dig")]
use num_bigint_dig::BigUint;

const DOUBLE_BLOB: &[u8] = include_bytes_aligned!(4, "double.blob");

#[derive(Clone, Debug, Eq, PartialEq)]
pub struct AffinePt {
    /// x coordinate
    pub x: BigUint,
    /// y coordinate
    pub y: BigUint,
}

impl AffinePt {
    /// The point as concatenated u32s for x and y
    ///
    /// Little-endian, x coordinate before y coordinate
    ///
    /// TODO: Ensure that this fills the bitwidth! Broken in rare cases otherwise!
    #[cfg(not(feature = "num-bigint-dig"))]
    pub fn to_u32s(&self) -> Vec<u32> {
        let mut output = self.x.to_u32_digits();
        output.extend(self.y.to_u32_digits());
        output
    }

    /// The point as concatenated u32s for x and y
    ///
    /// Little-endian, x coordinate before y coordinate
    ///
    /// TODO: Ensure that this fills the bitwidth! Broken in rare cases otherwise!
    #[cfg(feature = "num-bigint-dig")]
    pub fn to_u32s(&self) -> Vec<u32> {
        // TODO
        unimplemented!();
    }

    pub fn from_slice(slice: &[u32]) -> AffinePt {
        // TODO: Handle bitwidth properly, not hacked in like this
        const BITWIDTH: usize = 256;
        const WORD_WIDTH: usize = BITWIDTH / 32;

        let mut iter = slice.chunks(WORD_WIDTH);
        // TODO: length checking?
        let x = BigUint::from_slice(iter.next().expect("Slice too small to be an AffinePt"));
        let y = BigUint::from_slice(iter.next().expect("Slice too small to be an AffinePt"));
        assert_eq!(iter.len(), 0);
        AffinePt { x, y }
    }
}

pub fn double(point: AffinePt) -> AffinePt {
    // TODO: Handle bitwidth properly, not hacked in like this
    const BITWIDTH: usize = 256;
    const WORD_WIDTH: usize = BITWIDTH / 32;

    let mut result = [0u32; 2 * WORD_WIDTH];
    unsafe {
        double_raw(&point.to_u32s(), &mut result);
    }
    AffinePt::from_slice(&result)
}

/// SAFETY: Parameters must be aligned and correctly sized
///
/// Each parameter represents a field element and stores both coordinates; hence, the correct size
/// is twice the word width of an element of the elliptic curve field (or 1/16 the bitwidth when
/// the bitwidth is a multiple of 32).
unsafe fn double_raw(point: &[u32], result: &mut [u32]) {
    unsafe {
        sys_bigint2_2(DOUBLE_BLOB.as_ptr(), point.as_ptr(), result.as_mut_ptr());
    }
}

pub fn add(_lhs: &[u32], _rhs: &[u32], _result: &mut [u32]) {
    // TODO
    unimplemented!()
}
