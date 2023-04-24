#![no_main]
{% unless risc0_std -%}
// If you want to try std support, also update the guest Cargo.toml file
#![no_std]  // std support is experimental
{% endunless %}

use risc0_zkvm::guest::env;

risc0_zkvm::guest::entry!(main);

pub fn main() {
    // TODO: Implement your guest code here
}
