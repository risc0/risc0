use risc0_zkvm::build::{embed_methods_with_options, MethodOptions};
use std::collections::HashMap;

fn main() {
    let inner_method_options = MethodOptions {
        code_limit: 10,
        features: vec!["test_feature1".to_string(), "test_feature2".to_string()],
    };

    let map = HashMap::from([("risc0-zkvm-methods-inner", inner_method_options)]);

    embed_methods_with_options(map);
}
