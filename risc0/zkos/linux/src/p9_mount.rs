//! Mount Point Router and RAM Filesystem
//!
//! This module provides:
//! - MountBackend: Routes P9 requests to different backends based on mount points
//! - RamFilesystem: A simple in-memory writable filesystem for /tmp and similar use cases

#![allow(dead_code)]

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
                mode: 0o755,
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
        let (from_inode, from_path) = self.get_fid(from_fid).map_err(|e| e)?;
        let mut current_inode = from_inode;
        let mut current_path = from_path.clone();
        let mut qids = Vec::new();

        if wnames.is_empty() {
            // Clone FID
            qids.push(self.get_qid(current_inode));
            self.allocate_fid(to_fid, current_inode, current_path)?;
            return Ok(qids);
        }

        for wname in wnames {
            if !self.is_dir(current_inode) {
                return Err(P9Error::Enotdir as u32);
            }

            let dir = match self.nodes.get(&current_inode) {
                Some(RamNode::Directory { entries, .. }) => entries,
                _ => return Err(P9Error::Enotdir as u32),
            };

            let next_inode = dir.get(wname).copied().ok_or(P9Error::Enoent as u32)?;
            current_inode = next_inode;
            current_path = if current_path == "/" {
                format!("/{}", wname)
            } else {
                format!("{}/{}", current_path, wname)
            };
            qids.push(self.get_qid(current_inode));
        }

        self.allocate_fid(to_fid, current_inode, current_path)?;
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
                mode,
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
                        4 // DT_DIR
                    } else if self.is_symlink(entry_inode) {
                        10 // DT_LNK
                    } else {
                        8 // DT_REG
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
        match self.walk(msg.fid, msg.newfid, &msg.wnames) {
            Ok(qids) => Ok(P9Response::Success(RwalkMessage {
                tag: msg.tag,
                nwqid: qids.len() as u16,
                wqids: qids,
            })),
            Err(errno) => Ok(P9Response::Error(RlerrorMessage::new(msg.tag, errno))),
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
            blocks: (size + 4095) / 4096,
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
        _msg: &TsetattrMessage,
    ) -> Result<P9Response<RsetattrMessage>, TsetattrError> {
        // TODO: Implement attribute setting
        Ok(P9Response::Success(RsetattrMessage { tag: _msg.tag }))
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
        _msg: &TsymlinkMessage,
    ) -> Result<P9Response<RsymlinkMessage>, TsymlinkError> {
        // TODO: Implement symlink creation
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Enosys as u32,
        )))
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
        _msg: &TmkdirMessage,
    ) -> Result<P9Response<RmkdirMessage>, TmkdirError> {
        // TODO: Implement directory creation
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Enosys as u32,
        )))
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
        _msg: &TremoveMessage,
    ) -> Result<P9Response<RremoveMessage>, TremoveError> {
        Ok(P9Response::Error(RlerrorMessage::new(
            _msg.tag,
            P9Error::Enosys as u32,
        )))
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
    /// Create a new mount backend with a root backend
    pub fn new(root: Box<dyn P9Backend>) -> Self {
        Self {
            root,
            mounts: Vec::new(),
            fid_map: BTreeMap::new(),
        }
    }

    /// Mount a backend at a given path
    pub fn mount(&mut self, path: String, backend: Box<dyn P9Backend>) -> Result<(), u32> {
        // Normalize path: ensure it starts with / and ends with / (except root)
        let normalized = if path == "/" {
            return Err(P9Error::Einval as u32); // Can't mount over root
        } else if !path.starts_with('/') {
            format!("/{}", path)
        } else {
            path.clone()
        };

        // Check for conflicts
        for mount in &self.mounts {
            if mount.path == normalized || normalized.starts_with(&mount.path) {
                return Err(P9Error::Ebusy as u32); // Mount point conflict
            }
        }

        self.mounts.push(MountPoint {
            path: normalized,
            backend,
        });

        // Sort by path length (longest first) for proper prefix matching
        self.mounts.sort_by(|a, b| b.path.len().cmp(&a.path.len()));

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
                return Some((idx, remaining));
            }
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
        // Attach always uses root backend and starts at "/"
        match self.root.send_tattach(msg) {
            Ok(P9Response::Success(resp)) => {
                // Track the FID as being in root backend at "/"
                self.fid_map.insert(
                    msg.fid,
                    FidInfo {
                        backend_index: None,
                        path: "/".to_string(),
                    },
                );
                Ok(P9Response::Success(resp))
            }
            other => other,
        }
    }

    fn send_twalk(&mut self, msg: &TwalkMessage) -> Result<P9Response<RwalkMessage>, TwalkError> {
        // Get the from_fid's backend and path
        let from_fid_info = self.fid_map.get(&msg.fid).ok_or_else(|| {
            TwalkError::InternalError // FID not found
        })?;

        let from_path = from_fid_info.path.clone();
        let from_backend_idx = from_fid_info.backend_index;

        // Build the target path
        let to_path = Self::build_path(&from_path, &msg.wnames);

        // Check if we're crossing a mount point
        if let Some((_mount_idx, _remaining_path)) = self.check_mount_crossing(&from_path, &to_path)
        {
            // We're crossing into a mount point
            // This requires special handling:
            // 1. Walk to mount point in root backend (if not already there)
            // 2. Attach to mounted backend
            // 3. Walk remaining path in mounted backend

            // For now, return an error - mount crossing needs more complex logic
            // TODO: Implement proper mount crossing
            return Ok(P9Response::Error(RlerrorMessage::new(
                msg.tag,
                P9Error::Eopnotsupp as u32, // Operation not supported for mount crossing
            )));
        }

        // No mount crossing - walk in the current backend
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TwalkError::InternalError)?;
        match backend.send_twalk(msg) {
            Ok(P9Response::Success(resp)) => {
                // Update FID tracking
                self.fid_map.insert(
                    msg.newfid,
                    FidInfo {
                        backend_index: from_backend_idx,
                        path: to_path,
                    },
                );
                Ok(P9Response::Success(resp))
            }
            other => other,
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
        let backend = self
            .get_backend_for_fid(msg.fid)
            .map_err(|_| TclunkError::InternalError)?;
        let result = backend.send_tclunk(msg);
        // Remove FID tracking on successful clunk
        if matches!(result, Ok(P9Response::Success(_))) {
            self.fid_map.remove(&msg.fid);
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
