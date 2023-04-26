use risc0_zkvm_platform::syscall::{bigint, sys_bigint};
use num_traits::{Zero, One};
use core::mem::MaybeUninit;

// TODO(victor): Is there a better name for this type?
#[derive(Debug)]
pub struct BigInt([u32; bigint::WIDTH_WORDS]);

const ZERO = BigInt([0, 0, 0, 0, 0, 0, 0, 0]);

const ONE = BigInt([1, 0, 0, 0, 0, 0, 0, 0]);

impl BigInt {
    // TODO(victor): I would like to provide some kind of check to ensure that the inputs x and y
    // are reduced relative to the intended modulus. Unforcunately, the modulus is not known ahead
    // of time.
    pub fn new(arr: [u32; bigint::WIDTH_WORDS]) -> Self {
        Self(arr)
    }

    /// Calculates the modular multiplication self * other (mod modulus).
    #[inline(always)]
    pub mulmod(&self, other: &Self, modulus: &Self) -> Self {
        let mut result = MaybeUninit::uninit();
        unsafe {
            sys_bigint(result.as_mut_ptr(), bigint::OP_MULTIPLY, self.as_ptr(), other.as_ptr(), modulus.as_ptr());
            result.assume_init()
        }
    }

    /// Calculates the modular multiplication self * other (mod modulus) and assigns the result.
    #[inline(always)]
    pub mulmod_assign(&mut self, other: &Self, modulus: &Self) {
        unsafe {
            sys_bigint(self.as_mut_ptr(), bigint::OP_MULTIPLY, self.as_ptr(), other.as_ptr(), modulus.as_ptr());
        }
    }
}
