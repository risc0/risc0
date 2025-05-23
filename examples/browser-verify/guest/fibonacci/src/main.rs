use num_bigint::BigUint;
use num_traits::{One, Zero};
use risc0_zkvm::guest::env;

/// fast-doubling fib in O(log n) multiplications
fn fib_pair(n: u32) -> (BigUint, BigUint) {
    if n == 0 {
        (BigUint::zero(), BigUint::one())
    } else {
        let (a, b) = fib_pair(n >> 1);
        // F(2k) = F(k) * (2·F(k+1) – F(k))
        let two_b_minus_a = &b * 2u32 - &a;
        let c = &a * two_b_minus_a;
        // F(2k+1) = F(k)^2 + F(k+1)^2
        let d = &a * &a + &b * &b;
        if n & 1 == 0 {
            (c, d)
        } else {
            (d.clone(), c + d)
        }
    }
}

fn main() {
    let n: u32 = env::read();

    // compute F_n exactly
    let (f_n, _) = fib_pair(n);

    // decimal-serialize and count digits
    let s = f_n.to_str_radix(10);
    let digit_count = s.len() as u32;

    // only commit the digit count
    env::commit(&digit_count);
}
