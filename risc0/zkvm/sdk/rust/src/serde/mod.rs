// Copyright 2022 Risc0, Inc.
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

mod deserializer;
mod err;
mod serializer;

pub use deserializer::{from_slice, Deserializer};
pub use serializer::{to_slice, to_vec, to_vec_with_capacity, AllocVec, Serializer, Slice};

/// Align the given address `addr` upwards to alignment `align`.
///
/// Requires that `align` is a power of two.
fn align_up(addr: usize, align: usize) -> usize {
    (addr + align - 1) & !(align - 1)
}

#[cfg(test)]
mod test {
    use std::collections::HashMap;

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
        let input: HashMap<&str, u32> = HashMap::from([("foo", 1), ("bar", 2), ("baz", 3)]);
        let data = to_vec(&input).unwrap();
        let output: HashMap<&str, u32> = from_slice(data.as_slice()).unwrap();
        assert_eq!(input, output);
    }

    #[test]
    fn test_tuple_round_trip() {
        let input: (u32, u64) = (1, 2);
        let data = to_vec(&input).unwrap();
        let output: (u32, u64) = from_slice(data.as_slice()).unwrap();
        assert_eq!(input, output);
    }
}
