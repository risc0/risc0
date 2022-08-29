use risc0_build::{embed_methods_with_options, GuestOptions};
use std::{collections::HashMap, env};

fn main() {
    if env::var("CARGO_CFG_TARGET_OS").unwrap().contains("zkvm") {
        // Guest shouldn't recursively depend on itself.
        return;
    }

    let options = GuestOptions {
        code_limit: 10,
        features: vec![],
        std: false,
    };
    let map = HashMap::from([("risc0-zkvm-methods-verify-inner", options)]);
    embed_methods_with_options(map);
}
