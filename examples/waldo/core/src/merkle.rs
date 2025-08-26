// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use std::{hash::Hasher, marker::PhantomData, ops::Deref};

use merkle_light::{
    hash::{Algorithm, Hashable},
    merkle, proof,
};
use risc0_zkvm::{
    declare_syscall,
    sha::{
        Digest,
        rust_crypto::{Digest as _, Sha256},
    },
};
use serde::{Deserialize, Serialize};

declare_syscall!(
    /// RISC0 syscall for providing oracle access to a vector committed to by the host.
    pub SYS_VECTOR_ORACLE
);

/// Node type used in the Merkle tree. Simply an alias for a SHA-256  digest.
pub type Node = Digest;

/// Merkle tree for use as a vector commitment over elements of the specified
/// type.
///
/// MerkleTree is a wrapper around the `merkle_light::merkle::MerkleTree`,
/// created to integrate with the RISC0 SHA256 coprocessor, functionality to act
/// as a vector oracle for the for the guest, and some convenient functions.
pub struct MerkleTree<Element>
where
    Element: Hashable<ShaHasher>,
{
    tree: merkle::MerkleTree<Node, ShaHasher>,
    elements: Vec<Element>,
}

impl<Element> MerkleTree<Element>
where
    Element: Hashable<ShaHasher>,
{
    pub fn new(elements: Vec<Element>) -> Self {
        Self {
            tree: merkle::MerkleTree::<_, ShaHasher>::from_data(elements.iter()),
            elements,
        }
    }

    pub fn elements(&self) -> &[Element] {
        &self.elements
    }

    pub fn prove(&self, i: usize) -> Proof<Element> {
        self.tree.gen_proof(i).into()
    }
}

#[cfg(not(target_os = "zkvm"))]
impl<Element> MerkleTree<Element>
where
    Element: Hashable<ShaHasher> + Serialize,
{
    pub fn vector_oracle_callback(
        &self,
    ) -> impl Fn(risc0_zkvm::Bytes) -> risc0_zkvm::Result<risc0_zkvm::Bytes> + '_ {
        |data| {
            // TODO: Using bincode here, but it would likely be better on the guest side to
            // use the risc0 serde crate. I should try to use one of
            // those (again).
            let index: usize = bincode::deserialize::<u32>(&data)
                .unwrap()
                .try_into()
                .unwrap();

            let value = &self.elements()[index];
            let proof = self.prove(index);

            assert!(proof.verify(&self.root(), value));
            Ok(bincode::serialize(&(value, proof)).unwrap().into())
        }
    }
}

// Implement Deref so that all the methods on the wrapped type are accessible.
impl<Element> Deref for MerkleTree<Element>
where
    Element: Hashable<ShaHasher>,
{
    type Target = merkle::MerkleTree<Node, ShaHasher>;

    fn deref(&self) -> &Self::Target {
        &self.tree
    }
}

/// Wrapper for the `merkle_light` inclusion proof. Includes an improved API for
/// verifying that a proof supports serialization and references an expected
/// element and position.
#[derive(Debug, Serialize, Deserialize)]
#[serde(from = "(Vec<Node>, Vec<bool>)", into = "(Vec<Node>, Vec<bool>)")]
pub struct Proof<Element>
where
    Element: Hashable<ShaHasher>,
{
    inner: proof::Proof<Node>,
    phantom_elem: PhantomData<Element>,
}

impl<Element> Proof<Element>
where
    Element: Hashable<ShaHasher>,
{
    /// Verify that the proof commits to the inclusion of the given element in a
    /// Merkle tree with the given root.
    pub fn verify(&self, root: &Node, element: &Element) -> bool {
        // Check that the root of the proof matches the provided root.
        match &self.verified_root(element) {
            Some(verified_root) => verified_root == root,
            None => false,
        }
    }

    /// Verify that the proof commits to the element in _some_ Merkle tree and
    /// return the calculated Merkle root.
    pub fn verified_root(&self, element: &Element) -> Option<Node> {
        // Check that the path from the leaf to the root is consistent.
        if !self.inner.validate::<ShaHasher>() {
            return None;
        }

        // Check the element hashes to the leaf in the proof.
        let algorithm = &mut ShaHasher::default();
        element.hash(algorithm);
        let elem_hash = algorithm.hash();

        // Hash the element to get the leaf, and check that it matches.
        algorithm.reset();
        if algorithm.leaf(elem_hash) != self.inner.item() {
            return None;
        }

        Some(self.root())
    }

    /// Compute the vector index of the proven element.
    pub fn index(&self) -> usize {
        self.inner
            .path()
            .iter()
            .rfold(0, |index, bit| (index << 1) + (!*bit as usize))
    }
}

impl<Element> Clone for Proof<Element>
where
    Element: Hashable<ShaHasher>,
{
    fn clone(&self) -> Self {
        Self {
            inner: self.inner.clone(),
            phantom_elem: PhantomData,
        }
    }
}

impl<Element> Deref for Proof<Element>
where
    Element: Hashable<ShaHasher>,
{
    type Target = proof::Proof<Node>;

    fn deref(&self) -> &Self::Target {
        &self.inner
    }
}

impl<Element> From<proof::Proof<Node>> for Proof<Element>
where
    Element: Hashable<ShaHasher>,
{
    fn from(inner: proof::Proof<Node>) -> Self {
        Self {
            inner,
            phantom_elem: PhantomData,
        }
    }
}

// From tuple representation provided to enable serde deserialization.
impl<Element> From<(Vec<Node>, Vec<bool>)> for Proof<Element>
where
    Element: Hashable<ShaHasher>,
{
    fn from(tuple: (Vec<Node>, Vec<bool>)) -> Self {
        proof::Proof::new(tuple.0, tuple.1).into()
    }
}

// Into tuple representation provided to enable serde deserialization.
impl<Element> From<Proof<Element>> for (Vec<Node>, Vec<bool>)
where
    Element: Hashable<ShaHasher>,
{
    fn from(val: Proof<Element>) -> Self {
        (val.inner.lemma().to_vec(), val.inner.path().to_vec())
    }
}

/// ShaHasher is a wrapper around the RISC0 SHA2-256 implementations that
/// implements the Algorithm trait for use with the merkle_light package.
#[derive(Default)]
pub struct ShaHasher(Sha256);

// NOTE: The Hasher trait is really designed for use with hashmaps and is quite
// ill-suited as an interface for use by merkle_light. This is one of the design
// weaknesses of the merkle_light library.
impl Hasher for ShaHasher {
    fn write(&mut self, bytes: &[u8]) {
        self.0.update(bytes);
    }

    fn finish(&self) -> u64 {
        unimplemented!("finish is not implemented for merkletree hashers");
    }
}

impl Algorithm<Node> for ShaHasher {
    fn hash(&mut self) -> Node {
        Node::try_from(self.0.finalize_reset().as_slice()).unwrap()
    }
}

/// VectorOracle is used inside the zkVM guest to access elements of a vector
/// which are held by the host in a committed Merkle tree. On each access, the
/// guest will verify a Merkle proof against the root given when the
/// VectorOracle is created to ensure all accessed values are consistent
/// with a vector with that root.
#[cfg(target_os = "zkvm")]
pub struct VectorOracle<Element>
where
    Element: Hashable<ShaHasher> + Deserialize<'static>,
{
    root: Node,
    phantom_elem: PhantomData<Element>,
}

#[cfg(target_os = "zkvm")]
impl<Element> VectorOracle<Element>
where
    Element: Hashable<ShaHasher> + Deserialize<'static>,
{
    pub fn new(root: Node) -> Self {
        Self {
            root,
            phantom_elem: PhantomData,
        }
    }

    // NOTE: VectorOracle does not attempt to verify the length of the committed
    // vector, or that there is a valid, known element at every index. Any out
    // of bounds access or access to an index for which there is no element will
    // not return since no valid proof can be generated.
    //
    // NOTE: This implementation deserializes proof and element values, which copies
    // them from the address returned by send_recv onto the heap. This is fairly
    // inefficient and could be improved on with an implementation of Merkle
    // proofs that can be verified without deserialization, and by returning
    // references to the underlying element, which points to the
    // memory written by the syscall. Additionally note that this implementation
    // uses bincode instead of any serializer that is more native to (and
    // efficient in) the guest.
    pub fn get(&self, index: usize) -> Element {
        let (value, proof): (Element, Proof<Element>) =
            bincode::deserialize(risc0_zkvm::guest::env::send_recv_slice(
                SYS_VECTOR_ORACLE,
                // Cast the index to u32 since usize is an architecture dependent type.
                &bincode::serialize(&(u32::try_from(index).unwrap())).unwrap(),
            ))
            .unwrap();

        // Verify the proof for the value of the element at the given index in the
        // committed vector.
        assert_eq!(index, proof.index());
        assert!(proof.verify(&self.root, &value));
        value
    }

    pub fn root(&self) -> &Node {
        &self.root
    }
}

#[cfg(test)]
mod test {
    use rand::Rng;
    use sha2::Digest as Sha2Digest;

    use super::*;

    /// Build and return a random Merkle tree with 1028 u32 elements.
    fn random_merkle_tree() -> MerkleTree<u32> {
        let item_count: usize = rand::rng().random_range((1 << 10)..(1 << 12));
        let items: Vec<u32> = (0..item_count).map(|_| rand::rng().random()).collect();
        MerkleTree::<u32>::new(items)
    }

    #[test]
    fn merkle_tree_proving_works() {
        let tree = random_merkle_tree();
        for (index, item) in tree.elements().iter().enumerate() {
            let proof = tree.prove(index);
            assert!(proof.verify(&tree.root(), item));
        }
    }

    #[test]
    fn merkle_proof_serialization_works() {
        let tree = random_merkle_tree();
        for (index, item) in tree.elements().iter().enumerate() {
            let proof = tree.prove(index);

            let proof_bytes = bincode::serialize(&proof).unwrap();
            let proof_deserialized: Proof<u32> = bincode::deserialize(&proof_bytes).unwrap();

            assert!(proof_deserialized.verify(&tree.root(), item));
        }
    }

    #[test]
    fn merkle_proof_index_works() {
        let tree = random_merkle_tree();
        for (index, _item) in tree.elements().iter().enumerate() {
            let proof = tree.prove(index);
            assert_eq!(proof.index(), index);
        }
    }

    #[test]
    fn algorithm_is_consistent_with_sha2() {
        let test_string: &'static [u8] = "RISC0 SHA hasher test string".as_bytes();
        let mut hasher = ShaHasher::default();
        hasher.write(test_string);
        let node = hasher.hash();

        let reference_hash = sha2::Sha256::digest(test_string);
        assert_eq!(hex::encode(node), hex::encode(reference_hash));
    }
}
