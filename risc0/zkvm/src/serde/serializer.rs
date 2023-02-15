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

use bytemuck::PodCastError;
use risc0_zkvm_platform::WORD_SIZE;
use serde::Serialize;

use super::{
    align_up,
    err::{Error, Result},
};
use crate::sha::{self, Block, Sha256, BLOCK_BYTES, BLOCK_WORDS, SHA256_INIT};

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
    // of the serialized value. Allocates a word for every byte in the
    // mem::size_of_val, so the allocated Vec 4x the memory representation size.
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

// TODO(victor): Reconsider making stream public.
pub struct Serializer<W: StreamWriter> {
    pub stream: W,
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
        unimplemented!("collect_str")
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

    // NOTE: Serializing byte slices _does not_ currently call serialize_bytes. This
    // is because the default collect_seq implementation handles all [T] with
    // `collect_seq` which does not differentiate. Two options for enabling more
    // efficient serialization (or commit) of bytes values and
    // bytes-interpretable slices (e.g. [u32]) are:
    //   A) Implement collect_seq and check at runtime whether a type could be
    // serialized as bytes.
    //   B) Use the experimental Rust specialization
    // features.
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

#[derive(Default, Debug)]
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

#[derive(Default, Debug)]
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
        // Interpret the bytes as native-endian u32 values and push them into the
        // serialization buffer. If not aligned, this is less efficient.
        let (chunks, remainder) = data.as_chunks::<WORD_SIZE>();
        match bytemuck::try_cast_slice::<_, u32>(chunks) {
            Ok(words) => self.0.extend_from_slice(words),
            Err(PodCastError::TargetAlignmentGreaterAndInputNotAligned) => {
                self.0.extend(
                    chunks
                        .iter()
                        .map(|chunk| bytemuck::pod_read_unaligned::<u32>(chunk)),
                );
            }
            Err(e) => unreachable!("failed to cast &[[u8; 4]] to &[u32]: {}", e),
        };

        // Pad the remainder with zeros when the data is not a whole number of words.
        if remainder.len() > 0 {
            let mut word = [0; WORD_SIZE];
            word[..remainder.len()].copy_from_slice(remainder);
            self.0.push(u32::from_ne_bytes(word));
        }
        Ok(())
    }

    fn release(&mut self) -> Result<Self::Output> {
        Ok(mem::take(&mut self.0))
    }
}

/// An implementation of Committer provides a way to "commit" the given data. It
/// abstracts the sys_commit functionality, which sends the data from the guest
/// to the host by way of passing a pointer to an ecall. In testing, it may be
/// implemented using a write buffer.
pub trait Committer {
    fn commit(&mut self, data: &[u32]);

    /// Reset the internal state of this committer such that it can be used to
    /// commit a new stream of data. Implementaion is optional and the default
    /// implementation is a no-op.
    fn reset(&mut self) {}
}

#[derive(Default, Debug)]
pub struct NoopCommitter {}

impl Committer for NoopCommitter {
    fn commit(&mut self, _data: &[u32]) {}
}

/// CommitHasher is a serialization target that supported incremental hashing of
/// the data as it's being serialized. It uses only a fixed width buffer and
/// avoids copying the source data when possible.
pub struct CommitHasher<S: Sha256 = sha::Impl, C: Committer = NoopCommitter> {
    state: Option<S::DigestPtr>,
    buffer: Block,
    buffer_pos: usize,
    block_len: usize,
    committer: C,
}

impl<S: Sha256, C: Committer> CommitHasher<S, C> {
    fn new(committer: C) -> Self {
        Self {
            state: None,
            buffer: Block::default(),
            buffer_pos: 0,
            block_len: 0,
            committer: committer,
        }
    }

    /// Compress the buffer into the hasher state. Must only be called when the
    /// buffer is full. Resets the buffer position to zero.
    #[inline]
    fn compress(&mut self) {
        assert_eq!(self.buffer_pos, BLOCK_WORDS);

        // Send the full data via the committer before compressing the buffer.
        self.committer.commit(self.buffer.as_words());

        // Compress the buffer and reset the buffer position.
        self.state = Some(S::compress(
            self.state.as_deref().unwrap_or(&SHA256_INIT),
            self.buffer.as_half_blocks().0,
            self.buffer.as_half_blocks().1,
        ));
        self.buffer_pos = 0;
        self.block_len += 1;
    }

    /// Compress a slice of blocks into the hasher state without copying. Must
    /// only be called when the buffer is empty. Does not alter the buffer
    /// or buffer position.
    #[inline]
    fn compress_slice(&mut self, blocks: &[Block]) {
        assert_eq!(self.buffer_pos, 0);

        // Send the full data via the committer before compressing the buffer.
        self.committer.commit(bytemuck::cast_slice(blocks));

        // Compress the provided blocks into the hasher state.
        self.state = Some(S::compress_slice(
            self.state.as_deref().unwrap_or(&SHA256_INIT),
            blocks,
        ));
        self.block_len += blocks.len();
    }

    /// Finalizes the hasher, adding the standard SHA-256 padding and trailer
    /// then compressing and returning the finalized hasher state.
    ///
    /// DANGER: At the end of this method, the hasher is left in a dirty state.
    #[inline]
    fn finalize_internal(&mut self) -> S::DigestPtr {
        // Send the remaining data to the committer before writing the trailers.
        if self.buffer_pos != 0 {
            self.committer
                .commit(&self.buffer.as_words()[..self.buffer_pos]);
        }

        // Establish the final count of the number of bits in the stream. Using a u32,
        // the maximum message length is 500 MB.
        let bit_len =
            u32::try_from((self.block_len * BLOCK_WORDS + self.buffer_pos) * WORD_SIZE * 8)
                .unwrap();

        // Write the SHA-256 trailer including end marker, padding, and length.
        // If the buffer is nearly full, a compression may be required.
        // NOTE: BLOCK_WORDS is equal to 16. Named consts are not valid in match
        // expressions, so this block uses the the values as literals.
        match self.buffer_pos {
            0..=13 => {
                self.buffer.as_mut_words()[self.buffer_pos] = 0x80000000_u32.to_be();
                self.buffer.as_mut_words()[self.buffer_pos + 1..BLOCK_WORDS - 1].fill(0);
                self.buffer.as_mut_words()[BLOCK_WORDS - 1] = bit_len.to_be();
            }
            14..=15 => {
                self.buffer.as_mut_words()[self.buffer_pos] = 0x80000000_u32.to_be();
                self.buffer.as_mut_words()[self.buffer_pos + 1..BLOCK_WORDS].fill(0);
                self.state = Some(S::compress(
                    self.state.as_deref().unwrap_or(&SHA256_INIT),
                    self.buffer.as_half_blocks().0,
                    self.buffer.as_half_blocks().1,
                ));
                self.buffer.as_mut_words()[..BLOCK_WORDS - 1].fill(0);
                self.buffer.as_mut_words()[BLOCK_WORDS - 1] = bit_len.to_be();
            }
            16 => {
                self.state = Some(S::compress(
                    self.state.as_deref().unwrap_or(&SHA256_INIT),
                    self.buffer.as_half_blocks().0,
                    self.buffer.as_half_blocks().1,
                ));
                self.buffer.as_mut_words()[0] = 0x80000000_u32.to_be();
                self.buffer.as_mut_words()[1..(BLOCK_WORDS - 1)].fill(0);
                self.buffer.as_mut_words()[BLOCK_WORDS - 1] = bit_len.to_be();
            }
            _ => unreachable!("buffer_pos never exceeds BLOCK_WORDS"),
        };

        // Final compress.
        S::compress(
            self.state.as_deref().unwrap_or(&SHA256_INIT),
            self.buffer.as_half_blocks().0,
            self.buffer.as_half_blocks().1,
        )
    }

    /// Finalizes the hasher, adding the standard SHA-256 padding and trailer
    /// then compressing and returning the finalized hasher state. This method
    /// consumes the hasher.
    pub fn finalize(mut self) -> S::DigestPtr {
        self.finalize_internal()
    }
}

impl<S: Sha256, C: Committer> CommitHasher<S, C> {
    pub fn reset(&mut self) {
        // NOTE: The buffer does need to be replaced.
        self.state = None;
        self.buffer_pos = 0;
        self.block_len = 0;
        self.committer.reset();
    }

    /// Finalizes the hasher, adding the standard SHA-256 padding and trailer
    /// then compressing and returning the finalized hasher state. This method
    /// consumes the hasher.
    pub fn finalize_reset(&mut self) -> S::DigestPtr {
        let digest = self.finalize_internal();
        self.reset();
        digest
    }
}

impl<S: Sha256, C: Committer + Default> Default for CommitHasher<S, C> {
    fn default() -> Self {
        Self::new(C::default())
    }
}

impl<S: Sha256, C: Committer> StreamWriter for CommitHasher<S, C> {
    type Output = S::DigestPtr;

    fn try_push_word(&mut self, data: u32) -> Result<()> {
        if self.buffer_pos == BLOCK_WORDS {
            self.compress();
        }
        assert!(self.buffer_pos < BLOCK_WORDS);

        self.buffer.as_mut_words()[self.buffer_pos] = data;
        self.buffer_pos += 1;
        Ok(())
    }

    fn try_extend(&mut self, data: &[u8]) -> Result<()> {
        // Divide the data into the head, middle, and tail where middle is the set of
        // whole blocks that can be processed without copying into the buffer.
        // If the buffer is partially full at the start, it must be filled and
        // compressed before processing the remainder.
        let remainder: &[u8] = match (
            self.buffer_pos == 0,
            data.len() < BLOCK_BYTES - (self.buffer_pos * WORD_SIZE),
        ) {
            (_, true) => {
                // When the data does not fill the buffer, just copy it into the buffer.
                self.buffer.as_mut_bytes()[self.buffer_pos * WORD_SIZE..][..data.len()]
                    .copy_from_slice(data);
                self.buffer_pos += align_up(data.len(), WORD_SIZE) / WORD_SIZE;
                return Ok(());
            }
            (false, false) => {
                // When the buffer is non-empty, and we can fill it, split off a head large
                // enough to fill the buffer, copy it in and compress then
                // return the remainder.
                let (head, remainder) = data.split_at(BLOCK_BYTES - (self.buffer_pos * WORD_SIZE));
                self.buffer.as_mut_bytes()[self.buffer_pos * WORD_SIZE..].copy_from_slice(head);
                self.buffer_pos = BLOCK_WORDS;
                self.compress();
                remainder
            }
            (true, false) => {
                // When there is at least one block and the buffer is empty, head is empty.
                data
            }
        };
        assert_eq!(self.buffer_pos, 0);

        // Compress the whole blocks into the hasher state, without copying if data is
        // aligned.
        let (middle, tail) = remainder.as_chunks::<BLOCK_BYTES>();
        match bytemuck::try_cast_slice::<_, Block>(middle) {
            Ok(blocks) => self.compress_slice(blocks),
            Err(PodCastError::TargetAlignmentGreaterAndInputNotAligned) => {
                self.compress_slice(
                    &middle
                        .iter()
                        .map(|chunk| bytemuck::pod_read_unaligned(chunk))
                        .collect::<alloc::vec::Vec<_>>(),
                );
            }
            Err(e) => unreachable!("failed to cast &[[u8; BLOCK_BYTES]] to &[Block]: {}", e),
        };

        // Write the remaining data, which is less than a block, into the buffer.
        let tail_bytes = tail.len();
        let tail_words = align_up(tail_bytes, WORD_SIZE) / WORD_SIZE;
        assert!(tail_words <= BLOCK_WORDS);

        self.buffer.as_mut_bytes()[..tail_bytes].copy_from_slice(tail);
        self.buffer_pos += tail_words;

        Ok(())
    }

    fn release(&mut self) -> Result<Self::Output> {
        Ok(self.finalize_reset())
    }
}

#[cfg(test)]
mod tests {
    use alloc::string::String;
    use std::cell::RefCell;
    use std::rc::Rc;

    use serde::Serialize;

    use super::*;

    // Includes test cases for all the types in the serde data model.
    // https://docs.rs/serde/latest/serde/trait.Serializer.html

    #[derive(Debug)]
    pub struct DebugCommitter {
        buffer: std::rc::Rc<RefCell<Vec<u32>>>,
    }

    impl DebugCommitter {
        fn new(buffer: Rc<RefCell<Vec<u32>>>) -> Self {
            Self { buffer }
        }
    }

    impl Committer for DebugCommitter {
        fn commit(&mut self, data: &[u32]) {
            std::println!("commit: {:?}", data);
            self.buffer.borrow_mut().extend_from_slice(data);
        }
    }

    fn test_commit<T>(value: &T) -> (<sha::Impl as Sha256>::DigestPtr, Vec<u32>)
    where
        T: Serialize + ?Sized,
    {
        let commit_buffer = Rc::new(RefCell::new(Vec::<u32>::new()));
        let mut hasher = Serializer::new(CommitHasher::<sha::Impl, _>::new(DebugCommitter::new(
            commit_buffer.clone(),
        )));
        value.serialize(&mut hasher).unwrap();
        let digest = hasher.stream.finalize();
        let committed_data: Vec<u32> = commit_buffer.take();
        (digest, committed_data)
    }

    #[test]
    fn test_primitives() {
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
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_str() {
        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            first: String,
            second: String,
            third: String,
        }

        let expected = [1, 0x00000061, 3, 0x00636261, 5, 0x64636261, 0x00000065];
        let input = Test {
            first: "a".into(),
            second: "abc".into(),
            third: "abcde".into(),
        };

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_bytes() {
        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            first: &'static [u8],
            second: &'static [u8],
            third: &'static [u8],
        }

        let expected = [
            1, 0x61, 3, 0x61, 0x62, 0x63, 5, 0x61, 0x62, 0x63, 0x64, 0x65,
        ];
        let input = Test {
            first: "a".as_bytes(),
            second: "abc".as_bytes(),
            third: "abcde".as_bytes(),
        };

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_option() {
        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            some: Option<u32>,
            none: Option<u32>,
        }

        let expected = [1, 7, 0];
        let input = Test {
            some: Some(7),
            none: None,
        };

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_unit() {
        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            unit: (),
        }

        let expected: [u32; 0] = [];
        let input = Test { unit: () };

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_unit_variant() {
        #[derive(Serialize, PartialEq, Debug)]
        enum TestEnum {
            A,
            B,
            C,
        }

        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            a: TestEnum,
            b: TestEnum,
            c: TestEnum,
        }

        let expected = [0, 1, 2];
        let input = Test {
            a: TestEnum::A,
            b: TestEnum::B,
            c: TestEnum::C,
        };

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_newtype_struct() {
        #[derive(Serialize, PartialEq, Debug)]
        struct Test(u32);

        let expected = [7];
        let input = Test(7);

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_newtype_variant() {
        #[derive(Serialize, PartialEq, Debug)]
        enum TestEnum {
            A(u32),
            B(u64),
            C,
        }

        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            a: TestEnum,
            b: TestEnum,
            c: TestEnum,
        }

        let expected = [0, 7, 1, 83, 0, 2];
        let input = Test {
            a: TestEnum::A(7),
            b: TestEnum::B(83),
            c: TestEnum::C,
        };

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_seq() {
        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            first: Vec<u32>,
            second: Vec<u32>,
            third: Vec<u32>,
        }

        let expected = [4, 86, 52, 19, 28, 3, 52, 28, 93, 0];
        let input = Test {
            first: vec![86, 52, 19, 28],
            second: vec![52, 28, 93],
            third: vec![],
        };

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_tuple() {
        let expected = [7, 17, 45];
        let input = (7, 17, 45);

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_tuple_struct() {
        #[derive(Serialize, PartialEq, Debug)]
        struct Test(u32, u32, u32);

        let expected = [7, 17, 45];
        let input = Test(7, 17, 45);

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_tuple_variant() {
        #[derive(Serialize, PartialEq, Debug)]
        enum TestEnum {
            A(u32, u32),
            B(u64, u64),
            C,
        }

        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            a: TestEnum,
            b: TestEnum,
            c: TestEnum,
        }

        let expected = [0, 7, 53, 1, 83, 0, 28, 0, 2];
        let input = Test {
            a: TestEnum::A(7, 53),
            b: TestEnum::B(83, 28),
            c: TestEnum::C,
        };

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_map() {
        use std::collections::BTreeMap as Map;

        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            first: Map<String, u32>,
            second: Map<u32, String>,
            third: Map<u32, u32>,
        }

        let expected = [
            3, 1, 0x61, 17, 1, 0x62, 53, 1, 0x63, 84, 1, 26, 3, 0x636261, 0,
        ];
        let input = Test {
            first: Map::from([
                ("a".to_string(), 17),
                ("b".to_string(), 53),
                ("c".to_string(), 84),
            ]),
            second: Map::from([(26, "abc".to_string())]),
            third: Map::from([]),
        };

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    #[test]
    fn test_struct_variant() {
        #[derive(Serialize, PartialEq, Debug)]
        enum TestEnum {
            A { a: u32, b: u32 },
            B { a: u64, b: u64 },
            C,
        }

        #[derive(Serialize, PartialEq, Debug)]
        struct Test {
            a: TestEnum,
            b: TestEnum,
            c: TestEnum,
        }

        let expected = [0, 7, 53, 1, 83, 0, 28, 0, 2];
        let input = Test {
            a: TestEnum::A { a: 7, b: 53 },
            b: TestEnum::B { a: 83, b: 28 },
            c: TestEnum::C,
        };

        let buf: &mut [u32] = &mut [0; 256];
        assert_eq!(expected, to_slice(&input, buf).unwrap());
        assert_eq!(expected.as_slice(), &to_vec(&input).unwrap());
        assert_eq!(
            (
                sha::Impl::hash_words(expected.as_slice()),
                expected.as_slice().to_vec()
            ),
            test_commit(&input)
        );
    }

    // TODO(victor): Add some tests to excersize more of the code paths in
    // CommitHasher.
}
