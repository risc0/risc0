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

