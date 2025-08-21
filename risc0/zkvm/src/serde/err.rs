// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use alloc::string::{String, ToString};
use core::fmt::{Display, Formatter};

/// Errors used by Serde
#[derive(Clone, Debug, Eq, PartialEq)]
pub enum Error {
    /// A custom error
    Custom(String),
    /// Found a bool that wasn't 0 or 1
    DeserializeBadBool,
    /// Found an invalid unicode char
    DeserializeBadChar,
    /// Found an Option discriminant that wasn't 0 or 1
    DeserializeBadOption,
    /// Tried to parse invalid utf-8
    DeserializeBadUtf8,
    /// Unexpected end during deserialization
    DeserializeUnexpectedEnd,
    /// Not supported
    NotSupported,
    /// The serialize buffer is full
    SerializeBufferFull,
}

/// A Result type for `risc0_zkvm::serde` operations that can fail
pub type Result<T> = core::result::Result<T, Error>;

impl Display for Error {
    fn fmt(&self, formatter: &mut Formatter) -> core::fmt::Result {
        formatter.write_str(match self {
            Self::Custom(msg) => msg,
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
    fn custom<T: Display>(msg: T) -> Self {
        Error::Custom(msg.to_string())
    }
}

impl serde::de::Error for Error {
    fn custom<T: Display>(msg: T) -> Self {
        Error::Custom(msg.to_string())
    }
}

// This is an alias for either std::Error, or serde's no_std error replacement.
impl serde::ser::StdError for Error {}
