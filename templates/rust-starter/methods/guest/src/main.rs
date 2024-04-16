{% unless risc0_std -%}
#![no_main]
// If you want to try std support, also update the guest Cargo.toml file
#![no_std]  // std support is experimental
{% endunless %}

use risc0_zkvm::guest::env;

{% unless risc0_std -%}
risc0_zkvm::guest::entry!(main);
{% endunless %}

fn main() {
    // TODO: Implement your guest code here

    // read the input
    let input: u32 = env::read();

    // TODO: do something with the input

    // write public output to the journal
    env::commit(&input);
}
