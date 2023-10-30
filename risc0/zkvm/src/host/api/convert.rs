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

use std::{collections::BTreeMap, path::PathBuf};

use anyhow::{anyhow, bail, Result};
use prost::Message;
use risc0_binfmt::{MemoryImage, PageTableInfo, SystemState};
use risc0_zkp::core::digest::Digest;

use super::{malformed_err, path_to_string, pb, Asset, AssetRequest, Binary, BinaryKind};
use crate::{
    host::recursion::SuccinctReceipt, ExitCode, InnerReceipt, Journal, ProverOpts, Receipt,
    ReceiptMetadata, SegmentReceipt, SegmentReceipts, TraceEvent,
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
                value: event.value,
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
                ExitCode::Fault => pb::base::exit_code::Kind::Fault(()),
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
            pb::base::exit_code::Kind::Fault(_) => Self::Fault,
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
        }
    }
}

impl From<ProverOpts> for pb::api::ProverOpts {
    fn from(opts: ProverOpts) -> Self {
        Self {
            hashfn: opts.hashfn,
        }
    }
}

impl TryFrom<Binary> for pb::api::Binary {
    type Error = anyhow::Error;

    fn try_from(binary: Binary) -> Result<Self> {
        Ok(Self {
            kind: match binary.kind {
                BinaryKind::Elf => pb::api::binary::Kind::Elf,
                BinaryKind::Image => pb::api::binary::Kind::Image,
            } as i32,
            asset: Some(binary.asset.try_into()?),
        })
    }
}

impl From<MemoryImage> for Binary {
    fn from(image: MemoryImage) -> Self {
        let image_pb: pb::core::MemoryImage = image.into();
        let image_bytes = image_pb.encode_to_vec();
        Self {
            kind: BinaryKind::Image,
            asset: Asset::Inline(image_bytes.into()),
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
        Ok(Self::new(value.page_table_addr, value.page_size))
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
            seal: value.get_seal_bytes().into(),
            index: value.index,
            hashfn: value.hashfn,
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

        Ok(Self {
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
            meta: Some(value.meta.into()),
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
            meta: value.meta.ok_or(malformed_err())?.try_into()?,
        })
    }
}

impl From<InnerReceipt> for pb::core::InnerReceipt {
    fn from(value: InnerReceipt) -> Self {
        Self {
            kind: Some(match value {
                InnerReceipt::Flat(inner) => pb::core::inner_receipt::Kind::Flat(inner.into()),
                InnerReceipt::Succinct(inner) => {
                    pb::core::inner_receipt::Kind::Succinct(inner.into())
                }
                InnerReceipt::Fake => pb::core::inner_receipt::Kind::Fake(pb::core::FakeReceipt {}),
            }),
        }
    }
}

impl TryFrom<pb::core::InnerReceipt> for InnerReceipt {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::InnerReceipt) -> Result<Self> {
        Ok(match value.kind.ok_or(malformed_err())? {
            pb::core::inner_receipt::Kind::Flat(inner) => Self::Flat(inner.try_into()?),
            pb::core::inner_receipt::Kind::Succinct(inner) => Self::Succinct(inner.try_into()?),
            pb::core::inner_receipt::Kind::Fake(_) => Self::Fake,
        })
    }
}

impl From<SegmentReceipts> for pb::core::SegmentReceipts {
    fn from(value: SegmentReceipts) -> Self {
        Self {
            inner: value.0.iter().map(|x| (*x).clone().into()).collect(),
        }
    }
}

impl TryFrom<pb::core::SegmentReceipts> for SegmentReceipts {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::SegmentReceipts) -> Result<Self> {
        let mut inner = Vec::with_capacity(value.inner.len());
        for item in value.inner {
            inner.push(item.try_into()?);
        }
        Ok(Self(inner))
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

impl From<ReceiptMetadata> for pb::core::ReceiptMetadata {
    fn from(value: ReceiptMetadata) -> Self {
        Self {
            pre: Some(value.pre.into()),
            post: Some(value.post.into()),
            exit_code: Some(value.exit_code.into()),
            input: Some(value.input.into()),
            output: Some(value.output.into()),
        }
    }
}

impl TryFrom<pb::core::ReceiptMetadata> for ReceiptMetadata {
    type Error = anyhow::Error;

    fn try_from(value: pb::core::ReceiptMetadata) -> Result<Self> {
        Ok(Self {
            pre: value.pre.ok_or(malformed_err())?.try_into()?,
            post: value.post.ok_or(malformed_err())?.try_into()?,
            exit_code: value.exit_code.ok_or(malformed_err())?.try_into()?,
            input: value.input.ok_or(malformed_err())?.try_into()?,
            output: value.output.ok_or(malformed_err())?.try_into()?,
        })
    }
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
