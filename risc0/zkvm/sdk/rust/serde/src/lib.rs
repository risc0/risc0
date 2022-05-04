#![cfg_attr(not(feature = "std"), no_std)]

extern crate alloc;

mod deserializer;
mod err;
mod serializer;

pub use deserializer::{from_slice, Deserializer};
pub use err::Result;
pub use serializer::{
    to_slice, to_vec, to_vec_with_capacity, AllocVec, Serializer, Slice, StreamWriter,
};

/// Align the given address `addr` upwards to alignment `align`.
///
/// Requires that `align` is a power of two.
fn align_up(addr: usize, align: usize) -> usize {
    (addr + align - 1) & !(align - 1)
}
