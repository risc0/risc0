{% unless risc0_std -%}
#![no_main]
#![no_std]
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
