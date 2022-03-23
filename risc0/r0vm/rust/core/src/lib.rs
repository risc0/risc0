#![no_std]

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
