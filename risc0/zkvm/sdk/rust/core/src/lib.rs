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

#![cfg_attr(not(feature = "std"), no_std)]

#[cfg(feature = "pure")]
pub use risc0_zkp_core::sha::{Digest, DIGEST_WORDS};

cfg_if::cfg_if! {
    if #[cfg(not(feature = "pure"))] {
        use core::fmt::{Debug, Display, Formatter};

        use serde::{Deserialize, Serialize};

        pub const DIGEST_WORDS: usize = 8;

        #[derive(Clone, Copy, Default, Deserialize, Eq, Hash, Ord, PartialOrd, PartialEq, Serialize)]
        pub struct Digest([u32; DIGEST_WORDS]);

        impl Digest {
            /// Constructs a new `Digest` from a byte array.
            pub fn new(data: [u32; DIGEST_WORDS]) -> Self {
                Self(data)
            }

            pub fn as_slice(&self) -> &[u32] {
                &self.0
            }
        }

        impl Display for Digest {
            fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
                for word in self.0 {
                    core::write!(f, "{:08x?}", word)?;
                }
                Ok(())
            }
        }

        impl Debug for Digest {
            fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
                for word in self.0 {
                    core::write!(f, "{:08x?}", word)?;
                }
                Ok(())
            }
        }
    }
}

pub trait Log {
    fn log(&self, msg: &str);
}

static mut LOGGER: &dyn Log = &NopLogger;

struct NopLogger;

impl Log for NopLogger {
    fn log(&self, _msg: &str) {}
}

pub fn set_logger(logger: &'static dyn Log) {
    unsafe { LOGGER = logger };
}

pub fn logger() -> &'static dyn Log {
    unsafe { LOGGER }
}

pub fn log(msg: &str) {
    logger().log(msg);
}
