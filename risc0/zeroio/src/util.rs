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

/// Converts bytes to words, adding null padding at the end.
use super::WORD_SIZE;

pub struct AsWordsPadded<I>
where
    I: Iterator<Item = u8>,
{
    iter: I,
}

impl<I> Iterator for AsWordsPadded<I>
where
    I: Iterator<Item = u8>,
{
    type Item = u32;

    fn next(&mut self) -> Option<u32> {
        let mut word_bytes: [u8; WORD_SIZE] = [0; WORD_SIZE];
        for i in 0..WORD_SIZE {
            match self.iter.next() {
                Some(val) => {
                    word_bytes[i] = val;
                }
                None => {
                    if i == 0 {
                        return None;
                    }
                }
            }
        }
        Some(u32::from_le_bytes(word_bytes))
    }
}

/// Converts an iterator supplying u8s to an iterator supplying u32s,
/// padding the last u32 with 0s as necessary.
pub fn as_words_padded<I: IntoIterator<Item = u8>>(
    iter: I,
) -> AsWordsPadded<core::iter::Fuse<I::IntoIter>> {
    AsWordsPadded {
        iter: iter.into_iter().fuse(),
    }
}

#[test]
pub fn test_pads() {
    use alloc::vec::Vec;

    let mut a: Vec<u32> = as_words_padded([]).collect();
    assert_eq!(a, Vec::<u32>::new());

    a = as_words_padded([1]).collect();
    assert_eq!(a, vec![1]);

    a = as_words_padded([1, 3]).collect();
    assert_eq!(a, vec![1 + 3 * 256]);

    a = as_words_padded([1, 3, 5]).collect();
    assert_eq!(a, vec![1 + 3 * 256 + 5 * 256 * 256]);

    a = as_words_padded([1, 3, 5, 7]).collect();
    assert_eq!(a, vec![1 + 3 * 256 + 5 * 256 * 256 + 7 * 256 * 256 * 256]);

    a = as_words_padded([1, 3, 5, 7, 9]).collect();
    assert_eq!(
        a,
        vec![1 + 3 * 256 + 5 * 256 * 256 + 7 * 256 * 256 * 256, 9]
    );
}
