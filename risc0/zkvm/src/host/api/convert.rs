// Copyright 2024 RISC Zero, Inc.
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

use std::{collections::BTreeMap, path::PathBuf};

use anyhow::{anyhow, bail, Result};
use prost::{Message, Name};
use risc0_binfmt::{MemoryImage, PageTableInfo, SystemState};
use risc0_zkp::core::digest::Digest;

use super::{malformed_err, path_to_string, pb, Asset, AssetRequest};
use crate::{
    host::{
        receipt::{decode_receipt_claim_from_seal, CompositeReceipt, InnerReceipt, SegmentReceipt},
        recursion::SuccinctReceipt,
    },
    Assumptions, ExitCode, Journal, MaybePruned, Output, ProveInfo, ProverOpts, Receipt,
    ReceiptClaim, ReceiptKind, SessionStats, TraceEvent,
};

mod ver {
    use super::pb::base::CompatVersion;

    pub const MEMORY_IMAGE: CompatVersion = CompatVersion { value: 1 };
    pub const RECEIPT: CompatVersion = CompatVersion { value: 1 };
    pub const SEGMENT_RECEIPT: CompatVersion = CompatVersion { value: 1 };
    pub const SUCCINCT_RECEIPT: CompatVersion = CompatVersion { value: 1 };
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
            },
        })
    }
}

impl TryFrom<SuccinctReceipt> for Asset {
    type Error = anyhow::Error;

    fn try_from(succinct_receipt: SuccinctReceipt) -> Result<Self> {
        Ok(Asset::Inline(bincode::serialize(&succinct_receipt)?.into()))
    }
}

impl TryFrom<SegmentReceipt> for Asset {
    type Error = anyhow::Error;

    fn try_from(segment_receipt: SegmentReceipt) -> Result<Self> {
        Ok(Asset::Inline(bincode::serialize(&segment_receipt)?.into()))
    }
}

impl TryFrom<pb::api::Asset> for Asset {
    type Error = anyhow::Error;

    fn try_from(value: pb::api::Asset) -> Result<Self> {
        Ok(match value.kind.ok_or(malformed_err())? {
            pb::api::asset::Kind::Inline(bytes) => Asset::Inline(bytes.into()),
            pb::api::asset::Kind::Path(path) => Asset::Path(PathBuf::from(path)),
        })
    }
}

impl From<TraceEvent> for pb::api::TraceEvent {
    fn from(event: TraceEvent) -> Self {
        match event {
            TraceEvent::InstructionStart { cycle, pc, insn } => Self {
                kind: Some(pb::api::trace_event::Kind::InsnStart(
                    pb::api::trace_event::InstructionStart { cycle, pc, insn },
                )),
            },
            TraceEvent::RegisterSet { idx, value } => Self {
                kind: Some(pb::api::trace_event::Kind::RegisterSet(
                    pb::api::trace_event::RegisterSet {
                        idx: idx as u32,
                        value,
                    },
                )),
            },
            TraceEvent::MemorySet { addr, region } => Self {
                kind: Some(pb::api::trace_event::Kind::MemorySet(
                    pb::api::trace_event::MemorySet {
                        addr,
                        value: 0,
                        region,
                    },
                )),
            },
        }
    }
}

impl TryFrom<pb::api::TraceEvent> for TraceEvent {
    type Error = anyhow::Error;

    fn try_from(event: pb::api::TraceEvent) -> Result<Self> {
        Ok(match event.kind.ok_or(malformed_err())? {
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
        })
    }
}

impl From<ExitCode> for pb::base::ExitCode {
    fn from(value: ExitCode) -> Self {
        Self {
            kind: Some(match value {
                ExitCode::SystemSplit => pb::base::exit_code::Kind::SystemSplit(()),
                ExitCode::SessionLimit => pb::base::exit_code::Kind::SessionLimit(()),
                ExitCode::Paused(code) => pb::base::exit_code::Kind::Paused(code),
                ExitCode::Halted(code) => pb::base::exit_code::Kind::Halted(code),
            }),
        }
    }
}

impl TryFrom<pb::base::ExitCode> for ExitCode {
    type Error = anyhow::Error;

    fn try_from(value: pb::base::ExitCode) -> Result<Self> {
        Ok(match value.kind.ok_or(malformed_err())? {
            pb::base::exit_code::Kind::Halted(code) => Self::Halted(code),
            pb::base::exit_code::Kind::Paused(code) => Self::Paused(code),
            pb::base::exit_code::Kind::SystemSplit(_) => Self::SystemSplit,
            pb::base::exit_code::Kind::SessionLimit(_) => Self::SessionLimit,
        })
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

impl From<pb::api::ProverOpts> for ProverOpts {
    fn from(opts: pb::api::ProverOpts) -> Self {
        Self {
            hashfn: opts.hashfn,
            prove_guest_errors: opts.prove_guest_errors,
            receipt_kind: match opts.receipt_kind {
                0 => ReceiptKind::Composite,
                1 => ReceiptKind::Succinct,
                2 => ReceiptKind::Compact,
                value => panic!("Unknown receipt kind number: {value}"),
            },
        }
    }
}

impl From<ProverOpts> for pb::api::ProverOpts {
    fn from(opts: ProverOpts) -> Self {
        Self {
            hashfn: opts.hashfn,
            prove_guest_errors: opts.prove_guest_errors,
            receipt_kind: opts.receipt_kind as i32,
        }
    }
}

impl From<MemoryImage> for pb::core::MemoryImage {
    fn from(value: MemoryImage) -> Self {
        let pages = value
            .pages
            .iter()
            .map(|(addr, data)| pb::core::PageEntry {
                addr: *addr,
                data: data.clone(),
            })
            .collect();
        Self {
            version: Some(ver::MEMORY_IMAGE),
            info: Some(value.info.into()),
            pc: value.pc,
            pages,
        }
    }
}

impl TryFrom<pb::core::MemoryImage> for MemoryImage {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::MemoryImage) -> Result<Self> {
        let version = value.version.ok_or(malformed_err())?.value;
        if version > ver::MEMORY_IMAGE.value {
            bail!("Incompatible MemoryImage version: {version}");
        }
        let pages = BTreeMap::from_iter(
            value
                .pages
                .into_iter()
                .map(|entry| (entry.addr, entry.data)),
        );
        Ok(Self {
            pages,
            info: value.info.ok_or(malformed_err())?.try_into()?,
            pc: value.pc,
        })
    }
}

impl From<PageTableInfo> for pb::core::PageTableInfo {
    fn from(value: PageTableInfo) -> Self {
        Self {
            page_size: value.page_size,
            page_table_addr: value.page_table_addr,
        }
    }
}

impl TryFrom<pb::core::PageTableInfo> for PageTableInfo {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::PageTableInfo) -> Result<Self> {
        Self::new(value.page_table_addr, value.page_size)
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
        })
    }
}

impl From<ProveInfo> for pb::core::ProveInfo {
    fn from(value: ProveInfo) -> Self {
        Self {
            receipt: Some(value.receipt.into()),
            stats: Some(value.stats.into()),
        }
    }
}

impl TryFrom<pb::core::ProveInfo> for ProveInfo {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::ProveInfo) -> Result<Self> {
        Ok(Self {
            receipt: value.receipt.ok_or(malformed_err())?.try_into()?,
            stats: value.stats.ok_or(malformed_err())?.try_into()?,
        })
    }
}

impl From<Receipt> for pb::core::Receipt {
    fn from(value: Receipt) -> Self {
        Self {
            version: Some(ver::RECEIPT),
            inner: Some(value.inner.into()),
            journal: value.journal.bytes,
        }
    }
}

impl TryFrom<pb::core::Receipt> for Receipt {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::Receipt) -> Result<Self> {
        let version = value.version.ok_or(malformed_err())?.value;
        if version > ver::RECEIPT.value {
            bail!("Incompatible Receipt version: {version}");
        }
        Ok(Self {
            inner: value.inner.ok_or(malformed_err())?.try_into()?,
            journal: Journal::new(value.journal),
        })
    }
}

impl From<SegmentReceipt> for pb::core::SegmentReceipt {
    fn from(value: SegmentReceipt) -> Self {
        Self {
            version: Some(ver::SEGMENT_RECEIPT),
            seal: value.get_seal_bytes(),
            index: value.index,
            hashfn: value.hashfn,
            claim: Some(value.claim.into()),
        }
    }
}

impl TryFrom<pb::core::SegmentReceipt> for SegmentReceipt {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::SegmentReceipt) -> Result<Self> {
        const WORD_SIZE: usize = std::mem::size_of::<u32>();

        let version = value.version.ok_or(malformed_err())?.value;
        if version > ver::SEGMENT_RECEIPT.value {
            bail!("Incompatible SegmentReceipt version: {version}");
        }

        let mut seal = Vec::with_capacity(value.seal.len() / WORD_SIZE);
        for chunk in value.seal.chunks_exact(WORD_SIZE) {
            let word = u32::from_le_bytes(chunk.try_into()?);
            seal.push(word);
        }

        // If the claim field is not included, decode claim from the seal.
        let claim = value
            .claim
            .map(|m| m.try_into())
            .unwrap_or_else(|| Ok(decode_receipt_claim_from_seal(&seal)?))?;

        Ok(Self {
            claim,
            seal,
            index: value.index,
            hashfn: value.hashfn,
        })
    }
}

impl From<SuccinctReceipt> for pb::core::SuccinctReceipt {
    fn from(value: SuccinctReceipt) -> Self {
        Self {
            version: Some(ver::SUCCINCT_RECEIPT),
            seal: value.get_seal_bytes(),
            control_id: Some(value.control_id.into()),
            claim: Some(value.claim.into()),
        }
    }
}

impl TryFrom<pb::core::SuccinctReceipt> for SuccinctReceipt {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::SuccinctReceipt) -> Result<Self> {
        const WORD_SIZE: usize = std::mem::size_of::<u32>();

        let version = value.version.ok_or(malformed_err())?.value;
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
            control_id: value.control_id.ok_or(malformed_err())?.try_into()?,
            claim: value.claim.ok_or(malformed_err())?.try_into()?,
        })
    }
}

impl From<InnerReceipt> for pb::core::InnerReceipt {
    fn from(value: InnerReceipt) -> Self {
        Self {
            kind: Some(match value {
                InnerReceipt::Composite(inner) => {
                    pb::core::inner_receipt::Kind::Composite(inner.into())
                }
                InnerReceipt::Succinct(inner) => {
                    pb::core::inner_receipt::Kind::Succinct(inner.into())
                }
                InnerReceipt::Fake { claim } => {
                    pb::core::inner_receipt::Kind::Fake(pb::core::FakeReceipt {
                        claim: Some(claim.into()),
                    })
                }
                InnerReceipt::Compact(_) => unimplemented!(),
            }),
        }
    }
}

impl TryFrom<pb::core::InnerReceipt> for InnerReceipt {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::InnerReceipt) -> Result<Self> {
        Ok(match value.kind.ok_or(malformed_err())? {
            pb::core::inner_receipt::Kind::Composite(inner) => Self::Composite(inner.try_into()?),
            pb::core::inner_receipt::Kind::Groth16(_) => unimplemented!(),
            pb::core::inner_receipt::Kind::Succinct(inner) => Self::Succinct(inner.try_into()?),
            pb::core::inner_receipt::Kind::Fake(inner) => Self::Fake {
                claim: inner.claim.ok_or(malformed_err())?.try_into()?,
            },
        })
    }
}

impl From<CompositeReceipt> for pb::core::CompositeReceipt {
    fn from(value: CompositeReceipt) -> Self {
        Self {
            segments: value.segments.into_iter().map(|s| s.into()).collect(),
            assumptions: value.assumptions.into_iter().map(|a| a.into()).collect(),
            journal_digest: value.journal_digest.map(|d| d.into()),
        }
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
            assumptions: value
                .assumptions
                .into_iter()
                .map(|a| a.try_into())
                .collect::<Result<Vec<_>>>()?,
            journal_digest: value.journal_digest.map(|d| d.try_into()).transpose()?,
        })
    }
}

impl From<Digest> for pb::core::Digest {
    fn from(value: Digest) -> Self {
        Self {
            words: value.as_words().to_vec(),
        }
    }
}

impl TryFrom<pb::core::Digest> for Digest {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::Digest) -> Result<Self> {
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

impl From<ReceiptClaim> for pb::core::ReceiptClaim {
    fn from(value: ReceiptClaim) -> Self {
        Self {
            pre: Some(value.pre.into()),
            post: Some(value.post.into()),
            exit_code: Some(value.exit_code.into()),
            input: Some(value.input.into()),
            // Translate MaybePruned<Option<Output>>> to Option<MaybePruned<Output>>.
            output: match value.output {
                MaybePruned::Value(optional) => {
                    optional.map(|output| MaybePruned::Value(output).into())
                }
                MaybePruned::Pruned(digest) => Some(MaybePruned::<Output>::Pruned(digest).into()),
            },
        }
    }
}

impl TryFrom<pb::core::ReceiptClaim> for ReceiptClaim {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::ReceiptClaim) -> Result<Self> {
        Ok(Self {
            pre: value.pre.ok_or(malformed_err())?.try_into()?,
            post: value.post.ok_or(malformed_err())?.try_into()?,
            exit_code: value.exit_code.ok_or(malformed_err())?.try_into()?,
            input: value.input.ok_or(malformed_err())?.try_into()?,
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

impl From<SystemState> for pb::core::SystemState {
    fn from(value: SystemState) -> Self {
        Self {
            pc: value.pc,
            merkle_root: Some(value.merkle_root.into()),
        }
    }
}

impl TryFrom<pb::core::SystemState> for SystemState {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::SystemState) -> Result<Self> {
        Ok(Self {
            pc: value.pc,
            merkle_root: value.merkle_root.ok_or(malformed_err())?.try_into()?,
        })
    }
}

impl Name for pb::core::Output {
    const PACKAGE: &'static str = "risc0.protos.core";
    const NAME: &'static str = "Output";
}

impl AssociatedMessage for Output {
    type Message = pb::core::Output;
}

impl From<Output> for pb::core::Output {
    fn from(value: Output) -> Self {
        Self {
            journal: Some(value.journal.into()),
            assumptions: Some(value.assumptions.into()),
        }
    }
}

impl TryFrom<pb::core::Output> for Output {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::Output) -> Result<Self> {
        Ok(Self {
            journal: value.journal.ok_or(malformed_err())?.try_into()?,
            assumptions: value.assumptions.ok_or(malformed_err())?.try_into()?,
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

impl From<Assumptions> for pb::core::Assumptions {
    fn from(value: Assumptions) -> Self {
        Self {
            inner: value.0.into_iter().map(|a| a.into()).collect(),
        }
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

impl<T> From<MaybePruned<T>> for pb::core::MaybePruned
where
    T: AssociatedMessage + serde::Serialize + Clone,
    T::Message: From<T> + Sized,
{
    fn from(value: MaybePruned<T>) -> Self {
        Self {
            kind: Some(match value {
                MaybePruned::Value(inner) => {
                    pb::core::maybe_pruned::Kind::Value(T::Message::from(inner).encode_to_vec())
                }
                MaybePruned::Pruned(digest) => pb::core::maybe_pruned::Kind::Pruned(digest.into()),
            }),
        }
    }
}

impl<T> TryFrom<pb::core::MaybePruned> for MaybePruned<T>
where
    T: AssociatedMessage + serde::Serialize + Clone,
    T::Message: TryInto<T, Error = anyhow::Error> + Default,
{
    type Error = anyhow::Error;

    fn try_from(value: pb::core::MaybePruned) -> Result<Self> {
        Ok(match value.kind.ok_or(malformed_err())? {
            pb::core::maybe_pruned::Kind::Value(inner) => {
                Self::Value(T::Message::decode(inner.as_slice())?.try_into()?)
            }
            pb::core::maybe_pruned::Kind::Pruned(digest) => Self::Pruned(digest.try_into()?),
        })
    }
}

// Specialized implementation for Vec<u8> for work around challenges getting the
// generic implementation above to work for Vec<u8>.
impl From<MaybePruned<Vec<u8>>> for pb::core::MaybePruned {
    fn from(value: MaybePruned<Vec<u8>>) -> Self {
        Self {
            kind: Some(match value {
                MaybePruned::Value(inner) => {
                    pb::core::maybe_pruned::Kind::Value(inner.encode_to_vec())
                }
                MaybePruned::Pruned(digest) => pb::core::maybe_pruned::Kind::Pruned(digest.into()),
            }),
        }
    }
}

impl TryFrom<pb::core::MaybePruned> for MaybePruned<Vec<u8>> {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::MaybePruned) -> Result<Self> {
        Ok(match value.kind.ok_or(malformed_err())? {
            pb::core::maybe_pruned::Kind::Value(inner) => {
                Self::Value(<Vec<u8> as Message>::decode(inner.as_slice())?)
            }
            pb::core::maybe_pruned::Kind::Pruned(digest) => Self::Pruned(digest.try_into()?),
        })
    }
}
