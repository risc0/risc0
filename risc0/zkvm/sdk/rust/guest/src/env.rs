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

use core::{cell::RefMut, mem::MaybeUninit, slice};

use serde::{Deserialize, Serialize};

use crate::{
    gpio::{IoDescriptor, GPIO_COMMIT, GPIO_DESC_IO, GPIO_WRITE},
    mem_layout::{COMMIT_ZONE, OUTPUT_ZONE, REGION_INPUT_LEN, REGION_INPUT_START},
    mutex::Mutex,
    sha, WORD_SIZE,
};
use risc0_zkvm_core::DIGEST_WORDS;
use risc0_zkvm_serde::{Deserializer, Serializer};

struct Env {
    input: Deserializer<'static>,
}

static ENV: Mutex<MaybeUninit<Env>> = Mutex::new(MaybeUninit::uninit());

fn get_env<'a>() -> RefMut<'a, Env> {
    let borrowed: RefMut<'_, MaybeUninit<Env>> = ENV.lock().unwrap();
    RefMut::map(borrowed, |x| unsafe { x.assume_init_mut() })
}

pub(crate) fn init() {
    ENV.lock().unwrap().write(Env::new());
}

pub(crate) fn finalize(result: *mut usize) {
    get_env().finalize(result);
}

pub fn read<T: Deserialize<'static>>() -> T {
    get_env().read()
}

pub fn write<T: Serialize>(data: &T) {
    get_env().write(data);
}

pub fn commit<T: Serialize>(data: &T) {
    get_env().commit(data);
}

impl Env {
    fn new() -> Self {
        Env {
            input: Deserializer::new(unsafe {
                slice::from_raw_parts(REGION_INPUT_START as _, REGION_INPUT_LEN / WORD_SIZE)
            }),
        }
    }

    fn read<T: Deserialize<'static>>(&mut self) -> T {
        T::deserialize(&mut self.input).unwrap()
    }

    fn write<T: Serialize>(&mut self, data: &T) {
        let mut output = Serializer::new(OUTPUT_ZONE.as_buf());
        data.serialize(&mut output).unwrap();

        // Also write a copy to GPIO.
        let written = output.release().unwrap();
        GPIO_DESC_IO.write_volatile(IoDescriptor {
            size: written.len() * WORD_SIZE,
            addr: written.as_ptr() as usize,
        });
        GPIO_WRITE.write_volatile(GPIO_DESC_IO.ptr());
    }

    fn commit<T: Serialize>(&mut self, data: &T) {
        let mut output = Serializer::new(COMMIT_ZONE.as_buf());
        data.serialize(&mut output).unwrap();

        // Also write a copy to GPIO.
        let written = output.release().unwrap();
        GPIO_DESC_IO.write_volatile(IoDescriptor {
            size: written.len() * WORD_SIZE,
            addr: written.as_ptr() as usize,
        });
        GPIO_WRITE.write_volatile(GPIO_DESC_IO.ptr());
    }

    fn finalize(&mut self, result: *mut usize) {
        let len_words = COMMIT_ZONE.len();
        let len_bytes = len_words * WORD_SIZE;
        let slice = COMMIT_ZONE.as_slice();

        // Write the full data out to the host
        GPIO_DESC_IO.write_volatile(IoDescriptor {
            size: len_bytes,
            addr: slice.as_ptr() as usize,
        });
        GPIO_COMMIT.write_volatile(GPIO_DESC_IO.ptr());

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
            let mut buf = COMMIT_ZONE.as_buf();
            sha::add_wom_trailer(&mut buf, len_words * WORD_SIZE);
            unsafe {
                sha::raw_digest_to(COMMIT_ZONE.as_slice(), result as *mut [u32; DIGEST_WORDS])
            };
        }
        unsafe { result.add(DIGEST_WORDS).write_volatile(len_bytes) };
        sha::finalize();
    }
}
