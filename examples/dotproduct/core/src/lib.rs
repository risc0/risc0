use serde::{Deserialize, Serialize};

#[derive(Clone, Debug, Deserialize, Eq, PartialEq, Serialize)]
pub struct Args {
    pub left: Vec<u64>,
    pub right: Vec<u64>,
}

impl Args {
    pub fn dotproduct(&self) -> u64 {
        self.left
            .iter()
            .zip(&self.right)
            .map(|(a, b)| a.checked_mul(*b).unwrap())
            .sum()
    }
}
