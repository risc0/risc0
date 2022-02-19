#![no_main]
#![no_std]
#![allow(non_snake_case)]

use risc0::env;

risc0::entry!(main);

pub fn main() {
    let count: usize = env::read();
    for _ in 0..count {
        let addr: *mut usize = env::read();
        let value: usize = env::read();
        if value != 0 {
            unsafe { addr.write_volatile(value) };
        } else {
            let value = unsafe { addr.read_volatile() };
            env::write(&value);
        }
    }
}
