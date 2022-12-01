// Copyright 2022 RISC Zero, Inc.
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
use core::mem::MaybeUninit;

use impl_trait_for_tuples::impl_for_tuples;

use super::{align_bytes_to_words, as_words_padded, pad_words, Result, ZeroioError};

pub struct Alloc<'a> {
    buf_left: MaybeUninit<&'a mut [u32]>,
    base: usize,
}

pub struct AllocBuf<'a> {
    buf: &'a mut [u32],
    base: usize,
}

impl<'a> Alloc<'a> {
    pub fn alloc(&mut self, words: usize) -> Result<AllocBuf<'a>> {
        // Juggle around the slice contianing remaining allocation buffer, since
        // the borrow checker doesn't understand that we're returning part of the
        // buffer back to self.buf_left when we're done.
        let mut tmp: MaybeUninit<&'a mut [u32]> = MaybeUninit::uninit();
        core::mem::swap(&mut self.buf_left, &mut tmp);
        let buf_left = unsafe { tmp.assume_init() };

        if buf_left.len() < words {
            return Err(ZeroioError::AllocationSizeMismatch);
        }
        let (new_buf, rest) = buf_left.split_at_mut(words);
        self.buf_left.write(rest);
        let old_base = self.base;
        self.base += words;
        Ok(AllocBuf {
            buf: new_buf,
            base: old_base,
        })
    }
}

impl<'a> AllocBuf<'a> {
    pub fn descend(&mut self, offset: usize, len: usize) -> Result<AllocBuf> {
        if offset + len > self.buf.len() {
            return Err(ZeroioError::FillOverrun);
        }
        Ok(AllocBuf {
            buf: &mut self.buf[offset..offset + len],
            base: self.base + offset,
        })
    }

    pub fn fill_from<const N: usize>(&mut self, val: [u32; N]) -> Result<()> {
        if self.buf.len() != N {
            return Err(ZeroioError::FillOverrun);
        }

        self.buf.clone_from_slice(&val[..]);
        Ok(())
    }

    pub fn buf(&mut self, len: usize) -> Result<&mut [u32]> {
        if self.buf.len() != len {
            return Err(ZeroioError::FillOverrun);
        }
        Ok(&mut self.buf)
    }

    pub fn rel_ptr_from(&self, other: &AllocBuf) -> u32 {
        (self.base - other.base) as u32
    }
}

pub fn serialize<T>(val: &T) -> Result<Vec<u32>>
where
    T: Serialize,
{
    let tot_len = val.tot_len();
    let padded = pad_words(tot_len);
    let mut buf: Vec<u32> = Vec::new();
    buf.resize(padded, 0);

    let (mut alloc_buf, _) = buf.as_mut_slice().split_at_mut(tot_len);

    log::trace!(
        "Starting to serialize type {:?} with {} words and {} fixed words",
        core::any::type_name::<T>(),
        tot_len,
        T::FIXED_WORDS
    );

    let mut alloc = Alloc {
        buf_left: MaybeUninit::new(&mut alloc_buf),
        base: 0,
    };

    let mut fixed = alloc.alloc(T::FIXED_WORDS)?;
    val.fill(&mut fixed, &mut alloc)?;

    Ok(buf)
}

pub trait Serialize {
    const FIXED_WORDS: usize;

    fn tot_len(&self) -> usize;

    fn fill(&self, buf: &mut AllocBuf, a: &mut Alloc) -> Result<()>;
}

impl Serialize for u32 {
    const FIXED_WORDS: usize = 1;

    fn tot_len(&self) -> usize {
        1
    }

    fn fill(&self, buf: &mut AllocBuf, _a: &mut Alloc) -> Result<()> {
        buf.fill_from([*self])?;
        Ok(())
    }
}

impl Serialize for alloc::string::String {
    const FIXED_WORDS: usize = 2;

    fn tot_len(&self) -> usize {
        Self::FIXED_WORDS + align_bytes_to_words(self.len())
    }

    fn fill(&self, buf: &mut AllocBuf, a: &mut Alloc) -> Result<()> {
        let words = align_bytes_to_words(self.len());
        let str_data = a.alloc(words)?;

        for (w, val) in core::iter::zip(
            str_data.buf.iter_mut(),
            as_words_padded(self.as_bytes().into_iter().cloned()),
        ) {
            *w = val;
        }

        buf.fill_from([self.len() as u32, str_data.rel_ptr_from(buf)])?;
        Ok(())
    }
}

impl Serialize for Vec<u8> {
    const FIXED_WORDS: usize = 2;

    fn tot_len(&self) -> usize {
        Self::FIXED_WORDS + align_bytes_to_words(self.len())
    }

    fn fill(&self, buf: &mut AllocBuf, a: &mut Alloc) -> Result<()> {
        let words = align_bytes_to_words(self.len());
        let str_data = a.alloc(words)?;

        for (w, val) in core::iter::zip(
            str_data.buf.iter_mut(),
            as_words_padded(self.iter().cloned()),
        ) {
            *w = val;
        }

        buf.fill_from([self.len() as u32, str_data.rel_ptr_from(buf)])?;
        Ok(())
    }
}

impl<T: Serialize> Serialize for core::option::Option<T> {
    const FIXED_WORDS: usize = 1;

    fn tot_len(&self) -> usize {
        match self {
            None => 1,
            Some(val) => 1 + val.tot_len(),
        }
    }

    fn fill(&self, buf: &mut AllocBuf, a: &mut Alloc) -> Result<()> {
        match self {
            None => {
                buf.fill_from([0])?;
                Ok(())
            }
            Some(val) => {
                let mut sub_buf = a.alloc(T::FIXED_WORDS)?;
                val.fill(&mut sub_buf, a)?;
                buf.fill_from([sub_buf.rel_ptr_from(buf)])?;
                Ok(())
            }
        }
    }
}

impl<T: Serialize> Serialize for alloc::boxed::Box<T> {
    const FIXED_WORDS: usize = T::FIXED_WORDS;

    fn tot_len(&self) -> usize {
        self.as_ref().tot_len()
    }

    fn fill(&self, buf: &mut AllocBuf, a: &mut Alloc) -> Result<()> {
        self.as_ref().fill(buf, a)
    }
}

impl<T: Serialize> Serialize for alloc::vec::Vec<T> {
    const FIXED_WORDS: usize = 2;

    fn tot_len(&self) -> usize {
        self.iter().map(|x| x.tot_len()).sum::<usize>() + Self::FIXED_WORDS
    }

    fn fill(&self, buf: &mut AllocBuf, a: &mut Alloc) -> Result<()> {
        let mut sub_buf = a.alloc(T::FIXED_WORDS * self.len())?;
        let mut pos = 0;
        for val in self {
            val.fill(&mut sub_buf.descend(pos, T::FIXED_WORDS)?, a)?;
            pos += T::FIXED_WORDS;
        }
        buf.fill_from([self.len() as u32, sub_buf.rel_ptr_from(buf)])?;
        Ok(())
    }
}

impl<T: Serialize, const N: usize> Serialize for [T; N] {
    const FIXED_WORDS: usize = T::FIXED_WORDS * N;

    fn tot_len(&self) -> usize {
        self.iter().map(|x| x.tot_len()).sum()
    }

    fn fill(&self, buf: &mut AllocBuf, a: &mut Alloc) -> Result<()> {
        let mut pos = 0;
        for val in self {
            val.fill(&mut buf.descend(pos, T::FIXED_WORDS)?, a)?;
            pos += T::FIXED_WORDS;
        }
        Ok(())
    }
}

#[impl_for_tuples(1, 5)]
impl Serialize for Tuple {
    for_tuples!(const FIXED_WORDS: usize = #(Tuple::FIXED_WORDS)+*; );

    fn tot_len(&self) -> usize {
        for_tuples!(#(Tuple.tot_len())+*)
    }

    fn fill(&self, buf: &mut AllocBuf, a: &mut Alloc) -> Result<()> {
        let mut pos = 0;
        for_tuples!(
            #(
                let fixed = Tuple::FIXED_WORDS;
                Tuple.fill(&mut buf.descend(pos, fixed)?, a)?;
                pos += fixed;
            )*);
        Ok(())
    }
}

impl Serialize for () {
    const FIXED_WORDS: usize = 0;

    fn tot_len(&self) -> usize {
        0
    }

    fn fill(&self, _buf: &mut AllocBuf, _a: &mut Alloc) -> Result<()> {
        Ok(())
    }
}
