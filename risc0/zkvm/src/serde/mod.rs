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

pub use deserializer::{Deserializer, WordRead, from_slice};
pub use err::{Error, Result};
pub use serializer::{Serializer, WordWrite, to_vec, to_vec_with_capacity};

#[cfg(test)]
mod tests {
    use crate::serde::{from_slice, to_vec};
    use alloc::{collections::BTreeMap, string::String, vec, vec::Vec};
    use chrono::NaiveDate;

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
    fn naive_date_round_trip() {
        let input: NaiveDate = NaiveDate::parse_from_str("2015-09-05", "%Y-%m-%d").unwrap();
        let date_vec = to_vec(&input).unwrap();
        let output: NaiveDate = from_slice(date_vec.as_slice()).unwrap();
        assert_eq!(input, output);
    }
}
