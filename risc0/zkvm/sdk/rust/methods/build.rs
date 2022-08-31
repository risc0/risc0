use std::{collections::HashMap, env};

use risc0_build::{embed_methods_with_options, GuestOptions};

fn main() {
    if env::var("CARGO_CFG_TARGET_OS").unwrap().contains("zkvm") {
        // Guest shouldn't recursively depend on itself.
        return;
    }

    let map = HashMap::from([
        (
            "risc0-zkvm-methods-inner",
            GuestOptions {
                code_limit: 10,
                features: vec!["test_feature1".to_string(), "test_feature2".to_string()],
                std: true,
            },
        ),
        (
            "risc0-zkvm-methods-verify",
            GuestOptions {
                code_limit: 10,
                features: vec![],
                std: false,
            },
        ),
    ]);

    embed_methods_with_options(map);
}
