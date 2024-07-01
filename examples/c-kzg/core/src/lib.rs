use serde::{Deserialize, Serialize};

#[derive(Deserialize, Serialize)]
pub struct Proof {
    pub commitment: Vec<u8>,
    pub z: Vec<u8>,
    pub y: Vec<u8>,
    pub proof: Vec<u8>,
}
