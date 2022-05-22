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

use core::fmt::{Display, Formatter};

// use alloc::string::{String, ToString};

#[derive(Clone, Debug, Eq, PartialEq)]
pub enum Error {
    // Custom(String),
    DeserializeBadBool,
    DeserializeBadChar,
    DeserializeBadOption,
    DeserializeBadUtf8,
    DeserializeUnexpectedEnd,
    NotSupported,
    SerializeBufferFull,
}

pub type Result<T> = core::result::Result<T, Error>;

impl Display for Error {
    fn fmt(&self, formatter: &mut Formatter) -> core::fmt::Result {
        formatter.write_str(match self {
            // Self::Custom(msg) => msg,
            Self::DeserializeBadBool => "Found a bool that wasn't 0 or 1",
            Self::DeserializeBadChar => "Found an invalid unicode char",
            Self::DeserializeBadOption => "Found an Option discriminant that wasn't 0 or 1",
            Self::DeserializeBadUtf8 => "Tried to parse invalid utf-8",
            Self::DeserializeUnexpectedEnd => "Unexpected end during deserialization",
            Self::NotSupported => "Not supported",
            Self::SerializeBufferFull => "The serialize buffer is full",
        })
    }
}

impl serde::ser::Error for Error {
    fn custom<T: Display>(_msg: T) -> Self {
        // Error::Custom(msg.to_string())
        Error::NotSupported
    }
}

impl serde::de::Error for Error {
    fn custom<T: Display>(_msg: T) -> Self {
        // Error::Custom(msg.to_string())
        Error::NotSupported
    }
}

#[cfg(feature = "std")]
impl std::error::Error for Error {}
