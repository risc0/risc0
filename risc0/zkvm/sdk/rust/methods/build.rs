use risc0_build::{embed_methods_with_options, GuestOptions};
use std::{collections::HashMap, env};

fn main() {
    if env::var("CARGO_CFG_TARGET_OS").unwrap().contains("zkvm") {
        // Guest shouldn't recursively depend on itself.
        return;
    }

    let inner_pkg_options = GuestOptions {
        code_limit: 10,
        features: vec!["test_feature1".to_string(), "test_feature2".to_string()],
    };

    let map = HashMap::from([("risc0-zkvm-methods-inner", inner_pkg_options)]);

    embed_methods_with_options(map);
}
