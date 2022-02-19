#![no_main]
#![no_std]
#![allow(non_snake_case)]

risc0::entry!(main);

pub fn main() {
    panic!("Failure");
}
