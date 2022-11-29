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

use alloc::{boxed::Box, vec::Vec};
use core::marker::PhantomData;

use impl_trait_for_tuples::impl_for_tuples;

pub trait Deserialize<'a> {
    type RefType;

    const FIXED_WORDS: usize;

    fn deserialize_from(words: &'a [u32]) -> Self::RefType;

    fn from_ref(val: &Self::RefType) -> Self;
}

pub trait DeserializeOwned: for<'a> Deserialize<'a> {}
impl<T> DeserializeOwned for T where T: for<'a> Deserialize<'a> {}

impl<'a> Deserialize<'a> for u32 {
    type RefType = u32;

    const FIXED_WORDS: usize = 1;

    fn deserialize_from(words: &[u32]) -> Self::RefType {
        words[0]
    }

    fn from_ref(val: &Self::RefType) -> Self {
        *val
    }
}

impl<'a> Deserialize<'a> for alloc::string::String {
    type RefType = &'a str;

    const FIXED_WORDS: usize = 2;

    fn deserialize_from(words: &'a [u32]) -> Self::RefType {
        let (len, ptr) = (words[0], words[1]);

        core::str::from_utf8(&bytemuck::cast_slice(&words[ptr as usize..])[..len as usize]).unwrap()
    }

    fn from_ref(val: &Self::RefType) -> Self {
        (*val).into()
    }
}

impl<'a> Deserialize<'a> for Vec<u8> {
    type RefType = &'a [u8];

    const FIXED_WORDS: usize = 2;

    fn deserialize_from(words: &'a [u32]) -> Self::RefType {
        let (len, ptr) = (words[0], words[1]);

        &bytemuck::cast_slice(&words[ptr as usize..])[..len as usize]
    }

    fn from_ref(val: &Self::RefType) -> Self {
        (*val).into()
    }
}

impl<'a, T: Deserialize<'a>> Deserialize<'a> for Option<T> {
    type RefType = Option<T::RefType>;

    const FIXED_WORDS: usize = 1;

    fn deserialize_from(words: &'a [u32]) -> Self::RefType {
        let ptr = words[0];

        if ptr == 0 {
            None
        } else {
            Some(T::deserialize_from(&words[ptr as usize..]))
        }
    }

    fn from_ref(val: &Self::RefType) -> Self {
        val.as_ref().map(|v| T::from_ref(&v))
    }
}

impl<'a, T: Deserialize<'a>> Deserialize<'a> for Box<T> {
    type RefType = T::RefType;

    const FIXED_WORDS: usize = T::FIXED_WORDS;

    fn deserialize_from(words: &'a [u32]) -> T::RefType {
        T::deserialize_from(words)
    }

    fn from_ref(val: &Self::RefType) -> Self {
        Box::new(T::from_ref(&val))
    }
}

pub struct VecRef<'a, T> {
    len: usize,
    words: &'a [u32],
    phantom: PhantomData<T>,
}

impl<'a, T: Deserialize<'a>> VecRef<'a, T> {
    pub fn len(&self) -> usize {
        self.len
    }

    pub fn index(&self, index: usize) -> T::RefType {
        T::deserialize_from(&self.words[T::FIXED_WORDS * index..])
    }

    pub fn as_u32s(&self) -> &'a [u32] {
        &self.words[..T::FIXED_WORDS * self.len]
    }
}

pub struct VecRefIter<'a, T> {
    words: &'a [u32],
    items_left: usize,
    phantom: PhantomData<T>,
}

impl<'a, T: Deserialize<'a>> VecRef<'a, T> {
    pub fn iter(&self) -> VecRefIter<'a, T> {
        VecRefIter {
            words: self.words,
            items_left: self.len,
            phantom: PhantomData,
        }
    }
}

impl<'a, T: Deserialize<'a>> IntoIterator for VecRef<'a, T> {
    type Item = T::RefType;
    type IntoIter = VecRefIter<'a, T>;

    fn into_iter(self) -> Self::IntoIter {
        self.iter()
    }
}

impl<'a, T: Deserialize<'a>> Iterator for VecRefIter<'a, T> {
    type Item = T::RefType;
    fn next(&mut self) -> Option<T::RefType> {
        if self.items_left > 0 {
            let val = T::deserialize_from(self.words);
            self.items_left -= 1;
            self.words = &self.words[T::FIXED_WORDS..];
            Some(val)
        } else {
            None
        }
    }
}

impl<'a, T: Deserialize<'a>> Deserialize<'a> for Vec<T> {
    type RefType = VecRef<'a, T>;

    const FIXED_WORDS: usize = 2;

    fn deserialize_from(words: &'a [u32]) -> Self::RefType {
        VecRef {
            len: words[0] as usize,
            words: &words[words[1] as usize..],
            phantom: PhantomData,
        }
    }

    fn from_ref(val: &Self::RefType) -> Self {
        let mut v = Vec::with_capacity(val.len());
        v.extend(val.iter().map(|v| T::from_ref(&v)));
        v
    }
}

impl<'a, T: Deserialize<'a>, const N: usize> Deserialize<'a> for [T; N] {
    type RefType = VecRef<'a, T>;

    const FIXED_WORDS: usize = N * T::FIXED_WORDS;

    fn deserialize_from(words: &'a [u32]) -> Self::RefType {
        VecRef {
            len: N,
            words,
            phantom: PhantomData,
        }
    }

    fn from_ref(val: &Self::RefType) -> Self {
        match Vec::from_iter(val.iter().map(|x| T::from_ref(&x))).try_into() {
            Ok(result) => result,
            _ => panic!("VecRef iterator didn't return the proper number of elements"),
        }
    }
}

#[impl_for_tuples(1, 5)]
impl<'a> Deserialize<'a> for Tuple {
    for_tuples!(type RefType = (#(Tuple::RefType),*););
    for_tuples!(const FIXED_WORDS: usize = #(Tuple::FIXED_WORDS)+*; );

    fn deserialize_from(words: &'a [u32]) -> Self::RefType {
        let mut pos = 0;
        let mut inc_pos = |n| {
            let old_pos = pos;
            pos += n;
            old_pos
        };
        for_tuples!(
            (#(
                Tuple::deserialize_from(&words[inc_pos(Tuple::FIXED_WORDS)..])
            ),*));
    }

    fn from_ref(val: &Self::RefType) -> Self {
        for_tuples!(
            (#(
                Tuple::from_ref(&val.Tuple)
            ),*));
    }
}

impl<'a> Deserialize<'a> for () {
    type RefType = ();
    const FIXED_WORDS: usize = 0;

    fn deserialize_from(_words: &'a [u32]) -> Self::RefType {
        ()
    }

    fn from_ref(_val: &Self::RefType) -> Self {
        ()
    }
}
