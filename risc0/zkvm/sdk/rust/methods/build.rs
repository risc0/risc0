use risc0_zkvm::build::{embed_methods_with_options, GuestOptions};
use std::collections::HashMap;

fn main() {
    let inner_pkg_options = GuestOptions {
        code_limit: 10,
        features: vec!["test_feature1".to_string(), "test_feature2".to_string()],
    };

    let map = HashMap::from([("risc0-zkvm-methods-inner", inner_pkg_options)]);

    embed_methods_with_options(map);
}
