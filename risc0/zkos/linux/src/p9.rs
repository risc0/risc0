//! 9P2000.L Protocol Implementation
//!
//! This module implements the 9P2000.L protocol, a variant of 9P from the Plan 9 Operating System.
//! 9P2000.L consists of a subset of the canonical 9P2000 operations, the 9P2000.u `attach` and `auth`
//! messages, plus new operations designed to map to the Linux VFS in a straightforward way.
//!
//! For a general introduction to 9P see the Plan 9 intro(5) manual page.

#![allow(dead_code)]
use crate::kernel::print;
use core::fmt;
use no_std_strings::{str_format, str256};

#[cfg(target_arch = "riscv32")]
use alloc::string::String;

#[cfg(target_arch = "riscv32")]
use alloc::string::ToString;

#[cfg(target_arch = "riscv32")]
use alloc::vec::Vec;

#[cfg(target_arch = "riscv32")]
use alloc::vec;

// Re-export zkVM-specific transport layer functions for external use
pub use crate::p9_zkvm::{get_p9_traffic_hash, p9_read_message};

// Re-export error types for external use (marked as potentially unused in this module)
#[allow(unused_imports)]
pub use crate::p9_zkvm::{HostReadError, HostWriteError};

// Import backend system for message sending
use crate::p9_backend::get_backend;

// Import for tests
#[cfg(test)]
use crate::p9_zkvm::{p9_send_message, p9_update_traffic_hash, p9_write};

/// 9P message types
///
/// There are 14 basic operations in 9P2000, paired as requests and responses.
/// The one special case is ERROR as there is no P9_TERROR request for clients
/// to transmit to the server, but the server may respond to any other request
/// with an P9_RERROR.
#[repr(u8)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9MsgType {
    // 9P2000.L specific messages
    TLerror = 6,
    RLerror = 7,
    Tstatfs = 8,
    Rstatfs = 9,
    Tlopen = 12,
    Rlopen = 13,
    Tlcreate = 14,
    Rlcreate = 15,
    Tsymlink = 16,
    Rsymlink = 17,
    Tmknod = 18,
    Rmknod = 19,
    Trename = 20,
    Rrename = 21,
    Treadlink = 22,
    Rreadlink = 23,
    Tgetattr = 24,
    Rgetattr = 25,
    Tsetattr = 26,
    Rsetattr = 27,
    Txattrwalk = 30,
    Rxattrwalk = 31,
    Txattrcreate = 32,
    Rxattrcreate = 33,
    Treaddir = 40,
    Rreaddir = 41,
    Tfsync = 50,
    Rfsync = 51,
    Tlock = 52,
    Rlock = 53,
    Tgetlock = 54,
    Rgetlock = 55,
    Tlink = 70,
    Rlink = 71,
    Tmkdir = 72,
    Rmkdir = 73,
    Trenameat = 74,
    Rrenameat = 75,
    Tunlinkat = 76,
    Runlinkat = 77,

    // 9P2000 core messages
    Tversion = 100,
    Rversion = 101,
    Tauth = 102,
    Rauth = 103,
    Tattach = 104,
    Rattach = 105,
    Terror = 106,
    Rerror = 107,
    Tflush = 108,
    Rflush = 109,
    Twalk = 110,
    Rwalk = 111,
    Topen = 112,
    Ropen = 113,
    Tcreate = 114,
    Rcreate = 115,
    Tread = 116,
    Rread = 117,
    Twrite = 118,
    Rwrite = 119,
    Tclunk = 120,
    Rclunk = 121,
    Tremove = 122,
    Rremove = 123,
    Tstat = 124,
    Rstat = 125,
    Twstat = 126,
    Rwstat = 127,
}

impl P9MsgType {
    /// Check if this is a request message (starts with T)
    pub fn is_request(&self) -> bool {
        matches!(
            self,
            P9MsgType::Tlopen
                | P9MsgType::Tlcreate
                | P9MsgType::Tsymlink
                | P9MsgType::Tmknod
                | P9MsgType::Trename
                | P9MsgType::Treadlink
                | P9MsgType::Tgetattr
                | P9MsgType::Tsetattr
                | P9MsgType::Txattrwalk
                | P9MsgType::Txattrcreate
                | P9MsgType::Treaddir
                | P9MsgType::Tfsync
                | P9MsgType::Tlock
                | P9MsgType::Tgetlock
                | P9MsgType::Tlink
                | P9MsgType::Tmkdir
                | P9MsgType::Trenameat
                | P9MsgType::Tunlinkat
                | P9MsgType::Tversion
                | P9MsgType::Tauth
                | P9MsgType::Tattach
                | P9MsgType::Tflush
                | P9MsgType::Twalk
                | P9MsgType::Topen
                | P9MsgType::Tcreate
                | P9MsgType::Tread
                | P9MsgType::Twrite
                | P9MsgType::Tclunk
                | P9MsgType::Tremove
                | P9MsgType::Tstat
                | P9MsgType::Twstat
                | P9MsgType::Tstatfs
        )
    }

    /// Check if this is a response message (starts with R)
    pub fn is_response(&self) -> bool {
        !self.is_request()
    }
}

/// QID (13-byte unique file system object identifier)
///
/// A QID is represented on the wire as:
/// type[1] version[4] path[8]
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub struct Qid {
    /// QID type (see P9QidType)
    pub qtype: u8,
    /// Version number
    pub version: u32,
    /// Path identifier
    pub path: u64,
}

impl Qid {
    /// Create a new QID
    pub fn new(qtype: u8, version: u32, path: u64) -> Self {
        Self {
            qtype,
            version,
            path,
        }
    }

    /// Check if this QID represents a directory
    pub fn is_dir(&self) -> bool {
        self.qtype & P9QidType::Qtdir as u8 != 0
    }

    /// Check if this QID represents a file
    pub fn is_file(&self) -> bool {
        self.qtype == P9QidType::Qtfile as u8
    }

    /// Check if this QID represents a symlink
    pub fn is_symlink(&self) -> bool {
        self.qtype & P9QidType::Qtsymlink as u8 != 0
    }
}

/// QID type flags
#[repr(u8)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9QidType {
    Qtdir = 0x80,
    Qtappend = 0x40,
    Qtexcl = 0x20,
    Qtmount = 0x10,
    Qtauth = 0x08,
    Qttmp = 0x04,
    Qtsymlink = 0x02,
    Qtlink = 0x01,
    Qtfile = 0x00,
}

/// 9P2000.L open mode flags
#[repr(u32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9OpenMode {
    /// Read only
    Rdonly = 0o00000000,
    /// Write only
    Wronly = 0o00000001,
    /// Read and write
    Rdwr = 0o00000002,
    /// No access
    Noaccess = 0o00000003,
    /// Create file
    Create = 0o00000100,
    /// Exclusive create
    Excl = 0o00000200,
    /// No controlling terminal
    Noctty = 0o00000400,
    /// Truncate file
    Trunc = 0o00001000,
    /// Append mode
    Append = 0o00002000,
    /// Non-blocking I/O
    Nonblock = 0o00004000,
    /// Synchronized I/O data integrity
    Dsync = 0o00010000,
    /// Synchronized I/O file integrity
    Fasync = 0o00020000,
    /// Direct I/O
    Direct = 0o00040000,
    /// Large file support
    Largefile = 0o00100000,
    /// Directory
    Directory = 0o00200000,
    /// Don't follow symlinks
    Nofollow = 0o00400000,
    /// Don't update access time
    Noatime = 0o01000000,
    /// Close on exec
    Cloexec = 0o02000000,
    /// Synchronized I/O
    Sync = 0o04000000,
}

/// 9P2000.L at flags
#[repr(u32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9AtFlags {
    /// Remove directory
    Removedir = 0x200,
}

/// 9P2000.L lock types
#[repr(u8)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9LockType {
    /// Read lock
    Rdlck = 0,
    /// Write lock
    Wrlck = 1,
    /// Unlock
    Unlck = 2,
}

/// 9P2000.L lock flags
#[repr(u32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9LockFlags {
    /// Blocking request
    Block = 1,
    /// Reserved for future use
    Reclaim = 2,
}

/// 9P2000.L lock status
#[repr(u8)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9LockStatus {
    /// Lock acquired successfully
    Success = 0,
    /// Lock blocked by another process
    Blocked = 1,
    /// Lock error
    Error = 2,
    /// Lock in grace period
    Grace = 3,
}

/// 9P2000.L getattr mask flags
#[repr(u64)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9GetattrMask {
    Mode = 0x00000001,
    Nlink = 0x00000002,
    Uid = 0x00000004,
    Gid = 0x00000008,
    Rdev = 0x00000010,
    Atime = 0x00000020,
    Mtime = 0x00000040,
    Ctime = 0x00000080,
    Ino = 0x00000100,
    Size = 0x00000200,
    Blocks = 0x00000400,
    Btime = 0x00000800,
    Gen = 0x00001000,
    DataVersion = 0x00002000,
}

impl P9GetattrMask {
    /// Mask for basic fields (up to BLOCKS)
    pub const BASIC: u64 = 0x000007ff;

    /// Mask for all fields
    pub const ALL: u64 = 0x00003fff;
}

/// 9P2000.L setattr mask flags
#[repr(u32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9SetattrMask {
    Mode = 0x00000001,
    Uid = 0x00000002,
    Gid = 0x00000004,
    Size = 0x00000008,
    Atime = 0x00000010,
    Mtime = 0x00000020,
    Ctime = 0x00000040,
    AtimeSet = 0x00000080,
    MtimeSet = 0x00000100,
}

/// 9P2000.L permissions
#[repr(u32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9Perm {
    /// Directory
    Dmdir = 0x80000000,
    /// Append only
    Dmappend = 0x40000000,
    /// Exclusive use
    Dmexcl = 0x20000000,
    /// Mount point
    Dmmount = 0x10000000,
    /// Authentication file
    Dmauth = 0x08000000,
    /// Temporary file
    Dmtmp = 0x04000000,
    /// Symbolic link (9P2000.u extension)
    Dmsymlink = 0x02000000,
    /// Hard link (9P2000.u extension)
    Dmlink = 0x01000000,
    /// Device file (9P2000.u extension)
    Dmdevice = 0x00800000,
    /// Named pipe (9P2000.u extension)
    Dmnamedpipe = 0x00200000,
    /// Socket (9P2000.u extension)
    Dmsocket = 0x00100000,
    /// Set UID (9P2000.u extension)
    Dmsetuid = 0x00080000,
    /// Set GID (9P2000.u extension)
    Dmsetgid = 0x00040000,
    /// Set sticky bit (9P2000.u extension)
    Dmsetvtx = 0x00010000,
}

/// 9P2000.L open mode (legacy 9P)
#[repr(u32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9OpenModeLegacy {
    /// Read only
    Oread = 0x00,
    /// Write only
    Owrite = 0x01,
    /// Read and write
    Ordwr = 0x02,
    /// Execute
    Oexec = 0x03,
    /// Truncate
    Otrunc = 0x10,
    /// Remove on close
    Orclose = 0x40,
    /// Append
    Oappend = 0x80,
    /// Exclusive
    Oexcl = 0x1000,
}

/// 9P2000.L mode mask for legacy open
pub const P9L_MODE_MASK: u32 = 0x1FFF;

/// 9P2000.L flags for legacy open
#[repr(u32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9LFlags {
    /// Cache disabled
    Direct = 0x2000,
    /// No write caching
    Nowritecache = 0x4000,
    /// Loose cache
    Loose = 0x8000,
}

/// Special 9P values
pub mod constants {
    /// 9P2000.L getattr request bitmasks
    pub const P9_GETATTR_MODE: u64 = 0x0000_0001;
    pub const P9_GETATTR_NLINK: u64 = 0x0000_0002;
    pub const P9_GETATTR_UID: u64 = 0x0000_0004;
    pub const P9_GETATTR_GID: u64 = 0x0000_0008;
    pub const P9_GETATTR_RDEV: u64 = 0x0000_0010;
    pub const P9_GETATTR_ATIME: u64 = 0x0000_0020;
    pub const P9_GETATTR_MTIME: u64 = 0x0000_0040;
    pub const P9_GETATTR_CTIME: u64 = 0x0000_0080;
    pub const P9_GETATTR_INO: u64 = 0x0000_0100;
    pub const P9_GETATTR_SIZE: u64 = 0x0000_0200;
    pub const P9_GETATTR_BLOCKS: u64 = 0x0000_0400;

    pub const P9_GETATTR_BTIME: u64 = 0x0000_0800;
    pub const P9_GETATTR_GEN: u64 = 0x0000_1000;
    pub const P9_GETATTR_DATA_VERSION: u64 = 0x0000_2000;

    pub const P9_GETATTR_BASIC: u64 = 0x0000_07ff; // Mask for fields up to BLOCKS
    pub const P9_GETATTR_ALL: u64 = 0x0000_3fff; // Mask for all fields above
    /// No FID (invalid FID)
    pub const P9_NOFID: u32 = 0xffffffff;

    /// No user name (use uname instead)
    pub const P9_NONUNAME: u32 = 0xffffffff;

    /// Maximum message size
    pub const P9_MAX_MSIZE: u32 = 1024 * 1024;

    /// Default message size
    pub const P9_DEFAULT_MSIZE: u32 = 8192;

    /// Protocol version string
    pub const P9_VERSION: &str = "9P2000.L";
}

/// 9P wire format utilities for no_std serialization
pub mod wire {

    /// Write a u8 to buffer in little-endian format
    #[inline]
    pub fn write_u8(buf: &mut [u8], offset: usize, value: u8) -> Result<usize, WireError> {
        if offset >= buf.len() {
            return Err(WireError::BufferTooSmall);
        }
        buf[offset] = value;
        Ok(offset + 1)
    }

    /// Write a u16 to buffer in little-endian format
    #[inline]
    pub fn write_u16(buf: &mut [u8], offset: usize, value: u16) -> Result<usize, WireError> {
        if offset + 1 >= buf.len() {
            return Err(WireError::BufferTooSmall);
        }
        buf[offset] = (value & 0xff) as u8;
        buf[offset + 1] = ((value >> 8) & 0xff) as u8;
        Ok(offset + 2)
    }

    /// Write a u32 to buffer in little-endian format
    #[inline]
    pub fn write_u32(buf: &mut [u8], offset: usize, value: u32) -> Result<usize, WireError> {
        if offset + 3 >= buf.len() {
            return Err(WireError::BufferTooSmall);
        }
        buf[offset] = (value & 0xff) as u8;
        buf[offset + 1] = ((value >> 8) & 0xff) as u8;
        buf[offset + 2] = ((value >> 16) & 0xff) as u8;
        buf[offset + 3] = ((value >> 24) & 0xff) as u8;
        Ok(offset + 4)
    }

    /// Write a u64 to buffer in little-endian format
    #[inline]
    pub fn write_u64(buf: &mut [u8], offset: usize, value: u64) -> Result<usize, WireError> {
        if offset + 7 >= buf.len() {
            return Err(WireError::BufferTooSmall);
        }
        buf[offset] = (value & 0xff) as u8;
        buf[offset + 1] = ((value >> 8) & 0xff) as u8;
        buf[offset + 2] = ((value >> 16) & 0xff) as u8;
        buf[offset + 3] = ((value >> 24) & 0xff) as u8;
        buf[offset + 4] = ((value >> 32) & 0xff) as u8;
        buf[offset + 5] = ((value >> 40) & 0xff) as u8;
        buf[offset + 6] = ((value >> 48) & 0xff) as u8;
        buf[offset + 7] = ((value >> 56) & 0xff) as u8;
        Ok(offset + 8)
    }

    /// Write a string to buffer in 9P format: length[2] string[length]
    #[inline]
    pub fn write_string(buf: &mut [u8], offset: usize, s: &str) -> Result<usize, WireError> {
        let len = s.len();
        if len > u16::MAX as usize {
            return Err(WireError::StringTooLong);
        }

        let pos = write_u16(buf, offset, len as u16)?;

        if pos + len > buf.len() {
            return Err(WireError::BufferTooSmall);
        }

        buf[pos..pos + len].copy_from_slice(s.as_bytes());
        Ok(pos + len)
    }

    /// Read a u8 from buffer in little-endian format
    #[inline]
    pub fn read_u8(buf: &[u8], offset: usize) -> Result<(u8, usize), WireError> {
        if offset >= buf.len() {
            return Err(WireError::BufferTooSmall);
        }
        Ok((buf[offset], offset + 1))
    }

    /// Read a u16 from buffer in little-endian format
    #[inline]
    pub fn read_u16(buf: &[u8], offset: usize) -> Result<(u16, usize), WireError> {
        if offset + 1 >= buf.len() {
            return Err(WireError::BufferTooSmall);
        }
        let value = (buf[offset] as u16) | ((buf[offset + 1] as u16) << 8);
        Ok((value, offset + 2))
    }

    /// Read a u32 from buffer in little-endian format
    #[inline]
    pub fn read_u32(buf: &[u8], offset: usize) -> Result<(u32, usize), WireError> {
        if offset + 3 >= buf.len() {
            return Err(WireError::BufferTooSmall);
        }
        let value = (buf[offset] as u32)
            | ((buf[offset + 1] as u32) << 8)
            | ((buf[offset + 2] as u32) << 16)
            | ((buf[offset + 3] as u32) << 24);
        Ok((value, offset + 4))
    }

    /// Read a u64 from buffer in little-endian format
    #[inline]
    pub fn read_u64(buf: &[u8], offset: usize) -> Result<(u64, usize), WireError> {
        if offset + 7 >= buf.len() {
            return Err(WireError::BufferTooSmall);
        }
        let value = (buf[offset] as u64)
            | ((buf[offset + 1] as u64) << 8)
            | ((buf[offset + 2] as u64) << 16)
            | ((buf[offset + 3] as u64) << 24)
            | ((buf[offset + 4] as u64) << 32)
            | ((buf[offset + 5] as u64) << 40)
            | ((buf[offset + 6] as u64) << 48)
            | ((buf[offset + 7] as u64) << 56);
        Ok((value, offset + 8))
    }

    /// Read a string from buffer in 9P format: length[2] string[length]
    #[inline]
    pub fn read_string(buf: &[u8], offset: usize) -> Result<(&str, usize), WireError> {
        let (len, pos) = read_u16(buf, offset)?;
        let len = len as usize;

        if pos + len > buf.len() {
            return Err(WireError::BufferTooSmall);
        }

        // Convert bytes to string slice
        let string_bytes = &buf[pos..pos + len];
        let s = core::str::from_utf8(string_bytes).map_err(|_| WireError::InvalidUtf8)?;

        Ok((s, pos + len))
    }

    /// Wire format errors
    #[derive(Debug, Clone, Copy, PartialEq, Eq)]
    pub enum WireError {
        BufferTooSmall,
        StringTooLong,
        InvalidUtf8,
    }
}

/// Common error types that all R* message errors should have
pub trait MessageError: core::fmt::Debug + Clone + Copy + PartialEq + Eq {
    /// Create a BufferTooSmall error
    fn buffer_too_small() -> Self;

    /// Create an InvalidMessageType error  
    fn invalid_message_type() -> Self;
}

/// A 9P response that can be either a success message or an error
#[derive(Debug)]
pub enum P9Response<T> {
    Success(T),
    Error(RlerrorMessage),
}

/// Trait for all R* message types that can be read from a file descriptor
pub trait ReadableMessage: Sized {
    /// The error type for this message
    type Error: MessageError;

    /// Deserialize the message from a buffer
    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error>;

    /// Read a 9P response that can be either success or Rlerror
    /// This is the preferred method for reading 9P responses
    fn read_response() -> P9Response<Self> {
        // Read the message data once
        let mut buf = [0u8; 8192];

        // Use p9_read_message to handle the length prefix and reading
        match p9_read_message(3, &mut buf) {
            Ok(data_len) => {
                // Check the message type
                let msg_type = buf[4];

                if msg_type == P9MsgType::RLerror as u8 {
                    // This is an Rlerror message
                    match RlerrorMessage::deserialize(&buf[..data_len as usize]) {
                        Ok((rlerror, _)) => P9Response::Error(rlerror),
                        Err(_) => {
                            kprint!(
                                "ReadableMessage::read_response: error deserializing Rlerror message"
                            );
                            P9Response::Error(RlerrorMessage::new(0, 0)) // Generic error
                        }
                    }
                } else {
                    // This should be the expected response type
                    match Self::deserialize(&buf[..data_len as usize]) {
                        Ok((response, _)) => P9Response::Success(response),
                        Err(err) => {
                            kprint!(
                                "ReadableMessage::read_response: error deserializing message: {:?}",
                                err
                            );
                            P9Response::Error(RlerrorMessage::new(0, 0))
                        }
                    }
                }
            }
            Err(err) => {
                kprint!(
                    "ReadableMessage::read_response: p9_read_message error: {:?}",
                    err
                );
                P9Response::Error(RlerrorMessage::new(0, 0)) // Generic error
            }
        }
    }
}

/// Tversion message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TversionMessage {
    /// Message tag
    pub tag: u16,
    /// Maximum message size
    pub msize: u32,
    /// Protocol version string
    pub version: &'static str,
}

impl TversionMessage {
    /// Create a new Tversion message
    pub fn new(tag: u16, msize: u32, version: &'static str) -> Self {
        Self {
            tag,
            msize,
            version,
        }
    }

    /// Create a default Tversion message for 9P2000.L
    pub fn default_9p2000l(tag: u16) -> Self {
        Self {
            tag,
            msize: constants::P9_DEFAULT_MSIZE,
            version: constants::P9_VERSION,
        }
    }

    /// Serialize the Tversion message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TversionError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        // Calculate total message size first
        let version_len = self.version.len();
        let total_size = 4 + 1 + 2 + 4 + 2 + version_len; // size[4] + type[1] + tag[2] + msize[4] + version_len[2] + version[version_len]

        if total_size > buf.len() {
            return Err(TversionError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TversionError::BufferTooSmall,
            WireError::StringTooLong => TversionError::InternalError,
            WireError::InvalidUtf8 => TversionError::InternalError,
        })?;

        // Write message type[1] - Tversion
        buf[offset] = P9MsgType::Tversion as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TversionError::BufferTooSmall,
            WireError::StringTooLong => TversionError::InternalError,
            WireError::InvalidUtf8 => TversionError::InternalError,
        })?;

        // Write msize[4]
        offset = write_u32(buf, offset, self.msize).map_err(|e| match e {
            WireError::BufferTooSmall => TversionError::BufferTooSmall,
            WireError::StringTooLong => TversionError::InternalError,
            WireError::InvalidUtf8 => TversionError::InternalError,
        })?;

        // Write version[s] (length[2] + string[length])
        offset = write_string(buf, offset, self.version).map_err(|e| match e {
            WireError::BufferTooSmall => TversionError::BufferTooSmall,
            WireError::StringTooLong => TversionError::VersionTooLong,
            WireError::InvalidUtf8 => TversionError::InternalError,
        })?;

        Ok(offset)
    }

    /// Send the Tversion message using the active backend
    /// Returns the response from the backend
    pub fn send_tversion(&self) -> Result<P9Response<RversionMessage>, TversionError> {
        get_backend().send_tversion(self)
    }
}

/// Rversion message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RversionMessage {
    /// Message tag
    pub tag: u16,
    /// Maximum message size
    pub msize: u32,
    /// Protocol version string
    pub version: &'static str,
}

impl RversionMessage {
    /// Create a new Rversion message
    pub fn new(tag: u16, msize: u32, version: &'static str) -> Self {
        Self {
            tag,
            msize,
            version,
        }
    }

    /// Deserialize an Rversion message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RversionError> {
        use wire::{WireError, read_string, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RversionError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RversionError::BufferTooSmall,
            WireError::StringTooLong => RversionError::InternalError,
            WireError::InvalidUtf8 => RversionError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RversionError::BufferTooSmall);
        }

        // Read message type[1] - should be Rversion
        if offset >= buf.len() {
            return Err(RversionError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rversion as u8 {
            return Err(RversionError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RversionError::BufferTooSmall,
            WireError::StringTooLong => RversionError::InternalError,
            WireError::InvalidUtf8 => RversionError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read msize[4]
        let (msize, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RversionError::BufferTooSmall,
            WireError::StringTooLong => RversionError::InternalError,
            WireError::InvalidUtf8 => RversionError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read version[s] (length[2] + string[length])
        let (version, new_offset) = read_string(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RversionError::BufferTooSmall,
            WireError::StringTooLong => RversionError::VersionTooLong,
            WireError::InvalidUtf8 => RversionError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Note: We can't return a &str from a buffer because it would have the wrong lifetime
        // In a real implementation, you'd need to copy the string to a static buffer
        // For now, we'll return an error if the version is not a known static string
        kprint!("Version: {}", version);
        let static_version = match version {
            "9P2000.L" => constants::P9_VERSION,
            _ => return Err(RversionError::UnknownVersion),
        };

        let message = Self {
            tag,
            msize,
            version: static_version,
        };

        Ok((message, offset))
    }
}

impl ReadableMessage for RversionMessage {
    type Error = RversionError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RversionMessage::deserialize(buf)
    }
}

/// Tversion serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TversionError {
    BufferTooSmall,
    VersionTooLong,
    InternalError,
}

/// Rversion deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RversionError {
    BufferTooSmall,
    VersionTooLong,
    InvalidMessageType,
    InvalidUtf8,
    UnknownVersion,
    InternalError,
}

impl MessageError for RversionError {
    fn buffer_too_small() -> Self {
        RversionError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RversionError::InvalidMessageType
    }
}

/// Tflush message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TflushMessage {
    /// Message tag
    pub tag: u16,
    /// Tag of the message to flush
    pub oldtag: u16,
}

impl TflushMessage {
    /// Create a new Tflush message
    pub fn new(tag: u16, oldtag: u16) -> Self {
        Self { tag, oldtag }
    }

    /// Serialize the Tflush message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TflushError> {
        use wire::{WireError, write_u16, write_u32};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 2; // size[4] + type[1] + tag[2] + oldtag[2]

        if total_size > buf.len() {
            return Err(TflushError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TflushError::BufferTooSmall,
            WireError::StringTooLong => TflushError::InternalError,
            WireError::InvalidUtf8 => TflushError::InternalError,
        })?;

        // Write message type[1] - Tflush
        buf[offset] = P9MsgType::Tflush as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TflushError::BufferTooSmall,
            WireError::StringTooLong => TflushError::InternalError,
            WireError::InvalidUtf8 => TflushError::InternalError,
        })?;

        // Write oldtag[2]
        offset = write_u16(buf, offset, self.oldtag).map_err(|e| match e {
            WireError::BufferTooSmall => TflushError::BufferTooSmall,
            WireError::StringTooLong => TflushError::InternalError,
            WireError::InvalidUtf8 => TflushError::InternalError,
        })?;

        Ok(offset)
    }

    /// Send the Tflush message using p9_write
    /// Returns the number of bytes written, or an error
    pub fn send_tflush(&self) -> Result<P9Response<RflushMessage>, TflushError> {
        get_backend().send_tflush(self)
    }
}

/// Rflush message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RflushMessage {
    /// Message tag
    pub tag: u16,
}

impl RflushMessage {
    /// Create a new Rflush message
    pub fn new(tag: u16) -> Self {
        Self { tag }
    }

    /// Deserialize an Rflush message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RflushError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RflushError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RflushError::BufferTooSmall,
            WireError::StringTooLong => RflushError::InternalError,
            WireError::InvalidUtf8 => RflushError::InternalError,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RflushError::BufferTooSmall);
        }

        // Read message type[1] - should be Rflush
        if offset >= buf.len() {
            return Err(RflushError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rflush as u8 {
            return Err(RflushError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RflushError::BufferTooSmall,
            WireError::StringTooLong => RflushError::InternalError,
            WireError::InvalidUtf8 => RflushError::InternalError,
        })?;
        offset = new_offset;

        let message = Self { tag };

        Ok((message, offset))
    }
}

/// Tflush serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TflushError {
    BufferTooSmall,
    InternalError,
}

/// Rflush deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RflushError {
    BufferTooSmall,
    InvalidMessageType,
    InternalError,
}

/// Tread message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TreadMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Offset to read from
    pub offset: u64,
    /// Number of bytes to read
    pub count: u32,
}

impl TreadMessage {
    /// Create a new Tread message
    pub fn new(tag: u16, fid: u32, offset: u64, count: u32) -> Self {
        Self {
            tag,
            fid,
            offset,
            count,
        }
    }

    /// Serialize the Tread message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TreadError> {
        use wire::{WireError, write_u16, write_u32, write_u64};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4 + 8 + 4; // size[4] + type[1] + tag[2] + fid[4] + offset[8] + count[4]

        if total_size > buf.len() {
            return Err(TreadError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TreadError::BufferTooSmall,
            WireError::StringTooLong => TreadError::InternalError,
            WireError::InvalidUtf8 => TreadError::InternalError,
        })?;

        // Write message type[1] - Tread
        buf[offset] = P9MsgType::Tread as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TreadError::BufferTooSmall,
            WireError::StringTooLong => TreadError::InternalError,
            WireError::InvalidUtf8 => TreadError::InternalError,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TreadError::BufferTooSmall,
            WireError::StringTooLong => TreadError::InternalError,
            WireError::InvalidUtf8 => TreadError::InternalError,
        })?;

        // Write offset[8]
        offset = write_u64(buf, offset, self.offset).map_err(|e| match e {
            WireError::BufferTooSmall => TreadError::BufferTooSmall,
            WireError::StringTooLong => TreadError::InternalError,
            WireError::InvalidUtf8 => TreadError::InternalError,
        })?;

        // Write count[4]
        offset = write_u32(buf, offset, self.count).map_err(|e| match e {
            WireError::BufferTooSmall => TreadError::BufferTooSmall,
            WireError::StringTooLong => TreadError::InternalError,
            WireError::InvalidUtf8 => TreadError::InternalError,
        })?;

        Ok(offset)
    }

    /// Send the Tread message using the active backend
    /// Returns the response from the backend
    pub fn send_tread(&self) -> Result<P9Response<RreadMessage>, TreadError> {
        get_backend().send_tread(self)
    }
}

/// Rread message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RreadMessage {
    /// Message tag
    pub tag: u16,
    /// Number of bytes read
    pub count: u32,
    /// Data that was read
    pub data: Vec<u8>,
}

impl RreadMessage {
    /// Create a new Rread message
    pub fn new(tag: u16, data: Vec<u8>) -> Self {
        Self {
            tag,
            count: data.len() as u32,
            data,
        }
    }

    /// Deserialize an Rread message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RreadError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RreadError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RreadError::BufferTooSmall,
            WireError::StringTooLong => RreadError::InternalError,
            WireError::InvalidUtf8 => RreadError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RreadError::BufferTooSmall);
        }

        // Read message type[1] - should be Rread
        if offset >= buf.len() {
            return Err(RreadError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rread as u8 {
            return Err(RreadError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RreadError::BufferTooSmall,
            WireError::StringTooLong => RreadError::InternalError,
            WireError::InvalidUtf8 => RreadError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read count[4]
        let (count, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RreadError::BufferTooSmall,
            WireError::StringTooLong => RreadError::InternalError,
            WireError::InvalidUtf8 => RreadError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data for the data field
        if offset + count as usize > buf.len() {
            return Err(RreadError::BufferTooSmall);
        }

        // Read the data[count] field
        let data = buf[offset..offset + count as usize].to_vec();
        offset += count as usize;

        let message = Self { tag, count, data };

        Ok((message, offset))
    }
}

impl ReadableMessage for RreadMessage {
    type Error = RreadError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RreadMessage::deserialize(buf)
    }
}

/// Tread serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TreadError {
    BufferTooSmall,
    InternalError,
}

/// Rread deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RreadError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RreadError {
    fn buffer_too_small() -> Self {
        RreadError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RreadError::InvalidMessageType
    }
}

/// Twrite message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TwriteMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Offset to write to
    pub offset: u64,
    /// Number of bytes to write
    pub count: u32,
    /// Data to write
    pub data: Vec<u8>,
}

impl TwriteMessage {
    /// Create a new Twrite message
    pub fn new(tag: u16, fid: u32, offset: u64, data: Vec<u8>) -> Self {
        Self {
            tag,
            fid,
            offset,
            count: data.len() as u32,
            data,
        }
    }

    /// Serialize the Twrite message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TwriteError> {
        use wire::{WireError, write_u16, write_u32, write_u64};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4 + 8 + 4 + self.data.len(); // size[4] + type[1] + tag[2] + fid[4] + offset[8] + count[4] + data[count]

        if total_size > buf.len() {
            return Err(TwriteError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TwriteError::BufferTooSmall,
            WireError::StringTooLong => TwriteError::InternalError,
            WireError::InvalidUtf8 => TwriteError::InternalError,
        })?;

        // Write message type[1] - Twrite
        buf[offset] = P9MsgType::Twrite as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TwriteError::BufferTooSmall,
            WireError::StringTooLong => TwriteError::InternalError,
            WireError::InvalidUtf8 => TwriteError::InternalError,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TwriteError::BufferTooSmall,
            WireError::StringTooLong => TwriteError::InternalError,
            WireError::InvalidUtf8 => TwriteError::InternalError,
        })?;

        // Write offset[8]
        offset = write_u64(buf, offset, self.offset).map_err(|e| match e {
            WireError::BufferTooSmall => TwriteError::BufferTooSmall,
            WireError::StringTooLong => TwriteError::InternalError,
            WireError::InvalidUtf8 => TwriteError::InternalError,
        })?;

        // Write count[4]
        offset = write_u32(buf, offset, self.count).map_err(|e| match e {
            WireError::BufferTooSmall => TwriteError::BufferTooSmall,
            WireError::StringTooLong => TwriteError::InternalError,
            WireError::InvalidUtf8 => TwriteError::InternalError,
        })?;

        // Write data[count]
        if offset + self.data.len() > buf.len() {
            return Err(TwriteError::BufferTooSmall);
        }
        buf[offset..offset + self.data.len()].copy_from_slice(&self.data);
        offset += self.data.len();

        Ok(offset)
    }

    /// Send the Twrite message using host_write
    /// Returns the number of bytes written, or an error
    pub fn send_twrite(&self) -> Result<P9Response<RwriteMessage>, TwriteError> {
        get_backend().send_twrite(self)
    }
}

/// Rwrite message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RwriteMessage {
    /// Message tag
    pub tag: u16,
    /// Number of bytes written
    pub count: u32,
}

impl RwriteMessage {
    /// Create a new Rwrite message
    pub fn new(tag: u16, count: u32) -> Self {
        Self { tag, count }
    }

    /// Deserialize an Rwrite message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RwriteError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RwriteError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RwriteError::BufferTooSmall,
            WireError::StringTooLong => RwriteError::InternalError,
            WireError::InvalidUtf8 => RwriteError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RwriteError::BufferTooSmall);
        }

        // Read message type[1] - should be Rwrite
        if offset >= buf.len() {
            return Err(RwriteError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rwrite as u8 {
            return Err(RwriteError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RwriteError::BufferTooSmall,
            WireError::StringTooLong => RwriteError::InternalError,
            WireError::InvalidUtf8 => RwriteError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read count[4]
        let (count, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RwriteError::BufferTooSmall,
            WireError::StringTooLong => RwriteError::InternalError,
            WireError::InvalidUtf8 => RwriteError::InvalidUtf8,
        })?;
        offset = new_offset;

        let message = Self { tag, count };

        Ok((message, offset))
    }
}

impl ReadableMessage for RwriteMessage {
    type Error = RwriteError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RwriteMessage::deserialize(buf)
    }
}

/// Twrite serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TwriteError {
    BufferTooSmall,
    InternalError,
}

/// Rwrite deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RwriteError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RwriteError {
    fn buffer_too_small() -> Self {
        RwriteError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RwriteError::InvalidMessageType
    }
}

/// Twalk message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TwalkMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// New file identifier
    pub newfid: u32,
    /// Number of path name elements
    pub nwname: u16,
    /// Path name elements
    pub wnames: Vec<String>,
}

impl TwalkMessage {
    /// Create a new Twalk message
    pub fn new(tag: u16, fid: u32, newfid: u32, wnames: Vec<String>) -> Self {
        let nwname = wnames.len() as u16;
        Self {
            tag,
            fid,
            newfid,
            nwname,
            wnames,
        }
    }

    /// Create a new Twalk message with a single path element
    pub fn new_single(tag: u16, fid: u32, newfid: u32, wname: &'static str) -> Self {
        Self::new(tag, fid, newfid, vec![wname.to_string()])
    }

    /// Serialize the Twalk message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TwalkError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        // Calculate total message size
        let mut total_size = 4 + 1 + 2 + 4 + 4 + 2; // size[4] + type[1] + tag[2] + fid[4] + newfid[4] + nwname[2]

        // Add size for each wname[s]
        for wname in &self.wnames {
            total_size += 2 + wname.len(); // length[2] + string[length]
        }

        if total_size > buf.len() {
            return Err(TwalkError::BufferTooSmall);
        }

        if self.nwname as usize != self.wnames.len() {
            return Err(TwalkError::NameCountMismatch);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TwalkError::BufferTooSmall,
            WireError::StringTooLong => TwalkError::NameTooLong,
            WireError::InvalidUtf8 => TwalkError::InternalError,
        })?;

        // Write message type[1] - Twalk
        buf[offset] = P9MsgType::Twalk as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TwalkError::BufferTooSmall,
            WireError::StringTooLong => TwalkError::NameTooLong,
            WireError::InvalidUtf8 => TwalkError::InternalError,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TwalkError::BufferTooSmall,
            WireError::StringTooLong => TwalkError::NameTooLong,
            WireError::InvalidUtf8 => TwalkError::InternalError,
        })?;

        // Write newfid[4]
        offset = write_u32(buf, offset, self.newfid).map_err(|e| match e {
            WireError::BufferTooSmall => TwalkError::BufferTooSmall,
            WireError::StringTooLong => TwalkError::NameTooLong,
            WireError::InvalidUtf8 => TwalkError::InternalError,
        })?;

        // Write nwname[2]
        offset = write_u16(buf, offset, self.nwname).map_err(|e| match e {
            WireError::BufferTooSmall => TwalkError::BufferTooSmall,
            WireError::StringTooLong => TwalkError::NameTooLong,
            WireError::InvalidUtf8 => TwalkError::InternalError,
        })?;

        // Write each wname[s]
        for wname in &self.wnames {
            offset = write_string(buf, offset, wname).map_err(|e| match e {
                WireError::BufferTooSmall => TwalkError::BufferTooSmall,
                WireError::StringTooLong => TwalkError::NameTooLong,
                WireError::InvalidUtf8 => TwalkError::InternalError,
            })?;
        }

        Ok(offset)
    }

    /// Send the Twalk message using the active backend
    /// Returns the response from the backend
    pub fn send_twalk(&self) -> Result<P9Response<RwalkMessage>, TwalkError> {
        get_backend().send_twalk(self)
    }
}

/// Rwalk message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RwalkMessage {
    /// Message tag
    pub tag: u16,
    /// Number of QIDs returned
    pub nwqid: u16,
    /// QIDs returned
    pub wqids: Vec<Qid>,
}

impl RwalkMessage {
    /// Create a new Rwalk message
    pub fn new(tag: u16, wqids: &[Qid]) -> Self {
        let nwqid = wqids.len() as u16;
        Self {
            tag,
            nwqid,
            wqids: wqids.to_vec(),
        }
    }

    /// Create a new Rwalk message with a single QID
    pub fn new_single(tag: u16, qid: Qid) -> Self {
        Self::new(tag, &[qid])
    }

    /// Deserialize an Rwalk message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RwalkError> {
        use wire::{WireError, read_u16, read_u32, read_u64};

        if buf.len() < 4 {
            return Err(RwalkError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RwalkError::BufferTooSmall,
            WireError::StringTooLong => RwalkError::InternalError,
            WireError::InvalidUtf8 => RwalkError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RwalkError::BufferTooSmall);
        }

        // Read message type[1] - should be Rwalk
        if offset >= buf.len() {
            return Err(RwalkError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rwalk as u8 {
            return Err(RwalkError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RwalkError::BufferTooSmall,
            WireError::StringTooLong => RwalkError::InternalError,
            WireError::InvalidUtf8 => RwalkError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read nwqid[2]
        let (nwqid, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RwalkError::BufferTooSmall,
            WireError::StringTooLong => RwalkError::InternalError,
            WireError::InvalidUtf8 => RwalkError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read each wqid[13]
        let mut wqids = Vec::new();

        for _ in 0..nwqid {
            if offset + 13 > buf.len() {
                return Err(RwalkError::BufferTooSmall);
            }

            // Read QID: type[1] version[4] path[8]
            let qtype = buf[offset];
            offset += 1;

            let (version, new_offset) = read_u32(buf, offset).map_err(|e| match e {
                WireError::BufferTooSmall => RwalkError::BufferTooSmall,
                WireError::StringTooLong => RwalkError::InternalError,
                WireError::InvalidUtf8 => RwalkError::InvalidUtf8,
            })?;
            offset = new_offset;

            let (path, new_offset) = read_u64(buf, offset).map_err(|e| match e {
                WireError::BufferTooSmall => RwalkError::BufferTooSmall,
                WireError::StringTooLong => RwalkError::InternalError,
                WireError::InvalidUtf8 => RwalkError::InvalidUtf8,
            })?;
            offset = new_offset;

            wqids.push(Qid::new(qtype, version, path));
        }

        let message = Self { tag, nwqid, wqids };

        Ok((message, offset))
    }
}

impl ReadableMessage for RwalkMessage {
    type Error = RwalkError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        Self::deserialize(buf)
    }
}

/// Twalk serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TwalkError {
    BufferTooSmall,
    NameTooLong,
    NameCountMismatch,
    InternalError,
}

/// Rwalk deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RwalkError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RwalkError {
    fn buffer_too_small() -> Self {
        RwalkError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RwalkError::InvalidMessageType
    }
}

/// Tclunk message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TclunkMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
}

impl TclunkMessage {
    /// Create a new Tclunk message
    pub fn new(tag: u16, fid: u32) -> Self {
        Self { tag, fid }
    }

    /// Serialize the Tclunk message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TclunkError> {
        use wire::{WireError, write_u16, write_u32};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4; // size[4] + type[1] + tag[2] + fid[4]

        if total_size > buf.len() {
            return Err(TclunkError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TclunkError::BufferTooSmall,
            WireError::StringTooLong => TclunkError::InternalError,
            WireError::InvalidUtf8 => TclunkError::InternalError,
        })?;

        // Write message type[1] - Tclunk
        buf[offset] = P9MsgType::Tclunk as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TclunkError::BufferTooSmall,
            WireError::StringTooLong => TclunkError::InternalError,
            WireError::InvalidUtf8 => TclunkError::InternalError,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TclunkError::BufferTooSmall,
            WireError::StringTooLong => TclunkError::InternalError,
            WireError::InvalidUtf8 => TclunkError::InternalError,
        })?;

        Ok(offset)
    }

    /// Send the Tclunk message using the active backend
    /// Returns the response from the backend
    pub fn send_tclunk(&self) -> Result<P9Response<RclunkMessage>, TclunkError> {
        get_backend().send_tclunk(self)
    }
}

/// Rclunk message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RclunkMessage {
    /// Message tag
    pub tag: u16,
}

impl RclunkMessage {
    /// Create a new Rclunk message
    pub fn new(tag: u16) -> Self {
        Self { tag }
    }

    /// Deserialize an Rclunk message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RclunkError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RclunkError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RclunkError::BufferTooSmall,
            WireError::StringTooLong => RclunkError::InternalError,
            WireError::InvalidUtf8 => RclunkError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RclunkError::BufferTooSmall);
        }

        // Read message type[1] - should be Rclunk
        if offset >= buf.len() {
            return Err(RclunkError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rclunk as u8 {
            return Err(RclunkError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RclunkError::BufferTooSmall,
            WireError::StringTooLong => RclunkError::InternalError,
            WireError::InvalidUtf8 => RclunkError::InvalidUtf8,
        })?;
        offset = new_offset;

        let message = Self { tag };

        Ok((message, offset))
    }
}

impl ReadableMessage for RclunkMessage {
    type Error = RclunkError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        Self::deserialize(buf)
    }
}

/// Tclunk serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TclunkError {
    BufferTooSmall,
    InternalError,
}

/// Rclunk deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RclunkError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RclunkError {
    fn buffer_too_small() -> Self {
        RclunkError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RclunkError::InvalidMessageType
    }
}

/// Tremove message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TremoveMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
}

impl TremoveMessage {
    /// Create a new Tremove message
    pub fn new(tag: u16, fid: u32) -> Self {
        Self { tag, fid }
    }

    /// Serialize the Tremove message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TremoveError> {
        use wire::{WireError, write_u16, write_u32};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4; // size[4] + type[1] + tag[2] + fid[4]

        if total_size > buf.len() {
            return Err(TremoveError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TremoveError::BufferTooSmall,
            WireError::StringTooLong => TremoveError::InternalError,
            WireError::InvalidUtf8 => TremoveError::InternalError,
        })?;

        // Write message type[1] - Tremove
        buf[offset] = P9MsgType::Tremove as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TremoveError::BufferTooSmall,
            WireError::StringTooLong => TremoveError::InternalError,
            WireError::InvalidUtf8 => TremoveError::InternalError,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TremoveError::BufferTooSmall,
            WireError::StringTooLong => TremoveError::InternalError,
            WireError::InvalidUtf8 => TremoveError::InternalError,
        })?;

        Ok(offset)
    }

    /// Send the Tremove message using the active backend
    /// Returns the response from the backend
    pub fn send_tremove(&self) -> Result<P9Response<RremoveMessage>, TremoveError> {
        get_backend().send_tremove(self)
    }
}

/// Rremove message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RremoveMessage {
    /// Message tag
    pub tag: u16,
}

impl RremoveMessage {
    /// Create a new Rremove message
    pub fn new(tag: u16) -> Self {
        Self { tag }
    }

    /// Deserialize an Rremove message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RremoveError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RremoveError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RremoveError::BufferTooSmall,
            WireError::StringTooLong => RremoveError::InternalError,
            WireError::InvalidUtf8 => RremoveError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RremoveError::BufferTooSmall);
        }

        // Read message type[1] - should be Rremove
        if offset >= buf.len() {
            return Err(RremoveError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rremove as u8 {
            return Err(RremoveError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RremoveError::BufferTooSmall,
            WireError::StringTooLong => RremoveError::InternalError,
            WireError::InvalidUtf8 => RremoveError::InvalidUtf8,
        })?;
        offset = new_offset;

        let message = Self { tag };

        Ok((message, offset))
    }
}

/// Tremove serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TremoveError {
    BufferTooSmall,
    InternalError,
}

/// Rremove deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RremoveError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RremoveError {
    fn buffer_too_small() -> Self {
        RremoveError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RremoveError::InvalidMessageType
    }
}

impl ReadableMessage for RremoveMessage {
    type Error = RremoveError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RremoveMessage::deserialize(buf)
    }
}

/// Tauth message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TauthMessage {
    /// Message tag
    pub tag: u16,
    /// Authentication file identifier
    pub afid: u32,
    /// User name
    pub uname: String,
    /// Authentication name
    pub aname: String,
    /// Number of uname bytes
    pub n_uname: u32,
}

impl TauthMessage {
    /// Create a new Tauth message
    pub fn new(tag: u16, afid: u32, uname: String, aname: String) -> Self {
        let n_uname = uname.len() as u32;
        Self {
            tag,
            afid,
            uname,
            aname,
            n_uname,
        }
    }

    /// Serialize the Tauth message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TauthError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4 + (2 + self.uname.len()) + (2 + self.aname.len()) + 4;
        // size[4] + type[1] + tag[2] + afid[4] + uname[s] + aname[s] + n_uname[4]

        if total_size > buf.len() {
            return Err(TauthError::BufferTooSmall);
        }

        if self.n_uname as usize != self.uname.len() {
            return Err(TauthError::UnameCountMismatch);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TauthError::BufferTooSmall,
            WireError::StringTooLong => TauthError::StringTooLong,
            WireError::InvalidUtf8 => TauthError::InvalidUtf8,
        })?;

        // Write message type[1] - Tauth
        buf[offset] = P9MsgType::Tauth as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TauthError::BufferTooSmall,
            WireError::StringTooLong => TauthError::StringTooLong,
            WireError::InvalidUtf8 => TauthError::InvalidUtf8,
        })?;

        // Write afid[4]
        offset = write_u32(buf, offset, self.afid).map_err(|e| match e {
            WireError::BufferTooSmall => TauthError::BufferTooSmall,
            WireError::StringTooLong => TauthError::StringTooLong,
            WireError::InvalidUtf8 => TauthError::InvalidUtf8,
        })?;

        // Write uname[s]
        offset = write_string(buf, offset, &self.uname).map_err(|e| match e {
            WireError::BufferTooSmall => TauthError::BufferTooSmall,
            WireError::StringTooLong => TauthError::StringTooLong,
            WireError::InvalidUtf8 => TauthError::InvalidUtf8,
        })?;

        // Write aname[s]
        offset = write_string(buf, offset, &self.aname).map_err(|e| match e {
            WireError::BufferTooSmall => TauthError::BufferTooSmall,
            WireError::StringTooLong => TauthError::StringTooLong,
            WireError::InvalidUtf8 => TauthError::InvalidUtf8,
        })?;

        // Write n_uname[4]
        offset = write_u32(buf, offset, self.n_uname).map_err(|e| match e {
            WireError::BufferTooSmall => TauthError::BufferTooSmall,
            WireError::StringTooLong => TauthError::StringTooLong,
            WireError::InvalidUtf8 => TauthError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tauth message using the active backend
    pub fn send_tauth(&self) -> Result<P9Response<RauthMessage>, TauthError> {
        get_backend().send_tauth(self)
    }
}

/// Rauth message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RauthMessage {
    /// Message tag
    pub tag: u16,
    /// Authentication QID
    pub aqid: Qid,
}

impl RauthMessage {
    /// Create a new Rauth message
    pub fn new(tag: u16, aqid: Qid) -> Self {
        Self { tag, aqid }
    }

    /// Deserialize an Rauth message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RauthError> {
        use wire::{WireError, read_u16, read_u32, read_u64};

        if buf.len() < 4 {
            return Err(RauthError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RauthError::BufferTooSmall,
            WireError::StringTooLong => RauthError::InternalError,
            WireError::InvalidUtf8 => RauthError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RauthError::BufferTooSmall);
        }

        // Read message type[1] - should be Rauth
        if offset >= buf.len() {
            return Err(RauthError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rauth as u8 {
            return Err(RauthError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RauthError::BufferTooSmall,
            WireError::StringTooLong => RauthError::InternalError,
            WireError::InvalidUtf8 => RauthError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read aqid[13] - type[1] version[4] path[8]
        if offset + 13 > buf.len() {
            return Err(RauthError::BufferTooSmall);
        }

        let qtype = buf[offset];
        offset += 1;

        let (version, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RauthError::BufferTooSmall,
            WireError::StringTooLong => RauthError::InternalError,
            WireError::InvalidUtf8 => RauthError::InvalidUtf8,
        })?;
        offset = new_offset;

        let (path, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RauthError::BufferTooSmall,
            WireError::StringTooLong => RauthError::InternalError,
            WireError::InvalidUtf8 => RauthError::InvalidUtf8,
        })?;
        offset = new_offset;

        let aqid = Qid::new(qtype, version, path);

        let message = Self { tag, aqid };

        Ok((message, offset))
    }
}

/// Tauth serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TauthError {
    BufferTooSmall,
    StringTooLong,
    UnameCountMismatch,
    InvalidUtf8,
    InternalError,
}

/// Rauth deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RauthError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

/// Tattach message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TattachMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Authentication file identifier
    pub afid: u32,
    /// User name
    pub uname: String,
    /// Authentication name
    pub aname: String,
    /// Number of uname bytes
    pub n_uname: u32,
}

impl TattachMessage {
    /// Create a new Tattach message
    pub fn new(tag: u16, fid: u32, afid: u32, uname: String, aname: String) -> Self {
        let n_uname = uname.len() as u32;
        Self {
            tag,
            fid,
            afid,
            uname,
            aname,
            n_uname,
        }
    }

    /// Serialize the Tattach message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TattachError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4 + 4 + (2 + self.uname.len()) + (2 + self.aname.len()) + 4;
        // size[4] + type[1] + tag[2] + fid[4] + afid[4] + uname[s] + aname[s] + n_uname[4]

        if total_size > buf.len() {
            return Err(TattachError::BufferTooSmall);
        }

        if self.n_uname as usize != self.uname.len() {
            return Err(TattachError::UnameCountMismatch);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TattachError::BufferTooSmall,
            WireError::StringTooLong => TattachError::StringTooLong,
            WireError::InvalidUtf8 => TattachError::InvalidUtf8,
        })?;

        // Write message type[1] - Tattach
        buf[offset] = P9MsgType::Tattach as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TattachError::BufferTooSmall,
            WireError::StringTooLong => TattachError::StringTooLong,
            WireError::InvalidUtf8 => TattachError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TattachError::BufferTooSmall,
            WireError::StringTooLong => TattachError::StringTooLong,
            WireError::InvalidUtf8 => TattachError::InvalidUtf8,
        })?;

        // Write afid[4]
        offset = write_u32(buf, offset, self.afid).map_err(|e| match e {
            WireError::BufferTooSmall => TattachError::BufferTooSmall,
            WireError::StringTooLong => TattachError::StringTooLong,
            WireError::InvalidUtf8 => TattachError::InvalidUtf8,
        })?;

        // Write uname[s]
        offset = write_string(buf, offset, &self.uname).map_err(|e| match e {
            WireError::BufferTooSmall => TattachError::BufferTooSmall,
            WireError::StringTooLong => TattachError::StringTooLong,
            WireError::InvalidUtf8 => TattachError::InvalidUtf8,
        })?;

        // Write aname[s]
        offset = write_string(buf, offset, &self.aname).map_err(|e| match e {
            WireError::BufferTooSmall => TattachError::BufferTooSmall,
            WireError::StringTooLong => TattachError::StringTooLong,
            WireError::InvalidUtf8 => TattachError::InvalidUtf8,
        })?;

        // Write n_uname[4]
        offset = write_u32(buf, offset, self.n_uname).map_err(|e| match e {
            WireError::BufferTooSmall => TattachError::BufferTooSmall,
            WireError::StringTooLong => TattachError::StringTooLong,
            WireError::InvalidUtf8 => TattachError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tattach message using the active backend
    /// Returns the response from the backend
    pub fn send_tattach(&self) -> Result<P9Response<RattachMessage>, TattachError> {
        get_backend().send_tattach(self)
    }
}

/// Rattach message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RattachMessage {
    /// Message tag
    pub tag: u16,
    /// Root QID
    pub qid: Qid,
}

impl RattachMessage {
    /// Create a new Rattach message
    pub fn new(tag: u16, qid: Qid) -> Self {
        Self { tag, qid }
    }

    /// Deserialize an Rattach message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RattachError> {
        use wire::{WireError, read_u16, read_u32, read_u64};

        if buf.len() < 4 {
            return Err(RattachError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RattachError::BufferTooSmall,
            WireError::StringTooLong => RattachError::InternalError,
            WireError::InvalidUtf8 => RattachError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RattachError::BufferTooSmall);
        }

        // Read message type[1] - should be Rattach
        if offset >= buf.len() {
            return Err(RattachError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rattach as u8 {
            return Err(RattachError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RattachError::BufferTooSmall,
            WireError::StringTooLong => RattachError::InternalError,
            WireError::InvalidUtf8 => RattachError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read qid[13] - type[1] version[4] path[8]
        if offset + 13 > buf.len() {
            return Err(RattachError::BufferTooSmall);
        }

        let qtype = buf[offset];
        offset += 1;

        let (version, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RattachError::BufferTooSmall,
            WireError::StringTooLong => RattachError::InternalError,
            WireError::InvalidUtf8 => RattachError::InvalidUtf8,
        })?;
        offset = new_offset;

        let (path, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RattachError::BufferTooSmall,
            WireError::StringTooLong => RattachError::InternalError,
            WireError::InvalidUtf8 => RattachError::InvalidUtf8,
        })?;
        offset = new_offset;

        let qid = Qid::new(qtype, version, path);

        let message = Self { tag, qid };

        Ok((message, offset))
    }
}

impl ReadableMessage for RattachMessage {
    type Error = RattachError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        Self::deserialize(buf)
    }
}

/// Tattach serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TattachError {
    BufferTooSmall,
    StringTooLong,
    UnameCountMismatch,
    InvalidUtf8,
    InternalError,
}

/// Rattach deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RattachError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RattachError {
    fn buffer_too_small() -> Self {
        RattachError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RattachError::InvalidMessageType
    }
}

/// Rlerror message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RlerrorMessage {
    /// Message tag
    pub tag: u16,
    /// Error code
    pub ecode: u32,
}

impl RlerrorMessage {
    /// Create a new Rlerror message
    pub fn new(tag: u16, ecode: u32) -> Self {
        Self { tag, ecode }
    }

    /// Deserialize an Rlerror message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RlerrorError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RlerrorError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlerrorError::BufferTooSmall,
            WireError::StringTooLong => RlerrorError::InternalError,
            WireError::InvalidUtf8 => RlerrorError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RlerrorError::BufferTooSmall);
        }

        // Read message type[1] - should be Rlerror
        if offset >= buf.len() {
            return Err(RlerrorError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::RLerror as u8 {
            return Err(RlerrorError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlerrorError::BufferTooSmall,
            WireError::StringTooLong => RlerrorError::InternalError,
            WireError::InvalidUtf8 => RlerrorError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read ecode[4]
        let (ecode, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlerrorError::BufferTooSmall,
            WireError::StringTooLong => RlerrorError::InternalError,
            WireError::InvalidUtf8 => RlerrorError::InvalidUtf8,
        })?;
        offset = new_offset;

        let message = Self { tag, ecode };

        Ok((message, offset))
    }
}

impl ReadableMessage for RlerrorMessage {
    type Error = RlerrorError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        Self::deserialize(buf)
    }
}

/// Rlerror deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RlerrorError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RlerrorError {
    fn buffer_too_small() -> Self {
        RlerrorError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RlerrorError::InvalidMessageType
    }
}

/// Tstatfs message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TstatfsMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
}

impl TstatfsMessage {
    /// Create a new Tstatfs message
    pub fn new(tag: u16, fid: u32) -> Self {
        Self { tag, fid }
    }

    /// Serialize the Tstatfs message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TstatfsError> {
        use wire::{WireError, write_u16, write_u32};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4; // size[4] + type[1] + tag[2] + fid[4]

        if total_size > buf.len() {
            return Err(TstatfsError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TstatfsError::BufferTooSmall,
            WireError::StringTooLong => TstatfsError::InternalError,
            WireError::InvalidUtf8 => TstatfsError::InternalError,
        })?;

        // Write message type[1] - Tstatfs
        buf[offset] = P9MsgType::Tstatfs as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TstatfsError::BufferTooSmall,
            WireError::StringTooLong => TstatfsError::InternalError,
            WireError::InvalidUtf8 => TstatfsError::InternalError,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TstatfsError::BufferTooSmall,
            WireError::StringTooLong => TstatfsError::InternalError,
            WireError::InvalidUtf8 => TstatfsError::InternalError,
        })?;

        Ok(offset)
    }

    /// Send the Tstatfs message using the active backend
    pub fn send_tstatfs(&self) -> Result<P9Response<RstatfsMessage>, TstatfsError> {
        get_backend().send_tstatfs(self)
    }
}

/// Rstatfs message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RstatfsMessage {
    /// Message tag
    pub tag: u16,
    /// File system type
    pub type_: u32,
    /// Block size
    pub bsize: u32,
    /// Total blocks
    pub blocks: u64,
    /// Free blocks
    pub bfree: u64,
    /// Available blocks
    pub bavail: u64,
    /// Total files
    pub files: u64,
    /// Free files
    pub ffree: u64,
    /// File system ID
    pub fsid: u64,
    /// Maximum filename length
    pub namelen: u32,
}

impl RstatfsMessage {
    /// Create a new Rstatfs message
    #[allow(clippy::too_many_arguments)]
    pub fn new(
        tag: u16,
        type_: u32,
        bsize: u32,
        blocks: u64,
        bfree: u64,
        bavail: u64,
        files: u64,
        ffree: u64,
        fsid: u64,
        namelen: u32,
    ) -> Self {
        Self {
            tag,
            type_,
            bsize,
            blocks,
            bfree,
            bavail,
            files,
            ffree,
            fsid,
            namelen,
        }
    }

    /// Deserialize an Rstatfs message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RstatfsError> {
        use wire::{WireError, read_u16, read_u32, read_u64};

        if buf.len() < 4 {
            return Err(RstatfsError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RstatfsError::BufferTooSmall);
        }

        // Read message type[1] - should be Rstatfs
        if offset >= buf.len() {
            return Err(RstatfsError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rstatfs as u8 {
            return Err(RstatfsError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read type[4]
        let (type_, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read bsize[4]
        let (bsize, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read blocks[8]
        let (blocks, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read bfree[8]
        let (bfree, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read bavail[8]
        let (bavail, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read files[8]
        let (files, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read ffree[8]
        let (ffree, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read fsid[8]
        let (fsid, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read namelen[4]
        let (namelen, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RstatfsError::BufferTooSmall,
            WireError::StringTooLong => RstatfsError::InternalError,
            WireError::InvalidUtf8 => RstatfsError::InvalidUtf8,
        })?;
        offset = new_offset;

        let message = Self {
            tag,
            type_,
            bsize,
            blocks,
            bfree,
            bavail,
            files,
            ffree,
            fsid,
            namelen,
        };

        Ok((message, offset))
    }
}

/// Tstatfs serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TstatfsError {
    BufferTooSmall,
    InternalError,
}

/// Rstatfs deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RstatfsError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

/// Tlopen message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TlopenMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Open flags
    pub flags: u32,
}

impl TlopenMessage {
    /// Create a new Tlopen message
    pub fn new(tag: u16, fid: u32, flags: u32) -> Self {
        Self { tag, fid, flags }
    }

    /// Serialize the Tlopen message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TlopenError> {
        use wire::{WireError, write_u16, write_u32};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4 + 4; // size[4] + type[1] + tag[2] + fid[4] + flags[4]

        if total_size > buf.len() {
            return Err(TlopenError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TlopenError::BufferTooSmall,
            WireError::StringTooLong => TlopenError::InternalError,
            WireError::InvalidUtf8 => TlopenError::InternalError,
        })?;

        // Write message type[1] - Tlopen
        buf[offset] = P9MsgType::Tlopen as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TlopenError::BufferTooSmall,
            WireError::StringTooLong => TlopenError::InternalError,
            WireError::InvalidUtf8 => TlopenError::InternalError,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TlopenError::BufferTooSmall,
            WireError::StringTooLong => TlopenError::InternalError,
            WireError::InvalidUtf8 => TlopenError::InternalError,
        })?;

        // Write flags[4]
        offset = write_u32(buf, offset, self.flags).map_err(|e| match e {
            WireError::BufferTooSmall => TlopenError::BufferTooSmall,
            WireError::StringTooLong => TlopenError::InternalError,
            WireError::InvalidUtf8 => TlopenError::InternalError,
        })?;

        Ok(offset)
    }

    /// Send the Tlopen message using the active backend
    /// Returns the response from the backend
    pub fn send_tlopen(&self) -> Result<P9Response<RlopenMessage>, TlopenError> {
        get_backend().send_tlopen(self)
    }
}

/// Rlopen message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RlopenMessage {
    /// Message tag
    pub tag: u16,
    /// QID of the opened file
    pub qid: Qid,
    /// I/O unit size
    pub iounit: u32,
}

impl RlopenMessage {
    /// Create a new Rlopen message
    pub fn new(tag: u16, qid: Qid, iounit: u32) -> Self {
        Self { tag, qid, iounit }
    }

    /// Deserialize an Rlopen message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RlopenError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RlopenError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlopenError::BufferTooSmall,
            WireError::StringTooLong => RlopenError::InternalError,
            WireError::InvalidUtf8 => RlopenError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RlopenError::BufferTooSmall);
        }

        // Read message type[1] - should be Rlopen
        if offset >= buf.len() {
            return Err(RlopenError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rlopen as u8 {
            return Err(RlopenError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlopenError::BufferTooSmall,
            WireError::StringTooLong => RlopenError::InternalError,
            WireError::InvalidUtf8 => RlopenError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read qid[13] - type[1] version[4] path[8]
        if offset + 13 > buf.len() {
            return Err(RlopenError::BufferTooSmall);
        }
        let qid = Qid {
            qtype: buf[offset],
            version: u32::from_le_bytes([
                buf[offset + 1],
                buf[offset + 2],
                buf[offset + 3],
                buf[offset + 4],
            ]),
            path: u64::from_le_bytes([
                buf[offset + 5],
                buf[offset + 6],
                buf[offset + 7],
                buf[offset + 8],
                buf[offset + 9],
                buf[offset + 10],
                buf[offset + 11],
                buf[offset + 12],
            ]),
        };
        offset += 13;

        // Read iounit[4]
        let (iounit, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlopenError::BufferTooSmall,
            WireError::StringTooLong => RlopenError::InternalError,
            WireError::InvalidUtf8 => RlopenError::InvalidUtf8,
        })?;
        offset = new_offset;

        let message = Self { tag, qid, iounit };

        Ok((message, offset))
    }
}

impl ReadableMessage for RlopenMessage {
    type Error = RlopenError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        Self::deserialize(buf)
    }
}

/// Tlopen serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TlopenError {
    BufferTooSmall,
    InternalError,
}

/// Rlopen deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RlopenError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RlopenError {
    fn buffer_too_small() -> Self {
        RlopenError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RlopenError::InvalidMessageType
    }
}

/// Tlcreate message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TlcreateMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Name of the file to create
    pub name: String,
    /// Open flags
    pub flags: u32,
    /// File mode
    pub mode: u32,
    /// Group ID
    pub gid: u32,
}

impl TlcreateMessage {
    /// Create a new Tlcreate message
    pub fn new(tag: u16, fid: u32, name: String, flags: u32, mode: u32, gid: u32) -> Self {
        Self {
            tag,
            fid,
            name,
            flags,
            mode,
            gid,
        }
    }

    /// Serialize the Tlcreate message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TlcreateError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        // Calculate total message size
        let name_len = self.name.len();
        let total_size = 4 + 1 + 2 + 4 + (2 + name_len) + 4 + 4 + 4; // size[4] + type[1] + tag[2] + fid[4] + name[s] + flags[4] + mode[4] + gid[4]

        if total_size > buf.len() {
            return Err(TlcreateError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TlcreateError::BufferTooSmall,
            WireError::StringTooLong => TlcreateError::NameTooLong,
            WireError::InvalidUtf8 => TlcreateError::InvalidUtf8,
        })?;

        // Write message type[1] - Tlcreate
        buf[offset] = P9MsgType::Tlcreate as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TlcreateError::BufferTooSmall,
            WireError::StringTooLong => TlcreateError::InternalError,
            WireError::InvalidUtf8 => TlcreateError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TlcreateError::BufferTooSmall,
            WireError::StringTooLong => TlcreateError::InternalError,
            WireError::InvalidUtf8 => TlcreateError::InvalidUtf8,
        })?;

        // Write name[s]
        offset = write_string(buf, offset, &self.name).map_err(|e| match e {
            WireError::BufferTooSmall => TlcreateError::BufferTooSmall,
            WireError::StringTooLong => TlcreateError::NameTooLong,
            WireError::InvalidUtf8 => TlcreateError::InvalidUtf8,
        })?;

        // Write flags[4]
        offset = write_u32(buf, offset, self.flags).map_err(|e| match e {
            WireError::BufferTooSmall => TlcreateError::BufferTooSmall,
            WireError::StringTooLong => TlcreateError::InternalError,
            WireError::InvalidUtf8 => TlcreateError::InvalidUtf8,
        })?;

        // Write mode[4]
        offset = write_u32(buf, offset, self.mode).map_err(|e| match e {
            WireError::BufferTooSmall => TlcreateError::BufferTooSmall,
            WireError::StringTooLong => TlcreateError::InternalError,
            WireError::InvalidUtf8 => TlcreateError::InvalidUtf8,
        })?;

        // Write gid[4]
        offset = write_u32(buf, offset, self.gid).map_err(|e| match e {
            WireError::BufferTooSmall => TlcreateError::BufferTooSmall,
            WireError::StringTooLong => TlcreateError::InternalError,
            WireError::InvalidUtf8 => TlcreateError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tlcreate message using the active backend
    /// Returns the response from the backend
    pub fn send_tlcreate(&self) -> Result<P9Response<RlcreateMessage>, TlcreateError> {
        get_backend().send_tlcreate(self)
    }
}

/// Rlcreate message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RlcreateMessage {
    /// Message tag
    pub tag: u16,
    /// QID of the created file
    pub qid: Qid,
    /// I/O unit size
    pub iounit: u32,
}

impl RlcreateMessage {
    /// Create a new Rlcreate message
    pub fn new(tag: u16, qid: Qid, iounit: u32) -> Self {
        Self { tag, qid, iounit }
    }

    /// Deserialize an Rlcreate message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RlcreateError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RlcreateError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlcreateError::BufferTooSmall,
            WireError::StringTooLong => RlcreateError::InternalError,
            WireError::InvalidUtf8 => RlcreateError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RlcreateError::BufferTooSmall);
        }

        // Read message type[1] - should be Rlcreate
        if offset >= buf.len() {
            return Err(RlcreateError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rlcreate as u8 {
            return Err(RlcreateError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlcreateError::BufferTooSmall,
            WireError::StringTooLong => RlcreateError::InternalError,
            WireError::InvalidUtf8 => RlcreateError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read qid[13] - type[1] version[4] path[8]
        if offset + 13 > buf.len() {
            return Err(RlcreateError::BufferTooSmall);
        }
        let qid = Qid {
            qtype: buf[offset],
            version: u32::from_le_bytes([
                buf[offset + 1],
                buf[offset + 2],
                buf[offset + 3],
                buf[offset + 4],
            ]),
            path: u64::from_le_bytes([
                buf[offset + 5],
                buf[offset + 6],
                buf[offset + 7],
                buf[offset + 8],
                buf[offset + 9],
                buf[offset + 10],
                buf[offset + 11],
                buf[offset + 12],
            ]),
        };
        offset += 13;

        // Read iounit[4]
        let (iounit, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlcreateError::BufferTooSmall,
            WireError::StringTooLong => RlcreateError::InternalError,
            WireError::InvalidUtf8 => RlcreateError::InvalidUtf8,
        })?;
        offset = new_offset;

        let message = Self { tag, qid, iounit };

        Ok((message, offset))
    }
}

impl ReadableMessage for RlcreateMessage {
    type Error = RlcreateError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RlcreateMessage::deserialize(buf)
    }
}

/// Tlcreate serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TlcreateError {
    BufferTooSmall,
    NameTooLong,
    InvalidUtf8,
    InternalError,
}

/// Rlcreate deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RlcreateError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RlcreateError {
    fn buffer_too_small() -> Self {
        RlcreateError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RlcreateError::InvalidMessageType
    }
}

/// Tsymlink message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TsymlinkMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Name of the symlink
    pub name: String,
    /// Symlink target
    pub symtgt: String,
    /// Group ID
    pub gid: u32,
}

impl TsymlinkMessage {
    /// Create a new Tsymlink message
    pub fn new(tag: u16, fid: u32, name: String, symtgt: String, gid: u32) -> Self {
        Self {
            tag,
            fid,
            name,
            symtgt,
            gid,
        }
    }

    /// Serialize the Tsymlink message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TsymlinkError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        let name_len = self.name.len();
        let symtgt_len = self.symtgt.len();
        let total_size = 4 + 1 + 2 + 4 + (2 + name_len) + (2 + symtgt_len) + 4;

        if total_size > buf.len() {
            return Err(TsymlinkError::BufferTooSmall);
        }

        let mut offset = 0;
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TsymlinkError::BufferTooSmall,
            WireError::StringTooLong => TsymlinkError::StringTooLong,
            WireError::InvalidUtf8 => TsymlinkError::InvalidUtf8,
        })?;

        buf[offset] = P9MsgType::Tsymlink as u8;
        offset += 1;

        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TsymlinkError::BufferTooSmall,
            WireError::StringTooLong => TsymlinkError::InternalError,
            WireError::InvalidUtf8 => TsymlinkError::InvalidUtf8,
        })?;

        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TsymlinkError::BufferTooSmall,
            WireError::StringTooLong => TsymlinkError::InternalError,
            WireError::InvalidUtf8 => TsymlinkError::InvalidUtf8,
        })?;

        offset = write_string(buf, offset, &self.name).map_err(|e| match e {
            WireError::BufferTooSmall => TsymlinkError::BufferTooSmall,
            WireError::StringTooLong => TsymlinkError::StringTooLong,
            WireError::InvalidUtf8 => TsymlinkError::InvalidUtf8,
        })?;

        offset = write_string(buf, offset, &self.symtgt).map_err(|e| match e {
            WireError::BufferTooSmall => TsymlinkError::BufferTooSmall,
            WireError::StringTooLong => TsymlinkError::StringTooLong,
            WireError::InvalidUtf8 => TsymlinkError::InvalidUtf8,
        })?;

        offset = write_u32(buf, offset, self.gid).map_err(|e| match e {
            WireError::BufferTooSmall => TsymlinkError::BufferTooSmall,
            WireError::StringTooLong => TsymlinkError::InternalError,
            WireError::InvalidUtf8 => TsymlinkError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tsymlink message using the active backend
    pub fn send_tsymlink(&self) -> Result<P9Response<RsymlinkMessage>, TsymlinkError> {
        get_backend().send_tsymlink(self)
    }
}

/// Rsymlink message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RsymlinkMessage {
    /// Message tag
    pub tag: u16,
    /// QID of the created symlink
    pub qid: Qid,
}

impl RsymlinkMessage {
    /// Create a new Rsymlink message
    pub fn new(tag: u16, qid: Qid) -> Self {
        Self { tag, qid }
    }

    /// Deserialize an Rsymlink message from a buffer
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RsymlinkError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RsymlinkError::BufferTooSmall);
        }

        let mut offset = 0;
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RsymlinkError::BufferTooSmall,
            WireError::StringTooLong => RsymlinkError::InternalError,
            WireError::InvalidUtf8 => RsymlinkError::InvalidUtf8,
        })?;
        offset = new_offset;

        if buf.len() < size as usize {
            return Err(RsymlinkError::BufferTooSmall);
        }

        if offset >= buf.len() {
            return Err(RsymlinkError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rsymlink as u8 {
            return Err(RsymlinkError::InvalidMessageType);
        }

        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RsymlinkError::BufferTooSmall,
            WireError::StringTooLong => RsymlinkError::InternalError,
            WireError::InvalidUtf8 => RsymlinkError::InvalidUtf8,
        })?;
        offset = new_offset;

        if offset + 13 > buf.len() {
            return Err(RsymlinkError::BufferTooSmall);
        }
        let qid = Qid {
            qtype: buf[offset],
            version: u32::from_le_bytes([
                buf[offset + 1],
                buf[offset + 2],
                buf[offset + 3],
                buf[offset + 4],
            ]),
            path: u64::from_le_bytes([
                buf[offset + 5],
                buf[offset + 6],
                buf[offset + 7],
                buf[offset + 8],
                buf[offset + 9],
                buf[offset + 10],
                buf[offset + 11],
                buf[offset + 12],
            ]),
        };
        offset += 13;

        Ok((Self { tag, qid }, offset))
    }
}

/// Tmknod message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TmknodMessage {
    /// Message tag
    pub tag: u16,
    /// Directory file identifier
    pub dfid: u32,
    /// Name of the device file
    pub name: String,
    /// File mode
    pub mode: u32,
    /// Major device number
    pub major: u32,
    /// Minor device number
    pub minor: u32,
    /// Group ID
    pub gid: u32,
}

impl TmknodMessage {
    /// Create a new Tmknod message
    pub fn new(
        tag: u16,
        dfid: u32,
        name: String,
        mode: u32,
        major: u32,
        minor: u32,
        gid: u32,
    ) -> Self {
        Self {
            tag,
            dfid,
            name,
            mode,
            major,
            minor,
            gid,
        }
    }

    /// Serialize the Tmknod message to a buffer
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TmknodError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        let name_len = self.name.len();
        let total_size = 4 + 1 + 2 + 4 + (2 + name_len) + 4 + 4 + 4 + 4;

        if total_size > buf.len() {
            return Err(TmknodError::BufferTooSmall);
        }

        let mut offset = 0;
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TmknodError::BufferTooSmall,
            WireError::StringTooLong => TmknodError::NameTooLong,
            WireError::InvalidUtf8 => TmknodError::InvalidUtf8,
        })?;

        buf[offset] = P9MsgType::Tmknod as u8;
        offset += 1;

        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TmknodError::BufferTooSmall,
            WireError::StringTooLong => TmknodError::InternalError,
            WireError::InvalidUtf8 => TmknodError::InvalidUtf8,
        })?;

        offset = write_u32(buf, offset, self.dfid).map_err(|e| match e {
            WireError::BufferTooSmall => TmknodError::BufferTooSmall,
            WireError::StringTooLong => TmknodError::InternalError,
            WireError::InvalidUtf8 => TmknodError::InvalidUtf8,
        })?;

        offset = write_string(buf, offset, &self.name).map_err(|e| match e {
            WireError::BufferTooSmall => TmknodError::BufferTooSmall,
            WireError::StringTooLong => TmknodError::NameTooLong,
            WireError::InvalidUtf8 => TmknodError::InvalidUtf8,
        })?;

        offset = write_u32(buf, offset, self.mode).map_err(|e| match e {
            WireError::BufferTooSmall => TmknodError::BufferTooSmall,
            WireError::StringTooLong => TmknodError::InternalError,
            WireError::InvalidUtf8 => TmknodError::InvalidUtf8,
        })?;

        offset = write_u32(buf, offset, self.major).map_err(|e| match e {
            WireError::BufferTooSmall => TmknodError::BufferTooSmall,
            WireError::StringTooLong => TmknodError::InternalError,
            WireError::InvalidUtf8 => TmknodError::InvalidUtf8,
        })?;

        offset = write_u32(buf, offset, self.minor).map_err(|e| match e {
            WireError::BufferTooSmall => TmknodError::BufferTooSmall,
            WireError::StringTooLong => TmknodError::InternalError,
            WireError::InvalidUtf8 => TmknodError::InvalidUtf8,
        })?;

        offset = write_u32(buf, offset, self.gid).map_err(|e| match e {
            WireError::BufferTooSmall => TmknodError::BufferTooSmall,
            WireError::StringTooLong => TmknodError::InternalError,
            WireError::InvalidUtf8 => TmknodError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tmknod message using the active backend
    pub fn send_tmknod(&self) -> Result<P9Response<RmknodMessage>, TmknodError> {
        get_backend().send_tmknod(self)
    }
}

/// Rmknod message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RmknodMessage {
    /// Message tag
    pub tag: u16,
    /// QID of the created device file
    pub qid: Qid,
}

impl RmknodMessage {
    /// Create a new Rmknod message
    pub fn new(tag: u16, qid: Qid) -> Self {
        Self { tag, qid }
    }

    /// Deserialize an Rmknod message from a buffer
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RmknodError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RmknodError::BufferTooSmall);
        }

        let mut offset = 0;
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RmknodError::BufferTooSmall,
            WireError::StringTooLong => RmknodError::InternalError,
            WireError::InvalidUtf8 => RmknodError::InvalidUtf8,
        })?;
        offset = new_offset;

        if buf.len() < size as usize {
            return Err(RmknodError::BufferTooSmall);
        }

        if offset >= buf.len() {
            return Err(RmknodError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rmknod as u8 {
            return Err(RmknodError::InvalidMessageType);
        }

        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RmknodError::BufferTooSmall,
            WireError::StringTooLong => RmknodError::InternalError,
            WireError::InvalidUtf8 => RmknodError::InvalidUtf8,
        })?;
        offset = new_offset;

        if offset + 13 > buf.len() {
            return Err(RmknodError::BufferTooSmall);
        }
        let qid = Qid {
            qtype: buf[offset],
            version: u32::from_le_bytes([
                buf[offset + 1],
                buf[offset + 2],
                buf[offset + 3],
                buf[offset + 4],
            ]),
            path: u64::from_le_bytes([
                buf[offset + 5],
                buf[offset + 6],
                buf[offset + 7],
                buf[offset + 8],
                buf[offset + 9],
                buf[offset + 10],
                buf[offset + 11],
                buf[offset + 12],
            ]),
        };
        offset += 13;

        Ok((Self { tag, qid }, offset))
    }
}

impl ReadableMessage for RmknodMessage {
    type Error = RmknodError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RmknodMessage::deserialize(buf)
    }
}

/// Trename message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TrenameMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Directory file identifier
    pub dfid: u32,
    /// New name
    pub name: String,
}

impl TrenameMessage {
    /// Create a new Trename message
    pub fn new(tag: u16, fid: u32, dfid: u32, name: String) -> Self {
        Self {
            tag,
            fid,
            dfid,
            name,
        }
    }

    /// Serialize the Trename message to a buffer
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TrenameError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        let name_len = self.name.len();
        let total_size = 4 + 1 + 2 + 4 + 4 + (2 + name_len);

        if total_size > buf.len() {
            return Err(TrenameError::BufferTooSmall);
        }

        let mut offset = 0;
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameError::BufferTooSmall,
            WireError::StringTooLong => TrenameError::NameTooLong,
            WireError::InvalidUtf8 => TrenameError::InvalidUtf8,
        })?;

        buf[offset] = P9MsgType::Trename as u8;
        offset += 1;

        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameError::BufferTooSmall,
            WireError::StringTooLong => TrenameError::InternalError,
            WireError::InvalidUtf8 => TrenameError::InvalidUtf8,
        })?;

        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameError::BufferTooSmall,
            WireError::StringTooLong => TrenameError::InternalError,
            WireError::InvalidUtf8 => TrenameError::InvalidUtf8,
        })?;

        offset = write_u32(buf, offset, self.dfid).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameError::BufferTooSmall,
            WireError::StringTooLong => TrenameError::InternalError,
            WireError::InvalidUtf8 => TrenameError::InvalidUtf8,
        })?;

        offset = write_string(buf, offset, &self.name).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameError::BufferTooSmall,
            WireError::StringTooLong => TrenameError::NameTooLong,
            WireError::InvalidUtf8 => TrenameError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Trename message using p9_write
    pub fn send_trename(&self) -> Result<P9Response<RrenameMessage>, TrenameError> {
        get_backend().send_trename(self)
    }
}

/// Rrename message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RrenameMessage {
    /// Message tag
    pub tag: u16,
}

impl RrenameMessage {
    /// Create a new Rrename message
    pub fn new(tag: u16) -> Self {
        Self { tag }
    }

    /// Deserialize an Rrename message from a buffer
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RrenameError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RrenameError::BufferTooSmall);
        }

        let mut offset = 0;
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RrenameError::BufferTooSmall,
            WireError::StringTooLong => RrenameError::InternalError,
            WireError::InvalidUtf8 => RrenameError::InvalidUtf8,
        })?;
        offset = new_offset;

        if buf.len() < size as usize {
            return Err(RrenameError::BufferTooSmall);
        }

        if offset >= buf.len() {
            return Err(RrenameError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rrename as u8 {
            return Err(RrenameError::InvalidMessageType);
        }

        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RrenameError::BufferTooSmall,
            WireError::StringTooLong => RrenameError::InternalError,
            WireError::InvalidUtf8 => RrenameError::InvalidUtf8,
        })?;
        offset = new_offset;

        Ok((Self { tag }, offset))
    }
}

/// Treadlink message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TreadlinkMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
}

impl TreadlinkMessage {
    /// Create a new Treadlink message
    pub fn new(tag: u16, fid: u32) -> Self {
        Self { tag, fid }
    }

    /// Serialize the Treadlink message to a buffer
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TreadlinkError> {
        use wire::{WireError, write_u16, write_u32};

        let total_size = 4 + 1 + 2 + 4;

        if total_size > buf.len() {
            return Err(TreadlinkError::BufferTooSmall);
        }

        let mut offset = 0;
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TreadlinkError::BufferTooSmall,
            WireError::StringTooLong => TreadlinkError::InternalError,
            WireError::InvalidUtf8 => TreadlinkError::InvalidUtf8,
        })?;

        buf[offset] = P9MsgType::Treadlink as u8;
        offset += 1;

        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TreadlinkError::BufferTooSmall,
            WireError::StringTooLong => TreadlinkError::InternalError,
            WireError::InvalidUtf8 => TreadlinkError::InvalidUtf8,
        })?;

        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TreadlinkError::BufferTooSmall,
            WireError::StringTooLong => TreadlinkError::InternalError,
            WireError::InvalidUtf8 => TreadlinkError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Treadlink message using the active backend
    pub fn send_treadlink(&self) -> Result<P9Response<RreadlinkMessage>, TreadlinkError> {
        get_backend().send_treadlink(self)
    }
}

/// Rreadlink message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RreadlinkMessage {
    /// Message tag
    pub tag: u16,
    /// Symlink target
    pub target: String,
}

impl RreadlinkMessage {
    /// Create a new Rreadlink message
    pub fn new(tag: u16, target: String) -> Self {
        Self { tag, target }
    }

    /// Deserialize an Rreadlink message from a buffer
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RreadlinkError> {
        use wire::{WireError, read_string, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RreadlinkError::BufferTooSmall);
        }

        let mut offset = 0;
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RreadlinkError::BufferTooSmall,
            WireError::StringTooLong => RreadlinkError::InternalError,
            WireError::InvalidUtf8 => RreadlinkError::InvalidUtf8,
        })?;
        offset = new_offset;

        if buf.len() < size as usize {
            return Err(RreadlinkError::BufferTooSmall);
        }

        if offset >= buf.len() {
            return Err(RreadlinkError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rreadlink as u8 {
            return Err(RreadlinkError::InvalidMessageType);
        }

        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RreadlinkError::BufferTooSmall,
            WireError::StringTooLong => RreadlinkError::InternalError,
            WireError::InvalidUtf8 => RreadlinkError::InvalidUtf8,
        })?;
        offset = new_offset;

        let (target_str, new_offset) = read_string(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RreadlinkError::BufferTooSmall,
            WireError::StringTooLong => RreadlinkError::TargetTooLong,
            WireError::InvalidUtf8 => RreadlinkError::InvalidUtf8,
        })?;
        offset = new_offset;

        let target = target_str.to_string();

        Ok((Self { tag, target }, offset))
    }
}

// Error types for all the new message types
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TsymlinkError {
    BufferTooSmall,
    StringTooLong,
    InvalidUtf8,
    InternalError,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RsymlinkError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RsymlinkError {
    fn buffer_too_small() -> Self {
        RsymlinkError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RsymlinkError::InvalidMessageType
    }
}

impl ReadableMessage for RsymlinkMessage {
    type Error = RsymlinkError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RsymlinkMessage::deserialize(buf)
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TmknodError {
    BufferTooSmall,
    NameTooLong,
    InvalidUtf8,
    InternalError,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RmknodError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RmknodError {
    fn buffer_too_small() -> Self {
        RmknodError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RmknodError::InvalidMessageType
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TrenameError {
    BufferTooSmall,
    NameTooLong,
    InvalidUtf8,
    InternalError,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RrenameError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RrenameError {
    fn buffer_too_small() -> Self {
        RrenameError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RrenameError::InvalidMessageType
    }
}

impl ReadableMessage for RrenameMessage {
    type Error = RrenameError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        Self::deserialize(buf)
    }
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TreadlinkError {
    BufferTooSmall,
    InvalidUtf8,
    InternalError,
}

#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RreadlinkError {
    BufferTooSmall,
    InvalidMessageType,
    TargetTooLong,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RreadlinkError {
    fn buffer_too_small() -> Self {
        RreadlinkError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RreadlinkError::InvalidMessageType
    }
}

impl ReadableMessage for RreadlinkMessage {
    type Error = RreadlinkError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RreadlinkMessage::deserialize(buf)
    }
}

/// Tgetattr message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TgetattrMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Request mask for which attributes to get
    pub request_mask: u64,
}

impl TgetattrMessage {
    /// Create a new Tgetattr message
    pub fn new(tag: u16, fid: u32, request_mask: u64) -> Self {
        Self {
            tag,
            fid,
            request_mask,
        }
    }

    /// Serialize the Tgetattr message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TgetattrError> {
        use wire::{WireError, write_u16, write_u32, write_u64};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4 + 8; // size[4] + type[1] + tag[2] + fid[4] + request_mask[8]

        if total_size > buf.len() {
            return Err(TgetattrError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TgetattrError::BufferTooSmall,
            WireError::StringTooLong => TgetattrError::InternalError,
            WireError::InvalidUtf8 => TgetattrError::InvalidUtf8,
        })?;

        // Write message type[1] - Tgetattr
        buf[offset] = P9MsgType::Tgetattr as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TgetattrError::BufferTooSmall,
            WireError::StringTooLong => TgetattrError::InternalError,
            WireError::InvalidUtf8 => TgetattrError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TgetattrError::BufferTooSmall,
            WireError::StringTooLong => TgetattrError::InternalError,
            WireError::InvalidUtf8 => TgetattrError::InvalidUtf8,
        })?;

        // Write request_mask[8]
        offset = write_u64(buf, offset, self.request_mask).map_err(|e| match e {
            WireError::BufferTooSmall => TgetattrError::BufferTooSmall,
            WireError::StringTooLong => TgetattrError::InternalError,
            WireError::InvalidUtf8 => TgetattrError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tgetattr message using the active backend
    /// Returns the response from the backend
    pub fn send_tgetattr(&self) -> Result<P9Response<RgetattrMessage>, TgetattrError> {
        get_backend().send_tgetattr(self)
    }
}

/// Rgetattr message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RgetattrMessage {
    /// Message tag
    pub tag: u16,
    /// Valid mask indicating which attributes are valid
    pub valid: u64,
    /// QID of the file
    pub qid: Qid,
    /// File mode
    pub mode: u32,
    /// User ID
    pub uid: u32,
    /// Group ID
    pub gid: u32,
    /// Number of links
    pub nlink: u64,
    /// Device ID (for device files)
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
    /// Birth time (seconds)
    pub btime_sec: u64,
    /// Birth time (nanoseconds)
    pub btime_nsec: u64,
    /// Generation number
    pub gen_: u64,
    /// Data version
    pub data_version: u64,
}

impl RgetattrMessage {
    /// Create a new Rgetattr message
    #[allow(clippy::too_many_arguments)]
    pub fn new(
        tag: u16,
        valid: u64,
        qid: Qid,
        mode: u32,
        uid: u32,
        gid: u32,
        nlink: u64,
        rdev: u64,
        size: u64,
        blksize: u64,
        blocks: u64,
        atime_sec: u64,
        atime_nsec: u64,
        mtime_sec: u64,
        mtime_nsec: u64,
        ctime_sec: u64,
        ctime_nsec: u64,
        btime_sec: u64,
        btime_nsec: u64,
        gen_: u64,
        data_version: u64,
    ) -> Self {
        Self {
            tag,
            valid,
            qid,
            mode,
            uid,
            gid,
            nlink,
            rdev,
            size,
            blksize,
            blocks,
            atime_sec,
            atime_nsec,
            mtime_sec,
            mtime_nsec,
            ctime_sec,
            ctime_nsec,
            btime_sec,
            btime_nsec,
            gen_,
            data_version,
        }
    }

    /// Deserialize an Rgetattr message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RgetattrError> {
        use wire::{WireError, read_u16, read_u32, read_u64};

        if buf.len() < 4 {
            return Err(RgetattrError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RgetattrError::BufferTooSmall);
        }

        // Read message type[1] - should be Rgetattr
        if offset >= buf.len() {
            return Err(RgetattrError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rgetattr as u8 {
            return Err(RgetattrError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read valid[8]
        let (valid, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read qid[13] - type[1] version[4] path[8]
        if offset + 13 > buf.len() {
            return Err(RgetattrError::BufferTooSmall);
        }
        let qid = Qid {
            qtype: buf[offset],
            version: u32::from_le_bytes([
                buf[offset + 1],
                buf[offset + 2],
                buf[offset + 3],
                buf[offset + 4],
            ]),
            path: u64::from_le_bytes([
                buf[offset + 5],
                buf[offset + 6],
                buf[offset + 7],
                buf[offset + 8],
                buf[offset + 9],
                buf[offset + 10],
                buf[offset + 11],
                buf[offset + 12],
            ]),
        };
        offset += 13;

        // Read mode[4]
        let (mode, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read uid[4]
        let (uid, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read gid[4]
        let (gid, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read nlink[8]
        let (nlink, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read rdev[8]
        let (rdev, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read size[8]
        let (size, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read blksize[8]
        let (blksize, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read blocks[8]
        let (blocks, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read atime_sec[8]
        let (atime_sec, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read atime_nsec[8]
        let (atime_nsec, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read mtime_sec[8]
        let (mtime_sec, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read mtime_nsec[8]
        let (mtime_nsec, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read ctime_sec[8]
        let (ctime_sec, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read ctime_nsec[8]
        let (ctime_nsec, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read btime_sec[8]
        let (btime_sec, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read btime_nsec[8]
        let (btime_nsec, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read gen[8]
        let (gen_, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read data_version[8]
        let (data_version, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetattrError::BufferTooSmall,
            WireError::StringTooLong => RgetattrError::InternalError,
            WireError::InvalidUtf8 => RgetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        let message = Self {
            tag,
            valid,
            qid,
            mode,
            uid,
            gid,
            nlink,
            rdev,
            size,
            blksize,
            blocks,
            atime_sec,
            atime_nsec,
            mtime_sec,
            mtime_nsec,
            ctime_sec,
            ctime_nsec,
            btime_sec,
            btime_nsec,
            gen_,
            data_version,
        };

        Ok((message, offset))
    }
}

impl ReadableMessage for RgetattrMessage {
    type Error = RgetattrError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        Self::deserialize(buf)
    }
}

/// Tsetattr message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TsetattrMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Valid mask indicating which attributes to set
    pub valid: u32,
    /// File mode
    pub mode: u32,
    /// User ID
    pub uid: u32,
    /// Group ID
    pub gid: u32,
    /// File size
    pub size: u64,
    /// Access time (seconds)
    pub atime_sec: u64,
    /// Access time (nanoseconds)
    pub atime_nsec: u64,
    /// Modification time (seconds)
    pub mtime_sec: u64,
    /// Modification time (nanoseconds)
    pub mtime_nsec: u64,
}

impl TsetattrMessage {
    /// Create a new Tsetattr message
    #[allow(clippy::too_many_arguments)]
    pub fn new(
        tag: u16,
        fid: u32,
        valid: u32,
        mode: u32,
        uid: u32,
        gid: u32,
        size: u64,
        atime_sec: u64,
        atime_nsec: u64,
        mtime_sec: u64,
        mtime_nsec: u64,
    ) -> Self {
        Self {
            tag,
            fid,
            valid,
            mode,
            uid,
            gid,
            size,
            atime_sec,
            atime_nsec,
            mtime_sec,
            mtime_nsec,
        }
    }

    /// Serialize the Tsetattr message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TsetattrError> {
        use wire::{WireError, write_u16, write_u32, write_u64};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4 + 4 + 4 + 4 + 4 + 8 + 8 + 8 + 8 + 8; // size[4] + type[1] + tag[2] + fid[4] + valid[4] + mode[4] + uid[4] + gid[4] + size[8] + atime_sec[8] + atime_nsec[8] + mtime_sec[8] + mtime_nsec[8]

        if total_size > buf.len() {
            return Err(TsetattrError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write message type[1] - Tsetattr
        buf[offset] = P9MsgType::Tsetattr as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write valid[4]
        offset = write_u32(buf, offset, self.valid).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write mode[4]
        offset = write_u32(buf, offset, self.mode).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write uid[4]
        offset = write_u32(buf, offset, self.uid).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write gid[4]
        offset = write_u32(buf, offset, self.gid).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write size[8]
        offset = write_u64(buf, offset, self.size).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write atime_sec[8]
        offset = write_u64(buf, offset, self.atime_sec).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write atime_nsec[8]
        offset = write_u64(buf, offset, self.atime_nsec).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write mtime_sec[8]
        offset = write_u64(buf, offset, self.mtime_sec).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        // Write mtime_nsec[8]
        offset = write_u64(buf, offset, self.mtime_nsec).map_err(|e| match e {
            WireError::BufferTooSmall => TsetattrError::BufferTooSmall,
            WireError::StringTooLong => TsetattrError::InternalError,
            WireError::InvalidUtf8 => TsetattrError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tsetattr message using the active backend
    /// Returns the response from the backend
    pub fn send_tsetattr(&self) -> Result<P9Response<RsetattrMessage>, TsetattrError> {
        get_backend().send_tsetattr(self)
    }
}

/// Rsetattr message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RsetattrMessage {
    /// Message tag
    pub tag: u16,
}

impl RsetattrMessage {
    /// Create a new Rsetattr message
    pub fn new(tag: u16) -> Self {
        Self { tag }
    }

    /// Deserialize an Rsetattr message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RsetattrError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RsetattrError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RsetattrError::BufferTooSmall,
            WireError::StringTooLong => RsetattrError::InternalError,
            WireError::InvalidUtf8 => RsetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RsetattrError::BufferTooSmall);
        }

        // Read message type[1] - should be Rsetattr
        if offset >= buf.len() {
            return Err(RsetattrError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rsetattr as u8 {
            return Err(RsetattrError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RsetattrError::BufferTooSmall,
            WireError::StringTooLong => RsetattrError::InternalError,
            WireError::InvalidUtf8 => RsetattrError::InvalidUtf8,
        })?;
        offset = new_offset;

        Ok((Self { tag }, offset))
    }
}

/// Tgetattr serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TgetattrError {
    BufferTooSmall,
    InvalidUtf8,
    InternalError,
}

/// Rgetattr deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RgetattrError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RgetattrError {
    fn buffer_too_small() -> Self {
        RgetattrError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RgetattrError::InvalidMessageType
    }
}

/// Tsetattr serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TsetattrError {
    BufferTooSmall,
    InvalidUtf8,
    InternalError,
}

/// Rsetattr deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RsetattrError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RsetattrError {
    fn buffer_too_small() -> Self {
        RsetattrError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RsetattrError::InvalidMessageType
    }
}

impl ReadableMessage for RsetattrMessage {
    type Error = RsetattrError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RsetattrMessage::deserialize(buf)
    }
}

/// Txattrwalk message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TxattrwalkMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// New file identifier for the extended attribute
    pub newfid: u32,
    /// Name of the extended attribute
    pub name: String,
}

impl TxattrwalkMessage {
    /// Create a new Txattrwalk message
    pub fn new(tag: u16, fid: u32, newfid: u32, name: String) -> Self {
        Self {
            tag,
            fid,
            newfid,
            name,
        }
    }

    /// Serialize the Txattrwalk message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TxattrwalkError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        // Calculate total message size
        let name_len = self.name.len();
        let total_size = 4 + 1 + 2 + 4 + 4 + (2 + name_len); // size[4] + type[1] + tag[2] + fid[4] + newfid[4] + name[s]

        if total_size > buf.len() {
            return Err(TxattrwalkError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrwalkError::BufferTooSmall,
            WireError::StringTooLong => TxattrwalkError::NameTooLong,
            WireError::InvalidUtf8 => TxattrwalkError::InvalidUtf8,
        })?;

        // Write message type[1] - Txattrwalk
        buf[offset] = P9MsgType::Txattrwalk as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrwalkError::BufferTooSmall,
            WireError::StringTooLong => TxattrwalkError::NameTooLong,
            WireError::InvalidUtf8 => TxattrwalkError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrwalkError::BufferTooSmall,
            WireError::StringTooLong => TxattrwalkError::NameTooLong,
            WireError::InvalidUtf8 => TxattrwalkError::InvalidUtf8,
        })?;

        // Write newfid[4]
        offset = write_u32(buf, offset, self.newfid).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrwalkError::BufferTooSmall,
            WireError::StringTooLong => TxattrwalkError::NameTooLong,
            WireError::InvalidUtf8 => TxattrwalkError::InvalidUtf8,
        })?;

        // Write name[s]
        offset = write_string(buf, offset, &self.name).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrwalkError::BufferTooSmall,
            WireError::StringTooLong => TxattrwalkError::NameTooLong,
            WireError::InvalidUtf8 => TxattrwalkError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Txattrwalk message using the active backend
    pub fn send_txattrwalk(&self) -> Result<P9Response<RxattrwalkMessage>, TxattrwalkError> {
        get_backend().send_txattrwalk(self)
    }
}

/// Rxattrwalk message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RxattrwalkMessage {
    /// Message tag
    pub tag: u16,
    /// Size of the extended attribute
    pub size: u64,
}

impl RxattrwalkMessage {
    /// Create a new Rxattrwalk message
    pub fn new(tag: u16, size: u64) -> Self {
        Self { tag, size }
    }

    /// Deserialize an Rxattrwalk message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RxattrwalkError> {
        use wire::{WireError, read_u16, read_u32, read_u64};

        if buf.len() < 4 {
            return Err(RxattrwalkError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RxattrwalkError::BufferTooSmall,
            WireError::StringTooLong => RxattrwalkError::InternalError,
            WireError::InvalidUtf8 => RxattrwalkError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RxattrwalkError::BufferTooSmall);
        }

        // Read message type[1] - should be Rxattrwalk
        if offset >= buf.len() {
            return Err(RxattrwalkError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rxattrwalk as u8 {
            return Err(RxattrwalkError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RxattrwalkError::BufferTooSmall,
            WireError::StringTooLong => RxattrwalkError::InternalError,
            WireError::InvalidUtf8 => RxattrwalkError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read size[8]
        let (size, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RxattrwalkError::BufferTooSmall,
            WireError::StringTooLong => RxattrwalkError::InternalError,
            WireError::InvalidUtf8 => RxattrwalkError::InvalidUtf8,
        })?;
        offset = new_offset;

        Ok((Self { tag, size }, offset))
    }
}

impl MessageError for RxattrwalkError {
    fn buffer_too_small() -> Self {
        RxattrwalkError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RxattrwalkError::InvalidMessageType
    }
}

impl ReadableMessage for RxattrwalkMessage {
    type Error = RxattrwalkError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RxattrwalkMessage::deserialize(buf)
    }
}

/// Txattrcreate message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TxattrcreateMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Name of the extended attribute
    pub name: String,
    /// Size of the extended attribute
    pub attr_size: u64,
    /// Flags for the extended attribute
    pub flags: u32,
}

impl TxattrcreateMessage {
    /// Create a new Txattrcreate message
    pub fn new(tag: u16, fid: u32, name: String, attr_size: u64, flags: u32) -> Self {
        Self {
            tag,
            fid,
            name,
            attr_size,
            flags,
        }
    }

    /// Serialize the Txattrcreate message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TxattrcreateError> {
        use wire::{WireError, write_string, write_u16, write_u32, write_u64};

        // Calculate total message size
        let name_len = self.name.len();
        let total_size = 4 + 1 + 2 + 4 + (2 + name_len) + 8 + 4; // size[4] + type[1] + tag[2] + fid[4] + name[s] + attr_size[8] + flags[4]

        if total_size > buf.len() {
            return Err(TxattrcreateError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrcreateError::BufferTooSmall,
            WireError::StringTooLong => TxattrcreateError::NameTooLong,
            WireError::InvalidUtf8 => TxattrcreateError::InvalidUtf8,
        })?;

        // Write message type[1] - Txattrcreate
        buf[offset] = P9MsgType::Txattrcreate as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrcreateError::BufferTooSmall,
            WireError::StringTooLong => TxattrcreateError::NameTooLong,
            WireError::InvalidUtf8 => TxattrcreateError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrcreateError::BufferTooSmall,
            WireError::StringTooLong => TxattrcreateError::NameTooLong,
            WireError::InvalidUtf8 => TxattrcreateError::InvalidUtf8,
        })?;

        // Write name[s]
        offset = write_string(buf, offset, &self.name).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrcreateError::BufferTooSmall,
            WireError::StringTooLong => TxattrcreateError::NameTooLong,
            WireError::InvalidUtf8 => TxattrcreateError::InvalidUtf8,
        })?;

        // Write attr_size[8]
        offset = write_u64(buf, offset, self.attr_size).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrcreateError::BufferTooSmall,
            WireError::StringTooLong => TxattrcreateError::NameTooLong,
            WireError::InvalidUtf8 => TxattrcreateError::InvalidUtf8,
        })?;

        // Write flags[4]
        offset = write_u32(buf, offset, self.flags).map_err(|e| match e {
            WireError::BufferTooSmall => TxattrcreateError::BufferTooSmall,
            WireError::StringTooLong => TxattrcreateError::NameTooLong,
            WireError::InvalidUtf8 => TxattrcreateError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Txattrcreate message using the active backend
    pub fn send_txattrcreate(&self) -> Result<P9Response<RxattrcreateMessage>, TxattrcreateError> {
        get_backend().send_txattrcreate(self)
    }
}

/// Rxattrcreate message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RxattrcreateMessage {
    /// Message tag
    pub tag: u16,
}

impl RxattrcreateMessage {
    /// Create a new Rxattrcreate message
    pub fn new(tag: u16) -> Self {
        Self { tag }
    }

    /// Deserialize an Rxattrcreate message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RxattrcreateError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RxattrcreateError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RxattrcreateError::BufferTooSmall,
            WireError::StringTooLong => RxattrcreateError::InternalError,
            WireError::InvalidUtf8 => RxattrcreateError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RxattrcreateError::BufferTooSmall);
        }

        // Read message type[1] - should be Rxattrcreate
        if offset >= buf.len() {
            return Err(RxattrcreateError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rxattrcreate as u8 {
            return Err(RxattrcreateError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RxattrcreateError::BufferTooSmall,
            WireError::StringTooLong => RxattrcreateError::InternalError,
            WireError::InvalidUtf8 => RxattrcreateError::InvalidUtf8,
        })?;
        offset = new_offset;

        Ok((Self { tag }, offset))
    }
}

impl MessageError for RxattrcreateError {
    fn buffer_too_small() -> Self {
        RxattrcreateError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RxattrcreateError::InvalidMessageType
    }
}

impl ReadableMessage for RxattrcreateMessage {
    type Error = RxattrcreateError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RxattrcreateMessage::deserialize(buf)
    }
}

/// Treaddir message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TreaddirMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Offset in the directory
    pub offset: u64,
    /// Maximum number of bytes to read
    pub count: u32,
}

impl TreaddirMessage {
    /// Create a new Treaddir message
    pub fn new(tag: u16, fid: u32, offset: u64, count: u32) -> Self {
        Self {
            tag,
            fid,
            offset,
            count,
        }
    }

    /// Serialize the Treaddir message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TreaddirError> {
        use wire::{WireError, write_u16, write_u32, write_u64};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4 + 8 + 4; // size[4] + type[1] + tag[2] + fid[4] + offset[8] + count[4]

        if total_size > buf.len() {
            return Err(TreaddirError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TreaddirError::BufferTooSmall,
            WireError::StringTooLong => TreaddirError::InternalError,
            WireError::InvalidUtf8 => TreaddirError::InvalidUtf8,
        })?;

        // Write message type[1] - Treaddir
        buf[offset] = P9MsgType::Treaddir as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TreaddirError::BufferTooSmall,
            WireError::StringTooLong => TreaddirError::InternalError,
            WireError::InvalidUtf8 => TreaddirError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TreaddirError::BufferTooSmall,
            WireError::StringTooLong => TreaddirError::InternalError,
            WireError::InvalidUtf8 => TreaddirError::InvalidUtf8,
        })?;

        // Write offset[8]
        offset = write_u64(buf, offset, self.offset).map_err(|e| match e {
            WireError::BufferTooSmall => TreaddirError::BufferTooSmall,
            WireError::StringTooLong => TreaddirError::InternalError,
            WireError::InvalidUtf8 => TreaddirError::InvalidUtf8,
        })?;

        // Write count[4]
        offset = write_u32(buf, offset, self.count).map_err(|e| match e {
            WireError::BufferTooSmall => TreaddirError::BufferTooSmall,
            WireError::StringTooLong => TreaddirError::InternalError,
            WireError::InvalidUtf8 => TreaddirError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Treaddir message using the active backend
    /// Returns the response from the backend
    pub fn send_treaddir(&self) -> Result<P9Response<RreaddirMessage>, TreaddirError> {
        get_backend().send_treaddir(self)
    }
}

/// Rreaddir message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RreaddirMessage {
    /// Message tag
    pub tag: u16,
    /// Number of bytes returned in data
    pub count: u32,
    /// Directory entry data
    pub data: Vec<u8>,
}

impl RreaddirMessage {
    /// Create a new Rreaddir message
    pub fn new(tag: u16, count: u32, data: Vec<u8>) -> Self {
        Self { tag, count, data }
    }

    /// Deserialize an Rreaddir message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RreaddirError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RreaddirError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RreaddirError::BufferTooSmall,
            WireError::StringTooLong => RreaddirError::InternalError,
            WireError::InvalidUtf8 => RreaddirError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RreaddirError::BufferTooSmall);
        }

        // Read message type[1] - should be Rreaddir
        if offset >= buf.len() {
            return Err(RreaddirError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rreaddir as u8 {
            return Err(RreaddirError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RreaddirError::BufferTooSmall,
            WireError::StringTooLong => RreaddirError::InternalError,
            WireError::InvalidUtf8 => RreaddirError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read count[4]
        let (count, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RreaddirError::BufferTooSmall,
            WireError::StringTooLong => RreaddirError::InternalError,
            WireError::InvalidUtf8 => RreaddirError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read data[count]
        if offset + count as usize > buf.len() {
            return Err(RreaddirError::BufferTooSmall);
        }
        let data = buf[offset..offset + count as usize].to_vec();
        offset += count as usize;

        Ok((Self { tag, count, data }, offset))
    }
}

impl ReadableMessage for RreaddirMessage {
    type Error = RreaddirError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        Self::deserialize(buf)
    }
}

/// Txattrwalk serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TxattrwalkError {
    BufferTooSmall,
    NameTooLong,
    InvalidUtf8,
    InternalError,
}

/// Rxattrwalk deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RxattrwalkError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

/// Txattrcreate serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TxattrcreateError {
    BufferTooSmall,
    NameTooLong,
    InvalidUtf8,
    InternalError,
}

/// Rxattrcreate deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RxattrcreateError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

/// Treaddir serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TreaddirError {
    BufferTooSmall,
    InvalidUtf8,
    InternalError,
}

/// Rreaddir deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RreaddirError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RreaddirError {
    fn buffer_too_small() -> Self {
        RreaddirError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RreaddirError::InvalidMessageType
    }
}

/// Tfsync message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct TfsyncMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Data sync flag (0 = full sync, 1 = data sync only)
    pub datasync: u32,
}

impl TfsyncMessage {
    /// Create a new Tfsync message
    pub fn new(tag: u16, fid: u32, datasync: u32) -> Self {
        Self { tag, fid, datasync }
    }

    /// Serialize the Tfsync message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TfsyncError> {
        use wire::{WireError, write_u16, write_u32};

        // Calculate total message size
        let total_size = 4 + 1 + 2 + 4 + 4; // size[4] + type[1] + tag[2] + fid[4] + datasync[4]

        if total_size > buf.len() {
            return Err(TfsyncError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TfsyncError::BufferTooSmall,
            WireError::StringTooLong => TfsyncError::InternalError,
            WireError::InvalidUtf8 => TfsyncError::InvalidUtf8,
        })?;

        // Write message type[1] - Tfsync
        buf[offset] = P9MsgType::Tfsync as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TfsyncError::BufferTooSmall,
            WireError::StringTooLong => TfsyncError::InternalError,
            WireError::InvalidUtf8 => TfsyncError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TfsyncError::BufferTooSmall,
            WireError::StringTooLong => TfsyncError::InternalError,
            WireError::InvalidUtf8 => TfsyncError::InvalidUtf8,
        })?;

        // Write datasync[4]
        offset = write_u32(buf, offset, self.datasync).map_err(|e| match e {
            WireError::BufferTooSmall => TfsyncError::BufferTooSmall,
            WireError::StringTooLong => TfsyncError::InternalError,
            WireError::InvalidUtf8 => TfsyncError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tfsync message using the active backend
    pub fn send_tfsync(&self) -> Result<P9Response<RfsyncMessage>, TfsyncError> {
        get_backend().send_tfsync(self)
    }
}

/// Rfsync message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RfsyncMessage {
    /// Message tag
    pub tag: u16,
}

impl RfsyncMessage {
    /// Create a new Rfsync message
    pub fn new(tag: u16) -> Self {
        Self { tag }
    }

    /// Deserialize an Rfsync message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RfsyncError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RfsyncError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RfsyncError::BufferTooSmall,
            WireError::StringTooLong => RfsyncError::InternalError,
            WireError::InvalidUtf8 => RfsyncError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RfsyncError::BufferTooSmall);
        }

        // Read message type[1] - should be Rfsync
        if offset >= buf.len() {
            return Err(RfsyncError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rfsync as u8 {
            return Err(RfsyncError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RfsyncError::BufferTooSmall,
            WireError::StringTooLong => RfsyncError::InternalError,
            WireError::InvalidUtf8 => RfsyncError::InvalidUtf8,
        })?;
        offset = new_offset;

        Ok((Self { tag }, offset))
    }
}

/// Tlock message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TlockMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Lock type
    pub type_: u8,
    /// Lock flags
    pub flags: u32,
    /// Start offset
    pub start: u64,
    /// Length of the lock
    pub length: u64,
    /// Process ID
    pub proc_id: u32,
    /// Client ID
    pub client_id: String,
}

impl TlockMessage {
    /// Create a new Tlock message
    pub fn new(
        tag: u16,
        fid: u32,
        type_: u8,
        flags: u32,
        start: u64,
        length: u64,
        proc_id: u32,
        client_id: String,
    ) -> Self {
        Self {
            tag,
            fid,
            type_,
            flags,
            start,
            length,
            proc_id,
            client_id,
        }
    }

    /// Serialize the Tlock message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TlockError> {
        use wire::{WireError, write_string, write_u16, write_u32, write_u64};

        // Calculate total message size
        let client_id_len = self.client_id.len();
        let total_size = 4 + 1 + 2 + 4 + 1 + 4 + 8 + 8 + 4 + (2 + client_id_len); // size[4] + type[1] + tag[2] + fid[4] + type[1] + flags[4] + start[8] + length[8] + proc_id[4] + client_id[s]

        if total_size > buf.len() {
            return Err(TlockError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TlockError::BufferTooSmall,
            WireError::StringTooLong => TlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TlockError::InvalidUtf8,
        })?;

        // Write message type[1] - Tlock
        buf[offset] = P9MsgType::Tlock as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TlockError::BufferTooSmall,
            WireError::StringTooLong => TlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TlockError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TlockError::BufferTooSmall,
            WireError::StringTooLong => TlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TlockError::InvalidUtf8,
        })?;

        // Write type[1]
        buf[offset] = self.type_;
        offset += 1;

        // Write flags[4]
        offset = write_u32(buf, offset, self.flags).map_err(|e| match e {
            WireError::BufferTooSmall => TlockError::BufferTooSmall,
            WireError::StringTooLong => TlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TlockError::InvalidUtf8,
        })?;

        // Write start[8]
        offset = write_u64(buf, offset, self.start).map_err(|e| match e {
            WireError::BufferTooSmall => TlockError::BufferTooSmall,
            WireError::StringTooLong => TlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TlockError::InvalidUtf8,
        })?;

        // Write length[8]
        offset = write_u64(buf, offset, self.length).map_err(|e| match e {
            WireError::BufferTooSmall => TlockError::BufferTooSmall,
            WireError::StringTooLong => TlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TlockError::InvalidUtf8,
        })?;

        // Write proc_id[4]
        offset = write_u32(buf, offset, self.proc_id).map_err(|e| match e {
            WireError::BufferTooSmall => TlockError::BufferTooSmall,
            WireError::StringTooLong => TlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TlockError::InvalidUtf8,
        })?;

        // Write client_id[s]
        offset = write_string(buf, offset, &self.client_id).map_err(|e| match e {
            WireError::BufferTooSmall => TlockError::BufferTooSmall,
            WireError::StringTooLong => TlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TlockError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tlock message using the active backend
    pub fn send_tlock(&self) -> Result<P9Response<RlockMessage>, TlockError> {
        get_backend().send_tlock(self)
    }
}

/// Rlock message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RlockMessage {
    /// Message tag
    pub tag: u16,
    /// Lock status
    pub status: u8,
}

impl RlockMessage {
    /// Create a new Rlock message
    pub fn new(tag: u16, status: u8) -> Self {
        Self { tag, status }
    }

    /// Deserialize an Rlock message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RlockError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RlockError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlockError::BufferTooSmall,
            WireError::StringTooLong => RlockError::InternalError,
            WireError::InvalidUtf8 => RlockError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RlockError::BufferTooSmall);
        }

        // Read message type[1] - should be Rlock
        if offset >= buf.len() {
            return Err(RlockError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rlock as u8 {
            return Err(RlockError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlockError::BufferTooSmall,
            WireError::StringTooLong => RlockError::InternalError,
            WireError::InvalidUtf8 => RlockError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read status[1]
        if offset >= buf.len() {
            return Err(RlockError::BufferTooSmall);
        }
        let status = buf[offset];
        offset += 1;

        Ok((Self { tag, status }, offset))
    }
}

/// Tgetlock message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TgetlockMessage {
    /// Message tag
    pub tag: u16,
    /// File identifier
    pub fid: u32,
    /// Lock type
    pub type_: u8,
    /// Start offset
    pub start: u64,
    /// Length of the lock
    pub length: u64,
    /// Process ID
    pub proc_id: u32,
    /// Client ID
    pub client_id: String,
}

impl TgetlockMessage {
    /// Create a new Tgetlock message
    pub fn new(
        tag: u16,
        fid: u32,
        type_: u8,
        start: u64,
        length: u64,
        proc_id: u32,
        client_id: String,
    ) -> Self {
        Self {
            tag,
            fid,
            type_,
            start,
            length,
            proc_id,
            client_id,
        }
    }

    /// Serialize the Tgetlock message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TgetlockError> {
        use wire::{WireError, write_string, write_u16, write_u32, write_u64};

        // Calculate total message size
        let client_id_len = self.client_id.len();
        let total_size = 4 + 1 + 2 + 4 + 1 + 8 + 8 + 4 + (2 + client_id_len); // size[4] + type[1] + tag[2] + fid[4] + type[1] + start[8] + length[8] + proc_id[4] + client_id[s]

        if total_size > buf.len() {
            return Err(TgetlockError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TgetlockError::BufferTooSmall,
            WireError::StringTooLong => TgetlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TgetlockError::InvalidUtf8,
        })?;

        // Write message type[1] - Tgetlock
        buf[offset] = P9MsgType::Tgetlock as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TgetlockError::BufferTooSmall,
            WireError::StringTooLong => TgetlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TgetlockError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TgetlockError::BufferTooSmall,
            WireError::StringTooLong => TgetlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TgetlockError::InvalidUtf8,
        })?;

        // Write type[1]
        buf[offset] = self.type_;
        offset += 1;

        // Write start[8]
        offset = write_u64(buf, offset, self.start).map_err(|e| match e {
            WireError::BufferTooSmall => TgetlockError::BufferTooSmall,
            WireError::StringTooLong => TgetlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TgetlockError::InvalidUtf8,
        })?;

        // Write length[8]
        offset = write_u64(buf, offset, self.length).map_err(|e| match e {
            WireError::BufferTooSmall => TgetlockError::BufferTooSmall,
            WireError::StringTooLong => TgetlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TgetlockError::InvalidUtf8,
        })?;

        // Write proc_id[4]
        offset = write_u32(buf, offset, self.proc_id).map_err(|e| match e {
            WireError::BufferTooSmall => TgetlockError::BufferTooSmall,
            WireError::StringTooLong => TgetlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TgetlockError::InvalidUtf8,
        })?;

        // Write client_id[s]
        offset = write_string(buf, offset, &self.client_id).map_err(|e| match e {
            WireError::BufferTooSmall => TgetlockError::BufferTooSmall,
            WireError::StringTooLong => TgetlockError::ClientIdTooLong,
            WireError::InvalidUtf8 => TgetlockError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tgetlock message using the active backend
    pub fn send_tgetlock(&self) -> Result<P9Response<RgetlockMessage>, TgetlockError> {
        get_backend().send_tgetlock(self)
    }
}

/// Rgetlock message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RgetlockMessage {
    /// Message tag
    pub tag: u16,
    /// Lock type
    pub type_: u8,
    /// Start offset
    pub start: u64,
    /// Length of the lock
    pub length: u64,
    /// Process ID
    pub proc_id: u32,
    /// Client ID
    pub client_id: String,
}

impl RgetlockMessage {
    /// Create a new Rgetlock message
    pub fn new(
        tag: u16,
        type_: u8,
        start: u64,
        length: u64,
        proc_id: u32,
        client_id: String,
    ) -> Self {
        Self {
            tag,
            type_,
            start,
            length,
            proc_id,
            client_id,
        }
    }

    /// Deserialize an Rgetlock message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RgetlockError> {
        use wire::{WireError, read_string, read_u16, read_u32, read_u64};

        if buf.len() < 4 {
            return Err(RgetlockError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetlockError::BufferTooSmall,
            WireError::StringTooLong => RgetlockError::InternalError,
            WireError::InvalidUtf8 => RgetlockError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RgetlockError::BufferTooSmall);
        }

        // Read message type[1] - should be Rgetlock
        if offset >= buf.len() {
            return Err(RgetlockError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rgetlock as u8 {
            return Err(RgetlockError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetlockError::BufferTooSmall,
            WireError::StringTooLong => RgetlockError::InternalError,
            WireError::InvalidUtf8 => RgetlockError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read type[1]
        if offset >= buf.len() {
            return Err(RgetlockError::BufferTooSmall);
        }
        let type_ = buf[offset];
        offset += 1;

        // Read start[8]
        let (start, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetlockError::BufferTooSmall,
            WireError::StringTooLong => RgetlockError::InternalError,
            WireError::InvalidUtf8 => RgetlockError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read length[8]
        let (length, new_offset) = read_u64(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetlockError::BufferTooSmall,
            WireError::StringTooLong => RgetlockError::InternalError,
            WireError::InvalidUtf8 => RgetlockError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read proc_id[4]
        let (proc_id, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetlockError::BufferTooSmall,
            WireError::StringTooLong => RgetlockError::InternalError,
            WireError::InvalidUtf8 => RgetlockError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read client_id[s]
        let (client_id, new_offset) = read_string(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RgetlockError::BufferTooSmall,
            WireError::StringTooLong => RgetlockError::InternalError,
            WireError::InvalidUtf8 => RgetlockError::InvalidUtf8,
        })?;
        offset = new_offset;

        Ok((
            Self {
                tag,
                type_,
                start,
                length,
                proc_id,
                client_id: client_id.to_string(),
            },
            offset,
        ))
    }
}

/// Tlink message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TlinkMessage {
    /// Message tag
    pub tag: u16,
    /// Directory file identifier
    pub dfid: u32,
    /// File identifier
    pub fid: u32,
    /// Name of the link
    pub name: String,
}

impl TlinkMessage {
    /// Create a new Tlink message
    pub fn new(tag: u16, dfid: u32, fid: u32, name: String) -> Self {
        Self {
            tag,
            dfid,
            fid,
            name,
        }
    }

    /// Serialize the Tlink message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TlinkError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        // Calculate total message size
        let name_len = self.name.len();
        let total_size = 4 + 1 + 2 + 4 + 4 + (2 + name_len); // size[4] + type[1] + tag[2] + dfid[4] + fid[4] + name[s]

        if total_size > buf.len() {
            return Err(TlinkError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TlinkError::BufferTooSmall,
            WireError::StringTooLong => TlinkError::NameTooLong,
            WireError::InvalidUtf8 => TlinkError::InvalidUtf8,
        })?;

        // Write message type[1] - Tlink
        buf[offset] = P9MsgType::Tlink as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TlinkError::BufferTooSmall,
            WireError::StringTooLong => TlinkError::NameTooLong,
            WireError::InvalidUtf8 => TlinkError::InvalidUtf8,
        })?;

        // Write dfid[4]
        offset = write_u32(buf, offset, self.dfid).map_err(|e| match e {
            WireError::BufferTooSmall => TlinkError::BufferTooSmall,
            WireError::StringTooLong => TlinkError::NameTooLong,
            WireError::InvalidUtf8 => TlinkError::InvalidUtf8,
        })?;

        // Write fid[4]
        offset = write_u32(buf, offset, self.fid).map_err(|e| match e {
            WireError::BufferTooSmall => TlinkError::BufferTooSmall,
            WireError::StringTooLong => TlinkError::NameTooLong,
            WireError::InvalidUtf8 => TlinkError::InvalidUtf8,
        })?;

        // Write name[s]
        offset = write_string(buf, offset, &self.name).map_err(|e| match e {
            WireError::BufferTooSmall => TlinkError::BufferTooSmall,
            WireError::StringTooLong => TlinkError::NameTooLong,
            WireError::InvalidUtf8 => TlinkError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tlink message using p9_write
    /// Returns the number of bytes written, or an error
    pub fn send_tlink(&self) -> Result<P9Response<RlinkMessage>, TlinkError> {
        get_backend().send_tlink(self)
    }
}

/// Rlink message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RlinkMessage {
    /// Message tag
    pub tag: u16,
}

impl RlinkMessage {
    /// Create a new Rlink message
    pub fn new(tag: u16) -> Self {
        Self { tag }
    }

    /// Deserialize an Rlink message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RlinkError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RlinkError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlinkError::BufferTooSmall,
            WireError::StringTooLong => RlinkError::InternalError,
            WireError::InvalidUtf8 => RlinkError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RlinkError::BufferTooSmall);
        }

        // Read message type[1] - should be Rlink
        if offset >= buf.len() {
            return Err(RlinkError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rlink as u8 {
            return Err(RlinkError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RlinkError::BufferTooSmall,
            WireError::StringTooLong => RlinkError::InternalError,
            WireError::InvalidUtf8 => RlinkError::InvalidUtf8,
        })?;
        offset = new_offset;

        Ok((Self { tag }, offset))
    }
}

impl MessageError for RlinkError {
    fn buffer_too_small() -> Self {
        RlinkError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RlinkError::InvalidMessageType
    }
}

impl ReadableMessage for RlinkMessage {
    type Error = RlinkError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RlinkMessage::deserialize(buf)
    }
}

/// Tfsync serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TfsyncError {
    BufferTooSmall,
    InvalidUtf8,
    InternalError,
}

/// Rfsync deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RfsyncError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

/// Tlock serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TlockError {
    BufferTooSmall,
    ClientIdTooLong,
    InvalidUtf8,
    InternalError,
}

/// Rlock deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RlockError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

/// Tgetlock serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TgetlockError {
    BufferTooSmall,
    ClientIdTooLong,
    InvalidUtf8,
    InternalError,
}

/// Rgetlock deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RgetlockError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

/// Tlink serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TlinkError {
    BufferTooSmall,
    NameTooLong,
    InvalidUtf8,
    InternalError,
}

/// Rlink deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RlinkError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

/// Tmkdir message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TmkdirMessage {
    /// Message tag
    pub tag: u16,
    /// Directory file identifier
    pub dfid: u32,
    /// Name of the directory
    pub name: String,
    /// Directory mode
    pub mode: u32,
    /// Group ID
    pub gid: u32,
}

impl TmkdirMessage {
    /// Create a new Tmkdir message
    pub fn new(tag: u16, dfid: u32, name: String, mode: u32, gid: u32) -> Self {
        Self {
            tag,
            dfid,
            name,
            mode,
            gid,
        }
    }

    /// Serialize the Tmkdir message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TmkdirError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        // Calculate total message size
        let name_len = self.name.len();
        let total_size = 4 + 1 + 2 + 4 + (2 + name_len) + 4 + 4; // size[4] + type[1] + tag[2] + dfid[4] + name[s] + mode[4] + gid[4]

        if total_size > buf.len() {
            return Err(TmkdirError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TmkdirError::BufferTooSmall,
            WireError::StringTooLong => TmkdirError::NameTooLong,
            WireError::InvalidUtf8 => TmkdirError::InvalidUtf8,
        })?;

        // Write message type[1] - Tmkdir
        buf[offset] = P9MsgType::Tmkdir as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TmkdirError::BufferTooSmall,
            WireError::StringTooLong => TmkdirError::NameTooLong,
            WireError::InvalidUtf8 => TmkdirError::InvalidUtf8,
        })?;

        // Write dfid[4]
        offset = write_u32(buf, offset, self.dfid).map_err(|e| match e {
            WireError::BufferTooSmall => TmkdirError::BufferTooSmall,
            WireError::StringTooLong => TmkdirError::NameTooLong,
            WireError::InvalidUtf8 => TmkdirError::InvalidUtf8,
        })?;

        // Write name[s]
        offset = write_string(buf, offset, &self.name).map_err(|e| match e {
            WireError::BufferTooSmall => TmkdirError::BufferTooSmall,
            WireError::StringTooLong => TmkdirError::NameTooLong,
            WireError::InvalidUtf8 => TmkdirError::InvalidUtf8,
        })?;

        // Write mode[4]
        offset = write_u32(buf, offset, self.mode).map_err(|e| match e {
            WireError::BufferTooSmall => TmkdirError::BufferTooSmall,
            WireError::StringTooLong => TmkdirError::NameTooLong,
            WireError::InvalidUtf8 => TmkdirError::InvalidUtf8,
        })?;

        // Write gid[4]
        offset = write_u32(buf, offset, self.gid).map_err(|e| match e {
            WireError::BufferTooSmall => TmkdirError::BufferTooSmall,
            WireError::StringTooLong => TmkdirError::NameTooLong,
            WireError::InvalidUtf8 => TmkdirError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tmkdir message using the active backend
    /// Returns the response from the backend
    pub fn send_tmkdir(&self) -> Result<P9Response<RmkdirMessage>, TmkdirError> {
        get_backend().send_tmkdir(self)
    }
}

/// Rmkdir message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct RmkdirMessage {
    /// Message tag
    pub tag: u16,
    /// QID of the created directory
    pub qid: Qid,
}

impl RmkdirMessage {
    /// Create a new Rmkdir message
    pub fn new(tag: u16, qid: Qid) -> Self {
        Self { tag, qid }
    }

    /// Deserialize an Rmkdir message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RmkdirError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RmkdirError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RmkdirError::BufferTooSmall,
            WireError::StringTooLong => RmkdirError::InternalError,
            WireError::InvalidUtf8 => RmkdirError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RmkdirError::BufferTooSmall);
        }

        // Read message type[1] - should be Rmkdir
        if offset >= buf.len() {
            return Err(RmkdirError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rmkdir as u8 {
            return Err(RmkdirError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RmkdirError::BufferTooSmall,
            WireError::StringTooLong => RmkdirError::InternalError,
            WireError::InvalidUtf8 => RmkdirError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Read qid[13]
        if offset + 13 > buf.len() {
            return Err(RmkdirError::BufferTooSmall);
        }

        let qid = Qid {
            qtype: buf[offset],
            version: u32::from_le_bytes([
                buf[offset + 1],
                buf[offset + 2],
                buf[offset + 3],
                buf[offset + 4],
            ]),
            path: u64::from_le_bytes([
                buf[offset + 5],
                buf[offset + 6],
                buf[offset + 7],
                buf[offset + 8],
                buf[offset + 9],
                buf[offset + 10],
                buf[offset + 11],
                buf[offset + 12],
            ]),
        };
        offset += 13;

        Ok((Self { tag, qid }, offset))
    }
}

impl ReadableMessage for RmkdirMessage {
    type Error = RmkdirError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RmkdirMessage::deserialize(buf)
    }
}

/// Trenameat message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TrenameatMessage {
    /// Message tag
    pub tag: u16,
    /// Old directory file identifier
    pub olddirfid: u32,
    /// Old name
    pub oldname: String,
    /// New directory file identifier
    pub newdirfid: u32,
    /// New name
    pub newname: String,
}

impl TrenameatMessage {
    /// Create a new Trenameat message
    pub fn new(tag: u16, olddirfid: u32, oldname: String, newdirfid: u32, newname: String) -> Self {
        Self {
            tag,
            olddirfid,
            oldname,
            newdirfid,
            newname,
        }
    }

    /// Serialize the Trenameat message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TrenameatError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        // Calculate total message size
        let oldname_len = self.oldname.len();
        let newname_len = self.newname.len();
        let total_size = 4 + 1 + 2 + 4 + (2 + oldname_len) + 4 + (2 + newname_len); // size[4] + type[1] + tag[2] + olddirfid[4] + oldname[s] + newdirfid[4] + newname[s]

        if total_size > buf.len() {
            return Err(TrenameatError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameatError::BufferTooSmall,
            WireError::StringTooLong => TrenameatError::NameTooLong,
            WireError::InvalidUtf8 => TrenameatError::InvalidUtf8,
        })?;

        // Write message type[1] - Trenameat
        buf[offset] = P9MsgType::Trenameat as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameatError::BufferTooSmall,
            WireError::StringTooLong => TrenameatError::NameTooLong,
            WireError::InvalidUtf8 => TrenameatError::InvalidUtf8,
        })?;

        // Write olddirfid[4]
        offset = write_u32(buf, offset, self.olddirfid).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameatError::BufferTooSmall,
            WireError::StringTooLong => TrenameatError::NameTooLong,
            WireError::InvalidUtf8 => TrenameatError::InvalidUtf8,
        })?;

        // Write oldname[s]
        offset = write_string(buf, offset, &self.oldname).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameatError::BufferTooSmall,
            WireError::StringTooLong => TrenameatError::NameTooLong,
            WireError::InvalidUtf8 => TrenameatError::InvalidUtf8,
        })?;

        // Write newdirfid[4]
        offset = write_u32(buf, offset, self.newdirfid).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameatError::BufferTooSmall,
            WireError::StringTooLong => TrenameatError::NameTooLong,
            WireError::InvalidUtf8 => TrenameatError::InvalidUtf8,
        })?;

        // Write newname[s]
        offset = write_string(buf, offset, &self.newname).map_err(|e| match e {
            WireError::BufferTooSmall => TrenameatError::BufferTooSmall,
            WireError::StringTooLong => TrenameatError::NameTooLong,
            WireError::InvalidUtf8 => TrenameatError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Trenameat message using the active backend
    pub fn send_trenameat(&self) -> Result<P9Response<RrenameatMessage>, TrenameatError> {
        get_backend().send_trenameat(self)
    }
}

/// Rrenameat message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RrenameatMessage {
    /// Message tag
    pub tag: u16,
}

impl RrenameatMessage {
    /// Create a new Rrenameat message
    pub fn new(tag: u16) -> Self {
        Self { tag }
    }

    /// Deserialize an Rrenameat message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RrenameatError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RrenameatError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RrenameatError::BufferTooSmall,
            WireError::StringTooLong => RrenameatError::InternalError,
            WireError::InvalidUtf8 => RrenameatError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RrenameatError::BufferTooSmall);
        }

        // Read message type[1] - should be Rrenameat
        if offset >= buf.len() {
            return Err(RrenameatError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Rrenameat as u8 {
            return Err(RrenameatError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RrenameatError::BufferTooSmall,
            WireError::StringTooLong => RrenameatError::InternalError,
            WireError::InvalidUtf8 => RrenameatError::InvalidUtf8,
        })?;
        offset = new_offset;

        Ok((Self { tag }, offset))
    }
}

impl ReadableMessage for RrenameatMessage {
    type Error = RrenameatError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RrenameatMessage::deserialize(buf)
    }
}

/// Tunlinkat message structure
#[derive(Debug, Clone, PartialEq, Eq)]
pub struct TunlinkatMessage {
    /// Message tag
    pub tag: u16,
    /// Directory file descriptor
    pub dirfd: u32,
    /// Name to unlink
    pub name: String,
    /// Unlink flags
    pub flags: u32,
}

impl TunlinkatMessage {
    /// Create a new Tunlinkat message
    pub fn new(tag: u16, dirfd: u32, name: String, flags: u32) -> Self {
        Self {
            tag,
            dirfd,
            name,
            flags,
        }
    }

    /// Serialize the Tunlinkat message to a buffer
    /// Returns the number of bytes written
    pub fn serialize(&self, buf: &mut [u8]) -> Result<usize, TunlinkatError> {
        use wire::{WireError, write_string, write_u16, write_u32};

        // Calculate total message size
        let name_len = self.name.len();
        let total_size = 4 + 1 + 2 + 4 + (2 + name_len) + 4; // size[4] + type[1] + tag[2] + dirfd[4] + name[s] + flags[4]

        if total_size > buf.len() {
            return Err(TunlinkatError::BufferTooSmall);
        }

        let mut offset = 0;

        // Write size[4] - total message size including the size field itself
        offset = write_u32(buf, offset, total_size as u32).map_err(|e| match e {
            WireError::BufferTooSmall => TunlinkatError::BufferTooSmall,
            WireError::StringTooLong => TunlinkatError::NameTooLong,
            WireError::InvalidUtf8 => TunlinkatError::InvalidUtf8,
        })?;

        // Write message type[1] - Tunlinkat
        buf[offset] = P9MsgType::Tunlinkat as u8;
        offset += 1;

        // Write tag[2]
        offset = write_u16(buf, offset, self.tag).map_err(|e| match e {
            WireError::BufferTooSmall => TunlinkatError::BufferTooSmall,
            WireError::StringTooLong => TunlinkatError::NameTooLong,
            WireError::InvalidUtf8 => TunlinkatError::InvalidUtf8,
        })?;

        // Write dirfd[4]
        offset = write_u32(buf, offset, self.dirfd).map_err(|e| match e {
            WireError::BufferTooSmall => TunlinkatError::BufferTooSmall,
            WireError::StringTooLong => TunlinkatError::NameTooLong,
            WireError::InvalidUtf8 => TunlinkatError::InvalidUtf8,
        })?;

        // Write name[s]
        offset = write_string(buf, offset, &self.name).map_err(|e| match e {
            WireError::BufferTooSmall => TunlinkatError::BufferTooSmall,
            WireError::StringTooLong => TunlinkatError::NameTooLong,
            WireError::InvalidUtf8 => TunlinkatError::InvalidUtf8,
        })?;

        // Write flags[4]
        offset = write_u32(buf, offset, self.flags).map_err(|e| match e {
            WireError::BufferTooSmall => TunlinkatError::BufferTooSmall,
            WireError::StringTooLong => TunlinkatError::NameTooLong,
            WireError::InvalidUtf8 => TunlinkatError::InvalidUtf8,
        })?;

        Ok(offset)
    }

    /// Send the Tunlinkat message using the active backend
    pub fn send_tunlinkat(&self) -> Result<P9Response<RunlinkatMessage>, TunlinkatError> {
        get_backend().send_tunlinkat(self)
    }
}

/// Runlinkat message structure
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct RunlinkatMessage {
    /// Message tag
    pub tag: u16,
}

impl RunlinkatMessage {
    /// Create a new Runlinkat message
    pub fn new(tag: u16) -> Self {
        Self { tag }
    }

    /// Deserialize an Runlinkat message from a buffer
    /// Returns the number of bytes consumed
    pub fn deserialize(buf: &[u8]) -> Result<(Self, usize), RunlinkatError> {
        use wire::{WireError, read_u16, read_u32};

        if buf.len() < 4 {
            return Err(RunlinkatError::BufferTooSmall);
        }

        let mut offset = 0;

        // Read size[4] - total message size
        let (size, new_offset) = read_u32(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RunlinkatError::BufferTooSmall,
            WireError::StringTooLong => RunlinkatError::InternalError,
            WireError::InvalidUtf8 => RunlinkatError::InvalidUtf8,
        })?;
        offset = new_offset;

        // Verify we have enough data
        if buf.len() < size as usize {
            return Err(RunlinkatError::BufferTooSmall);
        }

        // Read message type[1] - should be Runlinkat
        if offset >= buf.len() {
            return Err(RunlinkatError::BufferTooSmall);
        }
        let msg_type = buf[offset];
        offset += 1;

        if msg_type != P9MsgType::Runlinkat as u8 {
            return Err(RunlinkatError::InvalidMessageType);
        }

        // Read tag[2]
        let (tag, new_offset) = read_u16(buf, offset).map_err(|e| match e {
            WireError::BufferTooSmall => RunlinkatError::BufferTooSmall,
            WireError::StringTooLong => RunlinkatError::InternalError,
            WireError::InvalidUtf8 => RunlinkatError::InvalidUtf8,
        })?;
        offset = new_offset;

        Ok((Self { tag }, offset))
    }
}

/// Tmkdir serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TmkdirError {
    BufferTooSmall,
    NameTooLong,
    InvalidUtf8,
    InternalError,
}

/// Rmkdir deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RmkdirError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RmkdirError {
    fn buffer_too_small() -> Self {
        RmkdirError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RmkdirError::InvalidMessageType
    }
}

/// Trenameat serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TrenameatError {
    BufferTooSmall,
    NameTooLong,
    InvalidUtf8,
    InternalError,
}

/// Rrenameat deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RrenameatError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RrenameatError {
    fn buffer_too_small() -> Self {
        RrenameatError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RrenameatError::InvalidMessageType
    }
}

/// Tunlinkat serialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum TunlinkatError {
    BufferTooSmall,
    NameTooLong,
    InvalidUtf8,
    InternalError,
}

/// Runlinkat deserialization errors
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub enum RunlinkatError {
    BufferTooSmall,
    InvalidMessageType,
    InvalidUtf8,
    InternalError,
}

impl MessageError for RunlinkatError {
    fn buffer_too_small() -> Self {
        RunlinkatError::BufferTooSmall
    }

    fn invalid_message_type() -> Self {
        RunlinkatError::InvalidMessageType
    }
}

impl ReadableMessage for RunlinkatMessage {
    type Error = RunlinkatError;

    fn deserialize(buf: &[u8]) -> Result<(Self, usize), Self::Error> {
        RunlinkatMessage::deserialize(buf)
    }
}

/// 9P2000.L file attributes structure
///
/// This structure closely follows the Linux stat structure but with some differences:
/// - st_dev is omitted
/// - st_ino is contained in the path component of qid
/// - times are nanosecond resolution
/// - btime, gen and data_version fields are reserved for future use
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct P9Stat {
    /// QID of the file
    pub qid: Qid,
    /// File mode and permissions
    pub mode: u32,
    /// User ID of owner
    pub uid: u32,
    /// Group ID of owner
    pub gid: u32,
    /// Number of hard links
    pub nlink: u64,
    /// Device ID (if special file)
    pub rdev: u64,
    /// Total size in bytes
    pub size: u64,
    /// Block size for file system I/O
    pub blksize: u64,
    /// Number of 512B blocks allocated
    pub blocks: u64,
    /// Time of last access (seconds)
    pub atime_sec: u64,
    /// Time of last access (nanoseconds)
    pub atime_nsec: u64,
    /// Time of last modification (seconds)
    pub mtime_sec: u64,
    /// Time of last modification (nanoseconds)
    pub mtime_nsec: u64,
    /// Time of last status change (seconds)
    pub ctime_sec: u64,
    /// Time of last status change (nanoseconds)
    pub ctime_nsec: u64,
    /// Birth time (seconds) - reserved for future use
    pub btime_sec: u64,
    /// Birth time (nanoseconds) - reserved for future use
    pub btime_nsec: u64,
    /// Generation number - reserved for future use
    pub generation: u64,
    /// Data version - reserved for future use
    pub data_version: u64,
}

impl P9Stat {
    /// Create a new P9Stat with default values
    pub fn new() -> Self {
        Self {
            qid: Qid::new(0, 0, 0),
            mode: 0,
            uid: 0,
            gid: 0,
            nlink: 0,
            rdev: 0,
            size: 0,
            blksize: 0,
            blocks: 0,
            atime_sec: 0,
            atime_nsec: 0,
            mtime_sec: 0,
            mtime_nsec: 0,
            ctime_sec: 0,
            ctime_nsec: 0,
            btime_sec: 0,
            btime_nsec: 0,
            generation: 0,
            data_version: 0,
        }
    }

    /// Check if this represents a directory
    pub fn is_dir(&self) -> bool {
        self.qid.is_dir()
    }

    /// Check if this represents a regular file
    pub fn is_file(&self) -> bool {
        self.qid.is_file()
    }

    /// Check if this represents a symlink
    pub fn is_symlink(&self) -> bool {
        self.qid.is_symlink()
    }
}

impl Default for P9Stat {
    fn default() -> Self {
        Self::new()
    }
}

/// 9P2000.L directory entry
///
/// Directory entries are represented as variable-length records:
/// qid[13] offset[8] type[1] name[s]
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct P9DirEntry {
    /// QID of the entry
    pub qid: Qid,
    /// Offset for next readdir call
    pub offset: u64,
    /// Entry type
    pub entry_type: u8,
    /// Entry name
    pub name: &'static str,
}

impl P9DirEntry {
    /// Create a new directory entry
    pub fn new(qid: Qid, offset: u64, entry_type: u8, name: &'static str) -> Self {
        Self {
            qid,
            offset,
            entry_type,
            name,
        }
    }
}

/// 9P2000.L file system information
///
/// Used by statfs operation to return file system information
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct P9Statfs {
    /// File system type
    pub f_type: u32,
    /// Block size
    pub f_bsize: u32,
    /// Total blocks
    pub f_blocks: u64,
    /// Free blocks
    pub f_bfree: u64,
    /// Available blocks
    pub f_bavail: u64,
    /// Total files
    pub f_files: u64,
    /// Free files
    pub f_ffree: u64,
    /// File system ID
    pub f_fsid: u64,
    /// Maximum filename length
    pub f_namelen: u32,
}

impl P9Statfs {
    /// Create a new P9Statfs with default values
    pub fn new() -> Self {
        Self {
            f_type: 0,
            f_bsize: 4096,
            f_blocks: 0,
            f_bfree: 0,
            f_bavail: 0,
            f_files: 0,
            f_ffree: 0,
            f_fsid: 0,
            f_namelen: 255,
        }
    }
}

impl Default for P9Statfs {
    fn default() -> Self {
        Self::new()
    }
}

/// 9P2000.L lock structure
///
/// Used for lock and getlock operations
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct P9Lock {
    /// Lock type (read, write, unlock)
    pub lock_type: u8,
    /// Lock flags
    pub flags: u32,
    /// Starting offset
    pub start: u64,
    /// Length of lock
    pub length: u64,
    /// Process ID
    pub proc_id: u32,
    /// Client ID (nodename)
    pub client_id: &'static str,
}

impl P9Lock {
    /// Create a new lock structure
    pub fn new(
        lock_type: u8,
        flags: u32,
        start: u64,
        length: u64,
        proc_id: u32,
        client_id: &'static str,
    ) -> Self {
        Self {
            lock_type,
            flags,
            start,
            length,
            proc_id,
            client_id,
        }
    }
}

/// 9P2000.L error codes
///
/// These correspond to Linux errno values
#[repr(i32)]
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum P9Error {
    /// Operation not permitted
    Eperm = 1,
    /// No such file or directory
    Enoent = 2,
    /// No such process
    Esrch = 3,
    /// Interrupted system call
    Eintr = 4,
    /// I/O error
    Eio = 5,
    /// No such device or address
    Enxio = 6,
    /// Argument list too long
    E2big = 7,
    /// Exec format error
    Enoexec = 8,
    /// Bad file number
    Ebadf = 9,
    /// No child processes
    Echild = 10,
    /// Try again
    Eagain = 11,
    /// Out of memory
    Enomem = 12,
    /// Permission denied
    Eacces = 13,
    /// Bad address
    Efault = 14,
    /// Block device required
    Enotblk = 15,
    /// Device or resource busy
    Ebusy = 16,
    /// File exists
    Eexist = 17,
    /// Cross-device link
    Exdev = 18,
    /// No such device
    Enodev = 19,
    /// Not a directory
    Enotdir = 20,
    /// Is a directory
    Eisdir = 21,
    /// Invalid argument
    Einval = 22,
    /// File table overflow
    Enfile = 23,
    /// Too many open files
    Emfile = 24,
    /// Not a typewriter
    Enotty = 25,
    /// Text file busy
    Etxtbsy = 26,
    /// File too large
    Efbig = 27,
    /// No space left on device
    Enospc = 28,
    /// Illegal seek
    Espipe = 29,
    /// Read-only file system
    Erofs = 30,
    /// Too many links
    Emlink = 31,
    /// Broken pipe
    Epipe = 32,
    /// Math argument out of domain
    Edom = 33,
    /// Math result not representable
    Erange = 34,
    /// Resource deadlock would occur
    Edeadlk = 35,
    /// File name too long
    Enametoolong = 36,
    /// No record locks available
    Enolck = 37,
    /// Function not implemented
    Enosys = 38,
    /// Directory not empty
    Enotempty = 39,
    /// Too many symbolic links encountered
    Eloop = 40,
    /// Operation would block
    Ewouldblock = 41,
    /// No message of desired type
    Enomsg = 42,
    /// Identifier removed
    Eidrm = 43,
    /// Channel number out of range
    Echrng = 44,
    /// Level 2 not synchronized
    El2nsync = 45,
    /// Level 3 halted
    El3hlt = 46,
    /// Level 3 reset
    El3rst = 47,
    /// Link number out of range
    Elnrng = 48,
    /// Protocol driver not attached
    Eunatch = 49,
    /// No CSI structure available
    Enocsi = 50,
    /// Level 2 halted
    El2hlt = 51,
    /// Invalid exchange
    Ebade = 52,
    /// Invalid request descriptor
    Ebadr = 53,
    /// Exchange full
    Exfull = 54,
    /// No anode
    Enoano = 55,
    /// Invalid request code
    Ebadrqc = 56,
    /// Invalid slot
    Ebadslt = 57,
    /// Bad font file format
    Ebfont = 59,
    /// Device not a stream
    Enostr = 60,
    /// No data available
    Enodata = 61,
    /// Timer expired
    Etime = 62,
    /// Out of streams resources
    Enosr = 63,
    /// Machine is not on the network
    Enonet = 64,
    /// Package not installed
    Enopkg = 65,
    /// Object is remote
    Eremote = 66,
    /// Link has been severed
    Enolink = 67,
    /// Advertise error
    Eadv = 68,
    /// Srmount error
    Esrmnt = 69,
    /// Communication error on send
    Ecomm = 70,
    /// Protocol error
    Eproto = 71,
    /// Multihop attempted
    Emultihop = 72,
    /// RFS specific error
    Edotdot = 73,
    /// Not a data message
    Ebadmsg = 74,
    /// Value too large for defined data type
    Eoverflow = 75,
    /// Name not unique on network
    Enotuniq = 76,
    /// File descriptor in bad state
    Ebadfd = 77,
    /// Remote address changed
    Eremchg = 78,
    /// Can not access a needed shared library
    Elibacc = 79,
    /// Accessing a corrupted shared library
    Elibbad = 80,
    /// .lib section in a.out corrupted
    Elibscn = 81,
    /// Attempting to link in too many shared libraries
    Elibmax = 82,
    /// Cannot exec a shared library directly
    Elibexec = 83,
    /// Illegal byte sequence
    Eilseq = 84,
    /// Interrupted system call should be restarted
    Erestart = 85,
    /// Streams pipe error
    Estrpipe = 86,
    /// Too many users
    Eusers = 87,
    /// Socket operation on non-socket
    Enotsock = 88,
    /// Destination address required
    Edestaddrreq = 89,
    /// Message too long
    Emsgsize = 90,
    /// Protocol wrong type for socket
    Eprototype = 91,
    /// Protocol not available
    Enoprotoopt = 92,
    /// Protocol not supported
    Eprotonosupport = 93,
    /// Socket type not supported
    Esocktnosupport = 94,
    /// Operation not supported on transport endpoint
    Eopnotsupp = 95,
    /// Protocol family not supported
    Epfnosupport = 96,
    /// Address family not supported by protocol
    Eafnosupport = 97,
    /// Address already in use
    Eaddrinuse = 98,
    /// Cannot assign requested address
    Eaddrnotavail = 99,
    /// Network is down
    Enetdown = 100,
    /// Network is unreachable
    Enetunreach = 101,
    /// Network dropped connection because of reset
    Enetreset = 102,
    /// Software caused connection abort
    Econnaborted = 103,
    /// Connection reset by peer
    Econnreset = 104,
    /// No buffer space available
    Enobufs = 105,
    /// Transport endpoint is already connected
    Eisconn = 106,
    /// Transport endpoint is not connected
    Enotconn = 107,
    /// Cannot send after transport endpoint shutdown
    Eshutdown = 108,
    /// Too many references: cannot splice
    Etoomanyrefs = 109,
    /// Connection timed out
    Etimedout = 110,
    /// Connection refused
    Econnrefused = 111,
    /// Host is down
    Ehostdown = 112,
    /// No route to host
    Ehostunreach = 113,
    /// Operation already in progress
    Ealready = 114,
    /// Operation now in progress
    Einprogress = 115,
    /// Stale file handle
    Estale = 116,
    /// Structure needs cleaning
    Euclean = 117,
    /// Not a XENIX named type file
    Enotnam = 118,
    /// No XENIX semaphores available
    Enavail = 119,
    /// Is a named type file
    Eisnam = 120,
    /// Remote I/O error
    Eremoteio = 121,
    /// Quota exceeded
    Edquot = 122,
    /// No medium found
    Enomedium = 123,
    /// Wrong medium type
    Emediumtype = 124,
    /// Operation canceled
    Ecanceled = 125,
    /// Required key not available
    Enokey = 126,
    /// Key has expired
    Ekeyexpired = 127,
    /// Key has been revoked
    Ekeyrevoked = 128,
    /// Key was rejected by service
    Ekeyrejected = 129,
    /// Owner died
    Eownerdead = 130,
    /// State not recoverable
    Enotrecoverable = 131,
    /// Operation not possible due to RF-kill
    Erfkill = 132,
    /// Memory page has hardware error
    Ehwpoison = 133,
}

impl fmt::Display for P9Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "P9Error({})", *self as i32)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_qid_creation() {
        let qid = Qid::new(P9QidType::Qtdir as u8, 1, 0x12345678);
        assert!(qid.is_dir());
        assert!(!qid.is_file());
        assert!(!qid.is_symlink());
    }

    #[test]
    fn test_qid_file() {
        let qid = Qid::new(P9QidType::Qtfile as u8, 1, 0x12345678);
        assert!(!qid.is_dir());
        assert!(qid.is_file());
        assert!(!qid.is_symlink());
    }

    #[test]
    fn test_qid_symlink() {
        let qid = Qid::new(P9QidType::Qtsymlink as u8, 1, 0x12345678);
        assert!(!qid.is_dir());
        assert!(!qid.is_file());
        assert!(qid.is_symlink());
    }

    #[test]
    fn test_p9_stat_creation() {
        let stat = P9Stat::new();
        assert_eq!(stat.mode, 0);
        assert_eq!(stat.size, 0);
        assert!(!stat.is_dir());
        assert!(stat.is_file()); // qtype 0 is Qtfile
        assert!(!stat.is_symlink());
    }

    #[test]
    fn test_p9_statfs_creation() {
        let statfs = P9Statfs::new();
        assert_eq!(statfs.f_bsize, 4096);
        assert_eq!(statfs.f_namelen, 255);
    }

    #[test]
    fn test_p9_dir_entry_creation() {
        let qid = Qid::new(P9QidType::Qtfile as u8, 1, 0x12345678);
        let entry = P9DirEntry::new(qid, 0, 0, "test.txt");
        assert_eq!(entry.name, "test.txt");
        assert_eq!(entry.offset, 0);
    }

    #[test]
    fn test_p9_lock_creation() {
        let lock = P9Lock::new(
            P9LockType::Rdlck as u8,
            P9LockFlags::Block as u32,
            0,
            1024,
            1234,
            "client1",
        );
        assert_eq!(lock.lock_type, P9LockType::Rdlck as u8);
        assert_eq!(lock.length, 1024);
        assert_eq!(lock.proc_id, 1234);
        assert_eq!(lock.client_id, "client1");
    }

    #[test]
    fn test_message_type_checks() {
        assert!(P9MsgType::Tversion.is_request());
        assert!(P9MsgType::Rversion.is_response());
        assert!(P9MsgType::Tlopen.is_request());
        assert!(P9MsgType::Rlopen.is_response());
    }

    #[test]
    fn test_getattr_masks() {
        assert_eq!(P9GetattrMask::BASIC, 0x000007ff);
        assert_eq!(P9GetattrMask::ALL, 0x00003fff);
    }

    #[test]
    fn test_constants() {
        assert_eq!(constants::P9_NOFID, 0xffffffff);
        assert_eq!(constants::P9_NONUNAME, 0xffffffff);
        assert_eq!(constants::P9_VERSION, "9P2000.L");
    }

    #[test]
    fn test_wire_write_u8() {
        let mut buf = [0u8; 4];
        let result = wire::write_u8(&mut buf, 0, 0xAB);
        assert_eq!(result, Ok(1));
        assert_eq!(buf[0], 0xAB);
        assert_eq!(buf[1], 0x00);
    }

    #[test]
    fn test_wire_write_u16() {
        let mut buf = [0u8; 4];
        let result = wire::write_u16(&mut buf, 0, 0x1234);
        assert_eq!(result, Ok(2));
        assert_eq!(buf[0], 0x34); // little-endian: LSB first
        assert_eq!(buf[1], 0x12); // MSB second
    }

    #[test]
    fn test_wire_write_u32() {
        let mut buf = [0u8; 8];
        let result = wire::write_u32(&mut buf, 0, 0x12345678);
        assert_eq!(result, Ok(4));
        assert_eq!(buf[0], 0x78); // little-endian: LSB first
        assert_eq!(buf[1], 0x56);
        assert_eq!(buf[2], 0x34);
        assert_eq!(buf[3], 0x12); // MSB last
    }

    #[test]
    fn test_wire_write_string() {
        let mut buf = [0u8; 16];
        let result = wire::write_string(&mut buf, 0, "test");
        assert_eq!(result, Ok(6)); // 2 bytes length + 4 bytes string
        assert_eq!(buf[0], 0x04); // length = 4 (little-endian)
        assert_eq!(buf[1], 0x00);
        assert_eq!(buf[2], b't');
        assert_eq!(buf[3], b'e');
        assert_eq!(buf[4], b's');
        assert_eq!(buf[5], b't');
    }

    #[test]
    fn test_wire_buffer_too_small() {
        let mut buf = [0u8; 2];
        let result = wire::write_u32(&mut buf, 0, 0x12345678);
        assert_eq!(result, Err(wire::WireError::BufferTooSmall));
    }

    #[test]
    fn test_tversion_message_creation() {
        let msg = TversionMessage::new(123, 8192, "9P2000.L");
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.msize, 8192);
        assert_eq!(msg.version, "9P2000.L");
    }

    #[test]
    fn test_tversion_default_9p2000l() {
        let msg = TversionMessage::default_9p2000l(456);
        assert_eq!(msg.tag, 456);
        assert_eq!(msg.msize, constants::P9_DEFAULT_MSIZE);
        assert_eq!(msg.version, constants::P9_VERSION);
    }

    #[test]
    fn test_tversion_serialize() {
        let msg = TversionMessage::new(123, 8192, "9P2000.L");
        let mut buf = [0u8; 32];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(21)); // 4 + 1 + 2 + 4 + 2 + 8 = 21 bytes total

        // Verify the serialized data
        // size[4] = 21 (little-endian)
        assert_eq!(buf[0], 21);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tversion (100)
        assert_eq!(buf[4], 100);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // msize[4] = 8192 (little-endian)
        assert_eq!(buf[7], 0);
        assert_eq!(buf[8], 32);
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // version length[2] = 8 (little-endian)
        assert_eq!(buf[11], 8);
        assert_eq!(buf[12], 0);

        // version[8] = "9P2000.L"
        assert_eq!(&buf[13..21], b"9P2000.L");
    }

    #[test]
    fn test_tversion_serialize_buffer_too_small() {
        let msg = TversionMessage::new(123, 8192, "9P2000.L");
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TversionError::BufferTooSmall));
    }

    #[test]
    fn test_tversion_serialize_version_too_long() {
        // Test with a version string that's too long (longer than u16::MAX)
        // We'll test the wire::write_string function directly since TversionMessage
        // requires a &'static str
        let mut buf = [0u8; 10];
        let long_string = "a".repeat(70000);
        let result = wire::write_string(&mut buf, 0, &long_string);
        assert_eq!(result, Err(wire::WireError::StringTooLong));
    }

    #[test]
    fn test_tversion_serialize_empty_version() {
        let msg = TversionMessage::new(123, 8192, "");
        let mut buf = [0u8; 32];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(13)); // 4 + 1 + 2 + 4 + 2 + 0 = 13 bytes total

        // Verify the serialized data
        // size[4] = 13 (little-endian)
        assert_eq!(buf[0], 13);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tversion (100)
        assert_eq!(buf[4], 100);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // msize[4] = 8192 (little-endian)
        assert_eq!(buf[7], 0);
        assert_eq!(buf[8], 32);
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // version length[2] = 0 (little-endian)
        assert_eq!(buf[11], 0);
        assert_eq!(buf[12], 0);

        // No version string data
    }

    #[test]
    fn test_tversion_send() {
        let msg = TversionMessage::default_9p2000l(123);

        // Test that send_tversion doesn't panic and returns a result
        // Note: In a real test environment, we might want to mock host_write
        // For now, we just verify the function compiles and can be called
        let result = msg.send_tversion();

        // The actual result depends on the host environment
        // We just verify it returns a Result<u32, TversionError>
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
                // bytes_written is u32, so it's always >= 0
            }
            Err(e) => {
                // Should not get serialization errors since we're using a valid message
                assert!(matches!(
                    e,
                    TversionError::BufferTooSmall
                        | TversionError::VersionTooLong
                        | TversionError::InternalError
                ));
            }
        }
    }

    #[test]
    fn test_wire_read_u8() {
        let buf = [0xAB, 0xCD];
        let (value, offset) = wire::read_u8(&buf, 0).unwrap();
        assert_eq!(value, 0xAB);
        assert_eq!(offset, 1);
    }

    #[test]
    fn test_wire_read_u16() {
        let buf = [0x34, 0x12, 0xCD, 0xAB];
        let (value, offset) = wire::read_u16(&buf, 0).unwrap();
        assert_eq!(value, 0x1234); // little-endian: LSB first
        assert_eq!(offset, 2);
    }

    #[test]
    fn test_wire_read_u32() {
        let buf = [0x78, 0x56, 0x34, 0x12, 0xCD, 0xAB];
        let (value, offset) = wire::read_u32(&buf, 0).unwrap();
        assert_eq!(value, 0x12345678); // little-endian: LSB first
        assert_eq!(offset, 4);
    }

    #[test]
    fn test_wire_read_string() {
        let buf = [0x04, 0x00, b't', b'e', b's', b't', 0xFF];
        let (value, offset) = wire::read_string(&buf, 0).unwrap();
        assert_eq!(value, "test");
        assert_eq!(offset, 6); // 2 bytes length + 4 bytes string
    }

    #[test]
    fn test_wire_read_buffer_too_small() {
        let buf = [0x12];
        let result = wire::read_u32(&buf, 0);
        assert_eq!(result, Err(wire::WireError::BufferTooSmall));
    }

    #[test]
    fn test_rversion_message_creation() {
        let msg = RversionMessage::new(123, 8192, "9P2000.L");
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.msize, 8192);
        assert_eq!(msg.version, "9P2000.L");
    }

    #[test]
    fn test_rversion_deserialize() {
        // Create a Tversion message and serialize it, then deserialize as Rversion
        let tversion = TversionMessage::new(123, 8192, "9P2000.L");
        let mut buf = [0u8; 32];
        let bytes_written = tversion.serialize(&mut buf).unwrap();

        // Change the message type from Tversion to Rversion
        buf[4] = P9MsgType::Rversion as u8;

        // Deserialize as Rversion
        let (rversion, bytes_consumed) = RversionMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, bytes_written);
        assert_eq!(rversion.tag, 123);
        assert_eq!(rversion.msize, 8192);
        assert_eq!(rversion.version, "9P2000.L");
    }

    #[test]
    fn test_rversion_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RversionMessage::deserialize(&buf);
        assert_eq!(result, Err(RversionError::BufferTooSmall));
    }

    #[test]
    fn test_rversion_deserialize_invalid_message_type() {
        // Create a valid Tversion message but don't change the type
        let tversion = TversionMessage::new(123, 8192, "9P2000.L");
        let mut buf = [0u8; 32];
        tversion.serialize(&mut buf).unwrap();

        // Try to deserialize as Rversion (should fail because type is Tversion)
        let result = RversionMessage::deserialize(&buf);
        assert_eq!(result, Err(RversionError::InvalidMessageType));
    }

    #[test]
    fn test_rversion_deserialize_unknown_version() {
        // Create a Tversion message with unknown version
        let tversion = TversionMessage::new(123, 8192, "9P2000.Unknown");
        let mut buf = [0u8; 64];
        tversion.serialize(&mut buf).unwrap();

        // Change the message type from Tversion to Rversion
        buf[4] = P9MsgType::Rversion as u8;

        // Deserialize as Rversion (should fail because version is unknown)
        let result = RversionMessage::deserialize(&buf);
        assert_eq!(result, Err(RversionError::UnknownVersion));
    }

    #[test]
    fn test_roundtrip_tversion_rversion() {
        // Create a Tversion message
        let original = TversionMessage::new(456, 4096, "9P2000.L");
        let mut buf = [0u8; 32];
        let bytes_written = original.serialize(&mut buf).unwrap();

        // Change the message type from Tversion to Rversion
        buf[4] = P9MsgType::Rversion as u8;

        // Deserialize as Rversion
        let (rversion, bytes_consumed) = RversionMessage::deserialize(&buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, bytes_written);
        assert_eq!(rversion.tag, original.tag);
        assert_eq!(rversion.msize, original.msize);
        assert_eq!(rversion.version, original.version);
    }

    #[test]
    fn test_tflush_message_creation() {
        let msg = TflushMessage::new(123, 456);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.oldtag, 456);
    }

    #[test]
    fn test_tflush_serialize() {
        let msg = TflushMessage::new(123, 456);
        let mut buf = [0u8; 16];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(9)); // 4 + 1 + 2 + 2 = 9 bytes total

        // Verify the serialized data
        // size[4] = 9 (little-endian)
        assert_eq!(buf[0], 9);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tflush (108)
        assert_eq!(buf[4], 108);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // oldtag[2] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
    }

    #[test]
    fn test_tflush_serialize_buffer_too_small() {
        let msg = TflushMessage::new(123, 456);
        let mut buf = [0u8; 5]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TflushError::BufferTooSmall));
    }

    #[test]
    fn test_tflush_send() {
        let msg = TflushMessage::new(123, 456);

        // Test that send_tflush doesn't panic and returns a result
        // Note: In a real test environment, we might want to mock host_write
        // For now, we just verify the function compiles and can be called
        let result = msg.send_tflush();

        // The actual result depends on the host environment
        // We just verify it returns a Result<u32, TflushError>
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
                // bytes_written is u32, so it's always >= 0
            }
            Err(e) => {
                // Should not get serialization errors since we're using a valid message
                assert!(matches!(
                    e,
                    TflushError::BufferTooSmall | TflushError::InternalError
                ));
            }
        }
    }

    #[test]
    fn test_rflush_message_creation() {
        let msg = RflushMessage::new(123);
        assert_eq!(msg.tag, 123);
    }

    #[test]
    fn test_rflush_deserialize() {
        // Create a proper Rflush message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 7 (little-endian)
        buf[0] = 7;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rflush (109)
        buf[4] = P9MsgType::Rflush as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Deserialize as Rflush
        let (rflush, bytes_consumed) = RflushMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 7);
        assert_eq!(rflush.tag, 123);
    }

    #[test]
    fn test_rflush_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RflushMessage::deserialize(&buf);
        assert_eq!(result, Err(RflushError::BufferTooSmall));
    }

    #[test]
    fn test_rflush_deserialize_invalid_message_type() {
        // Create a valid Tflush message but don't change the type
        let tflush = TflushMessage::new(123, 456);
        let mut buf = [0u8; 16];
        tflush.serialize(&mut buf).unwrap();

        // Try to deserialize as Rflush (should fail because type is Tflush)
        let result = RflushMessage::deserialize(&buf);
        assert_eq!(result, Err(RflushError::InvalidMessageType));
    }

    #[test]
    fn test_roundtrip_tflush_rflush() {
        // Create a Tflush message
        let original = TflushMessage::new(789, 1011);
        let mut tflush_buf = [0u8; 16];
        let tflush_bytes_written = original.serialize(&mut tflush_buf).unwrap();

        // Create a separate Rflush message with the same tag
        let _rflush_msg = RflushMessage::new(original.tag);
        let mut rflush_buf = [0u8; 16];

        // Manually create Rflush buffer
        // Write size[4] = 7 (little-endian)
        rflush_buf[0] = 7;
        rflush_buf[1] = 0;
        rflush_buf[2] = 0;
        rflush_buf[3] = 0;

        // Write message type[1] = Rflush (109)
        rflush_buf[4] = P9MsgType::Rflush as u8;

        // Write tag[2] = 789 (little-endian)
        rflush_buf[5] = (789 & 0xff) as u8;
        rflush_buf[6] = ((789 >> 8) & 0xff) as u8;

        // Deserialize as Rflush
        let (rflush, bytes_consumed) = RflushMessage::deserialize(&rflush_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 7);
        assert_eq!(rflush.tag, original.tag);
        assert_eq!(tflush_bytes_written, 9); // Tflush is 9 bytes
    }

    #[test]
    fn test_tflush_serialize_edge_cases() {
        // Test with maximum u16 values
        let msg = TflushMessage::new(u16::MAX, u16::MAX);
        let mut buf = [0u8; 16];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(9));

        // Verify the serialized data
        // size[4] = 9 (little-endian)
        assert_eq!(buf[0], 9);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tflush (108)
        assert_eq!(buf[4], 108);

        // tag[2] = u16::MAX (little-endian)
        assert_eq!(buf[5], 255);
        assert_eq!(buf[6], 255);

        // oldtag[2] = u16::MAX (little-endian)
        assert_eq!(buf[7], 255);
        assert_eq!(buf[8], 255);
    }

    #[test]
    fn test_tflush_serialize_zero_values() {
        // Test with zero values
        let msg = TflushMessage::new(0, 0);
        let mut buf = [0u8; 16];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(9));

        // Verify the serialized data
        // size[4] = 9 (little-endian)
        assert_eq!(buf[0], 9);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tflush (108)
        assert_eq!(buf[4], 108);

        // tag[2] = 0 (little-endian)
        assert_eq!(buf[5], 0);
        assert_eq!(buf[6], 0);

        // oldtag[2] = 0 (little-endian)
        assert_eq!(buf[7], 0);
        assert_eq!(buf[8], 0);
    }

    // Tread message tests
    #[test]
    fn test_tread_message_creation() {
        let msg = TreadMessage::new(123, 456, 789, 1024);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.offset, 789);
        assert_eq!(msg.count, 1024);
    }

    #[test]
    fn test_tread_serialize() {
        let msg = TreadMessage::new(123, 456, 789, 1024);
        let mut buf = [0u8; 32];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(23)); // 4 + 1 + 2 + 4 + 8 + 4 = 23 bytes total

        // Verify the serialized data
        // size[4] = 23 (little-endian)
        assert_eq!(buf[0], 23);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tread (116)
        assert_eq!(buf[4], 116);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // offset[8] = 789 (little-endian)
        assert_eq!(buf[11], 21); // 789 & 0xff = 21
        assert_eq!(buf[12], 3); // (789 >> 8) & 0xff = 3
        assert_eq!(buf[13], 0);
        assert_eq!(buf[14], 0);
        assert_eq!(buf[15], 0);
        assert_eq!(buf[16], 0);
        assert_eq!(buf[17], 0);
        assert_eq!(buf[18], 0);

        // count[4] = 1024 (little-endian)
        assert_eq!(buf[19], 0);
        assert_eq!(buf[20], 4);
        assert_eq!(buf[21], 0);
        assert_eq!(buf[22], 0);
    }

    #[test]
    fn test_tread_serialize_buffer_too_small() {
        let msg = TreadMessage::new(123, 456, 789, 1024);
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TreadError::BufferTooSmall));
    }

    #[test]
    fn test_tread_send() {
        let msg = TreadMessage::new(123, 456, 789, 1024);

        // Test that send_tread doesn't panic and returns a result
        let result = msg.send_tread();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TreadError::BufferTooSmall | TreadError::InternalError
                ));
            }
        }
    }

    // Rread message tests
    #[test]
    fn test_rread_message_creation() {
        let data = vec![1, 2, 3, 4];
        let msg = RreadMessage::new(123, data.clone());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.count, 4);
        assert_eq!(msg.data, data);
    }

    #[test]
    fn test_rread_deserialize() {
        // Create a proper Rread message buffer
        let mut buf = [0u8; 32];

        // Write size[4] = 15 (little-endian) - 4 + 1 + 2 + 4 + 4 = 15
        buf[0] = 15;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rread (117)
        buf[4] = P9MsgType::Rread as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write count[4] = 4 (little-endian)
        buf[7] = 4;
        buf[8] = 0;
        buf[9] = 0;
        buf[10] = 0;

        // Add some dummy data
        buf[11..15].copy_from_slice(b"test");

        // Deserialize as Rread
        let (rread, bytes_consumed) = RreadMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 15);
        assert_eq!(rread.tag, 123);
        assert_eq!(rread.count, 4);
        assert_eq!(rread.data, b"test".to_vec());
    }

    #[test]
    fn test_rread_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RreadMessage::deserialize(&buf);
        assert_eq!(result, Err(RreadError::BufferTooSmall));
    }

    #[test]
    fn test_rread_deserialize_invalid_message_type() {
        // Create a valid Tread message but don't change the type
        let tread = TreadMessage::new(123, 456, 789, 1024);
        let mut buf = [0u8; 32];
        tread.serialize(&mut buf).unwrap();

        // Try to deserialize as Rread (should fail because type is Tread)
        let result = RreadMessage::deserialize(&buf);
        assert_eq!(result, Err(RreadError::InvalidMessageType));
    }

    // Twrite message tests
    #[test]
    fn test_twrite_message_creation() {
        let data = vec![1, 2, 3, 4];
        let msg = TwriteMessage::new(123, 456, 789, data.clone());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.offset, 789);
        assert_eq!(msg.count, 4);
        assert_eq!(msg.data, data);
    }

    #[test]
    fn test_twrite_serialize() {
        let data = b"test".to_vec();
        let msg = TwriteMessage::new(123, 456, 789, data);
        let mut buf = [0u8; 32];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(27)); // 4 + 1 + 2 + 4 + 8 + 4 + 4 = 27 bytes total

        // Verify the serialized data
        // size[4] = 27 (little-endian)
        assert_eq!(buf[0], 27);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Twrite (118)
        assert_eq!(buf[4], 118);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // offset[8] = 789 (little-endian)
        assert_eq!(buf[11], 21); // 789 & 0xff = 21
        assert_eq!(buf[12], 3); // (789 >> 8) & 0xff = 3
        assert_eq!(buf[13], 0);
        assert_eq!(buf[14], 0);
        assert_eq!(buf[15], 0);
        assert_eq!(buf[16], 0);
        assert_eq!(buf[17], 0);
        assert_eq!(buf[18], 0);

        // count[4] = 4 (little-endian)
        assert_eq!(buf[19], 4);
        assert_eq!(buf[20], 0);
        assert_eq!(buf[21], 0);
        assert_eq!(buf[22], 0);

        // data[4] = "test"
        assert_eq!(&buf[23..27], b"test");
    }

    #[test]
    fn test_twrite_serialize_buffer_too_small() {
        let data = b"test".to_vec();
        let msg = TwriteMessage::new(123, 456, 789, data);
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TwriteError::BufferTooSmall));
    }

    #[test]
    fn test_twrite_send() {
        let data = b"test".to_vec();
        let msg = TwriteMessage::new(123, 456, 789, data);

        // Test that send_twrite doesn't panic and returns a result
        let result = msg.send_twrite();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TwriteError::BufferTooSmall | TwriteError::InternalError
                ));
            }
        }
    }

    // Rwrite message tests
    #[test]
    fn test_rwrite_message_creation() {
        let msg = RwriteMessage::new(123, 1024);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.count, 1024);
    }

    #[test]
    fn test_rwrite_deserialize() {
        // Create a proper Rwrite message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 11 (little-endian) - 4 + 1 + 2 + 4 = 11
        buf[0] = 11;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rwrite (119)
        buf[4] = P9MsgType::Rwrite as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write count[4] = 1024 (little-endian)
        buf[7] = 0;
        buf[8] = 4;
        buf[9] = 0;
        buf[10] = 0;

        // Deserialize as Rwrite
        let (rwrite, bytes_consumed) = RwriteMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 11);
        assert_eq!(rwrite.tag, 123);
        assert_eq!(rwrite.count, 1024);
    }

    #[test]
    fn test_rwrite_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RwriteMessage::deserialize(&buf);
        assert_eq!(result, Err(RwriteError::BufferTooSmall));
    }

    #[test]
    fn test_rwrite_deserialize_invalid_message_type() {
        // Create a valid Twrite message but don't change the type
        let data = b"test".to_vec();
        let twrite = TwriteMessage::new(123, 456, 789, data);
        let mut buf = [0u8; 32];
        twrite.serialize(&mut buf).unwrap();

        // Try to deserialize as Rwrite (should fail because type is Twrite)
        let result = RwriteMessage::deserialize(&buf);
        assert_eq!(result, Err(RwriteError::InvalidMessageType));
    }

    // Roundtrip tests
    #[test]
    fn test_roundtrip_tread_rread() {
        // Create a Tread message
        let original = TreadMessage::new(456, 789, 1024, 4);
        let mut tread_buf = [0u8; 32];
        let tread_bytes_written = original.serialize(&mut tread_buf).unwrap();

        // Create a separate Rread message with the same tag
        let data = b"test".to_vec();
        let _rread_msg = RreadMessage::new(original.tag, data);
        let mut rread_buf = [0u8; 32];

        // Manually create Rread buffer
        // Write size[4] = 15 (little-endian) - 4 + 1 + 2 + 4 + 4 = 15
        rread_buf[0] = 15;
        rread_buf[1] = 0;
        rread_buf[2] = 0;
        rread_buf[3] = 0;

        // Write message type[1] = Rread (117)
        rread_buf[4] = P9MsgType::Rread as u8;

        // Write tag[2] = 456 (little-endian)
        rread_buf[5] = (456 & 0xff) as u8;
        rread_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write count[4] = 4 (little-endian)
        rread_buf[7] = 4;
        rread_buf[8] = 0;
        rread_buf[9] = 0;
        rread_buf[10] = 0;

        // Add some dummy data
        rread_buf[11..15].copy_from_slice(b"test");

        // Deserialize as Rread
        let (rread, bytes_consumed) = RreadMessage::deserialize(&rread_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 15);
        assert_eq!(rread.tag, original.tag);
        assert_eq!(rread.count, 4);
        assert_eq!(tread_bytes_written, 23); // Tread is 23 bytes
    }

    #[test]
    fn test_roundtrip_twrite_rwrite() {
        // Create a Twrite message
        let data = b"test".to_vec();
        let original = TwriteMessage::new(789, 1011, 2048, data);
        let mut twrite_buf = [0u8; 32];
        let twrite_bytes_written = original.serialize(&mut twrite_buf).unwrap();

        // Create a separate Rwrite message with the same tag
        let _rwrite_msg = RwriteMessage::new(original.tag, 4);
        let mut rwrite_buf = [0u8; 16];

        // Manually create Rwrite buffer
        // Write size[4] = 11 (little-endian)
        rwrite_buf[0] = 11;
        rwrite_buf[1] = 0;
        rwrite_buf[2] = 0;
        rwrite_buf[3] = 0;

        // Write message type[1] = Rwrite (119)
        rwrite_buf[4] = P9MsgType::Rwrite as u8;

        // Write tag[2] = 789 (little-endian)
        rwrite_buf[5] = (789 & 0xff) as u8;
        rwrite_buf[6] = ((789 >> 8) & 0xff) as u8;

        // Write count[4] = 4 (little-endian)
        rwrite_buf[7] = 4;
        rwrite_buf[8] = 0;
        rwrite_buf[9] = 0;
        rwrite_buf[10] = 0;

        // Deserialize as Rwrite
        let (rwrite, bytes_consumed) = RwriteMessage::deserialize(&rwrite_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 11);
        assert_eq!(rwrite.tag, original.tag);
        assert_eq!(rwrite.count, 4);
        assert_eq!(twrite_bytes_written, 27); // Twrite is 27 bytes
    }

    // Twalk message tests
    #[test]
    fn test_twalk_message_creation() {
        let wnames = vec![
            "dir1".to_string(),
            "dir2".to_string(),
            "file.txt".to_string(),
        ];
        let msg = TwalkMessage::new(123, 456, 789, wnames);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.newfid, 789);
        assert_eq!(msg.nwname, 3);
        assert_eq!(msg.wnames.len(), 3);
        assert_eq!(msg.wnames[0], "dir1");
        assert_eq!(msg.wnames[1], "dir2");
        assert_eq!(msg.wnames[2], "file.txt");
    }

    #[test]
    fn test_twalk_message_creation_single() {
        let msg = TwalkMessage::new_single(123, 456, 789, "file.txt");
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.newfid, 789);
        assert_eq!(msg.nwname, 1);
        assert_eq!(msg.wnames.len(), 1);
        assert_eq!(msg.wnames[0], "file.txt");
    }

    #[test]
    fn test_twalk_serialize() {
        let wnames = vec!["dir1".to_string(), "file.txt".to_string()];
        let msg = TwalkMessage::new(123, 456, 789, wnames);
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(33)); // 4 + 1 + 2 + 4 + 4 + 2 + (2+4) + (2+8) = 33 bytes total

        // Verify the serialized data
        // size[4] = 33 (little-endian)
        assert_eq!(buf[0], 33);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Twalk (110)
        assert_eq!(buf[4], 110);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // newfid[4] = 789 (little-endian)
        assert_eq!(buf[11], 21); // 789 & 0xff = 21
        assert_eq!(buf[12], 3); // (789 >> 8) & 0xff = 3
        assert_eq!(buf[13], 0);
        assert_eq!(buf[14], 0);

        // nwname[2] = 2 (little-endian)
        assert_eq!(buf[15], 2);
        assert_eq!(buf[16], 0);

        // wname[0] = "dir1" (length[2] + string[4])
        assert_eq!(buf[17], 4); // length = 4
        assert_eq!(buf[18], 0);
        assert_eq!(&buf[19..23], b"dir1");

        // wname[1] = "file.txt" (length[2] + string[8])
        assert_eq!(buf[23], 8); // length = 8
        assert_eq!(buf[24], 0);
        assert_eq!(&buf[25..33], b"file.txt");
    }

    #[test]
    fn test_twalk_serialize_buffer_too_small() {
        let wnames = vec!["dir1".to_string(), "file.txt".to_string()];
        let msg = TwalkMessage::new(123, 456, 789, wnames);
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TwalkError::BufferTooSmall));
    }

    #[test]
    fn test_twalk_send() {
        let wnames = vec!["dir1".to_string(), "file.txt".to_string()];
        let msg = TwalkMessage::new(123, 456, 789, wnames);

        // Test that send_twalk doesn't panic and returns a result
        let result = msg.send_twalk();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TwalkError::BufferTooSmall
                        | TwalkError::NameTooLong
                        | TwalkError::NameCountMismatch
                        | TwalkError::InternalError
                ));
            }
        }
    }

    // Rwalk message tests
    #[test]
    fn test_rwalk_message_creation() {
        let qids = [
            Qid::new(P9QidType::Qtdir as u8, 1, 0x12345678),
            Qid::new(P9QidType::Qtfile as u8, 2, 0x87654321),
        ];
        let msg = RwalkMessage::new(123, &qids);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.nwqid, 2);
        assert_eq!(msg.wqids.len(), 2);
        assert_eq!(msg.wqids[0].qtype, P9QidType::Qtdir as u8);
        assert_eq!(msg.wqids[0].version, 1);
        assert_eq!(msg.wqids[0].path, 0x12345678);
        assert_eq!(msg.wqids[1].qtype, P9QidType::Qtfile as u8);
        assert_eq!(msg.wqids[1].version, 2);
        assert_eq!(msg.wqids[1].path, 0x87654321);
    }

    #[test]
    fn test_rwalk_message_creation_single() {
        let qid = Qid::new(P9QidType::Qtfile as u8, 1, 0x12345678);
        let msg = RwalkMessage::new_single(123, qid);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.nwqid, 1);
        assert_eq!(msg.wqids.len(), 1);
        assert_eq!(msg.wqids[0].qtype, P9QidType::Qtfile as u8);
        assert_eq!(msg.wqids[0].version, 1);
        assert_eq!(msg.wqids[0].path, 0x12345678);
    }

    #[test]
    fn test_rwalk_deserialize() {
        // Create a proper Rwalk message buffer
        let mut buf = [0u8; 64];

        // Write size[4] = 20 (little-endian) - 4 + 1 + 2 + 2 + 13 = 22
        buf[0] = 22;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rwalk (111)
        buf[4] = P9MsgType::Rwalk as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write nwqid[2] = 1 (little-endian)
        buf[7] = 1;
        buf[8] = 0;

        // Write wqid[0][13] = QID(type=0x80, version=1, path=0x12345678)
        buf[9] = 0x80; // Qtdir
        // version[4] = 1 (little-endian)
        buf[10] = 1;
        buf[11] = 0;
        buf[12] = 0;
        buf[13] = 0;
        // path[8] = 0x12345678 (little-endian)
        buf[14] = 0x78;
        buf[15] = 0x56;
        buf[16] = 0x34;
        buf[17] = 0x12;
        buf[18] = 0;
        buf[19] = 0;
        buf[20] = 0;
        buf[21] = 0;

        // Deserialize as Rwalk
        let (rwalk, bytes_consumed) = RwalkMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 22);
        assert_eq!(rwalk.tag, 123);
        assert_eq!(rwalk.nwqid, 1);
        assert_eq!(rwalk.wqids.len(), 1);
        assert_eq!(rwalk.wqids[0].qtype, 0x80);
        assert_eq!(rwalk.wqids[0].version, 1);
        assert_eq!(rwalk.wqids[0].path, 0x12345678);
    }

    #[test]
    fn test_rwalk_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RwalkMessage::deserialize(&buf);
        assert_eq!(result, Err(RwalkError::BufferTooSmall));
    }

    #[test]
    fn test_rwalk_deserialize_invalid_message_type() {
        // Create a valid Twalk message but don't change the type
        let wnames = vec!["dir1".to_string()];
        let twalk = TwalkMessage::new(123, 456, 789, wnames);
        let mut buf = [0u8; 64];
        twalk.serialize(&mut buf).unwrap();

        // Try to deserialize as Rwalk (should fail because type is Twalk)
        let result = RwalkMessage::deserialize(&buf);
        assert_eq!(result, Err(RwalkError::InvalidMessageType));
    }

    // Roundtrip tests for Twalk/Rwalk
    #[test]
    fn test_roundtrip_twalk_rwalk() {
        // Create a Twalk message
        let wnames = vec!["dir1".to_string(), "file.txt".to_string()];
        let original = TwalkMessage::new(456, 789, 1011, wnames);
        let mut twalk_buf = [0u8; 64];
        let twalk_bytes_written = original.serialize(&mut twalk_buf).unwrap();

        // Create a separate Rwalk message with the same tag
        let qids = [
            Qid::new(P9QidType::Qtdir as u8, 1, 0x12345678),
            Qid::new(P9QidType::Qtfile as u8, 2, 0x87654321),
        ];
        let _rwalk_msg = RwalkMessage::new(original.tag, &qids);
        let mut rwalk_buf = [0u8; 64];

        // Manually create Rwalk buffer
        // Write size[4] = 35 (little-endian) - 4 + 1 + 2 + 2 + (13*2) = 35
        rwalk_buf[0] = 35;
        rwalk_buf[1] = 0;
        rwalk_buf[2] = 0;
        rwalk_buf[3] = 0;

        // Write message type[1] = Rwalk (111)
        rwalk_buf[4] = P9MsgType::Rwalk as u8;

        // Write tag[2] = 456 (little-endian)
        rwalk_buf[5] = (456 & 0xff) as u8;
        rwalk_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write nwqid[2] = 2 (little-endian)
        rwalk_buf[7] = 2;
        rwalk_buf[8] = 0;

        // Write wqid[0][13] = QID(type=0x80, version=1, path=0x12345678)
        rwalk_buf[9] = 0x80; // Qtdir
        rwalk_buf[10] = 1; // version = 1
        rwalk_buf[11] = 0;
        rwalk_buf[12] = 0;
        rwalk_buf[13] = 0;
        rwalk_buf[14] = 0x78; // path = 0x12345678 (little-endian)
        rwalk_buf[15] = 0x56;
        rwalk_buf[16] = 0x34;
        rwalk_buf[17] = 0x12;
        rwalk_buf[18] = 0;
        rwalk_buf[19] = 0;
        rwalk_buf[20] = 0;
        rwalk_buf[21] = 0;

        // Write wqid[1][13] = QID(type=0x00, version=2, path=0x87654321)
        rwalk_buf[22] = 0x00; // Qtfile
        rwalk_buf[23] = 2; // version = 2
        rwalk_buf[24] = 0;
        rwalk_buf[25] = 0;
        rwalk_buf[26] = 0;
        rwalk_buf[27] = 0x21; // path = 0x87654321 (little-endian)
        rwalk_buf[28] = 0x43;
        rwalk_buf[29] = 0x65;
        rwalk_buf[30] = 0x87;

        // Deserialize as Rwalk
        let (rwalk, bytes_consumed) = RwalkMessage::deserialize(&rwalk_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 35);
        assert_eq!(rwalk.tag, original.tag);
        assert_eq!(rwalk.nwqid, 2);
        assert_eq!(rwalk.wqids.len(), 2);
        assert_eq!(twalk_bytes_written, 33); // Twalk is 33 bytes
    }

    // Tclunk message tests
    #[test]
    fn test_tclunk_message_creation() {
        let msg = TclunkMessage::new(123, 456);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
    }

    #[test]
    fn test_tclunk_serialize() {
        let msg = TclunkMessage::new(123, 456);
        let mut buf = [0u8; 16];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(11)); // 4 + 1 + 2 + 4 = 11 bytes total

        // Verify the serialized data
        // size[4] = 11 (little-endian)
        assert_eq!(buf[0], 11);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tclunk (120)
        assert_eq!(buf[4], 120);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);
    }

    #[test]
    fn test_tclunk_serialize_buffer_too_small() {
        let msg = TclunkMessage::new(123, 456);
        let mut buf = [0u8; 5]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TclunkError::BufferTooSmall));
    }

    #[test]
    fn test_tclunk_send() {
        let msg = TclunkMessage::new(123, 456);

        // Test that send_tclunk doesn't panic and returns a result
        let result = msg.send_tclunk();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TclunkError::BufferTooSmall | TclunkError::InternalError
                ));
            }
        }
    }

    // Rclunk message tests
    #[test]
    fn test_rclunk_message_creation() {
        let msg = RclunkMessage::new(123);
        assert_eq!(msg.tag, 123);
    }

    #[test]
    fn test_rclunk_deserialize() {
        // Create a proper Rclunk message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 7 (little-endian) - 4 + 1 + 2 = 7
        buf[0] = 7;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rclunk (121)
        buf[4] = P9MsgType::Rclunk as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Deserialize as Rclunk
        let (rclunk, bytes_consumed) = RclunkMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 7);
        assert_eq!(rclunk.tag, 123);
    }

    #[test]
    fn test_rclunk_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RclunkMessage::deserialize(&buf);
        assert_eq!(result, Err(RclunkError::BufferTooSmall));
    }

    #[test]
    fn test_rclunk_deserialize_invalid_message_type() {
        // Create a valid Tclunk message but don't change the type
        let tclunk = TclunkMessage::new(123, 456);
        let mut buf = [0u8; 16];
        tclunk.serialize(&mut buf).unwrap();

        // Try to deserialize as Rclunk (should fail because type is Tclunk)
        let result = RclunkMessage::deserialize(&buf);
        assert_eq!(result, Err(RclunkError::InvalidMessageType));
    }

    // Roundtrip tests for Tclunk/Rclunk
    #[test]
    fn test_roundtrip_tclunk_rclunk() {
        // Create a Tclunk message
        let original = TclunkMessage::new(456, 789);
        let mut tclunk_buf = [0u8; 16];
        let tclunk_bytes_written = original.serialize(&mut tclunk_buf).unwrap();

        // Create a separate Rclunk message with the same tag
        let _rclunk_msg = RclunkMessage::new(original.tag);
        let mut rclunk_buf = [0u8; 16];

        // Manually create Rclunk buffer
        // Write size[4] = 7 (little-endian)
        rclunk_buf[0] = 7;
        rclunk_buf[1] = 0;
        rclunk_buf[2] = 0;
        rclunk_buf[3] = 0;

        // Write message type[1] = Rclunk (121)
        rclunk_buf[4] = P9MsgType::Rclunk as u8;

        // Write tag[2] = 456 (little-endian)
        rclunk_buf[5] = (456 & 0xff) as u8;
        rclunk_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Deserialize as Rclunk
        let (rclunk, bytes_consumed) = RclunkMessage::deserialize(&rclunk_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 7);
        assert_eq!(rclunk.tag, original.tag);
        assert_eq!(tclunk_bytes_written, 11); // Tclunk is 11 bytes
    }

    // Tremove message tests
    #[test]
    fn test_tremove_message_creation() {
        let msg = TremoveMessage::new(123, 456);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
    }

    #[test]
    fn test_tremove_serialize() {
        let msg = TremoveMessage::new(123, 456);
        let mut buf = [0u8; 16];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(11)); // 4 + 1 + 2 + 4 = 11 bytes total

        // Verify the serialized data
        // size[4] = 11 (little-endian)
        assert_eq!(buf[0], 11);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tremove (122)
        assert_eq!(buf[4], 122);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);
    }

    #[test]
    fn test_tremove_serialize_buffer_too_small() {
        let msg = TremoveMessage::new(123, 456);
        let mut buf = [0u8; 5]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TremoveError::BufferTooSmall));
    }

    #[test]
    fn test_tremove_send() {
        let msg = TremoveMessage::new(123, 456);

        // Test that send_tremove doesn't panic and returns a result
        let result = msg.send_tremove();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TremoveError::BufferTooSmall | TremoveError::InternalError
                ));
            }
        }
    }

    // Rremove message tests
    #[test]
    fn test_rremove_message_creation() {
        let msg = RremoveMessage::new(123);
        assert_eq!(msg.tag, 123);
    }

    #[test]
    fn test_rremove_deserialize() {
        // Create a proper Rremove message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 7 (little-endian) - 4 + 1 + 2 = 7
        buf[0] = 7;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rremove (123)
        buf[4] = P9MsgType::Rremove as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Deserialize as Rremove
        let (rremove, bytes_consumed) = RremoveMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 7);
        assert_eq!(rremove.tag, 123);
    }

    #[test]
    fn test_rremove_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RremoveMessage::deserialize(&buf);
        assert_eq!(result, Err(RremoveError::BufferTooSmall));
    }

    #[test]
    fn test_rremove_deserialize_invalid_message_type() {
        // Create a valid Tremove message but don't change the type
        let tremove = TremoveMessage::new(123, 456);
        let mut buf = [0u8; 16];
        tremove.serialize(&mut buf).unwrap();

        // Try to deserialize as Rremove (should fail because type is Tremove)
        let result = RremoveMessage::deserialize(&buf);
        assert_eq!(result, Err(RremoveError::InvalidMessageType));
    }

    // Roundtrip tests for Tremove/Rremove
    #[test]
    fn test_roundtrip_tremove_rremove() {
        // Create a Tremove message
        let original = TremoveMessage::new(456, 789);
        let mut tremove_buf = [0u8; 16];
        let tremove_bytes_written = original.serialize(&mut tremove_buf).unwrap();

        // Create a separate Rremove message with the same tag
        let _rremove_msg = RremoveMessage::new(original.tag);
        let mut rremove_buf = [0u8; 16];

        // Manually create Rremove buffer
        // Write size[4] = 7 (little-endian)
        rremove_buf[0] = 7;
        rremove_buf[1] = 0;
        rremove_buf[2] = 0;
        rremove_buf[3] = 0;

        // Write message type[1] = Rremove (123)
        rremove_buf[4] = P9MsgType::Rremove as u8;

        // Write tag[2] = 456 (little-endian)
        rremove_buf[5] = (456 & 0xff) as u8;
        rremove_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Deserialize as Rremove
        let (rremove, bytes_consumed) = RremoveMessage::deserialize(&rremove_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 7);
        assert_eq!(rremove.tag, original.tag);
        assert_eq!(tremove_bytes_written, 11); // Tremove is 11 bytes
    }

    // Tauth message tests
    #[test]
    fn test_tauth_message_creation() {
        let msg = TauthMessage::new(123, 456, "user".to_string(), "auth".to_string());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.afid, 456);
        assert_eq!(msg.uname, "user");
        assert_eq!(msg.aname, "auth");
        assert_eq!(msg.n_uname, 4);
    }

    #[test]
    fn test_tauth_serialize() {
        let msg = TauthMessage::new(123, 456, "user".to_string(), "auth".to_string());
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(27)); // 4 + 1 + 2 + 4 + (2+4) + (2+4) + 4 = 27 bytes total

        // Verify the serialized data
        // size[4] = 27 (little-endian)
        assert_eq!(buf[0], 27);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tauth (102)
        assert_eq!(buf[4], 102);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // afid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // uname[s] = "user" (length[2] + string[4])
        assert_eq!(buf[11], 4); // length = 4
        assert_eq!(buf[12], 0);
        assert_eq!(&buf[13..17], b"user");

        // aname[s] = "auth" (length[2] + string[4])
        assert_eq!(buf[17], 4); // length = 4
        assert_eq!(buf[18], 0);
        assert_eq!(&buf[19..23], b"auth");

        // n_uname[4] = 4 (little-endian)
        assert_eq!(buf[23], 4);
        assert_eq!(buf[24], 0);
        assert_eq!(buf[25], 0);
        assert_eq!(buf[26], 0);
    }

    #[test]
    fn test_tauth_serialize_buffer_too_small() {
        let msg = TauthMessage::new(123, 456, "user".to_string(), "auth".to_string());
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TauthError::BufferTooSmall));
    }

    #[test]
    fn test_tauth_serialize_uname_count_mismatch() {
        let mut msg = TauthMessage::new(123, 456, "user".to_string(), "auth".to_string());
        msg.n_uname = 5; // Wrong count
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TauthError::UnameCountMismatch));
    }

    #[test]
    fn test_tauth_send() {
        let msg = TauthMessage::new(123, 456, "user".to_string(), "auth".to_string());

        // Test that send_tauth doesn't panic and returns a result
        let result = msg.send_tauth();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TauthError::BufferTooSmall
                        | TauthError::StringTooLong
                        | TauthError::UnameCountMismatch
                        | TauthError::InvalidUtf8
                        | TauthError::InternalError
                ));
            }
        }
    }

    // Rauth message tests
    #[test]
    fn test_rauth_message_creation() {
        let qid = Qid::new(P9QidType::Qtfile as u8, 1, 0x12345678);
        let msg = RauthMessage::new(123, qid);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.aqid.qtype, P9QidType::Qtfile as u8);
        assert_eq!(msg.aqid.version, 1);
        assert_eq!(msg.aqid.path, 0x12345678);
    }

    #[test]
    fn test_rauth_deserialize() {
        // Create a proper Rauth message buffer
        let mut buf = [0u8; 32];

        // Write size[4] = 20 (little-endian) - 4 + 1 + 2 + 13 = 20
        buf[0] = 20;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rauth (103)
        buf[4] = P9MsgType::Rauth as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write aqid[13] - type[1] version[4] path[8]
        buf[7] = 0x80; // Qtdir type
        buf[8] = 1; // version = 1 (little-endian)
        buf[9] = 0;
        buf[10] = 0;
        buf[11] = 0;
        buf[12] = 0x78; // path = 0x12345678 (little-endian)
        buf[13] = 0x56;
        buf[14] = 0x34;
        buf[15] = 0x12;
        buf[16] = 0;
        buf[17] = 0;
        buf[18] = 0;
        buf[19] = 0;

        // Deserialize as Rauth
        let (rauth, bytes_consumed) = RauthMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 20);
        assert_eq!(rauth.tag, 123);
        assert_eq!(rauth.aqid.qtype, 0x80);
        assert_eq!(rauth.aqid.version, 1);
        assert_eq!(rauth.aqid.path, 0x12345678);
    }

    #[test]
    fn test_rauth_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RauthMessage::deserialize(&buf);
        assert_eq!(result, Err(RauthError::BufferTooSmall));
    }

    #[test]
    fn test_rauth_deserialize_invalid_message_type() {
        // Create a valid Tauth message but don't change the type
        let tauth = TauthMessage::new(123, 456, "user".to_string(), "auth".to_string());
        let mut buf = [0u8; 64];
        tauth.serialize(&mut buf).unwrap();

        // Try to deserialize as Rauth (should fail because type is Tauth)
        let result = RauthMessage::deserialize(&buf);
        assert_eq!(result, Err(RauthError::InvalidMessageType));
    }

    // Roundtrip tests for Tauth/Rauth
    #[test]
    fn test_roundtrip_tauth_rauth() {
        // Create a Tauth message
        let original = TauthMessage::new(456, 789, "testuser".to_string(), "testauth".to_string());
        let mut tauth_buf = [0u8; 64];
        let tauth_bytes_written = original.serialize(&mut tauth_buf).unwrap();

        // Create a separate Rauth message with the same tag
        let qid = Qid::new(P9QidType::Qtfile as u8, 1, 0x12345678);
        let _rauth_msg = RauthMessage::new(original.tag, qid);
        let mut rauth_buf = [0u8; 32];

        // Manually create Rauth buffer
        // Write size[4] = 20 (little-endian)
        rauth_buf[0] = 20;
        rauth_buf[1] = 0;
        rauth_buf[2] = 0;
        rauth_buf[3] = 0;

        // Write message type[1] = Rauth (103)
        rauth_buf[4] = P9MsgType::Rauth as u8;

        // Write tag[2] = 456 (little-endian)
        rauth_buf[5] = (456 & 0xff) as u8;
        rauth_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write aqid[13] - type[1] version[4] path[8]
        rauth_buf[7] = P9QidType::Qtfile as u8;
        rauth_buf[8] = 1; // version = 1 (little-endian)
        rauth_buf[9] = 0;
        rauth_buf[10] = 0;
        rauth_buf[11] = 0;
        rauth_buf[12] = 0x78; // path = 0x12345678 (little-endian)
        rauth_buf[13] = 0x56;
        rauth_buf[14] = 0x34;
        rauth_buf[15] = 0x12;
        rauth_buf[16] = 0;
        rauth_buf[17] = 0;
        rauth_buf[18] = 0;
        rauth_buf[19] = 0;

        // Deserialize as Rauth
        let (rauth, bytes_consumed) = RauthMessage::deserialize(&rauth_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 20);
        assert_eq!(rauth.tag, original.tag);
        assert_eq!(rauth.aqid.qtype, P9QidType::Qtfile as u8);
        assert_eq!(rauth.aqid.version, 1);
        assert_eq!(rauth.aqid.path, 0x12345678);
        assert_eq!(tauth_bytes_written, 35); // Tauth is 35 bytes (4+1+2+4+(2+8)+(2+8)+4)
    }

    // Tattach message tests
    #[test]
    fn test_tattach_message_creation() {
        let msg = TattachMessage::new(123, 456, 789, "user".to_string(), "attach".to_string());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.afid, 789);
        assert_eq!(msg.uname, "user");
        assert_eq!(msg.aname, "attach");
        assert_eq!(msg.n_uname, 4);
    }

    #[test]
    fn test_tattach_serialize() {
        let msg = TattachMessage::new(123, 456, 789, "user".to_string(), "attach".to_string());
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(33)); // 4 + 1 + 2 + 4 + 4 + (2+4) + (2+6) + 4 = 33 bytes total

        // Verify the serialized data
        // size[4] = 33 (little-endian)
        assert_eq!(buf[0], 33);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tattach (104)
        assert_eq!(buf[4], 104);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // afid[4] = 789 (little-endian)
        assert_eq!(buf[11], 21); // 789 & 0xff = 21
        assert_eq!(buf[12], 3); // (789 >> 8) & 0xff = 3
        assert_eq!(buf[13], 0);
        assert_eq!(buf[14], 0);

        // uname[s] = "user" (length[2] + string[4])
        assert_eq!(buf[15], 4); // length = 4
        assert_eq!(buf[16], 0);
        assert_eq!(&buf[17..21], b"user");

        // aname[s] = "attach" (length[2] + string[6])
        assert_eq!(buf[21], 6); // length = 6
        assert_eq!(buf[22], 0);
        assert_eq!(&buf[23..29], b"attach");

        // n_uname[4] = 4 (little-endian)
        assert_eq!(buf[29], 4);
        assert_eq!(buf[30], 0);
        assert_eq!(buf[31], 0);
        assert_eq!(buf[32], 0);
    }

    #[test]
    fn test_tattach_serialize_buffer_too_small() {
        let msg = TattachMessage::new(123, 456, 789, "user".to_string(), "attach".to_string());
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TattachError::BufferTooSmall));
    }

    #[test]
    fn test_tattach_serialize_uname_count_mismatch() {
        let mut msg = TattachMessage::new(123, 456, 789, "user".to_string(), "attach".to_string());
        msg.n_uname = 5; // Wrong count
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TattachError::UnameCountMismatch));
    }

    #[test]
    fn test_tattach_send() {
        let msg = TattachMessage::new(123, 456, 789, "user".to_string(), "attach".to_string());

        // Test that send_tattach doesn't panic and returns a result
        let result = msg.send_tattach();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TattachError::BufferTooSmall
                        | TattachError::StringTooLong
                        | TattachError::UnameCountMismatch
                        | TattachError::InvalidUtf8
                        | TattachError::InternalError
                ));
            }
        }
    }

    // Rattach message tests
    #[test]
    fn test_rattach_message_creation() {
        let qid = Qid::new(P9QidType::Qtdir as u8, 1, 0x12345678);
        let msg = RattachMessage::new(123, qid);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.qid.qtype, P9QidType::Qtdir as u8);
        assert_eq!(msg.qid.version, 1);
        assert_eq!(msg.qid.path, 0x12345678);
    }

    #[test]
    fn test_rattach_deserialize() {
        // Create a proper Rattach message buffer
        let mut buf = [0u8; 32];

        // Write size[4] = 20 (little-endian) - 4 + 1 + 2 + 13 = 20
        buf[0] = 20;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rattach (105)
        buf[4] = P9MsgType::Rattach as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write qid[13] - type[1] version[4] path[8]
        buf[7] = 0x80; // Qtdir type
        buf[8] = 1; // version = 1 (little-endian)
        buf[9] = 0;
        buf[10] = 0;
        buf[11] = 0;
        buf[12] = 0x78; // path = 0x12345678 (little-endian)
        buf[13] = 0x56;
        buf[14] = 0x34;
        buf[15] = 0x12;
        buf[16] = 0;
        buf[17] = 0;
        buf[18] = 0;
        buf[19] = 0;

        // Deserialize as Rattach
        let (rattach, bytes_consumed) = RattachMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 20);
        assert_eq!(rattach.tag, 123);
        assert_eq!(rattach.qid.qtype, 0x80);
        assert_eq!(rattach.qid.version, 1);
        assert_eq!(rattach.qid.path, 0x12345678);
    }

    #[test]
    fn test_rattach_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RattachMessage::deserialize(&buf);
        assert_eq!(result, Err(RattachError::BufferTooSmall));
    }

    #[test]
    fn test_rattach_deserialize_invalid_message_type() {
        // Create a valid Tattach message but don't change the type
        let tattach = TattachMessage::new(123, 456, 789, "user".to_string(), "attach".to_string());
        let mut buf = [0u8; 64];
        tattach.serialize(&mut buf).unwrap();

        // Try to deserialize as Rattach (should fail because type is Tattach)
        let result = RattachMessage::deserialize(&buf);
        assert_eq!(result, Err(RattachError::InvalidMessageType));
    }

    // Roundtrip tests for Tattach/Rattach
    #[test]
    fn test_roundtrip_tattach_rattach() {
        // Create a Tattach message
        let original = TattachMessage::new(
            456,
            789,
            1011,
            "testuser".to_string(),
            "testattach".to_string(),
        );
        let mut tattach_buf = [0u8; 64];
        let tattach_bytes_written = original.serialize(&mut tattach_buf).unwrap();

        // Create a separate Rattach message with the same tag
        let qid = Qid::new(P9QidType::Qtdir as u8, 1, 0x12345678);
        let _rattach_msg = RattachMessage::new(original.tag, qid);
        let mut rattach_buf = [0u8; 32];

        // Manually create Rattach buffer
        // Write size[4] = 20 (little-endian)
        rattach_buf[0] = 20;
        rattach_buf[1] = 0;
        rattach_buf[2] = 0;
        rattach_buf[3] = 0;

        // Write message type[1] = Rattach (105)
        rattach_buf[4] = P9MsgType::Rattach as u8;

        // Write tag[2] = 456 (little-endian)
        rattach_buf[5] = (456 & 0xff) as u8;
        rattach_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write qid[13] - type[1] version[4] path[8]
        rattach_buf[7] = P9QidType::Qtdir as u8;
        rattach_buf[8] = 1; // version = 1 (little-endian)
        rattach_buf[9] = 0;
        rattach_buf[10] = 0;
        rattach_buf[11] = 0;
        rattach_buf[12] = 0x78; // path = 0x12345678 (little-endian)
        rattach_buf[13] = 0x56;
        rattach_buf[14] = 0x34;
        rattach_buf[15] = 0x12;
        rattach_buf[16] = 0;
        rattach_buf[17] = 0;
        rattach_buf[18] = 0;
        rattach_buf[19] = 0;

        // Deserialize as Rattach
        let (rattach, bytes_consumed) = RattachMessage::deserialize(&rattach_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 20);
        assert_eq!(rattach.tag, original.tag);
        assert_eq!(rattach.qid.qtype, P9QidType::Qtdir as u8);
        assert_eq!(rattach.qid.version, 1);
        assert_eq!(rattach.qid.path, 0x12345678);
        assert_eq!(tattach_bytes_written, 41); // Tattach is 41 bytes (4+1+2+4+4+(2+8)+(2+10)+4)
    }

    // Rlerror message tests
    #[test]
    fn test_rlerror_message_creation() {
        let msg = RlerrorMessage::new(123, 2); // ENOENT error
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.ecode, 2);
    }

    #[test]
    fn test_rlerror_deserialize() {
        // Create a proper Rlerror message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 11 (little-endian) - 4 + 1 + 2 + 4 = 11
        buf[0] = 11;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = RLerror (7)
        buf[4] = P9MsgType::RLerror as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write ecode[4] = 2 (ENOENT) (little-endian)
        buf[7] = 2;
        buf[8] = 0;
        buf[9] = 0;
        buf[10] = 0;

        // Deserialize as Rlerror
        let (rlerror, bytes_consumed) = RlerrorMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 11);
        assert_eq!(rlerror.tag, 123);
        assert_eq!(rlerror.ecode, 2);
    }

    #[test]
    fn test_rlerror_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RlerrorMessage::deserialize(&buf);
        assert_eq!(result, Err(RlerrorError::BufferTooSmall));
    }

    #[test]
    fn test_rlerror_deserialize_invalid_message_type() {
        // Create a valid Tattach message but don't change the type
        let tattach = TattachMessage::new(123, 456, 789, "user".to_string(), "attach".to_string());
        let mut buf = [0u8; 64];
        tattach.serialize(&mut buf).unwrap();

        // Try to deserialize as Rlerror (should fail because type is Tattach)
        let result = RlerrorMessage::deserialize(&buf);
        assert_eq!(result, Err(RlerrorError::InvalidMessageType));
    }

    #[test]
    fn test_rlerror_deserialize_common_error_codes() {
        // Test common Linux error codes
        let error_codes = [
            (1, "EPERM"),   // Operation not permitted
            (2, "ENOENT"),  // No such file or directory
            (5, "EIO"),     // I/O error
            (13, "EACCES"), // Permission denied
            (22, "EINVAL"), // Invalid argument
        ];

        for (ecode, _name) in error_codes.iter() {
            let mut buf = [0u8; 16];

            // Write size[4] = 11 (little-endian)
            buf[0] = 11;
            buf[1] = 0;
            buf[2] = 0;
            buf[3] = 0;

            // Write message type[1] = RLerror (7)
            buf[4] = P9MsgType::RLerror as u8;

            // Write tag[2] = 123 (little-endian)
            buf[5] = 123;
            buf[6] = 0;

            // Write ecode[4] (little-endian)
            buf[7] = *ecode as u8;
            buf[8] = 0;
            buf[9] = 0;
            buf[10] = 0;

            // Deserialize as Rlerror
            let (rlerror, bytes_consumed) = RlerrorMessage::deserialize(&buf).unwrap();

            assert_eq!(bytes_consumed, 11);
            assert_eq!(rlerror.tag, 123);
            assert_eq!(rlerror.ecode, *ecode);
        }
    }

    // Tstatfs message tests
    #[test]
    fn test_tstatfs_message_creation() {
        let msg = TstatfsMessage::new(123, 456);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
    }

    #[test]
    fn test_tstatfs_serialize() {
        let msg = TstatfsMessage::new(123, 456);
        let mut buf = [0u8; 16];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(11)); // 4 + 1 + 2 + 4 = 11 bytes total

        // Verify the serialized data
        // size[4] = 11 (little-endian)
        assert_eq!(buf[0], 11);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tstatfs (8)
        assert_eq!(buf[4], 8);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);
    }

    #[test]
    fn test_tstatfs_serialize_buffer_too_small() {
        let msg = TstatfsMessage::new(123, 456);
        let mut buf = [0u8; 5]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TstatfsError::BufferTooSmall));
    }

    #[test]
    fn test_tstatfs_send() {
        let msg = TstatfsMessage::new(123, 456);

        // Test that send_tstatfs doesn't panic and returns a result
        let result = msg.send_tstatfs();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TstatfsError::BufferTooSmall | TstatfsError::InternalError
                ));
            }
        }
    }

    // Rstatfs message tests
    #[test]
    fn test_rstatfs_message_creation() {
        let msg = RstatfsMessage::new(
            123,          // tag
            0xEF53,       // type (ext4 filesystem)
            4096,         // bsize
            1000000,      // blocks
            500000,       // bfree
            450000,       // bavail
            10000,        // files
            5000,         // ffree
            0x1234567890, // fsid
            255,          // namelen
        );
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.type_, 0xEF53);
        assert_eq!(msg.bsize, 4096);
        assert_eq!(msg.blocks, 1000000);
        assert_eq!(msg.bfree, 500000);
        assert_eq!(msg.bavail, 450000);
        assert_eq!(msg.files, 10000);
        assert_eq!(msg.ffree, 5000);
        assert_eq!(msg.fsid, 0x1234567890);
        assert_eq!(msg.namelen, 255);
    }

    #[test]
    fn test_rstatfs_deserialize() {
        // Create a proper Rstatfs message buffer
        let mut buf = [0u8; 80];

        // Write size[4] = 67 (little-endian) - 4 + 1 + 2 + 4 + 4 + 8 + 8 + 8 + 8 + 8 + 8 + 4 = 67
        buf[0] = 67;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rstatfs (9)
        buf[4] = P9MsgType::Rstatfs as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write type[4] = 0xEF53 (ext4) (little-endian)
        buf[7] = 0x53;
        buf[8] = 0xEF;
        buf[9] = 0;
        buf[10] = 0;

        // Write bsize[4] = 4096 (little-endian)
        buf[11] = 0;
        buf[12] = 16;
        buf[13] = 0;
        buf[14] = 0;

        // Write blocks[8] = 1000000 (little-endian)
        buf[15] = 64;
        buf[16] = 66;
        buf[17] = 15;
        buf[18] = 0;
        buf[19] = 0;
        buf[20] = 0;
        buf[21] = 0;
        buf[22] = 0;

        // Write bfree[8] = 500000 (little-endian)
        buf[23] = 32;
        buf[24] = 161;
        buf[25] = 7;
        buf[26] = 0;
        buf[27] = 0;
        buf[28] = 0;
        buf[29] = 0;
        buf[30] = 0;

        // Write bavail[8] = 450000 (little-endian)
        buf[31] = 208; // 0xd0
        buf[32] = 221; // 0xdd
        buf[33] = 6; // 0x06
        buf[34] = 0;
        buf[35] = 0;
        buf[36] = 0;
        buf[37] = 0;
        buf[38] = 0;

        // Write files[8] = 10000 (little-endian)
        buf[39] = 16;
        buf[40] = 39;
        buf[41] = 0;
        buf[42] = 0;
        buf[43] = 0;
        buf[44] = 0;
        buf[45] = 0;
        buf[46] = 0;

        // Write ffree[8] = 5000 (little-endian)
        buf[47] = 136;
        buf[48] = 19;
        buf[49] = 0;
        buf[50] = 0;
        buf[51] = 0;
        buf[52] = 0;
        buf[53] = 0;
        buf[54] = 0;

        // Write fsid[8] = 0x1234567890 (little-endian)
        buf[55] = 0x90;
        buf[56] = 0x78;
        buf[57] = 0x56;
        buf[58] = 0x34;
        buf[59] = 0x12;
        buf[60] = 0;
        buf[61] = 0;
        buf[62] = 0;

        // Write namelen[4] = 255 (little-endian)
        buf[63] = 255;
        buf[64] = 0;
        buf[65] = 0;
        buf[66] = 0;

        // Deserialize as Rstatfs
        let (rstatfs, bytes_consumed) = RstatfsMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 67);
        assert_eq!(rstatfs.tag, 123);
        assert_eq!(rstatfs.type_, 0xEF53);
        assert_eq!(rstatfs.bsize, 4096);
        assert_eq!(rstatfs.blocks, 1000000);
        assert_eq!(rstatfs.bfree, 500000);
        assert_eq!(rstatfs.bavail, 450000);
        assert_eq!(rstatfs.files, 10000);
        assert_eq!(rstatfs.ffree, 5000);
        assert_eq!(rstatfs.fsid, 0x1234567890);
        assert_eq!(rstatfs.namelen, 255);
    }

    #[test]
    fn test_rstatfs_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RstatfsMessage::deserialize(&buf);
        assert_eq!(result, Err(RstatfsError::BufferTooSmall));
    }

    #[test]
    fn test_rstatfs_deserialize_invalid_message_type() {
        // Create a valid Tstatfs message but don't change the type
        let tstatfs = TstatfsMessage::new(123, 456);
        let mut buf = [0u8; 16];
        tstatfs.serialize(&mut buf).unwrap();

        // Try to deserialize as Rstatfs (should fail because type is Tstatfs)
        let result = RstatfsMessage::deserialize(&buf);
        assert_eq!(result, Err(RstatfsError::InvalidMessageType));
    }

    // Roundtrip tests for Tstatfs/Rstatfs
    #[test]
    fn test_roundtrip_tstatfs_rstatfs() {
        // Create a Tstatfs message
        let original = TstatfsMessage::new(456, 789);
        let mut tstatfs_buf = [0u8; 16];
        let tstatfs_bytes_written = original.serialize(&mut tstatfs_buf).unwrap();

        // Create a separate Rstatfs message with the same tag
        let _rstatfs_msg = RstatfsMessage::new(
            original.tag, // tag
            0xEF53,       // type (ext4)
            4096,         // bsize
            1000000,      // blocks
            500000,       // bfree
            450000,       // bavail
            10000,        // files
            5000,         // ffree
            0x1234567890, // fsid
            255,          // namelen
        );
        let mut rstatfs_buf = [0u8; 80];

        // Manually create Rstatfs buffer
        // Write size[4] = 67 (little-endian)
        rstatfs_buf[0] = 67;
        rstatfs_buf[1] = 0;
        rstatfs_buf[2] = 0;
        rstatfs_buf[3] = 0;

        // Write message type[1] = Rstatfs (9)
        rstatfs_buf[4] = P9MsgType::Rstatfs as u8;

        // Write tag[2] = 456 (little-endian)
        rstatfs_buf[5] = (456 & 0xff) as u8;
        rstatfs_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write type[4] = 0xEF53 (ext4) (little-endian)
        rstatfs_buf[7] = 0x53;
        rstatfs_buf[8] = 0xEF;
        rstatfs_buf[9] = 0;
        rstatfs_buf[10] = 0;

        // Write bsize[4] = 4096 (little-endian)
        rstatfs_buf[11] = 0;
        rstatfs_buf[12] = 16;
        rstatfs_buf[13] = 0;
        rstatfs_buf[14] = 0;

        // Write blocks[8] = 1000000 (little-endian)
        rstatfs_buf[15] = 64;
        rstatfs_buf[16] = 66;
        rstatfs_buf[17] = 15;
        rstatfs_buf[18] = 0;
        rstatfs_buf[19] = 0;
        rstatfs_buf[20] = 0;
        rstatfs_buf[21] = 0;
        rstatfs_buf[22] = 0;

        // Write bfree[8] = 500000 (little-endian)
        rstatfs_buf[23] = 32;
        rstatfs_buf[24] = 161;
        rstatfs_buf[25] = 7;
        rstatfs_buf[26] = 0;
        rstatfs_buf[27] = 0;
        rstatfs_buf[28] = 0;
        rstatfs_buf[29] = 0;
        rstatfs_buf[30] = 0;

        // Write bavail[8] = 450000 (little-endian)
        rstatfs_buf[31] = 208; // 0xd0
        rstatfs_buf[32] = 221; // 0xdd
        rstatfs_buf[33] = 6; // 0x06
        rstatfs_buf[34] = 0;
        rstatfs_buf[35] = 0;
        rstatfs_buf[36] = 0;
        rstatfs_buf[37] = 0;
        rstatfs_buf[38] = 0;

        // Write files[8] = 10000 (little-endian)
        rstatfs_buf[39] = 16;
        rstatfs_buf[40] = 39;
        rstatfs_buf[41] = 0;
        rstatfs_buf[42] = 0;
        rstatfs_buf[43] = 0;
        rstatfs_buf[44] = 0;
        rstatfs_buf[45] = 0;
        rstatfs_buf[46] = 0;

        // Write ffree[8] = 5000 (little-endian)
        rstatfs_buf[47] = 136;
        rstatfs_buf[48] = 19;
        rstatfs_buf[49] = 0;
        rstatfs_buf[50] = 0;
        rstatfs_buf[51] = 0;
        rstatfs_buf[52] = 0;
        rstatfs_buf[53] = 0;
        rstatfs_buf[54] = 0;

        // Write fsid[8] = 0x1234567890 (little-endian)
        rstatfs_buf[55] = 0x90;
        rstatfs_buf[56] = 0x78;
        rstatfs_buf[57] = 0x56;
        rstatfs_buf[58] = 0x34;
        rstatfs_buf[59] = 0x12;
        rstatfs_buf[60] = 0;
        rstatfs_buf[61] = 0;
        rstatfs_buf[62] = 0;

        // Write namelen[4] = 255 (little-endian)
        rstatfs_buf[63] = 255;
        rstatfs_buf[64] = 0;
        rstatfs_buf[65] = 0;
        rstatfs_buf[66] = 0;

        // Deserialize as Rstatfs
        let (rstatfs, bytes_consumed) = RstatfsMessage::deserialize(&rstatfs_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 67);
        assert_eq!(rstatfs.tag, original.tag);
        assert_eq!(rstatfs.type_, 0xEF53);
        assert_eq!(rstatfs.bsize, 4096);
        assert_eq!(rstatfs.blocks, 1000000);
        assert_eq!(rstatfs.bfree, 500000);
        assert_eq!(rstatfs.bavail, 450000);
        assert_eq!(rstatfs.files, 10000);
        assert_eq!(rstatfs.ffree, 5000);
        assert_eq!(rstatfs.fsid, 0x1234567890);
        assert_eq!(rstatfs.namelen, 255);
        assert_eq!(tstatfs_bytes_written, 11); // Tstatfs is 11 bytes
    }

    // Tgetattr message tests
    #[test]
    fn test_tgetattr_message_creation() {
        let msg = TgetattrMessage::new(123, 456, 0xFFFFFFFF);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.request_mask, 0xFFFFFFFF);
    }

    #[test]
    fn test_tgetattr_serialize() {
        let msg = TgetattrMessage::new(123, 456, 0xFFFFFFFF);
        let mut buf = [0u8; 32];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(19)); // 4 + 1 + 2 + 4 + 8 = 19 bytes total

        // Verify the serialized data
        // size[4] = 19 (little-endian)
        assert_eq!(buf[0], 19);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tgetattr (24)
        assert_eq!(buf[4], 24);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // request_mask[8] = 0xFFFFFFFF (little-endian)
        assert_eq!(buf[11], 0xFF);
        assert_eq!(buf[12], 0xFF);
        assert_eq!(buf[13], 0xFF);
        assert_eq!(buf[14], 0xFF);
        assert_eq!(buf[15], 0);
        assert_eq!(buf[16], 0);
        assert_eq!(buf[17], 0);
        assert_eq!(buf[18], 0);
    }

    #[test]
    fn test_tgetattr_serialize_buffer_too_small() {
        let msg = TgetattrMessage::new(123, 456, 0xFFFFFFFF);
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TgetattrError::BufferTooSmall));
    }

    #[test]
    fn test_tgetattr_send() {
        let msg = TgetattrMessage::new(123, 456, 0xFFFFFFFF);

        // Test that send_tgetattr doesn't panic and returns a result
        let result = msg.send_tgetattr();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TgetattrError::BufferTooSmall | TgetattrError::InternalError
                ));
            }
        }
    }

    // Rgetattr message tests
    #[test]
    fn test_rgetattr_message_creation() {
        let qid = Qid {
            qtype: P9QidType::Qtdir as u8,
            version: 1,
            path: 0x12345678,
        };
        let msg = RgetattrMessage::new(
            123,        // tag
            0xFFFFFFFF, // valid
            qid,        // qid
            0o755,      // mode
            1000,       // uid
            1000,       // gid
            1,          // nlink
            0,          // rdev
            1024,       // size
            4096,       // blksize
            1,          // blocks
            1640995200, // atime_sec
            0,          // atime_nsec
            1640995200, // mtime_sec
            0,          // mtime_nsec
            1640995200, // ctime_sec
            0,          // ctime_nsec
            1640995200, // btime_sec
            0,          // btime_nsec
            1,          // gen
            1,          // data_version
        );
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.valid, 0xFFFFFFFF);
        assert_eq!(msg.qid.qtype, P9QidType::Qtdir as u8);
        assert_eq!(msg.mode, 0o755);
        assert_eq!(msg.uid, 1000);
        assert_eq!(msg.gid, 1000);
        assert_eq!(msg.size, 1024);
    }

    #[test]
    fn test_rgetattr_deserialize() {
        // Create a proper Rgetattr message buffer
        let mut buf = [0u8; 200];

        // Write size[4] = 160 (little-endian) - 4 + 1 + 2 + 8 + 13 + 4 + 4 + 4 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 + 8 = 160
        buf[0] = 160;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rgetattr (25)
        buf[4] = P9MsgType::Rgetattr as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write valid[8] = 0xFFFFFFFF (little-endian)
        buf[7] = 0xFF;
        buf[8] = 0xFF;
        buf[9] = 0xFF;
        buf[10] = 0xFF;
        buf[11] = 0;
        buf[12] = 0;
        buf[13] = 0;
        buf[14] = 0;

        // Write qid[13] - type[1] version[4] path[8]
        buf[15] = P9QidType::Qtdir as u8; // type
        buf[16] = 1; // version = 1 (little-endian)
        buf[17] = 0;
        buf[18] = 0;
        buf[19] = 0;
        buf[20] = 0x78; // path = 0x12345678 (little-endian)
        buf[21] = 0x56;
        buf[22] = 0x34;
        buf[23] = 0x12;
        buf[24] = 0;
        buf[25] = 0;
        buf[26] = 0;
        buf[27] = 0;

        // Write mode[4] = 0o755 (little-endian)
        let mode_bytes = (0o755u32).to_le_bytes();
        buf[28..32].copy_from_slice(&mode_bytes);

        // Write uid[4] = 1000 (little-endian)
        let uid_bytes = (1000u32).to_le_bytes();
        buf[32..36].copy_from_slice(&uid_bytes);

        // Write gid[4] = 1000 (little-endian)
        let gid_bytes = (1000u32).to_le_bytes();
        buf[36..40].copy_from_slice(&gid_bytes);

        // Write nlink[8] = 1 (little-endian)
        let nlink_bytes = (1u64).to_le_bytes();
        buf[40..48].copy_from_slice(&nlink_bytes);

        // Write rdev[8] = 0 (little-endian)
        let rdev_bytes = (0u64).to_le_bytes();
        buf[48..56].copy_from_slice(&rdev_bytes);

        // Write size[8] = 1024 (little-endian)
        let size_bytes = (1024u64).to_le_bytes();
        buf[56..64].copy_from_slice(&size_bytes);

        // Write blksize[8] = 4096 (little-endian)
        let blksize_bytes = (4096u64).to_le_bytes();
        buf[64..72].copy_from_slice(&blksize_bytes);

        // Write blocks[8] = 1 (little-endian)
        let blocks_bytes = (1u64).to_le_bytes();
        buf[72..80].copy_from_slice(&blocks_bytes);

        // Write atime_sec[8] = 1640995200 (little-endian)
        let atime_sec_bytes = (1640995200u64).to_le_bytes();
        buf[80..88].copy_from_slice(&atime_sec_bytes);

        // Write atime_nsec[8] = 0 (little-endian)
        let atime_nsec_bytes = (0u64).to_le_bytes();
        buf[88..96].copy_from_slice(&atime_nsec_bytes);

        // Write mtime_sec[8] = 1640995200 (little-endian)
        let mtime_sec_bytes = (1640995200u64).to_le_bytes();
        buf[96..104].copy_from_slice(&mtime_sec_bytes);

        // Write mtime_nsec[8] = 0 (little-endian)
        let mtime_nsec_bytes = (0u64).to_le_bytes();
        buf[104..112].copy_from_slice(&mtime_nsec_bytes);

        // Write ctime_sec[8] = 1640995200 (little-endian)
        let ctime_sec_bytes = (1640995200u64).to_le_bytes();
        buf[112..120].copy_from_slice(&ctime_sec_bytes);

        // Write ctime_nsec[8] = 0 (little-endian)
        let ctime_nsec_bytes = (0u64).to_le_bytes();
        buf[120..128].copy_from_slice(&ctime_nsec_bytes);

        // Write btime_sec[8] = 1640995200 (little-endian)
        let btime_sec_bytes = (1640995200u64).to_le_bytes();
        buf[128..136].copy_from_slice(&btime_sec_bytes);

        // Write btime_nsec[8] = 0 (little-endian)
        let btime_nsec_bytes = (0u64).to_le_bytes();
        buf[136..144].copy_from_slice(&btime_nsec_bytes);

        // Write gen[8] = 1 (little-endian)
        let gen_bytes = (1u64).to_le_bytes();
        buf[144..152].copy_from_slice(&gen_bytes);

        // Write data_version[8] = 1 (little-endian)
        let data_version_bytes = (1u64).to_le_bytes();
        buf[152..160].copy_from_slice(&data_version_bytes);

        // Deserialize as Rgetattr
        let (rgetattr, bytes_consumed) = RgetattrMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 160);
        assert_eq!(rgetattr.tag, 123);
        assert_eq!(rgetattr.valid, 0xFFFFFFFF);
        assert_eq!(rgetattr.qid.qtype, P9QidType::Qtdir as u8);
        assert_eq!(rgetattr.qid.version, 1);
        assert_eq!(rgetattr.qid.path, 0x12345678);
        assert_eq!(rgetattr.mode, 0o755);
        assert_eq!(rgetattr.uid, 1000);
        assert_eq!(rgetattr.gid, 1000);
        assert_eq!(rgetattr.nlink, 1);
        assert_eq!(rgetattr.rdev, 0);
        assert_eq!(rgetattr.size, 1024);
        assert_eq!(rgetattr.blksize, 4096);
        assert_eq!(rgetattr.blocks, 1);
        assert_eq!(rgetattr.atime_sec, 1640995200);
        assert_eq!(rgetattr.atime_nsec, 0);
        assert_eq!(rgetattr.mtime_sec, 1640995200);
        assert_eq!(rgetattr.mtime_nsec, 0);
        assert_eq!(rgetattr.ctime_sec, 1640995200);
        assert_eq!(rgetattr.ctime_nsec, 0);
        assert_eq!(rgetattr.btime_sec, 1640995200);
        assert_eq!(rgetattr.btime_nsec, 0);
        assert_eq!(rgetattr.gen_, 1);
        assert_eq!(rgetattr.data_version, 1);
    }

    #[test]
    fn test_rgetattr_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RgetattrMessage::deserialize(&buf);
        assert_eq!(result, Err(RgetattrError::BufferTooSmall));
    }

    #[test]
    fn test_rgetattr_deserialize_invalid_message_type() {
        // Create a valid Tgetattr message but don't change the type
        let tgetattr = TgetattrMessage::new(123, 456, 0xFFFFFFFF);
        let mut buf = [0u8; 32];
        tgetattr.serialize(&mut buf).unwrap();

        // Try to deserialize as Rgetattr (should fail because type is Tgetattr)
        let result = RgetattrMessage::deserialize(&buf);
        assert_eq!(result, Err(RgetattrError::InvalidMessageType));
    }

    // Tsetattr message tests
    #[test]
    fn test_tsetattr_message_creation() {
        let msg = TsetattrMessage::new(
            123,        // tag
            456,        // fid
            0xFFFFFFFF, // valid
            0o755,      // mode
            1000,       // uid
            1000,       // gid
            1024,       // size
            1640995200, // atime_sec
            0,          // atime_nsec
            1640995200, // mtime_sec
            0,          // mtime_nsec
        );
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.valid, 0xFFFFFFFF);
        assert_eq!(msg.mode, 0o755);
        assert_eq!(msg.uid, 1000);
        assert_eq!(msg.gid, 1000);
        assert_eq!(msg.size, 1024);
        assert_eq!(msg.atime_sec, 1640995200);
        assert_eq!(msg.mtime_sec, 1640995200);
    }

    #[test]
    fn test_tsetattr_serialize() {
        let msg = TsetattrMessage::new(
            123,        // tag
            456,        // fid
            0xFFFFFFFF, // valid
            0o755,      // mode
            1000,       // uid
            1000,       // gid
            1024,       // size
            1640995200, // atime_sec
            0,          // atime_nsec
            1640995200, // mtime_sec
            0,          // mtime_nsec
        );
        let mut buf = [0u8; 128];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(67)); // 4 + 1 + 2 + 4 + 4 + 4 + 4 + 4 + 8 + 8 + 8 + 8 + 8 = 67 bytes total

        // Verify the serialized data
        // size[4] = 67 (little-endian)
        assert_eq!(buf[0], 67);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tsetattr (26)
        assert_eq!(buf[4], 26);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // valid[4] = 0xFFFFFFFF (little-endian)
        assert_eq!(buf[11], 0xFF);
        assert_eq!(buf[12], 0xFF);
        assert_eq!(buf[13], 0xFF);
        assert_eq!(buf[14], 0xFF);

        // mode[4] = 0o755 (little-endian)
        let expected_mode_bytes = (0o755u32).to_le_bytes();
        assert_eq!(&buf[15..19], &expected_mode_bytes);

        // uid[4] = 1000 (little-endian)
        let expected_uid_bytes = (1000u32).to_le_bytes();
        assert_eq!(&buf[19..23], &expected_uid_bytes);

        // gid[4] = 1000 (little-endian)
        let expected_gid_bytes = (1000u32).to_le_bytes();
        assert_eq!(&buf[23..27], &expected_gid_bytes);

        // size[8] = 1024 (little-endian)
        let expected_size_bytes = (1024u64).to_le_bytes();
        assert_eq!(&buf[27..35], &expected_size_bytes);

        // atime_sec[8] = 1640995200 (little-endian)
        let expected_atime_sec_bytes = (1640995200u64).to_le_bytes();
        assert_eq!(&buf[35..43], &expected_atime_sec_bytes);

        // atime_nsec[8] = 0 (little-endian)
        let expected_atime_nsec_bytes = (0u64).to_le_bytes();
        assert_eq!(&buf[43..51], &expected_atime_nsec_bytes);

        // mtime_sec[8] = 1640995200 (little-endian)
        let expected_mtime_sec_bytes = (1640995200u64).to_le_bytes();
        assert_eq!(&buf[51..59], &expected_mtime_sec_bytes);

        // mtime_nsec[8] = 0 (little-endian)
        let expected_mtime_nsec_bytes = (0u64).to_le_bytes();
        assert_eq!(&buf[59..67], &expected_mtime_nsec_bytes);
    }

    #[test]
    fn test_tsetattr_serialize_buffer_too_small() {
        let msg = TsetattrMessage::new(
            123, 456, 0xFFFFFFFF, 0o755, 1000, 1000, 1024, 1640995200, 0, 1640995200, 0,
        );
        let mut buf = [0u8; 50]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TsetattrError::BufferTooSmall));
    }

    #[test]
    fn test_tsetattr_send() {
        let msg = TsetattrMessage::new(
            123, 456, 0xFFFFFFFF, 0o755, 1000, 1000, 1024, 1640995200, 0, 1640995200, 0,
        );

        // Test that send_tsetattr doesn't panic and returns a result
        let result = msg.send_tsetattr();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TsetattrError::BufferTooSmall | TsetattrError::InternalError
                ));
            }
        }
    }

    // Rsetattr message tests
    #[test]
    fn test_rsetattr_message_creation() {
        let msg = RsetattrMessage::new(123);
        assert_eq!(msg.tag, 123);
    }

    #[test]
    fn test_rsetattr_deserialize() {
        // Create a proper Rsetattr message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 7 (little-endian) - 4 + 1 + 2 = 7
        buf[0] = 7;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rsetattr (27)
        buf[4] = P9MsgType::Rsetattr as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Deserialize as Rsetattr
        let (rsetattr, bytes_consumed) = RsetattrMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 7);
        assert_eq!(rsetattr.tag, 123);
    }

    #[test]
    fn test_rsetattr_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RsetattrMessage::deserialize(&buf);
        assert_eq!(result, Err(RsetattrError::BufferTooSmall));
    }

    #[test]
    fn test_rsetattr_deserialize_invalid_message_type() {
        // Create a valid Tsetattr message but don't change the type
        let tsetattr = TsetattrMessage::new(
            123, 456, 0xFFFFFFFF, 0o755, 1000, 1000, 1024, 1640995200, 0, 1640995200, 0,
        );
        let mut buf = [0u8; 128];
        tsetattr.serialize(&mut buf).unwrap();

        // Try to deserialize as Rsetattr (should fail because type is Tsetattr)
        let result = RsetattrMessage::deserialize(&buf);
        assert_eq!(result, Err(RsetattrError::InvalidMessageType));
    }

    // Roundtrip tests for Tgetattr/Rgetattr and Tsetattr/Rsetattr
    #[test]
    fn test_roundtrip_tgetattr_rgetattr() {
        // Create a Tgetattr message
        let original = TgetattrMessage::new(456, 789, 0xFFFFFFFF);
        let mut tgetattr_buf = [0u8; 32];
        let tgetattr_bytes_written = original.serialize(&mut tgetattr_buf).unwrap();

        // Create a separate Rgetattr message with the same tag
        let qid = Qid {
            qtype: P9QidType::Qtdir as u8,
            version: 1,
            path: 0x12345678,
        };
        let _rgetattr_msg = RgetattrMessage::new(
            original.tag, // tag
            0xFFFFFFFF,   // valid
            qid,          // qid
            0o755,        // mode
            1000,         // uid
            1000,         // gid
            1,            // nlink
            0,            // rdev
            1024,         // size
            4096,         // blksize
            1,            // blocks
            1640995200,   // atime_sec
            0,            // atime_nsec
            1640995200,   // mtime_sec
            0,            // mtime_nsec
            1640995200,   // ctime_sec
            0,            // ctime_nsec
            1640995200,   // btime_sec
            0,            // btime_nsec
            1,            // gen
            1,            // data_version
        );
        let mut rgetattr_buf = [0u8; 200];

        // Manually create Rgetattr buffer (simplified version)
        // Write size[4] = 160 (little-endian)
        rgetattr_buf[0] = 160;
        rgetattr_buf[1] = 0;
        rgetattr_buf[2] = 0;
        rgetattr_buf[3] = 0;

        // Write message type[1] = Rgetattr (25)
        rgetattr_buf[4] = P9MsgType::Rgetattr as u8;

        // Write tag[2] = 456 (little-endian)
        rgetattr_buf[5] = (456 & 0xff) as u8;
        rgetattr_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write valid[8] = 0xFFFFFFFF (little-endian)
        for i in 7..11 {
            rgetattr_buf[i] = 0xFF;
        }
        for i in 11..15 {
            rgetattr_buf[i] = 0;
        }

        // Write qid[13] - type[1] version[4] path[8]
        rgetattr_buf[15] = P9QidType::Qtdir as u8;
        rgetattr_buf[16] = 1; // version = 1 (little-endian)
        rgetattr_buf[17] = 0;
        rgetattr_buf[18] = 0;
        rgetattr_buf[19] = 0;
        rgetattr_buf[20] = 0x78; // path = 0x12345678 (little-endian)
        rgetattr_buf[21] = 0x56;
        rgetattr_buf[22] = 0x34;
        rgetattr_buf[23] = 0x12;
        rgetattr_buf[24] = 0;
        rgetattr_buf[25] = 0;
        rgetattr_buf[26] = 0;
        rgetattr_buf[27] = 0;

        // Fill the rest with zeros for simplicity
        for i in 28..160 {
            rgetattr_buf[i] = 0;
        }

        // Deserialize as Rgetattr
        let (rgetattr, bytes_consumed) = RgetattrMessage::deserialize(&rgetattr_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 160);
        assert_eq!(rgetattr.tag, original.tag);
        assert_eq!(rgetattr.valid, 0xFFFFFFFF);
        assert_eq!(rgetattr.qid.qtype, P9QidType::Qtdir as u8);
        assert_eq!(rgetattr.qid.version, 1);
        assert_eq!(rgetattr.qid.path, 0x12345678);
        assert_eq!(tgetattr_bytes_written, 19); // Tgetattr is 19 bytes
    }

    #[test]
    fn test_roundtrip_tsetattr_rsetattr() {
        // Create a Tsetattr message
        let original = TsetattrMessage::new(
            456, 789, 0xFFFFFFFF, 0o755, 1000, 1000, 1024, 1640995200, 0, 1640995200, 0,
        );
        let mut tsetattr_buf = [0u8; 128];
        let tsetattr_bytes_written = original.serialize(&mut tsetattr_buf).unwrap();

        // Create a separate Rsetattr message with the same tag
        let _rsetattr_msg = RsetattrMessage::new(original.tag);
        let mut rsetattr_buf = [0u8; 16];

        // Manually create Rsetattr buffer
        // Write size[4] = 7 (little-endian)
        rsetattr_buf[0] = 7;
        rsetattr_buf[1] = 0;
        rsetattr_buf[2] = 0;
        rsetattr_buf[3] = 0;

        // Write message type[1] = Rsetattr (27)
        rsetattr_buf[4] = P9MsgType::Rsetattr as u8;

        // Write tag[2] = 456 (little-endian)
        rsetattr_buf[5] = (456 & 0xff) as u8;
        rsetattr_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Deserialize as Rsetattr
        let (rsetattr, bytes_consumed) = RsetattrMessage::deserialize(&rsetattr_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 7);
        assert_eq!(rsetattr.tag, original.tag);
        assert_eq!(tsetattr_bytes_written, 67); // Tsetattr is 67 bytes
    }

    // Txattrwalk message tests
    #[test]
    fn test_txattrwalk_message_creation() {
        let msg = TxattrwalkMessage::new(123, 456, 789, "user.test".to_string());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.newfid, 789);
        assert_eq!(msg.name, "user.test");
    }

    #[test]
    fn test_txattrwalk_serialize() {
        let msg = TxattrwalkMessage::new(123, 456, 789, "user.test".to_string());
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(26)); // 4 + 1 + 2 + 4 + 4 + (2+9) = 26 bytes total

        // Verify the serialized data
        // size[4] = 26 (little-endian)
        assert_eq!(buf[0], 26);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Txattrwalk (30)
        assert_eq!(buf[4], 30);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // newfid[4] = 789 (little-endian)
        assert_eq!(buf[11], 21); // 789 & 0xff = 21
        assert_eq!(buf[12], 3); // (789 >> 8) & 0xff = 3
        assert_eq!(buf[13], 0);
        assert_eq!(buf[14], 0);

        // name[s] = "user.test" (length[2] + string)
        assert_eq!(buf[15], 9); // length = 9
        assert_eq!(buf[16], 0);
        assert_eq!(&buf[17..26], b"user.test");
    }

    #[test]
    fn test_txattrwalk_serialize_buffer_too_small() {
        let msg = TxattrwalkMessage::new(123, 456, 789, "user.test".to_string());
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TxattrwalkError::BufferTooSmall));
    }

    #[test]
    fn test_txattrwalk_send() {
        let msg = TxattrwalkMessage::new(123, 456, 789, "user.test".to_string());

        // Test that send_txattrwalk doesn't panic and returns a result
        let result = msg.send_txattrwalk();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TxattrwalkError::BufferTooSmall | TxattrwalkError::InternalError
                ));
            }
        }
    }

    // Rxattrwalk message tests
    #[test]
    fn test_rxattrwalk_message_creation() {
        let msg = RxattrwalkMessage::new(123, 1024);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.size, 1024);
    }

    #[test]
    fn test_rxattrwalk_deserialize() {
        // Create a proper Rxattrwalk message buffer
        let mut buf = [0u8; 32];

        // Write size[4] = 15 (little-endian) - 4 + 1 + 2 + 8 = 15
        buf[0] = 15;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rxattrwalk (29)
        buf[4] = P9MsgType::Rxattrwalk as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write size[8] = 1024 (little-endian)
        let size_bytes = (1024u64).to_le_bytes();
        buf[7..15].copy_from_slice(&size_bytes);

        // Deserialize as Rxattrwalk
        let (rxattrwalk, bytes_consumed) = RxattrwalkMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 15);
        assert_eq!(rxattrwalk.tag, 123);
        assert_eq!(rxattrwalk.size, 1024);
    }

    #[test]
    fn test_rxattrwalk_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RxattrwalkMessage::deserialize(&buf);
        assert_eq!(result, Err(RxattrwalkError::BufferTooSmall));
    }

    #[test]
    fn test_rxattrwalk_deserialize_invalid_message_type() {
        // Create a valid Txattrwalk message but don't change the type
        let txattrwalk = TxattrwalkMessage::new(123, 456, 789, "user.test".to_string());
        let mut buf = [0u8; 64];
        txattrwalk.serialize(&mut buf).unwrap();

        // Try to deserialize as Rxattrwalk (should fail because type is Txattrwalk)
        let result = RxattrwalkMessage::deserialize(&buf);
        assert_eq!(result, Err(RxattrwalkError::InvalidMessageType));
    }

    // Txattrcreate message tests
    #[test]
    fn test_txattrcreate_message_creation() {
        let msg = TxattrcreateMessage::new(123, 456, "user.test".to_string(), 1024, 0x1);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.name, "user.test");
        assert_eq!(msg.attr_size, 1024);
        assert_eq!(msg.flags, 0x1);
    }

    #[test]
    fn test_txattrcreate_serialize() {
        let msg = TxattrcreateMessage::new(123, 456, "user.test".to_string(), 1024, 0x1);
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(34)); // 4 + 1 + 2 + 4 + (2+9) + 8 + 4 = 34 bytes total

        // Verify the serialized data
        // size[4] = 34 (little-endian)
        assert_eq!(buf[0], 34);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Txattrcreate (32)
        assert_eq!(buf[4], 32);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // name[s] = "user.test" (length[2] + string)
        assert_eq!(buf[11], 9); // length = 9
        assert_eq!(buf[12], 0);
        assert_eq!(&buf[13..22], b"user.test");

        // attr_size[8] = 1024 (little-endian)
        let expected_attr_size_bytes = (1024u64).to_le_bytes();
        assert_eq!(&buf[22..30], &expected_attr_size_bytes);

        // flags[4] = 0x1 (little-endian)
        let expected_flags_bytes = (0x1u32).to_le_bytes();
        assert_eq!(&buf[30..34], &expected_flags_bytes);
    }

    #[test]
    fn test_txattrcreate_serialize_buffer_too_small() {
        let msg = TxattrcreateMessage::new(123, 456, "user.test".to_string(), 1024, 0x1);
        let mut buf = [0u8; 20]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TxattrcreateError::BufferTooSmall));
    }

    #[test]
    fn test_txattrcreate_send() {
        let msg = TxattrcreateMessage::new(123, 456, "user.test".to_string(), 1024, 0x1);

        // Test that send_txattrcreate doesn't panic and returns a result
        let result = msg.send_txattrcreate();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TxattrcreateError::BufferTooSmall | TxattrcreateError::InternalError
                ));
            }
        }
    }

    // Rxattrcreate message tests
    #[test]
    fn test_rxattrcreate_message_creation() {
        let msg = RxattrcreateMessage::new(123);
        assert_eq!(msg.tag, 123);
    }

    #[test]
    fn test_rxattrcreate_deserialize() {
        // Create a proper Rxattrcreate message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 7 (little-endian) - 4 + 1 + 2 = 7
        buf[0] = 7;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rxattrcreate (31)
        buf[4] = P9MsgType::Rxattrcreate as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Deserialize as Rxattrcreate
        let (rxattrcreate, bytes_consumed) = RxattrcreateMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 7);
        assert_eq!(rxattrcreate.tag, 123);
    }

    #[test]
    fn test_rxattrcreate_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RxattrcreateMessage::deserialize(&buf);
        assert_eq!(result, Err(RxattrcreateError::BufferTooSmall));
    }

    #[test]
    fn test_rxattrcreate_deserialize_invalid_message_type() {
        // Create a valid Txattrcreate message but don't change the type
        let txattrcreate = TxattrcreateMessage::new(123, 456, "user.test".to_string(), 1024, 0x1);
        let mut buf = [0u8; 64];
        txattrcreate.serialize(&mut buf).unwrap();

        // Try to deserialize as Rxattrcreate (should fail because type is Txattrcreate)
        let result = RxattrcreateMessage::deserialize(&buf);
        assert_eq!(result, Err(RxattrcreateError::InvalidMessageType));
    }

    // Treaddir message tests
    #[test]
    fn test_treaddir_message_creation() {
        let msg = TreaddirMessage::new(123, 456, 0, 1024);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.offset, 0);
        assert_eq!(msg.count, 1024);
    }

    #[test]
    fn test_treaddir_serialize() {
        let msg = TreaddirMessage::new(123, 456, 0, 1024);
        let mut buf = [0u8; 32];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(23)); // 4 + 1 + 2 + 4 + 8 + 4 = 23 bytes total

        // Verify the serialized data
        // size[4] = 23 (little-endian)
        assert_eq!(buf[0], 23);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Treaddir (40)
        assert_eq!(buf[4], 40);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // offset[8] = 0 (little-endian)
        let expected_offset_bytes = (0u64).to_le_bytes();
        assert_eq!(&buf[11..19], &expected_offset_bytes);

        // count[4] = 1024 (little-endian)
        let expected_count_bytes = (1024u32).to_le_bytes();
        assert_eq!(&buf[19..23], &expected_count_bytes);
    }

    #[test]
    fn test_treaddir_serialize_buffer_too_small() {
        let msg = TreaddirMessage::new(123, 456, 0, 1024);
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TreaddirError::BufferTooSmall));
    }

    #[test]
    fn test_treaddir_send() {
        let msg = TreaddirMessage::new(123, 456, 0, 1024);

        // Test that send_treaddir doesn't panic and returns a result
        let result = msg.send_treaddir();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TreaddirError::BufferTooSmall | TreaddirError::InternalError
                ));
            }
        }
    }

    // Rreaddir message tests
    #[test]
    fn test_rreaddir_message_creation() {
        let data = vec![0x01, 0x02, 0x03, 0x04];
        let msg = RreaddirMessage::new(123, 4, data.clone());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.count, 4);
        assert_eq!(msg.data, data);
    }

    #[test]
    fn test_rreaddir_deserialize() {
        // Create a proper Rreaddir message buffer
        let mut buf = [0u8; 32];

        // Write size[4] = 11 (little-endian) - 4 + 1 + 2 + 4 = 11
        buf[0] = 11;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rreaddir (33)
        buf[4] = P9MsgType::Rreaddir as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write count[4] = 4 (little-endian)
        let count_bytes = (4u32).to_le_bytes();
        buf[7..11].copy_from_slice(&count_bytes);

        // Write data[4] = [0x01, 0x02, 0x03, 0x04]
        buf[11] = 0x01;
        buf[12] = 0x02;
        buf[13] = 0x03;
        buf[14] = 0x04;

        // Deserialize as Rreaddir
        let (rreaddir, bytes_consumed) = RreaddirMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 15);
        assert_eq!(rreaddir.tag, 123);
        assert_eq!(rreaddir.count, 4);
        assert_eq!(rreaddir.data, vec![0x01, 0x02, 0x03, 0x04]);
    }

    #[test]
    fn test_rreaddir_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RreaddirMessage::deserialize(&buf);
        assert_eq!(result, Err(RreaddirError::BufferTooSmall));
    }

    #[test]
    fn test_rreaddir_deserialize_invalid_message_type() {
        // Create a valid Treaddir message but don't change the type
        let treaddir = TreaddirMessage::new(123, 456, 0, 1024);
        let mut buf = [0u8; 32];
        treaddir.serialize(&mut buf).unwrap();

        // Try to deserialize as Rreaddir (should fail because type is Treaddir)
        let result = RreaddirMessage::deserialize(&buf);
        assert_eq!(result, Err(RreaddirError::InvalidMessageType));
    }

    // Roundtrip tests for Txattrwalk/Rxattrwalk, Txattrcreate/Rxattrcreate, and Treaddir/Rreaddir
    #[test]
    fn test_roundtrip_txattrwalk_rxattrwalk() {
        // Create a Txattrwalk message
        let original = TxattrwalkMessage::new(456, 789, 101112, "user.test".to_string());
        let mut txattrwalk_buf = [0u8; 64];
        let txattrwalk_bytes_written = original.serialize(&mut txattrwalk_buf).unwrap();

        // Create a separate Rxattrwalk message with the same tag
        let _rxattrwalk_msg = RxattrwalkMessage::new(original.tag, 1024);
        let mut rxattrwalk_buf = [0u8; 32];

        // Manually create Rxattrwalk buffer
        // Write size[4] = 15 (little-endian)
        rxattrwalk_buf[0] = 15;
        rxattrwalk_buf[1] = 0;
        rxattrwalk_buf[2] = 0;
        rxattrwalk_buf[3] = 0;

        // Write message type[1] = Rxattrwalk (29)
        rxattrwalk_buf[4] = P9MsgType::Rxattrwalk as u8;

        // Write tag[2] = 456 (little-endian)
        rxattrwalk_buf[5] = (456 & 0xff) as u8;
        rxattrwalk_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write size[8] = 1024 (little-endian)
        let size_bytes = (1024u64).to_le_bytes();
        rxattrwalk_buf[7..15].copy_from_slice(&size_bytes);

        // Deserialize as Rxattrwalk
        let (rxattrwalk, bytes_consumed) = RxattrwalkMessage::deserialize(&rxattrwalk_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 15);
        assert_eq!(rxattrwalk.tag, original.tag);
        assert_eq!(rxattrwalk.size, 1024);
        assert_eq!(txattrwalk_bytes_written, 26); // Txattrwalk is 26 bytes
    }

    #[test]
    fn test_roundtrip_txattrcreate_rxattrcreate() {
        // Create a Txattrcreate message
        let original = TxattrcreateMessage::new(456, 789, "user.test".to_string(), 1024, 0x1);
        let mut txattrcreate_buf = [0u8; 64];
        let txattrcreate_bytes_written = original.serialize(&mut txattrcreate_buf).unwrap();

        // Create a separate Rxattrcreate message with the same tag
        let _rxattrcreate_msg = RxattrcreateMessage::new(original.tag);
        let mut rxattrcreate_buf = [0u8; 16];

        // Manually create Rxattrcreate buffer
        // Write size[4] = 7 (little-endian)
        rxattrcreate_buf[0] = 7;
        rxattrcreate_buf[1] = 0;
        rxattrcreate_buf[2] = 0;
        rxattrcreate_buf[3] = 0;

        // Write message type[1] = Rxattrcreate (31)
        rxattrcreate_buf[4] = P9MsgType::Rxattrcreate as u8;

        // Write tag[2] = 456 (little-endian)
        rxattrcreate_buf[5] = (456 & 0xff) as u8;
        rxattrcreate_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Deserialize as Rxattrcreate
        let (rxattrcreate, bytes_consumed) =
            RxattrcreateMessage::deserialize(&rxattrcreate_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 7);
        assert_eq!(rxattrcreate.tag, original.tag);
        assert_eq!(txattrcreate_bytes_written, 34); // Txattrcreate is 34 bytes
    }

    #[test]
    fn test_roundtrip_treaddir_rreaddir() {
        // Create a Treaddir message
        let original = TreaddirMessage::new(456, 789, 0, 1024);
        let mut treaddir_buf = [0u8; 32];
        let treaddir_bytes_written = original.serialize(&mut treaddir_buf).unwrap();

        // Create a separate Rreaddir message with the same tag
        let data = vec![0x01, 0x02, 0x03, 0x04];
        let _rreaddir_msg = RreaddirMessage::new(original.tag, 4, data);
        let mut rreaddir_buf = [0u8; 32];

        // Manually create Rreaddir buffer
        // Write size[4] = 15 (little-endian) - 4 + 1 + 2 + 4 + 4 = 15
        rreaddir_buf[0] = 15;
        rreaddir_buf[1] = 0;
        rreaddir_buf[2] = 0;
        rreaddir_buf[3] = 0;

        // Write message type[1] = Rreaddir (33)
        rreaddir_buf[4] = P9MsgType::Rreaddir as u8;

        // Write tag[2] = 456 (little-endian)
        rreaddir_buf[5] = (456 & 0xff) as u8;
        rreaddir_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write count[4] = 4 (little-endian)
        let count_bytes = (4u32).to_le_bytes();
        rreaddir_buf[7..11].copy_from_slice(&count_bytes);

        // Write data[4] = [0x01, 0x02, 0x03, 0x04]
        rreaddir_buf[11] = 0x01;
        rreaddir_buf[12] = 0x02;
        rreaddir_buf[13] = 0x03;
        rreaddir_buf[14] = 0x04;

        // Deserialize as Rreaddir
        let (rreaddir, bytes_consumed) = RreaddirMessage::deserialize(&rreaddir_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 15);
        assert_eq!(rreaddir.tag, original.tag);
        assert_eq!(rreaddir.count, 4);
        assert_eq!(rreaddir.data, vec![0x01, 0x02, 0x03, 0x04]);
        assert_eq!(treaddir_bytes_written, 23); // Treaddir is 23 bytes
    }

    // Tfsync message tests
    #[test]
    fn test_tfsync_message_creation() {
        let msg = TfsyncMessage::new(123, 456, 0);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.datasync, 0);
    }

    #[test]
    fn test_tfsync_serialize() {
        let msg = TfsyncMessage::new(123, 456, 0);
        let mut buf = [0u8; 32];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(15)); // 4 + 1 + 2 + 4 + 4 = 15 bytes total

        // Verify the serialized data
        // size[4] = 15 (little-endian)
        assert_eq!(buf[0], 15);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tfsync (50)
        assert_eq!(buf[4], 50);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // datasync[4] = 0 (little-endian)
        let expected_datasync_bytes = (0u32).to_le_bytes();
        assert_eq!(&buf[11..15], &expected_datasync_bytes);
    }

    #[test]
    fn test_tfsync_serialize_buffer_too_small() {
        let msg = TfsyncMessage::new(123, 456, 0);
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TfsyncError::BufferTooSmall));
    }

    #[test]
    fn test_tfsync_send() {
        let msg = TfsyncMessage::new(123, 456, 0);

        // Test that send_tfsync doesn't panic and returns a result
        let result = msg.send_tfsync();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TfsyncError::BufferTooSmall | TfsyncError::InternalError
                ));
            }
        }
    }

    // Rfsync message tests
    #[test]
    fn test_rfsync_message_creation() {
        let msg = RfsyncMessage::new(123);
        assert_eq!(msg.tag, 123);
    }

    #[test]
    fn test_rfsync_deserialize() {
        // Create a proper Rfsync message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 7 (little-endian) - 4 + 1 + 2 = 7
        buf[0] = 7;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rfsync (51)
        buf[4] = P9MsgType::Rfsync as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Deserialize as Rfsync
        let (rfsync, bytes_consumed) = RfsyncMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 7);
        assert_eq!(rfsync.tag, 123);
    }

    #[test]
    fn test_rfsync_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RfsyncMessage::deserialize(&buf);
        assert_eq!(result, Err(RfsyncError::BufferTooSmall));
    }

    #[test]
    fn test_rfsync_deserialize_invalid_message_type() {
        // Create a valid Tfsync message but don't change the type
        let tfsync = TfsyncMessage::new(123, 456, 0);
        let mut buf = [0u8; 32];
        tfsync.serialize(&mut buf).unwrap();

        // Try to deserialize as Rfsync (should fail because type is Tfsync)
        let result = RfsyncMessage::deserialize(&buf);
        assert_eq!(result, Err(RfsyncError::InvalidMessageType));
    }

    // Tlock message tests
    #[test]
    fn test_tlock_message_creation() {
        let msg = TlockMessage::new(123, 456, 1, 0x1, 0, 1024, 1000, "client1".to_string());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.type_, 1);
        assert_eq!(msg.flags, 0x1);
        assert_eq!(msg.start, 0);
        assert_eq!(msg.length, 1024);
        assert_eq!(msg.proc_id, 1000);
        assert_eq!(msg.client_id, "client1");
    }

    #[test]
    fn test_tlock_serialize() {
        let msg = TlockMessage::new(123, 456, 1, 0x1, 0, 1024, 1000, "client1".to_string());
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(45)); // 4 + 1 + 2 + 4 + 1 + 4 + 8 + 8 + 4 + (2+7) = 45 bytes total

        // Verify the serialized data
        // size[4] = 45 (little-endian)
        assert_eq!(buf[0], 45);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tlock (52)
        assert_eq!(buf[4], 52);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // type[1] = 1
        assert_eq!(buf[11], 1);

        // flags[4] = 0x1 (little-endian)
        let expected_flags_bytes = (0x1u32).to_le_bytes();
        assert_eq!(&buf[12..16], &expected_flags_bytes);

        // start[8] = 0 (little-endian)
        let expected_start_bytes = (0u64).to_le_bytes();
        assert_eq!(&buf[16..24], &expected_start_bytes);

        // length[8] = 1024 (little-endian)
        let expected_length_bytes = (1024u64).to_le_bytes();
        assert_eq!(&buf[24..32], &expected_length_bytes);

        // proc_id[4] = 1000 (little-endian)
        let expected_proc_id_bytes = (1000u32).to_le_bytes();
        assert_eq!(&buf[32..36], &expected_proc_id_bytes);

        // client_id[s] = "client1" (length[2] + string)
        assert_eq!(buf[36], 7); // length = 7
        assert_eq!(buf[37], 0);
        assert_eq!(&buf[38..45], b"client1");
    }

    #[test]
    fn test_tlock_serialize_buffer_too_small() {
        let msg = TlockMessage::new(123, 456, 1, 0x1, 0, 1024, 1000, "client1".to_string());
        let mut buf = [0u8; 20]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TlockError::BufferTooSmall));
    }

    #[test]
    fn test_tlock_send() {
        let msg = TlockMessage::new(123, 456, 1, 0x1, 0, 1024, 1000, "client1".to_string());

        // Test that send_tlock doesn't panic and returns a result
        let result = msg.send_tlock();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TlockError::BufferTooSmall | TlockError::InternalError
                ));
            }
        }
    }

    // Rlock message tests
    #[test]
    fn test_rlock_message_creation() {
        let msg = RlockMessage::new(123, 1);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.status, 1);
    }

    #[test]
    fn test_rlock_deserialize() {
        // Create a proper Rlock message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 8 (little-endian) - 4 + 1 + 2 + 1 = 8
        buf[0] = 8;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rlock (53)
        buf[4] = P9MsgType::Rlock as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write status[1] = 1
        buf[7] = 1;

        // Deserialize as Rlock
        let (rlock, bytes_consumed) = RlockMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 8);
        assert_eq!(rlock.tag, 123);
        assert_eq!(rlock.status, 1);
    }

    #[test]
    fn test_rlock_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RlockMessage::deserialize(&buf);
        assert_eq!(result, Err(RlockError::BufferTooSmall));
    }

    #[test]
    fn test_rlock_deserialize_invalid_message_type() {
        // Create a valid Tlock message but don't change the type
        let tlock = TlockMessage::new(123, 456, 1, 0x1, 0, 1024, 1000, "client1".to_string());
        let mut buf = [0u8; 64];
        tlock.serialize(&mut buf).unwrap();

        // Try to deserialize as Rlock (should fail because type is Tlock)
        let result = RlockMessage::deserialize(&buf);
        assert_eq!(result, Err(RlockError::InvalidMessageType));
    }

    // Tgetlock message tests
    #[test]
    fn test_tgetlock_message_creation() {
        let msg = TgetlockMessage::new(123, 456, 1, 0, 1024, 1000, "client1".to_string());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.fid, 456);
        assert_eq!(msg.type_, 1);
        assert_eq!(msg.start, 0);
        assert_eq!(msg.length, 1024);
        assert_eq!(msg.proc_id, 1000);
        assert_eq!(msg.client_id, "client1");
    }

    #[test]
    fn test_tgetlock_serialize() {
        let msg = TgetlockMessage::new(123, 456, 1, 0, 1024, 1000, "client1".to_string());
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(41)); // 4 + 1 + 2 + 4 + 1 + 8 + 8 + 4 + (2+7) = 41 bytes total

        // Verify the serialized data
        // size[4] = 41 (little-endian)
        assert_eq!(buf[0], 41);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tgetlock (54)
        assert_eq!(buf[4], 54);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // fid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // type[1] = 1
        assert_eq!(buf[11], 1);

        // start[8] = 0 (little-endian)
        let expected_start_bytes = (0u64).to_le_bytes();
        assert_eq!(&buf[12..20], &expected_start_bytes);

        // length[8] = 1024 (little-endian)
        let expected_length_bytes = (1024u64).to_le_bytes();
        assert_eq!(&buf[20..28], &expected_length_bytes);

        // proc_id[4] = 1000 (little-endian)
        let expected_proc_id_bytes = (1000u32).to_le_bytes();
        assert_eq!(&buf[28..32], &expected_proc_id_bytes);

        // client_id[s] = "client1" (length[2] + string)
        assert_eq!(buf[32], 7); // length = 7
        assert_eq!(buf[33], 0);
        assert_eq!(&buf[34..41], b"client1");
    }

    #[test]
    fn test_tgetlock_serialize_buffer_too_small() {
        let msg = TgetlockMessage::new(123, 456, 1, 0, 1024, 1000, "client1".to_string());
        let mut buf = [0u8; 20]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TgetlockError::BufferTooSmall));
    }

    #[test]
    fn test_tgetlock_send() {
        let msg = TgetlockMessage::new(123, 456, 1, 0, 1024, 1000, "client1".to_string());

        // Test that send_tgetlock doesn't panic and returns a result
        let result = msg.send_tgetlock();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TgetlockError::BufferTooSmall | TgetlockError::InternalError
                ));
            }
        }
    }

    // Rgetlock message tests
    #[test]
    fn test_rgetlock_message_creation() {
        let msg = RgetlockMessage::new(123, 1, 0, 1024, 1000, "client1".to_string());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.type_, 1);
        assert_eq!(msg.start, 0);
        assert_eq!(msg.length, 1024);
        assert_eq!(msg.proc_id, 1000);
        assert_eq!(msg.client_id, "client1");
    }

    #[test]
    fn test_rgetlock_deserialize() {
        // Create a proper Rgetlock message buffer
        let mut buf = [0u8; 64];

        // Write size[4] = 37 (little-endian) - 4 + 1 + 2 + 1 + 8 + 8 + 4 + (2+7) = 37
        buf[0] = 37;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rgetlock (55)
        buf[4] = P9MsgType::Rgetlock as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write type[1] = 1
        buf[7] = 1;

        // Write start[8] = 0 (little-endian)
        let start_bytes = (0u64).to_le_bytes();
        buf[8..16].copy_from_slice(&start_bytes);

        // Write length[8] = 1024 (little-endian)
        let length_bytes = (1024u64).to_le_bytes();
        buf[16..24].copy_from_slice(&length_bytes);

        // Write proc_id[4] = 1000 (little-endian)
        let proc_id_bytes = (1000u32).to_le_bytes();
        buf[24..28].copy_from_slice(&proc_id_bytes);

        // Write client_id[s] = "client1" (length[2] + string)
        buf[28] = 7; // length = 7
        buf[29] = 0;
        buf[30..37].copy_from_slice(b"client1");

        // Deserialize as Rgetlock
        let (rgetlock, bytes_consumed) = RgetlockMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 37);
        assert_eq!(rgetlock.tag, 123);
        assert_eq!(rgetlock.type_, 1);
        assert_eq!(rgetlock.start, 0);
        assert_eq!(rgetlock.length, 1024);
        assert_eq!(rgetlock.proc_id, 1000);
        assert_eq!(rgetlock.client_id, "client1");
    }

    #[test]
    fn test_rgetlock_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RgetlockMessage::deserialize(&buf);
        assert_eq!(result, Err(RgetlockError::BufferTooSmall));
    }

    #[test]
    fn test_rgetlock_deserialize_invalid_message_type() {
        // Create a valid Tgetlock message but don't change the type
        let tgetlock = TgetlockMessage::new(123, 456, 1, 0, 1024, 1000, "client1".to_string());
        let mut buf = [0u8; 64];
        tgetlock.serialize(&mut buf).unwrap();

        // Try to deserialize as Rgetlock (should fail because type is Tgetlock)
        let result = RgetlockMessage::deserialize(&buf);
        assert_eq!(result, Err(RgetlockError::InvalidMessageType));
    }

    // Tlink message tests
    #[test]
    fn test_tlink_message_creation() {
        let msg = TlinkMessage::new(123, 456, 789, "linkname".to_string());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.dfid, 456);
        assert_eq!(msg.fid, 789);
        assert_eq!(msg.name, "linkname");
    }

    #[test]
    fn test_tlink_serialize() {
        let msg = TlinkMessage::new(123, 456, 789, "linkname".to_string());
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(25)); // 4 + 1 + 2 + 4 + 4 + (2+8) = 25 bytes total

        // Verify the serialized data
        // size[4] = 25 (little-endian)
        assert_eq!(buf[0], 25);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tlink (70)
        assert_eq!(buf[4], 70);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // dfid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // fid[4] = 789 (little-endian)
        assert_eq!(buf[11], 21); // 789 & 0xff = 21
        assert_eq!(buf[12], 3); // (789 >> 8) & 0xff = 3
        assert_eq!(buf[13], 0);
        assert_eq!(buf[14], 0);

        // name[s] = "linkname" (length[2] + string)
        assert_eq!(buf[15], 8); // length = 8
        assert_eq!(buf[16], 0);
        assert_eq!(&buf[17..25], b"linkname");
    }

    #[test]
    fn test_tlink_serialize_buffer_too_small() {
        let msg = TlinkMessage::new(123, 456, 789, "linkname".to_string());
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TlinkError::BufferTooSmall));
    }

    #[test]
    fn test_tlink_send() {
        let msg = TlinkMessage::new(123, 456, 789, "linkname".to_string());

        // Test that send_tlink doesn't panic and returns a result
        let result = msg.send_tlink();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TlinkError::BufferTooSmall | TlinkError::InternalError
                ));
            }
        }
    }

    // Rlink message tests
    #[test]
    fn test_rlink_message_creation() {
        let msg = RlinkMessage::new(123);
        assert_eq!(msg.tag, 123);
    }

    #[test]
    fn test_rlink_deserialize() {
        // Create a proper Rlink message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 7 (little-endian) - 4 + 1 + 2 = 7
        buf[0] = 7;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rlink (71)
        buf[4] = P9MsgType::Rlink as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Deserialize as Rlink
        let (rlink, bytes_consumed) = RlinkMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 7);
        assert_eq!(rlink.tag, 123);
    }

    #[test]
    fn test_rlink_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RlinkMessage::deserialize(&buf);
        assert_eq!(result, Err(RlinkError::BufferTooSmall));
    }

    #[test]
    fn test_rlink_deserialize_invalid_message_type() {
        // Create a valid Tlink message but don't change the type
        let tlink = TlinkMessage::new(123, 456, 789, "linkname".to_string());
        let mut buf = [0u8; 64];
        tlink.serialize(&mut buf).unwrap();

        // Try to deserialize as Rlink (should fail because type is Tlink)
        let result = RlinkMessage::deserialize(&buf);
        assert_eq!(result, Err(RlinkError::InvalidMessageType));
    }

    // Roundtrip tests for Tfsync/Rfsync, Tlock/Rlock, Tgetlock/Rgetlock, and Tlink/Rlink
    #[test]
    fn test_roundtrip_tfsync_rfsync() {
        // Create a Tfsync message
        let original = TfsyncMessage::new(456, 789, 1);
        let mut tfsync_buf = [0u8; 32];
        let tfsync_bytes_written = original.serialize(&mut tfsync_buf).unwrap();

        // Create a separate Rfsync message with the same tag
        let _rfsync_msg = RfsyncMessage::new(original.tag);
        let mut rfsync_buf = [0u8; 16];

        // Manually create Rfsync buffer
        // Write size[4] = 7 (little-endian)
        rfsync_buf[0] = 7;
        rfsync_buf[1] = 0;
        rfsync_buf[2] = 0;
        rfsync_buf[3] = 0;

        // Write message type[1] = Rfsync (51)
        rfsync_buf[4] = P9MsgType::Rfsync as u8;

        // Write tag[2] = 456 (little-endian)
        rfsync_buf[5] = (456 & 0xff) as u8;
        rfsync_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Deserialize as Rfsync
        let (rfsync, bytes_consumed) = RfsyncMessage::deserialize(&rfsync_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 7);
        assert_eq!(rfsync.tag, original.tag);
        assert_eq!(tfsync_bytes_written, 15); // Tfsync is 15 bytes
    }

    #[test]
    fn test_roundtrip_tlock_rlock() {
        // Create a Tlock message
        let original = TlockMessage::new(456, 789, 1, 0x1, 0, 1024, 1000, "client1".to_string());
        let mut tlock_buf = [0u8; 64];
        let tlock_bytes_written = original.serialize(&mut tlock_buf).unwrap();

        // Create a separate Rlock message with the same tag
        let _rlock_msg = RlockMessage::new(original.tag, 1);
        let mut rlock_buf = [0u8; 16];

        // Manually create Rlock buffer
        // Write size[4] = 8 (little-endian)
        rlock_buf[0] = 8;
        rlock_buf[1] = 0;
        rlock_buf[2] = 0;
        rlock_buf[3] = 0;

        // Write message type[1] = Rlock (53)
        rlock_buf[4] = P9MsgType::Rlock as u8;

        // Write tag[2] = 456 (little-endian)
        rlock_buf[5] = (456 & 0xff) as u8;
        rlock_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write status[1] = 1
        rlock_buf[7] = 1;

        // Deserialize as Rlock
        let (rlock, bytes_consumed) = RlockMessage::deserialize(&rlock_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 8);
        assert_eq!(rlock.tag, original.tag);
        assert_eq!(rlock.status, 1);
        assert_eq!(tlock_bytes_written, 45); // Tlock is 45 bytes
    }

    #[test]
    fn test_roundtrip_tgetlock_rgetlock() {
        // Create a Tgetlock message
        let original = TgetlockMessage::new(456, 789, 1, 0, 1024, 1000, "client1".to_string());
        let mut tgetlock_buf = [0u8; 64];
        let tgetlock_bytes_written = original.serialize(&mut tgetlock_buf).unwrap();

        // Create a separate Rgetlock message with the same tag
        let _rgetlock_msg =
            RgetlockMessage::new(original.tag, 1, 0, 1024, 1000, "client1".to_string());
        let mut rgetlock_buf = [0u8; 64];

        // Manually create Rgetlock buffer
        // Write size[4] = 37 (little-endian)
        rgetlock_buf[0] = 37;
        rgetlock_buf[1] = 0;
        rgetlock_buf[2] = 0;
        rgetlock_buf[3] = 0;

        // Write message type[1] = Rgetlock (55)
        rgetlock_buf[4] = P9MsgType::Rgetlock as u8;

        // Write tag[2] = 456 (little-endian)
        rgetlock_buf[5] = (456 & 0xff) as u8;
        rgetlock_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write type[1] = 1
        rgetlock_buf[7] = 1;

        // Write start[8] = 0 (little-endian)
        let start_bytes = (0u64).to_le_bytes();
        rgetlock_buf[8..16].copy_from_slice(&start_bytes);

        // Write length[8] = 1024 (little-endian)
        let length_bytes = (1024u64).to_le_bytes();
        rgetlock_buf[16..24].copy_from_slice(&length_bytes);

        // Write proc_id[4] = 1000 (little-endian)
        let proc_id_bytes = (1000u32).to_le_bytes();
        rgetlock_buf[24..28].copy_from_slice(&proc_id_bytes);

        // Write client_id[s] = "client1" (length[2] + string)
        rgetlock_buf[28] = 7; // length = 7
        rgetlock_buf[29] = 0;
        rgetlock_buf[30..37].copy_from_slice(b"client1");

        // Deserialize as Rgetlock
        let (rgetlock, bytes_consumed) = RgetlockMessage::deserialize(&rgetlock_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 37);
        assert_eq!(rgetlock.tag, original.tag);
        assert_eq!(rgetlock.type_, 1);
        assert_eq!(rgetlock.start, 0);
        assert_eq!(rgetlock.length, 1024);
        assert_eq!(rgetlock.proc_id, 1000);
        assert_eq!(rgetlock.client_id, "client1");
        assert_eq!(tgetlock_bytes_written, 41); // Tgetlock is 41 bytes
    }

    #[test]
    fn test_roundtrip_tlink_rlink() {
        // Create a Tlink message
        let original = TlinkMessage::new(456, 789, 101112, "linkname".to_string());
        let mut tlink_buf = [0u8; 64];
        let tlink_bytes_written = original.serialize(&mut tlink_buf).unwrap();

        // Create a separate Rlink message with the same tag
        let _rlink_msg = RlinkMessage::new(original.tag);
        let mut rlink_buf = [0u8; 16];

        // Manually create Rlink buffer
        // Write size[4] = 7 (little-endian)
        rlink_buf[0] = 7;
        rlink_buf[1] = 0;
        rlink_buf[2] = 0;
        rlink_buf[3] = 0;

        // Write message type[1] = Rlink (71)
        rlink_buf[4] = P9MsgType::Rlink as u8;

        // Write tag[2] = 456 (little-endian)
        rlink_buf[5] = (456 & 0xff) as u8;
        rlink_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Deserialize as Rlink
        let (rlink, bytes_consumed) = RlinkMessage::deserialize(&rlink_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 7);
        assert_eq!(rlink.tag, original.tag);
        assert_eq!(tlink_bytes_written, 25); // Tlink is 25 bytes
    }

    // Tmkdir message tests
    #[test]
    fn test_tmkdir_message_creation() {
        let msg = TmkdirMessage::new(123, 456, "newdir".to_string(), 0o755, 1000);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.dfid, 456);
        assert_eq!(msg.name, "newdir");
        assert_eq!(msg.mode, 0o755);
        assert_eq!(msg.gid, 1000);
    }

    #[test]
    fn test_tmkdir_serialize() {
        let msg = TmkdirMessage::new(123, 456, "newdir".to_string(), 0o755, 1000);
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(27)); // 4 + 1 + 2 + 4 + (2+6) + 4 + 4 = 27 bytes total

        // Verify the serialized data
        // size[4] = 27 (little-endian)
        assert_eq!(buf[0], 27);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tmkdir (72)
        assert_eq!(buf[4], 72);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // dfid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // name[s] = "newdir" (length[2] + string)
        assert_eq!(buf[11], 6); // length = 6
        assert_eq!(buf[12], 0);
        assert_eq!(&buf[13..19], b"newdir");

        // mode[4] = 0o755 (little-endian)
        let expected_mode_bytes = (0o755u32).to_le_bytes();
        assert_eq!(&buf[19..23], &expected_mode_bytes);

        // gid[4] = 1000 (little-endian)
        let expected_gid_bytes = (1000u32).to_le_bytes();
        assert_eq!(&buf[23..27], &expected_gid_bytes);
    }

    #[test]
    fn test_tmkdir_serialize_buffer_too_small() {
        let msg = TmkdirMessage::new(123, 456, "newdir".to_string(), 0o755, 1000);
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TmkdirError::BufferTooSmall));
    }

    #[test]
    fn test_tmkdir_send() {
        let msg = TmkdirMessage::new(123, 456, "newdir".to_string(), 0o755, 1000);

        // Test that send_tmkdir doesn't panic and returns a result
        let result = msg.send_tmkdir();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TmkdirError::BufferTooSmall | TmkdirError::InternalError
                ));
            }
        }
    }

    // Rmkdir message tests
    #[test]
    fn test_rmkdir_message_creation() {
        let qid = Qid {
            qtype: 0x80, // Directory type
            version: 1,
            path: 0x123456789abcdef0,
        };
        let msg = RmkdirMessage::new(123, qid);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.qid.qtype, 0x80);
        assert_eq!(msg.qid.version, 1);
        assert_eq!(msg.qid.path, 0x123456789abcdef0);
    }

    #[test]
    fn test_rmkdir_deserialize() {
        // Create a proper Rmkdir message buffer
        let mut buf = [0u8; 32];

        // Write size[4] = 20 (little-endian) - 4 + 1 + 2 + 13 = 20
        buf[0] = 20;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rmkdir (73)
        buf[4] = P9MsgType::Rmkdir as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Write qid[13]
        buf[7] = 0x80; // type = directory
        let version_bytes = (1u32).to_le_bytes();
        buf[8..12].copy_from_slice(&version_bytes);
        let path_bytes = (0x123456789abcdef0u64).to_le_bytes();
        buf[12..20].copy_from_slice(&path_bytes);

        // Deserialize as Rmkdir
        let (rmkdir, bytes_consumed) = RmkdirMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 20);
        assert_eq!(rmkdir.tag, 123);
        assert_eq!(rmkdir.qid.qtype, 0x80);
        assert_eq!(rmkdir.qid.version, 1);
        assert_eq!(rmkdir.qid.path, 0x123456789abcdef0);
    }

    #[test]
    fn test_rmkdir_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RmkdirMessage::deserialize(&buf);
        assert_eq!(result, Err(RmkdirError::BufferTooSmall));
    }

    #[test]
    fn test_rmkdir_deserialize_invalid_message_type() {
        // Create a valid Tmkdir message but don't change the type
        let tmkdir = TmkdirMessage::new(123, 456, "newdir".to_string(), 0o755, 1000);
        let mut buf = [0u8; 64];
        tmkdir.serialize(&mut buf).unwrap();

        // Try to deserialize as Rmkdir (should fail because type is Tmkdir)
        let result = RmkdirMessage::deserialize(&buf);
        assert_eq!(result, Err(RmkdirError::InvalidMessageType));
    }

    // Trenameat message tests
    #[test]
    fn test_trenameat_message_creation() {
        let msg =
            TrenameatMessage::new(123, 456, "oldname".to_string(), 789, "newname".to_string());
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.olddirfid, 456);
        assert_eq!(msg.oldname, "oldname");
        assert_eq!(msg.newdirfid, 789);
        assert_eq!(msg.newname, "newname");
    }

    #[test]
    fn test_trenameat_serialize() {
        let msg =
            TrenameatMessage::new(123, 456, "oldname".to_string(), 789, "newname".to_string());
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(33)); // 4 + 1 + 2 + 4 + (2+7) + 4 + (2+7) = 33 bytes total

        // Verify the serialized data
        // size[4] = 33 (little-endian)
        assert_eq!(buf[0], 33);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Trenameat (74)
        assert_eq!(buf[4], 74);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // olddirfid[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // oldname[s] = "oldname" (length[2] + string)
        assert_eq!(buf[11], 7); // length = 7
        assert_eq!(buf[12], 0);
        assert_eq!(&buf[13..20], b"oldname");

        // newdirfid[4] = 789 (little-endian)
        assert_eq!(buf[20], 21); // 789 & 0xff = 21
        assert_eq!(buf[21], 3); // (789 >> 8) & 0xff = 3
        assert_eq!(buf[22], 0);
        assert_eq!(buf[23], 0);

        // newname[s] = "newname" (length[2] + string)
        assert_eq!(buf[24], 7); // length = 7
        assert_eq!(buf[25], 0);
        assert_eq!(&buf[26..33], b"newname");
    }

    #[test]
    fn test_trenameat_serialize_buffer_too_small() {
        let msg =
            TrenameatMessage::new(123, 456, "oldname".to_string(), 789, "newname".to_string());
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TrenameatError::BufferTooSmall));
    }

    #[test]
    fn test_trenameat_send() {
        let msg =
            TrenameatMessage::new(123, 456, "oldname".to_string(), 789, "newname".to_string());

        // Test that send_trenameat doesn't panic and returns a result
        let result = msg.send_trenameat();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TrenameatError::BufferTooSmall | TrenameatError::InternalError
                ));
            }
        }
    }

    // Rrenameat message tests
    #[test]
    fn test_rrenameat_message_creation() {
        let msg = RrenameatMessage::new(123);
        assert_eq!(msg.tag, 123);
    }

    #[test]
    fn test_rrenameat_deserialize() {
        // Create a proper Rrenameat message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 7 (little-endian) - 4 + 1 + 2 = 7
        buf[0] = 7;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Rrenameat (75)
        buf[4] = P9MsgType::Rrenameat as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Deserialize as Rrenameat
        let (rrenameat, bytes_consumed) = RrenameatMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 7);
        assert_eq!(rrenameat.tag, 123);
    }

    #[test]
    fn test_rrenameat_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RrenameatMessage::deserialize(&buf);
        assert_eq!(result, Err(RrenameatError::BufferTooSmall));
    }

    #[test]
    fn test_rrenameat_deserialize_invalid_message_type() {
        // Create a valid Trenameat message but don't change the type
        let trenameat =
            TrenameatMessage::new(123, 456, "oldname".to_string(), 789, "newname".to_string());
        let mut buf = [0u8; 64];
        trenameat.serialize(&mut buf).unwrap();

        // Try to deserialize as Rrenameat (should fail because type is Trenameat)
        let result = RrenameatMessage::deserialize(&buf);
        assert_eq!(result, Err(RrenameatError::InvalidMessageType));
    }

    // Tunlinkat message tests
    #[test]
    fn test_tunlinkat_message_creation() {
        let msg = TunlinkatMessage::new(123, 456, "filename".to_string(), 0);
        assert_eq!(msg.tag, 123);
        assert_eq!(msg.dirfd, 456);
        assert_eq!(msg.name, "filename");
        assert_eq!(msg.flags, 0);
    }

    #[test]
    fn test_tunlinkat_serialize() {
        let msg = TunlinkatMessage::new(123, 456, "filename".to_string(), 0);
        let mut buf = [0u8; 64];

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Ok(25)); // 4 + 1 + 2 + 4 + (2+8) + 4 = 25 bytes total

        // Verify the serialized data
        // size[4] = 25 (little-endian)
        assert_eq!(buf[0], 25);
        assert_eq!(buf[1], 0);
        assert_eq!(buf[2], 0);
        assert_eq!(buf[3], 0);

        // type[1] = Tunlinkat (76)
        assert_eq!(buf[4], 76);

        // tag[2] = 123 (little-endian)
        assert_eq!(buf[5], 123);
        assert_eq!(buf[6], 0);

        // dirfd[4] = 456 (little-endian)
        assert_eq!(buf[7], 200); // 456 & 0xff = 200
        assert_eq!(buf[8], 1); // (456 >> 8) & 0xff = 1
        assert_eq!(buf[9], 0);
        assert_eq!(buf[10], 0);

        // name[s] = "filename" (length[2] + string)
        assert_eq!(buf[11], 8); // length = 8
        assert_eq!(buf[12], 0);
        assert_eq!(&buf[13..21], b"filename");

        // flags[4] = 0 (little-endian)
        let expected_flags_bytes = (0u32).to_le_bytes();
        assert_eq!(&buf[21..25], &expected_flags_bytes);
    }

    #[test]
    fn test_tunlinkat_serialize_buffer_too_small() {
        let msg = TunlinkatMessage::new(123, 456, "filename".to_string(), 0);
        let mut buf = [0u8; 10]; // Too small for the message

        let result = msg.serialize(&mut buf);
        assert_eq!(result, Err(TunlinkatError::BufferTooSmall));
    }

    #[test]
    fn test_tunlinkat_send() {
        let msg = TunlinkatMessage::new(123, 456, "filename".to_string(), 0);

        // Test that send_tunlinkat doesn't panic and returns a result
        let result = msg.send_tunlinkat();

        // The actual result depends on the host environment
        match result {
            Ok(_bytes_written) => {
                // In test environment, host_write might return 0 or the actual bytes
            }
            Err(e) => {
                assert!(matches!(
                    e,
                    TunlinkatError::BufferTooSmall | TunlinkatError::InternalError
                ));
            }
        }
    }

    // Runlinkat message tests
    #[test]
    fn test_runlinkat_message_creation() {
        let msg = RunlinkatMessage::new(123);
        assert_eq!(msg.tag, 123);
    }

    #[test]
    fn test_runlinkat_deserialize() {
        // Create a proper Runlinkat message buffer
        let mut buf = [0u8; 16];

        // Write size[4] = 7 (little-endian) - 4 + 1 + 2 = 7
        buf[0] = 7;
        buf[1] = 0;
        buf[2] = 0;
        buf[3] = 0;

        // Write message type[1] = Runlinkat (77)
        buf[4] = P9MsgType::Runlinkat as u8;

        // Write tag[2] = 123 (little-endian)
        buf[5] = 123;
        buf[6] = 0;

        // Deserialize as Runlinkat
        let (runlinkat, bytes_consumed) = RunlinkatMessage::deserialize(&buf).unwrap();

        assert_eq!(bytes_consumed, 7);
        assert_eq!(runlinkat.tag, 123);
    }

    #[test]
    fn test_runlinkat_deserialize_buffer_too_small() {
        let buf = [0x01, 0x00, 0x00, 0x00]; // Only 4 bytes
        let result = RunlinkatMessage::deserialize(&buf);
        assert_eq!(result, Err(RunlinkatError::BufferTooSmall));
    }

    #[test]
    fn test_runlinkat_deserialize_invalid_message_type() {
        // Create a valid Tunlinkat message but don't change the type
        let tunlinkat = TunlinkatMessage::new(123, 456, "filename".to_string(), 0);
        let mut buf = [0u8; 64];
        tunlinkat.serialize(&mut buf).unwrap();

        // Try to deserialize as Runlinkat (should fail because type is Tunlinkat)
        let result = RunlinkatMessage::deserialize(&buf);
        assert_eq!(result, Err(RunlinkatError::InvalidMessageType));
    }

    // Roundtrip tests for Tmkdir/Rmkdir, Trenameat/Rrenameat, and Tunlinkat/Runlinkat
    #[test]
    fn test_roundtrip_tmkdir_rmkdir() {
        // Create a Tmkdir message
        let original = TmkdirMessage::new(456, 789, "newdir".to_string(), 0o755, 1000);
        let mut tmkdir_buf = [0u8; 64];
        let tmkdir_bytes_written = original.serialize(&mut tmkdir_buf).unwrap();

        // Create a separate Rmkdir message with the same tag
        let qid = Qid {
            qtype: 0x80, // Directory type
            version: 1,
            path: 0x123456789abcdef0,
        };
        let _rmkdir_msg = RmkdirMessage::new(original.tag, qid);
        let mut rmkdir_buf = [0u8; 32];

        // Manually create Rmkdir buffer
        // Write size[4] = 20 (little-endian)
        rmkdir_buf[0] = 20;
        rmkdir_buf[1] = 0;
        rmkdir_buf[2] = 0;
        rmkdir_buf[3] = 0;

        // Write message type[1] = Rmkdir (73)
        rmkdir_buf[4] = P9MsgType::Rmkdir as u8;

        // Write tag[2] = 456 (little-endian)
        rmkdir_buf[5] = (456 & 0xff) as u8;
        rmkdir_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Write qid[13]
        rmkdir_buf[7] = 0x80; // type = directory
        let version_bytes = (1u32).to_le_bytes();
        rmkdir_buf[8..12].copy_from_slice(&version_bytes);
        let path_bytes = (0x123456789abcdef0u64).to_le_bytes();
        rmkdir_buf[12..20].copy_from_slice(&path_bytes);

        // Deserialize as Rmkdir
        let (rmkdir, bytes_consumed) = RmkdirMessage::deserialize(&rmkdir_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 20);
        assert_eq!(rmkdir.tag, original.tag);
        assert_eq!(rmkdir.qid.qtype, 0x80);
        assert_eq!(rmkdir.qid.version, 1);
        assert_eq!(rmkdir.qid.path, 0x123456789abcdef0);
        assert_eq!(tmkdir_bytes_written, 27); // Tmkdir is 27 bytes
    }

    #[test]
    fn test_roundtrip_trenameat_rrenameat() {
        // Create a Trenameat message
        let original = TrenameatMessage::new(
            456,
            789,
            "oldname".to_string(),
            101112,
            "newname".to_string(),
        );
        let mut trenameat_buf = [0u8; 64];
        let trenameat_bytes_written = original.serialize(&mut trenameat_buf).unwrap();

        // Create a separate Rrenameat message with the same tag
        let _rrenameat_msg = RrenameatMessage::new(original.tag);
        let mut rrenameat_buf = [0u8; 16];

        // Manually create Rrenameat buffer
        // Write size[4] = 7 (little-endian)
        rrenameat_buf[0] = 7;
        rrenameat_buf[1] = 0;
        rrenameat_buf[2] = 0;
        rrenameat_buf[3] = 0;

        // Write message type[1] = Rrenameat (75)
        rrenameat_buf[4] = P9MsgType::Rrenameat as u8;

        // Write tag[2] = 456 (little-endian)
        rrenameat_buf[5] = (456 & 0xff) as u8;
        rrenameat_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Deserialize as Rrenameat
        let (rrenameat, bytes_consumed) = RrenameatMessage::deserialize(&rrenameat_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 7);
        assert_eq!(rrenameat.tag, original.tag);
        assert_eq!(trenameat_bytes_written, 33); // Trenameat is 33 bytes
    }

    #[test]
    fn test_roundtrip_tunlinkat_runlinkat() {
        // Create a Tunlinkat message
        let original = TunlinkatMessage::new(456, 789, "filename".to_string(), 0);
        let mut tunlinkat_buf = [0u8; 64];
        let tunlinkat_bytes_written = original.serialize(&mut tunlinkat_buf).unwrap();

        // Create a separate Runlinkat message with the same tag
        let _runlinkat_msg = RunlinkatMessage::new(original.tag);
        let mut runlinkat_buf = [0u8; 16];

        // Manually create Runlinkat buffer
        // Write size[4] = 7 (little-endian)
        runlinkat_buf[0] = 7;
        runlinkat_buf[1] = 0;
        runlinkat_buf[2] = 0;
        runlinkat_buf[3] = 0;

        // Write message type[1] = Runlinkat (77)
        runlinkat_buf[4] = P9MsgType::Runlinkat as u8;

        // Write tag[2] = 456 (little-endian)
        runlinkat_buf[5] = (456 & 0xff) as u8;
        runlinkat_buf[6] = ((456 >> 8) & 0xff) as u8;

        // Deserialize as Runlinkat
        let (runlinkat, bytes_consumed) = RunlinkatMessage::deserialize(&runlinkat_buf).unwrap();

        // Verify roundtrip
        assert_eq!(bytes_consumed, 7);
        assert_eq!(runlinkat.tag, original.tag);
        assert_eq!(tunlinkat_bytes_written, 25); // Tunlinkat is 25 bytes
    }

    #[test]
    fn test_p9_write_errors() {
        // Test null buffer error
        let result = p9_write(0, core::ptr::null(), 10);
        assert_eq!(result, Err(HostWriteError::NullBuffer));

        // Test zero length error
        let buf = [0u8; 10];
        let result = p9_write(0, buf.as_ptr(), 0);
        assert_eq!(result, Err(HostWriteError::ZeroLength));
    }

    #[test]
    fn test_p9_read_message_errors() {
        // Test buffer too small error
        let mut buf = [0u8; 3];
        let result = p9_read_message(0, &mut buf);
        assert_eq!(result, Err(HostReadError::BufferTooSmall));
    }

    #[test]
    fn test_host_error_display() {
        // Test HostReadError display
        assert_eq!(
            format!("{}", HostReadError::NullBuffer),
            "Null buffer provided for host read"
        );
        assert_eq!(
            format!("{}", HostReadError::ZeroLength),
            "Zero length buffer provided for host read"
        );
        assert_eq!(
            format!("{}", HostReadError::NoData),
            "No data available to read from host"
        );
        assert_eq!(
            format!("{}", HostReadError::BufferTooSmall),
            "Buffer too small for P9 message (minimum 4 bytes)"
        );
        assert_eq!(
            format!("{}", HostReadError::IncompleteLengthPrefix),
            "Failed to read complete 4-byte length prefix"
        );
        assert_eq!(
            format!(
                "{}",
                HostReadError::InvalidLength {
                    length: 100,
                    max_allowed: 50
                }
            ),
            "Invalid message length: 100 (max allowed: 50)"
        );
        assert_eq!(
            format!(
                "{}",
                HostReadError::LengthMismatch {
                    expected: 10,
                    actual: 5
                }
            ),
            "Length mismatch: expected 10 bytes, got 5"
        );

        // Test HostWriteError display
        assert_eq!(
            format!("{}", HostWriteError::NullBuffer),
            "Null buffer provided for host write"
        );
        assert_eq!(
            format!("{}", HostWriteError::ZeroLength),
            "Zero length buffer provided for host write"
        );
        assert_eq!(
            format!("{}", HostWriteError::NoDataWritten),
            "No data was written to host"
        );
        assert_eq!(
            format!(
                "{}",
                HostWriteError::PartialWrite {
                    expected: 10,
                    actual: 5
                }
            ),
            "Partial write: expected 10 bytes, wrote 5 bytes"
        );
    }
}
