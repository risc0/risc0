//! Mount Point Router and RAM Filesystem
//!
//! This module provides:
//! - MountBackend: Routes P9 requests to different backends based on mount points
//! - RamFilesystem: A simple in-memory writable filesystem for /tmp and similar use cases

#![allow(dead_code)]

use crate::constants::{S_IFDIR, S_IFLNK, S_IFMT, S_IFREG};
use crate::linux_abi_fs::{DT_DIR, DT_LNK, DT_REG};
use crate::p9::*;
use crate::p9_backend::P9Backend;

#[cfg(target_arch = "riscv32")]
use alloc::boxed::Box;
#[cfg(target_arch = "riscv32")]
use alloc::collections::BTreeMap;
#[cfg(target_arch = "riscv32")]
use alloc::format;
#[cfg(target_arch = "riscv32")]
use alloc::string::{String, ToString};
#[cfg(target_arch = "riscv32")]
use alloc::vec::Vec;

#[cfg(not(target_arch = "riscv32"))]
use std::boxed::Box;
#[cfg(not(target_arch = "riscv32"))]
use std::collections::BTreeMap;
#[cfg(not(target_arch = "riscv32"))]
use std::format;
#[cfg(not(target_arch = "riscv32"))]
use std::string::String;
#[cfg(not(target_arch = "riscv32"))]
use std::vec::Vec;

// Debug flag for mount backend
const MOUNT_DEBUG: bool = true;

//==============================================================================
// RAM FILESYSTEM
//==============================================================================

/// In-memory file/directory node
#[derive(Clone, Debug)]
enum RamNode {
    File {
        data: Vec<u8>,
        mode: u32,
        uid: u32,
        gid: u32,
    },
    Directory {
        entries: BTreeMap<String, u64>, // name -> inode
        mode: u32,
        uid: u32,
        gid: u32,
    },
    Symlink {
        target: String,
        mode: u32,
        uid: u32,
        gid: u32,
    },
}

/// RAM filesystem - simple in-memory writable filesystem
pub struct RamFilesystem {
    /// Inode table: inode -> node data
    nodes: BTreeMap<u64, RamNode>,
    /// Next inode number to allocate
    next_inode: u64,
    /// Root inode (always 1)
    root_inode: u64,
    /// FID table: fid -> (inode, path)
    fid_table: BTreeMap<u32, (u64, String)>,
    /// QID version counter (increments on modification)
    qid_versions: BTreeMap<u64, u32>,
}

impl RamFilesystem {
    const DEFAULT_SYMLINK_PERMS: u32 = 0o777;

    /// Create a new empty RAM filesystem
    pub fn new() -> Self {
        let mut fs = Self {
            nodes: BTreeMap::new(),
            next_inode: 2, // Start at 2, 1 is root
            root_inode: 1,
            fid_table: BTreeMap::new(),
            qid_versions: BTreeMap::new(),
        };

        // Create root directory
        fs.nodes.insert(
            1,
            RamNode::Directory {
                entries: BTreeMap::new(),
                mode: S_IFDIR | 0o755,
                uid: 0,
                gid: 0,
            },
        );
        fs.qid_versions.insert(1, 0);

        fs
    }

    fn get_qid(&self, inode: u64) -> Qid {
        let qtype = if self.is_dir(inode) {
            P9QidType::Qtdir as u8
        } else if self.is_symlink(inode) {
            P9QidType::Qtsymlink as u8
        } else {
            P9QidType::Qtfile as u8
        };
        let version = self.qid_versions.get(&inode).copied().unwrap_or(0);
        Qid::new(qtype, version, inode)
    }

    fn is_dir(&self, inode: u64) -> bool {
        matches!(self.nodes.get(&inode), Some(RamNode::Directory { .. }))
    }

    fn is_symlink(&self, inode: u64) -> bool {
        matches!(self.nodes.get(&inode), Some(RamNode::Symlink { .. }))
    }

    fn is_regular(&self, inode: u64) -> bool {
        matches!(self.nodes.get(&inode), Some(RamNode::File { .. }))
    }

    fn allocate_fid(&mut self, fid: u32, inode: u64, path: String) -> Result<(), u32> {
        if self.fid_table.len() >= 1024 {
            return Err(P9Error::Emfile as u32);
        }
        if self.fid_table.contains_key(&fid) {
            return Err(P9Error::Eexist as u32);
        }
        self.fid_table.insert(fid, (inode, path));
        Ok(())
    }

    fn get_fid(&self, fid: u32) -> Result<(u64, String), u32> {
        self.fid_table
            .get(&fid)
            .cloned()
            .ok_or(P9Error::Ebadf as u32)
    }

    fn get_fid_mut(&mut self, fid: u32) -> Result<&mut (u64, String), u32> {
        self.fid_table.get_mut(&fid).ok_or(P9Error::Ebadf as u32)
    }

    fn clunk_fid(&mut self, fid: u32) -> Result<(), u32> {
        self.fid_table.remove(&fid).ok_or(P9Error::Ebadf as u32)?;
        Ok(())
    }

    fn walk(&mut self, from_fid: u32, to_fid: u32, wnames: &[String]) -> Result<Vec<Qid>, u32> {
        let (from_inode, from_path) = self.get_fid(from_fid)?;
        let mut current_inode = from_inode;
        let mut current_path = from_path.clone();
        let mut qids = Vec::new();

        if wnames.is_empty() {
            // Clone FID
            qids.push(self.get_qid(current_inode));
            if from_fid == to_fid {
                // Same FID - just update the path (though it should be the same)
                // Actually, if same FID and empty wnames, nothing to do
                return Ok(qids);
            }
            self.allocate_fid(to_fid, current_inode, current_path)?;
            return Ok(qids);
        }

        for wname in wnames {
            if !self.is_dir(current_inode) {
                return Err(P9Error::Enotdir as u32);
            }

            // Handle special path components
            let next_inode = if wname == "." {
                // "." refers to the current directory
                current_inode
            } else if wname == ".." {
                // ".." refers to the parent directory
                // Find the parent of current_inode
                let mut parent_inode = None;
                for (node_inode, node) in &self.nodes {
                    let found_parent = if let RamNode::Directory { entries, .. } = node {
                        entries
                            .values()
                            .any(|&entry_inode| entry_inode == current_inode)
                    } else {
                        false
                    };
                    if found_parent {
                        parent_inode = Some(*node_inode);
                        break;
                    }
                }
                // If no parent found, we're at root, so ".." is root itself
                parent_inode.unwrap_or(self.root_inode)
            } else {
                // Normal path component - look it up in the directory
                let dir = match self.nodes.get(&current_inode) {
                    Some(RamNode::Directory { entries, .. }) => entries,
                    _ => return Err(P9Error::Enotdir as u32),
                };
                dir.get(wname).copied().ok_or(P9Error::Enoent as u32)?
            };

            current_inode = next_inode;
            // Only update path for non-special components
            if wname != "." && wname != ".." {
                current_path = if current_path == "/" {
                    format!("/{}", wname)
                } else {
                    format!("{}/{}", current_path, wname)
                };
            } else if wname == ".." {
                // Update path to parent
                if current_path == "/" {
                    // Already at root, stay at root
                } else {
                    // Remove last component
                    if let Some(last_slash) = current_path.rfind('/') {
                        if last_slash == 0 {
                            current_path = "/".to_string();
                        } else {
                            current_path = current_path[..last_slash].to_string();
                        }
                    }
                }
            }
            qids.push(self.get_qid(current_inode));
        }

        // If walking to the same FID, update it instead of allocating
        if from_fid == to_fid {
            // Update existing FID entry
            let fid_entry = self.get_fid_mut(to_fid)?;
            *fid_entry = (current_inode, current_path);
        } else {
            // Allocate new FID - if it already exists, clunk it first
            if self.fid_table.contains_key(&to_fid) {
                // FID already exists, clunk it first
                let _ = self.clunk_fid(to_fid);
            }
            self.allocate_fid(to_fid, current_inode, current_path)?;
        }
        Ok(qids)
    }

    fn create_file(&mut self, parent_inode: u64, name: String, mode: u32) -> Result<u64, u32> {
        if !self.is_dir(parent_inode) {
            return Err(P9Error::Enotdir as u32);
        }

        let dir = match self.nodes.get_mut(&parent_inode) {
            Some(RamNode::Directory { entries, .. }) => entries,
            _ => return Err(P9Error::Enotdir as u32),
        };

        if dir.contains_key(&name) {
            return Err(P9Error::Eexist as u32);
        }

        let inode = self.next_inode;
        self.next_inode += 1;

        dir.insert(name, inode);
        self.nodes.insert(
            inode,
            RamNode::File {
                data: Vec::new(),
                // Preserve special bits (setuid/setgid/sticky, 0o7000) and permission bits (0o777)
                // Mask out file type bits and add S_IFREG
                mode: S_IFREG | (mode & 0o7777),
                uid: 0,
                gid: 0,
            },
        );
        self.qid_versions.insert(inode, 0);

        // Increment parent version
        if let Some(version) = self.qid_versions.get_mut(&parent_inode) {
            *version = version.wrapping_add(1);
        }

        Ok(inode)
    }

    fn create_directory(
        &mut self,
        parent_inode: u64,
        name: String,
        mode: u32,
        gid: u32,
    ) -> Result<u64, u32> {
        if !self.is_dir(parent_inode) {
            return Err(P9Error::Enotdir as u32);
        }

        let dir = match self.nodes.get_mut(&parent_inode) {
            Some(RamNode::Directory { entries, .. }) => entries,
            _ => return Err(P9Error::Enotdir as u32),
        };

        if dir.contains_key(&name) {
            return Err(P9Error::Eexist as u32);
        }

        let inode = self.next_inode;
        self.next_inode += 1;

        dir.insert(name, inode);
        self.nodes.insert(
            inode,
            RamNode::Directory {
                entries: BTreeMap::new(),
                // Preserve special bits (setuid/setgid/sticky, 0o7000) and permission bits (0o777)
                // Mask out file type bits and add S_IFDIR
                mode: S_IFDIR | (mode & 0o7777),
                uid: 0,
                gid,
            },
        );
        self.qid_versions.insert(inode, 0);

        // Increment parent version
        if let Some(version) = self.qid_versions.get_mut(&parent_inode) {
            *version = version.wrapping_add(1);
        }

        Ok(inode)
    }

    fn create_symlink(
        &mut self,
        parent_inode: u64,
        name: String,
        target: String,
        gid: u32,
    ) -> Result<u64, u32> {
        if !self.is_dir(parent_inode) {
            return Err(P9Error::Enotdir as u32);
        }

        let dir = match self.nodes.get_mut(&parent_inode) {
            Some(RamNode::Directory { entries, .. }) => entries,
            _ => return Err(P9Error::Enotdir as u32),
        };

        if dir.contains_key(&name) {
            return Err(P9Error::Eexist as u32);
        }

        let inode = self.next_inode;
        self.next_inode += 1;

        dir.insert(name, inode);
        self.nodes.insert(
            inode,
            RamNode::Symlink {
                target,
                mode: S_IFLNK | Self::DEFAULT_SYMLINK_PERMS,
                uid: 0,
                gid,
            },
        );
        self.qid_versions.insert(inode, 0);

        if let Some(version) = self.qid_versions.get_mut(&parent_inode) {
            *version = version.wrapping_add(1);
        }

        Ok(inode)
    }

    fn read_file(&self, inode: u64, offset: u64, count: u32) -> Result<Vec<u8>, u32> {
        match self.nodes.get(&inode) {
            Some(RamNode::File { data, .. }) => {
                let start = offset.min(data.len() as u64) as usize;
                let end = (offset + count as u64).min(data.len() as u64) as usize;
                Ok(data[start..end].to_vec())
            }
            _ => Err(P9Error::Eisdir as u32),
        }
    }

    fn write_file(&mut self, inode: u64, offset: u64, data: &[u8]) -> Result<u32, u32> {
        match self.nodes.get_mut(&inode) {
            Some(RamNode::File {
                data: file_data, ..
            }) => {
                let offset = offset as usize;
                if offset + data.len() > file_data.len() {
                    file_data.resize(offset + data.len(), 0);
                }
                file_data[offset..offset + data.len()].copy_from_slice(data);

                // Increment version on write
                if let Some(version) = self.qid_versions.get_mut(&inode) {
                    *version = version.wrapping_add(1);
                }

                Ok(data.len() as u32)
            }
            _ => Err(P9Error::Eisdir as u32),
        }
    }

    fn read_dir(&self, inode: u64) -> Result<Vec<(String, Qid, u8)>, u32> {
        match self.nodes.get(&inode) {
            Some(RamNode::Directory { entries, .. }) => {
                let mut result = Vec::new();
                for (name, &entry_inode) in entries {
                    let qid = self.get_qid(entry_inode);
                    let entry_type = if self.is_dir(entry_inode) {
                        DT_DIR
                    } else if self.is_symlink(entry_inode) {
                        DT_LNK
                    } else {
                        DT_REG
                    };
                    result.push((name.clone(), qid, entry_type));
                }
                Ok(result)
            }
            _ => Err(P9Error::Enotdir as u32),
        }
    }
}

impl P9Backend for RamFilesystem {
    fn send_tversion(
        &mut self,
        msg: &TversionMessage,
    ) -> Result<P9Response<RversionMessage>, TversionError> {
        Ok(P9Response::Success(RversionMessage {
            tag: msg.tag,
            msize: msg.msize.min(8192),
            version: if msg.version == "9P2000.L" {
                "9P2000.L"
            } else {
                "unknown"
            },
        }))
    }

    fn send_tattach(
        &mut self,
        msg: &TattachMessage,
    ) -> Result<P9Response<RattachMessage>, TattachError> {
        match self.allocate_fid(msg.fid, self.root_inode, "/".to_string()) {
            Ok(_) => Ok(P9Response::Success(RattachMessage {
                tag: msg.tag,
                qid: self.get_qid(self.root_inode),
            })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }

    fn send_twalk(&mut self, msg: &TwalkMessage) -> Result<P9Response<RwalkMessage>, TwalkError> {
        if MOUNT_DEBUG {
            crate::kernel::print(&format!(
                "[RamFilesystem] send_twalk: fid={} newfid={} wnames={:?}",
                msg.fid, msg.newfid, msg.wnames
            ));
        }
        match self.walk(msg.fid, msg.newfid, &msg.wnames) {
            Ok(qids) => {
                if MOUNT_DEBUG {
                    crate::kernel::print(&format!(
                        "[RamFilesystem] send_twalk: success, nwqid={}",
                        qids.len()
                    ));
                }
                Ok(P9Response::Success(RwalkMessage {
                    tag: msg.tag,
                    nwqid: qids.len() as u16,
                    wqids: qids,
                }))
            }
            Err(errno) => {
                if MOUNT_DEBUG {
                    crate::kernel::print(&format!(
                        "[RamFilesystem] send_twalk: error, errno={}",
                        errno
                    ));
                }
                Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno)))
            }
        }
    }

    fn send_tread(&mut self, msg: &TreadMessage) -> Result<P9Response<RreadMessage>, TreadError> {
        let (inode, _) = self
            .get_fid(msg.fid)
            .map_err(|_| TreadError::InternalError)?;
        match self.read_file(inode, msg.offset, msg.count) {
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
        msg: &TwriteMessage,
    ) -> Result<P9Response<RwriteMessage>, TwriteError> {
        let (inode, _) = self
            .get_fid(msg.fid)
            .map_err(|_| TwriteError::InternalError)?;
        match self.write_file(inode, msg.offset, &msg.data) {
            Ok(count) => Ok(P9Response::Success(RwriteMessage {
                tag: msg.tag,
                count,
            })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }

    fn send_tlopen(
        &mut self,
        msg: &TlopenMessage,
    ) -> Result<P9Response<RlopenMessage>, TlopenError> {
        let (inode, _) = self
            .get_fid(msg.fid)
            .map_err(|_| TlopenError::InternalError)?;
        Ok(P9Response::Success(RlopenMessage {
            tag: msg.tag,
            qid: self.get_qid(inode),
            iounit: 8192,
        }))
    }

    fn send_tlcreate(
        &mut self,
        msg: &TlcreateMessage,
    ) -> Result<P9Response<RlcreateMessage>, TlcreateError> {
        let (parent_inode, _) = self
            .get_fid(msg.fid)
            .map_err(|_| TlcreateError::InternalError)?;
        match self.create_file(parent_inode, msg.name.clone(), msg.mode) {
            Ok(inode) => {
                // Update FID to point to new file
                if let Ok((fid_inode, _)) = self.get_fid_mut(msg.fid) {
                    *fid_inode = inode;
                }
                Ok(P9Response::Success(RlcreateMessage {
                    tag: msg.tag,
                    qid: self.get_qid(inode),
                    iounit: 8192,
                }))
            }
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }

    fn send_tgetattr(
        &mut self,
        msg: &TgetattrMessage,
    ) -> Result<P9Response<RgetattrMessage>, TgetattrError> {
        let (inode, _) = self
            .get_fid(msg.fid)
            .map_err(|_| TgetattrError::InternalError)?;
        let (mode, uid, gid, size) = match self.nodes.get(&inode) {
            Some(RamNode::File {
                data,
                mode,
                uid,
                gid,
                ..
            }) => (*mode, *uid, *gid, data.len() as u64),
            Some(RamNode::Directory { mode, uid, gid, .. }) => (*mode, *uid, *gid, 0),
            Some(RamNode::Symlink { mode, uid, gid, .. }) => (*mode, *uid, *gid, 0),
            None => {
                return Ok(P9Response::Error(RlerrorMessage::new(
                    msg.tag,
                    P9Error::Enoent as u32,
                )));
            }
        };

        Ok(P9Response::Success(RgetattrMessage {
            tag: msg.tag,
            valid: msg.request_mask,
            qid: self.get_qid(inode),
            mode,
            uid,
            gid,
            nlink: 1,
            rdev: 0,
            size,
            blksize: 4096,
            blocks: size.div_ceil(4096),
            atime_sec: 0,
            atime_nsec: 0,
            mtime_sec: 0,
            mtime_nsec: 0,
            ctime_sec: 0,
            ctime_nsec: 0,
            btime_sec: 0,
            btime_nsec: 0,
            gen_: 0,
            data_version: 0,
        }))
    }

    fn send_tsetattr(
        &mut self,
        msg: &TsetattrMessage,
    ) -> Result<P9Response<RsetattrMessage>, TsetattrError> {
        if MOUNT_DEBUG {
            crate::kernel::print(&format!(
                "[RamFilesystem] send_tsetattr: fid={}, valid=0x{:x}, size={}",
                msg.fid, msg.valid, msg.size
            ));
        }

        let (inode, _) = self
            .get_fid(msg.fid)
            .map_err(|_| TsetattrError::InternalError)?;

        let node = self
            .nodes
            .get_mut(&inode)
            .ok_or(TsetattrError::InternalError)?;

        // Check which attributes to set based on valid mask
        if (msg.valid & P9SetattrMask::Size as u32) != 0 {
            // Truncate or extend file size
            match node {
                RamNode::File { data, .. } => {
                    if msg.size < data.len() as u64 {
                        // Truncate
                        data.truncate(msg.size as usize);
                        if MOUNT_DEBUG {
                            crate::kernel::print(&format!(
                                "[RamFilesystem] send_tsetattr: truncated file inode {} to {} bytes",
                                inode, msg.size
                            ));
                        }
                    } else if msg.size > data.len() as u64 {
                        // Extend with zeros
                        data.resize(msg.size as usize, 0);
                        if MOUNT_DEBUG {
                            crate::kernel::print(&format!(
                                "[RamFilesystem] send_tsetattr: extended file inode {} to {} bytes",
                                inode, msg.size
                            ));
                        }
                    }
                    // Update QID version when file is modified
                    if let Some(version) = self.qid_versions.get_mut(&inode) {
                        *version = version.wrapping_add(1);
                    }
                }
                RamNode::Directory { .. } | RamNode::Symlink { .. } => {
                    // For directories and symlinks, ignore size setting if size is 0
                    // (this can happen when chmod sets the valid mask but size=0)
                    // Only return error if trying to set a non-zero size
                    if msg.size != 0 {
                        if MOUNT_DEBUG {
                            crate::kernel::print(&format!(
                                "[RamFilesystem] send_tsetattr: ERROR - cannot set non-zero size on non-file inode {}",
                                inode
                            ));
                        }
                        return Ok(P9Response::Error(RlerrorMessage::new(
                            msg.tag,
                            P9Error::Eisdir as u32,
                        )));
                    }
                    // Otherwise, silently ignore size=0 for directories/symlinks
                }
            }
        }

        if (msg.valid & P9SetattrMask::Mode as u32) != 0 {
            match node {
                RamNode::File { mode, .. } => {
                    // Preserve file type bits, update special bits (0o7000) and permission bits (0o777)
                    *mode = (*mode & S_IFMT) | (msg.mode & 0o7777);
                }
                RamNode::Directory { mode, .. } => {
                    // Preserve file type bits, update special bits (0o7000) and permission bits (0o777)
                    *mode = (*mode & S_IFMT) | (msg.mode & 0o7777);
                }
                RamNode::Symlink { mode, .. } => {
                    // Preserve file type bits, update special bits (0o7000) and permission bits (0o777)
                    *mode = (*mode & S_IFMT) | (msg.mode & 0o7777);
                }
            }
        }

        // When only uid/gid are being changed (not mode), Linux clears setuid/setgid bits
        // on regular files according to specific rules:
        // - Always clear setuid (0o4000) on regular files
        // - Clear setgid (0o2000) on regular files only if group-executable (0o0010)
        // - For directories, preserve setgid
        let should_clear_special_bits = (msg.valid & P9SetattrMask::Uid as u32) != 0
            || (msg.valid & P9SetattrMask::Gid as u32) != 0;
        let mode_not_changing = (msg.valid & P9SetattrMask::Mode as u32) == 0;

        if (msg.valid & P9SetattrMask::Uid as u32) != 0 {
            match node {
                RamNode::File { uid, .. } => *uid = msg.uid,
                RamNode::Directory { uid, .. } => *uid = msg.uid,
                RamNode::Symlink { uid, .. } => *uid = msg.uid,
            }
        }

        if (msg.valid & P9SetattrMask::Gid as u32) != 0 {
            match node {
                RamNode::File { gid, .. } => *gid = msg.gid,
                RamNode::Directory { gid, .. } => *gid = msg.gid,
                RamNode::Symlink { gid, .. } => *gid = msg.gid,
            }
        }

        // Clear setuid/setgid bits on regular files when only uid/gid changed (fchown behavior)
        if should_clear_special_bits && mode_not_changing {
            match node {
                RamNode::File { mode, .. } => {
                    // Always clear setuid (0o4000)
                    *mode &= !0o4000;
                    // Clear setgid (0o2000) only if group-executable (0o0010)
                    if (*mode & 0o0010) != 0 {
                        *mode &= !0o2000;
                    }
                    // Update QID version when mode is modified
                    if let Some(version) = self.qid_versions.get_mut(&inode) {
                        *version = version.wrapping_add(1);
                    }
                }
                RamNode::Directory { .. } | RamNode::Symlink { .. } => {
                    // For directories and symlinks, preserve setgid (Linux behavior)
                    // Do nothing
                }
            }
        }

        // Note: We don't handle atime/mtime here as they're not stored in RamNode
        // P9SetattrMask::Atime = 0x00000010
        // P9SetattrMask::Mtime = 0x00000020

        Ok(P9Response::Success(RsetattrMessage { tag: msg.tag }))
    }

    fn send_treaddir(
        &mut self,
        msg: &TreaddirMessage,
    ) -> Result<P9Response<RreaddirMessage>, TreaddirError> {
        let (inode, _) = self
            .get_fid(msg.fid)
            .map_err(|_| TreaddirError::InternalError)?;
        match self.read_dir(inode) {
            Ok(entries) => {
                // Simple serialization - just return all entries
                let mut data = Vec::new();
                let mut offset = 0u64;
                for (name, qid, entry_type) in entries {
                    if data.len() + 13 + 8 + 1 + 2 + name.len() > msg.count as usize {
                        break;
                    }
                    // qid[13]
                    data.push(qid.qtype);
                    data.extend_from_slice(&qid.version.to_le_bytes());
                    data.extend_from_slice(&qid.path.to_le_bytes());
                    // offset[8]
                    offset += 1;
                    data.extend_from_slice(&offset.to_le_bytes());
                    // type[1]
                    data.push(entry_type);
                    // name[s] = length[2] + name[length]
                    let name_len = name.len().min(u16::MAX as usize) as u16;
                    data.extend_from_slice(&name_len.to_le_bytes());
                    data.extend_from_slice(name.as_bytes());
                }
                Ok(P9Response::Success(RreaddirMessage {
                    tag: msg.tag,
                    count: data.len() as u32,
                    data,
                }))
            }
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }

    fn send_treadlink(
        &mut self,
        msg: &TreadlinkMessage,
    ) -> Result<P9Response<RreadlinkMessage>, TreadlinkError> {
        let (inode, _) = self
            .get_fid(msg.fid)
            .map_err(|_| TreadlinkError::InvalidUtf8)?;
        match self.nodes.get(&inode) {
            Some(RamNode::Symlink { target, .. }) => Ok(P9Response::Success(RreadlinkMessage {
                tag: msg.tag,
                target: target.clone(),
            })),
            _ => Ok(P9Response::Error(RlerrorMessage::new(
                msg.tag,
                P9Error::Einval as u32,
            ))),
        }
    }

    fn send_tsymlink(
        &mut self,
        msg: &TsymlinkMessage,
    ) -> Result<P9Response<RsymlinkMessage>, TsymlinkError> {
        let (parent_inode, _) = self
            .get_fid(msg.fid)
            .map_err(|_| TsymlinkError::InternalError)?;
        match self.create_symlink(parent_inode, msg.name.clone(), msg.symtgt.clone(), msg.gid) {
            Ok(inode) => Ok(P9Response::Success(RsymlinkMessage {
                tag: msg.tag,
                qid: self.get_qid(inode),
            })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }

    fn send_tmknod(
        &mut self,
        _msg: &TmknodMessage,
    ) -> Result<P9Response<RmknodMessage>, TmknodError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Enosys as u32,
        )))
    }

    fn send_tmkdir(
        &mut self,
        msg: &TmkdirMessage,
    ) -> Result<P9Response<RmkdirMessage>, TmkdirError> {
        let (parent_inode, _) = self
            .get_fid(msg.dfid)
            .map_err(|_| TmkdirError::InternalError)?;
        match self.create_directory(parent_inode, msg.name.clone(), msg.mode, msg.gid) {
            Ok(inode) => {
                if MOUNT_DEBUG {
                    crate::kernel::print(&format!(
                        "[RamFilesystem] send_tmkdir: created directory '{}' inode={}",
                        msg.name, inode
                    ));
                }
                Ok(P9Response::Success(RmkdirMessage {
                    tag: msg.tag,
                    qid: self.get_qid(inode),
                }))
            }
            Err(errno) => {
                if MOUNT_DEBUG {
                    crate::kernel::print(&format!(
                        "[RamFilesystem] send_tmkdir: error creating '{}', errno={}",
                        msg.name, errno
                    ));
                }
                Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno)))
            }
        }
    }

    fn send_tunlinkat(
        &mut self,
        _msg: &TunlinkatMessage,
    ) -> Result<P9Response<RunlinkatMessage>, TunlinkatError> {
        // TODO: Implement unlink
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Enosys as u32,
        )))
    }

    fn send_trenameat(
        &mut self,
        _msg: &TrenameatMessage,
    ) -> Result<P9Response<RrenameatMessage>, TrenameatError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Enosys as u32,
        )))
    }

    fn send_tclunk(
        &mut self,
        msg: &TclunkMessage,
    ) -> Result<P9Response<RclunkMessage>, TclunkError> {
        match self.clunk_fid(msg.fid) {
            Ok(_) => Ok(P9Response::Success(RclunkMessage { tag: msg.tag })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
        }
    }

    fn send_tremove(
        &mut self,
        msg: &TremoveMessage,
    ) -> Result<P9Response<RremoveMessage>, TremoveError> {
        let (inode, _path) = self
            .get_fid(msg.fid)
            .map_err(|_| TremoveError::InternalError)?;

        if inode == self.root_inode {
            // Cannot remove root directory
            if MOUNT_DEBUG {
                crate::kernel::print("[RamFilesystem] send_tremove: cannot remove root directory");
            }
            return Ok(P9Response::Error(RlerrorMessage::new(
                msg.tag,
                P9Error::Eperm as u32,
            )));
        }

        // Find the parent directory that contains this inode
        let mut parent_inode = None;
        let mut entry_name = None;

        for (node_inode, node) in &self.nodes {
            if let RamNode::Directory { entries, .. } = node {
                for (name, &entry_inode) in entries {
                    if entry_inode == inode {
                        parent_inode = Some(*node_inode);
                        entry_name = Some(name.clone());
                        break;
                    }
                }
                if parent_inode.is_some() {
                    break;
                }
            }
        }

        let parent_inode = parent_inode.ok_or_else(|| {
            if MOUNT_DEBUG {
                crate::kernel::print(&format!(
                    "[RamFilesystem] send_tremove: inode {} not found in any directory",
                    inode
                ));
            }
            TremoveError::InternalError
        })?;

        let entry_name = entry_name.unwrap();

        // Check if it's a directory and if it's empty
        if self.is_dir(inode)
            && let Some(RamNode::Directory { entries, .. }) = self.nodes.get(&inode)
            && !entries.is_empty()
        {
            if MOUNT_DEBUG {
                crate::kernel::print(&format!(
                    "[RamFilesystem] send_tremove: directory '{}' is not empty",
                    entry_name
                ));
            }
            return Ok(P9Response::Error(RlerrorMessage::new(
                msg.tag,
                P9Error::Enotempty as u32,
            )));
        }

        // Remove the entry from parent directory
        if let Some(RamNode::Directory { entries, .. }) = self.nodes.get_mut(&parent_inode) {
            entries.remove(&entry_name);
            // Increment parent version
            if let Some(version) = self.qid_versions.get_mut(&parent_inode) {
                *version = version.wrapping_add(1);
            }
        }

        // Remove the node itself
        self.nodes.remove(&inode);
        self.qid_versions.remove(&inode);

        // Remove the FID (it's being removed)
        self.fid_table.remove(&msg.fid);

        if MOUNT_DEBUG {
            crate::kernel::print(&format!(
                "[RamFilesystem] send_tremove: removed '{}' (inode={})",
                entry_name, inode
            ));
        }

        Ok(P9Response::Success(RremoveMessage { tag: msg.tag }))
    }

    fn send_tfsync(
        &mut self,
        msg: &TfsyncMessage,
    ) -> Result<P9Response<RfsyncMessage>, TfsyncError> {
        Ok(P9Response::Success(RfsyncMessage { tag: msg.tag }))
    }

    fn send_tlink(&mut self, _msg: &TlinkMessage) -> Result<P9Response<RlinkMessage>, TlinkError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Enosys as u32,
        )))
    }

    fn send_trename(
        &mut self,
        _msg: &TrenameMessage,
    ) -> Result<P9Response<RrenameMessage>, TrenameError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Enosys as u32,
        )))
    }

    fn send_txattrwalk(
        &mut self,
        _msg: &TxattrwalkMessage,
    ) -> Result<P9Response<RxattrwalkMessage>, TxattrwalkError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Eopnotsupp as u32,
        )))
    }

    fn send_txattrcreate(
        &mut self,
        _msg: &TxattrcreateMessage,
    ) -> Result<P9Response<RxattrcreateMessage>, TxattrcreateError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Enosys as u32,
        )))
    }

    fn send_tflush(
        &mut self,
        msg: &TflushMessage,
    ) -> Result<P9Response<RflushMessage>, TflushError> {
        Ok(P9Response::Success(RflushMessage { tag: msg.tag }))
    }

    fn send_tauth(&mut self, msg: &TauthMessage) -> Result<P9Response<RauthMessage>, TauthError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            msg.tag,
            P9Error::Enosys as u32,
        )))
    }

    fn send_tstatfs(
        &mut self,
        _msg: &TstatfsMessage,
    ) -> Result<P9Response<RstatfsMessage>, TstatfsError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Enosys as u32,
        )))
    }

    fn send_tlock(&mut self, msg: &TlockMessage) -> Result<P9Response<RlockMessage>, TlockError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            msg.tag,
            P9Error::Enosys as u32,
        )))
    }

    fn send_tgetlock(
        &mut self,
        msg: &TgetlockMessage,
    ) -> Result<P9Response<RgetlockMessage>, TgetlockError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            msg.tag,
            P9Error::Enosys as u32,
        )))
    }
}

//==============================================================================
// MOUNT BACKEND
//==============================================================================

/// Mount point entry
struct MountPoint {
    path: String,                // Mount point path (e.g., "/tmp")
    backend: Box<dyn P9Backend>, // The mounted backend
}

/// FID tracking information
struct FidInfo {
    /// Which backend this FID belongs to (None = root, Some(index) = mount)
    backend_index: Option<usize>,
    /// Current path of this FID
    path: String,
}

/// Mount backend that routes requests to different backends based on mount points
pub struct MountBackend {
    /// Root backend (zero-copy filesystem)
    root: Box<dyn P9Backend>,
    /// Mount points: path -> backend
    /// Sorted by path length (longest first) for proper matching
    mounts: Vec<MountPoint>,
    /// FID -> backend mapping and path tracking
    fid_map: BTreeMap<u32, FidInfo>,
}

impl MountBackend {
    /// Debug logging helper
    fn debug_log(&self, msg: &str) {
        if MOUNT_DEBUG {
            crate::kernel::print(&format!("[MountBackend] {}", msg));
        }
    }

    /// Create a new mount backend with a root backend
    pub fn new(root: Box<dyn P9Backend>) -> Self {
        if MOUNT_DEBUG {
            crate::kernel::print("[MountBackend] Creating new MountBackend");
        }
        Self {
            root,
            mounts: Vec::new(),
            fid_map: BTreeMap::new(),
        }
    }

    /// Mount a backend at a given path
    pub fn mount(&mut self, path: String, backend: Box<dyn P9Backend>) -> Result<(), u32> {
        self.debug_log(&format!("mount: attempting to mount at '{}'", path));

        // Normalize path: ensure it starts with / and ends with / (except root)
        let normalized = if path == "/" {
            self.debug_log("mount: ERROR - cannot mount over root");
            return Err(P9Error::Einval as u32); // Can't mount over root
        } else if !path.starts_with('/') {
            format!("/{}", path)
        } else {
            path.clone()
        };

        self.debug_log(&format!("mount: normalized path to '{}'", normalized));

        // Check for conflicts
        for mount in &self.mounts {
            if mount.path == normalized || normalized.starts_with(&mount.path) {
                self.debug_log(&format!(
                    "mount: ERROR - conflict with existing mount at '{}'",
                    mount.path
                ));
                return Err(P9Error::Ebusy as u32); // Mount point conflict
            }
        }

        self.mounts.push(MountPoint {
            path: normalized.clone(),
            backend,
        });

        // Sort by path length (longest first) for proper prefix matching
        self.mounts.sort_by(|a, b| b.path.len().cmp(&a.path.len()));

        self.debug_log(&format!(
            "mount: successfully mounted at '{}' (total mounts: {})",
            normalized,
            self.mounts.len()
        ));

        Ok(())
    }

    /// Find the backend and remaining path for a given absolute path
    fn find_backend(&mut self, path: &str) -> (&mut dyn P9Backend, String, Option<usize>) {
        // Check mount points (longest first due to sorting)
        for (idx, mount) in self.mounts.iter_mut().enumerate() {
            if path.starts_with(&mount.path) {
                // Path is under this mount point
                let remaining = if path.len() == mount.path.len() {
                    "/".to_string()
                } else {
                    path[mount.path.len()..].to_string()
                };
                return (mount.backend.as_mut(), remaining, Some(idx));
            }
        }

        // No mount point matches, use root
        (self.root.as_mut(), path.to_string(), None)
    }

    /// Get backend for a FID
    fn get_backend_for_fid(&mut self, fid: u32) -> Result<&mut dyn P9Backend, u32> {
        match self.fid_map.get(&fid) {
            Some(FidInfo {
                backend_index: None,
                ..
            }) => Ok(self.root.as_mut()),
            Some(FidInfo {
                backend_index: Some(idx),
                ..
            }) => Ok(self.mounts[*idx].backend.as_mut()),
            None => Err(P9Error::Ebadf as u32),
        }
    }

    /// Normalize a path (ensure it starts with /)
    fn normalize_path(path: &str) -> String {
        if path.starts_with('/') {
            path.to_string()
        } else {
            format!("/{}", path)
        }
    }

    /// Build a path from components
    fn build_path(base: &str, components: &[String]) -> String {
        let mut path = base.to_string();
        for component in components {
            if path == "/" {
                path = format!("/{}", component);
            } else {
                path = format!("{}/{}", path, component);
            }
        }
        path
    }

    /// Check if a path crosses a mount point boundary
    fn check_mount_crossing(&self, from_path: &str, to_path: &str) -> Option<(usize, String)> {
        if MOUNT_DEBUG {
            self.debug_log(&format!(
                "check_mount_crossing: from='{}' to='{}'",
                from_path, to_path
            ));
        }

        // Check if we're crossing into a mount point
        for (idx, mount) in self.mounts.iter().enumerate() {
            // Check if from_path is not under mount, but to_path is
            let from_under = from_path.starts_with(&mount.path);
            let to_under = to_path.starts_with(&mount.path);

            if !from_under && to_under {
                // Crossing into mount point
                let remaining = if to_path.len() == mount.path.len() {
                    "/".to_string()
                } else {
                    to_path[mount.path.len()..].to_string()
                };
                if MOUNT_DEBUG {
                    self.debug_log(&format!(
                        "check_mount_crossing: CROSSING into mount '{}' (idx={}), remaining='{}'",
                        mount.path, idx, remaining
                    ));
                }
                return Some((idx, remaining));
            }
        }

        if MOUNT_DEBUG {
            self.debug_log("check_mount_crossing: no mount crossing detected");
        }
        None
    }
}

impl P9Backend for MountBackend {
    fn send_tversion(
        &mut self,
        msg: &TversionMessage,
    ) -> Result<P9Response<RversionMessage>, TversionError> {
        // Version negotiation uses root backend
        self.root.send_tversion(msg)
    }

    fn send_tattach(
        &mut self,
        msg: &TattachMessage,
    ) -> Result<P9Response<RattachMessage>, TattachError> {
        self.debug_log(&format!("send_tattach: fid={}", msg.fid));

        // Attach always uses root backend and starts at "/"
        match self.root.send_tattach(msg) {
            Ok(P9Response::Success(resp)) => {
                self.debug_log(&format!("send_tattach: attached, qid={:?}", resp.qid));
                // Track the FID as being in root backend at "/"
                self.fid_map.insert(
                    msg.fid,
                    FidInfo {
                        backend_index: None,
                        path: "/".to_string(),
                    },
                );
                self.debug_log(&format!(
                    "send_tattach: FID {} tracked at root '/'",
                    msg.fid
                ));
                Ok(P9Response::Success(resp))
            }
            other => {
                self.debug_log(&format!("send_tattach: failed: {:?}", other));
                other
            }
        }
    }

    fn send_twalk(&mut self, msg: &TwalkMessage) -> Result<P9Response<RwalkMessage>, TwalkError> {
        self.debug_log(&format!(
            "send_twalk: fid={} newfid={} wnames={:?}",
            msg.fid, msg.newfid, msg.wnames
        ));

        // Get the from_fid's backend and path
        let from_fid_info = self.fid_map.get(&msg.fid).ok_or_else(|| {
            self.debug_log(&format!("send_twalk: ERROR - FID {} not found", msg.fid));
            TwalkError::InternalError
        })?; // FID not found

        let from_path = from_fid_info.path.clone();
        let from_backend_idx = from_fid_info.backend_index;

        self.debug_log(&format!(
            "send_twalk: from_fid={} path='{}' backend_idx={:?}",
            msg.fid, from_path, from_backend_idx
        ));

        // Build the target path
        let to_path = Self::build_path(&from_path, &msg.wnames);
        self.debug_log(&format!("send_twalk: target path='{}'", to_path));

        // Check if we're crossing a mount point
        if let Some((mount_idx, remaining_path)) = self.check_mount_crossing(&from_path, &to_path) {
            self.debug_log(&format!(
                "send_twalk: MOUNT CROSSING detected! mount_idx={} remaining='{}'",
                mount_idx, remaining_path
            ));

            // We're crossing into a mount point
            // Strategy:
            // 1. If we're not already at the mount point, walk to it in root backend
            // 2. Attach to the mounted backend (using target FID)
            // 3. Walk remaining path in mounted backend

            let mount_path = &self.mounts[mount_idx].path;
            self.debug_log(&format!("send_twalk: mount_path='{}'", mount_path));
            let mount_components: Vec<String> = mount_path
                .trim_start_matches('/')
                .split('/')
                .filter(|s| !s.is_empty())
                .map(|s| s.to_string())
                .collect();

            // Step 1: Walk to mount point if not already there
            // Collect QIDs from walking to the mount point
            let mut mount_qids = Vec::new();
            if from_path != mount_path.as_str() {
                self.debug_log(&format!(
                    "send_twalk: walking to mount point (from='{}' mount='{}')",
                    from_path, mount_path
                ));

                // Use a temporary FID to walk to mount point
                const TEMP_MOUNT_FID: u32 = 0xFFFF_FFF0; // Use a temp FID
                let walk_to_mount = TwalkMessage {
                    tag: msg.tag,
                    fid: msg.fid,
                    newfid: TEMP_MOUNT_FID,
                    nwname: mount_components.len() as u16,
                    wnames: mount_components.clone(),
                };

                self.debug_log(&format!(
                    "send_twalk: walking to mount with components={:?}",
                    mount_components
                ));

                let root_backend = self.root.as_mut();
                match root_backend.send_twalk(&walk_to_mount) {
                    Ok(P9Response::Success(walk_resp)) => {
                        if MOUNT_DEBUG {
                            crate::kernel::print(&format!(
                                "[MountBackend] send_twalk: successfully walked to mount point, got {} QIDs",
                                walk_resp.nwqid
                            ));
                        }
                        // Collect QIDs from walking to mount point
                        mount_qids.extend_from_slice(&walk_resp.wqids);
                        // Clean up temp FID
                        let _ = root_backend.send_tclunk(&TclunkMessage {
                            tag: msg.tag,
                            fid: TEMP_MOUNT_FID,
                        });
                    }
                    Ok(P9Response::Error(err)) => {
                        if MOUNT_DEBUG {
                            crate::kernel::print(&format!(
                                "[MountBackend] send_twalk: error walking to mount: errno={}",
                                err.ecode
                            ));
                        }
                        return Ok(P9Response::Error(err));
                    }
                    Err(e) => {
                        if MOUNT_DEBUG {
                            crate::kernel::print(&format!(
                                "[MountBackend] send_twalk: error walking to mount: {:?}",
                                e
                            ));
                        }
                        return Err(e);
                    }
                }
            } else {
                self.debug_log("send_twalk: already at mount point, skipping walk");
            }

            // Step 2: Attach to the mounted backend
            // First, ensure the FID is not already in use
            if MOUNT_DEBUG {
                crate::kernel::print(&format!(
                    "[MountBackend] send_twalk: attaching to mounted backend (fid={})",
                    msg.newfid
                ));
            }

            // Remove FID from our tracking if it exists (might be from a previous operation)
            self.fid_map.remove(&msg.newfid);

            let mounted_backend = self.mounts[mount_idx].backend.as_mut();

            // Try to clunk the FID in the mounted backend if it exists
            // This handles the case where the FID was previously used in the RamFilesystem
            let _ = mounted_backend.send_tclunk(&TclunkMessage {
                tag: msg.tag,
                fid: msg.newfid,
            });

            let attach_msg = TattachMessage {
                tag: msg.tag,
                fid: msg.newfid,  // Use target FID for attach
                afid: 0xFFFFFFFF, // No authentication
                uname: "".to_string(),
                aname: "".to_string(),
                n_uname: 0,
            };

            // Attach to mounted backend (needed to establish FID, even if we don't use the QID)
            match mounted_backend.send_tattach(&attach_msg) {
                Ok(P9Response::Success(_resp)) => {
                    if MOUNT_DEBUG {
                        crate::kernel::print(&format!(
                            "[MountBackend] send_twalk: attached to mounted backend, qid={:?}",
                            _resp.qid
                        ));
                    }
                }
                Ok(P9Response::Error(err)) => {
                    if MOUNT_DEBUG {
                        crate::kernel::print(&format!(
                            "[MountBackend] send_twalk: attach error: errno={}",
                            err.ecode
                        ));
                    }
                    return Ok(P9Response::Error(err));
                }
                Err(_) => {
                    if MOUNT_DEBUG {
                        crate::kernel::print(
                            "[MountBackend] send_twalk: attach failed with internal error",
                        );
                    }
                    return Err(TwalkError::InternalError);
                }
            }

            // Step 3: Walk remaining path in mounted backend
            let remaining_components: Vec<String> = remaining_path
                .trim_start_matches('/')
                .split('/')
                .filter(|s| !s.is_empty())
                .map(|s| s.to_string())
                .collect();

            if remaining_components.is_empty() {
                if MOUNT_DEBUG {
                    crate::kernel::print(
                        "[MountBackend] send_twalk: at mount root, returning only mount QIDs (attach QID is internal)",
                    );
                }
                // Already at mount point root, return only the QIDs from walking to the mount point
                // The attach QID is internal and shouldn't be included in the walk response
                if MOUNT_DEBUG {
                    crate::kernel::print(&format!(
                        "[MountBackend] send_twalk: returning {} mount QIDs",
                        mount_qids.len()
                    ));
                }
                self.fid_map.insert(
                    msg.newfid,
                    FidInfo {
                        backend_index: Some(mount_idx),
                        path: "/".to_string(),
                    },
                );
                if MOUNT_DEBUG {
                    crate::kernel::print(&format!(
                        "[MountBackend] send_twalk: FID {} now in mounted backend at '/'",
                        msg.newfid
                    ));
                }
                return Ok(P9Response::Success(RwalkMessage {
                    tag: msg.tag,
                    nwqid: mount_qids.len() as u16,
                    wqids: mount_qids,
                }));
            }

            // Walk remaining path
            if MOUNT_DEBUG {
                crate::kernel::print(&format!(
                    "[MountBackend] send_twalk: walking remaining path in mount: components={:?}",
                    remaining_components
                ));
            }

            let walk_in_mount = TwalkMessage {
                tag: msg.tag,
                fid: msg.newfid,
                newfid: msg.newfid, // Walk in place
                nwname: remaining_components.len() as u16,
                wnames: remaining_components,
            };

            match mounted_backend.send_twalk(&walk_in_mount) {
                Ok(P9Response::Success(resp)) => {
                    if MOUNT_DEBUG {
                        crate::kernel::print(&format!(
                            "[MountBackend] send_twalk: walk in mount succeeded, nwqid={}",
                            resp.nwqid
                        ));
                    }
                    // Combine QIDs: mount point QIDs + mounted backend QIDs
                    let mount_qids_len = mount_qids.len();
                    let mut all_qids = mount_qids;
                    all_qids.extend_from_slice(&resp.wqids);
                    if MOUNT_DEBUG {
                        crate::kernel::print(&format!(
                            "[MountBackend] send_twalk: combined {} mount QIDs + {} mount-backend QIDs = {} total",
                            mount_qids_len,
                            resp.wqids.len(),
                            all_qids.len()
                        ));
                    }
                    // Update FID tracking
                    let remaining_path_clone = remaining_path.clone();
                    self.fid_map.insert(
                        msg.newfid,
                        FidInfo {
                            backend_index: Some(mount_idx),
                            path: remaining_path,
                        },
                    );
                    if MOUNT_DEBUG {
                        crate::kernel::print(&format!(
                            "[MountBackend] send_twalk: FID {} now in mounted backend at '{}'",
                            msg.newfid, remaining_path_clone
                        ));
                    }
                    Ok(P9Response::Success(RwalkMessage {
                        tag: msg.tag,
                        nwqid: all_qids.len() as u16,
                        wqids: all_qids,
                    }))
                }
                other => {
                    if MOUNT_DEBUG {
                        crate::kernel::print(&format!(
                            "[MountBackend] send_twalk: walk in mount failed: {:?}",
                            other
                        ));
                    }
                    other
                }
            }
        } else {
            // No mount crossing - walk in the current backend
            self.debug_log("send_twalk: no mount crossing, walking in current backend");

            let fid = msg.fid;
            let backend = self.get_backend_for_fid(fid).map_err(|_| {
                if MOUNT_DEBUG {
                    crate::kernel::print(&format!(
                        "[MountBackend] send_twalk: ERROR - cannot get backend for FID {}",
                        fid
                    ));
                }
                TwalkError::InternalError
            })?;

            match backend.send_twalk(msg) {
                Ok(P9Response::Success(resp)) => {
                    self.debug_log(&format!("send_twalk: walk succeeded, nwqid={}", resp.nwqid));
                    // Update FID tracking
                    self.fid_map.insert(
                        msg.newfid,
                        FidInfo {
                            backend_index: from_backend_idx,
                            path: to_path.clone(),
                        },
                    );
                    self.debug_log(&format!(
                        "send_twalk: FID {} now at path '{}'",
                        msg.newfid, to_path
                    ));
                    Ok(P9Response::Success(resp))
                }
                other => {
                    self.debug_log(&format!("send_twalk: walk failed: {:?}", other));
                    other
                }
            }
        }
    }

    fn send_tread(&mut self, msg: &TreadMessage) -> Result<P9Response<RreadMessage>, TreadError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TreadError::InternalError)?;
        backend.send_tread(msg)
    }

    fn send_twrite(
        &mut self,
        msg: &TwriteMessage,
    ) -> Result<P9Response<RwriteMessage>, TwriteError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TwriteError::InternalError)?;
        backend.send_twrite(msg)
    }

    fn send_tlopen(
        &mut self,
        msg: &TlopenMessage,
    ) -> Result<P9Response<RlopenMessage>, TlopenError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TlopenError::InternalError)?;
        backend.send_tlopen(msg)
    }

    fn send_tlcreate(
        &mut self,
        msg: &TlcreateMessage,
    ) -> Result<P9Response<RlcreateMessage>, TlcreateError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TlcreateError::InternalError)?;
        backend.send_tlcreate(msg)
    }

    fn send_tgetattr(
        &mut self,
        msg: &TgetattrMessage,
    ) -> Result<P9Response<RgetattrMessage>, TgetattrError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TgetattrError::InternalError)?;
        backend.send_tgetattr(msg)
    }

    fn send_tsetattr(
        &mut self,
        msg: &TsetattrMessage,
    ) -> Result<P9Response<RsetattrMessage>, TsetattrError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TsetattrError::InternalError)?;
        backend.send_tsetattr(msg)
    }

    fn send_treaddir(
        &mut self,
        msg: &TreaddirMessage,
    ) -> Result<P9Response<RreaddirMessage>, TreaddirError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TreaddirError::InternalError)?;
        backend.send_treaddir(msg)
    }

    fn send_treadlink(
        &mut self,
        msg: &TreadlinkMessage,
    ) -> Result<P9Response<RreadlinkMessage>, TreadlinkError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TreadlinkError::InvalidUtf8)?;
        backend.send_treadlink(msg)
    }

    fn send_tsymlink(
        &mut self,
        msg: &TsymlinkMessage,
    ) -> Result<P9Response<RsymlinkMessage>, TsymlinkError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TsymlinkError::InternalError)?;
        backend.send_tsymlink(msg)
    }

    fn send_tmknod(
        &mut self,
        msg: &TmknodMessage,
    ) -> Result<P9Response<RmknodMessage>, TmknodError> {
        let backend = self
            .get_backend_for_fid(msg.dfid)
            .map_err(|_| TmknodError::InternalError)?;
        backend.send_tmknod(msg)
    }

    fn send_tmkdir(
        &mut self,
        msg: &TmkdirMessage,
    ) -> Result<P9Response<RmkdirMessage>, TmkdirError> {
        let backend = self
            .get_backend_for_fid(msg.dfid)
            .map_err(|_| TmkdirError::InternalError)?;
        backend.send_tmkdir(msg)
    }

    fn send_tunlinkat(
        &mut self,
        msg: &TunlinkatMessage,
    ) -> Result<P9Response<RunlinkatMessage>, TunlinkatError> {
        let backend = self
            .get_backend_for_fid(msg.dirfd)
            .map_err(|_| TunlinkatError::InternalError)?;
        backend.send_tunlinkat(msg)
    }

    fn send_trenameat(
        &mut self,
        msg: &TrenameatMessage,
    ) -> Result<P9Response<RrenameatMessage>, TrenameatError> {
        // Use olddirfid for routing (both should be in same backend)
        let backend = self
            .get_backend_for_fid(msg.olddirfid)
            .map_err(|_| TrenameatError::InternalError)?;
        backend.send_trenameat(msg)
    }

    fn send_tclunk(
        &mut self,
        msg: &TclunkMessage,
    ) -> Result<P9Response<RclunkMessage>, TclunkError> {
        self.debug_log(&format!("send_tclunk: fid={}", msg.fid));

        let fid = msg.fid;
        let backend = self.get_backend_for_fid(fid).map_err(|_| {
            if MOUNT_DEBUG {
                crate::kernel::print(&format!(
                    "[MountBackend] send_tclunk: ERROR - cannot get backend for FID {}",
                    fid
                ));
            }
            TclunkError::InternalError
        })?;

        let result = backend.send_tclunk(msg);
        // Remove FID tracking on successful clunk
        if matches!(result, Ok(P9Response::Success(_))) {
            self.fid_map.remove(&msg.fid);
            self.debug_log(&format!(
                "send_tclunk: FID {} removed from tracking",
                msg.fid
            ));
        } else {
            self.debug_log(&format!("send_tclunk: clunk failed: {:?}", result));
        }
        result
    }

    fn send_tremove(
        &mut self,
        msg: &TremoveMessage,
    ) -> Result<P9Response<RremoveMessage>, TremoveError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TremoveError::InternalError)?;
        backend.send_tremove(msg)
    }

    fn send_tfsync(
        &mut self,
        msg: &TfsyncMessage,
    ) -> Result<P9Response<RfsyncMessage>, TfsyncError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TfsyncError::InternalError)?;
        backend.send_tfsync(msg)
    }

    fn send_tlink(&mut self, msg: &TlinkMessage) -> Result<P9Response<RlinkMessage>, TlinkError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TlinkError::InternalError)?;
        backend.send_tlink(msg)
    }

    fn send_trename(
        &mut self,
        msg: &TrenameMessage,
    ) -> Result<P9Response<RrenameMessage>, TrenameError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TrenameError::InternalError)?;
        backend.send_trename(msg)
    }

    fn send_txattrwalk(
        &mut self,
        msg: &TxattrwalkMessage,
    ) -> Result<P9Response<RxattrwalkMessage>, TxattrwalkError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TxattrwalkError::InternalError)?;
        backend.send_txattrwalk(msg)
    }

    fn send_txattrcreate(
        &mut self,
        msg: &TxattrcreateMessage,
    ) -> Result<P9Response<RxattrcreateMessage>, TxattrcreateError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TxattrcreateError::InternalError)?;
        backend.send_txattrcreate(msg)
    }

    fn send_tflush(
        &mut self,
        msg: &TflushMessage,
    ) -> Result<P9Response<RflushMessage>, TflushError> {
        // Flush doesn't have a FID - it flushes by tag, so route to root
        // TODO: Track which backend a tag belongs to
        self.root.send_tflush(msg)
    }

    fn send_tauth(&mut self, msg: &TauthMessage) -> Result<P9Response<RauthMessage>, TauthError> {
        self.root.send_tauth(msg)
    }

    fn send_tstatfs(
        &mut self,
        msg: &TstatfsMessage,
    ) -> Result<P9Response<RstatfsMessage>, TstatfsError> {
        // Tstatfs uses fid field
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TstatfsError::InternalError)?;
        backend.send_tstatfs(msg)
    }

    fn send_tlock(&mut self, msg: &TlockMessage) -> Result<P9Response<RlockMessage>, TlockError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TlockError::InternalError)?;
        backend.send_tlock(msg)
    }

    fn send_tgetlock(
        &mut self,
        msg: &TgetlockMessage,
    ) -> Result<P9Response<RgetlockMessage>, TgetlockError> {
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TgetlockError::InternalError)?;
        backend.send_tgetlock(msg)
    }
}
