// Copyright (c) 2025 RISC Zero, Inc.
//
// All rights reserved.

use std::{
    cmp::Ordering,
    collections::{btree_map, BTreeMap, BTreeSet},
    fmt::Debug,
    ops::{Add, BitOr, ShrAssign, Sub},
};

use anyhow::{bail, ensure};
use hybrid_array::{sizes, typenum, typenum::ToInt, Array, ArraySize};
use risc0_zkvm::{
    sha::{self, Sha256 as _},
    Digest,
};
use ruint::{
    aliases::{U160, U256},
    Uint,
};

mod consts;
pub mod guest;

// TODO: Break up the following code into modules.

use borsh::{BorshDeserialize, BorshSerialize};
use consts::{EMPTY_SUBTREE_ROOTS, FULL_SUBTREE_ROOTS};
use serde::{Deserialize, Serialize};

type U96 = Uint<96, 2>;

// NOTE: The ruint U256 type is not special here. It's just a convinient bitmap.
#[derive(
    Copy, Clone, Debug, PartialEq, Eq, Serialize, Deserialize, BorshSerialize, BorshDeserialize,
)]
pub struct Bitmap(U256);

impl Bitmap {
    pub const EMPTY: Self = Self(U256::ZERO);

    pub const FULL: Self = Self(U256::MAX);

    pub fn bit(&self, index: usize) -> bool {
        assert!(index < U256::BITS);
        self.0.bit(index)
    }

    pub fn set_bit(&mut self, index: usize) {
        assert!(index < U256::BITS);
        self.0.set_bit(index, true)
    }

    pub fn clear_bit(&mut self, index: usize) {
        assert!(index < U256::BITS);
        self.0.set_bit(index, false)
    }

    /// Returns the bitmap with bits min..max set (exclusive of max).
    pub fn from_bit_range(min: usize, max: usize) -> Self {
        let bits = (U256::from(1) << max).wrapping_sub(U256::from(1));
        Self(bits << min)
    }
}

#[cfg(target_endian = "little")]
impl AsRef<[u8; 32]> for Bitmap {
    fn as_ref(&self) -> &[u8; 32] {
        bytemuck::cast_ref(self.0.as_limbs())
    }
}

impl BitOr for Bitmap {
    type Output = Self;

    fn bitor(self, rhs: Self) -> Self::Output {
        Self(self.0 | rhs.0)
    }
}

impl From<[u8; 32]> for Bitmap {
    /// Convert a byte array into a [Bitmap] with the first byte containing the lowest indexed bit.
    fn from(value: [u8; 32]) -> Self {
        Self(U256::from_le_bytes(value))
    }
}

impl From<Bitmap> for [u8; 32] {
    /// Convert a [Bitmap] into a byte array with the first byte containing the lowest indexed bit.
    fn from(value: Bitmap) -> Self {
        value.0.to_le_bytes()
    }
}

#[derive(Clone, Debug, Default)]
pub struct WorkSet {
    pub logs: BTreeMap<U160, WorkLog>,
}

impl WorkSet {
    pub const TREE_HEIGHT: usize = WorkLog::TREE_HEIGHT + 160;
    pub const EMPTY: Self = Self {
        logs: BTreeMap::new(),
    };

    pub fn add(&mut self, id: U160, log: WorkLog) -> anyhow::Result<()> {
        match self.logs.entry(id) {
            btree_map::Entry::Vacant(entry) => entry.insert(log),
            btree_map::Entry::Occupied(_) => bail!("log id 0x{:020x} is occupied", id),
        };
        Ok(())
    }

    pub fn contains(&self, nonce: U256) -> bool {
        self.logs
            .get(&nonce.wrapping_shr(96).to::<U160>())
            .map(|job| job.contains(nonce.wrapping_to::<U96>()))
            .unwrap_or_default()
    }

    pub fn commit(&self) -> Digest {
        self.subtree_root(Self::TREE_HEIGHT, U256::ZERO)
    }

    pub fn prove_opening(&self, nonce: U256) -> Opening<Self> {
        let mut index = nonce;
        let bitmap = self.bitmap_at(index);

        // Build the path as the sibling of each subtree root in the path to the root.
        let mut path = Box::<Array<Digest, _>>::default();
        index >>= 8;
        for i in 0..path.len() {
            path[i] = self.subtree_root(i, index ^ U256::from(1));
            index >>= 1;
        }

        Opening { bitmap, path }
    }

    fn subtree_root(&self, height: usize, index: U256) -> Digest {
        assert!(height <= Self::TREE_HEIGHT);
        assert!(index < (U256::from(1) << (Self::TREE_HEIGHT - height)));

        if height < WorkLog::TREE_HEIGHT {
            let sublog_index_bits = WorkLog::TREE_HEIGHT - height;
            let sublog_index =
                (index & ((U256::from(1) << sublog_index_bits) - U256::from(1))).to::<U96>();
            let log_index = (index >> sublog_index_bits).to::<U160>();
            return self
                .logs
                .get(&log_index)
                .unwrap_or(&WorkLog::EMPTY)
                .subtree_root(height, sublog_index);
        }

        // Cast index to U160. At this point it must be less than 2^160.
        let index: U160 = index.to();
        let height_offset = height - WorkLog::TREE_HEIGHT;

        // A level of the tree, holding only roots of non-empty subtrees that are decendents of the
        // desired root.
        let mut level: BTreeMap<U160, Digest> = self
            .logs
            .iter()
            .filter(|(id, _)| id.wrapping_shr(height_offset) == index)
            .map(|(id, job)| (*id, job.commit()))
            .collect();

        // Index is of an empty subtree
        if level.is_empty() {
            return EMPTY_SUBTREE_ROOTS[height];
        }

        // Iterate up the levels, from the roots of the job trees to the root of the subtree.
        #[allow(clippy::needless_range_loop)]
        for i in WorkLog::TREE_HEIGHT..height {
            let next_level_keys: BTreeSet<U160> =
                level.keys().map(|idx| idx.wrapping_shr(1)).collect();
            level = next_level_keys
                .into_iter()
                .map(|idx| {
                    let empty = &EMPTY_SUBTREE_ROOTS[i];
                    let left = level.get(&(idx << 1)).unwrap_or(empty);
                    let right = level.get(&((idx << 1) ^ U160::from(1))).unwrap_or(empty);
                    (idx, join(*left, *right))
                })
                .collect();
        }

        // At this point, there should be exactly one node in the level.
        assert!(level.len() == 1);
        *level.first_key_value().unwrap().1
    }

    fn bitmap_at(&self, index: U256) -> Bitmap {
        self.logs
            .get(&(index >> 96usize).to::<U160>())
            .unwrap_or(&WorkLog::EMPTY)
            .bitmap_at(index.wrapping_to::<U96>())
    }
}

#[derive(Clone, Debug, Default)]
pub struct WorkLog {
    pub jobs: BTreeMap<u64, Job>,
}

impl WorkLog {
    pub const TREE_HEIGHT: usize = Job::TREE_HEIGHT + 64;
    pub const EMPTY: Self = Self {
        jobs: BTreeMap::new(),
    };

    pub fn add(&mut self, id: u64, job: Job) -> anyhow::Result<()> {
        match self.jobs.entry(id) {
            btree_map::Entry::Vacant(entry) => entry.insert(job),
            btree_map::Entry::Occupied(_) => bail!("job id 0x{:08x} is occupied", id),
        };
        Ok(())
    }

    // TODO: Not a very good name.
    /// Add the given [Job] to the [WorkLog] and provide a Merkle inclusion path showing that the
    /// job number previous was unoccupied in the Merkle tree.
    pub fn prove_add(
        &mut self,
        id: u64,
        job: Job,
    ) -> anyhow::Result<SubtreeOpening<Self, { Job::TREE_HEIGHT }>> {
        let noninclusion_proof = self.prove_job_opening(id);
        self.add(id, job)?;
        Ok(noninclusion_proof)
    }

    /// Check whether the work log contains a given sequence number, which is the combined job
    /// number and index within the job.
    pub fn contains(&self, seq: U96) -> bool {
        self.jobs
            .get(&seq.wrapping_shr(32).to::<u64>())
            .map(|job| job.contains(seq.wrapping_to::<u32>()))
            .unwrap_or_default()
    }

    pub fn commit(&self) -> Digest {
        self.subtree_root(Self::TREE_HEIGHT, U96::ZERO)
    }

    pub fn prove_opening(&self, seq: U96) -> Opening<Self> {
        let mut index = seq;
        let bitmap = self.bitmap_at(index);

        // Build the path as the sibling of each subtree root in the path to the root.
        let mut path = Box::<Array<Digest, _>>::default();
        index >>= 8;
        for i in 0..path.len() {
            path[i] = self.subtree_root(i, index ^ U96::from(1));
            index >>= 1;
        }

        Opening { bitmap, path }
    }

    pub fn prove_job_opening(&self, job_id: u64) -> SubtreeOpening<Self, { Job::TREE_HEIGHT }> {
        let mut index = job_id;

        // Build the path as the sibling of each subtree root in the path to the root.
        let mut path = Box::<Array<Digest, _>>::default();
        for i in 0..path.len() {
            path[i] = self.subtree_root(Job::TREE_HEIGHT + i, U96::from(index ^ 1));
            index >>= 1;
        }

        SubtreeOpening { path }
    }

    fn subtree_root(&self, height: usize, index: U96) -> Digest {
        assert!(height <= Self::TREE_HEIGHT);
        assert!(index < (U96::from(1) << (Self::TREE_HEIGHT - height)));

        if height <= Job::TREE_HEIGHT {
            let subjob_index_bits = Job::TREE_HEIGHT - height;
            let subjob_index =
                (index & ((U96::from(1) << subjob_index_bits) - U96::from(1))).to::<u32>();
            let job_index = (index >> subjob_index_bits).to::<u64>();
            return self
                .jobs
                .get(&job_index)
                .unwrap_or(&Job::EMPTY)
                .subtree_root(height, subjob_index);
        }

        // Cast index to u64. At this point it must be less than 2^64.
        let index: u64 = index.to();
        let height_offset = height - Job::TREE_HEIGHT;

        // A level of the tree, holding only roots of non-empty subtrees that are decendents of the
        // desired root. Starts holding all decendent nodes at Job::TREE_HEIGHT + 1.
        let mut level: BTreeMap<u64, Digest> = self
            .jobs
            .iter()
            .filter(|(id, _)| id.checked_shr(height_offset as u32).unwrap_or(0) == index)
            .map(|(id, job)| (*id, job.commit()))
            .collect();

        // Index is of an empty subtree
        if level.is_empty() {
            return EMPTY_SUBTREE_ROOTS[height];
        }

        // Iterate up the levels, from the roots of the job trees to the root of the subtree.
        #[allow(clippy::needless_range_loop)]
        for i in Job::TREE_HEIGHT..height {
            let next_level_keys: BTreeSet<u64> = level.keys().map(|idx| idx >> 1).collect();
            level = next_level_keys
                .into_iter()
                .map(|idx| {
                    let empty = &EMPTY_SUBTREE_ROOTS[i];
                    let left = level.get(&(idx << 1)).unwrap_or(empty);
                    let right = level.get(&((idx << 1) ^ 1)).unwrap_or(empty);
                    (idx, join(*left, *right))
                })
                .collect();
        }

        // At this point, there should be exactly one node in the level.
        assert!(level.len() == 1);
        *level.first_key_value().unwrap().1
    }

    fn bitmap_at(&self, index: U96) -> Bitmap {
        self.jobs
            .get(&(index >> 32usize).to::<u64>())
            .unwrap_or(&Job::EMPTY)
            .bitmap_at(index.wrapping_to::<u32>())
    }
}

#[derive(Clone, Debug)]
pub struct Job {
    /// Only store the max used index, as a shorthand for the range [0, index_max]. When set to
    /// none, this represents an empty job.
    pub index_max: Option<u32>,
}

impl Job {
    pub const TREE_HEIGHT: usize = <Self as Merkleized>::TreeHeight::INT;
    pub const EMPTY: Self = Self { index_max: None };

    pub fn new(index_max: u32) -> Self {
        Self {
            index_max: Some(index_max),
        }
    }

    pub fn contains(&self, index: u32) -> bool {
        self.index_max.is_some_and(|max| index <= max)
    }

    pub fn commit(&self) -> Digest {
        self.subtree_root(Self::TREE_HEIGHT, 0)
    }

    pub fn prove_opening(&self, mut index: u32) -> Opening<Self> {
        let bitmap = self.bitmap_at(index);

        // Build the path as the sibling of each subtree root in the path to the root.
        let mut path = Box::<Array<Digest, _>>::default();
        index >>= 8;
        for i in 0..path.len() {
            path[i] = self.subtree_root(i, index ^ 1);
            index >>= 1;
        }

        Opening { bitmap, path }
    }

    /// Calculate the root of the subtree that contains the given index, at the given height.
    ///
    /// The index is the index within the specified level (not the index of a bit).
    /// Height 0 is defined as the height of the bitmaps, of which there are 2^24.
    fn subtree_root(&self, height: usize, index: u32) -> Digest {
        // Ensure the height and index are valid.
        assert!(height <= Self::TREE_HEIGHT);
        assert!(index < 1 << (Self::TREE_HEIGHT - height));

        if height == 0 {
            // TODO: We might want to add a tag and hash the leaf here instead.
            return <[u8; 32]>::from(self.bitmap_at(index << 8)).into();
        }

        let Some(index_max) = self.index_max else {
            return EMPTY_SUBTREE_ROOTS[height];
        };

        // Check whether the requested subtree contains the boundry.
        let boundry_level_index = index_max.checked_shr(8 + height as u32).unwrap_or(0);
        match index.cmp(&boundry_level_index) {
            Ordering::Less => FULL_SUBTREE_ROOTS[height],
            Ordering::Equal => self.boundry_subtree_root(height),
            Ordering::Greater => EMPTY_SUBTREE_ROOTS[height],
        }
    }

    fn boundry_subtree_root(&self, height: usize) -> Digest {
        let mut index: u32 = self.index_max.unwrap();

        // Get the leaf and consume the first 8 bits.
        // TODO: We might want to add a tag and hash the leaf here instead.
        let mut node: Digest = <[u8; 32]>::from(self.bitmap_at(index)).into();
        index >>= 8;

        // Iteratively compute the root. All leaves to the left are full, the right empty.
        for i in 0..height {
            node = match index & 1 == 1 {
                true => join(FULL_SUBTREE_ROOTS[i], node),
                false => join(node, EMPTY_SUBTREE_ROOTS[i]),
            };
            index >>= 1;
        }
        node
    }

    fn bitmap_at(&self, index: u32) -> Bitmap {
        let Some(index_max) = self.index_max else {
            return Bitmap::EMPTY;
        };

        // Shave off the lowest 8 bits to get the index of the bitmap within the tree.
        let bitmap_index = index >> 8;
        let bitmap_index_max = index_max >> 8;
        match bitmap_index.cmp(&bitmap_index_max) {
            Ordering::Less => Bitmap::FULL,
            Ordering::Equal => Bitmap::from_bit_range(0, ((index_max & 0xff) + 1) as usize),
            Ordering::Greater => Bitmap::EMPTY,
        }
    }
}

pub trait MerkleizedIndex: Copy + Eq + ShrAssign<usize> + Debug {
    const ZERO: Self;

    /// Lowest 8 bits of the index, which serve as an index into the leaf bitmap.
    fn bitmap_index(self) -> usize;

    /// Lowest bit of the index.
    fn lowest_bit(self) -> bool;
}

impl MerkleizedIndex for u32 {
    const ZERO: u32 = 0;

    fn bitmap_index(self) -> usize {
        (self & 0xff) as usize
    }

    fn lowest_bit(self) -> bool {
        self & 1 == 1
    }
}

impl<const BITS: usize, const LIMBS: usize> MerkleizedIndex for Uint<BITS, LIMBS> {
    const ZERO: Self = Self::ZERO;

    fn bitmap_index(self) -> usize {
        (self & Self::from(0xff)).try_into().unwrap()
    }

    fn lowest_bit(self) -> bool {
        self & Self::from(1) == Self::from(1)
    }
}

mod private {
    use super::*;

    pub(crate) trait Sealed {}

    impl Sealed for Job {}
    impl Sealed for WorkLog {}
    impl Sealed for WorkSet {}
}

#[allow(private_bounds)]
pub trait Merkleized: private::Sealed {
    type TreeHeight: ArraySize;
    type Index: MerkleizedIndex;
}

impl Merkleized for Job {
    type TreeHeight = sizes::U24;
    type Index = u32;
}

impl Merkleized for WorkLog {
    type TreeHeight = <<Job as Merkleized>::TreeHeight as Add<sizes::U64>>::Output;
    type Index = U96;
}

impl Merkleized for WorkSet {
    type TreeHeight = <<WorkLog as Merkleized>::TreeHeight as Add<sizes::U160>>::Output;
    type Index = U256;
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct Opening<T: Merkleized> {
    bitmap: Bitmap,
    path: Box<Array<Digest, T::TreeHeight>>,
}

impl<T: Merkleized> BorshSerialize for Opening<T>
where
    <T::TreeHeight as ArraySize>::ArrayType<Digest>: BorshSerialize,
{
    fn serialize<W: borsh::io::Write>(&self, writer: &mut W) -> borsh::io::Result<()> {
        BorshSerialize::serialize(&self.bitmap, writer)?;
        BorshSerialize::serialize(&self.path.0, writer)
    }
}

impl<T: Merkleized> BorshDeserialize for Opening<T>
where
    <T::TreeHeight as ArraySize>::ArrayType<Digest>: BorshDeserialize,
{
    fn deserialize_reader<R: borsh::io::Read>(reader: &mut R) -> borsh::io::Result<Self> {
        Ok(Self {
            bitmap: BorshDeserialize::deserialize_reader(reader)?,
            path: Box::new(Array(BorshDeserialize::deserialize_reader(reader)?)),
        })
    }
}

impl<T: Merkleized> Opening<T> {
    pub fn verify_inclusion(&self, commit: Digest, index: T::Index) -> anyhow::Result<()> {
        ensure!(
            self.bitmap.bit(index.bitmap_index()),
            "bitmap indicates non-inclusion"
        );
        ensure!(self.root(index) == commit, "path root does not match root");
        Ok(())
    }

    pub fn verify_noninclusion(&self, commit: Digest, index: T::Index) -> anyhow::Result<()> {
        ensure!(
            !self.bitmap.bit(index.bitmap_index()),
            "bitmap indicates inclusion"
        );
        ensure!(self.root(index) == commit, "path root does not match root");
        Ok(())
    }

    fn root(&self, mut index: T::Index) -> Digest {
        // Drop the lowest 8 bits, which are an index into the bitmap.
        index >>= 8;

        // TODO: We might want to add a tag and hash the leaf here instead.
        let mut node = <[u8; 32]>::from(self.bitmap).into();
        for path_node in self.path.iter() {
            node = match index.lowest_bit() {
                true => join(*path_node, node),
                false => join(node, *path_node),
            };
            index >>= 1;
        }
        // NOTE: At this point all bits should be processed and the index should be zero. If it is
        // not, then there is an error in the implementation.
        assert_eq!(
            index,
            T::Index::ZERO,
            "implementation error: index is non-zero at root of path",
        );
        node
    }
}

#[derive(Clone, Debug, Serialize, Deserialize)]
pub struct SubtreeOpening<T: Merkleized, const LEVEL: usize>
where
    typenum::Const<LEVEL>: typenum::ToUInt,
    T::TreeHeight: Sub<typenum::U<LEVEL>>,
    <T::TreeHeight as Sub<typenum::U<LEVEL>>>::Output: ArraySize,
{
    path: Box<Array<Digest, <T::TreeHeight as Sub<typenum::U<LEVEL>>>::Output>>,
}

impl<T: Merkleized, const LEVEL: usize> BorshSerialize for SubtreeOpening<T, LEVEL>
where
    typenum::Const<LEVEL>: typenum::ToUInt,
    T::TreeHeight: Sub<typenum::U<LEVEL>>,
    <T::TreeHeight as Sub<typenum::U<LEVEL>>>::Output: ArraySize,
    <<T::TreeHeight as Sub<typenum::U<LEVEL>>>::Output as ArraySize>::ArrayType<Digest>:
        BorshSerialize,
{
    fn serialize<W: borsh::io::Write>(&self, writer: &mut W) -> borsh::io::Result<()> {
        BorshSerialize::serialize(&self.path.0, writer)
    }
}

impl<T: Merkleized, const LEVEL: usize> BorshDeserialize for SubtreeOpening<T, LEVEL>
where
    typenum::Const<LEVEL>: typenum::ToUInt,
    T::TreeHeight: Sub<typenum::U<LEVEL>>,
    <T::TreeHeight as Sub<typenum::U<LEVEL>>>::Output: ArraySize,
    <<T::TreeHeight as Sub<typenum::U<LEVEL>>>::Output as ArraySize>::ArrayType<Digest>:
        BorshDeserialize,
{
    fn deserialize_reader<R: borsh::io::Read>(reader: &mut R) -> borsh::io::Result<Self> {
        Ok(Self {
            path: Box::new(Array(BorshDeserialize::deserialize_reader(reader)?)),
        })
    }
}

impl<T: Merkleized, const LEVEL: usize> SubtreeOpening<T, LEVEL>
where
    typenum::Const<LEVEL>: typenum::ToUInt,
    T::TreeHeight: Sub<typenum::U<LEVEL>>,
    <T::TreeHeight as Sub<typenum::U<LEVEL>>>::Output: ArraySize,
{
    // TODO: The definition of an index here is a bit awkward and inconsistent with usage
    // elsewhere.
    /// Verify the opening as the root of an empty subtree at the given level (i.e. every bit in
    /// the subtree indicates non-inclusion).
    ///
    /// The given index is the index of any bit in the subtree (e.g. for an opening at level 2. the
    /// indices 0b000, 0b001, 0b010, and 0b011 are all the same subtree. Index 0b100 would be the
    /// sibling subtree).
    pub fn verify_empty(&self, commit: Digest, index: T::Index) -> anyhow::Result<()> {
        ensure!(
            self.root(EMPTY_SUBTREE_ROOTS[LEVEL], index) == commit,
            "path root does not match root"
        );
        Ok(())
    }

    /// Verify the opening as the root of a full subtree at the given level (i.e. every bit in the
    /// subtree indicates inclusion).
    ///
    /// The given index is the index of any bit in the subtree (e.g. for an opening at level 2. the
    /// indices 0b000, 0b001, 0b010, and 0b011 are all the same subtree. Index 0b100 would be the
    /// sibling subtree).
    pub fn verify_full(&self, commit: Digest, index: T::Index) -> anyhow::Result<()> {
        ensure!(
            self.root(FULL_SUBTREE_ROOTS[LEVEL], index) == commit,
            "path root does not match root"
        );
        Ok(())
    }

    pub fn root(&self, subtree_root: Digest, mut index: T::Index) -> Digest {
        // Drop the lowest LEVEL + 8 bits.
        index >>= LEVEL + 8;

        // TODO: We might want to add a tag and hash the leaf here instead.
        let mut node = subtree_root;
        for path_node in self.path.iter() {
            node = match index.lowest_bit() {
                true => join(*path_node, node),
                false => join(node, *path_node),
            };
            index >>= 1;
        }
        node
    }
}

// TODO: Add a tag to the leaves, the inner nodes, or both, to improve resistance to confusion
// issues.
pub(crate) fn join(left: impl Into<[u8; 32]>, right: impl Into<[u8; 32]>) -> Digest {
    *sha::Impl::hash_bytes(&[left.into(), right.into()].concat())
}

#[cfg(test)]
mod tests {
    use anyhow::Context;
    use proptest::{
        arbitrary::any,
        collection::btree_map,
        option, prop_oneof,
        strategy::{Just, Strategy},
        test_runner::{TestCaseError, TestRunner},
    };
    use ruint::aliases::{U160, U256};

    use super::{Bitmap, Job, WorkLog, WorkSet, U96};

    /// Utility used to map any error to Ok(()) and Ok(()) to an error.
    fn expect_err(result: anyhow::Result<()>) -> anyhow::Result<()> {
        result.err().map(|_| ()).context("unexpected Ok result")
    }

    #[test]
    fn bitmap_from_bit_range() {
        assert_eq!(Bitmap::from_bit_range(0, 0), Bitmap::EMPTY);
        assert_eq!(Bitmap::from_bit_range(0, 256), Bitmap::FULL);
        assert_eq!(Bitmap::from_bit_range(0, 1), Bitmap(U256::from(0x1)));
        assert_eq!(Bitmap::from_bit_range(0, 10), Bitmap(U256::from(0x3ff)));
        assert_eq!(Bitmap::from_bit_range(3, 10), Bitmap(U256::from(0x1ff8)));
        assert_eq!(Bitmap::from_bit_range(256, 256), Bitmap::EMPTY);
    }

    #[test]
    fn job_contains() {
        let cases = [
            (
                Job::EMPTY,
                [(0, false), (1, false), (100, false), (u32::MAX, false)].as_slice(),
            ),
            (
                Job::new(100),
                [
                    (0, true),
                    (1, true),
                    (100, true),
                    (101, false),
                    (u32::MAX, false),
                ]
                .as_slice(),
            ),
            (
                Job::new(u32::MAX),
                [(0, true), (1, true), (100, true), (u32::MAX, true)].as_slice(),
            ),
        ];
        for (job, subcases) in cases {
            for (index, expected) in subcases {
                assert_eq!(job.contains(*index), *expected);
            }
        }
    }

    #[test]
    fn job_inclusion_proof_basic() {
        let job = Job::EMPTY;
        let index = 0;
        job.prove_opening(index)
            .verify_noninclusion(job.commit(), index)
            .unwrap();

        let job = Job::new(0);
        let index = 0;
        job.prove_opening(index)
            .verify_inclusion(job.commit(), index)
            .unwrap();

        let job = Job::new(1);
        let index = 0;
        job.prove_opening(index)
            .verify_inclusion(job.commit(), index)
            .unwrap();

        let job = Job::new(u32::MAX);
        let index = 0;
        job.prove_opening(index)
            .verify_inclusion(job.commit(), index)
            .unwrap();

        let job = Job::new(u32::MAX);
        let index = u32::MAX;
        job.prove_opening(index)
            .verify_inclusion(job.commit(), index)
            .unwrap();
    }

    fn arbitrary_job() -> impl Strategy<Value = Job> {
        option::of(any::<u32>()).prop_map(|index_max| Job { index_max })
    }

    #[test]
    fn job_proptest() {
        let mut runner = TestRunner::default();
        runner
            .run(&(arbitrary_job(), any::<u32>()), |(job, index)| {
                let opening = job.prove_opening(index);
                let commit = job.commit();
                if job.contains(index) {
                    Result::and(
                        opening.verify_inclusion(commit, index),
                        expect_err(opening.verify_noninclusion(commit, index)),
                    )
                } else {
                    Result::and(
                        opening.verify_noninclusion(commit, index),
                        expect_err(opening.verify_inclusion(commit, index)),
                    )
                }
                .map_err(|e| TestCaseError::fail(e.to_string()))
            })
            .unwrap();
    }

    #[test]
    fn work_log_inclusion_proof_basic() {
        let mut log = WorkLog::EMPTY;
        for index in [U96::ZERO, U96::MAX, U96::from_limbs([0xdeadbeef; 2])] {
            log.prove_opening(index)
                .verify_noninclusion(log.commit(), index)
                .unwrap();
        }

        log.add(1, Job::new(0)).unwrap();
        let index = U96::ZERO;
        log.prove_opening(index)
            .verify_noninclusion(log.commit(), index)
            .unwrap();

        let index = U96::from(1) << 32;
        log.prove_opening(index)
            .verify_inclusion(log.commit(), index)
            .unwrap();

        let index = (U96::from(1) << 32) + U96::from(1);
        log.prove_opening(index)
            .verify_noninclusion(log.commit(), index)
            .unwrap();
    }

    fn arbitrary_work_log(max_jobs: usize) -> impl Strategy<Value = WorkLog> {
        // NOTE: This only produces non-empty work logs.
        btree_map(any::<u64>(), arbitrary_job(), 1..=max_jobs).prop_map(|jobs| WorkLog { jobs })
    }

    fn arbitrary_work_log_index(
        work_log: impl Strategy<Value = WorkLog>,
    ) -> impl Strategy<Value = (WorkLog, U96)> {
        work_log.prop_flat_map(|work_log| {
            // Uniform sampling of a job index would almost certainly be a job not in the log.
            // Instead, sample from the list of job keys, and from the full space with even weight.
            // NOTE: This will panic if the work log is empty, due to select from empty Vec.
            let job_index = prop_oneof![
                proptest::sample::select(work_log.jobs.keys().copied().collect::<Vec<u64>>()),
                any::<u64>(),
            ];
            let index = (any::<u32>(), job_index).prop_map(|(subjob_index, job_index)| {
                U96::from(job_index)
                    .wrapping_shl(32)
                    .bitor(U96::from(subjob_index))
            });
            (Just(work_log), index)
        })
    }

    #[test]
    fn work_log_proptest() {
        let mut runner = TestRunner::default();
        runner
            .run(
                &arbitrary_work_log_index(arbitrary_work_log(100)),
                |(work_log, index)| {
                    let opening = work_log.prove_opening(index);
                    let commit = work_log.commit();
                    if work_log.contains(index) {
                        Result::and(
                            opening.verify_inclusion(commit, index),
                            expect_err(opening.verify_noninclusion(commit, index)),
                        )
                    } else {
                        Result::and(
                            opening.verify_noninclusion(commit, index),
                            expect_err(opening.verify_inclusion(commit, index)),
                        )
                    }
                    .map_err(|e| TestCaseError::fail(e.to_string()))
                },
            )
            .unwrap();
    }

    #[test]
    fn work_log_proptest_open_job_subtree() {
        let mut runner = TestRunner::default();
        runner
            .run(
                &arbitrary_work_log_index(arbitrary_work_log(100)),
                |(work_log, index)| {
                    let job_id = (index >> 32usize).to::<u64>();
                    let opening = work_log.prove_job_opening(job_id);
                    let commit = work_log.commit();
                    if work_log.contains(U96::from(job_id) << 32) {
                        expect_err(opening.verify_empty(commit, index))
                    } else {
                        opening.verify_empty(commit, index)
                    }
                    .map_err(|e| TestCaseError::fail(e.to_string()))
                },
            )
            .unwrap();
    }

    #[test]
    fn work_set_inclusion_proof_basic() {
        let mut work_set = WorkSet::EMPTY;
        for index in [U256::ZERO, U256::MAX, U256::from_limbs([0xdeadbeef; 4])] {
            work_set
                .prove_opening(index)
                .verify_noninclusion(work_set.commit(), index)
                .unwrap();
        }

        work_set.add(U160::from(1), WorkLog::default()).unwrap();
        work_set
            .logs
            .get_mut(&U160::from(1))
            .unwrap()
            .add(1, Job::new(0))
            .unwrap();

        let index = U256::ZERO;
        work_set
            .prove_opening(index)
            .verify_noninclusion(work_set.commit(), index)
            .unwrap();

        let index = (U256::from(1) << 96) + (U256::from(1) << 32);
        work_set
            .prove_opening(index)
            .verify_inclusion(work_set.commit(), index)
            .unwrap();

        let index = (U256::from(1) << 96) + (U256::from(1) << 32) + U256::from(1);
        work_set
            .prove_opening(index)
            .verify_noninclusion(work_set.commit(), index)
            .unwrap();

        let index = (U256::from(1) << 96) + (U256::from(2) << 32);
        work_set
            .prove_opening(index)
            .verify_noninclusion(work_set.commit(), index)
            .unwrap();
    }

    fn arbitrary_work_set(max_logs: usize, max_jobs: usize) -> impl Strategy<Value = WorkSet> {
        // NOTE: This only produces non-empty work logs.
        btree_map(any::<U160>(), arbitrary_work_log(max_jobs), 1..=max_logs)
            .prop_map(|logs| WorkSet { logs })
    }

    fn arbitrary_work_set_index(
        work_set: impl Strategy<Value = WorkSet>,
    ) -> impl Strategy<Value = (WorkSet, U256)> {
        work_set.prop_flat_map(|work_set| {
            // Uniform sampling of an index would almost certainly be in the set.
            // Instead, sample from the list of log keys, and from the full space with even weight.
            // NOTE: This will panic if the work set is empty, due to select from empty Vec.
            let work_set_strat = Just(work_set.clone());
            let index = prop_oneof![
                proptest::sample::select(work_set.logs.keys().copied().collect::<Vec<U160>>())
                    .prop_flat_map(move |log_index| {
                        let work_log = work_set.logs.get(&log_index).unwrap().clone();
                        arbitrary_work_log_index(Just(work_log)).prop_map(move |(_, index)| {
                            (U256::from(log_index).wrapping_shl(96)).bitor(U256::from(index))
                        })
                    }),
                any::<U256>(),
            ];
            (work_set_strat, index)
        })
    }

    #[test]
    fn work_set_proptest() {
        let mut runner = TestRunner::default();
        runner
            .run(
                &arbitrary_work_set_index(arbitrary_work_set(10, 10)),
                |(work_set, index)| {
                    let opening = work_set.prove_opening(index);
                    let commit = work_set.commit();
                    if work_set.contains(index) {
                        Result::and(
                            opening.verify_inclusion(commit, index),
                            expect_err(opening.verify_noninclusion(commit, index)),
                        )
                    } else {
                        Result::and(
                            opening.verify_noninclusion(commit, index),
                            expect_err(opening.verify_inclusion(commit, index)),
                        )
                    }
                    .map_err(|e| TestCaseError::fail(e.to_string()))
                },
            )
            .unwrap();
    }
}
