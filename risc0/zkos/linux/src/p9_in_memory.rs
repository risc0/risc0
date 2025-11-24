//! Zero-Copy P9 Filesystem
//!
//! This module provides a zero-copy implementation of a P9 filesystem that can satisfy
//! all P9 protocol requests without any host I/O. It's useful for:
//! - Pre-loaded filesystems (snapshot a real filesystem and load it into zkVM)
//! - Testing P9 protocol implementation
//! - Deterministic execution (no external dependencies)
//!
//! The filesystem is built from a serialized snapshot embedded in the ELF binary.
//! All metadata access is zero-copy (via bytemuck casting), and file data is accessed
//! as slices directly from the embedded image.

#![allow(dead_code)]

use crate::p9::*;
use crate::p9_backend::P9Backend;
use bytemuck::{cast_slice, from_bytes};
use core::mem::size_of;
use risc0_zkos_fs::{
    FS_MAGIC, FS_VERSION, FilesystemImageHeader, HEADER_SIZE, INODE_META_SIZE, INodeMeta,
};

const ZERO_COPY_DEBUG: bool = false;

#[cfg(target_arch = "riscv32")]
use alloc::collections::BTreeMap;
#[cfg(target_arch = "riscv32")]
use alloc::format;
#[cfg(target_arch = "riscv32")]
use alloc::string::{String, ToString};
#[cfg(target_arch = "riscv32")]
use alloc::vec::Vec;

#[cfg(not(target_arch = "riscv32"))]
use std::collections::BTreeMap;
#[cfg(not(target_arch = "riscv32"))]
use std::format;
#[cfg(not(target_arch = "riscv32"))]
use std::string::String;
#[cfg(not(target_arch = "riscv32"))]
use std::vec::Vec;

/// Maximum number of FIDs that can be allocated
const MAX_FIDS: usize = 1024;

//==============================================================================
// ZERO-COPY FILESYSTEM IMAGE FORMAT
//==============================================================================

trait INodeMetaExt {
    fn qid(&self) -> Qid;
    fn is_dir(&self) -> bool;
    fn is_symlink(&self) -> bool;
    fn is_regular(&self) -> bool;
}

impl INodeMetaExt for INodeMeta {
    fn qid(&self) -> Qid {
        Qid::new(self.qid_type, self.qid_version, self.qid_path)
    }

    fn is_dir(&self) -> bool {
        self.qid_type & P9QidType::Qtdir as u8 != 0
    }

    fn is_symlink(&self) -> bool {
        self.qid_type & P9QidType::Qtsymlink as u8 != 0
    }

    fn is_regular(&self) -> bool {
        self.qid_type == P9QidType::Qtfile as u8
    }
}

/// Virtual Node - represents an open FID
#[derive(Clone, Debug)]
pub struct VNode {
    /// Which inode this FID points to
    pub inode: u64,

    /// Current path (for relative walks)
    pub path: String,

    /// Open mode (O_RDONLY, O_WRONLY, O_RDWR)
    pub mode: u32,

    /// Whether this FID is open for I/O
    pub is_open: bool,
}

/// Directory entry
#[derive(Clone, Debug)]
pub struct DirEntry {
    /// Entry name
    pub name: String,

    /// QID of the entry
    pub qid: Qid,

    /// Entry type (DT_REG, DT_DIR, etc.)
    pub entry_type: u8,

    /// Inode number this entry points to
    pub inode: u64,
}

/// Zero-copy filesystem accessor
///
/// This structure provides access to a filesystem image embedded in the ELF binary.
/// All metadata access is zero-copy (via bytemuck casting).
/// File data is accessed as slices directly from the embedded image.
pub struct ZeroCopyFilesystem {
    /// Header (zero-copy reference)
    header: &'static FilesystemImageHeader,

    /// Inode metadata table (zero-copy slice)
    inode_table: &'static [INodeMeta],

    /// File data blob (zero-copy slice)
    data_blob: &'static [u8],

    /// Path to inode mapping (deserialized once, small)
    /// NOTE: Uses String keys (not &'static str) because we need to look up dynamically created paths
    path_index: BTreeMap<String, u64>,

    /// Active FID table (runtime state)
    fid_table: BTreeMap<u32, VNode>,
}

impl Drop for ZeroCopyFilesystem {
    fn drop(&mut self) {
        let path_index_len = self.path_index.len();
        // Only log if path_index has entries (real instance, not temporary validation instance)
        if path_index_len > 0 {
            let (heap_used, _heap_free, _heap_total) = crate::allocator::get_heap_stats();
            crate::kernel::print(&format!(
                "ZeroCopyFilesystem::drop() called! path_index.len()={}, heap_used={} bytes ({} KB)",
                path_index_len,
                heap_used,
                heap_used / 1024
            ));
            crate::kernel::print(&format!(
                "ZeroCopyFilesystem::drop() - CRITICAL: Real backend being dropped! This will deallocate path_index (BTreeMap with {} entries, ~{} KB)",
                path_index_len,
                (path_index_len * 100) / 1024 // Rough estimate
            ));
        }
        // Silently drop temporary validation instances (path_index_len == 0)
    }
}

impl ZeroCopyFilesystem {
    #[inline(always)]
    fn debug_log(&self, msg: &str) {
        if ZERO_COPY_DEBUG {
            crate::kernel::print(msg);
        }
    }

    fn sanity_check_layout() {
        debug_assert_eq!(size_of::<FilesystemImageHeader>(), HEADER_SIZE);
        debug_assert_eq!(size_of::<INodeMeta>(), INODE_META_SIZE);
    }

    /// Validate that an INodeMeta struct contains reasonable values
    /// Returns true if valid, false if corrupted
    fn validate_inode_meta(&self, meta: &INodeMeta, inode_num: u64, data_blob_len: usize) -> bool {
        // Validate QID type - must be one of the known types
        // Valid types: Qtfile (0x00), Qtdir (0x80), Qtsymlink (0x02), or combinations
        // Invalid: anything with bits that don't correspond to known types
        let qtype = meta.qid_type;
        let valid_qtype_bits = P9QidType::Qtdir as u8
            | P9QidType::Qtappend as u8
            | P9QidType::Qtexcl as u8
            | P9QidType::Qtmount as u8
            | P9QidType::Qtauth as u8
            | P9QidType::Qttmp as u8
            | P9QidType::Qtsymlink as u8
            | P9QidType::Qtlink as u8
            | P9QidType::Qtfile as u8;

        // Check if qtype has any invalid bits set
        if (qtype & !valid_qtype_bits) != 0 {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC validate_inode_meta: invalid qid_type 0x{:02x} for inode {}",
                    qtype, inode_num
                ));
            }
            return false;
        }

        // Validate content_type (0=reg, 1=dir, 2=symlink, 3=special)
        if meta.content_type > 3 {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC validate_inode_meta: invalid content_type {} for inode {}",
                    meta.content_type, inode_num
                ));
            }
            return false;
        }

        // Validate content_type matches qid_type
        let is_dir = meta.is_dir();
        let is_symlink = meta.is_symlink();
        let is_regular = meta.is_regular();

        if is_dir && meta.content_type != 1 {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC validate_inode_meta: qid_type indicates dir but content_type={} for inode {}",
                    meta.content_type, inode_num
                ));
            }
            return false;
        }

        if is_symlink && meta.content_type != 2 {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC validate_inode_meta: qid_type indicates symlink but content_type={} for inode {}",
                    meta.content_type, inode_num
                ));
            }
            return false;
        }

        if is_regular && meta.content_type != 0 {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC validate_inode_meta: qid_type indicates file but content_type={} for inode {}",
                    meta.content_type, inode_num
                ));
            }
            return false;
        }

        // Validate content_offset and content_length
        let content_offset = meta.content_offset as usize;
        let content_length = meta.content_length as usize;

        // Check for integer overflow in offset + length
        if let Some(end) = content_offset.checked_add(content_length) {
            if end > data_blob_len {
                if ZERO_COPY_DEBUG {
                    self.debug_log(&format!(
                        "ZC validate_inode_meta: content out of bounds for inode {}: offset={} len={} blob_len={}",
                        inode_num, content_offset, content_length, data_blob_len
                    ));
                }
                return false;
            }
        } else {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC validate_inode_meta: integer overflow in content offset+length for inode {}: offset={} len={}",
                    inode_num, content_offset, content_length
                ));
            }
            return false;
        }

        // Validate that content_offset is within bounds
        if content_offset > data_blob_len {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC validate_inode_meta: content_offset out of bounds for inode {}: offset={} blob_len={}",
                    inode_num, content_offset, data_blob_len
                ));
            }
            return false;
        }

        // Sanity check: qid_path should match inode number (common pattern, but not always required)
        // We'll warn but not fail on this, as it's not strictly required by the format
        if meta.qid_path != inode_num && ZERO_COPY_DEBUG {
            // This is just a warning, not an error - qid_path can be different
            // But if it's wildly different, it might indicate corruption
            if meta.qid_path > (inode_num * 2) || meta.qid_path < (inode_num / 2) {
                self.debug_log(&format!(
                    "ZC validate_inode_meta: suspicious qid_path mismatch for inode {}: qid_path={}",
                    inode_num, meta.qid_path
                ));
            }
        }

        // Validate reasonable size values (prevent obviously corrupted data)
        // Max reasonable file size: 1GB (prevent corrupted size values)
        const MAX_REASONABLE_SIZE: u64 = 1024 * 1024 * 1024;
        if meta.size > MAX_REASONABLE_SIZE && ZERO_COPY_DEBUG {
            self.debug_log(&format!(
                "ZC validate_inode_meta: suspiciously large size for inode {}: size={}",
                inode_num, meta.size
            ));
            // Don't fail on this - might be legitimate, but log it
        }

        // Validate timestamps are reasonable (not in the far future)
        // Max reasonable timestamp: year 2100 (4102444800 seconds since epoch)
        const MAX_REASONABLE_TIMESTAMP: u64 = 4102444800;
        if (meta.atime_sec > MAX_REASONABLE_TIMESTAMP
            || meta.mtime_sec > MAX_REASONABLE_TIMESTAMP
            || meta.ctime_sec > MAX_REASONABLE_TIMESTAMP
            || meta.btime_sec > MAX_REASONABLE_TIMESTAMP)
            && ZERO_COPY_DEBUG
        {
            self.debug_log(&format!(
                "ZC validate_inode_meta: suspicious timestamp for inode {}: atime={} mtime={} ctime={} btime={}",
                inode_num, meta.atime_sec, meta.mtime_sec, meta.ctime_sec, meta.btime_sec
            ));
            // Don't fail on this - might be legitimate, but log it
        }

        // Validate nsec values are < 1 billion (nanoseconds in a second)
        if meta.atime_nsec >= 1_000_000_000
            || meta.mtime_nsec >= 1_000_000_000
            || meta.ctime_nsec >= 1_000_000_000
            || meta.btime_nsec >= 1_000_000_000
        {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC validate_inode_meta: invalid nanosecond values for inode {}: atime_nsec={} mtime_nsec={} ctime_nsec={} btime_nsec={}",
                    inode_num, meta.atime_nsec, meta.mtime_nsec, meta.ctime_nsec, meta.btime_nsec
                ));
            }
            return false;
        }

        true
    }

    /// Initialize filesystem from embedded image at given address
    ///
    /// # Safety
    /// The address must point to a valid FilesystemImage with correct alignment.
    /// The memory must remain valid for the 'static lifetime.
    pub unsafe fn from_address(addr: usize, max_size: usize) -> Result<Self, u32> {
        Self::sanity_check_layout();
        // First, read just the header to get the total size
        let header_slice = unsafe { core::slice::from_raw_parts(addr as *const u8, HEADER_SIZE) };

        // Debug: show raw header bytes
        crate::kernel::print(&format!("Reading header at 0x{:08x}", addr));
        crate::kernel::print(&format!(
            "  First 16 bytes: {:02x?}",
            &header_slice[..16.min(header_slice.len())]
        ));

        let header: &'static FilesystemImageHeader = from_bytes(header_slice);

        // Verify magic
        if header.magic != FS_MAGIC {
            crate::kernel::print("ZeroCopyFilesystem: invalid magic");
            crate::kernel::print(&format!("  Expected: {:?} (P9FS)", FS_MAGIC));
            crate::kernel::print(&format!("  Got: {:?}", &header.magic));
            crate::kernel::print("  This indicates the filesystem was not properly embedded");
            return Err(22); // EINVAL
        }

        // Verify version
        if header.version != FS_VERSION {
            crate::kernel::print("ZeroCopyFilesystem: unsupported version");
            crate::kernel::print(&format!("  Got version: {}", header.version));
            return Err(22); // EINVAL
        }

        // Verify inode table offset is valid and aligned
        // Note: After adding padding for alignment, offset may be > HEADER_SIZE
        let inode_table_offset = header.inode_table_offset as usize;
        if inode_table_offset < HEADER_SIZE {
            crate::kernel::print("ZeroCopyFilesystem: invalid inode table offset");
            crate::kernel::print(&format!(
                "  Offset {} is before header end ({})",
                inode_table_offset, HEADER_SIZE
            ));
            return Err(22);
        }

        // CRITICAL: Verify 8-byte alignment for bytemuck::cast_slice
        const INODE_ALIGNMENT: usize = 8; // INodeMeta requires 8-byte alignment
        #[allow(clippy::manual_is_multiple_of)]
        if inode_table_offset % INODE_ALIGNMENT != 0 {
            crate::kernel::print("ZeroCopyFilesystem: inode table not 8-byte aligned!");
            crate::kernel::print(&format!(
                "  Offset: {}, alignment: {} bytes",
                inode_table_offset,
                inode_table_offset % INODE_ALIGNMENT
            ));
            return Err(22);
        }

        // Verify offset is reasonable (not beyond image)
        if inode_table_offset > header.total_size as usize {
            crate::kernel::print("ZeroCopyFilesystem: inode table offset beyond image");
            return Err(22);
        }

        if header.root_inode == 0 || header.num_inodes == 0 {
            crate::kernel::print("ZeroCopyFilesystem: missing root inode metadata");
            return Err(22);
        }

        // Check total size is reasonable
        let total_size = header.total_size as usize;
        if total_size > max_size {
            crate::kernel::print("ZeroCopyFilesystem: image too large");
            crate::kernel::print(&format!("  Image size: {}, max: {}", total_size, max_size));
            return Err(22); // EINVAL
        }

        // Now get slice of the actual size needed
        let data = unsafe { core::slice::from_raw_parts(addr as *const u8, total_size) };

        // Zero-copy inode table access
        // Use the verified offset (already checked for alignment above)
        let inode_start = inode_table_offset;

        // Check for integer overflow in inode_bytes calculation
        let inode_bytes = match (header.num_inodes as usize).checked_mul(INODE_META_SIZE) {
            Some(bytes) => bytes,
            None => {
                crate::kernel::print(
                    "ZeroCopyFilesystem: integer overflow in inode_bytes calculation",
                );
                return Err(22); // EINVAL
            }
        };

        // Check for integer overflow in bounds check
        let inode_end = match inode_start.checked_add(inode_bytes) {
            Some(end) => end,
            None => {
                crate::kernel::print("ZeroCopyFilesystem: integer overflow in inode table bounds");
                return Err(22); // EINVAL
            }
        };

        if inode_end > header.total_size as usize {
            crate::kernel::print("ZeroCopyFilesystem: inode table out of bounds");
            return Err(22); // EINVAL
        }

        if (header.path_index_offset as usize) < inode_end {
            crate::kernel::print("ZeroCopyFilesystem: path index overlaps inode table");
            return Err(22);
        }

        let inode_table: &'static [INodeMeta] = cast_slice(&data[inode_start..inode_end]);

        // Zero-copy data blob access
        let blob_start = header.data_blob_offset as usize;
        let total_size = header.total_size as usize;

        if blob_start < header.path_index_offset as usize {
            crate::kernel::print("ZeroCopyFilesystem: data blob overlaps path index");
            return Err(22);
        }

        // Validate blob_start is within bounds
        if blob_start > total_size {
            crate::kernel::print("ZeroCopyFilesystem: data blob start beyond total size");
            return Err(22);
        }

        let data_blob = &data[blob_start..total_size];

        // Deserialize path index (one-time, small)
        let path_start = header.path_index_offset as usize;
        let path_end = blob_start;
        if path_start > path_end || path_end > data.len() {
            crate::kernel::print("ZeroCopyFilesystem: invalid path index range");
            return Err(22);
        }
        // Track heap before parsing path_index
        let (heap_before_used, _, _) = crate::allocator::get_heap_stats();
        crate::kernel::print(&format!(
            "ZeroCopyFilesystem: Heap before parse_path_index: {} bytes",
            heap_before_used
        ));

        let path_index = Self::parse_path_index(&data[path_start..path_end])?;

        // Track heap after parsing path_index
        let (heap_after_used, heap_after_free, heap_after_total) =
            crate::allocator::get_heap_stats();
        let heap_delta = heap_after_used.saturating_sub(heap_before_used);
        let path_index_size = path_end.saturating_sub(path_start);
        crate::kernel::print(&format!(
            "ZeroCopyFilesystem: Heap after parse_path_index: {} bytes (delta: {} bytes, {:.2} KB), free: {} bytes, total: {} bytes",
            heap_after_used,
            heap_delta,
            heap_delta as f64 / 1024.0,
            heap_after_free,
            heap_after_total
        ));
        crate::kernel::print(&format!(
            "ZeroCopyFilesystem: path_index.len()={}, path_index data size: {} bytes ({:.2} KB)",
            path_index.len(),
            path_index_size,
            path_index_size as f64 / 1024.0
        ));

        // Create temporary filesystem instance for validation (before final construction)
        // This allows us to validate all inodes during initialization to catch corruption early
        let temp_fs = Self {
            header,
            inode_table,
            data_blob,
            path_index: BTreeMap::new(), // Empty for validation, will use real one below
            fid_table: BTreeMap::new(),
        };

        // Validate all inodes during initialization to catch corruption early
        // This is optional but helps detect issues before they cause problems
        let mut corrupted_inodes = 0;
        for inode_num in 1..=header.num_inodes as u64 {
            if let Some(meta) = temp_fs.inode_table.get((inode_num - 1) as usize) {
                if !temp_fs.validate_inode_meta(meta, inode_num, data_blob.len()) {
                    corrupted_inodes += 1;
                    if corrupted_inodes <= 5 {
                        // Only log first 5 to avoid spam
                        crate::kernel::print(&format!(
                            "ZeroCopyFilesystem: WARNING - corrupted inode {} detected during init",
                            inode_num
                        ));
                    }
                }
            }
        }

        if corrupted_inodes > 0 {
            crate::kernel::print(&format!(
                "ZeroCopyFilesystem: WARNING - {} corrupted inodes detected (filesystem may be unreliable)",
                corrupted_inodes
            ));
            // Don't fail initialization - allow degraded operation, but warn
            // Individual accesses will still be validated and fail safely
        }

        crate::kernel::print("ZeroCopyFilesystem: initialized");
        crate::kernel::print(&format!("  Inodes: {}", header.num_inodes));
        crate::kernel::print(&format!("  Paths: {}", path_index.len()));
        crate::kernel::print(&format!("  Data blob: {} bytes", data_blob.len()));
        if corrupted_inodes == 0 {
            crate::kernel::print("  Validation: All inodes passed integrity checks");
        }

        // Now create the final filesystem instance with the real path_index
        Ok(Self {
            header,
            inode_table,
            data_blob,
            path_index,
            fid_table: BTreeMap::new(),
        })
    }

    /// Parse path index from bytes
    fn parse_path_index(data: &[u8]) -> Result<BTreeMap<String, u64>, u32> {
        let mut index = BTreeMap::new();
        let mut pos: usize = 0;

        if data.len() < 4 {
            return Ok(index); // Empty index
        }

        // Read number of entries
        let num_entries = u32::from_le_bytes([data[0], data[1], data[2], data[3]]);
        pos += 4;

        for _ in 0..num_entries {
            // Check for overflow when reading minimum required bytes (2 for path_len + 8 for inode)
            match pos.checked_add(10) {
                Some(sum) if sum > data.len() => return Err(22), // EINVAL
                None => return Err(22),                          // EINVAL - overflow
                _ => {}
            }

            // Read path length (u16)
            let path_len = u16::from_le_bytes([data[pos], data[pos + 1]]) as usize;
            pos += 2;

            // Check for integer overflow: pos + path_len + 8
            let required_bytes = match path_len.checked_add(8) {
                Some(sum) => match pos.checked_add(sum) {
                    Some(total) => total,
                    None => return Err(22), // EINVAL - overflow
                },
                None => return Err(22), // EINVAL - overflow
            };

            if required_bytes > data.len() {
                return Err(22); // EINVAL
            }

            // Check for overflow when accessing path string
            let path_end = match pos.checked_add(path_len) {
                Some(end) => end,
                None => return Err(22), // EINVAL - overflow
            };

            if path_end > data.len() {
                return Err(22); // EINVAL
            }

            // Read path string
            // NOTE: We copy to String (not &'static str) because we need to look up dynamically created paths
            let path = core::str::from_utf8(&data[pos..path_end])
                .map_err(|_| 22u32)? // EINVAL
                .to_string();
            pos = path_end;

            // Read inode number
            let inode = u64::from_le_bytes([
                data[pos],
                data[pos + 1],
                data[pos + 2],
                data[pos + 3],
                data[pos + 4],
                data[pos + 5],
                data[pos + 6],
                data[pos + 7],
            ]);
            pos += 8;

            index.insert(path, inode);
        }

        Ok(index)
    }

    /// Dump all known filesystem paths for debugging
    pub fn dump_all_paths(&self) {}

    /// Get inode metadata by number (zero-copy!)
    /// Validates metadata integrity before returning
    pub fn get_inode_meta(&self, inode_num: u64) -> Result<&'static INodeMeta, u32> {
        if inode_num == 0 || inode_num > self.header.num_inodes as u64 {
            return Err(2); // ENOENT
        }

        // Safe: inode_num is > 0, so (inode_num - 1) cannot underflow
        // inode_num is <= num_inodes, so idx will be < inode_table.len()
        let idx = (inode_num - 1) as usize;
        let meta = self.inode_table.get(idx).ok_or(2u32)?; // ENOENT

        // Validate metadata integrity to detect corruption
        if !self.validate_inode_meta(meta, inode_num, self.data_blob.len()) {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC get_inode_meta: corrupted metadata detected for inode {}",
                    inode_num
                ));
            }
            return Err(22); // EINVAL - corrupted metadata
        }

        Ok(meta)
    }

    /// Get inode metadata by path (zero-copy metadata!)
    pub fn get_inode_by_path(&self, path: &str) -> Result<&'static INodeMeta, u32> {
        let inode_num = self.path_index.get(path).ok_or(2u32)?; // ENOENT
        self.get_inode_meta(*inode_num)
    }

    /// Read file content (zero-copy slice!)
    /// Validates metadata before accessing data to prevent corruption
    pub fn read_file_data(&self, meta: &INodeMeta) -> &'static [u8] {
        // First, validate the metadata structure itself
        // We need to determine the inode number from qid_path (best guess)
        // If validation fails, return empty slice to prevent corruption
        let inode_num = meta.qid_path; // Use qid_path as proxy for inode number
        if !self.validate_inode_meta(meta, inode_num, self.data_blob.len()) {
            if ZERO_COPY_DEBUG {
                self.debug_log(
                    "ZC read_file_data: corrupted metadata detected, refusing to read data",
                );
            }
            return &[];
        }

        let start = meta.content_offset as usize;
        let content_length = meta.content_length as usize;

        // Validate that INodeMeta fields are reasonable (sanity check for corrupted metadata)
        // If content_length is extremely large, it's likely corrupted
        if content_length > self.data_blob.len() {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC read_file_data: suspicious content_length {} > blob_len {} (likely corrupted meta)",
                    content_length, self.data_blob.len()
                ));
            }
            return &[];
        }

        // Check for integer overflow before bounds check
        let end = match start.checked_add(content_length) {
            Some(e) => e,
            None => {
                if ZERO_COPY_DEBUG {
                    self.debug_log(&format!(
                        "ZC read_file_data: integer overflow offset={} len={}",
                        start, content_length
                    ));
                }
                return &[];
            }
        };

        if end > self.data_blob.len() {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC read_file_data: out-of-bounds slice offset={} len={} blob_len={}",
                    start,
                    content_length,
                    self.data_blob.len()
                ));
            }
            return &[];
        }

        // Additional check: ensure start is within bounds
        if start > self.data_blob.len() {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC read_file_data: start offset out of bounds offset={} blob_len={}",
                    start,
                    self.data_blob.len()
                ));
            }
            return &[];
        }

        if ZERO_COPY_DEBUG {
            self.debug_log(&format!(
                "ZC read_file_data: slice offset={} len={} inode={} qtype=0x{:02x}",
                start, content_length, meta.qid_path, meta.qid_type
            ));
        }

        &self.data_blob[start..end]
    }

    /// Read directory entries from content blob
    pub fn read_dir_entries(&self, meta: &INodeMeta) -> Result<Vec<DirEntry>, u32> {
        if !meta.is_dir() {
            if ZERO_COPY_DEBUG {
                self.debug_log("ZC read_dir_entries: is not a dir");
            }
            return Err(20); // ENOTDIR
        }

        let data = self.read_file_data(meta);
        if ZERO_COPY_DEBUG {
            self.debug_log(&format!(
                "ZC read_dir_entries: inode={} entries_blob_len={} (path='{}')",
                meta.qid_path,
                data.len(),
                self.fid_table
                    .iter()
                    .find(|(_, vnode)| vnode.inode == meta.qid_path)
                    .map(|(_, vnode)| vnode.path.clone())
                    .unwrap_or_else(|| "<unknown>".to_string())
            ));
        }
        Self::parse_dir_entries(data)
    }

    /// Parse directory entries from serialized format
    fn parse_dir_entries(data: &[u8]) -> Result<Vec<DirEntry>, u32> {
        let mut entries = Vec::new();
        let mut pos: usize = 0;

        if data.len() < 4 {
            return Ok(entries);
        }

        // Read number of entries
        let num_entries = u32::from_le_bytes([data[0], data[1], data[2], data[3]]);
        pos += 4;

        for _ in 0..num_entries {
            // Check for overflow: minimum 22 bytes needed (13 QID + 1 type + 8 inode)
            match pos.checked_add(22) {
                Some(sum) if sum > data.len() => return Err(22), // EINVAL
                None => return Err(22),                          // EINVAL - overflow
                _ => {}
            }

            // Parse QID (13 bytes)
            let qtype = data[pos];
            let version =
                u32::from_le_bytes([data[pos + 1], data[pos + 2], data[pos + 3], data[pos + 4]]);
            let path = u64::from_le_bytes([
                data[pos + 5],
                data[pos + 6],
                data[pos + 7],
                data[pos + 8],
                data[pos + 9],
                data[pos + 10],
                data[pos + 11],
                data[pos + 12],
            ]);
            pos += 13;

            // Entry type
            let entry_type = data[pos];
            pos += 1;

            // Inode number
            let inode = u64::from_le_bytes([
                data[pos],
                data[pos + 1],
                data[pos + 2],
                data[pos + 3],
                data[pos + 4],
                data[pos + 5],
                data[pos + 6],
                data[pos + 7],
            ]);
            pos += 8;

            // Name length
            let name_len = u16::from_le_bytes([data[pos], data[pos + 1]]) as usize;
            pos += 2;

            // Check for integer overflow: pos + name_len
            let name_end = match pos.checked_add(name_len) {
                Some(end) => end,
                None => return Err(22), // EINVAL - overflow
            };

            if name_end > data.len() {
                return Err(22); // EINVAL
            }

            // Name string
            let name = core::str::from_utf8(&data[pos..name_end])
                .map_err(|_| 22u32)? // EINVAL
                .to_string();
            pos = name_end;

            entries.push(DirEntry {
                name,
                qid: Qid::new(qtype, version, path),
                entry_type,
                inode,
            });
        }

        Ok(entries)
    }

    /// Get total image size
    pub fn image_size(&self) -> usize {
        self.header.total_size as usize
    }

    /// Get root inode number
    pub fn root_inode(&self) -> u64 {
        self.header.root_inode
    }

    /// Allocate a FID
    pub fn allocate_fid(&mut self, fid: u32, inode: u64, path: String) -> Result<(), u32> {
        if self.fid_table.len() >= MAX_FIDS {
            return Err(24); // EMFILE
        }

        if self.fid_table.contains_key(&fid) {
            return Err(17); // EEXIST
        }

        self.fid_table.insert(
            fid,
            VNode {
                inode,
                path,
                mode: 0,
                is_open: false,
            },
        );

        Ok(())
    }

    /// Get FID
    pub fn get_fid(&self, fid: u32) -> Result<&VNode, u32> {
        self.fid_table.get(&fid).ok_or(9u32) // EBADF
    }

    /// Get FID (mutable)
    pub fn get_fid_mut(&mut self, fid: u32) -> Result<&mut VNode, u32> {
        self.fid_table.get_mut(&fid).ok_or(9u32) // EBADF
    }

    /// Release a FID
    pub fn clunk_fid(&mut self, fid: u32) -> Result<(), u32> {
        self.fid_table.remove(&fid).ok_or(9u32)?; // EBADF
        Ok(())
    }

    /// Walk from a FID following path components (zero-copy metadata access!)
    pub fn walk(&mut self, from_fid: u32, to_fid: u32, wnames: &[String]) -> Result<Vec<Qid>, u32> {
        // Get starting vnode
        let from_vnode = self.get_fid(from_fid)?.clone();
        if ZERO_COPY_DEBUG {
            self.debug_log(&format!(
                "ZC walk: from_fid={} ({}) -> to_fid={} components={:?}",
                from_fid, from_vnode.path, to_fid, wnames
            ));
        }
        // Validate initial inode number
        if from_vnode.inode == 0 || from_vnode.inode > self.header.num_inodes as u64 {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC walk: corrupted initial inode {} (max={})",
                    from_vnode.inode, self.header.num_inodes
                ));
            }
            return Err(22); // EINVAL - corrupted inode
        }

        let mut current_inode = from_vnode.inode;
        let mut current_path = from_vnode.path.clone();
        let mut qids = Vec::new();

        // If wnames is empty, just clone the FID
        if wnames.is_empty() {
            if ZERO_COPY_DEBUG {
                self.debug_log("ZC walk [p1]: empty wnames, cloning fid");
            }
            let meta = self.get_inode_meta(current_inode)?;
            qids.push(meta.qid());
            self.allocate_fid(to_fid, current_inode, current_path.clone())?;
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC walk [p1]: cloned fid {} -> inode {} path '{}'",
                    to_fid, current_inode, current_path
                ));
            }
            return Ok(qids);
        }

        // Walk each component
        for (i, wname) in wnames.iter().enumerate() {
            let meta = self.get_inode_meta(current_inode)?;

            // Must be a directory to walk into
            if !meta.is_dir() {
                if ZERO_COPY_DEBUG {
                    self.debug_log(&format!(
                        "ZC walk [p6]: current inode {} is not a dir (wnames={:?})",
                        current_inode, wnames
                    ));
                }
                return Err(20); // ENOTDIR
            }

            // Read directory entries
            let entries = self.read_dir_entries(meta)?;

            // Validate all directory entry inode numbers to prevent using corrupted data
            for entry in &entries {
                if entry.inode == 0 || entry.inode > self.header.num_inodes as u64 {
                    if ZERO_COPY_DEBUG {
                        self.debug_log(&format!(
                            "ZC walk: corrupted inode {} in dir entry '{}' (max={})",
                            entry.inode, entry.name, self.header.num_inodes
                        ));
                    }
                    return Err(22); // EINVAL - corrupted directory entry
                }
            }

            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC walk: directory inode {} '{}' entries={}",
                    current_inode,
                    current_path,
                    entries.len()
                ));
                /* for (idx, entry) in entries.iter().enumerate() {
                    self.debug_log(&format!(
                        "ZC walk:   entry[{}] name='{}' inode={} qtype=0x{:02x} entry_type={} qid_path={}",
                        idx,
                        entry.name,
                        entry.inode,
                        entry.qid.qtype,
                        entry.entry_type,
                        entry.qid.path
                    ));
                } */
            }
            // Compute the next absolute path for path-index fallback
            let next_path = if current_path == "/" {
                format!("/{}", wname)
            } else {
                format!("{}/{}", current_path, wname)
            };

            // Validate next_path is valid UTF-8 and not corrupted
            if next_path.is_empty() {
                if ZERO_COPY_DEBUG {
                    self.debug_log("ZC walk pxyA: ERROR: next_path is empty!");
                }
                return Err(22); // EINVAL
            }
            // Check if path_index is accessible
            if ZERO_COPY_DEBUG {
                let path_index_len = self.path_index.len();
                self.debug_log(&format!(
                    "ZC walk pxyA2: path_index.len()={}",
                    path_index_len
                ));
            }

            // Now try the actual lookup - wrap in a way that catches panics
            // Since we can't use catch_unwind in no_std, we'll just be very careful
            let inode_opt = self.path_index.get(&next_path);
            if ZERO_COPY_DEBUG {
                if let Some(inode) = inode_opt {
                    self.debug_log(&format!("ZC walk pxyB: found inode={}", inode));
                } else {
                    self.debug_log("ZC walk pxyB: not found");
                }
            }
            // Find the named entry, falling back to the path index if needed
            let next_inode = if let Some(entry) = entries.iter().find(|e| e.name == *wname) {
                // Validate inode number from directory entry before using
                if entry.inode == 0 || entry.inode > self.header.num_inodes as u64 {
                    if ZERO_COPY_DEBUG {
                        self.debug_log(&format!(
                            "ZC walk: corrupted inode {} from dir entry (max={})",
                            entry.inode, self.header.num_inodes
                        ));
                    }
                    return Err(22); // EINVAL - corrupted inode
                }
                if ZERO_COPY_DEBUG {
                    self.debug_log(&format!(
                        "ZC walk: found '{}' in dir listing -> inode {} qtype=0x{:02x}",
                        wname, entry.inode, entry.qid.qtype
                    ));
                }
                entry.inode
            } else if let Some(inode) = self.path_index.get(&next_path) {
                // Validate inode number from path_index before using
                if *inode == 0 || *inode > self.header.num_inodes as u64 {
                    if ZERO_COPY_DEBUG {
                        self.debug_log(&format!(
                            "ZC walk: corrupted inode {} from path_index (max={})",
                            inode, self.header.num_inodes
                        ));
                    }
                    return Err(22); // EINVAL - corrupted inode
                }
                if ZERO_COPY_DEBUG {
                    self.debug_log(&format!(
                        "ZC walk: '{}' missing from dir entries, using path index inode {}",
                        next_path, inode
                    ));
                }
                *inode
            } else {
                if ZERO_COPY_DEBUG {
                    self.debug_log("ZC walk [p2]: not found");
                }
                return Err(2); // ENOENT
            };

            current_inode = next_inode;
            current_path = next_path;

            let next_meta = self.get_inode_meta(current_inode)?;
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC walk: inode {} qtype=0x{:02x} size={} offset={} content_len={}",
                    current_inode,
                    next_meta.qid_type,
                    next_meta.size,
                    next_meta.content_offset,
                    next_meta.content_length
                ));
            }
            let next_qid = next_meta.qid();
            qids.push(next_qid);
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC walk: pushed qid path={} type=0x{:02x} total_qids={}",
                    next_qid.path,
                    next_qid.qtype,
                    qids.len()
                ));
            }

            // Stop walking if we hit a symlink before the final component.
            if next_meta.is_symlink() && (i + 1) < wnames.len() {
                if ZERO_COPY_DEBUG {
                    self.debug_log(&format!(
                        "ZC walk [p3]: encountered symlink '{}' inode {}, stopping walk early",
                        current_path, current_inode
                    ));
                }
                break;
            }
        }

        // Allocate the new FID
        if let Err(errno) = self.allocate_fid(to_fid, current_inode, current_path.clone()) {
            if ZERO_COPY_DEBUG {
                self.debug_log(&format!(
                    "ZC walk [p4]: allocate_fid failed fid={} errno={}",
                    to_fid, errno
                ));
            }
            return Err(errno);
        }
        if ZERO_COPY_DEBUG {
            match self.get_fid(to_fid) {
                Ok(vnode) => self.debug_log(&format!(
                    "ZC walk [p5]: completed walk -> fid {} inode {} path '{}'",
                    to_fid, vnode.inode, vnode.path
                )),
                Err(errno) => self.debug_log(&format!(
                    "ZC walk [p5]: completed walk but get_fid({}) failed with errno {}",
                    to_fid, errno
                )),
            }
        }

        Ok(qids)
    }

    /// Read from a file (zero-copy!)
    pub fn read(&self, fid: u32, offset: u64, count: u32) -> Result<Vec<u8>, u32> {
        let vnode = self.get_fid(fid)?;

        if !vnode.is_open {
            return Err(9); // EBADF
        }

        let meta = self.get_inode_meta(vnode.inode)?;

        if !meta.is_regular() {
            return Err(21); // EISDIR
        }

        // Get file data (zero-copy slice!)
        let file_data = self.read_file_data(meta);
        if ZERO_COPY_DEBUG {
            self.debug_log(&format!(
                "ZC read: fid={} path='{}' inode={} offset={} count={} available={}",
                fid,
                vnode.path,
                vnode.inode,
                offset,
                count,
                file_data.len()
            ));
        }

        // Calculate read range
        let start = offset.min(file_data.len() as u64) as usize;
        let end = (offset + count as u64).min(file_data.len() as u64) as usize;

        // Return copy of the slice (caller needs owned data for P9 response)
        Ok(file_data[start..end].to_vec())
    }
}

//==============================================================================
// ZERO-COPY BACKEND IMPLEMENTATION
//==============================================================================

/// Zero-Copy P9 Backend
///
/// This backend uses a zero-copy filesystem image embedded in the ELF binary.
/// All metadata is accessed via bytemuck casting (zero deserialization).
/// All file data is accessed as slices directly from the embedded image.
pub struct ZeroCopyBackend {
    fs: ZeroCopyFilesystem,
}

impl Drop for ZeroCopyBackend {
    fn drop(&mut self) {
        let (heap_used, _heap_free, _heap_total) = crate::allocator::get_heap_stats();
        let path_index_len = self.fs.path_index.len();
        crate::kernel::print(&format!(
            "ZeroCopyBackend::drop() called! path_index.len()={}, heap_used={} bytes ({} KB)",
            path_index_len,
            heap_used,
            heap_used / 1024
        ));
        crate::kernel::print(&format!(
            "ZeroCopyBackend::drop() - This will deallocate path_index (BTreeMap with {} entries)",
            path_index_len
        ));
    }
}

impl ZeroCopyBackend {
    /// Create a new zero-copy backend from an embedded image
    ///
    /// # Safety
    /// The address must point to a valid FilesystemImage with correct alignment.
    /// The memory must remain valid for the 'static lifetime.
    pub unsafe fn from_address(addr: usize, max_size: usize) -> Result<Self, u32> {
        let fs = unsafe { ZeroCopyFilesystem::from_address(addr, max_size)? };
        Ok(Self { fs })
    }

    /// Get the filesystem size (for heap calculation)
    pub fn image_size(&self) -> usize {
        self.fs.image_size()
    }

    /// Get mutable access to filesystem (for FID management)
    pub fn filesystem_mut(&mut self) -> &mut ZeroCopyFilesystem {
        &mut self.fs
    }

    /// Dump all known paths for debugging purposes
    pub fn dump_all_paths(&self) {
        self.fs.dump_all_paths();
    }
}

impl P9Backend for ZeroCopyBackend {
    fn send_tversion(
        &mut self,
        msg: &TversionMessage,
    ) -> Result<P9Response<RversionMessage>, TversionError> {
        // Version negotiation - no filesystem state needed
        let version = if msg.version == "9P2000.L" {
            "9P2000.L"
        } else {
            "unknown"
        };

        Ok(P9Response::Success(RversionMessage {
            tag: msg.tag,
            msize: msg.msize.min(8192),
            version,
        }))
    }

    fn send_tattach(
        &mut self,
        msg: &TattachMessage,
    ) -> Result<P9Response<RattachMessage>, TattachError> {
        // Allocate root FID
        match self
            .fs
            .allocate_fid(msg.fid, self.fs.root_inode(), "/".to_string())
        {
            Ok(_) => {
                let root = self.fs.get_inode_meta(self.fs.root_inode()).unwrap();
                Ok(P9Response::Success(RattachMessage {
                    tag: msg.tag,
                    qid: root.qid(),
                }))
            }
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }

    fn send_twalk(&mut self, msg: &TwalkMessage) -> Result<P9Response<RwalkMessage>, TwalkError> {
        // Use zero-copy walk operation
        match self.fs.walk(msg.fid, msg.newfid, &msg.wnames) {
            Ok(qids) => {
                if ZERO_COPY_DEBUG {
                    crate::kernel::print(&format!(
                        "ZC send_twalk: success fid={} newfid={} qids={:?}",
                        msg.fid, msg.newfid, qids
                    ));
                }
                Ok(P9Response::Success(RwalkMessage {
                    tag: msg.tag,
                    nwqid: qids.len() as u16,
                    wqids: qids,
                }))
            }
            Err(errno) => {
                if ZERO_COPY_DEBUG {
                    crate::kernel::print(&format!(
                        "ZC send_twalk: error fid={} newfid={} errno={}",
                        msg.fid, msg.newfid, errno
                    ));
                }
                Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno)))
            }
        }
    }

    fn send_tread(&mut self, msg: &TreadMessage) -> Result<P9Response<RreadMessage>, TreadError> {
        // Zero-copy read!
        match self.fs.read(msg.fid, msg.offset, msg.count) {
            Ok(data) => Ok(P9Response::Success(RreadMessage {
                tag: msg.tag,
                count: data.len() as u32,
                data,
            })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }

    fn send_twrite(
        &mut self,
        _msg: &TwriteMessage,
    ) -> Result<P9Response<RwriteMessage>, TwriteError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 30))) // EROFS
    }

    fn send_tlopen(
        &mut self,
        msg: &TlopenMessage,
    ) -> Result<P9Response<RlopenMessage>, TlopenError> {
        // Get inode number first to avoid borrow issues
        let inode_num = match self.fs.get_fid(msg.fid) {
            Ok(vnode) => vnode.inode,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };

        let inode_qid = match self.fs.get_inode_meta(inode_num) {
            Ok(meta) => meta.qid(),
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };

        // Mark as open
        match self.fs.get_fid_mut(msg.fid) {
            Ok(vnode) => {
                vnode.is_open = true;
                vnode.mode = msg.flags;

                Ok(P9Response::Success(RlopenMessage {
                    tag: msg.tag,
                    qid: inode_qid,
                    iounit: 8192,
                }))
            }
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }

    fn send_tlcreate(
        &mut self,
        msg: &TlcreateMessage,
    ) -> Result<P9Response<RlcreateMessage>, TlcreateError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_tgetattr(
        &mut self,
        msg: &TgetattrMessage,
    ) -> Result<P9Response<RgetattrMessage>, TgetattrError> {
        let vnode = match self.fs.get_fid(msg.fid) {
            Ok(v) => v,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };

        let meta = match self.fs.get_inode_meta(vnode.inode) {
            Ok(m) => m,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };

        // All metadata is already in INodeMeta - zero-copy!
        Ok(P9Response::Success(RgetattrMessage {
            tag: msg.tag,
            valid: msg.request_mask,
            qid: meta.qid(),
            mode: meta.mode,
            uid: meta.uid,
            gid: meta.gid,
            nlink: meta.nlink,
            rdev: meta.rdev,
            size: meta.size,
            blksize: meta.blksize,
            blocks: meta.blocks,
            atime_sec: meta.atime_sec,
            atime_nsec: meta.atime_nsec,
            mtime_sec: meta.mtime_sec,
            mtime_nsec: meta.mtime_nsec,
            ctime_sec: meta.ctime_sec,
            ctime_nsec: meta.ctime_nsec,
            btime_sec: meta.btime_sec,
            btime_nsec: meta.btime_nsec,
            gen_: 0,
            data_version: 0,
        }))
    }

    fn send_tsetattr(
        &mut self,
        msg: &TsetattrMessage,
    ) -> Result<P9Response<RsetattrMessage>, TsetattrError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_treaddir(
        &mut self,
        msg: &TreaddirMessage,
    ) -> Result<P9Response<RreaddirMessage>, TreaddirError> {
        let vnode = match self.fs.get_fid(msg.fid) {
            Ok(v) => v,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };

        let meta = match self.fs.get_inode_meta(vnode.inode) {
            Ok(m) => m,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };

        // Read directory entries
        let _entries = match self.fs.read_dir_entries(meta) {
            Ok(e) => e,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };

        // Serialize entries starting from offset
        // TODO: Implement proper directory entry serialization with offset/count
        // For now, return error
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 38))) // ENOSYS
    }

    fn send_treadlink(
        &mut self,
        msg: &TreadlinkMessage,
    ) -> Result<P9Response<RreadlinkMessage>, TreadlinkError> {
        let vnode = match self.fs.get_fid(msg.fid) {
            Ok(v) => v,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };

        let meta = match self.fs.get_inode_meta(vnode.inode) {
            Ok(m) => m,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };

        if !meta.is_symlink() {
            return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 22))); // EINVAL
        }

        // Read symlink target (zero-copy slice, then convert to String)
        let target_bytes = self.fs.read_file_data(meta);
        if ZERO_COPY_DEBUG {
            self.fs.debug_log(&format!(
                "ZC treadlink: fid={} inode={} target_len={}",
                msg.fid,
                vnode.inode,
                target_bytes.len()
            ));
        }
        let target = core::str::from_utf8(target_bytes)
            .map_err(|_| TreadlinkError::InvalidUtf8)?
            .to_string();

        Ok(P9Response::Success(RreadlinkMessage {
            tag: msg.tag,
            target,
        }))
    }

    fn send_tsymlink(
        &mut self,
        msg: &TsymlinkMessage,
    ) -> Result<P9Response<RsymlinkMessage>, TsymlinkError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_tmknod(
        &mut self,
        msg: &TmknodMessage,
    ) -> Result<P9Response<RmknodMessage>, TmknodError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_tmkdir(
        &mut self,
        msg: &TmkdirMessage,
    ) -> Result<P9Response<RmkdirMessage>, TmkdirError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_tunlinkat(
        &mut self,
        msg: &TunlinkatMessage,
    ) -> Result<P9Response<RunlinkatMessage>, TunlinkatError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_trenameat(
        &mut self,
        msg: &TrenameatMessage,
    ) -> Result<P9Response<RrenameatMessage>, TrenameatError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_tclunk(
        &mut self,
        msg: &TclunkMessage,
    ) -> Result<P9Response<RclunkMessage>, TclunkError> {
        match self.fs.clunk_fid(msg.fid) {
            Ok(_) => Ok(P9Response::Success(RclunkMessage { tag: msg.tag })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }

    fn send_tremove(
        &mut self,
        msg: &TremoveMessage,
    ) -> Result<P9Response<RremoveMessage>, TremoveError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_tfsync(
        &mut self,
        msg: &TfsyncMessage,
    ) -> Result<P9Response<RfsyncMessage>, TfsyncError> {
        // No-op for zero-copy filesystem
        Ok(P9Response::Success(RfsyncMessage { tag: msg.tag }))
    }

    fn send_tlink(&mut self, msg: &TlinkMessage) -> Result<P9Response<RlinkMessage>, TlinkError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_trename(
        &mut self,
        msg: &TrenameMessage,
    ) -> Result<P9Response<RrenameMessage>, TrenameError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_txattrwalk(
        &mut self,
        msg: &TxattrwalkMessage,
    ) -> Result<P9Response<RxattrwalkMessage>, TxattrwalkError> {
        // Extended attributes not supported
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 95))) // EOPNOTSUPP
    }

    fn send_txattrcreate(
        &mut self,
        msg: &TxattrcreateMessage,
    ) -> Result<P9Response<RxattrcreateMessage>, TxattrcreateError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }

    fn send_tflush(
        &mut self,
        msg: &TflushMessage,
    ) -> Result<P9Response<RflushMessage>, TflushError> {
        // No-op for zero-copy (nothing to flush)
        Ok(P9Response::Success(RflushMessage { tag: msg.tag }))
    }

    fn send_tauth(&mut self, msg: &TauthMessage) -> Result<P9Response<RauthMessage>, TauthError> {
        // No authentication needed for zero-copy
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 38))) // ENOSYS
    }

    fn send_tstatfs(
        &mut self,
        msg: &TstatfsMessage,
    ) -> Result<P9Response<RstatfsMessage>, TstatfsError> {
        // TODO: Implement statfs
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 38))) // ENOSYS
    }

    fn send_tlock(&mut self, msg: &TlockMessage) -> Result<P9Response<RlockMessage>, TlockError> {
        // Read-only filesystem doesn't support locks
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 38))) // ENOSYS
    }

    fn send_tgetlock(
        &mut self,
        msg: &TgetlockMessage,
    ) -> Result<P9Response<RgetlockMessage>, TgetlockError> {
        // Read-only filesystem doesn't support locks
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 38))) // ENOSYS
    }
}
