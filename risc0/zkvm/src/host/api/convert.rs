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

use std::{fmt::Debug, path::PathBuf};

use anyhow::{anyhow, bail, Result};
use prost::{Message, Name};
use risc0_binfmt::SystemState;
use risc0_circuit_keccak::KeccakState;
use risc0_zkp::core::digest::Digest;
use serde::Serialize;

use super::{malformed_err, path_to_string, pb, Asset, AssetRequest, RedisParams};
use crate::{
    host::client::env::{ProveKeccakRequest, ProveZkrRequest},
    receipt::{
        merkle::MerkleProof, CompositeReceipt, FakeReceipt, InnerAssumptionReceipt, InnerReceipt,
        ReceiptMetadata, SegmentReceipt, SuccinctReceipt,
    },
    receipt_claim::{UnionClaim, Unknown},
    Assumption, Assumptions, ExitCode, Groth16Receipt, Input, Journal, MaybePruned, Output,
    ProveInfo, ProverOpts, Receipt, ReceiptClaim, ReceiptKind, SessionStats, TraceEvent,
};

mod ver {
    use super::pb::base::CompatVersion;

    pub const RECEIPT: CompatVersion = CompatVersion { value: 1 };
    pub const SEGMENT_RECEIPT: CompatVersion = CompatVersion { value: 1 };
    pub const SUCCINCT_RECEIPT: CompatVersion = CompatVersion { value: 1 };
    pub const GROTH16_RECEIPT: CompatVersion = CompatVersion { value: 1 };
}

impl TryFrom<AssetRequest> for pb::api::AssetRequest {
    type Error = anyhow::Error;

    fn try_from(value: AssetRequest) -> Result<Self> {
        Ok(Self {
            kind: Some(match value {
                AssetRequest::Inline => pb::api::asset_request::Kind::Inline(()),
                AssetRequest::Path(path) => {
                    pb::api::asset_request::Kind::Path(path_to_string(path)?)
                }
                AssetRequest::Redis(params) => {
                    pb::api::asset_request::Kind::Redis(pb::api::RedisParams {
                        url: params.url,
                        key: params.key,
                        ttl: params.ttl,
                    })
                }
            }),
        })
    }
}

impl TryFrom<Asset> for pb::api::Asset {
    type Error = anyhow::Error;

    fn try_from(value: Asset) -> Result<Self> {
        Ok(Self {
            kind: match value {
                Asset::Inline(bytes) => Some(pb::api::asset::Kind::Inline(bytes.into())),
                Asset::Path(path) => Some(pb::api::asset::Kind::Path(path_to_string(path)?)),
                Asset::Redis(key) => Some(pb::api::asset::Kind::Redis(key)),
            },
        })
    }
}

impl<Claim> TryFrom<SuccinctReceipt<Claim>> for Asset
where
    Claim: risc0_binfmt::Digestible + Debug + Clone + Serialize,
{
    type Error = anyhow::Error;

    fn try_from(succinct_receipt: SuccinctReceipt<Claim>) -> Result<Self> {
        Ok(Asset::Inline(bincode::serialize(&succinct_receipt)?.into()))
    }
}

impl TryFrom<SegmentReceipt> for Asset {
    type Error = anyhow::Error;

    fn try_from(segment_receipt: SegmentReceipt) -> Result<Self> {
        Ok(Asset::Inline(bincode::serialize(&segment_receipt)?.into()))
    }
}

impl TryFrom<Receipt> for Asset {
    type Error = anyhow::Error;

    fn try_from(receipt: Receipt) -> Result<Self> {
        Ok(Asset::Inline(bincode::serialize(&receipt)?.into()))
    }
}

impl TryFrom<pb::api::Asset> for Asset {
    type Error = anyhow::Error;

    fn try_from(value: pb::api::Asset) -> Result<Self> {
        Ok(
            match value.kind.ok_or_else(|| malformed_err("Asset.kind"))? {
                pb::api::asset::Kind::Inline(bytes) => Asset::Inline(bytes.into()),
                pb::api::asset::Kind::Path(path) => Asset::Path(PathBuf::from(path)),
                pb::api::asset::Kind::Redis(key) => Asset::Redis(key),
            },
        )
    }
}

impl TryFrom<pb::api::AssetRequest> for AssetRequest {
    type Error = anyhow::Error;

    fn try_from(value: pb::api::AssetRequest) -> Result<Self> {
        Ok(
            match value
                .kind
                .ok_or_else(|| malformed_err("AssetRequest.kind"))?
            {
                pb::api::asset_request::Kind::Inline(()) => AssetRequest::Inline,
                pb::api::asset_request::Kind::Path(path) => {
                    AssetRequest::Path(std::path::PathBuf::from(path))
                }
                pb::api::asset_request::Kind::Redis(params) => AssetRequest::Redis(RedisParams {
                    url: params.url,
                    key: params.key,
                    ttl: params.ttl,
                }),
            },
        )
    }
}

impl TryFrom<TraceEvent> for pb::api::TraceEvent {
    type Error = anyhow::Error;

    fn try_from(event: TraceEvent) -> Result<Self> {
        match event {
            TraceEvent::InstructionStart { cycle, pc, insn } => Ok(Self {
                kind: Some(pb::api::trace_event::Kind::InsnStart(
                    pb::api::trace_event::InstructionStart { cycle, pc, insn },
                )),
            }),
            TraceEvent::RegisterSet { idx, value } => Ok(Self {
                kind: Some(pb::api::trace_event::Kind::RegisterSet(
                    pb::api::trace_event::RegisterSet {
                        idx: idx as u32,
                        value,
                    },
                )),
            }),
            TraceEvent::MemorySet { addr, region } => Ok(Self {
                kind: Some(pb::api::trace_event::Kind::MemorySet(
                    pb::api::trace_event::MemorySet {
                        addr,
                        value: 0,
                        region,
                    },
                )),
            }),
            TraceEvent::PageIn { cycles } => Ok(Self {
                kind: Some(pb::api::trace_event::Kind::PageIn(
                    pb::api::trace_event::PageIn { cycles },
                )),
            }),
            TraceEvent::PageOut { cycles } => Ok(Self {
                kind: Some(pb::api::trace_event::Kind::PageOut(
                    pb::api::trace_event::PageOut { cycles },
                )),
            }),
            _ => Err(anyhow!("unknown TraceEvent kind")),
        }
    }
}

impl TryFrom<pb::api::TraceEvent> for TraceEvent {
    type Error = anyhow::Error;

    fn try_from(event: pb::api::TraceEvent) -> Result<Self> {
        Ok(
            match event.kind.ok_or_else(|| malformed_err("TraceEvent.kind"))? {
                pb::api::trace_event::Kind::InsnStart(event) => TraceEvent::InstructionStart {
                    cycle: event.cycle,
                    pc: event.pc,
                    insn: event.insn,
                },
                pb::api::trace_event::Kind::RegisterSet(event) => TraceEvent::RegisterSet {
                    idx: event.idx as usize,
                    value: event.value,
                },
                pb::api::trace_event::Kind::MemorySet(event) => TraceEvent::MemorySet {
                    addr: event.addr,
                    region: event.region,
                },
                pb::api::trace_event::Kind::PageIn(event) => TraceEvent::PageIn {
                    cycles: event.cycles,
                },
                pb::api::trace_event::Kind::PageOut(event) => TraceEvent::PageOut {
                    cycles: event.cycles,
                },
            },
        )
    }
}

impl TryFrom<ExitCode> for pb::base::ExitCode {
    type Error = anyhow::Error;

    fn try_from(value: ExitCode) -> Result<Self> {
        Ok(Self {
            kind: Some(match value {
                ExitCode::SystemSplit => pb::base::exit_code::Kind::SystemSplit(()),
                ExitCode::SessionLimit => pb::base::exit_code::Kind::SessionLimit(()),
                ExitCode::Paused(code) => pb::base::exit_code::Kind::Paused(code),
                ExitCode::Halted(code) => pb::base::exit_code::Kind::Halted(code),
                e => bail!("unsupported exit code: {e:?}"),
            }),
        })
    }
}

impl TryFrom<pb::base::ExitCode> for ExitCode {
    type Error = anyhow::Error;

    fn try_from(value: pb::base::ExitCode) -> Result<Self> {
        Ok(
            match value.kind.ok_or_else(|| malformed_err("ExitCode.kind"))? {
                pb::base::exit_code::Kind::Halted(code) => Self::Halted(code),
                pb::base::exit_code::Kind::Paused(code) => Self::Paused(code),
                pb::base::exit_code::Kind::SystemSplit(_) => Self::SystemSplit,
                pb::base::exit_code::Kind::SessionLimit(_) => Self::SessionLimit,
            },
        )
    }
}

impl From<Result<(), anyhow::Error>> for pb::api::GenericReply {
    fn from(result: Result<(), anyhow::Error>) -> Self {
        Self {
            kind: Some(match result {
                Ok(_) => pb::api::generic_reply::Kind::Ok(()),
                Err(err) => pb::api::generic_reply::Kind::Error(err.into()),
            }),
        }
    }
}

impl From<anyhow::Error> for pb::api::GenericError {
    fn from(err: anyhow::Error) -> Self {
        Self {
            reason: err.to_string(),
        }
    }
}

impl From<pb::api::GenericError> for anyhow::Error {
    fn from(err: pb::api::GenericError) -> Self {
        anyhow::Error::msg(err.reason)
    }
}

impl TryFrom<pb::api::ProverOpts> for ProverOpts {
    type Error = anyhow::Error;

    fn try_from(opts: pb::api::ProverOpts) -> Result<Self> {
        Ok(Self {
            hashfn: opts.hashfn,
            prove_guest_errors: opts.prove_guest_errors,
            receipt_kind: match opts.receipt_kind {
                0 => ReceiptKind::Composite,
                1 => ReceiptKind::Succinct,
                2 => ReceiptKind::Groth16,
                value => panic!("Unknown receipt kind number: {value}"),
            },
            control_ids: opts
                .control_ids
                .into_iter()
                .map(TryInto::try_into)
                .collect::<Result<_>>()?,
            max_segment_po2: opts
                .max_segment_po2
                .try_into()
                .map_err(|_| malformed_err("ProverOpts.max_segment_po2"))?,
            povw_nonce_base: None, // TODO: Add povw_nonce_base to proto
        })
    }
}

impl From<ProverOpts> for pb::api::ProverOpts {
    fn from(opts: ProverOpts) -> Self {
        Self {
            hashfn: opts.hashfn,
            prove_guest_errors: opts.prove_guest_errors,
            receipt_kind: opts.receipt_kind as i32,
            control_ids: opts.control_ids.into_iter().map(Into::into).collect(),
            max_segment_po2: opts.max_segment_po2 as u64,
        }
    }
}

impl From<semver::Version> for pb::base::SemanticVersion {
    fn from(value: semver::Version) -> Self {
        Self {
            major: value.major,
            minor: value.minor,
            patch: value.patch,
            pre: value.pre.to_string(),
            build: value.build.to_string(),
        }
    }
}

impl TryFrom<pb::base::SemanticVersion> for semver::Version {
    type Error = semver::Error;

    fn try_from(value: pb::base::SemanticVersion) -> Result<Self, Self::Error> {
        Ok(Self {
            major: value.major,
            minor: value.minor,
            patch: value.patch,
            pre: semver::Prerelease::new(&value.pre)?,
            build: semver::BuildMetadata::new(&value.build)?,
        })
    }
}

impl From<SessionStats> for pb::core::SessionStats {
    fn from(value: SessionStats) -> Self {
        Self {
            // we use usize because that's the type returned by len() for vectors
            segments: value.segments.try_into().unwrap(),
            total_cycles: value.total_cycles,
            user_cycles: value.user_cycles,
            paging_cycles: value.paging_cycles,
            reserved_cycles: value.reserved_cycles,
        }
    }
}

impl TryFrom<pb::core::SessionStats> for SessionStats {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::SessionStats) -> Result<Self> {
        Ok(Self {
            segments: value.segments.try_into()?,
            total_cycles: value.total_cycles,
            user_cycles: value.user_cycles,
            paging_cycles: value.paging_cycles,
            reserved_cycles: value.reserved_cycles,
        })
    }
}

impl TryFrom<ProveInfo> for pb::core::ProveInfo {
    type Error = anyhow::Error;

    fn try_from(value: ProveInfo) -> Result<Self> {
        Ok(Self {
            receipt: Some(value.receipt.try_into()?),
            stats: Some(value.stats.into()),
        })
    }
}

impl TryFrom<pb::core::ProveInfo> for ProveInfo {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::ProveInfo) -> Result<Self> {
        Ok(Self {
            receipt: value
                .receipt
                .ok_or_else(|| malformed_err("ProveInfo.receipt"))?
                .try_into()?,
            stats: value
                .stats
                .ok_or_else(|| malformed_err("ProveInfo.stats"))?
                .try_into()?,
        })
    }
}

impl TryFrom<Receipt> for pb::core::Receipt {
    type Error = anyhow::Error;

    fn try_from(value: Receipt) -> Result<Self> {
        Ok(Self {
            version: Some(ver::RECEIPT),
            inner: Some(value.inner.try_into()?),
            journal: value.journal.bytes,
            metadata: Some(value.metadata.into()),
        })
    }
}

impl TryFrom<pb::core::Receipt> for Receipt {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::Receipt) -> Result<Self> {
        let version = value
            .version
            .ok_or_else(|| malformed_err("Receipt.version"))?
            .value;
        if version > ver::RECEIPT.value {
            bail!("Incompatible Receipt version: {version}");
        }
        Ok(Self {
            inner: value
                .inner
                .ok_or_else(|| malformed_err("Receipt.inner"))?
                .try_into()?,
            journal: Journal::new(value.journal),
            metadata: value
                .metadata
                .ok_or_else(|| malformed_err("Receipt.metadata"))?
                .try_into()?,
        })
    }
}

impl From<ReceiptMetadata> for pb::core::ReceiptMetadata {
    fn from(value: ReceiptMetadata) -> Self {
        Self {
            verifier_parameters: Some(value.verifier_parameters.into()),
        }
    }
}

impl TryFrom<pb::core::ReceiptMetadata> for ReceiptMetadata {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::ReceiptMetadata) -> Result<Self> {
        Ok(Self {
            verifier_parameters: value
                .verifier_parameters
                .ok_or_else(|| malformed_err("ReceiptMetadata.verifier_parameters"))?
                .try_into()?,
        })
    }
}

impl TryFrom<SegmentReceipt> for pb::core::SegmentReceipt {
    type Error = anyhow::Error;

    fn try_from(value: SegmentReceipt) -> Result<Self> {
        Ok(Self {
            version: Some(ver::SEGMENT_RECEIPT),
            seal: value.get_seal_bytes(),
            index: value.index,
            hashfn: value.hashfn,
            claim: Some(value.claim.try_into()?),
            verifier_parameters: Some(value.verifier_parameters.into()),
        })
    }
}

impl TryFrom<pb::core::SegmentReceipt> for SegmentReceipt {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::SegmentReceipt) -> Result<Self> {
        const WORD_SIZE: usize = std::mem::size_of::<u32>();

        let mut seal = Vec::with_capacity(value.seal.len() / WORD_SIZE);
        for chunk in value.seal.chunks_exact(WORD_SIZE) {
            let word = u32::from_le_bytes(chunk.try_into()?);
            seal.push(word);
        }

        let claim = value
            .claim
            .ok_or_else(|| malformed_err("SegmentReceipt.claim"))?
            .try_into()?;

        Ok(Self {
            claim,
            seal,
            index: value.index,
            hashfn: value.hashfn,
            verifier_parameters: value
                .verifier_parameters
                .ok_or_else(|| malformed_err("SegmentReceipt.verifier_parameters"))?
                .try_into()?,
        })
    }
}

impl<Claim> TryFrom<SuccinctReceipt<Claim>> for pb::core::SuccinctReceipt
where
    Claim: risc0_binfmt::Digestible + Debug + Clone + Serialize,
    MaybePruned<Claim>: TryInto<pb::core::MaybePruned, Error = anyhow::Error>,
{
    type Error = anyhow::Error;

    fn try_from(value: SuccinctReceipt<Claim>) -> Result<Self> {
        Ok(Self {
            version: Some(ver::SUCCINCT_RECEIPT),
            seal: value.get_seal_bytes(),
            control_id: Some(value.control_id.into()),
            control_inclusion_proof: Some(value.control_inclusion_proof.into()),
            claim: Some(value.claim.try_into()?),
            hashfn: value.hashfn,
            verifier_parameters: Some(value.verifier_parameters.into()),
        })
    }
}

impl<Claim> TryFrom<pb::core::SuccinctReceipt> for SuccinctReceipt<Claim>
where
    Claim: risc0_binfmt::Digestible + Debug + Clone + Serialize,
    MaybePruned<Claim>: TryFrom<pb::core::MaybePruned, Error = anyhow::Error>,
{
    type Error = anyhow::Error;

    fn try_from(value: pb::core::SuccinctReceipt) -> Result<Self> {
        const WORD_SIZE: usize = std::mem::size_of::<u32>();

        let version = value
            .version
            .ok_or_else(|| malformed_err("SuccinctReceipt.version"))?
            .value;
        if version > ver::SUCCINCT_RECEIPT.value {
            bail!("Incompatible SuccinctReceipt version: {version}");
        }

        let mut seal = Vec::with_capacity(value.seal.len() / WORD_SIZE);
        for chunk in value.seal.chunks_exact(WORD_SIZE) {
            let word = u32::from_le_bytes(chunk.try_into()?);
            seal.push(word);
        }
        Ok(Self {
            seal,
            control_id: value
                .control_id
                .ok_or_else(|| malformed_err("SuccinctReceipt.control_id"))?
                .try_into()?,
            control_inclusion_proof: value
                .control_inclusion_proof
                .ok_or_else(|| malformed_err("SuccinctReceipt.control_inclusion_proof"))?
                .try_into()?,
            claim: value
                .claim
                .ok_or_else(|| malformed_err("SuccinctReceipt.claim"))?
                .try_into()?,
            hashfn: value.hashfn,
            verifier_parameters: value
                .verifier_parameters
                .ok_or_else(|| malformed_err("SuccinctReceipt.verifier_parameters"))?
                .try_into()?,
        })
    }
}

impl From<MerkleProof> for pb::core::MerkleProof {
    fn from(value: MerkleProof) -> Self {
        Self {
            index: value.index,
            digests: value.digests.into_iter().map(Into::into).collect(),
        }
    }
}

impl TryFrom<pb::core::MerkleProof> for MerkleProof {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::MerkleProof) -> Result<Self> {
        Ok(Self {
            index: value.index,
            digests: value
                .digests
                .into_iter()
                .map(TryInto::try_into)
                .collect::<Result<_>>()?,
        })
    }
}

impl<Claim> TryFrom<Groth16Receipt<Claim>> for pb::core::Groth16Receipt
where
    Claim: risc0_binfmt::Digestible + Debug + Clone + Serialize,
    MaybePruned<Claim>: TryInto<pb::core::MaybePruned, Error = anyhow::Error>,
{
    type Error = anyhow::Error;

    fn try_from(value: Groth16Receipt<Claim>) -> Result<Self> {
        Ok(Self {
            version: Some(ver::GROTH16_RECEIPT),
            seal: value.seal,
            claim: Some(value.claim.try_into()?),
            verifier_parameters: Some(value.verifier_parameters.into()),
        })
    }
}

impl<Claim> TryFrom<pb::core::Groth16Receipt> for Groth16Receipt<Claim>
where
    Claim: risc0_binfmt::Digestible + Debug + Clone + Serialize,
    MaybePruned<Claim>: TryFrom<pb::core::MaybePruned, Error = anyhow::Error>,
{
    type Error = anyhow::Error;

    fn try_from(value: pb::core::Groth16Receipt) -> Result<Self> {
        let version = value
            .version
            .ok_or_else(|| malformed_err("Groth16Receipt.version"))?
            .value;
        if version > ver::GROTH16_RECEIPT.value {
            bail!("Incompatible Groth16Receipt version: {version}");
        }

        Ok(Self {
            seal: value.seal,
            claim: value
                .claim
                .ok_or_else(|| malformed_err("Groth16Receipt.claim"))?
                .try_into()?,
            verifier_parameters: value
                .verifier_parameters
                .ok_or_else(|| malformed_err("Groth16Receipt.verifier_parameters"))?
                .try_into()?,
        })
    }
}

impl TryFrom<InnerReceipt> for pb::core::InnerReceipt {
    type Error = anyhow::Error;

    fn try_from(value: InnerReceipt) -> Result<Self> {
        Ok(Self {
            kind: Some(match value {
                InnerReceipt::Composite(inner) => {
                    pb::core::inner_receipt::Kind::Composite(inner.try_into()?)
                }
                InnerReceipt::Succinct(inner) => {
                    pb::core::inner_receipt::Kind::Succinct(inner.try_into()?)
                }
                InnerReceipt::Fake(inner) => {
                    pb::core::inner_receipt::Kind::Fake(pb::core::FakeReceipt {
                        claim: Some(inner.claim.try_into()?),
                    })
                }
                InnerReceipt::Groth16(inner) => {
                    pb::core::inner_receipt::Kind::Groth16(inner.try_into()?)
                }
            }),
        })
    }
}

impl TryFrom<pb::core::InnerReceipt> for InnerReceipt {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::InnerReceipt) -> Result<Self> {
        Ok(
            match value
                .kind
                .ok_or_else(|| malformed_err("InnerReceipt.kind"))?
            {
                pb::core::inner_receipt::Kind::Composite(inner) => {
                    Self::Composite(inner.try_into()?)
                }
                pb::core::inner_receipt::Kind::Groth16(inner) => Self::Groth16(inner.try_into()?),
                pb::core::inner_receipt::Kind::Succinct(inner) => Self::Succinct(inner.try_into()?),
                pb::core::inner_receipt::Kind::Fake(inner) => Self::Fake(inner.try_into()?),
            },
        )
    }
}

// NOTE: InnerReceipt and InnerAssumptionReceipt are the same type in protobuf.
// In Rust, they are distinct types because Rust needs to size everything on the
// stack and e.g. SuccinctReceipt<ReceiptClaim> and SuccinctReceipt<Unknown>
// have different sizes. Protobuf handles this without issue.
impl TryFrom<InnerAssumptionReceipt> for pb::core::InnerReceipt {
    type Error = anyhow::Error;

    fn try_from(value: InnerAssumptionReceipt) -> Result<Self> {
        Ok(Self {
            kind: Some(match value {
                InnerAssumptionReceipt::Composite(inner) => {
                    pb::core::inner_receipt::Kind::Composite(inner.try_into()?)
                }
                InnerAssumptionReceipt::Succinct(inner) => {
                    pb::core::inner_receipt::Kind::Succinct(inner.try_into()?)
                }
                InnerAssumptionReceipt::Fake(inner) => {
                    pb::core::inner_receipt::Kind::Fake(pb::core::FakeReceipt {
                        claim: Some(inner.claim.try_into()?),
                    })
                }
                InnerAssumptionReceipt::Groth16(inner) => {
                    pb::core::inner_receipt::Kind::Groth16(inner.try_into()?)
                }
            }),
        })
    }
}

impl TryFrom<pb::core::InnerReceipt> for InnerAssumptionReceipt {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::InnerReceipt) -> Result<Self> {
        Ok(
            match value
                .kind
                .ok_or_else(|| malformed_err("InnerReceipt.kind"))?
            {
                pb::core::inner_receipt::Kind::Composite(inner) => {
                    Self::Composite(inner.try_into()?)
                }
                pb::core::inner_receipt::Kind::Groth16(inner) => Self::Groth16(inner.try_into()?),
                pb::core::inner_receipt::Kind::Succinct(inner) => Self::Succinct(inner.try_into()?),
                pb::core::inner_receipt::Kind::Fake(inner) => Self::Fake(inner.try_into()?),
            },
        )
    }
}

impl<Claim> TryFrom<FakeReceipt<Claim>> for pb::core::FakeReceipt
where
    Claim: risc0_binfmt::Digestible + Debug + Clone + Serialize,
    MaybePruned<Claim>: TryInto<pb::core::MaybePruned, Error = anyhow::Error>,
{
    type Error = anyhow::Error;

    fn try_from(value: FakeReceipt<Claim>) -> Result<Self> {
        Ok(Self {
            claim: Some(value.claim.try_into()?),
        })
    }
}

impl<Claim> TryFrom<pb::core::FakeReceipt> for FakeReceipt<Claim>
where
    Claim: risc0_binfmt::Digestible + Debug + Clone + Serialize,
    MaybePruned<Claim>: TryFrom<pb::core::MaybePruned, Error = anyhow::Error>,
{
    type Error = anyhow::Error;

    fn try_from(value: pb::core::FakeReceipt) -> Result<Self> {
        Ok(Self {
            claim: value
                .claim
                .ok_or_else(|| malformed_err("FakeReceipt.claim"))?
                .try_into()?,
        })
    }
}

impl TryFrom<CompositeReceipt> for pb::core::CompositeReceipt {
    type Error = anyhow::Error;

    fn try_from(value: CompositeReceipt) -> Result<Self> {
        Ok(Self {
            segments: value
                .segments
                .into_iter()
                .map(TryInto::try_into)
                .collect::<Result<_>>()?,
            assumption_receipts: value
                .assumption_receipts
                .into_iter()
                .map(TryInto::try_into)
                .collect::<Result<_>>()?,
            verifier_parameters: Some(value.verifier_parameters.into()),
        })
    }
}

impl TryFrom<pb::core::CompositeReceipt> for CompositeReceipt {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::CompositeReceipt) -> Result<Self> {
        Ok(Self {
            segments: value
                .segments
                .into_iter()
                .map(|s| s.try_into())
                .collect::<Result<Vec<_>>>()?,
            assumption_receipts: value
                .assumption_receipts
                .into_iter()
                .map(|a| a.try_into())
                .collect::<Result<Vec<_>>>()?,
            verifier_parameters: value
                .verifier_parameters
                .ok_or_else(|| malformed_err("CompositeReceipt.verifier_parameters"))?
                .try_into()?,
        })
    }
}

impl From<Digest> for pb::base::Digest {
    fn from(value: Digest) -> Self {
        Self {
            words: value.as_words().to_vec(),
        }
    }
}

impl TryFrom<pb::base::Digest> for Digest {
    type Error = anyhow::Error;

    fn try_from(value: pb::base::Digest) -> Result<Self> {
        value
            .words
            .try_into()
            .map_err(|_| anyhow!("invalid digest"))
    }
}

impl Name for pb::core::ReceiptClaim {
    const PACKAGE: &'static str = "risc0.protos.core";
    const NAME: &'static str = "ReceiptClaim";
}

impl AssociatedMessage for ReceiptClaim {
    type Message = pb::core::ReceiptClaim;
}

impl AssociatedMessage for UnionClaim {
    type Message = pb::core::UnionClaim;
}

impl TryFrom<UnionClaim> for pb::core::UnionClaim {
    type Error = anyhow::Error;

    fn try_from(value: UnionClaim) -> Result<Self> {
        Ok(Self {
            left: Some(value.left.into()),
            right: Some(value.right.into()),
        })
    }
}

impl TryFrom<pb::core::UnionClaim> for UnionClaim {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::UnionClaim) -> Result<Self> {
        Ok(Self {
            left: value
                .left
                .ok_or_else(|| malformed_err("UnionClaim.left"))?
                .try_into()?,
            right: value
                .right
                .ok_or_else(|| malformed_err("UnionClaim.right"))?
                .try_into()?,
        })
    }
}

impl TryFrom<ReceiptClaim> for pb::core::ReceiptClaim {
    type Error = anyhow::Error;

    fn try_from(value: ReceiptClaim) -> Result<Self> {
        Ok(Self {
            pre: Some(value.pre.try_into()?),
            post: Some(value.post.try_into()?),
            exit_code: Some(value.exit_code.try_into()?),
            // Translate MaybePruned<Option<Input>>> to Option<MaybePruned<Input>>.
            input: match value.input {
                MaybePruned::Value(optional) => optional
                    .map(|input| MaybePruned::Value(input).try_into())
                    .transpose()?,
                MaybePruned::Pruned(digest) => {
                    Some(MaybePruned::<Input>::Pruned(digest).try_into()?)
                }
            },
            // Translate MaybePruned<Option<Output>>> to Option<MaybePruned<Output>>.
            output: match value.output {
                MaybePruned::Value(optional) => optional
                    .map(|output| MaybePruned::Value(output).try_into())
                    .transpose()?,
                MaybePruned::Pruned(digest) => {
                    Some(MaybePruned::<Output>::Pruned(digest).try_into()?)
                }
            },
        })
    }
}

impl TryFrom<pb::core::ReceiptClaim> for ReceiptClaim {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::ReceiptClaim) -> Result<Self> {
        Ok(Self {
            pre: value
                .pre
                .ok_or_else(|| malformed_err("ReceiptClaim.pre"))?
                .try_into()?,
            post: value
                .post
                .ok_or_else(|| malformed_err("ReceiptClaim.post"))?
                .try_into()?,
            exit_code: value
                .exit_code
                .ok_or_else(|| malformed_err("ReceiptClaim.exit_code"))?
                .try_into()?,
            // Translate Option<MaybePruned<Input>> to MaybePruned<Option<Input>>.
            input: match value.input {
                None => MaybePruned::Value(None),
                Some(x) => match MaybePruned::<Input>::try_from(x)? {
                    #[allow(unreachable_patterns)]
                    MaybePruned::Value(input) => MaybePruned::Value(Some(input)),
                    MaybePruned::Pruned(digest) => MaybePruned::Pruned(digest),
                },
            },
            // Translate Option<MaybePruned<Output>> to MaybePruned<Option<Output>>.
            output: match value.output {
                None => MaybePruned::Value(None),
                Some(x) => match MaybePruned::<Output>::try_from(x)? {
                    MaybePruned::Value(output) => MaybePruned::Value(Some(output)),
                    MaybePruned::Pruned(digest) => MaybePruned::Pruned(digest),
                },
            },
        })
    }
}

impl Name for pb::core::SystemState {
    const PACKAGE: &'static str = "risc0.protos.core";
    const NAME: &'static str = "SystemState";
}

impl AssociatedMessage for SystemState {
    type Message = pb::core::SystemState;
}

impl TryFrom<SystemState> for pb::core::SystemState {
    type Error = anyhow::Error;

    fn try_from(value: SystemState) -> Result<Self> {
        Ok(Self {
            pc: value.pc,
            merkle_root: Some(value.merkle_root.into()),
        })
    }
}

impl TryFrom<pb::core::SystemState> for SystemState {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::SystemState) -> Result<Self> {
        Ok(Self {
            pc: value.pc,
            merkle_root: value
                .merkle_root
                .ok_or_else(|| malformed_err("SystemState.merkle_root"))?
                .try_into()?,
        })
    }
}

impl Name for pb::core::Input {
    const PACKAGE: &'static str = "risc0.protos.core";
    const NAME: &'static str = "Input";
}

impl AssociatedMessage for Input {
    type Message = pb::core::Input;
}

impl TryFrom<Input> for pb::core::Input {
    type Error = anyhow::Error;

    fn try_from(value: Input) -> Result<Self> {
        match value.x { /* unreachable  */ }
    }
}

impl TryFrom<pb::core::Input> for Input {
    type Error = anyhow::Error;

    fn try_from(_value: pb::core::Input) -> Result<Self> {
        Err(malformed_err("Input"))
    }
}

impl Name for pb::core::Output {
    const PACKAGE: &'static str = "risc0.protos.core";
    const NAME: &'static str = "Output";
}

impl AssociatedMessage for Output {
    type Message = pb::core::Output;
}

impl TryFrom<Output> for pb::core::Output {
    type Error = anyhow::Error;

    fn try_from(value: Output) -> Result<Self> {
        Ok(Self {
            journal: Some(value.journal.try_into()?),
            assumptions: Some(value.assumptions.try_into()?),
        })
    }
}

impl TryFrom<pb::core::Output> for Output {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::Output) -> Result<Self> {
        Ok(Self {
            journal: value
                .journal
                .ok_or_else(|| malformed_err("Output.journal"))?
                .try_into()?,
            assumptions: value
                .assumptions
                .ok_or_else(|| malformed_err("Output.assumptions"))?
                .try_into()?,
        })
    }
}

impl Name for pb::core::Assumption {
    const PACKAGE: &'static str = "risc0.protos.core";
    const NAME: &'static str = "Assumption";
}

impl AssociatedMessage for Assumption {
    type Message = pb::core::Assumption;
}

impl TryFrom<Assumption> for pb::core::Assumption {
    type Error = anyhow::Error;

    fn try_from(value: Assumption) -> Result<Self> {
        Ok(Self {
            claim: Some(value.claim.into()),
            control_root: Some(value.control_root.into()),
        })
    }
}

impl TryFrom<pb::core::Assumption> for Assumption {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::Assumption) -> Result<Self> {
        Ok(Self {
            claim: value
                .claim
                .ok_or_else(|| malformed_err("Assumption.claim"))?
                .try_into()?,
            control_root: value
                .control_root
                .ok_or_else(|| malformed_err("Assumption.control_root"))?
                .try_into()?,
        })
    }
}

impl Name for pb::core::Assumptions {
    const PACKAGE: &'static str = "risc0.protos.core";
    const NAME: &'static str = "Assumptions";
}

impl AssociatedMessage for Assumptions {
    type Message = pb::core::Assumptions;
}

impl TryFrom<Assumptions> for pb::core::Assumptions {
    type Error = anyhow::Error;

    fn try_from(value: Assumptions) -> Result<Self> {
        Ok(Self {
            inner: value
                .0
                .into_iter()
                .map(|a| a.try_into())
                .collect::<Result<_>>()?,
        })
    }
}

impl TryFrom<pb::core::Assumptions> for Assumptions {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::Assumptions) -> Result<Self> {
        Ok(Self(
            value
                .inner
                .into_iter()
                .map(|a| a.try_into())
                .collect::<Result<Vec<_>>>()?,
        ))
    }
}

trait AssociatedMessage {
    type Message: Message;
}

impl<T> TryFrom<MaybePruned<T>> for pb::core::MaybePruned
where
    T: AssociatedMessage + serde::Serialize + Clone,
    T::Message: TryFrom<T, Error = anyhow::Error> + Sized,
{
    type Error = anyhow::Error;

    fn try_from(value: MaybePruned<T>) -> Result<Self> {
        Ok(Self {
            kind: Some(match value {
                MaybePruned::Value(inner) => pb::core::maybe_pruned::Kind::Value(
                    T::Message::try_from(inner)?.encode_to_vec(),
                ),
                MaybePruned::Pruned(digest) => pb::core::maybe_pruned::Kind::Pruned(digest.into()),
            }),
        })
    }
}

impl<T> TryFrom<pb::core::MaybePruned> for MaybePruned<T>
where
    T: AssociatedMessage + serde::Serialize + Clone,
    T::Message: TryInto<T, Error = anyhow::Error> + Default,
{
    type Error = anyhow::Error;

    fn try_from(value: pb::core::MaybePruned) -> Result<Self> {
        Ok(
            match value
                .kind
                .ok_or_else(|| malformed_err("MaybePruned<T>.kind"))?
            {
                pb::core::maybe_pruned::Kind::Value(inner) => {
                    Self::Value(T::Message::decode(inner.as_slice())?.try_into()?)
                }
                pb::core::maybe_pruned::Kind::Pruned(digest) => Self::Pruned(digest.try_into()?),
            },
        )
    }
}

// Specialized implementation for Vec<u8> for work around challenges getting the
// generic implementation above to work for Vec<u8>.
impl TryFrom<MaybePruned<Vec<u8>>> for pb::core::MaybePruned {
    type Error = anyhow::Error;

    fn try_from(value: MaybePruned<Vec<u8>>) -> Result<Self> {
        Ok(Self {
            kind: Some(match value {
                MaybePruned::Value(inner) => {
                    pb::core::maybe_pruned::Kind::Value(inner.encode_to_vec())
                }
                MaybePruned::Pruned(digest) => pb::core::maybe_pruned::Kind::Pruned(digest.into()),
            }),
        })
    }
}

impl TryFrom<pb::core::MaybePruned> for MaybePruned<Vec<u8>> {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::MaybePruned) -> Result<Self> {
        Ok(
            match value
                .kind
                .ok_or_else(|| malformed_err("MaybePruned<Vec<u8>>.kind"))?
            {
                pb::core::maybe_pruned::Kind::Value(inner) => {
                    Self::Value(<Vec<u8> as Message>::decode(inner.as_slice())?)
                }
                pb::core::maybe_pruned::Kind::Pruned(digest) => Self::Pruned(digest.try_into()?),
            },
        )
    }
}

impl TryFrom<MaybePruned<Unknown>> for pb::core::MaybePruned {
    type Error = anyhow::Error;

    fn try_from(value: MaybePruned<Unknown>) -> Result<Self> {
        Ok(Self {
            kind: Some(match value {
                #[allow(unreachable_patterns)]
                MaybePruned::Value(inner) => {
                    match inner { /* unreachable */ }
                }
                MaybePruned::Pruned(digest) => pb::core::maybe_pruned::Kind::Pruned(digest.into()),
            }),
        })
    }
}

impl TryFrom<pb::core::MaybePruned> for MaybePruned<Unknown> {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::MaybePruned) -> Result<Self> {
        Ok(
            match value
                .kind
                .ok_or_else(|| malformed_err("MaybePruned<Unknown>.kind"))?
            {
                pb::core::maybe_pruned::Kind::Value(_) => {
                    Err(malformed_err("MaybePruned<Unknown>.value"))?
                }
                pb::core::maybe_pruned::Kind::Pruned(digest) => Self::Pruned(digest.try_into()?),
            },
        )
    }
}

impl TryFrom<pb::api::ProveZkrRequest> for ProveZkrRequest {
    type Error = anyhow::Error;

    fn try_from(value: pb::api::ProveZkrRequest) -> Result<Self> {
        Ok(Self {
            claim_digest: value
                .claim_digest
                .ok_or_else(|| malformed_err("ProveZkrRequest.claim_digest"))?
                .try_into()?,
            control_id: value
                .control_id
                .ok_or_else(|| malformed_err("ProveZkrRequest.control_id"))?
                .try_into()?,
            input: value.input,
        })
    }
}

impl TryFrom<pb::api::ProveKeccakRequest> for ProveKeccakRequest {
    type Error = anyhow::Error;

    fn try_from(value: pb::api::ProveKeccakRequest) -> Result<Self> {
        let input = try_keccak_bytes_to_input(&value.input)?;

        Ok(Self {
            claim_digest: value
                .claim_digest
                .ok_or_else(|| malformed_err("ProveKeccakRequest.claim_digest"))?
                .try_into()?,
            po2: value.po2 as usize,
            control_root: value
                .control_root
                .ok_or_else(|| malformed_err("ProveKeccakRequest.control_root"))?
                .try_into()?,
            input,
        })
    }
}

pub(crate) fn keccak_input_to_bytes(input: &[KeccakState]) -> Vec<u8> {
    bytemuck::cast_slice(input).to_vec()
}

pub(crate) fn try_keccak_bytes_to_input(input: &[u8]) -> Result<Vec<KeccakState>> {
    let chunks = input.chunks_exact(std::mem::size_of::<KeccakState>());
    if !chunks.remainder().is_empty() {
        bail!("Input length must be a multiple of KeccakState size");
    }
    chunks
        .map(bytemuck::try_pod_read_unaligned)
        .collect::<Result<_, _>>()
        .map_err(|e| anyhow!("Failed to convert input bytes to KeccakState: {}", e))
}

#[test]
fn test_keccak_bytes_to_input_alignment() {
    // Create a buffer with extra padding at the start to test different alignments
    let padding = 16; // We should hit all alignments by cycling through offsets 0-15
    let keccak_states = 3; // Test multiple KeccakStates
    let state_size = std::mem::size_of::<KeccakState>();
    let mut test_buffer = vec![0u8; padding + (keccak_states * state_size)];

    // Fill with recognizable pattern
    for (i, byte) in test_buffer.iter_mut().enumerate() {
        *byte = (i % 256) as u8;
    }

    // Test each offset
    for offset in 0..padding {
        let aligned_slice = &test_buffer[offset..][..(keccak_states * state_size)];
        let result = try_keccak_bytes_to_input(aligned_slice);

        assert!(result.is_ok(), "Failed to parse at offset {offset}");
        let states = result.unwrap();
        assert_eq!(
            states.len(),
            keccak_states,
            "Wrong number of states at offset {offset}",
        );

        // Verify roundtrip
        let bytes = keccak_input_to_bytes(&states);
        assert_eq!(bytes, aligned_slice, "Roundtrip failed at offset {offset}",);
    }
}

#[test]
fn test_keccak_bytes_to_input_invalid_size() {
    // Test with a buffer that's not a multiple of KeccakState size
    let invalid_size = std::mem::size_of::<KeccakState>() + 1;
    let buffer = vec![0u8; invalid_size];
    let result = try_keccak_bytes_to_input(&buffer);
    assert!(result.is_err(), "Should fail with invalid size");
}
