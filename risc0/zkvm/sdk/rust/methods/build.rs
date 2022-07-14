use std::collections::HashMap;

fn main() {
    risc0_zkvm::build::embed_methods_with_features(HashMap::from([(
        "risc0-zkvm-methods-inner".to_string(),
        vec!["test_feature1".to_string(), "test_feature2".to_string()],
    )]));
}
