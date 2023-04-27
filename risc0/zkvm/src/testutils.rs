use core::mem;

use num_bigint::BigUint;
use num_traits::{One, Zero};
use rand::{
    distributions::{Distribution, Standard, Uniform},
    Rng,
};
use risc0_zkvm_platform::syscall::bigint;

#[derive(Debug)]
pub struct BigIntTestCase {
    pub x: [u32; bigint::WIDTH_WORDS],
    pub y: [u32; bigint::WIDTH_WORDS],
    pub modulus: [u32; bigint::WIDTH_WORDS],
}

// NOTE: Testing here could be significantly improved by creating a less uniform
// test case generator. It is likely more important to test inputs of different
// byte-lengths, with zero and 0xff bytes, and other boundary values than
// testing values in the middle.
impl Distribution<BigIntTestCase> for Standard {
    fn sample<R: Rng + ?Sized>(&self, rng: &mut R) -> BigIntTestCase {
        let bigint_max = BigUint::one() << bigint::WIDTH_BITS;

        let modulus = Uniform::new(&BigUint::one(), &bigint_max).sample(rng);
        let mut x = Uniform::new(&BigUint::zero(), &bigint_max).sample(rng);
        let mut y = Uniform::new(&BigUint::zero(), &modulus).sample(rng);

        // x and y come from slightly different ranges because at least one input must
        // be less than the modulus, but it doesn't matter which one. Randomly swap.
        if rng.gen::<bool>() {
            mem::swap(&mut x, &mut y);
        }

        BigIntTestCase {
            x: x.to_u32_digits().try_into().unwrap(),
            y: y.to_u32_digits().try_into().unwrap(),
            modulus: modulus.to_u32_digits().try_into().unwrap(),
        }
    }
}

impl BigIntTestCase {
    pub fn expected(&self) -> [u32; bigint::WIDTH_WORDS] {
        let modulus = BigUint::from_slice(&self.modulus);
        let z = if modulus.is_zero() {
            BigUint::from_slice(&self.x) * BigUint::from_slice(&self.y)
        } else {
            (BigUint::from_slice(&self.x) * BigUint::from_slice(&self.y)) % modulus
        };
        let mut vec = z.to_u32_digits();
        if vec.len() > bigint::WIDTH_WORDS {
            panic!("modular multiplication result larger than input modulus");
        }
        vec.resize(bigint::WIDTH_WORDS, 0);
        vec.try_into().unwrap()
    }
}

/// Generate the test cases for the BigInt accelerator circuit that are applied
/// to both the simulator and circuit implementations.
pub fn generate_bigint_test_cases(rng: &mut impl Rng, rand_count: usize) -> Vec<BigIntTestCase> {
    let zero = [0, 0, 0, 0, 0, 0, 0, 0];
    let one = [1, 0, 0, 0, 0, 0, 0, 0];

    let mut cases = vec![
        BigIntTestCase {
            x: [1, 2, 3, 4, 5, 6, 7, 8],
            y: [9, 10, 11, 12, 13, 14, 15, 16],
            modulus: [17, 18, 19, 20, 21, 22, 23, 24],
        },
        BigIntTestCase {
            x: [1, 2, 3, 4, 5, 6, 7, 8],
            y: zero,
            modulus: [17, 18, 19, 20, 21, 22, 23, 24],
        },
        BigIntTestCase {
            x: [1, 2, 3, 4, 5, 6, 7, 8],
            y: one,
            modulus: [17, 18, 19, 20, 21, 22, 23, 24],
        },
        BigIntTestCase {
            x: one,
            y: [9, 10, 11, 12, 13, 14, 15, 16],
            modulus: [1, 2, 3, 4, 5, 6, 7, 8],
        },
        BigIntTestCase {
            x: [1, 2, 3, 4, 0, 0, 0, 0],
            y: [9, 10, 11, 12, 0, 0, 0, 0],
            modulus: zero,
        },
    ];

    cases.extend(Standard.sample_iter(rng).take(rand_count));
    cases
}
