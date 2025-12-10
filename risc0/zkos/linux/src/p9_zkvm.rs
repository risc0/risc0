//! zkVM-specific P9 I/O operations
//!
//! This module contains the zkVM-specific implementation for P9 protocol communication.
//! It handles:
//! - Reading and writing P9 messages via zkVM host calls
//! - Tracking all P9 traffic with a cumulative hash (for proof verification)
//! - Chunking I/O operations to respect zkVM's 1024-byte limit
//!
//! The core P9 protocol logic in `p9.rs` is generic and can work with different
//! transport implementations. This module provides the zkVM-specific transport layer.

#![allow(dead_code)] // Functions are re-exported and used via p9 module

use crate::p9::*;
use crate::p9_backend::P9Backend;
use core::fmt;

/// Static mutable global to store the traffic hash value
static mut TRAFFIC_HASH: [u8; 32] = [0; 32];

/// P9 traffic hash update function that performs a 32-byte hash on input data and updates the traffic hash
///
/// This function:
/// 1. Performs a 32-byte hash operation on the input slice
/// 2. Combines the result with the previous hash stored in TRAFFIC_HASH
/// 3. Updates TRAFFIC_HASH with the new combined hash
///
/// # Arguments
/// * `data` - The u8 slice to hash
///
/// # Safety
/// This function uses unsafe code to access the static mutable TRAFFIC_HASH
pub fn p9_update_traffic_hash(data: &[u8]) {
    // Create a 32-byte hash of the input data
    let mut data_hash = [0u8; 32];

    // XXX this should be using real SHA eventually
    // Simple hash algorithm: distribute input bytes across the 32-byte output
    for (i, &byte) in data.iter().enumerate() {
        let pos = i % 32;
        data_hash[pos] ^= byte;
        // Also mix with position to avoid simple patterns
        data_hash[pos] = data_hash[pos].wrapping_add((i as u8).wrapping_mul(7));
    }

    // Combine with previous hash using XOR
    unsafe {
        let mut combined_hash = [0u8; 32];
        for i in 0..32 {
            combined_hash[i] = TRAFFIC_HASH[i] ^ data_hash[i];
        }
        TRAFFIC_HASH = combined_hash;
    }
}

/// Get the current P9 traffic hash value
///
/// # Returns
/// * `[u8; 32]` - The current 32-byte traffic hash value
///
/// # Safety
/// This function uses unsafe code to access the static mutable TRAFFIC_HASH
pub fn get_p9_traffic_hash() -> [u8; 32] {
    unsafe { TRAFFIC_HASH }
}

/// Helper function to send a serialized message via p9_write
/// Returns the number of bytes written, or an error
pub(crate) fn p9_send_message(buf: &[u8], bytes_written: usize) -> Result<u32, HostWriteError> {
    // Update traffic hash with the message being sent
    p9_update_traffic_hash(&buf[..bytes_written]);

    p9_write(4, buf.as_ptr(), bytes_written)
}

/// P9 function for reading messages with length prefix
///
/// This function implements the common P9 pattern of reading a 4-byte length prefix
/// followed by the actual message data. It handles the length parsing and validation
/// automatically.
///
/// # Arguments
/// * `fd` - File descriptor to read from
/// * `buf` - Buffer to read data into (must be at least 4 bytes)
///
/// # Returns
/// * `Result<u32, HostReadError>` - Total number of bytes read (including 4-byte prefix) on success
pub fn p9_read_message(fd: u32, buf: &mut [u8]) -> Result<u32, HostReadError> {
    use crate::host_calls::host_read;

    const MAX_IO_BYTES: usize = 1024;

    if buf.len() < 4 {
        return Err(HostReadError::BufferTooSmall);
    }

    // Read the length prefix (4 bytes)
    let len_prefix = host_read(fd, buf.as_mut_ptr(), 4);
    if len_prefix != 4 {
        return Err(HostReadError::IncompleteLengthPrefix);
    }

    // Parse the length (little-endian)
    let data_len = u32::from_le_bytes([buf[0], buf[1], buf[2], buf[3]]);

    // Validate the length is reasonable
    if !(5..=buf.len() as u32).contains(&data_len) {
        return Err(HostReadError::InvalidLength {
            length: data_len,
            max_allowed: buf.len() as u32,
        });
    }

    // Read the rest of the message in chunks, respecting MAX_IO_BYTES limit
    let remaining_len = (data_len - 4) as usize;
    let mut total_read = 0;
    let mut offset = 4; // Start reading after the 4-byte length prefix

    while total_read < remaining_len {
        let bytes_remaining = remaining_len - total_read;
        let chunk_size = core::cmp::min(MAX_IO_BYTES, bytes_remaining);
        let len = host_read(fd, unsafe { buf.as_mut_ptr().add(offset) }, chunk_size);

        if len == 0 {
            return Err(HostReadError::LengthMismatch {
                expected: remaining_len as u32,
                actual: total_read as u32,
            });
        }

        total_read += len as usize;
        offset += len as usize;
    }

    if total_read != remaining_len {
        return Err(HostReadError::LengthMismatch {
            expected: remaining_len as u32,
            actual: total_read as u32,
        });
    }

    // Update traffic hash with the full message being read
    p9_update_traffic_hash(&buf[..data_len as usize]);

    Ok(data_len)
}

/// P9 function for writing data to the host
///
/// This function wraps the existing `host_write` function and provides additional
/// error handling and logging capabilities.
///
/// # Arguments
/// * `fd` - File descriptor to write to
/// * `buf` - Buffer containing data to write
/// * `buf_len` - Number of bytes to write
///
/// # Returns
/// * `Result<u32, HostWriteError>` - Number of bytes written on success, or error on failure
pub fn p9_write(fd: u32, buf: *const u8, buf_len: usize) -> Result<u32, HostWriteError> {
    use crate::host_calls::host_write;

    const MAX_IO_BYTES: usize = 1024;

    if buf.is_null() {
        return Err(HostWriteError::NullBuffer);
    }

    if buf_len == 0 {
        return Err(HostWriteError::ZeroLength);
    }

    let mut offset = 0usize;

    // Write in chunks of MAX_IO_BYTES
    while offset < buf_len {
        let chunk_size = core::cmp::min(MAX_IO_BYTES, buf_len - offset);
        let chunk_ptr = unsafe { buf.add(offset) };

        // XXX: host_write doesn't return reliable length, so we assume success
        let _bytes_written = host_write(fd, chunk_ptr, chunk_size);

        offset += chunk_size;
    }

    Ok(buf_len as u32)
}

/// Error types for custom host read operations
#[derive(Debug, Clone, PartialEq)]
pub enum HostReadError {
    NullBuffer,
    ZeroLength,
    NoData,
    BufferTooSmall,
    IncompleteLengthPrefix,
    InvalidLength { length: u32, max_allowed: u32 },
    LengthMismatch { expected: u32, actual: u32 },
}

impl fmt::Display for HostReadError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            HostReadError::NullBuffer => write!(f, "Null buffer provided for host read"),
            HostReadError::ZeroLength => write!(f, "Zero length buffer provided for host read"),
            HostReadError::NoData => write!(f, "No data available to read from host"),
            HostReadError::BufferTooSmall => {
                write!(f, "Buffer too small for P9 message (minimum 4 bytes)")
            }
            HostReadError::IncompleteLengthPrefix => {
                write!(f, "Failed to read complete 4-byte length prefix")
            }
            HostReadError::InvalidLength {
                length,
                max_allowed,
            } => {
                write!(
                    f,
                    "Invalid message length: {} (max allowed: {})",
                    length, max_allowed
                )
            }
            HostReadError::LengthMismatch { expected, actual } => {
                write!(
                    f,
                    "Length mismatch: expected {} bytes, got {}",
                    expected, actual
                )
            }
        }
    }
}

/// Error types for custom host write operations
#[derive(Debug, Clone, PartialEq)]
pub enum HostWriteError {
    NullBuffer,
    ZeroLength,
    NoDataWritten,
    PartialWrite { expected: usize, actual: usize },
    InternalError,
}

impl fmt::Display for HostWriteError {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        match self {
            HostWriteError::NullBuffer => write!(f, "Null buffer provided for host write"),
            HostWriteError::ZeroLength => write!(f, "Zero length buffer provided for host write"),
            HostWriteError::NoDataWritten => write!(f, "No data was written to host"),
            HostWriteError::PartialWrite { expected, actual } => {
                write!(
                    f,
                    "Partial write: expected {} bytes, wrote {} bytes",
                    expected, actual
                )
            }
            HostWriteError::InternalError => write!(f, "Internal error during host write"),
        }
    }
}

/// zkVM backend implementation for P9 protocol
///
/// This backend serializes messages and sends them via zkVM host calls (ecalls).
/// All traffic is hashed for proof verification.
pub struct ZkvmBackend;

impl ZkvmBackend {
    pub fn new() -> Self {
        Self
    }
}

// Implement P9Backend for ZkvmBackend
impl P9Backend for ZkvmBackend {
    fn send_tversion(
        &mut self,
        msg: &TversionMessage,
    ) -> Result<P9Response<RversionMessage>, TversionError> {
        let mut buf = [0u8; 64];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TversionError::InternalError)?;
        Ok(RversionMessage::read_response())
    }

    fn send_tattach(
        &mut self,
        msg: &TattachMessage,
    ) -> Result<P9Response<RattachMessage>, TattachError> {
        let mut buf = [0u8; 256];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TattachError::InternalError)?;
        Ok(RattachMessage::read_response())
    }

    fn send_twalk(&mut self, msg: &TwalkMessage) -> Result<P9Response<RwalkMessage>, TwalkError> {
        let mut buf = [0u8; 1024];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TwalkError::InternalError)?;
        Ok(RwalkMessage::read_response())
    }

    fn send_tread(&mut self, msg: &TreadMessage) -> Result<P9Response<RreadMessage>, TreadError> {
        let mut buf = [0u8; 32];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TreadError::InternalError)?;
        Ok(RreadMessage::read_response())
    }

    fn send_twrite(
        &mut self,
        msg: &TwriteMessage,
    ) -> Result<P9Response<RwriteMessage>, TwriteError> {
        let mut buf = [0u8; 8192];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TwriteError::InternalError)?;
        Ok(RwriteMessage::read_response())
    }

    fn send_tlopen(
        &mut self,
        msg: &TlopenMessage,
    ) -> Result<P9Response<RlopenMessage>, TlopenError> {
        let mut buf = [0u8; 32];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TlopenError::InternalError)?;
        Ok(RlopenMessage::read_response())
    }

    fn send_tlcreate(
        &mut self,
        msg: &TlcreateMessage,
    ) -> Result<P9Response<RlcreateMessage>, TlcreateError> {
        let mut buf = [0u8; 512];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TlcreateError::InternalError)?;
        Ok(RlcreateMessage::read_response())
    }

    fn send_tgetattr(
        &mut self,
        msg: &TgetattrMessage,
    ) -> Result<P9Response<RgetattrMessage>, TgetattrError> {
        let mut buf = [0u8; 32];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TgetattrError::InternalError)?;
        Ok(RgetattrMessage::read_response())
    }

    fn send_tsetattr(
        &mut self,
        msg: &TsetattrMessage,
    ) -> Result<P9Response<RsetattrMessage>, TsetattrError> {
        let mut buf = [0u8; 128];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TsetattrError::InternalError)?;
        Ok(RsetattrMessage::read_response())
    }

    fn send_treaddir(
        &mut self,
        msg: &TreaddirMessage,
    ) -> Result<P9Response<RreaddirMessage>, TreaddirError> {
        let mut buf = [0u8; 32];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TreaddirError::InternalError)?;
        Ok(RreaddirMessage::read_response())
    }

    fn send_treadlink(
        &mut self,
        msg: &TreadlinkMessage,
    ) -> Result<P9Response<RreadlinkMessage>, TreadlinkError> {
        let mut buf = [0u8; 16];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TreadlinkError::InternalError)?;
        Ok(RreadlinkMessage::read_response())
    }

    fn send_tsymlink(
        &mut self,
        msg: &TsymlinkMessage,
    ) -> Result<P9Response<RsymlinkMessage>, TsymlinkError> {
        let mut buf = [0u8; 512];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TsymlinkError::InternalError)?;
        Ok(RsymlinkMessage::read_response())
    }

    fn send_tmknod(
        &mut self,
        msg: &TmknodMessage,
    ) -> Result<P9Response<RmknodMessage>, TmknodError> {
        let mut buf = [0u8; 512];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TmknodError::InternalError)?;
        Ok(RmknodMessage::read_response())
    }

    fn send_tmkdir(
        &mut self,
        msg: &TmkdirMessage,
    ) -> Result<P9Response<RmkdirMessage>, TmkdirError> {
        let mut buf = [0u8; 512];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TmkdirError::InternalError)?;
        Ok(RmkdirMessage::read_response())
    }

    fn send_tunlinkat(
        &mut self,
        msg: &TunlinkatMessage,
    ) -> Result<P9Response<RunlinkatMessage>, TunlinkatError> {
        let mut buf = [0u8; 512];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TunlinkatError::InternalError)?;
        Ok(RunlinkatMessage::read_response())
    }

    fn send_trenameat(
        &mut self,
        msg: &TrenameatMessage,
    ) -> Result<P9Response<RrenameatMessage>, TrenameatError> {
        let mut buf = [0u8; 512];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TrenameatError::InternalError)?;
        Ok(RrenameatMessage::read_response())
    }

    fn send_tclunk(
        &mut self,
        msg: &TclunkMessage,
    ) -> Result<P9Response<RclunkMessage>, TclunkError> {
        let mut buf = [0u8; 16];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TclunkError::InternalError)?;
        Ok(RclunkMessage::read_response())
    }

    fn send_tremove(
        &mut self,
        msg: &TremoveMessage,
    ) -> Result<P9Response<RremoveMessage>, TremoveError> {
        let mut buf = [0u8; 16];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TremoveError::InternalError)?;
        Ok(RremoveMessage::read_response())
    }

    fn send_tfsync(
        &mut self,
        msg: &TfsyncMessage,
    ) -> Result<P9Response<RfsyncMessage>, TfsyncError> {
        let mut buf = [0u8; 16];
        let bytes_written = msg.serialize(&mut buf)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TfsyncError::InternalError)?;

        // Read response manually since RfsyncMessage doesn't implement ReadableMessage
        let mut rbuf = [0u8; 8192];
        match p9_read_message(3, &mut rbuf) {
            Ok(data_len) => {
                let msg_type = rbuf[4];
                if msg_type == P9MsgType::RLerror as u8 {
                    match RlerrorMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((rlerror, _)) => Ok(P9Response::Error(rlerror)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                } else {
                    match RfsyncMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((response, _)) => Ok(P9Response::Success(response)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                }
            }
            Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
        }
    }

    fn send_tlink(&mut self, msg: &TlinkMessage) -> Result<P9Response<RlinkMessage>, TlinkError> {
        let mut buf = [0u8; 128];
        let bytes_written = msg
            .serialize(&mut buf)
            .map_err(|_| TlinkError::InternalError)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TlinkError::InternalError)?;

        let mut rbuf = [0u8; 1024];
        match p9_read_message(3, &mut rbuf) {
            Ok(data_len) => {
                let msg_type = rbuf[4];
                if msg_type == P9MsgType::RLerror as u8 {
                    match RlerrorMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((rlerror, _)) => Ok(P9Response::Error(rlerror)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                } else {
                    match RlinkMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((response, _)) => Ok(P9Response::Success(response)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                }
            }
            Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
        }
    }

    fn send_trename(
        &mut self,
        msg: &TrenameMessage,
    ) -> Result<P9Response<RrenameMessage>, TrenameError> {
        let mut buf = [0u8; 128];
        let bytes_written = msg
            .serialize(&mut buf)
            .map_err(|_| TrenameError::InternalError)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TrenameError::InternalError)?;

        let mut rbuf = [0u8; 1024];
        match p9_read_message(3, &mut rbuf) {
            Ok(data_len) => {
                let msg_type = rbuf[4];
                if msg_type == P9MsgType::RLerror as u8 {
                    match RlerrorMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((rlerror, _)) => Ok(P9Response::Error(rlerror)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                } else {
                    match RrenameMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((response, _)) => Ok(P9Response::Success(response)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                }
            }
            Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
        }
    }

    fn send_txattrwalk(
        &mut self,
        msg: &TxattrwalkMessage,
    ) -> Result<P9Response<RxattrwalkMessage>, TxattrwalkError> {
        let mut buf = [0u8; 128];
        let bytes_written = msg
            .serialize(&mut buf)
            .map_err(|_| TxattrwalkError::InternalError)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TxattrwalkError::InternalError)?;

        let mut rbuf = [0u8; 1024];
        match p9_read_message(3, &mut rbuf) {
            Ok(data_len) => {
                let msg_type = rbuf[4];
                if msg_type == P9MsgType::RLerror as u8 {
                    match RlerrorMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((rlerror, _)) => Ok(P9Response::Error(rlerror)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                } else {
                    match RxattrwalkMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((response, _)) => Ok(P9Response::Success(response)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                }
            }
            Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
        }
    }

    fn send_txattrcreate(
        &mut self,
        msg: &TxattrcreateMessage,
    ) -> Result<P9Response<RxattrcreateMessage>, TxattrcreateError> {
        let mut buf = [0u8; 128];
        let bytes_written = msg
            .serialize(&mut buf)
            .map_err(|_| TxattrcreateError::InternalError)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TxattrcreateError::InternalError)?;

        let mut rbuf = [0u8; 1024];
        match p9_read_message(3, &mut rbuf) {
            Ok(data_len) => {
                let msg_type = rbuf[4];
                if msg_type == P9MsgType::RLerror as u8 {
                    match RlerrorMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((rlerror, _)) => Ok(P9Response::Error(rlerror)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                } else {
                    match RxattrcreateMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((response, _)) => Ok(P9Response::Success(response)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                }
            }
            Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
        }
    }

    fn send_tflush(
        &mut self,
        msg: &TflushMessage,
    ) -> Result<P9Response<RflushMessage>, TflushError> {
        let mut buf = [0u8; 16];
        let bytes_written = msg
            .serialize(&mut buf)
            .map_err(|_| TflushError::InternalError)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TflushError::InternalError)?;
        let mut rbuf = [0u8; 1024];
        match p9_read_message(3, &mut rbuf) {
            Ok(data_len) => {
                let msg_type = rbuf[4];
                if msg_type == P9MsgType::RLerror as u8 {
                    match RlerrorMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((rlerror, _)) => Ok(P9Response::Error(rlerror)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                } else {
                    match RflushMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((response, _)) => Ok(P9Response::Success(response)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                }
            }
            Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
        }
    }

    fn send_tauth(&mut self, msg: &TauthMessage) -> Result<P9Response<RauthMessage>, TauthError> {
        let mut buf = [0u8; 128];
        let bytes_written = msg
            .serialize(&mut buf)
            .map_err(|_| TauthError::InternalError)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TauthError::InternalError)?;
        let mut rbuf = [0u8; 1024];
        match p9_read_message(3, &mut rbuf) {
            Ok(data_len) => {
                let msg_type = rbuf[4];
                if msg_type == P9MsgType::RLerror as u8 {
                    match RlerrorMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((rlerror, _)) => Ok(P9Response::Error(rlerror)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                } else {
                    match RauthMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((response, _)) => Ok(P9Response::Success(response)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                }
            }
            Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
        }
    }

    fn send_tstatfs(
        &mut self,
        msg: &TstatfsMessage,
    ) -> Result<P9Response<RstatfsMessage>, TstatfsError> {
        let mut buf = [0u8; 16];
        let bytes_written = msg
            .serialize(&mut buf)
            .map_err(|_| TstatfsError::InternalError)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TstatfsError::InternalError)?;
        let mut rbuf = [0u8; 1024];
        match p9_read_message(3, &mut rbuf) {
            Ok(data_len) => {
                let msg_type = rbuf[4];
                if msg_type == P9MsgType::RLerror as u8 {
                    match RlerrorMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((rlerror, _)) => Ok(P9Response::Error(rlerror)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                } else {
                    match RstatfsMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((response, _)) => Ok(P9Response::Success(response)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                }
            }
            Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
        }
    }

    fn send_tlock(&mut self, msg: &TlockMessage) -> Result<P9Response<RlockMessage>, TlockError> {
        let mut buf = [0u8; 128];
        let bytes_written = msg
            .serialize(&mut buf)
            .map_err(|_| TlockError::InternalError)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TlockError::InternalError)?;
        let mut rbuf = [0u8; 1024];
        match p9_read_message(3, &mut rbuf) {
            Ok(data_len) => {
                let msg_type = rbuf[4];
                if msg_type == P9MsgType::RLerror as u8 {
                    match RlerrorMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((rlerror, _)) => Ok(P9Response::Error(rlerror)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                } else {
                    match RlockMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((response, _)) => Ok(P9Response::Success(response)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                }
            }
            Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
        }
    }

    fn send_tgetlock(
        &mut self,
        msg: &TgetlockMessage,
    ) -> Result<P9Response<RgetlockMessage>, TgetlockError> {
        let mut buf = [0u8; 128];
        let bytes_written = msg
            .serialize(&mut buf)
            .map_err(|_| TgetlockError::InternalError)?;
        p9_send_message(&buf, bytes_written).map_err(|_| TgetlockError::InternalError)?;
        let mut rbuf = [0u8; 1024];
        match p9_read_message(3, &mut rbuf) {
            Ok(data_len) => {
                let msg_type = rbuf[4];
                if msg_type == P9MsgType::RLerror as u8 {
                    match RlerrorMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((rlerror, _)) => Ok(P9Response::Error(rlerror)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                } else {
                    match RgetlockMessage::deserialize(&rbuf[..data_len as usize]) {
                        Ok((response, _)) => Ok(P9Response::Success(response)),
                        Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
                    }
                }
            }
            Err(_) => Ok(P9Response::Error(RlerrorMessage::new(0, 0))),
        }
    }

    fn write_output_data(&mut self, _data: &[u8]) -> Result<usize, u32> {
        // No-op for zkvm backend
        Ok(0)
    }

    fn read_data(&mut self, _buf: &mut [u8]) -> Result<usize, u32> {
        // No-op for zkvm backend, returns empty
        Ok(0)
    }

    fn load_and_unpack_tar_to_tmp(&mut self) -> Result<usize, u32> {
        // No-op for zkvm backend
        Ok(0)
    }
}
