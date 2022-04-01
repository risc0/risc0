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
