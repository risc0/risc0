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

//! [WorkClaim] and associated types and functions.

use alloc::{boxed::Box, collections::VecDeque, vec::Vec};
use core::fmt;

use borsh::{BorshDeserialize, BorshSerialize};
use risc0_binfmt::{tagged_struct, DecodeError, Digestible, PovwNonce};
use serde::{Deserialize, Serialize};

use crate::{
    sha::{Digest, Sha256},
    MaybePruned, PrunedValueError, ReceiptClaim,
};

/// A wrapper around the underlying claim that additionally includes the amount of verifiable work
/// completed, and the nonces used, in the process of proving the claim.
///
/// This type is instantiated as [WorkClaim<ReceiptClaim>] when PoVW is used with zkVM proving.
#[derive(Clone, Serialize, Deserialize, BorshSerialize, BorshDeserialize)]
pub struct WorkClaim<Claim>
where
    Claim: Clone + Serialize,
{
    /// The wrapped claim (e.g. [ReceiptClaim][crate::ReceiptClaim]).
    pub claim: MaybePruned<Claim>,
    /// Work associated with proving the wrapped claim.
    pub work: MaybePruned<Work>,
}

impl<Claim> Digestible for WorkClaim<Claim>
where
    Claim: Digestible + Clone + Serialize,
{
    /// Hash the [ReceiptClaim] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        tagged_struct::<S>(
            "risc0.WorkClaim",
            &[self.claim.digest::<S>(), self.work.digest::<S>()],
            &[],
        )
    }
}

impl<Claim> fmt::Debug for WorkClaim<Claim>
where
    Claim: Clone + Serialize + Digestible + fmt::Debug,
{
    fn fmt(&self, fmt: &mut fmt::Formatter<'_>) -> fmt::Result {
        fmt.debug_struct("WorkClaim")
            .field("claim", &self.claim)
            .field("work", &self.work)
            .finish()
    }
}

impl WorkClaim<ReceiptClaim> {
    /// TODO
    pub fn encode_to_seal(&self, buf: &mut Vec<u32>) -> Result<(), PrunedValueError> {
        self.claim.as_value()?.encode(buf)?;
        self.work.as_value()?.encode_to_seal(buf);
        Ok(())
    }

    /// TODO
    pub fn decode_from_seal(
        buf: &mut VecDeque<u32>,
    ) -> Result<Self, crate::claim::receipt::DecodeError> {
        Ok(Self {
            claim: ReceiptClaim::decode(buf)?.into(),
            work: Work::decode_from_seal(buf)?.into(),
        })
    }
}

/// A compact representation of completed work within Proof of Verifiable Work (PoVW).
///
/// This struct contains a compact representation of the range of used nonces, along with the value
/// of the work. It is used to represent the work within a single execution.
// TODO(povw): Rename this to be more clear that this is just one representation of work? (in
// particular that this is the compact range representation).
#[derive(Clone, Debug, Serialize, Deserialize, BorshSerialize, BorshDeserialize, PartialEq, Eq)]
pub struct Work {
    /// Lowest nonce in the range, inclusive.
    pub nonce_min: PovwNonce,
    /// Highest nonce in the range, inclusive.
    pub nonce_max: PovwNonce,
    /// Value of work (e.g. cycles) accumulated.
    pub value: u64,
}

/// Error returned when the
#[derive(Debug, Clone)]
#[non_exhaustive]
pub enum WorkClaimError {
    NonceRangesNotContiguous(Box<(Work, Work)>),
    PrunedValue(PrunedValueError),
}

impl fmt::Display for WorkClaimError {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            WorkClaimError::NonceRangesNotContiguous(ab) => {
                write!(
                    f,
                    "work nonce ranges are not contiguous: ({:?}, {:?}) and ({:?}. {:?})",
                    ab.0.nonce_min, ab.0.nonce_max, ab.1.nonce_min, ab.1.nonce_max
                )
            }
            WorkClaimError::PrunedValue(err) => err.fmt(f),
        }
    }
}

impl From<PrunedValueError> for WorkClaimError {
    fn from(err: PrunedValueError) -> Self {
        Self::PrunedValue(err)
    }
}

#[cfg(feature = "std")]
impl std::error::Error for WorkClaimError {}

impl Work {
    /// TODO
    pub fn join(&self, other: &Self) -> Result<Self, WorkClaimError> {
        // Check that the two nonce ranges are contiguous. This must match the implementation of
        // the join_povw recursion program.
        let contiguous = self
            .nonce_max
            .to_u256()
            .checked_add(1u64.try_into().unwrap())
            .map(|max| max == other.nonce_min.to_u256())
            .unwrap_or(false);
        if !contiguous {
            return Err(WorkClaimError::NonceRangesNotContiguous(Box::new((
                self.clone(),
                other.clone(),
            ))));
        }

        Ok(Self {
            nonce_min: self.nonce_min,
            nonce_max: other.nonce_max,
            value: self.value + other.value,
        })
    }

    pub(crate) fn encode_to_seal(&self, buf: &mut Vec<u32>) {
        buf.extend(self.nonce_min.to_u16s().into_iter().map(u32::from));
        buf.extend(self.nonce_max.to_u16s().into_iter().map(u32::from));
        buf.extend(u64_to_u16s(self.value).into_iter().map(u32::from));
    }

    pub(crate) fn decode_from_seal(
        buf: &mut VecDeque<u32>,
    ) -> Result<Self, risc0_binfmt::DecodeError> {
        Ok(Self {
            nonce_min: PovwNonce::decode_from_seal(buf)?,
            nonce_max: PovwNonce::decode_from_seal(buf)?,
            value: decode_work_value_from_seal(buf)?,
        })
    }
}

impl MaybePruned<Work> {
    /// TODO
    pub fn join(&self, other: &Self) -> Result<Self, WorkClaimError> {
        Ok(self.as_value()?.join(other.as_value()?)?.into())
    }
}

fn u64_to_u16s(x: u64) -> [u16; 4] {
    let mut u16s = bytemuck::cast::<_, [u16; 4]>(x.to_le_bytes());
    // Bytes are little-endian, so on a big-endian machine, they need to be reversed.
    for x in u16s.iter_mut() {
        *x = u16::from_le(*x);
    }
    u16s
}

fn u64_from_u16s(mut u16s: [u16; 4]) -> u64 {
    // Bytes are little-endian, so on a big-endian machine, they need to be reversed.
    for x in u16s.iter_mut() {
        *x = u16::from_le(*x);
    }
    u64::from_le_bytes(bytemuck::cast(u16s))
}

fn decode_work_value_from_seal(buf: &mut VecDeque<u32>) -> Result<u64, risc0_binfmt::DecodeError> {
    if buf.len() < 4 {
        return Err(DecodeError::EndOfStream);
    }
    fn u16_from_u32(x: u32) -> Result<u16, risc0_binfmt::DecodeError> {
        x.try_into()
            .map_err(|_| risc0_binfmt::DecodeError::OutOfRange)
    }
    Ok(u64_from_u16s(
        buf.drain(..4)
            .map(u16_from_u32)
            .collect::<Result<Vec<_>, _>>()?
            .try_into()
            .unwrap(),
    ))
}

impl Digestible for Work {
    /// Hash the [ReceiptClaim] to get a digest of the struct.
    fn digest<S: Sha256>(&self) -> Digest {
        let mut buf = Vec::new();
        self.encode_to_seal(&mut buf);
        tagged_struct::<S>("risc0.Work", &Vec::<Digest>::new(), &buf)
    }
}

#[cfg(test)]
mod tests {
    use super::*;
    use crate::ReceiptClaim;
    use alloc::collections::VecDeque;

    #[test]
    fn test_work_seal_encoding_round_trip() {
        let original = Work {
            nonce_min: rand::random(),
            nonce_max: rand::random(),
            value: rand::random(),
        };

        let mut buf = Vec::new();
        original.encode_to_seal(&mut buf);

        let mut decode_buf = VecDeque::from(buf);
        let decoded = Work::decode_from_seal(&mut decode_buf).unwrap();

        assert_eq!(original.nonce_min, decoded.nonce_min);
        assert_eq!(original.nonce_max, decoded.nonce_max);
        assert_eq!(original.value, decoded.value);
        assert!(decode_buf.is_empty());
    }

    #[test]
    fn test_work_claim_seal_encoding_round_trip() {
        use crate::sha::Digest;

        let original = WorkClaim {
            claim: ReceiptClaim::ok(Digest::from([1u8; 32]), vec![1u8, 2u8, 3u8]).into(),
            work: Work {
                nonce_min: rand::random(),
                nonce_max: rand::random(),
                value: rand::random(),
            }
            .into(),
        };

        let mut buf = Vec::new();
        original.encode_to_seal(&mut buf).unwrap();

        let mut decode_buf = VecDeque::from(buf);
        let decoded = WorkClaim::decode_from_seal(&mut decode_buf).unwrap();

        assert_eq!(
            original.claim.as_value().unwrap(),
            decoded.claim.as_value().unwrap()
        );
        assert_eq!(
            original.work.as_value().unwrap().nonce_min,
            decoded.work.as_value().unwrap().nonce_min
        );
        assert_eq!(
            original.work.as_value().unwrap().nonce_max,
            decoded.work.as_value().unwrap().nonce_max
        );
        assert_eq!(
            original.work.as_value().unwrap().value,
            decoded.work.as_value().unwrap().value
        );
        assert!(decode_buf.is_empty());
    }
}
