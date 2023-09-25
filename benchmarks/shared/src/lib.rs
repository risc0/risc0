extern crate merkletree;
extern crate sha2;

use merkletree::{hash::Algorithm, merkle::Element};
use serde::{Deserialize, Serialize};
use sha2::{Digest, Sha256};
use std::hash::Hasher;

pub use merkletree::proof::Proof;

#[derive(Serialize, Deserialize, Debug, Default, Clone, Eq, Ord, PartialEq, PartialOrd)]
pub struct Item([u8; 32]);

impl AsRef<[u8]> for Item {
    fn as_ref(&self) -> &[u8] {
        &self.0
    }
}

impl Element for Item {
    fn byte_len() -> usize {
        32
    }

    fn from_slice(bytes: &[u8]) -> Self {
        assert_eq!(bytes.len(), 32, "Slice size should be 32 for Item");
        let mut item = Item([0u8; 32]);
        item.0.copy_from_slice(bytes);
        item
    }

    fn copy_to_slice(&self, bytes: &mut [u8]) {
        bytes.copy_from_slice(&self.0);
    }
}

pub fn generate_vector_of_elements<E: Element>(leaves: usize) -> Vec<E> {
    let result = (0..leaves).map(|index| {
        let vector: Vec<u8> = (0..E::byte_len()).map(|x| (index + x) as u8).collect();
        E::from_slice(vector.as_slice())
    });
    result.collect()
}

pub struct Sha256Hasher(Sha256);

impl Default for Sha256Hasher {
    fn default() -> Self {
        Sha256Hasher(Sha256::new())
    }
}

impl Hasher for Sha256Hasher {
    fn finish(&self) -> u64 {
        unimplemented!()
    }

    fn write(&mut self, bytes: &[u8]) {
        self.0.update(bytes);
    }
}

impl Algorithm<Item> for Sha256Hasher {
    fn hash(&mut self) -> Item {
        let result = self.0.clone().finalize();
        let mut array = [0u8; 32];
        array.copy_from_slice(&result[..]);
        Item(array)
    }
}

#[cfg(test)]
mod tests {
    use merkletree::{merkle::MerkleTree, store::VecStore};

    use super::*;

    #[test]
    fn basic_merkletree_test() {
        let data = generate_vector_of_elements::<Item>(2);
        let tree = MerkleTree::<Item, Sha256Hasher, VecStore<Item>>::new(data).unwrap();
        let proof = tree.gen_proof(0).unwrap();
        assert!(proof.validate::<Sha256Hasher>().unwrap());
    }
}
