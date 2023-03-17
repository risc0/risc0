// TODO: Rename this file to change the name of this method from METHOD_NAME

#![no_main]
// If you want to try std support, also update the guest Cargo.toml file
#![no_std]  // std support is experimental

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // TODO: Implement your guest code here
}
