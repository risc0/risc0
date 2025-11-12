//! In-Memory P9 Filesystem
//!
//! This module provides an in-memory implementation of a P9 filesystem that can satisfy
//! all P9 protocol requests without any host I/O. It's useful for:
//! - Pre-loaded filesystems (snapshot a real filesystem and load it into zkVM)
//! - Testing P9 protocol implementation
//! - Deterministic execution (no external dependencies)
//!
//! The filesystem is built from a serialized snapshot that can be created externally
//! by walking a real P9 filesystem and capturing all data.

#![allow(dead_code)]

use crate::p9::{Qid, P9QidType, P9Response};
use crate::p9_backend::P9Backend;
use crate::p9::*;
use core::mem::size_of;

#[cfg(target_arch = "riscv32")]
use bytemuck::{Pod, Zeroable};

#[cfg(not(target_arch = "riscv32"))]
use bytemuck::{Pod, Zeroable};

#[cfg(target_arch = "riscv32")]
use alloc::collections::BTreeMap;
#[cfg(target_arch = "riscv32")]
use alloc::string::{String, ToString};
#[cfg(target_arch = "riscv32")]
use alloc::vec::Vec;
#[cfg(target_arch = "riscv32")]
use alloc::format;

#[cfg(not(target_arch = "riscv32"))]
use std::collections::BTreeMap;
#[cfg(not(target_arch = "riscv32"))]
use std::string::String;
#[cfg(not(target_arch = "riscv32"))]
use std::vec::Vec;

/// Maximum number of FIDs that can be allocated
const MAX_FIDS: usize = 1024;

//==============================================================================
// ZERO-COPY FILESYSTEM IMAGE FORMAT
//==============================================================================

/// Filesystem image header (embedded in ELF, zero-copy access)
#[repr(C, align(8))]
#[derive(Copy, Clone, Pod, Zeroable, Debug)]
pub struct FilesystemImageHeader {
    /// Magic bytes: "P9FS"
    pub magic: [u8; 4],
    /// Format version (currently 1)
    pub version: u32,
    /// Total size of this filesystem image in bytes
    pub total_size: u32,
    /// Number of inodes in the inode table
    pub num_inodes: u32,
    /// Offset to inode metadata table
    pub inode_table_offset: u32,
    /// Offset to file data blob
    pub data_blob_offset: u32,
    /// Offset to path index
    pub path_index_offset: u32,
    pub _padding: u32,
    /// Root inode number
    pub root_inode: u64,
}

impl FilesystemImageHeader {
    pub fn new(total_size: u32, num_inodes: u32) -> Self {
        Self {
            magic: *b"P9FS",
            version: 1,
            total_size,
            num_inodes,
            inode_table_offset: size_of::<FilesystemImageHeader>() as u32,
            data_blob_offset: 0, // Set by builder
            path_index_offset: 0, // Set by builder
            _padding: 0,
            root_inode: 1,
        }
    }
}

/// Fixed-size inode metadata (zero-copy via bytemuck)
#[repr(C, align(8))]
#[derive(Copy, Clone, Pod, Zeroable, Debug)]
pub struct INodeMeta {
    // QID (13 bytes in wire format, padded to 16 for alignment)
    pub qid_type: u8,
    pub _padding1: [u8; 3],
    pub qid_version: u32,
    pub qid_path: u64,
    
    // Standard stat fields
    pub mode: u32,
    pub uid: u32,
    pub gid: u32,
    pub _padding2: u32,
    pub nlink: u64,
    pub rdev: u64,
    pub size: u64,
    pub blksize: u64,
    pub blocks: u64,
    
    // Timestamps (all u64)
    pub atime_sec: u64,
    pub atime_nsec: u64,
    pub mtime_sec: u64,
    pub mtime_nsec: u64,
    pub ctime_sec: u64,
    pub ctime_nsec: u64,
    pub btime_sec: u64,
    pub btime_nsec: u64,
    
    // Content location in data blob (total 8 bytes for alignment)
    pub content_type: u8,     // 0=regular, 1=directory, 2=symlink, 3=special
    pub _padding3: [u8; 3],
    pub content_offset: u32,  // Offset into data blob
    pub content_length: u32,  // Length of content in bytes
    pub _padding4: u32,       // Ensure 8-byte alignment at end
}

impl INodeMeta {
    pub fn qid(&self) -> Qid {
        Qid::new(self.qid_type, self.qid_version, self.qid_path)
    }
    
    pub fn is_dir(&self) -> bool {
        self.qid_type & P9QidType::Qtdir as u8 != 0
    }
    
    pub fn is_symlink(&self) -> bool {
        self.qid_type & P9QidType::Qtsymlink as u8 != 0
    }
    
    pub fn is_regular(&self) -> bool {
        self.qid_type == P9QidType::Qtfile as u8
    }
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
    path_index: BTreeMap<String, u64>,
    
    /// Active FID table (runtime state)
    fid_table: BTreeMap<u32, VNode>,
}

impl ZeroCopyFilesystem {
    /// Initialize filesystem from embedded image at given address
    ///
    /// # Safety
    /// The address must point to a valid FilesystemImage with correct alignment.
    /// The memory must remain valid for the 'static lifetime.
    pub unsafe fn from_address(addr: usize, max_size: usize) -> Result<Self, u32> {
        // Get slice to the image
        let data = unsafe { core::slice::from_raw_parts(addr as *const u8, max_size) };
        
        // Check minimum size
        if data.len() < size_of::<FilesystemImageHeader>() {
            return Err(22); // EINVAL
        }
        
        // Zero-copy header access
        let header: &'static FilesystemImageHeader = 
            bytemuck::from_bytes(&data[..size_of::<FilesystemImageHeader>()]);
        
        // Verify magic
        if &header.magic != b"P9FS" {
            crate::kernel::print("ZeroCopyFilesystem: invalid magic");
            return Err(22); // EINVAL
        }
        
        // Verify version
        if header.version != 1 {
            crate::kernel::print("ZeroCopyFilesystem: unsupported version");
            return Err(22); // EINVAL
        }
        
        // Verify total size
        if header.total_size as usize > data.len() {
            crate::kernel::print("ZeroCopyFilesystem: image truncated");
            return Err(22); // EINVAL
        }
        
        // Zero-copy inode table access
        let inode_start = header.inode_table_offset as usize;
        let inode_bytes = header.num_inodes as usize * size_of::<INodeMeta>();
        
        if inode_start + inode_bytes > header.total_size as usize {
            crate::kernel::print("ZeroCopyFilesystem: inode table out of bounds");
            return Err(22); // EINVAL
        }
        
        let inode_table: &'static [INodeMeta] = bytemuck::cast_slice(
            &data[inode_start..inode_start + inode_bytes]
        );
        
        // Zero-copy data blob access
        let blob_start = header.data_blob_offset as usize;
        let data_blob = &data[blob_start..header.total_size as usize];
        
        // Deserialize path index (one-time, small)
        let path_start = header.path_index_offset as usize;
        let path_end = blob_start;
        let path_index = Self::parse_path_index(&data[path_start..path_end])?;
        
        crate::kernel::print("ZeroCopyFilesystem: initialized");
        crate::kernel::print(&format!("  Inodes: {}", header.num_inodes));
        crate::kernel::print(&format!("  Paths: {}", path_index.len()));
        crate::kernel::print(&format!("  Data blob: {} bytes", data_blob.len()));
        
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
        let mut pos = 0;
        
        if data.len() < 4 {
            return Ok(index); // Empty index
        }
        
        // Read number of entries
        let num_entries = u32::from_le_bytes([data[0], data[1], data[2], data[3]]);
        pos += 4;
        
        for _ in 0..num_entries {
            if pos + 10 > data.len() {
                return Err(22); // EINVAL
            }
            
            // Read path length (u16)
            let path_len = u16::from_le_bytes([data[pos], data[pos + 1]]) as usize;
            pos += 2;
            
            if pos + path_len + 8 > data.len() {
                return Err(22); // EINVAL
            }
            
            // Read path string
            let path = core::str::from_utf8(&data[pos..pos + path_len])
                .map_err(|_| 22u32)?  // EINVAL
                .to_string();
            pos += path_len;
            
            // Read inode number
            let inode = u64::from_le_bytes([
                data[pos], data[pos+1], data[pos+2], data[pos+3],
                data[pos+4], data[pos+5], data[pos+6], data[pos+7],
            ]);
            pos += 8;
            
            index.insert(path, inode);
        }
        
        Ok(index)
    }
    
    /// Get inode metadata by number (zero-copy!)
    pub fn get_inode_meta(&self, inode_num: u64) -> Result<&'static INodeMeta, u32> {
        if inode_num == 0 || inode_num > self.header.num_inodes as u64 {
            return Err(2); // ENOENT
        }
        
        let idx = (inode_num - 1) as usize;
        self.inode_table.get(idx).ok_or(2u32) // ENOENT
    }
    
    /// Get inode metadata by path (zero-copy metadata!)
    pub fn get_inode_by_path(&self, path: &str) -> Result<&'static INodeMeta, u32> {
        let inode_num = self.path_index.get(path).ok_or(2u32)?; // ENOENT
        self.get_inode_meta(*inode_num)
    }
    
    /// Read file content (zero-copy slice!)
    pub fn read_file_data(&self, meta: &INodeMeta) -> &'static [u8] {
        let start = meta.content_offset as usize;
        let end = start + meta.content_length as usize;
        
        if end > self.data_blob.len() {
            return &[];
        }
        
        &self.data_blob[start..end]
    }
    
    /// Read directory entries from content blob
    pub fn read_dir_entries(&self, meta: &INodeMeta) -> Result<Vec<DirEntry>, u32> {
        if !meta.is_dir() {
            return Err(20); // ENOTDIR
        }
        
        let data = self.read_file_data(meta);
        Self::parse_dir_entries(data)
    }
    
    /// Parse directory entries from serialized format
    fn parse_dir_entries(data: &[u8]) -> Result<Vec<DirEntry>, u32> {
        let mut entries = Vec::new();
        let mut pos = 0;
        
        if data.len() < 4 {
            return Ok(entries);
        }
        
        // Read number of entries
        let num_entries = u32::from_le_bytes([data[0], data[1], data[2], data[3]]);
        pos += 4;
        
        for _ in 0..num_entries {
            if pos + 22 > data.len() {
                return Err(22); // EINVAL
            }
            
            // Parse QID (13 bytes)
            let qtype = data[pos];
            let version = u32::from_le_bytes([data[pos+1], data[pos+2], data[pos+3], data[pos+4]]);
            let path = u64::from_le_bytes([
                data[pos+5], data[pos+6], data[pos+7], data[pos+8],
                data[pos+9], data[pos+10], data[pos+11], data[pos+12],
            ]);
            pos += 13;
            
            // Entry type
            let entry_type = data[pos];
            pos += 1;
            
            // Inode number
            let inode = u64::from_le_bytes([
                data[pos], data[pos+1], data[pos+2], data[pos+3],
                data[pos+4], data[pos+5], data[pos+6], data[pos+7],
            ]);
            pos += 8;
            
            // Name length
            let name_len = u16::from_le_bytes([data[pos], data[pos+1]]) as usize;
            pos += 2;
            
            if pos + name_len > data.len() {
                return Err(22); // EINVAL
            }
            
            // Name string
            let name = core::str::from_utf8(&data[pos..pos + name_len])
                .map_err(|_| 22u32)?  // EINVAL
                .to_string();
            pos += name_len;
            
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
        
        self.fid_table.insert(fid, VNode {
            inode,
            path,
            mode: 0,
            is_open: false,
        });
        
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
        let mut current_inode = from_vnode.inode;
        let mut current_path = from_vnode.path.clone();
        let mut qids = Vec::new();
        
        // If wnames is empty, just clone the FID
        if wnames.is_empty() {
            let meta = self.get_inode_meta(current_inode)?;
            qids.push(meta.qid());
            self.allocate_fid(to_fid, current_inode, current_path)?;
            return Ok(qids);
        }
        
        // Walk each component
        for wname in wnames {
            let meta = self.get_inode_meta(current_inode)?;
            
            // Must be a directory to walk into
            if !meta.is_dir() {
                return Err(20); // ENOTDIR
            }
            
            // Read directory entries
            let entries = self.read_dir_entries(meta)?;
            
            // Find the named entry
            let entry = entries.iter()
                .find(|e| e.name == *wname)
                .ok_or(2u32)?; // ENOENT
            
            current_inode = entry.inode;
            current_path = if current_path == "/" {
                format!("/{}", wname)
            } else {
                format!("{}/{}", current_path, wname)
            };
            
            let next_meta = self.get_inode_meta(current_inode)?;
            qids.push(next_meta.qid());
        }
        
        // Allocate the new FID
        self.allocate_fid(to_fid, current_inode, current_path)?;
        
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
        
        // Calculate read range
        let start = offset.min(file_data.len() as u64) as usize;
        let end = (offset + count as u64).min(file_data.len() as u64) as usize;
        
        // Return copy of the slice (caller needs owned data for P9 response)
        Ok(file_data[start..end].to_vec())
    }
}

//==============================================================================
// DYNAMIC IN-MEMORY FILESYSTEM (Original Implementation)
//==============================================================================

/// In-memory P9 filesystem state
pub struct InMemoryFilesystem {
    /// Map from inode number to inode data
    inodes: BTreeMap<u64, INode>,
    
    /// Map from path to inode number (for fast lookups)
    path_to_inode: BTreeMap<String, u64>,
    
    /// Map from FID to VNode (virtual file handle)
    fid_table: BTreeMap<u32, VNode>,
    
    /// Next inode number to allocate
    next_inode: u64,
    
    /// Root inode number
    root_inode: u64,
    
    /// Current message tag (for responses)
    current_tag: u16,
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

/// In-memory representation of an inode
#[derive(Clone, Debug)]
pub struct INode {
    /// QID (type + version + path/inode number)
    pub qid: Qid,
    
    /// File mode and permissions (st_mode)
    pub mode: u32,
    
    /// User ID
    pub uid: u32,
    
    /// Group ID
    pub gid: u32,
    
    /// Number of hard links
    pub nlink: u64,
    
    /// Device ID (for special files)
    pub rdev: u64,
    
    /// File size
    pub size: u64,
    
    /// Block size
    pub blksize: u64,
    
    /// Number of blocks
    pub blocks: u64,
    
    /// Access time (seconds)
    pub atime_sec: u64,
    
    /// Access time (nanoseconds)
    pub atime_nsec: u64,
    
    /// Modification time (seconds)
    pub mtime_sec: u64,
    
    /// Modification time (nanoseconds)
    pub mtime_nsec: u64,
    
    /// Change time (seconds)
    pub ctime_sec: u64,
    
    /// Change time (nanoseconds)
    pub ctime_nsec: u64,
    
    /// Birth/creation time (seconds)
    pub btime_sec: u64,
    
    /// Birth/creation time (nanoseconds)
    pub btime_nsec: u64,
    
    /// The actual content
    pub content: FileContent,
}

/// File content types
#[derive(Clone, Debug)]
pub enum FileContent {
    /// Regular file with data
    Regular(Vec<u8>),
    
    /// Directory with entries
    Directory(Vec<DirEntry>),
    
    /// Symbolic link with target path
    Symlink(String),
    
    /// Special file (device, socket, etc.) - no content
    Special,
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

/// Filesystem snapshot for serialization
#[derive(Clone, Debug)]
pub struct FilesystemSnapshot {
    /// All inodes indexed by inode number
    pub inodes: BTreeMap<u64, INode>,
    
    /// Path to inode mapping
    pub paths: BTreeMap<String, u64>,
    
    /// Root inode number
    pub root_inode: u64,
}

impl InMemoryFilesystem {
    /// Create a new empty filesystem
    pub fn new() -> Self {
        let mut fs = Self {
            inodes: BTreeMap::new(),
            path_to_inode: BTreeMap::new(),
            fid_table: BTreeMap::new(),
            next_inode: 2, // Start at 2 (1 is root)
            root_inode: 1,
            current_tag: 0,
        };
        
        // Create root directory
        let root_inode = INode {
            qid: Qid::new(P9QidType::Qtdir as u8, 0, 1),
            mode: 0o040755, // S_IFDIR | 0755
            uid: 0,
            gid: 0,
            nlink: 2,
            rdev: 0,
            size: 4096,
            blksize: 4096,
            blocks: 8,
            atime_sec: 0,
            atime_nsec: 0,
            mtime_sec: 0,
            mtime_nsec: 0,
            ctime_sec: 0,
            ctime_nsec: 0,
            btime_sec: 0,
            btime_nsec: 0,
            content: FileContent::Directory(Vec::new()),
        };
        
        fs.inodes.insert(1, root_inode);
        fs.path_to_inode.insert("/".to_string(), 1);
        
        fs
    }
    
    /// Load filesystem from a snapshot
    pub fn from_snapshot(snapshot: FilesystemSnapshot) -> Self {
        let next_inode = snapshot.inodes.keys().max().copied().unwrap_or(1) + 1;
        let root_inode = snapshot.root_inode;
        
        Self {
            inodes: snapshot.inodes,
            path_to_inode: snapshot.paths,
            fid_table: BTreeMap::new(),
            next_inode,
            root_inode,
            current_tag: 0,
        }
    }
    
    /// Add a file to the filesystem
    pub fn add_file(&mut self, path: &str, content: Vec<u8>, mode: u32, uid: u32, gid: u32) -> Result<u64, u32> {
        let inode_num = self.next_inode;
        self.next_inode += 1;
        
        let inode = INode {
            qid: Qid::new(P9QidType::Qtfile as u8, 0, inode_num),
            mode,
            uid,
            gid,
            nlink: 1,
            rdev: 0,
            size: content.len() as u64,
            blksize: 4096,
            blocks: ((content.len() as u64 + 511) / 512),
            atime_sec: 0,
            atime_nsec: 0,
            mtime_sec: 0,
            mtime_nsec: 0,
            ctime_sec: 0,
            ctime_nsec: 0,
            btime_sec: 0,
            btime_nsec: 0,
            content: FileContent::Regular(content),
        };
        
        self.inodes.insert(inode_num, inode);
        self.path_to_inode.insert(path.to_string(), inode_num);
        
        // Add to parent directory
        if let Some(parent_path) = Self::parent_path(path) {
            self.add_dir_entry(parent_path, Self::basename(path), inode_num)?;
        }
        
        Ok(inode_num)
    }
    
    /// Add a directory to the filesystem
    pub fn add_directory(&mut self, path: &str, mode: u32, uid: u32, gid: u32) -> Result<u64, u32> {
        let inode_num = self.next_inode;
        self.next_inode += 1;
        
        let inode = INode {
            qid: Qid::new(P9QidType::Qtdir as u8, 0, inode_num),
            mode,
            uid,
            gid,
            nlink: 2,
            rdev: 0,
            size: 4096,
            blksize: 4096,
            blocks: 8,
            atime_sec: 0,
            atime_nsec: 0,
            mtime_sec: 0,
            mtime_nsec: 0,
            ctime_sec: 0,
            ctime_nsec: 0,
            btime_sec: 0,
            btime_nsec: 0,
            content: FileContent::Directory(Vec::new()),
        };
        
        self.inodes.insert(inode_num, inode);
        self.path_to_inode.insert(path.to_string(), inode_num);
        
        // Add to parent directory
        if path != "/" {
            if let Some(parent_path) = Self::parent_path(path) {
                self.add_dir_entry(parent_path, Self::basename(path), inode_num)?;
            }
        }
        
        Ok(inode_num)
    }
    
    /// Add a symlink to the filesystem
    pub fn add_symlink(&mut self, path: &str, target: String, uid: u32, gid: u32) -> Result<u64, u32> {
        let inode_num = self.next_inode;
        self.next_inode += 1;
        
        let inode = INode {
            qid: Qid::new(P9QidType::Qtsymlink as u8, 0, inode_num),
            mode: 0o120777, // S_IFLNK | 0777
            uid,
            gid,
            nlink: 1,
            rdev: 0,
            size: target.len() as u64,
            blksize: 4096,
            blocks: 0,
            atime_sec: 0,
            atime_nsec: 0,
            mtime_sec: 0,
            mtime_nsec: 0,
            ctime_sec: 0,
            ctime_nsec: 0,
            btime_sec: 0,
            btime_nsec: 0,
            content: FileContent::Symlink(target),
        };
        
        self.inodes.insert(inode_num, inode);
        self.path_to_inode.insert(path.to_string(), inode_num);
        
        // Add to parent directory
        if let Some(parent_path) = Self::parent_path(path) {
            self.add_dir_entry(parent_path, Self::basename(path), inode_num)?;
        }
        
        Ok(inode_num)
    }
    
    /// Helper: Add entry to a directory
    fn add_dir_entry(&mut self, dir_path: &str, name: &str, inode: u64) -> Result<(), u32> {
        let dir_inode_num = *self.path_to_inode.get(dir_path).ok_or(2u32)?; // ENOENT
        
        // Get child inode info first (before mutable borrow)
        let child_inode = self.inodes.get(&inode).ok_or(2u32)?;
        let child_qid = child_inode.qid;
        let child_entry_type = Self::qid_to_dt_type(child_inode.qid.qtype);
        
        // Now get mutable reference to directory
        let dir_inode = self.inodes.get_mut(&dir_inode_num).ok_or(2u32)?;
        
        if let FileContent::Directory(ref mut entries) = dir_inode.content {
            entries.push(DirEntry {
                name: name.to_string(),
                qid: child_qid,
                entry_type: child_entry_type,
                inode,
            });
            
            Ok(())
        } else {
            Err(20) // ENOTDIR
        }
    }
    
    /// Helper: Get parent path
    fn parent_path(path: &str) -> Option<&str> {
        if path == "/" {
            return None;
        }
        
        let path = path.trim_end_matches('/');
        if let Some(pos) = path.rfind('/') {
            if pos == 0 {
                Some("/")
            } else {
                Some(&path[..pos])
            }
        } else {
            Some("/")
        }
    }
    
    /// Helper: Get basename
    fn basename(path: &str) -> &str {
        let path = path.trim_end_matches('/');
        if let Some(pos) = path.rfind('/') {
            &path[pos + 1..]
        } else {
            path
        }
    }
    
    /// Helper: Convert QID type to directory entry type
    fn qid_to_dt_type(qtype: u8) -> u8 {
        const DT_REG: u8 = 8;
        const DT_DIR: u8 = 4;
        const DT_LNK: u8 = 10;
        
        if qtype & P9QidType::Qtdir as u8 != 0 {
            DT_DIR
        } else if qtype & P9QidType::Qtsymlink as u8 != 0 {
            DT_LNK
        } else {
            DT_REG
        }
    }
    
    /// Allocate a FID
    pub fn allocate_fid(&mut self, fid: u32, inode: u64, path: String) -> Result<(), u32> {
        if self.fid_table.len() >= MAX_FIDS {
            return Err(24); // EMFILE
        }
        
        if self.fid_table.contains_key(&fid) {
            return Err(17); // EEXIST
        }
        
        self.fid_table.insert(fid, VNode {
            inode,
            path,
            mode: 0,
            is_open: false,
        });
        
        Ok(())
    }
    
    /// Get FID
    pub fn get_fid(&self, fid: u32) -> Result<&VNode, u32> {
        self.fid_table.get(&fid).ok_or(9) // EBADF
    }
    
    /// Get FID (mutable)
    pub fn get_fid_mut(&mut self, fid: u32) -> Result<&mut VNode, u32> {
        self.fid_table.get_mut(&fid).ok_or(9) // EBADF
    }
    
    /// Release a FID
    pub fn clunk_fid(&mut self, fid: u32) -> Result<(), u32> {
        self.fid_table.remove(&fid).ok_or(9u32)?; // EBADF
        Ok(())
    }
    
    /// Get inode by number
    pub fn get_inode(&self, inode: u64) -> Result<&INode, u32> {
        self.inodes.get(&inode).ok_or(2u32) // ENOENT
    }
    
    /// Get inode by path
    pub fn get_inode_by_path(&self, path: &str) -> Result<&INode, u32> {
        let inode_num = self.path_to_inode.get(path).ok_or(2u32)?; // ENOENT
        self.get_inode(*inode_num)
    }
    
    /// Walk from a FID following path components
    pub fn walk(&mut self, from_fid: u32, to_fid: u32, wnames: &[String]) -> Result<Vec<Qid>, u32> {
        // Get starting vnode
        let from_vnode = self.get_fid(from_fid)?.clone();
        let mut current_inode = from_vnode.inode;
        let mut current_path = from_vnode.path.clone();
        let mut qids = Vec::new();
        
        // If wnames is empty, just clone the FID
        if wnames.is_empty() {
            let inode = self.get_inode(current_inode)?;
            qids.push(inode.qid);
            self.allocate_fid(to_fid, current_inode, current_path)?;
            return Ok(qids);
        }
        
        // Walk each component
        for wname in wnames {
            let inode = self.get_inode(current_inode)?;
            
            // Must be a directory to walk into
            if let FileContent::Directory(ref entries) = inode.content {
                // Find the named entry
                let entry = entries.iter()
                    .find(|e| e.name == *wname)
                    .ok_or(2u32)?; // ENOENT
                
                current_inode = entry.inode;
                current_path = if current_path == "/" {
                    format!("/{}", wname)
                } else {
                    format!("{}/{}", current_path, wname)
                };
                
                let next_inode = self.get_inode(current_inode)?;
                qids.push(next_inode.qid);
            } else {
                return Err(20); // ENOTDIR
            }
        }
        
        // Allocate the new FID
        self.allocate_fid(to_fid, current_inode, current_path)?;
        
        Ok(qids)
    }
    
    /// Read from a file
    pub fn read(&self, fid: u32, offset: u64, count: u32) -> Result<Vec<u8>, u32> {
        let vnode = self.get_fid(fid)?;
        
        if !vnode.is_open {
            return Err(9); // EBADF
        }
        
        let inode = self.get_inode(vnode.inode)?;
        
        match &inode.content {
            FileContent::Regular(data) => {
                let start = offset.min(data.len() as u64) as usize;
                let end = (offset + count as u64).min(data.len() as u64) as usize;
                Ok(data[start..end].to_vec())
            }
            _ => Err(21), // EISDIR
        }
    }
    
    /// Get root inode number
    pub fn root_inode(&self) -> u64 {
        self.root_inode
    }
}

impl Default for InMemoryFilesystem {
    fn default() -> Self {
        Self::new()
    }
}

/// In-Memory P9 Backend
///
/// This backend handles P9 operations entirely in-memory without any I/O.
/// Perfect for pre-loaded filesystems in zkVM guests.
pub struct InMemoryBackend {
    fs: InMemoryFilesystem,
}

impl InMemoryBackend {
    pub fn new() -> Self {
        Self {
            fs: InMemoryFilesystem::new(),
        }
    }
    
    pub fn from_snapshot(snapshot: FilesystemSnapshot) -> Self {
        Self {
            fs: InMemoryFilesystem::from_snapshot(snapshot),
        }
    }
    
    pub fn filesystem_mut(&mut self) -> &mut InMemoryFilesystem {
        &mut self.fs
    }
}

impl P9Backend for InMemoryBackend {
    fn send_tversion(&mut self, msg: &TversionMessage) -> Result<P9Response<RversionMessage>, TversionError> {
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
    
    fn send_tattach(&mut self, msg: &TattachMessage) -> Result<P9Response<RattachMessage>, TattachError> {
        // Allocate root FID
        match self.fs.allocate_fid(msg.fid, self.fs.root_inode(), "/".to_string()) {
            Ok(_) => {
                let root = self.fs.get_inode(self.fs.root_inode()).unwrap();
                Ok(P9Response::Success(RattachMessage {
                    tag: msg.tag,
                    qid: root.qid,
                }))
            }
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }
    
    fn send_twalk(&mut self, msg: &TwalkMessage) -> Result<P9Response<RwalkMessage>, TwalkError> {
        // Use in-memory walk operation
        match self.fs.walk(msg.fid, msg.newfid, &msg.wnames) {
            Ok(qids) => Ok(P9Response::Success(RwalkMessage {
                tag: msg.tag,
                nwqid: qids.len() as u16,
                wqids: qids,
            })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }
    
    fn send_tread(&mut self, msg: &TreadMessage) -> Result<P9Response<RreadMessage>, TreadError> {
        match self.fs.read(msg.fid, msg.offset, msg.count) {
            Ok(data) => Ok(P9Response::Success(RreadMessage {
                tag: msg.tag,
                count: data.len() as u32,
                data,
            })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }
    
    fn send_twrite(&mut self, _msg: &TwriteMessage) -> Result<P9Response<RwriteMessage>, TwriteError> {
        // TODO: Implement write support
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 38))) // ENOSYS
    }
    
    fn send_tlopen(&mut self, msg: &TlopenMessage) -> Result<P9Response<RlopenMessage>, TlopenError> {
        // Mark FID as open - get inode number first to avoid borrow issues
        let inode_num = match self.fs.get_fid(msg.fid) {
            Ok(vnode) => vnode.inode,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };
        
        let inode_qid = match self.fs.get_inode(inode_num) {
            Ok(inode) => inode.qid,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };
        
        // Now mark as open
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
    
    fn send_tlcreate(&mut self, _msg: &TlcreateMessage) -> Result<P9Response<RlcreateMessage>, TlcreateError> {
        // TODO: Implement file creation
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 38))) // ENOSYS
    }
    
    fn send_tgetattr(&mut self, msg: &TgetattrMessage) -> Result<P9Response<RgetattrMessage>, TgetattrError> {
        let vnode = match self.fs.get_fid(msg.fid) {
            Ok(v) => v,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };
        
        let inode = match self.fs.get_inode(vnode.inode) {
            Ok(i) => i,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };
        
        Ok(P9Response::Success(RgetattrMessage {
            tag: msg.tag,
            valid: msg.request_mask,
            qid: inode.qid,
            mode: inode.mode,
            uid: inode.uid,
            gid: inode.gid,
            nlink: inode.nlink,
            rdev: inode.rdev,
            size: inode.size,
            blksize: inode.blksize,
            blocks: inode.blocks,
            atime_sec: inode.atime_sec,
            atime_nsec: inode.atime_nsec,
            mtime_sec: inode.mtime_sec,
            mtime_nsec: inode.mtime_nsec,
            ctime_sec: inode.ctime_sec,
            ctime_nsec: inode.ctime_nsec,
            btime_sec: inode.btime_sec,
            btime_nsec: inode.btime_nsec,
            gen_: 0,
            data_version: 0,
        }))
    }
    
    fn send_tsetattr(&mut self, _msg: &TsetattrMessage) -> Result<P9Response<RsetattrMessage>, TsetattrError> {
        // TODO: Implement setattr
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 38))) // ENOSYS
    }
    
    fn send_treaddir(&mut self, _msg: &TreaddirMessage) -> Result<P9Response<RreaddirMessage>, TreaddirError> {
        // TODO: Implement readdir
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 38))) // ENOSYS
    }
    
    fn send_treadlink(&mut self, msg: &TreadlinkMessage) -> Result<P9Response<RreadlinkMessage>, TreadlinkError> {
        let vnode = match self.fs.get_fid(msg.fid) {
            Ok(v) => v,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };
        
        let inode = match self.fs.get_inode(vnode.inode) {
            Ok(i) => i,
            Err(errno) => return Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        };
        
        match &inode.content {
            FileContent::Symlink(target) => {
                Ok(P9Response::Success(RreadlinkMessage {
                    tag: msg.tag,
                    target: target.clone(),
                }))
            }
            _ => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 22))), // EINVAL
        }
    }
    
    fn send_tsymlink(&mut self, _msg: &TsymlinkMessage) -> Result<P9Response<RsymlinkMessage>, TsymlinkError> {
        // TODO: Implement symlink creation
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 38))) // ENOSYS
    }
    
    fn send_tmknod(&mut self, _msg: &TmknodMessage) -> Result<P9Response<RmknodMessage>, TmknodError> {
        // TODO: Implement mknod
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 38))) // ENOSYS
    }
    
    fn send_tmkdir(&mut self, _msg: &TmkdirMessage) -> Result<P9Response<RmkdirMessage>, TmkdirError> {
        // TODO: Implement mkdir
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 38))) // ENOSYS
    }
    
    fn send_tunlinkat(&mut self, _msg: &TunlinkatMessage) -> Result<P9Response<RunlinkatMessage>, TunlinkatError> {
        // TODO: Implement unlink
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 38))) // ENOSYS
    }
    
    fn send_trenameat(&mut self, _msg: &TrenameatMessage) -> Result<P9Response<RrenameatMessage>, TrenameatError> {
        // TODO: Implement rename
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 38))) // ENOSYS
    }
    
    fn send_tclunk(&mut self, msg: &TclunkMessage) -> Result<P9Response<RclunkMessage>, TclunkError> {
        match self.fs.clunk_fid(msg.fid) {
            Ok(_) => Ok(P9Response::Success(RclunkMessage {
                tag: msg.tag,
            })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }
    
    fn send_tremove(&mut self, _msg: &TremoveMessage) -> Result<P9Response<RremoveMessage>, TremoveError> {
        // TODO: Implement remove
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 38))) // ENOSYS
    }
    
    fn send_tfsync(&mut self, msg: &TfsyncMessage) -> Result<P9Response<RfsyncMessage>, TfsyncError> {
        // No-op for in-memory filesystem
        Ok(P9Response::Success(RfsyncMessage {
            tag: msg.tag,
        }))
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
}

impl P9Backend for ZeroCopyBackend {
    fn send_tversion(&mut self, msg: &TversionMessage) -> Result<P9Response<RversionMessage>, TversionError> {
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
    
    fn send_tattach(&mut self, msg: &TattachMessage) -> Result<P9Response<RattachMessage>, TattachError> {
        // Allocate root FID
        match self.fs.allocate_fid(msg.fid, self.fs.root_inode(), "/".to_string()) {
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
            Ok(qids) => Ok(P9Response::Success(RwalkMessage {
                tag: msg.tag,
                nwqid: qids.len() as u16,
                wqids: qids,
            })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
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
    
    fn send_twrite(&mut self, _msg: &TwriteMessage) -> Result<P9Response<RwriteMessage>, TwriteError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(_msg.tag, 30))) // EROFS
    }
    
    fn send_tlopen(&mut self, msg: &TlopenMessage) -> Result<P9Response<RlopenMessage>, TlopenError> {
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
    
    fn send_tlcreate(&mut self, msg: &TlcreateMessage) -> Result<P9Response<RlcreateMessage>, TlcreateError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }
    
    fn send_tgetattr(&mut self, msg: &TgetattrMessage) -> Result<P9Response<RgetattrMessage>, TgetattrError> {
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
    
    fn send_tsetattr(&mut self, msg: &TsetattrMessage) -> Result<P9Response<RsetattrMessage>, TsetattrError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }
    
    fn send_treaddir(&mut self, msg: &TreaddirMessage) -> Result<P9Response<RreaddirMessage>, TreaddirError> {
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
    
    fn send_treadlink(&mut self, msg: &TreadlinkMessage) -> Result<P9Response<RreadlinkMessage>, TreadlinkError> {
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
        let target = core::str::from_utf8(target_bytes)
            .map_err(|_| TreadlinkError::InvalidUtf8)?
            .to_string();
        
        Ok(P9Response::Success(RreadlinkMessage {
            tag: msg.tag,
            target,
        }))
    }
    
    fn send_tsymlink(&mut self, msg: &TsymlinkMessage) -> Result<P9Response<RsymlinkMessage>, TsymlinkError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }
    
    fn send_tmknod(&mut self, msg: &TmknodMessage) -> Result<P9Response<RmknodMessage>, TmknodError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }
    
    fn send_tmkdir(&mut self, msg: &TmkdirMessage) -> Result<P9Response<RmkdirMessage>, TmkdirError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }
    
    fn send_tunlinkat(&mut self, msg: &TunlinkatMessage) -> Result<P9Response<RunlinkatMessage>, TunlinkatError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }
    
    fn send_trenameat(&mut self, msg: &TrenameatMessage) -> Result<P9Response<RrenameatMessage>, TrenameatError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }
    
    fn send_tclunk(&mut self, msg: &TclunkMessage) -> Result<P9Response<RclunkMessage>, TclunkError> {
        match self.fs.clunk_fid(msg.fid) {
            Ok(_) => Ok(P9Response::Success(RclunkMessage {
                tag: msg.tag,
            })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }
    
    fn send_tremove(&mut self, msg: &TremoveMessage) -> Result<P9Response<RremoveMessage>, TremoveError> {
        // Read-only filesystem
        Ok(P9Response::Error(RlerrorMessage::new(msg.tag, 30))) // EROFS
    }
    
    fn send_tfsync(&mut self, msg: &TfsyncMessage) -> Result<P9Response<RfsyncMessage>, TfsyncError> {
        // No-op for zero-copy filesystem
        Ok(P9Response::Success(RfsyncMessage {
            tag: msg.tag,
        }))
    }
}

