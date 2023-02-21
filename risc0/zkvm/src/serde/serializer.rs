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

use alloc::vec::Vec;
use core::mem;

use bytemuck::Pod;
use risc0_zkvm_platform::WORD_SIZE;
use serde::Serialize;

use super::{
    align_up,
    err::{Error, Result},
};

pub fn to_vec<'a, T>(value: &'a T) -> Result<Vec<u32>>
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

pub fn to_vec_with_capacity<'a, T>(value: &'a T, cap: usize) -> Result<Vec<u32>>
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

    fn write_u32(&mut self, data: u32) -> Result<()>;

    fn write_u64(&mut self, data: u64) -> Result<()> {
        self.write_u32((data & 0xffffffff) as u32)?;
        self.write_u32((data >> 32) as u32)
    }

    fn write_slice<T: Pod>(&mut self, slice: &[T]) -> Result<()>;

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

    fn write_bytes(&mut self, bytes: &[u8]) -> Result<()> {
        static ZEROS: [u8; WORD_SIZE] = [0, 0, 0, 0];
        self.stream.write_slice(bytes)?;
        let padding = align_up(bytes.len(), WORD_SIZE) - bytes.len();
        self.stream.write_slice(&ZEROS[..padding])
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
        self.stream.write_u32(v as u32)
    }

    fn serialize_i64(self, v: i64) -> Result<()> {
        self.stream.write_u64(v as u64)
    }

    fn serialize_u8(self, v: u8) -> Result<()> {
        self.serialize_u32(v as u32)
    }

    fn serialize_u16(self, v: u16) -> Result<()> {
        self.serialize_u32(v as u32)
    }

    fn serialize_u32(self, v: u32) -> Result<()> {
        self.stream.write_u32(v)
    }

    fn serialize_u64(self, v: u64) -> Result<()> {
        self.stream.write_u64(v)
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
        self.stream.write_u32(v.len() as u32)?;
        self.write_bytes(v.as_bytes())?;
        Ok(())
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
        self.stream.write_u32(v.len() as u32)?;
        self.write_bytes(v)
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
        self.stream.write_u32(variant_index)
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
        self.stream.write_u32(variant_index)?;
        value.serialize(self)
    }

    fn serialize_seq(self, len: Option<usize>) -> Result<Self::SerializeSeq> {
        match len {
            Some(val) => {
                self.stream.write_u32(val.try_into().unwrap())?;
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
        self.stream.write_u32(variant_index)?;
        Ok(self)
    }

    fn serialize_map(self, len: Option<usize>) -> Result<Self::SerializeMap> {
        match len {
            Some(val) => {
                self.stream.write_u32(val.try_into().unwrap())?;
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
        self.stream.write_u32(variant_index)?;
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

pub struct AllocVec(pub Vec<u8>);

impl AllocVec {
    pub fn new() -> Self {
        AllocVec(Vec::new())
    }

    pub fn with_capacity(capacity: usize) -> Self {
        AllocVec(Vec::with_capacity(capacity))
    }
}

impl StreamWriter for AllocVec {
    type Output = Vec<u32>;

    fn write_u32(&mut self, data: u32) -> Result<()> {
        self.write_slice(data.to_ne_bytes().as_slice())
    }

    fn write_slice<T: Pod>(&mut self, slice: &[T]) -> Result<()> {
        self.0.extend_from_slice(bytemuck::cast_slice(slice));
        Ok(())
    }

    fn release(&mut self) -> Result<Self::Output> {
        let mut out = Vec::new();
        out.extend_from_slice(bytemuck::cast_slice(self.0.as_slice()));
        Ok(out)
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
