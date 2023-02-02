// Copyright 2023 RISC Zero, Inc.
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

//! Simple SHA-256 wrappers.

use alloc::format;
use alloc::vec::Vec;
use core::{
    fmt::{Debug, Display, Formatter},
    ops::DerefMut,
};

use bytemuck::{Pod, PodCastError, Zeroable};
use hex::{FromHex, FromHexError};
use risc0_zeroio::{Deserialize as ZeroioDeserialize, Serialize as ZeroioSerialize};
pub use risc0_zkvm_platform::WORD_SIZE;
use serde::{Deserialize, Serialize};

/// The number of words in the representation of a [Digest].
pub const DIGEST_WORDS: usize = 8;

/// Size of the [Digest] representation in bytes.
///
/// Note that digests are stored in memory as words instead of bytes.
pub const DIGEST_BYTES: usize = DIGEST_WORDS * WORD_SIZE;

/// The number of words in the representation of a [Block].
///
/// Note that for SHA-256 the block is twice the size of the [Digest].
pub const BLOCK_WORDS: usize = DIGEST_WORDS * 2;

/// Size of the [Block] representation in bytes.
///
/// Note that blocks are stored in memory as words instead of bytes, and that a
/// [Block] is twice the size of a [Digest].
pub const BLOCK_BYTES: usize = DIGEST_BYTES * 2;

/// Standard SHA-256 initialization vector.
pub static SHA256_INIT: Digest = Digest([
    0x6a09e667_u32.to_be(),
    0xbb67ae85_u32.to_be(),
    0x3c6ef372_u32.to_be(),
    0xa54ff53a_u32.to_be(),
    0x510e527f_u32.to_be(),
    0x9b05688c_u32.to_be(),
    0x1f83d9ab_u32.to_be(),
    0x5be0cd19_u32.to_be(),
]);

/// An implementation of the SHA-256 hashing algorithm of [FIPS 180-4].
///
/// [FIPS 180-4]: https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
pub trait Sha256 {
    /// A pointer to the digest created as the result of a hashing operation.
    ///
    /// This may either be a `Box<Digest>` or some other pointer in case the
    /// implementation wants to manage its own memory. Semantically, holding the
    /// `DigestPtr` denotes ownership of the underlying value. (e.g. `DigestPtr`
    /// does not implement `Copy` and the owner of `DigestPtr` can create a
    /// mutable reference to the underlying digest).
    type DigestPtr: DerefMut<Target = Digest> + Debug;

    /// Generate a SHA-256 hash from a slice of bytes, padding to block size
    /// and adding the SHA-256 hash trailer, as specified in FIPS 180-4.
    fn hash_bytes(bytes: &[u8]) -> Self::DigestPtr;

    /// Generate a SHA-256 hash from a slice of words, padding to block size
    /// and adding the SHA-256 hash trailer, as specified in FIPS 180-4.
    fn hash_words(words: &[u32]) -> Self::DigestPtr {
        Self::hash_bytes(bytemuck::cast_slice(words) as &[u8])
    }

    /// Generate a hash from a pair of [Digest] using the SHA-256 compression
    /// function. Note that the result is not a standard-compliant hash of any
    /// kwown preimage.
    fn hash_pair(a: &Digest, b: &Digest) -> Self::DigestPtr {
        Self::compress(&SHA256_INIT, a, b)
    }

    /// Execute the SHA-256 compression function on a single block given as
    /// two half-blocks and return a pointer to the result.
    ///
    /// NOTE: The half blocks do not need to be adjacent.
    ///
    /// DANGER: This is the low-level SHA-256 compression function. It is a
    /// primitive used to construct SHA-256, but it is NOT the full
    /// algorithm and should be used directly only with extreme caution.
    fn compress(state: &Digest, block_half1: &Digest, block_half2: &Digest) -> Self::DigestPtr;

    /// Execute the SHA-256 compression function on a slice of blocks following
    /// the [Merkle–Damgård] construction and return a pointer to the result.
    ///
    /// DANGER: This is the low-level SHA-256 compression function. It is a
    /// primitive used to construct SHA-256, but it is NOT the full
    /// algorithm and should be used directly only with extreme caution.
    ///
    /// [Merkle–Damgård]: https://en.wikipedia.org/wiki/Merkle%E2%80%93Damg%C3%A5rd_construction
    fn compress_slice(state: &Digest, blocks: &[Block]) -> Self::DigestPtr;

    /// Generate a hash from a slice of anything that can be represented as
    /// plain old data. Pads up to the SHA-256 block boundary, but does not
    /// add the standard SHA-256 trailer and so is not a standards compliant
    /// hash.
    fn hash_raw_pod_slice<T: bytemuck::Pod>(slice: &[T]) -> Self::DigestPtr;
}

/// The result of the SHA-256 hash algorithm.
///
/// NOTE: Bytes in the [Digest] type are stored in big-endian order regardless
/// of the host architecture. When interpreted as words, the numerical result
/// will depend on the architecture.
#[derive(
    Copy,
    Clone,
    Eq,
    Ord,
    PartialOrd,
    PartialEq,
    Pod,
    Zeroable,
    Serialize,
    Deserialize,
    ZeroioSerialize,
    ZeroioDeserialize,
)]
#[repr(transparent)]
pub struct Digest([u32; DIGEST_WORDS]);

impl Digest {
    /// Returns a reference to the [Digest] as a slice of words.
    pub fn as_words(&self) -> &[u32] {
        &self.0
    }

    /// Returns a reference to the [Digest] as a slice of bytes.
    pub fn as_bytes(&self) -> &[u8] {
        bytemuck::cast_slice(&self.0)
    }

    /// Returns a mutable slice of words.
    pub fn as_mut_words(&mut self) -> &mut [u32] {
        &mut self.0
    }

    /// Returns a mutable slice of bytes.
    pub fn as_mut_bytes(&mut self) -> &mut [u8] {
        bytemuck::cast_slice_mut(&mut self.0)
    }
}

impl Default for Digest {
    fn default() -> Digest {
        Digest([0; DIGEST_WORDS])
    }
}

/// Create a new [Digest] from an array of words.
impl From<[u32; DIGEST_WORDS]> for Digest {
    fn from(data: [u32; DIGEST_WORDS]) -> Self {
        Self(data)
    }
}

/// Create a new [Digest] from an array of bytes.
impl From<[u8; DIGEST_BYTES]> for Digest {
    fn from(data: [u8; DIGEST_BYTES]) -> Self {
        match bytemuck::try_cast(data) {
            Ok(digest) => digest,
            Err(PodCastError::TargetAlignmentGreaterAndInputNotAligned) => {
                // Bytes are not aligned. Copy the byte array into a new digest.
                bytemuck::pod_read_unaligned(&data)
            }
            Err(e) => unreachable!("failed to cast [u8; DIGEST_BYTES] to Digest: {}", e),
        }
    }
}

impl<'a> From<&'a [u32; DIGEST_WORDS]> for &'a Digest {
    fn from(data: &'a [u32; DIGEST_WORDS]) -> Self {
        bytemuck::cast_ref(data)
    }
}

impl FromHex for Digest {
    type Error = FromHexError;

    fn from_hex<T: AsRef<[u8]>>(hex: T) -> Result<Self, Self::Error> {
        Ok(<[u8; DIGEST_BYTES]>::from_hex(hex)?.into())
    }
}

impl TryFrom<&[u8]> for Digest {
    type Error = core::array::TryFromSliceError;

    fn try_from(data: &[u8]) -> Result<Self, Self::Error> {
        Ok(<[u8; DIGEST_BYTES]>::try_from(data)?.into())
    }
}

impl TryFrom<&[u32]> for Digest {
    type Error = core::array::TryFromSliceError;

    fn try_from(data: &[u32]) -> Result<Self, Self::Error> {
        Ok(<[u32; DIGEST_WORDS]>::try_from(data)?.into())
    }
}

impl<'a> TryFrom<&'a [u32]> for &'a Digest {
    type Error = PodCastError;

    fn try_from(data: &'a [u32]) -> Result<Self, Self::Error> {
        match bytemuck::try_cast_slice(data) {
            Ok(&[ref digest]) => Ok(digest),
            Ok(_) => Err(PodCastError::SizeMismatch),
            Err(e) => Err(e),
        }
    }
}

impl TryFrom<Vec<u8>> for Digest {
    type Error = Vec<u8>;

    fn try_from(data: Vec<u8>) -> Result<Self, Self::Error> {
        Ok(<[u8; DIGEST_BYTES]>::try_from(data)?.into())
    }
}

impl TryFrom<Vec<u32>> for Digest {
    type Error = Vec<u32>;

    fn try_from(data: Vec<u32>) -> Result<Self, Self::Error> {
        Ok(<[u32; DIGEST_WORDS]>::try_from(data)?.into())
    }
}

impl From<Digest> for [u8; DIGEST_BYTES] {
    fn from(digest: Digest) -> Self {
        bytemuck::cast(digest)
    }
}

impl From<Digest> for [u32; DIGEST_WORDS] {
    fn from(digest: Digest) -> Self {
        digest.0
    }
}

impl AsRef<[u8; DIGEST_BYTES]> for Digest {
    fn as_ref(&self) -> &[u8; DIGEST_BYTES] {
        bytemuck::cast_ref(&self.0)
    }
}

impl AsMut<[u8; DIGEST_BYTES]> for Digest {
    fn as_mut(&mut self) -> &mut [u8; DIGEST_BYTES] {
        bytemuck::cast_mut(&mut self.0)
    }
}

impl AsRef<[u32; DIGEST_WORDS]> for Digest {
    fn as_ref(&self) -> &[u32; DIGEST_WORDS] {
        &self.0
    }
}

impl AsMut<[u32; DIGEST_WORDS]> for Digest {
    fn as_mut(&mut self) -> &mut [u32; DIGEST_WORDS] {
        &mut self.0
    }
}

impl AsRef<[u8]> for Digest {
    fn as_ref(&self) -> &[u8] {
        self.as_bytes()
    }
}

impl AsMut<[u8]> for Digest {
    fn as_mut(&mut self) -> &mut [u8] {
        self.as_mut_bytes()
    }
}

impl AsRef<[u32]> for Digest {
    fn as_ref(&self) -> &[u32] {
        self.as_words()
    }
}

impl AsMut<[u32]> for Digest {
    fn as_mut(&mut self) -> &mut [u32] {
        self.as_mut_words()
    }
}

impl Display for Digest {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        f.write_str(&hex::encode(&self))
    }
}

impl Debug for Digest {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        f.write_str(&format!("Digest({})", &hex::encode(&self)))
    }
}

/// Input block to the SHA-256 hashing algorithm. SHA-256 consumes blocks in
/// 512-bit (64-byte) chunks in a [Merkle–Damgård] construction.
///
/// [Merkle–Damgård]: https://en.wikipedia.org/wiki/Merkle%E2%80%93Damg%C3%A5rd_construction
#[derive(
    Copy,
    Clone,
    Eq,
    PartialEq,
    Pod,
    Zeroable,
    Serialize,
    Deserialize,
    ZeroioSerialize,
    ZeroioDeserialize,
)]
#[repr(transparent)]
pub struct Block([u32; BLOCK_WORDS]);

impl Block {
    /// Returns a reference to the [Block] as a slice of words.
    pub fn as_words(&self) -> &[u32] {
        &self.0
    }

    /// Returns a reference to the [Block] as a slice of bytes.
    pub fn as_bytes(&self) -> &[u8] {
        bytemuck::cast_slice(&self.0)
    }

    /// Returns a mutable slice of words.
    pub fn as_mut_words(&mut self) -> &mut [u32] {
        &mut self.0
    }

    /// Returns the [Block] as references to two half-blocks, with the same size
    /// are a SHA-256 digest.
    pub fn as_half_blocks(&self) -> (&Digest, &Digest) {
        match bytemuck::cast_slice::<_, Digest>(self.as_words()) {
            &[ref half_block1, ref half_block2] => (half_block1, half_block2),
            _ => unreachable!("a block can always be decomposed into two digests"),
        }
    }

    /// Returns a mutable slice of bytes.
    pub fn as_mut_bytes(&mut self) -> &mut [u8] {
        bytemuck::cast_slice_mut(&mut self.0)
    }
}

impl Default for Block {
    fn default() -> Block {
        Block([0; BLOCK_WORDS])
    }
}

/// Create a new [Block] from an array of words.
impl From<[u32; BLOCK_WORDS]> for Block {
    fn from(data: [u32; BLOCK_WORDS]) -> Self {
        Self(data)
    }
}

/// Create a new [Block] from an array of bytes.
impl From<[u8; BLOCK_BYTES]> for Block {
    fn from(data: [u8; BLOCK_BYTES]) -> Self {
        match bytemuck::try_cast(data) {
            Ok(block) => block,
            Err(PodCastError::TargetAlignmentGreaterAndInputNotAligned) => {
                // Bytes are not aligned. Copy the byte array into a new block.
                bytemuck::pod_read_unaligned(&data)
            }
            Err(e) => unreachable!("failed to cast [u8; BLOCK_BYTES] to Block: {}", e),
        }
    }
}

impl<'a> From<&'a [u32; BLOCK_WORDS]> for &'a Block {
    fn from(data: &'a [u32; BLOCK_WORDS]) -> Self {
        bytemuck::cast_ref(data)
    }
}

impl FromHex for Block {
    type Error = FromHexError;

    fn from_hex<T: AsRef<[u8]>>(hex: T) -> Result<Self, Self::Error> {
        Ok(<[u8; BLOCK_BYTES]>::from_hex(hex)?.into())
    }
}

impl TryFrom<&[u8]> for Block {
    type Error = core::array::TryFromSliceError;

    fn try_from(data: &[u8]) -> Result<Self, Self::Error> {
        Ok(<[u8; BLOCK_BYTES]>::try_from(data)?.into())
    }
}

impl TryFrom<&[u32]> for Block {
    type Error = core::array::TryFromSliceError;

    fn try_from(data: &[u32]) -> Result<Self, Self::Error> {
        Ok(<[u32; BLOCK_WORDS]>::try_from(data)?.into())
    }
}

impl TryFrom<Vec<u8>> for Block {
    type Error = Vec<u8>;

    fn try_from(data: Vec<u8>) -> Result<Self, Self::Error> {
        Ok(<[u8; BLOCK_BYTES]>::try_from(data)?.into())
    }
}

impl TryFrom<Vec<u32>> for Block {
    type Error = Vec<u32>;

    fn try_from(data: Vec<u32>) -> Result<Self, Self::Error> {
        Ok(<[u32; BLOCK_WORDS]>::try_from(data)?.into())
    }
}

impl From<Block> for [u8; BLOCK_BYTES] {
    fn from(digest: Block) -> Self {
        bytemuck::cast(digest)
    }
}

impl From<Block> for [u32; BLOCK_WORDS] {
    fn from(digest: Block) -> Self {
        digest.0
    }
}

impl AsRef<[u8; BLOCK_BYTES]> for Block {
    fn as_ref(&self) -> &[u8; BLOCK_BYTES] {
        bytemuck::cast_ref(&self.0)
    }
}

impl AsMut<[u8; BLOCK_BYTES]> for Block {
    fn as_mut(&mut self) -> &mut [u8; BLOCK_BYTES] {
        bytemuck::cast_mut(&mut self.0)
    }
}

impl AsRef<[u32; BLOCK_WORDS]> for Block {
    fn as_ref(&self) -> &[u32; BLOCK_WORDS] {
        &self.0
    }
}

impl AsMut<[u32; BLOCK_WORDS]> for Block {
    fn as_mut(&mut self) -> &mut [u32; BLOCK_WORDS] {
        &mut self.0
    }
}

impl AsRef<[u8]> for Block {
    fn as_ref(&self) -> &[u8] {
        self.as_bytes()
    }
}

impl AsMut<[u8]> for Block {
    fn as_mut(&mut self) -> &mut [u8] {
        self.as_mut_bytes()
    }
}

impl AsRef<[u32]> for Block {
    fn as_ref(&self) -> &[u32] {
        self.as_words()
    }
}

impl AsMut<[u32]> for Block {
    fn as_mut(&mut self) -> &mut [u32] {
        self.as_mut_words()
    }
}

impl Display for Block {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        f.write_str(&hex::encode(&self))
    }
}

impl Debug for Block {
    fn fmt(&self, f: &mut Formatter) -> core::fmt::Result {
        f.write_str(&format!("Block({})", &hex::encode(&self)))
    }
}

pub mod rust_crypto {
    //! [Rust Crypto] wrappers for the RISC0 Sha256 trait.
    //!
    //! [Rust Crypto]: https://github.com/RustCrypto
    //!
    //! # Usage
    //!
    //! ```rust
    //! use risc0_zkp::core::{
    //!     sha::rust_crypto::{Sha256, Digest as _},
    //!     sha_cpu,
    //! };
    //!
    //! // create a Sha256 object
    //! let mut hasher = Sha256::<sha_cpu::Impl>::new();
    //!
    //! // write input message
    //! hasher.update(b"hello world");
    //!
    //! // read hash digest and consume hasher
    //! let result = hasher.finalize();
    //!
    //! assert_eq!(hex::encode(result), "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9");
    //!
    //! // more concise version of the code above.
    //! assert_eq!(hex::encode(Sha256::<sha_cpu::Impl>::digest(b"hello world")),
    //!     "b94d27b9934d3e08a52e52d7da7dabfac484efe37a5380ee9088f7ace2efcde9"
    //! );
    //! ```

    use alloc::format;
    use alloc::vec::Vec;
    use core::fmt::{Debug, Formatter};

    pub use digest::Digest;
    use digest::{
        block_buffer::Eager,
        core_api::{
            AlgorithmName, Block, BlockSizeUser, Buffer, BufferKindUser, CoreWrapper,
            CtVariableCoreWrapper, OutputSizeUser, TruncSide, UpdateCore, VariableOutputCore,
        },
        typenum::{U32, U64},
        HashMarker, InvalidOutputSize, Output,
    };

    use super::{BLOCK_BYTES, SHA256_INIT};

    /// Core block-level SHA-256 hasher with variable output size.
    ///
    /// Supports initialization only for the 32 byte output size.
    #[derive(Clone)]
    pub struct Sha256VarCore<S: super::Sha256> {
        // Current internal state of the SHA-256 hashing operation.
        state: Option<S::DigestPtr>,
        // Counter of the number of blocks hashed so far. Note that with blocks of 64 bytes, this
        // implies that a maximum of 256 GB can be hashed.
        block_len: u32,
    }

    impl<S: super::Sha256> HashMarker for Sha256VarCore<S> {}

    impl<S: super::Sha256> BlockSizeUser for Sha256VarCore<S> {
        type BlockSize = U64;
    }

    impl<S: super::Sha256> BufferKindUser for Sha256VarCore<S> {
        type BufferKind = Eager;
    }

    impl<S: super::Sha256> UpdateCore for Sha256VarCore<S> {
        #[inline]
        fn update_blocks(&mut self, blocks: &[Block<Self>]) {
            self.block_len += u32::try_from(blocks.len()).unwrap();

            // If aligned, reinterpret the u8 array blocks as u32 array blocks.
            // If unaligned, the data needs to be copied.
            // SAFETY: We know that Block (alias for GenericArray<u8, U64>) is
            // an array of bytes and so is safe to reinterpret as blocks of words.
            let current_state = self.state.as_deref().unwrap_or(&SHA256_INIT);
            self.state = Some(match unsafe { blocks.align_to::<super::Block>() } {
                (&[], aligned_blocks, &[]) => S::compress_slice(current_state, aligned_blocks),
                _ => S::compress_slice(
                    current_state,
                    &blocks
                        .iter()
                        .map(|block| bytemuck::pod_read_unaligned(block.as_slice()))
                        .collect::<Vec<_>>(),
                ),
            });
        }
    }

    impl<S: super::Sha256> OutputSizeUser for Sha256VarCore<S> {
        type OutputSize = U32;
    }

    impl<S: super::Sha256> VariableOutputCore for Sha256VarCore<S> {
        const TRUNC_SIDE: TruncSide = TruncSide::Left;

        #[inline]
        fn new(output_size: usize) -> Result<Self, InvalidOutputSize> {
            let state = match output_size {
                32 => None,
                _ => return Err(InvalidOutputSize),
            };
            let block_len = 0;
            Ok(Self { state, block_len })
        }

        #[inline]
        fn finalize_variable_core(&mut self, buffer: &mut Buffer<Self>, out: &mut Output<Self>) {
            let bit_len = 8
                * (u32::try_from(buffer.get_pos()).unwrap()
                    + (BLOCK_BYTES as u32) * self.block_len);
            buffer.len64_padding_be(bit_len as u64, |block| {
                // If aligned, reinterpret the u8 array blocks as a u32 array block.
                // If unaligned, the data needs to be copied.
                let current_state = self.state.as_deref().unwrap_or(&SHA256_INIT);
                self.state = Some(
                    match bytemuck::try_from_bytes::<super::Block>(block.as_slice()) {
                        Ok(b) => {
                            S::compress(current_state, b.as_half_blocks().0, b.as_half_blocks().1)
                        }
                        Err(_) => {
                            let b: super::Block = bytemuck::pod_read_unaligned(block.as_slice());
                            S::compress(current_state, b.as_half_blocks().0, b.as_half_blocks().1)
                        }
                    },
                );
            });

            // NOTE: With some work, it would be possible to eliminate the copy here.
            // However it will require quite a bit of reworking of the APIs
            // involved and this copy may be optimized out by the compiler
            // anyway.
            out.copy_from_slice(self.state.as_deref().unwrap().as_bytes())
        }
    }

    impl<S: super::Sha256> AlgorithmName for Sha256VarCore<S> {
        #[inline]
        fn write_alg_name(f: &mut Formatter<'_>) -> core::fmt::Result {
            f.write_str("Sha256")
        }
    }

    impl<S: super::Sha256> Debug for Sha256VarCore<S> {
        #[inline]
        fn fmt(&self, f: &mut Formatter<'_>) -> core::fmt::Result {
            f.write_str(&format!(
                "Sha256VarCore<{}> {{ ... }}",
                core::any::type_name::<S>()
            ))
        }
    }

    /// SHA-256 implementation cross-compatible with `sha2::Sha256`.
    pub type Sha256<S> = CoreWrapper<CtVariableCoreWrapper<Sha256VarCore<S>, U32>>;
}

#[cfg(test)]
mod tests {
    use hex::FromHex;

    use super::Digest;

    #[test]
    fn test_from_hex() {
        assert_eq!(
            Digest::from_hex("00000077000000AA0000001200000034000000560000007a000000a900000009")
                .unwrap(),
            Digest::from([
                0x77_u32.to_be(),
                0xaa_u32.to_be(),
                0x12_u32.to_be(),
                0x34_u32.to_be(),
                0x56_u32.to_be(),
                0x7a_u32.to_be(),
                0xa9_u32.to_be(),
                0x09_u32.to_be(),
            ])
        );
    }

    #[test]
    fn test_roundtrip() {
        const HEX: &str = "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad";
        assert_eq!(hex::encode(Digest::from_hex(HEX).unwrap()), HEX);
    }
}

#[allow(missing_docs)]
pub mod testutil {
    use alloc::vec::Vec;
    use core::ops::Deref;

    use hex::FromHex;
    use risc0_core::field::baby_bear::{BabyBearElem, BabyBearExtElem};

    use super::rust_crypto::Digest as _;
    use super::{rust_crypto, Digest, Sha256};

    // Runs conformance test on a SHA-256 implementation to make sure it properly
    // behaves.
    pub fn test_sha_impl<S: Sha256>() {
        test_hash_pair::<S>();
        test_rust_crypto_wrapper::<S>();
        test_hash_raw_pod_slice::<S>();
        test_sha_basics::<S>();
        test_elems::<S>();
        test_extelems::<S>();

        crate::core::sha_rng::testutil::test_sha_rng_impl::<S>();
    }

    fn test_sha_basics<S: Sha256>() {
        // Standard test vectors
        assert_eq!(
            hex::encode(S::hash_bytes("abc".as_bytes()).deref()),
            "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
        );
        assert_eq!(
            hex::encode(S::hash_bytes("".as_bytes()).deref()),
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
        );
        assert_eq!(
            hex::encode(
                &S::hash_bytes(
                    "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq".as_bytes()
                )
                .deref()
            ),
            "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1"
        );
        assert_eq!(hex::encode(&S::hash_bytes(
            "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu" .as_bytes()).deref()),
            "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1");
        // Test also the 'hexDigest' bit.
        // Python says:
        // >>> hashlib.sha256("Byzantium").hexdigest()
        // 'f75c763b4a52709ac294fc7bd7cf14dd45718c3d50b36f4732b05b8c6017492a'
        assert_eq!(
            hex::encode(&S::hash_bytes(&"Byzantium".as_bytes()).deref()),
            "f75c763b4a52709ac294fc7bd7cf14dd45718c3d50b36f4732b05b8c6017492a"
        );
    }

    fn test_rust_crypto_wrapper<S: Sha256>() {
        // Standard test vectors
        assert_eq!(
            hex::encode(rust_crypto::Sha256::<S>::digest("abc".as_bytes())),
            "ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"
        );
        assert_eq!(
            hex::encode(rust_crypto::Sha256::<S>::digest("".as_bytes())),
            "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"
        );
        assert_eq!(
            hex::encode(rust_crypto::Sha256::<S>::digest(
                "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq".as_bytes()
            )),
            "248d6a61d20638b8e5c026930c3e6039a33ce45964ff2167f6ecedd419db06c1"
        );
        assert_eq!(hex::encode(rust_crypto::Sha256::<S>::digest(
            "abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmnhijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu" .as_bytes())),
            "cf5b16a778af8380036ce59e7b0492370b249b11e8f07a51afac45037afee9d1");
        // Test also the 'hexDigest' bit.
        // Python says:
        // >>> hashlib.sha256("Byzantium").hexdigest()
        // 'f75c763b4a52709ac294fc7bd7cf14dd45718c3d50b36f4732b05b8c6017492a'
        assert_eq!(
            hex::encode(rust_crypto::Sha256::<S>::digest(&"Byzantium".as_bytes())),
            "f75c763b4a52709ac294fc7bd7cf14dd45718c3d50b36f4732b05b8c6017492a"
        );
    }

    fn hash_elems<S: Sha256>(len: usize) -> Digest {
        let items: Vec<BabyBearElem> = (0..len as u32)
            .into_iter()
            .map(|x| BabyBearElem::new(x))
            .collect();
        *S::hash_raw_pod_slice(items.as_slice())
    }

    fn hash_extelems<S: Sha256>(len: usize) -> Digest {
        let items: Vec<BabyBearExtElem> = (0..len as u32)
            .into_iter()
            .map(|x| {
                BabyBearExtElem::new(
                    BabyBearElem::new(x * 4),
                    BabyBearElem::new(x * 4 + 1),
                    BabyBearElem::new(x * 4 + 2),
                    BabyBearElem::new(x * 4 + 3),
                )
            })
            .collect();
        *S::hash_raw_pod_slice(items.as_slice())
    }

    fn test_elems<S: Sha256>() {
        const LENS: &[usize] = &[0, 1, 7, 8, 9];
        // It doesn't matter what elems hash to, as long as they're consistent.
        const EXPECTED_STRS: &[&str] = &[
            "6a09e667bb67ae853c6ef372a54ff53a510e527f9b05688c1f83d9ab5be0cd19",
            "da5698be17b9b46962335799779fbeca8ce5d491c0d26243bafef9ea1837a9d8",
            "643f71dab15c4f6a6e8820dee5f59cc07818b9c4473b47bba9516cc3be992f1c",
            "3dae53575097f63d0a461048813cc9ab870f0ddbcf9e4aea8dcddecc0aea736d",
            "903fe671a0971f6dea6e8a1180dcd1ce87b56d0b42ee3861212e86428a983a5b",
        ];

        let expected: Vec<Digest> = EXPECTED_STRS
            .iter()
            .map(|x| Digest::from_hex(x).unwrap())
            .collect();
        let actual: Vec<Digest> = LENS.iter().map(|x| hash_elems::<S>(*x)).collect();
        assert_eq!(expected, actual);
    }

    fn test_extelems<S: Sha256>() {
        const LENS: &[usize] = &[0, 1, 7, 8, 9];
        // It doesn't matter what extelems hash to, as long as they're consistent.
        const EXPECTED_STRS: &[&str] = &[
            "6a09e667bb67ae853c6ef372a54ff53a510e527f9b05688c1f83d9ab5be0cd19",
            "6343c9ca9260f2d6cf190c2d2bbff0bf928789e4d2c1a24654137a5d48f254bc",
            "07d3bfa65009530790a51cca21b83dd492c60ade96ee1d2c5b25c4c5cfe257b0",
            "60a53ad42dfe03c7c0d1d46790a832356d09b52c6812eada27622476d6180392",
            "5af62d0303208f4573656ac707d7447f0303fd76a134a775f329104d03c37985",
        ];

        let expected: Vec<Digest> = EXPECTED_STRS
            .iter()
            .map(|x| Digest::from_hex(x).unwrap())
            .collect();
        let actual: Vec<Digest> = LENS.iter().map(|x| hash_extelems::<S>(*x)).collect();
        assert_eq!(expected, actual);
    }

    fn test_hash_raw_pod_slice<S: Sha256>() {
        {
            let items: &[u32] = &[1];
            assert_eq!(
                *S::hash_raw_pod_slice(items),
                Digest::from_hex(
                    "e3050856aac389661ae490656ad0ea57df6aff0ff6eef306f8cc2eed4f240249"
                )
                .unwrap()
            );
        }
        {
            let items: &[u32] = &[1, 2];
            assert_eq!(
                *S::hash_raw_pod_slice(items),
                Digest::from_hex(
                    "4138ebae12299733cc677d1150c2a0139454662fc76ec95da75d2bf9efddc57a"
                )
                .unwrap()
            );
        }
        {
            let items: &[u32] = &[0xffffffff];
            assert_eq!(
                *S::hash_raw_pod_slice(items),
                Digest::from_hex(
                    "a3dba037d56175209dfd4191f727e91c5feb67e65a6ab5ed4daf0893c89598c8"
                )
                .unwrap()
            );
        }
    }

    fn test_hash_pair<S: Sha256>() {
        assert_eq!(
            *S::hash_pair(
                &Digest::from_hex(
                    "67e6096a85ae67bb72f36e3c3af54fa57f520e518c68059babd9831f19cde05b"
                )
                .unwrap(),
                &Digest::from_hex(
                    "ad5c37ed90bb53c604e9ce787f6feeac7674bff229c92dc97ce2ba1115c0eb41"
                )
                .unwrap()
            ),
            Digest::from_hex("3aa2c47c47cd9e5c5259fd1c3428c30b9608201f5e163061deea8d2d7c65f2c3")
                .unwrap()
        );
        assert_eq!(
            *S::hash_pair(
                &Digest::from_hex(
                    "0000000000000000000000000000000000000000000000000000000000000000"
                )
                .unwrap(),
                &Digest::from_hex(
                    "0000000000000000000000000000000000000000000000000000000000000000"
                )
                .unwrap()
            ),
            Digest::from_hex("da5698be17b9b46962335799779fbeca8ce5d491c0d26243bafef9ea1837a9d8")
                .unwrap()
        );
    }
}
