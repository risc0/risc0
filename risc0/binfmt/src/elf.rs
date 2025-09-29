// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

extern crate alloc;

use alloc::{collections::BTreeMap, vec, vec::Vec};

use anyhow::{Context, Result, anyhow, bail, ensure};
use elf::{ElfBytes, endian::LittleEndian, file::Class};
use risc0_zkp::core::{digest::Digest, hash::sha::Impl};
use risc0_zkvm_platform::WORD_SIZE;
use serde::{Deserialize, Serialize};

use crate::{ByteAddr, Digestible as _, KERNEL_START_ADDR, MemoryImage, SystemState};

const USER_START_ADDR: ByteAddr = ByteAddr(0x0001_0000);

const SUSPEND_PC_ADDR: ByteAddr = ByteAddr(0xffff_0210);
const SUSPEND_MODE_ADDR: ByteAddr = ByteAddr(0xffff_0214);

/// A RISC Zero program
pub struct Program {
    /// The entrypoint of the program
    pub(crate) entry: u32,

    /// The initial memory image
    pub(crate) image: BTreeMap<u32, u32>,
}

impl Program {
    /// Initialize a RISC Zero Program from an appropriate ELF file
    pub fn load_elf(input: &[u8], max_mem: u32) -> Result<Program> {
        let mut image: BTreeMap<u32, u32> = BTreeMap::new();
        let elf = ElfBytes::<LittleEndian>::minimal_parse(input)
            .map_err(|err| anyhow!("Elf parse error: {err}"))?;
        if elf.ehdr.class != Class::ELF32 {
            bail!("Not a 32-bit ELF");
        }
        if elf.ehdr.e_machine != elf::abi::EM_RISCV {
            bail!("Invalid machine type, must be RISC-V");
        }
        if elf.ehdr.e_type != elf::abi::ET_EXEC {
            bail!("Invalid ELF type, must be executable");
        }
        let entry: u32 = elf
            .ehdr
            .e_entry
            .try_into()
            .map_err(|err| anyhow!("e_entry was larger than 32 bits. {err}"))?;
        if entry >= max_mem || !entry.is_multiple_of(WORD_SIZE as u32) {
            bail!("Invalid entrypoint");
        }
        let segments = elf
            .segments()
            .ok_or_else(|| anyhow!("Missing segment table"))?;
        if segments.len() > 256 {
            bail!("Too many program headers");
        }
        for segment in segments.iter().filter(|x| x.p_type == elf::abi::PT_LOAD) {
            let file_size: u32 = segment
                .p_filesz
                .try_into()
                .map_err(|err| anyhow!("filesize was larger than 32 bits. {err}"))?;
            if file_size >= max_mem {
                bail!("Invalid segment file_size");
            }
            let mem_size: u32 = segment
                .p_memsz
                .try_into()
                .map_err(|err| anyhow!("mem_size was larger than 32 bits {err}"))?;
            if mem_size >= max_mem {
                bail!("Invalid segment mem_size");
            }
            let vaddr: u32 = segment
                .p_vaddr
                .try_into()
                .map_err(|err| anyhow!("vaddr is larger than 32 bits. {err}"))?;
            if !vaddr.is_multiple_of(WORD_SIZE as u32) {
                bail!("vaddr {vaddr:08x} is unaligned");
            }
            let offset: u32 = segment
                .p_offset
                .try_into()
                .map_err(|err| anyhow!("offset is larger than 32 bits. {err}"))?;
            for i in (0..mem_size).step_by(WORD_SIZE) {
                let addr = vaddr.checked_add(i).context("Invalid segment vaddr")?;
                if addr >= max_mem {
                    bail!(
                        "Address [0x{addr:08x}] exceeds maximum address for guest programs [0x{max_mem:08x}]"
                    );
                }
                if i >= file_size {
                    // Past the file size, all zeros.
                    image.insert(addr, 0);
                } else {
                    let mut word = 0;
                    // Don't read past the end of the file.
                    let len = core::cmp::min(file_size - i, WORD_SIZE as u32);
                    for j in 0..len {
                        let offset = (offset + i + j) as usize;
                        let byte = input.get(offset).context("Invalid segment offset")?;
                        word |= (*byte as u32) << (j * 8);
                    }
                    image.insert(addr, word);
                }
            }
        }
        Ok(Program::new_from_entry_and_image(entry, image))
    }

    /// Create `Program` from given entry-point and image map
    pub fn new_from_entry_and_image(entry: u32, image: BTreeMap<u32, u32>) -> Self {
        Self { entry, image }
    }

    /// The size of the image in a count of words
    pub fn size_in_words(&self) -> usize {
        self.image.len()
    }

    /// Read a word from the image
    pub fn read_u32(&self, address: &u32) -> Option<u32> {
        self.image.get(address).copied()
    }

    pub(crate) fn prepare_user(&mut self) {
        self.image.insert(USER_START_ADDR.0, self.entry);
    }

    pub(crate) fn prepare_kernel(&mut self, user: Option<&mut Program>) {
        if let Some(user) = user {
            self.image.append(&mut user.image);
        }
        self.image.insert(SUSPEND_PC_ADDR.0, self.entry);
        self.image.insert(SUSPEND_MODE_ADDR.0, 1);
    }
    /// Write a word to the image
    pub fn write_u32(&mut self, address: u32, value: u32) {
        self.image.insert(address, value);
    }
}

const MAGIC: &[u8] = b"R0BF"; // RISC Zero Binary Format
const BINARY_FORMAT_VERSION: u32 = 1; // RISC Zero Binary Format Version Number

#[derive(Serialize, Deserialize)]
enum ProgramBinaryHeaderValueOnDisk {
    AbiVersion(AbiKind, semver::Version),
}

trait ReadBytesExt<'a> {
    fn read_u32(&mut self) -> Result<u32>;
    fn read_slice(&mut self, len: usize) -> Result<&'a [u8]>;
}

impl<'a> ReadBytesExt<'a> for &'a [u8] {
    fn read_u32(&mut self) -> Result<u32> {
        const U32_SIZE: usize = core::mem::size_of::<u32>();

        if self.len() < U32_SIZE {
            bail!("unexpected end of file");
        }

        let value = u32::from_le_bytes(self[..U32_SIZE].try_into().unwrap());
        *self = &self[U32_SIZE..];
        Ok(value)
    }

    fn read_slice(&mut self, len: usize) -> Result<&'a [u8]> {
        if self.len() < len {
            bail!("unexpected end of file");
        }
        let mut other: &[u8] = &[][..];
        core::mem::swap(self, &mut other);
        let (first, rest) = other.split_at(len);
        *self = rest;
        Ok(first)
    }
}

trait WriteBytesExt {
    fn write_u32(&mut self, value: u32);
}

impl WriteBytesExt for Vec<u8> {
    fn write_u32(&mut self, value: u32) {
        self.extend_from_slice(&value.to_le_bytes());
    }
}

/// What kind of ABI is the program using
#[non_exhaustive]
#[derive(Copy, Clone, Debug, PartialEq, Eq, Serialize, Deserialize)]
pub enum AbiKind {
    /// The v1 version of the ABI
    V1Compat,
    /// The Linux ABI
    Linux, // unused for now
}

/// A list of key-value pairs that contains information about the program.
#[non_exhaustive]
#[derive(Clone, Debug, PartialEq, Eq)]
pub struct ProgramBinaryHeader {
    /// The ABI the program uses
    pub abi_kind: AbiKind,

    /// The version of the ABI that the program uses
    pub abi_version: semver::Version,
}

impl Default for ProgramBinaryHeader {
    fn default() -> Self {
        Self {
            abi_version: semver::Version::new(1, 0, 0),
            abi_kind: AbiKind::V1Compat,
        }
    }
}

impl ProgramBinaryHeader {
    fn decode(mut bytes: &[u8]) -> Result<Self> {
        let num_kv_pairs = bytes.read_u32().context("Malformed ProgramBinaryHeader")?;

        // Decode the key-value pairs
        let mut kv_pairs = vec![];
        for _ in 0..num_kv_pairs {
            let kv_pair_len = bytes.read_u32().context("Malformed ProgramBinaryHeader")?;
            let kv_bytes = bytes
                .read_slice(kv_pair_len as usize)
                .context("Malformed ProgramBinaryHeader")?;

            // Skip any entries we can't decode
            if let Ok(kv_pair) = postcard::from_bytes(kv_bytes) {
                kv_pairs.push(kv_pair);
            }
        }

        if !bytes.is_empty() {
            bail!("Malformed ProgramBinaryHeader: trailing bytes");
        }

        // Find the individual key-value pairs we need
        if kv_pairs.len() != 1 {
            bail!("Malformed ProgramBinaryHeader: duplicate attributes");
        }
        let (abi_kind, abi_version) = kv_pairs
            .into_iter()
            .map(|pair| {
                let ProgramBinaryHeaderValueOnDisk::AbiVersion(abi_kind, abi_version) = pair;
                (abi_kind, abi_version)
            })
            .next()
            .ok_or_else(|| anyhow!("ProgramBinary header missing AbiVersion"))?;

        Ok(Self {
            abi_kind,
            abi_version,
        })
    }

    fn encode(&self) -> Vec<u8> {
        let kv_pairs = vec![ProgramBinaryHeaderValueOnDisk::AbiVersion(
            self.abi_kind,
            self.abi_version.clone(),
        )];

        let mut ret = vec![];

        ret.write_u32(kv_pairs.len() as u32);
        for p in &kv_pairs {
            let kv_bytes = postcard::to_allocvec(p).unwrap();
            ret.write_u32(kv_bytes.len() as u32);
            ret.extend_from_slice(&kv_bytes[..]);
        }

        ret
    }
}

#[test]
fn header_encode_decode() {
    let header = ProgramBinaryHeader::default();
    let header_roundtripped = ProgramBinaryHeader::decode(&header.encode()[..]).unwrap();

    assert_eq!(header, header_roundtripped);
}

#[test]
fn header_decode_errors_on_too_short() {
    ProgramBinaryHeader::decode(&[1, 2, 3, 4][..]).unwrap_err();
    ProgramBinaryHeader::decode(&[1, 2, 3, 4, 5, 6][..]).unwrap_err();
}

#[test]
fn header_decode_errors_on_trailing_bytes() {
    let mut encoded = ProgramBinaryHeader::default().encode();
    encoded.extend_from_slice(&[1, 2, 3, 4][..]);
    ProgramBinaryHeader::decode(&encoded).unwrap_err();
}

#[test]
fn header_decode_ignores_unknown_attributes() {
    let mut encoded = ProgramBinaryHeader::default().encode();

    encoded[0] += 1;
    encoded.extend_from_slice(&[2, 0, 0, 0, 0xFF, 0xFF][..]);
    let header = ProgramBinaryHeader::decode(&encoded).unwrap();
    assert_eq!(header, ProgramBinaryHeader::default());
}

/// A container to hold a user ELF and a kernel ELF together.
#[non_exhaustive]
#[derive(Debug, PartialEq, Eq)]
pub struct ProgramBinary<'a> {
    /// The header.
    pub header: ProgramBinaryHeader,

    /// The user ELF.
    pub user_elf: &'a [u8],

    /// The kernel ELF.
    pub kernel_elf: &'a [u8],
}

impl<'a> ProgramBinary<'a> {
    /// Construct from a pair of ELFs.
    pub fn new(user_elf: &'a [u8], kernel_elf: &'a [u8]) -> Self {
        Self {
            header: ProgramBinaryHeader::default(),
            user_elf,
            kernel_elf,
        }
    }

    /// Parse a blob into a `ProgramBinary`.
    pub fn decode(mut blob: &'a [u8]) -> Result<Self> {
        // Read MAGIC bytes. These signal the file format.
        let magic = blob
            .read_slice(MAGIC.len())
            .context("Malformed ProgramBinary")?;
        ensure!(magic == MAGIC, "Malformed ProgramBinary");

        // Read the format version number.
        let binary_format_version = blob.read_u32().context("Malformed ProgramBinary")?;
        ensure!(
            binary_format_version == BINARY_FORMAT_VERSION,
            "ProgramBinary binary format version mismatch"
        );

        // Read the header.
        let header_len = blob.read_u32().context("Malformed ProgramBinary")? as usize;
        let header = ProgramBinaryHeader::decode(
            blob.read_slice(header_len)
                .context("Malformed ProgramBinary")?,
        )?;

        // Read user length, and calculate kernel offset / length
        let user_len = blob.read_u32().context("Malformed ProgramBinary")? as usize;
        let user_elf = blob
            .read_slice(user_len)
            .context("Malformed ProgramBinary")?;
        ensure!(!user_elf.is_empty(), "Malformed ProgramBinary");

        let kernel_elf = blob;
        ensure!(!kernel_elf.is_empty(), "Malformed ProgramBinary");

        Ok(Self {
            header,
            user_elf,
            kernel_elf,
        })
    }

    /// Convert this binary into a blob.
    pub fn encode(&self) -> Vec<u8> {
        let mut ret = vec![];

        // Write magic and format version
        ret.extend_from_slice(MAGIC);
        ret.write_u32(BINARY_FORMAT_VERSION);

        // Write the header
        let header_bytes = ProgramBinaryHeader::encode(&self.header);
        ret.write_u32(header_bytes.len() as u32);
        ret.extend_from_slice(&header_bytes[..]);

        // Write the user and kernel elfs
        ret.write_u32(self.user_elf.len() as u32);
        ret.extend_from_slice(self.user_elf);
        ret.extend_from_slice(self.kernel_elf);

        ret
    }

    fn user_program(&self) -> Result<Program> {
        Program::load_elf(self.user_elf, KERNEL_START_ADDR.0).context("Loading user ELF")
    }

    fn kernel_program(&self) -> Result<Program> {
        Program::load_elf(self.kernel_elf, u32::MAX).context("Loading kernel ELF")
    }

    /// Convert this binary into a `MemoryImage`.
    pub fn to_image(&self) -> Result<MemoryImage> {
        Ok(MemoryImage::with_kernel(
            self.user_program()?,
            self.kernel_program()?,
        ))
    }

    /// Compute and return the ImageID of this binary.
    pub fn compute_image_id(&self) -> Result<Digest> {
        let merkle_root = self.to_image()?.image_id();
        Ok(SystemState { pc: 0, merkle_root }.digest::<Impl>())
    }

    /// Compute the memory merkle root of the kernel.
    pub fn kernel_id(&self) -> Result<Digest> {
        Ok(MemoryImage::new_kernel(self.kernel_program()?).image_id())
    }
}

#[test]
fn encode_decode() {
    let p1 = ProgramBinary::new(&[1, 2, 3, 4], &[5, 6, 7, 8]);
    let v = p1.encode();
    let p2 = ProgramBinary::decode(&v).unwrap();

    assert_eq!(p1, p2);
}

#[test]
fn bad_magic() {
    let p1 = ProgramBinary::new(&[1, 2, 3, 4], &[5, 6, 7, 8]);
    let mut v = p1.encode();
    v[0] = 0xbe;
    ProgramBinary::decode(&v).unwrap_err();
}

#[test]
fn bad_version() {
    let p1 = ProgramBinary::new(&[1, 2, 3, 4], &[5, 6, 7, 8]);
    let mut v = p1.encode();
    v[MAGIC.len()] = 0xbe;
    ProgramBinary::decode(&v).unwrap_err();
}
