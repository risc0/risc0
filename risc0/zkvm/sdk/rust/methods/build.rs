use std::collections::HashMap;
use risc0_zkvm::build::{
    EmbedMethodsOptions,
    embed_methods_with_options
};

fn main() {

    let options = EmbedMethodsOptions{
       code_limit: 10,
        method_features: HashMap::from([(
            "risc0-zkvm-methods-inner".to_string(),
            vec!["test_feature1".to_string(), "test_feature2".to_string()],
        )])
    };

    risc0_zkvm::build::embed_methods_with_options(options);
}
