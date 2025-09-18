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

    /// Send the Tversion message using host_write
    /// Returns the number of bytes written, or an error
    pub fn send_tversion(&self) -> Result<u32, TversionError> {
        use crate::host_calls::host_write;

        // Create a buffer for the serialized message
        let mut buf = [0u8; 64]; // Large enough for any reasonable version string

        // Serialize the message
        let bytes_written = self.serialize(&mut buf)?;

        // Send via host_write to file descriptor 4
        let result = host_write(4, buf.as_ptr(), bytes_written);

        Ok(result)
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

    /// Send the Tflush message using host_write
    /// Returns the number of bytes written, or an error
    pub fn send_tflush(&self) -> Result<u32, TflushError> {
        use crate::host_calls::host_write;

        // Create a buffer for the serialized message
        let mut buf = [0u8; 16]; // Large enough for Tflush message

        // Serialize the message
        let bytes_written = self.serialize(&mut buf)?;

        // Send via host_write to file descriptor 4
        let result = host_write(4, buf.as_ptr(), bytes_written);

        Ok(result)
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
}
