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

use alloc::vec::Vec;

use risc0_zkvm_platform::WORD_SIZE;

use super::err::{Error, Result};

use crate::alloc::string::ToString;

/// A writer for writing streams preferring word-based data.
pub trait WordWrite {
    /// Write the given words to the stream.
    fn write_words(&mut self, words: &[u32]) -> Result<()>;

    /// Write the given bytes to the stream, padding up to the next word
    /// boundary.
    // TODO: Do we still want to pad the bytes now that we have
    // posix-style I/O that can read things into buffers right where
    // we want them to be?  If we don't, we could change the
    // serialization buffers to use Vec<u8> instead of Vec<u32>,
    fn write_padded_bytes(&mut self, bytes: &[u8]) -> Result<()>;
}

impl WordWrite for Vec<u32> {
    fn write_words(&mut self, words: &[u32]) -> Result<()> {
        self.extend_from_slice(words);
        Ok(())
    }

    fn write_padded_bytes(&mut self, bytes: &[u8]) -> Result<()> {
        let chunks = bytes.chunks_exact(WORD_SIZE);
        let last_word = chunks.remainder();
        self.extend(chunks.map(|word_bytes| u32::from_le_bytes(word_bytes.try_into().unwrap())));
        if !last_word.is_empty() {
            let mut last_word_bytes = [0u8; WORD_SIZE];
            last_word_bytes[..last_word.len()].clone_from_slice(last_word);
            self.push(u32::from_le_bytes(last_word_bytes));
        }
        Ok(())
    }
}

// Allow borrowed WordWrites to work transparently.
impl<W: WordWrite + ?Sized> WordWrite for &mut W {
    #[inline]
    fn write_words(&mut self, words: &[u32]) -> Result<()> {
        (**self).write_words(words)
    }

    #[inline]
    fn write_padded_bytes(&mut self, bytes: &[u8]) -> Result<()> {
        (**self).write_padded_bytes(bytes)
    }
}

/// Serialize to a vector of u32 words
pub fn to_vec<T>(value: &T) -> Result<Vec<u32>>
where
    T: serde::Serialize + ?Sized,
{
    // Use the in-memory size of the value as a guess for the length
    // of the serialized value.
    let mut vec: Vec<u32> = Vec::with_capacity(core::mem::size_of_val(value));
    let mut serializer = Serializer::new(&mut vec);
    value.serialize(&mut serializer)?;
    Ok(vec)
}

/// Serialize to a vector of u32 words with size hinting
///
/// Includes a caller-provided hint `cap` giving the capacity of u32 words
/// necessary to serialize `value`.
pub fn to_vec_with_capacity<T>(value: &T, cap: usize) -> Result<Vec<u32>>
where
    T: serde::Serialize + ?Sized,
{
    let mut vec: Vec<u32> = Vec::with_capacity(cap);
    let mut serializer = Serializer::new(&mut vec);
    value.serialize(&mut serializer)?;
    Ok(vec)
}

/// Enables serializing to a stream
pub struct Serializer<W: WordWrite> {
    stream: W,
}

impl<W: WordWrite> Serializer<W> {
    /// Construct a Serializer
    ///
    /// Creates a serializer that writes to `stream`.
    pub fn new(stream: W) -> Self {
        Serializer { stream }
    }
}

impl<W: WordWrite> serde::ser::Serializer for &'_ mut Serializer<W> {
    type Ok = ();
    type Error = Error;
    type SerializeSeq = Self;
    type SerializeTuple = Self;
    type SerializeTupleStruct = Self;
    type SerializeTupleVariant = Self;
    type SerializeMap = Self;
    type SerializeStruct = Self;
    type SerializeStructVariant = Self;

    fn is_human_readable(&self) -> bool {
        false
    }

    fn collect_str<T>(self, value: &T) -> Result<()>
    where
        T: ?Sized + core::fmt::Display,
    {
        self.serialize_str(&value.to_string())
    }

    fn serialize_bool(self, v: bool) -> Result<()> {
        self.serialize_u8(if v { 1 } else { 0 })
    }

    fn serialize_i8(self, v: i8) -> Result<()> {
        self.serialize_i32(v as i32)
    }

    fn serialize_i16(self, v: i16) -> Result<()> {
        self.serialize_i32(v as i32)
    }

    fn serialize_i32(self, v: i32) -> Result<()> {
        self.serialize_u32(v as u32)
    }

    fn serialize_i64(self, v: i64) -> Result<()> {
        self.serialize_u64(v as u64)
    }

    fn serialize_i128(self, v: i128) -> Result<()> {
        self.serialize_u128(v as u128)
    }

    fn serialize_u8(self, v: u8) -> Result<()> {
        self.serialize_u32(v as u32)
    }

    fn serialize_u16(self, v: u16) -> Result<()> {
        self.serialize_u32(v as u32)
    }

    fn serialize_u32(self, v: u32) -> Result<()> {
        self.stream.write_words(&[v])
    }

    fn serialize_u64(self, v: u64) -> Result<()> {
        self.serialize_u32((v & 0xFFFFFFFF) as u32)?;
        self.serialize_u32(((v >> 32) & 0xFFFFFFFF) as u32)
    }

    fn serialize_u128(self, v: u128) -> Result<()> {
        self.stream.write_padded_bytes(&v.to_le_bytes())
    }

    fn serialize_f32(self, v: f32) -> Result<()> {
        self.serialize_u32(v.to_bits())
    }

    fn serialize_f64(self, v: f64) -> Result<()> {
        self.serialize_u64(f64::to_bits(v))
    }

    fn serialize_char(self, v: char) -> Result<()> {
        self.serialize_u32(v as u32)
    }

    fn serialize_str(self, v: &str) -> Result<()> {
        let bytes = v.as_bytes();
        self.serialize_u32(bytes.len() as u32)?;
        self.stream.write_padded_bytes(bytes)
    }

    // NOTE: Serializing byte slices _does not_ currently call serialize_bytes. This
    // is because the default collect_seq implementation handles all [T] with
    // `collect_seq` which does not differentiate. Two options for enabling more
    // efficient serialization (or commit) of bytes values and
    // bytes-interpretable slices (e.g. [u32]) are:
    // A) Implement collect_seq and check at runtime whether a type could be
    //    serialized as bytes.
    // B) Use the experimental Rust specialization
    //    features.
    fn serialize_bytes(self, v: &[u8]) -> Result<()> {
        self.serialize_u32(v.len() as u32)?;
        self.stream.write_padded_bytes(v)
    }

    fn serialize_none(self) -> Result<()> {
        self.serialize_u32(0)
    }

    fn serialize_some<T>(self, value: &T) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        self.serialize_u32(1)?;
        value.serialize(self)
    }

    fn serialize_unit(self) -> Result<()> {
        Ok(())
    }

    fn serialize_unit_struct(self, _name: &'static str) -> Result<()> {
        Ok(())
    }

    fn serialize_unit_variant(
        self,
        _name: &'static str,
        variant_index: u32,
        _variant: &'static str,
    ) -> Result<()> {
        self.serialize_u32(variant_index)
    }

    fn serialize_newtype_struct<T>(self, _name: &'static str, value: &T) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        value.serialize(self)
    }

    fn serialize_newtype_variant<T>(
        self,
        _name: &'static str,
        variant_index: u32,
        _variant: &'static str,
        value: &T,
    ) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        self.serialize_u32(variant_index)?;
        value.serialize(self)
    }

    fn serialize_seq(self, len: Option<usize>) -> Result<Self::SerializeSeq> {
        match len {
            Some(val) => {
                self.serialize_u32(val.try_into().unwrap())?;
                Ok(self)
            }
            None => Err(Error::NotSupported),
        }
    }

    fn serialize_tuple(self, _len: usize) -> Result<Self::SerializeTuple> {
        Ok(self)
    }

    fn serialize_tuple_struct(
        self,
        _name: &'static str,
        _len: usize,
    ) -> Result<Self::SerializeTupleStruct> {
        Ok(self)
    }

    fn serialize_tuple_variant(
        self,
        _name: &'static str,
        variant_index: u32,
        _variant: &'static str,
        _len: usize,
    ) -> Result<Self::SerializeTupleVariant> {
        self.serialize_u32(variant_index)?;
        Ok(self)
    }

    fn serialize_map(self, len: Option<usize>) -> Result<Self::SerializeMap> {
        match len {
            Some(val) => {
                self.serialize_u32(val.try_into().unwrap())?;
                Ok(self)
            }
            None => Err(Error::NotSupported),
        }
    }

    fn serialize_struct(self, _name: &'static str, _len: usize) -> Result<Self::SerializeStruct> {
        Ok(self)
    }

    fn serialize_struct_variant(
        self,
        _name: &'static str,
        variant_index: u32,
        _variant: &'static str,
        _len: usize,
    ) -> Result<Self::SerializeStructVariant> {
        self.serialize_u32(variant_index)?;
        Ok(self)
    }
}

impl<W: WordWrite> serde::ser::SerializeSeq for &'_ mut Serializer<W> {
    type Ok = ();
    type Error = Error;

    fn serialize_element<T>(&mut self, value: &T) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        value.serialize(&mut **self)
    }

    fn end(self) -> Result<()> {
        Ok(())
    }
}

impl<W: WordWrite> serde::ser::SerializeTuple for &'_ mut Serializer<W> {
    type Ok = ();
    type Error = Error;

    fn serialize_element<T>(&mut self, value: &T) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        value.serialize(&mut **self)
    }

    fn end(self) -> Result<()> {
        Ok(())
    }
}

impl<W: WordWrite> serde::ser::SerializeTupleStruct for &'_ mut Serializer<W> {
    type Ok = ();
    type Error = Error;

    fn serialize_field<T>(&mut self, value: &T) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        value.serialize(&mut **self)
    }

    fn end(self) -> Result<()> {
        Ok(())
    }
}

impl<W: WordWrite> serde::ser::SerializeTupleVariant for &'_ mut Serializer<W> {
    type Ok = ();
    type Error = Error;

    fn serialize_field<T>(&mut self, value: &T) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        value.serialize(&mut **self)
    }

    fn end(self) -> Result<()> {
        Ok(())
    }
}

impl<W: WordWrite> serde::ser::SerializeMap for &'_ mut Serializer<W> {
    type Ok = ();
    type Error = Error;

    fn serialize_key<T>(&mut self, key: &T) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        key.serialize(&mut **self)
    }

    fn serialize_value<T>(&mut self, value: &T) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        value.serialize(&mut **self)
    }

    fn end(self) -> Result<()> {
        Ok(())
    }
}

impl<W: WordWrite> serde::ser::SerializeStruct for &'_ mut Serializer<W> {
    type Ok = ();
    type Error = Error;

    fn serialize_field<T>(&mut self, _key: &'static str, value: &T) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        value.serialize(&mut **self)
    }

    fn end(self) -> Result<()> {
        Ok(())
    }
}

impl<W: WordWrite> serde::ser::SerializeStructVariant for &'_ mut Serializer<W> {
    type Ok = ();
    type Error = Error;

    fn serialize_field<T>(&mut self, _key: &'static str, value: &T) -> Result<()>
    where
        T: serde::Serialize + ?Sized,
    {
        value.serialize(&mut **self)
    }

    fn end(self) -> Result<()> {
        Ok(())
    }
}

#[cfg(test)]
mod tests {
    use alloc::string::String;

    use serde::Serialize;

    use super::*;

    #[test]
    #[allow(clippy::approx_constant)]
    fn test_struct() {
        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            bool: bool,
            i8: i8,
            u8: u8,
            i16: i16,
            u16: u16,
            i32: i32,
            u32: u32,
            f32: f32,
            i64: i64,
            u64: u64,
            f64: f64,
        }

        let expected = [
            1,
            -4_i32 as u32,
            4,
            -5_i32 as u32,
            5,
            -6_i32 as u32,
            6,
            f32::to_bits(3.14_f32),
            -7_i32 as u32,
            0xffffffff,
            7,
            0x00000000,
            f64::to_bits(2.71).checked_rem(0x100000000).unwrap() as u32,
            f64::to_bits(2.71).checked_shr(32).unwrap() as u32,
        ];

        let input = Test {
            bool: true,
            i8: -4,
            u8: 4,
            i16: -5,
            u16: 5,
            i32: -6,
            u32: 6,
            f32: 3.14,
            i64: -7,
            u64: 7,
            f64: 2.71,
        };
        assert_eq!(expected, to_vec(&input).unwrap().as_slice());
    }

    #[test]
    fn test_str() {
        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            first: String,
            second: String,
        }

        let expected = [1, 0x00000061, 3, 0x00636261];
        let input = Test {
            first: "a".into(),
            second: "abc".into(),
        };
        assert_eq!(expected, to_vec(&input).unwrap().as_slice());
    }
}
