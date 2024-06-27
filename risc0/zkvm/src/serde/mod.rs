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

//! Serialization and deserialization tools for the RISC Zero zkVM
//!
//! Data needs to be serialized for transmission between the zkVM host and
//! guest. This module contains tools for this serialization and the
//! corresponding deserialization.
//!
//! On the host side, a serialization function such as [to_vec] should be used
//! when transmitting data to the guest. Similarly, the deserialization function
//! [from_slice] should be used when reading data from the guest. For example:
//! ```rust
//! use risc0_zkvm::serde::{from_slice, to_vec};
//! let input = 42_u32;
//! let encoded = to_vec(&[input]).unwrap();
//! let output: u32 = from_slice(&encoded).unwrap();
//! assert_eq!(input, output);
//! ```
//!
//! On the guest side, the necessary (de)serialization functionality is
//! included in [`env`] module functions such as [`env::read`] and
//! [`env::commit`], so this crate rarely needs to be directly used in the
//! guest.
//!
//! [`env`]: ../guest/env/index.html
//! [`env::commit`]: ../guest/env/fn.commit.html
//! [`env::read`]: ../guest/env/fn.read.html

mod deserializer;
mod err;
mod serializer;

pub use deserializer::{from_slice, Deserializer, WordRead};
pub use err::{Error, Result};
pub use serializer::{to_vec, to_vec_with_capacity, Serializer, WordWrite};

#[cfg(test)]
mod tests {
    use alloc::{collections::BTreeMap, string::String, vec, vec::Vec};
    use serde::{Deserialize, Serialize};

    use crate::serde::{from_slice, to_vec};

    #[test]
    fn test_vec_round_trip() {
        let input: Vec<u64> = vec![1, 2, 3];
        let data = to_vec(&input).unwrap();
        let output: Vec<u64> = from_slice(data.as_slice()).unwrap();
        assert_eq!(input, output);
    }

    #[test]
    fn test_map_round_trip() {
        let input: BTreeMap<String, u32> =
            BTreeMap::from([("foo".into(), 1), ("bar".into(), 2), ("baz".into(), 3)]);
        let data = to_vec(&input).unwrap();
        let output: BTreeMap<String, u32> = from_slice(data.as_slice()).unwrap();
        assert_eq!(input, output);
    }

    #[test]
    fn test_tuple_round_trip() {
        let input: (u32, u64) = (1, 2);
        let data = to_vec(&input).unwrap();
        let output: (u32, u64) = from_slice(data.as_slice()).unwrap();
        assert_eq!(input, output);
    }

    #[test]
    fn test_mixed_tuple() {
        type TestType = (Vec<u8>, u32, u8, u8, Vec<u8>, u8);
        let input: TestType = (vec![0u8, 1], 8u32, 7u8, 222u8, vec![1, 1, 1, 1, 1], 5u8);
        let data = to_vec(&input).unwrap();
        assert_eq!([2, 256, 8, 56839, 5, 16843009, 1281].as_slice(), data);
        let output: TestType = from_slice(&data).unwrap();
        assert_eq!(input, output);
    }

    #[test]
    fn test_mixed_struct() {
        #[derive(Debug, Serialize, PartialEq, Eq, Deserialize)]
        struct WrappedU8(pub u8);

        #[derive(Default, Debug, PartialEq, Eq, Serialize, Deserialize)]
        struct TestType {
            pub wrapped_u8_seq: Vec<WrappedU8>,
            pub u16_seq: Vec<u16>,
            pub u32_seq: Vec<u32>,
            pub u64_seq: Vec<u64>,
            pub i8_seq: Vec<i8>,
            pub i16_seq: Vec<i16>,
            pub i32_seq: Vec<i32>,
            pub i64_seq: Vec<i64>,
            pub u8: u8,
            pub bool: bool,
            pub some_u16: Option<u16>,
            pub none_u32: Option<u32>,
            pub string_seq: Vec<u8>,
            pub string_seq_seq: Vec<Vec<u8>>,
        }

        let mut input = TestType::default();
        input.wrapped_u8_seq = vec![WrappedU8(1u8), WrappedU8(231u8), WrappedU8(123u8)];
        input.u16_seq = vec![124u16, 41374u16];
        input.u32_seq = vec![14710471u32, 3590275702u32, 1u32, 2u32];
        input.u64_seq = vec![352905235952532u64, 2147102974910410u64];
        input.i8_seq = vec![-1i8, 120i8, -22i8];
        input.i16_seq = vec![-7932i16];
        input.i32_seq = vec![-4327i32, 35207277i32];
        input.i64_seq = vec![-1i64, 1i64];
        input.u8 = 3u8;
        input.bool = true;
        input.some_u16 = Some(5u16);
        input.none_u32 = None;
        input.string_seq = b"Here is a string.".to_vec();
        input.string_seq_seq = vec![b"string a".to_vec(), b"34720471290497230".to_vec()];

        let data = to_vec(&input).unwrap();
        assert_eq!(
            [
                3u32, 8120065, 2, 124, 41374, 4, 14710471, 3590275702, 1, 2, 2, 658142100, 82167,
                1578999754, 499911, 3, 4294967295, 120, 4294967274, 1, 4294959364, 2, 4294962969,
                35207277, 2, 4294967295, 4294967295, 1, 0, 259, 1, 5, 0, 17, 1701995848, 544434464,
                1953701985, 1735289202, 46, 2, 8, 1769108595, 1629513582, 17, 842478643, 825701424,
                875575602, 858928953, 48,
            ]
            .as_slice(),
            data
        );

        let output: TestType = from_slice(&data).unwrap();
        assert_eq!(input, output);
    }

    #[test]
    fn test_edge_cases() {
        #[derive(PartialEq, Eq, Debug, Default, Serialize, Deserialize)]
        struct U8SeqThenU32(Vec<u8>, u32);
        #[derive(PartialEq, Eq, Debug, Default, Serialize, Deserialize)]
        struct U32ThenU8SeqT(u32, Vec<u8>);

        for i in 0..=5 {
            let mut input = U8SeqThenU32::default();
            input.0 = vec![127u8; i];
            let data = to_vec(&input).unwrap();
            let output: U8SeqThenU32 = from_slice(&data).unwrap();
            assert_eq!(input, output);
        }

        for i in 0..=5 {
            let mut input = U32ThenU8SeqT::default();
            input.1 = vec![127u8; i];
            let data = to_vec(&input).unwrap();
            let output: U32ThenU8SeqT = from_slice(&data).unwrap();
            assert_eq!(input, output);
        }
    }
}
