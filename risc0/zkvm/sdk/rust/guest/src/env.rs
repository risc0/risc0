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

use core::{cell::UnsafeCell, mem::MaybeUninit, slice};

use serde::{Deserialize, Serialize};

use crate::{
    gpio::{IoDescriptor, GPIO_COMMIT, GPIO_DESC_IO, GPIO_WRITE},
    sha::{self, digest_commit_into},
    REGION_COMMIT_LEN, REGION_COMMIT_START, REGION_INPUT_LEN, REGION_INPUT_START,
    REGION_OUTPUT_LEN, REGION_OUTPUT_START, WORD_SIZE,
};
use zkvm_serde::{Deserializer, Serializer, Slice};

struct Env {
    input: Deserializer<'static>,
    output: Serializer<Slice<'static>>,
    commit: Serializer<Slice<'static>>,
    commit_len: usize,
}

struct Once<T> {
    data: UnsafeCell<MaybeUninit<T>>,
}

unsafe impl<T: Send + Sync> Sync for Once<T> {}

impl<T> Once<T> {
    const fn new() -> Self {
        Once {
            data: UnsafeCell::new(MaybeUninit::uninit()),
        }
    }

    fn init(&self, value: T) {
        unsafe { &mut *(self.data.get()) }.write(value);
    }

    fn get(&self) -> &mut T {
        unsafe {
            self.data
                .get()
                .as_mut()
                .unwrap_unchecked()
                .assume_init_mut()
        }
    }
}

static ENV: Once<Env> = Once::new();

pub(crate) fn init() {
    ENV.init(Env::new());
}

pub(crate) fn finalize(result: *mut usize) {
    ENV.get().finalize(result);
}

pub fn read<T: Deserialize<'static>>() -> T {
    ENV.get().read()
}

pub fn write<T: Serialize>(data: &T) {
    ENV.get().write(data);
}

pub fn commit<T: Serialize>(data: &T) {
    ENV.get().commit(data);
}

impl Env {
    fn new() -> Self {
        Env {
            input: Deserializer::new(unsafe {
                slice::from_raw_parts(REGION_INPUT_START as _, REGION_INPUT_LEN / WORD_SIZE)
            }),
            output: Serializer::new(Slice::new(unsafe {
                slice::from_raw_parts_mut(REGION_OUTPUT_START as _, REGION_OUTPUT_LEN / WORD_SIZE)
            })),
            commit: Serializer::new(Slice::new(unsafe {
                slice::from_raw_parts_mut(REGION_COMMIT_START as _, REGION_COMMIT_LEN / WORD_SIZE)
            })),
            commit_len: 0,
        }
    }

    fn read<T: Deserialize<'static>>(&mut self) -> T {
        T::deserialize(&mut self.input).unwrap()
    }

    fn write<T: Serialize>(&mut self, data: &T) {
        data.serialize(&mut self.output).unwrap();
        let buf = self.output.release().unwrap();
        unsafe {
            GPIO_DESC_IO.write_volatile(IoDescriptor {
                size: buf.len() * WORD_SIZE,
                addr: buf.as_ptr() as usize,
            });
            GPIO_WRITE.write_volatile(GPIO_DESC_IO);
        }
    }

    fn commit<T: Serialize>(&mut self, data: &T) {
        data.serialize(&mut self.commit).unwrap();
        let buf = self.commit.release().unwrap();
        self.commit_len += buf.len();
        let len_bytes = buf.len() * WORD_SIZE;
        unsafe {
            GPIO_DESC_IO.write_volatile(IoDescriptor {
                size: len_bytes,
                addr: buf.as_ptr() as usize,
            });
            GPIO_WRITE.write_volatile(GPIO_DESC_IO);
        }
    }

    fn finalize(&mut self, result: *mut usize) {
        let len_words = self.commit_len;
        let len_bytes = len_words * WORD_SIZE;
        let slice: &mut [u32] = unsafe {
            slice::from_raw_parts_mut(REGION_COMMIT_START as _, REGION_COMMIT_LEN / WORD_SIZE)
        };

        // Write the full data out to the host
        unsafe {
            GPIO_DESC_IO.write_volatile(IoDescriptor {
                size: len_bytes,
                addr: slice.as_ptr() as usize,
            });
            GPIO_COMMIT.write_volatile(GPIO_DESC_IO);
        }

        // If the total proof message is small (<= 32 bytes), return it directly
        // from the proof, otherwise SHA it and return the hash.
        if len_words <= 8 {
            for i in 0..len_words {
                unsafe {
                    result
                        .add(i)
                        .write_volatile(*slice.get_unchecked(i) as usize)
                };
            }
            for i in len_words..8 {
                unsafe { result.add(i).write_volatile(0) };
            }
        } else {
            digest_commit_into(len_bytes, slice, result);
        }
        unsafe { result.add(8).write_volatile(len_bytes) };
        sha::finalize();
    }
}
