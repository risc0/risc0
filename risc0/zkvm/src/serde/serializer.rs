// Copyright 2023 RISC Zero, Inc.
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

use core::mem;

use risc0_zkvm_platform::WORD_SIZE;
use serde::Serialize;

use super::{
    align_up,
    err::{Error, Result},
};

pub fn to_slice<'a, 'b, T>(value: &'b T, buf: &'a mut [u32]) -> Result<&'a [u32]>
where
    T: Serialize + ?Sized,
{
    let mut serializer = Serializer::new(Slice::new(buf));
    value.serialize(&mut serializer)?;
    serializer.stream.release()
}

pub fn to_vec<'a, T>(value: &'a T) -> Result<alloc::vec::Vec<u32>>
where
    T: Serialize + ?Sized,
{
    // Use the in-memory size of the value as a guess for the length
    // of the serialized value.
    let vec = AllocVec::with_capacity(mem::size_of_val(value));
    let mut serializer = Serializer::new(vec);
    value.serialize(&mut serializer)?;
    serializer.stream.release()
}

pub fn to_vec_with_capacity<'a, T>(value: &'a T, cap: usize) -> Result<alloc::vec::Vec<u32>>
where
    T: Serialize + ?Sized,
{
    let vec = AllocVec::with_capacity(cap);
    let mut serializer = Serializer::new(vec);
    value.serialize(&mut serializer)?;
    serializer.stream.release()
}

pub trait StreamWriter {
    type Output;

    fn try_push_word(&mut self, data: u32) -> Result<()>;

    fn try_push_dword(&mut self, data: u64) -> Result<()> {
        self.try_push_word((data & 0xffffffff) as u32)?;
        self.try_push_word((data >> 32) as u32)
    }

    fn try_extend(&mut self, data: &[u8]) -> Result<()>;

    fn release(&mut self) -> Result<Self::Output>;
}

pub struct Serializer<W: StreamWriter> {
    stream: W,
}

impl<W: StreamWriter> Serializer<W> {
    pub fn new(stream: W) -> Self {
        Serializer { stream }
    }

    pub fn release(&mut self) -> Result<W::Output> {
        self.stream.release()
    }
}

impl<'a, W: StreamWriter> serde::ser::Serializer for &'a mut Serializer<W> {
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

    fn collect_str<T>(self, _: &T) -> Result<()>
    where
        T: core::fmt::Display + ?Sized,
    {
        panic!("collect_str")
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
        self.stream.try_push_word(v as u32)
    }

    fn serialize_i64(self, v: i64) -> Result<()> {
        self.stream.try_push_dword(v as u64)
    }

    fn serialize_u8(self, v: u8) -> Result<()> {
        self.serialize_u32(v as u32)
    }

    fn serialize_u16(self, v: u16) -> Result<()> {
        self.serialize_u32(v as u32)
    }

    fn serialize_u32(self, v: u32) -> Result<()> {
        self.stream.try_push_word(v)
    }

    fn serialize_u64(self, v: u64) -> Result<()> {
        self.stream.try_push_dword(v)
    }

    fn serialize_f32(self, _v: f32) -> Result<()> {
        Err(Error::NotSupported)
    }

    fn serialize_f64(self, _v: f64) -> Result<()> {
        Err(Error::NotSupported)
    }

    fn serialize_char(self, v: char) -> Result<()> {
        let mut buf = [0u8; WORD_SIZE];
        let str = v.encode_utf8(&mut buf);
        str.serialize(self)
    }

    fn serialize_str(self, v: &str) -> Result<()> {
        self.stream.try_push_word(v.len() as u32)?;
        self.stream.try_extend(v.as_bytes())?;
        Ok(())
    }

    fn serialize_bytes(self, v: &[u8]) -> Result<()> {
        self.stream.try_push_word(v.len() as u32)?;
        self.stream.try_extend(v)
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
        self.stream.try_push_word(variant_index)
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
        self.stream.try_push_word(variant_index)?;
        value.serialize(self)
    }

    fn serialize_seq(self, len: Option<usize>) -> Result<Self::SerializeSeq> {
        match len {
            Some(val) => {
                self.stream.try_push_word(val.try_into().unwrap())?;
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
        self.stream.try_push_word(variant_index)?;
        Ok(self)
    }

    fn serialize_map(self, len: Option<usize>) -> Result<Self::SerializeMap> {
        match len {
            Some(val) => {
                self.stream.try_push_word(val.try_into().unwrap())?;
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
        self.stream.try_push_word(variant_index)?;
        Ok(self)
    }
}

impl<'a, W: StreamWriter> serde::ser::SerializeSeq for &'a mut Serializer<W> {
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

impl<'a, W: StreamWriter> serde::ser::SerializeTuple for &'a mut Serializer<W> {
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

impl<'a, W: StreamWriter> serde::ser::SerializeTupleStruct for &'a mut Serializer<W> {
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

impl<'a, W: StreamWriter> serde::ser::SerializeTupleVariant for &'a mut Serializer<W> {
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

impl<'a, W: StreamWriter> serde::ser::SerializeMap for &'a mut Serializer<W> {
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

impl<'a, W: StreamWriter> serde::ser::SerializeStruct for &'a mut Serializer<W> {
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

impl<'a, W: StreamWriter> serde::ser::SerializeStructVariant for &'a mut Serializer<W> {
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

pub struct Slice<'a> {
    slice: &'a mut [u32],
    idx: usize,
}

impl<'a> StreamWriter for Slice<'a> {
    type Output = &'a [u32];

    fn try_push_word(&mut self, data: u32) -> Result<()> {
        if self.idx >= self.slice.len() {
            return Err(Error::SerializeBufferFull);
        }

        self.slice[self.idx] = data;
        self.idx += 1;

        Ok(())
    }

    fn try_extend(&mut self, data: &[u8]) -> Result<()> {
        let len_bytes = data.len();
        let len_words = align_up(len_bytes, WORD_SIZE) / WORD_SIZE;

        if (len_words + self.idx) > self.slice.len() {
            return Err(Error::SerializeBufferFull);
        }

        let slice = &mut self.slice[self.idx..self.idx + len_words];
        let bytes: &mut [u8] = bytemuck::cast_slice_mut(slice);
        bytes[..len_bytes].copy_from_slice(data);

        self.idx += len_words;

        Ok(())
    }

    fn release(&mut self) -> Result<Self::Output> {
        // Remove the slice we're modifying out of self.slice so we
        // don't run into problems trying to replace it while it's
        // borrowed.
        let tmp: &mut [u32] = mem::replace(&mut self.slice, &mut []);
        let (head, tail) = tmp.split_at_mut(self.idx);
        self.slice = tail;
        self.idx = 0;
        Ok(head)
    }
}

impl<'a> Slice<'a> {
    pub fn new(slice: &'a mut [u32]) -> Self {
        Slice { slice, idx: 0 }
    }
}

pub struct AllocVec(pub alloc::vec::Vec<u32>);

impl AllocVec {
    pub fn new() -> Self {
        AllocVec(alloc::vec::Vec::new())
    }

    pub fn with_capacity(capacity: usize) -> Self {
        AllocVec(alloc::vec::Vec::with_capacity(capacity))
    }
}

impl StreamWriter for AllocVec {
    type Output = alloc::vec::Vec<u32>;

    fn try_push_word(&mut self, data: u32) -> Result<()> {
        self.0.push(data);
        Ok(())
    }

    fn try_extend(&mut self, data: &[u8]) -> Result<()> {
        let mut chunks = data.chunks_exact(WORD_SIZE);
        for chunk in &mut chunks {
            let word = chunk[0] as u32
                | (chunk[1] as u32) << 8
                | (chunk[2] as u32) << 16
                | (chunk[3] as u32) << 24;
            self.0.push(word);
        }
        let remainder = chunks.remainder();
        if remainder.len() > 0 {
            let mut word = 0;
            for i in 0..remainder.len() {
                word |= (remainder[i] as u32) << (8 * i);
            }
            self.0.push(word);
        }
        Ok(())
    }

    fn release(&mut self) -> Result<Self::Output> {
        let ret = self.0.clone();
        self.0 = alloc::vec::Vec::new();
        Ok(ret)
    }
}

#[cfg(test)]
mod tests {
    use alloc::string::String;

    use serde::Serialize;

    use super::*;

    #[test]
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
            i64: i64,
            u64: u64,
        }

        let expected = [
            1,
            -4_i32 as u32,
            4,
            -5_i32 as u32,
            5,
            -6_i32 as u32,
            6,
            -7_i32 as u32,
            0xffffffff,
            7,
            0x00000000,
        ];

        let input = Test {
            bool: true,
            i8: -4,
            u8: 4,
            i16: -5,
            u16: 5,
            i32: -6,
            u32: 6,
            i64: -7,
            u64: 7,
        };
        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
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
        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
    }
}
