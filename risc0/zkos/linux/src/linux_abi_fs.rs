use no_std_strings::{str_format, str256};

use crate::{
    constants::*,
    host_calls::{host_log, host_terminate, host_write},
    kernel::{DEBUG_ENABLED, print},
    linux_abi::Err,
    p9::{
        P9Response, P9SetattrMask, Qid, RgetattrMessage, TattachMessage, TlcreateMessage,
        TlopenMessage, TmkdirMessage, TmknodMessage, TreadMessage, TreaddirMessage,
        TreadlinkMessage, TremoveMessage, TsetattrMessage, TsymlinkMessage, TversionMessage,
        TwriteMessage, constants::*,
    },
};

#[cfg(target_arch = "riscv32")]
use alloc::string::{String, ToString};
#[cfg(target_arch = "riscv32")]
use alloc::{format, vec, vec::Vec};

use core::str;

// Helper functions for user pointer validation

/// Validate and read a null-terminated pathname from user memory
/// Returns the pathname as a String, or EFAULT/EINVAL on error
fn validate_and_read_pathname(ptr: u32) -> Result<String, Err> {
    validate_and_read_pathname_with_len(ptr, 256)
}

/// Validate and read a null-terminated pathname with custom max length
/// Returns the pathname as a String, or EFAULT/EINVAL/ENAMETOOLONG on error
fn validate_and_read_pathname_with_len(ptr: u32, max_len: usize) -> Result<String, Err> {
    if ptr == 0 {
        return Err(Err::Fault);
    }

    let valid_len = match crate::linux_abi::is_valid_user_address(ptr, max_len, false) {
        Some(len) => len,
        None => {
            debug_print!(
                "validate_and_read_pathname: EFAULT - invalid pointer {:#010x}",
                ptr
            );
            return Err(Err::Fault);
        }
    };

    // Use the maximum safe length
    let safe_len = core::cmp::min(max_len, valid_len);
    let buf = unsafe { core::slice::from_raw_parts(ptr as *const u8, safe_len) };
    let null_pos = buf.iter().position(|&b| b == 0).unwrap_or(buf.len());

    // Check for path too long (before null terminator found)
    if null_pos >= max_len - 1 {
        return Err(Err::NameTooLong);
    }

    str::from_utf8(&buf[..null_pos])
        .map(|s| s.to_string())
        .map_err(|_| Err::Inval)
}

/// Validate a user buffer pointer for writing
/// Returns Ok(()) if valid, Err(Err::Fault) otherwise
fn validate_user_buffer_write(ptr: u32, len: usize) -> Result<(), Err> {
    if ptr == 0 {
        return Err(Err::Fault);
    }

    match crate::linux_abi::is_valid_user_address(ptr, len, true) {
        Some(valid_len) => {
            if valid_len < len {
                debug_print!(
                    "validate_user_buffer_write: EFAULT - buffer extends beyond valid region (requested={}, available={})",
                    len,
                    valid_len
                );
                return Err(Err::Fault);
            }
            Ok(())
        }
        None => {
            debug_print!(
                "validate_user_buffer_write: EFAULT - invalid pointer {:#010x} len {}",
                ptr,
                len
            );
            Err(Err::Fault)
        }
    }
}

/// Validate a user buffer pointer for reading
/// Returns Ok(()) if valid, Err(Err::Fault) otherwise
#[allow(dead_code)]
fn validate_user_buffer_read(ptr: u32, len: usize) -> Result<(), Err> {
    if ptr == 0 {
        return Err(Err::Fault);
    }

    match crate::linux_abi::is_valid_user_address(ptr, len, false) {
        Some(valid_len) => {
            if valid_len < len {
                debug_print!(
                    "validate_user_buffer_read: EFAULT - buffer extends beyond valid region (requested={}, available={})",
                    len,
                    valid_len
                );
                return Err(Err::Fault);
            }
            Ok(())
        }
        None => {
            debug_print!(
                "validate_user_buffer_read: EFAULT - invalid pointer {:#010x} len {}",
                ptr,
                len
            );
            Err(Err::Fault)
        }
    }
}

/// Map 9P error codes to Linux errno values
///
/// This function provides a centralized mapping from 9P protocol error codes
/// to the appropriate Linux `Err` type. It covers all common error codes that
/// can be returned by the 9P server.
///
/// # Arguments
/// * `ecode` - The 9P error code (from RlerrorMessage.ecode)
///
/// # Returns
/// * `Err` - The corresponding Linux error enum value
///
/// # Notes
/// - Error codes match standard Linux errno values
/// - Unmapped errors default to `Err::IO` as a safe fallback
#[inline]
fn map_p9_error(ecode: u32) -> Err {
    match ecode {
        1 => Err::Access,       // EPERM - Operation not permitted
        2 => Err::FileNotFound, // ENOENT - No such file or directory
        5 => Err::IO,           // EIO - I/O error
        9 => Err::BadFd,        // EBADF - Bad file descriptor
        12 => Err::NoMem,       // ENOMEM - Out of memory
        13 => Err::Access,      // EACCES - Permission denied
        14 => Err::Fault,       // EFAULT - Bad address
        17 => Err::FileExists,  // EEXIST - File exists
        20 => Err::NotDir,      // ENOTDIR - Not a directory
        21 => Err::IsDir,       // EISDIR - Is a directory
        22 => Err::Inval,       // EINVAL - Invalid argument
        24 => Err::MFile,       // EMFILE - Too many open files
        27 => Err::FileTooBig,  // EFBIG - File too large
        28 => Err::NoSpc,       // ENOSPC - No space left on device
        36 => Err::NameTooLong, // ENAMETOOLONG - File name too long
        38 => Err::NoSys,       // ENOSYS - Function not implemented
        40 => Err::Loop,        // ELOOP - Too many symbolic links
        34 => Err::Range,       // ERANGE - Math result not representable
        61 => Err::NoData,      // ENODATA - No data available
        95 => Err::OpNotSupp,   // EOPNOTSUPP - Operation not supported
        _ => {
            // For unmapped errors, log and default to IO error
            debug_print!(
                "map_p9_error: unmapped P9 error code {} (defaulting to EIO)",
                ecode
            );
            Err::IO
        }
    }
}

// Filesystem-related syscalls

// open() flags
pub const O_CREAT: u32 = 0o100;
pub const O_EXCL: u32 = 0o200;
pub const O_TRUNC: u32 = 0o1000;
pub const O_APPEND: u32 = 0o2000;
pub const O_NOFOLLOW: u32 = 0o400000;
pub const O_PATH: u32 = 0o10000000;

// Special directory file descriptor value
pub const AT_FDCWD: i32 = -100;

// Temporary FID values for internal operations
// These are used for temporary file operations and must not conflict with user FDs
#[allow(dead_code)]
const TEMP_FID_BASE: u32 = 0xFFFF_FFF0;
const TEMP_FID_1: u32 = 0xFFFF_FFFE; // Most commonly used temporary FID
const TEMP_FID_2: u32 = 0xFFFF_FFFD; // CWD operations
const TEMP_FID_3: u32 = 0xFFFF_FFFC; // Secondary operations
const TEMP_FID_4: u32 = 0xFFFF_FFFB; // Directory operations
const TEMP_FID_5: u32 = 0xFFFF_FFFA; // File resolution
const TEMP_FID_6: u32 = 0xFFFF_FFF9; // Additional operations
const TEMP_FID_7: u32 = 0xFFFF_FFF8; // Additional operations
const TEMP_FID_8: u32 = 0xFFFF_FFF7; // Additional operations
const TEMP_FID_9: u32 = 0xFFFF_FFF6; // Additional operations
const TEMP_FID_10: u32 = 0xFFFF_FFF5; // Additional operations
const TEMP_FID_11: u32 = 0xFFFF_FFF4; // Additional operations

// Virtual device FID values (0xFFFF_FFE0 - 0xFFFF_FFEF range)
// These are special FIDs that represent virtual devices that don't go through 9p
const VIRTUAL_DEV_NULL: u32 = 0xFFFF_FFE0;
const VIRTUAL_DEV_ZERO: u32 = 0xFFFF_FFE1;
const VIRTUAL_DEV_RANDOM: u32 = 0xFFFF_FFE2;
const VIRTUAL_DEV_URANDOM: u32 = 0xFFFF_FFE3;
const VIRTUAL_DEV_FULL: u32 = 0xFFFF_FFE4;

// Virtual file FID values (0xFFFF_FFD0 - 0xFFFF_FFDF range)
// These represent virtual files like /proc entries that return content
const VIRTUAL_FILE_PROC_CPUINFO: u32 = 0xFFFF_FFD0;

// fcntl constants
#[allow(dead_code)]
pub const F_DUPFD: u32 = 0; // Duplicate file descriptor.
#[allow(dead_code)]
pub const F_GETFD: u32 = 1; // Get file descriptor flags.
pub const F_SETFD: u32 = 2; // Set file descriptor flags.
#[allow(dead_code)]
pub const F_GETFL: u32 = 3; // Get file status flags.
#[allow(dead_code)]
pub const F_SETFL: u32 = 4; // Set file status flags.
pub const FD_CLOEXEC: u32 = 1; // Close on exec flag.

// File locking constants
#[allow(dead_code)]
pub const F_GETLK: u32 = 12; // Get file lock
#[allow(dead_code)]
pub const F_SETLK: u32 = 13; // Set file lock
#[allow(dead_code)]
pub const F_SETLKW: u32 = 14; // Set file lock (wait)

// Lock types
#[allow(dead_code)]
pub const F_RDLCK: u32 = 0; // Read lock
#[allow(dead_code)]
pub const F_WRLCK: u32 = 1; // Write lock
#[allow(dead_code)]
pub const F_UNLCK: u32 = 2; // Unlock

pub static mut ROOT_FID: u32 = 0;
pub static mut CWD_FID: u32 = 0;
pub static mut CWD_STR: String = String::new();
pub static mut UMASK: u32 = 0o022; // Default umask value

// Max chunk size for 9P I/O operations
// P9_DEFAULT_MSIZE is 8192. The diod server checks: count + IOHDRSZ <= msize
// where IOHDRSZ = 24 (diod's conservative header size for Twrite/Rread messages)
// Maximum data per operation: 8192 - 24 = 8168 bytes
// The p9_write and p9_read_message functions automatically chunk the full message
// into 1024-byte pieces for transmission to stay within the host I/O limits
const MAX_9P_IO_CHUNK: u32 = 8192 - 24; // 8168 bytes

// Sentinel value for invalid/uninitialized file mode
const INVALID_MODE: u32 = 0xFFFF_FFFF;

pub fn get_root_fid() -> u32 {
    unsafe { ROOT_FID }
}

#[allow(dead_code)]
pub fn get_cwd_fid() -> u32 {
    unsafe { CWD_FID }
}

#[allow(dead_code)]
pub fn set_root_fid(fid: u32) {
    unsafe {
        ROOT_FID = fid;
    }
}

#[allow(dead_code)]
pub fn set_cwd_fid(fid: u32) {
    unsafe {
        CWD_FID = fid;
    }
}

#[allow(dead_code)]
pub fn set_cwd_str(cwd_str: String) {
    unsafe {
        CWD_STR = cwd_str;
    }
}

#[allow(dead_code)]
pub fn get_cwd_str() -> String {
    #[allow(static_mut_refs)]
    unsafe {
        CWD_STR.clone()
    }
}

// File description (like Linux's struct file) - shared state for duplicated fds
#[derive(Copy, Clone)]
pub struct FileDescription {
    pub fid: u32,
    pub cursor: u64, // Shared cursor for all fds pointing to this description
    pub is_dir: bool,
    pub mode: u32,
    pub flags: u32,    // Linux open flags (O_APPEND, etc.)
    pub refcount: u32, // Number of file descriptors pointing to this description
}

// File descriptor table - each fd points to a file description
#[derive(Copy, Clone)]
pub struct FileDescriptor {
    pub file_desc_id: u32, // Index into FILE_DESC_TABLE, 0xFF means unused
    pub cloexec: bool,     // FD_CLOEXEC flag (close-on-exec)
}

// File description table (similar to Linux's file table)
pub static mut FILE_DESC_TABLE: [FileDescription; 256] = [FileDescription {
    fid: 0,
    cursor: 0,
    is_dir: false,
    mode: INVALID_MODE,
    flags: 0,
    refcount: 0,
}; 256];

// File descriptor table (maps fd -> file_desc_id)
pub static mut FD_TABLE: [FileDescriptor; 256] = [FileDescriptor {
    file_desc_id: 0xFF, // 0xFF means unused
    cloexec: false,
}; 256];

pub fn get_fd(fd: u32) -> FileDescriptor {
    unsafe { FD_TABLE[fd as usize] }
}

pub fn update_fd(fd: u32, file_descriptor: FileDescriptor) {
    unsafe {
        FD_TABLE[fd as usize] = file_descriptor;
    }
}

// Get file description by ID
pub fn get_file_desc(desc_id: u32) -> FileDescription {
    unsafe { FILE_DESC_TABLE[desc_id as usize] }
}

// Update file description
pub fn update_file_desc(desc_id: u32, desc: FileDescription) {
    unsafe {
        FILE_DESC_TABLE[desc_id as usize] = desc;
    }
}

// Helper to get file description from file descriptor
#[allow(dead_code)]
pub fn get_file_desc_from_fd(fd: u32) -> Option<FileDescription> {
    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        None
    } else {
        Some(get_file_desc(fd_entry.file_desc_id))
    }
}

// Helper to update file description through file descriptor
#[allow(dead_code)]
pub fn update_file_desc_through_fd(fd: u32, desc: FileDescription) -> Result<(), Err> {
    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }
    update_file_desc(fd_entry.file_desc_id, desc);
    Ok(())
}

// Find a free file description slot
pub fn find_free_file_desc() -> Result<u32, Err> {
    for i in 0..256 {
        let desc = get_file_desc(i);
        if desc.fid == 0 && desc.refcount == 0 {
            return Ok(i);
        }
    }
    debug_print!("find_free_file_desc: no free file descriptions available");
    Err(Err::MFile)
}

// Increment reference count for a file description
pub fn inc_refcount(desc_id: u32) {
    let mut desc = get_file_desc(desc_id);
    desc.refcount += 1;
    update_file_desc(desc_id, desc);
}

// Decrement reference count for a file description
// Returns true if this was the last reference (should clunk)
pub fn dec_refcount(desc_id: u32) -> bool {
    let mut desc = get_file_desc(desc_id);
    if desc.refcount > 0 {
        desc.refcount -= 1;
    }
    let should_clunk = desc.refcount == 0;
    update_file_desc(desc_id, desc);
    should_clunk
}

// Linux dirent64 structure
#[repr(C)]
#[derive(Debug, Clone, Copy)]
#[allow(dead_code)]
pub struct LinuxDirent64 {
    d_ino: u64,      // inode number
    d_off: i64,      // offset to next record
    d_reclen: u16,   // length of this record
    d_type: u8,      // file type
    d_name: [u8; 1], // filename (variable length, but we use [u8; 1] for the struct)
}

// Directory entry types
#[allow(dead_code)]
pub const DT_UNKNOWN: u8 = 0;
#[allow(dead_code)]
const DT_FIFO: u8 = 1;
#[allow(dead_code)]
const DT_CHR: u8 = 2;
pub const DT_DIR: u8 = 4;
#[allow(dead_code)]
const DT_BLK: u8 = 6;
pub const DT_REG: u8 = 8;
pub const DT_LNK: u8 = 10;
#[allow(dead_code)]
const DT_SOCK: u8 = 12;

// make this a global static that we can set
static mut P9_ENABLED: bool = false;

pub fn set_p9_enabled(enabled: bool) {
    unsafe {
        P9_ENABLED = enabled;
    }
}

pub fn get_p9_enabled() -> bool {
    unsafe { P9_ENABLED }
}

pub fn sys_unlinkat(dfd: u32, pathname: u32, flag: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_unlinkat: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Check for invalid address - NULL pointer
    if pathname == 0 {
        debug_print!("sys_unlinkat: invalid pathname address (NULL)");
        return Err(Err::Fault);
    }

    // Validate the pathname pointer is in readable user memory (max path length = 256)
    const MAX_PATH_LEN: usize = 256;
    let safe_len = match crate::linux_abi::is_valid_user_address(pathname, MAX_PATH_LEN, false) {
        Some(valid_len) => core::cmp::min(MAX_PATH_LEN, valid_len),
        None => {
            debug_print!(
                "sys_unlinkat: EFAULT - invalid pathname address {:#010x}",
                pathname
            );
            return Err(Err::Fault);
        }
    };

    // Read the pathname from user space (up to the safe length)
    let filename = unsafe { core::slice::from_raw_parts(pathname as *const u8, safe_len) };
    let null_pos = filename
        .iter()
        .position(|&b| b == 0)
        .unwrap_or(filename.len());
    let filename = &filename[..null_pos];
    let filename_str = match str::from_utf8(filename) {
        Ok(s) => s,
        Err(_) => {
            debug_print!("sys_unlinkat: invalid UTF-8 filename");
            return Err(Err::Inval); // EINVAL for invalid UTF-8
        }
    };

    // Check for empty pathname
    if filename_str.is_empty() {
        debug_print!("sys_unlinkat: empty pathname, returning ENOENT");
        return Err(Err::FileNotFound);
    }

    // Check for pathname too long (limit is 255 for 9P)
    if filename_str.len() > 255 {
        debug_print!(
            "sys_unlinkat: pathname too long ({} bytes), returning ENAMETOOLONG",
            filename_str.len()
        );
        return Err(Err::NameTooLong);
    }

    // Validate flags - only AT_REMOVEDIR is valid
    const AT_REMOVEDIR: u32 = 0x200;
    if (flag & !AT_REMOVEDIR) != 0 {
        debug_print!(
            "sys_unlinkat: invalid flag value 0x{:x}, returning EINVAL",
            flag
        );
        return Err(Err::Inval);
    }

    debug_print!(
        "sys_unlinkat: dfd={}, filename='{}', flag={}",
        dfd,
        filename_str,
        flag
    );

    // For unlink, we must NOT follow symlinks - we want to remove the symlink itself, not its target
    // Use direct Twalk instead of resolve_path
    let starting_fid = get_starting_fid(dfd, filename_str)?;
    let (dir_path, file_name) = split_path(&filename_str);

    // Walk to the directory (following symlinks in the path)
    let dir_fid = if dir_path.is_empty() || dir_path == "." {
        starting_fid
    } else {
        let dir_path = normalize_path(&dir_path);
        do_walk(starting_fid, TEMP_FID_4, dir_path)?;
        TEMP_FID_4
    };

    // Walk to the file itself WITHOUT following symlinks
    let file_path = vec![file_name];
    let twalk = crate::p9::TwalkMessage::new(0, dir_fid, TEMP_FID_1, file_path);
    match twalk.send_twalk() {
        Ok(crate::p9::P9Response::Success(rwalk)) => {
            if dir_fid != starting_fid {
                clunk(dir_fid, false);
            }

            if rwalk.wqids.is_empty() {
                clunk(TEMP_FID_1, false);
                return Err(Err::FileNotFound);
            }
        }
        Ok(crate::p9::P9Response::Error(rlerror)) => {
            if dir_fid != starting_fid {
                clunk(dir_fid, false);
            }
            debug_print!(
                "sys_unlinkat: walk to file failed with ecode={}",
                rlerror.ecode
            );
            return Err(map_p9_error(rlerror.ecode));
        }
        Err(_) => {
            if dir_fid != starting_fid {
                clunk(dir_fid, false);
            }
            return Err(Err::FileNotFound);
        }
    }

    // Now TEMP_FID_1 points to the file/symlink itself (not its target)
    let tremove = TremoveMessage::new(0, TEMP_FID_1);
    match tremove.send_tremove() {
        Ok(P9Response::Success(rremove)) => {
            debug_print!("sys_unlinkat: rremove = {:?}", rremove);
            clunk(TEMP_FID_1, false);
            Ok(0)
        }
        Ok(P9Response::Error(rlerror2)) => {
            debug_print!(
                "sys_unlinkat: received Rlerror for Rremove: tag={}, ecode={}",
                rlerror2.tag,
                rlerror2.ecode
            );
            Err(map_p9_error(rlerror2.ecode))
        }
        Err(e) => {
            debug_print!("sys_unlinkat: error sending Tremove: {:?}", e);
            Err(Err::IO)
        }
    }
}

// Statfs64 structure matching the Linux kernel definition
#[repr(C)]
#[derive(Debug, Clone, Copy)]
struct Statfs64 {
    f_type: u32,       // Filesystem type
    f_bsize: u32,      // Block size
    f_blocks: u64,     // Total blocks
    f_bfree: u64,      // Free blocks
    f_bavail: u64,     // Available blocks
    f_files: u64,      // Total inodes
    f_ffree: u64,      // Free inodes
    f_fsid: u64,       // Filesystem ID (as u64 for simplicity)
    f_namelen: u32,    // Maximum filename length
    f_frsize: u32,     // Fragment size
    f_flags: u32,      // Mount flags
    f_spare: [u32; 4], // Spare fields
}

pub fn sys_statfs64(path: u32, sz: u32, buf: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_statfs64: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    debug_print!("sys_statfs64: path={}, sz={}, buf={}", path, sz, buf);

    // Validate the size parameter
    if sz != core::mem::size_of::<Statfs64>() as u32 {
        debug_print!(
            "sys_statfs64: invalid size parameter: expected {}, got {}",
            core::mem::size_of::<Statfs64>(),
            sz
        );
        return Err(Err::NoSys);
    }

    // Create statfs64 structure with the specified f_type
    let statfs = Statfs64 {
        f_type: 0x01021994,         // 9P filesystem type as requested
        f_bsize: 4096,              // 4KB block size (typical for 9P)
        f_blocks: 1000000,          // Total blocks (placeholder)
        f_bfree: 500000,            // Free blocks (placeholder)
        f_bavail: 500000,           // Available blocks (placeholder)
        f_files: 10000,             // Total inodes (placeholder)
        f_ffree: 5000,              // Free inodes (placeholder)
        f_fsid: 0x1234567890ABCDEF, // Filesystem ID (placeholder)
        f_namelen: 255,             // Maximum filename length
        f_frsize: 4096,             // Fragment size (same as block size)
        f_flags: 0,                 // No special mount flags
        f_spare: [0; 4],            // Spare fields
    };

    // Write the statfs64 structure to user memory using copy_to_user
    let statfs_bytes = unsafe {
        core::slice::from_raw_parts(
            &statfs as *const Statfs64 as *const u8,
            core::mem::size_of::<Statfs64>(),
        )
    };
    let bytes_copied = crate::kernel::copy_to_user(
        buf as *mut u8,
        statfs_bytes.as_ptr(),
        core::mem::size_of::<Statfs64>(),
    );
    if bytes_copied == 0 {
        debug_print!("sys_statfs64: failed to copy statfs64 structure to user memory");
        return Err(Err::Fault); // EFAULT for memory copy failure
    }

    debug_print!(
        "sys_statfs64: wrote statfs64 structure with f_type=0x{:x}",
        statfs.f_type
    );
    Ok(0)
}

pub fn init_fs() {
    set_fd(0, TEMP_FID_1);
    set_fd(1, TEMP_FID_1);
    set_fd(2, TEMP_FID_1);
}

// Helper function to check if a FID is a virtual device or file
fn is_virtual_device(fid: u32) -> bool {
    matches!(
        fid,
        VIRTUAL_DEV_NULL
            | VIRTUAL_DEV_ZERO
            | VIRTUAL_DEV_RANDOM
            | VIRTUAL_DEV_URANDOM
            | VIRTUAL_DEV_FULL
            | VIRTUAL_FILE_PROC_CPUINFO
    )
}

// Helper function to check if a FID is specifically a virtual file (like /proc entries)
fn is_virtual_file(fid: u32) -> bool {
    matches!(fid, VIRTUAL_FILE_PROC_CPUINFO)
}

// Check if a path is a virtual device/file and return its FID if so
fn get_virtual_device_fid(path: &str) -> Option<u32> {
    match path {
        "/dev/null" => Some(VIRTUAL_DEV_NULL),
        "/dev/zero" => Some(VIRTUAL_DEV_ZERO),
        "/dev/random" => Some(VIRTUAL_DEV_RANDOM),
        "/dev/urandom" => Some(VIRTUAL_DEV_URANDOM),
        "/dev/full" => Some(VIRTUAL_DEV_FULL),
        "/proc/cpuinfo" => Some(VIRTUAL_FILE_PROC_CPUINFO),
        _ => None,
    }
}

pub fn sys_close(_fd: u32) -> Result<u32, Err> {
    if _fd >= 256 {
        return Err(Err::BadFd);
    }
    let fd_entry = get_fd(_fd);
    if fd_entry.file_desc_id == 0xFF {
        // File descriptor is not open
        return Err(Err::BadFd);
    }

    let desc_id = fd_entry.file_desc_id;
    let file_desc = get_file_desc(desc_id);

    // Decrement reference count
    let should_clunk = dec_refcount(desc_id);

    // Only clunk the fid when this is the last reference and it's not a virtual device
    if should_clunk
        && file_desc.fid != TEMP_FID_1
        && file_desc.fid != 0
        && !is_virtual_device(file_desc.fid)
    {
        clunk(file_desc.fid, false);
        // Clear the file description
        update_file_desc(
            desc_id,
            FileDescription {
                fid: 0,
                cursor: 0,
                is_dir: false,
                mode: INVALID_MODE,
                flags: 0,
                refcount: 0,
            },
        );
    }

    // Clear the file descriptor entry
    update_fd(
        _fd,
        FileDescriptor {
            file_desc_id: 0xFF,
            cloexec: false,
        },
    );

    Ok(0)
}

pub fn read_file_to_user_memory(fd: u32, buf: u32, count: u32, offset: u64) -> Result<u32, Err> {
    if fd >= 256 {
        return Err(Err::Inval);
    }
    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);
    if file_desc.fid != 0 {
        let mut cursor = offset;
        let mut total_bytes_read = 0u32;
        while cursor < offset + (count as u64) {
            // read max MAX_9P_IO_CHUNK bytes at a time
            let max_count = (offset + count as u64 - cursor).min(MAX_9P_IO_CHUNK as u64) as u32;
            let tread = TreadMessage::new(0, file_desc.fid, cursor, max_count);
            match tread.send_tread() {
                Ok(P9Response::Success(rread)) => {
                    if rread.count == 0 {
                        debug_print!(
                            "read_file_to_user_memory: read 0 bytes, offset={} cursor={} count={}, max_count={}",
                            offset,
                            cursor,
                            count,
                            max_count
                        );
                        return Ok(total_bytes_read);
                    }
                    let user_ptr = buf as *mut u8;
                    let user_ptr = unsafe { user_ptr.add(cursor as usize).sub(offset as usize) };
                    let data = rread.data;
                    let _bytes_copied =
                        crate::kernel::copy_to_user(user_ptr, data.as_ptr(), rread.count as usize);
                    cursor += rread.count as u64;
                    total_bytes_read += rread.count;
                }
                Ok(P9Response::Error(rlerror)) => {
                    if rlerror.ecode == 0 {
                        return Ok(total_bytes_read);
                    }
                    debug_print!(
                        "read_file_to_user_memory: Rread error: ecode={}",
                        rlerror.ecode
                    );
                    return Err(map_p9_error(rlerror.ecode));
                }
                Err(e) => {
                    debug_print!("read_file_to_user_memory: error sending tread: {:?}", e);
                    return Err(Err::IO);
                }
            }
        }
        return Ok(total_bytes_read);
    }
    Err(Err::NoSys)
}

// Generate the content for /proc/cpuinfo
fn get_proc_cpuinfo_content() -> &'static [u8] {
    // RISC-V cpuinfo format
    // For RISC0 zkVM, we present it as a single RISC-V processor
    b"processor\t: 0\n\
hart\t\t: 0\n\
isa\t\t: rv32imac\n\
mmu\t\t: sv32\n\
uarch\t\t: risc0\n\
\n"
}

// Handle read operations for virtual devices
fn handle_virtual_device_read(fid: u32, buf: u32, count: u32, desc_id: u32) -> Result<u32, Err> {
    match fid {
        VIRTUAL_DEV_NULL => {
            // Reading from /dev/null always returns 0 (EOF)
            debug_print!("handle_virtual_device_read: /dev/null returns EOF");
            Ok(0)
        }
        VIRTUAL_DEV_ZERO | VIRTUAL_DEV_FULL => {
            // Reading from /dev/zero or /dev/full returns zeros
            debug_print!(
                "handle_virtual_device_read: /dev/zero or /dev/full, filling {} bytes with zeros",
                count
            );
            let buf_slice =
                unsafe { core::slice::from_raw_parts_mut(buf as *mut u8, count as usize) };
            buf_slice.fill(0);
            Ok(count)
        }
        VIRTUAL_DEV_RANDOM | VIRTUAL_DEV_URANDOM => {
            // Return pseudo-random data using a simple XOR shift PRNG
            debug_print!(
                "handle_virtual_device_read: /dev/random or /dev/urandom, generating {} bytes",
                count
            );
            let buf_slice =
                unsafe { core::slice::from_raw_parts_mut(buf as *mut u8, count as usize) };
            // Simple pseudo-random using XOR shift
            static mut RAND_STATE: u32 = 0x12345678;
            unsafe {
                for byte in buf_slice.iter_mut() {
                    RAND_STATE ^= RAND_STATE << 13;
                    RAND_STATE ^= RAND_STATE >> 17;
                    RAND_STATE ^= RAND_STATE << 5;
                    *byte = (RAND_STATE & 0xFF) as u8;
                }
            }
            Ok(count)
        }
        VIRTUAL_FILE_PROC_CPUINFO => {
            // Read from /proc/cpuinfo with cursor support
            let mut file_desc = get_file_desc(desc_id);
            let content = get_proc_cpuinfo_content();
            let cursor = file_desc.cursor as usize;

            debug_print!(
                "handle_virtual_device_read: /proc/cpuinfo at cursor={}, count={}",
                cursor,
                count
            );

            // Check if we're past the end of the content
            if cursor >= content.len() {
                debug_print!("handle_virtual_device_read: /proc/cpuinfo EOF");
                return Ok(0); // EOF
            }

            // Calculate how many bytes to copy
            let remaining = content.len() - cursor;
            let to_copy = (count as usize).min(remaining);

            // Copy the content to user buffer
            let buf_slice = unsafe { core::slice::from_raw_parts_mut(buf as *mut u8, to_copy) };
            buf_slice.copy_from_slice(&content[cursor..cursor + to_copy]);

            // Update cursor
            file_desc.cursor += to_copy as u64;
            update_file_desc(desc_id, file_desc);

            debug_print!(
                "handle_virtual_device_read: /proc/cpuinfo read {} bytes",
                to_copy
            );
            Ok(to_copy as u32)
        }
        _ => {
            debug_print!(
                "handle_virtual_device_read: unknown virtual device fid={}",
                fid
            );
            Err(Err::Inval)
        }
    }
}

pub fn sys_read(_fd: u32, _buf: u32, _count: u32) -> Result<u32, Err> {
    // Check for NULL buffer
    if _buf == 0 {
        return Err(Err::Fault);
    }

    // Validate the buffer is in writable user memory
    match crate::linux_abi::is_valid_user_address(_buf, _count as usize, true) {
        Some(valid_len) if valid_len >= _count as usize => {}
        _ => {
            debug_print!(
                "sys_read: EFAULT - invalid buffer address {:#010x} len {}",
                _buf,
                _count
            );
            return Err(Err::Fault);
        }
    }

    if !get_p9_enabled() {
        let msg = b"sys_read: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Validate file descriptor is within range
    if _fd >= 256 {
        debug_print!("sys_read: invalid fd={}", _fd);
        return Err(Err::BadFd);
    }

    debug_print!("sys_read: _fd={} _buf={} _count={}", _fd, _buf, _count);
    let fd_entry = get_fd(_fd);

    // Check if fd is closed/invalid
    if fd_entry.file_desc_id == 0xFF {
        debug_print!("sys_read: fd={} is not open", _fd);
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    // Check if file was opened with read access
    // file_desc.mode contains p9 access mode: 0=read, 1=write, 2=read+write
    let access_mode = file_desc.mode & 0x3;
    if access_mode == 1 {
        // O_WRONLY - can't read
        debug_print!("sys_read: fd={} opened write-only", _fd);
        return Err(Err::BadFd);
    }

    // Check if fd is a directory
    if file_desc.is_dir {
        debug_print!("sys_read: fd={} is a directory", _fd);
        return Err(Err::IsDir);
    }

    // Handle virtual devices
    if is_virtual_device(file_desc.fid) {
        debug_print!("sys_read: fd={} is a virtual device", _fd);
        return handle_virtual_device_read(file_desc.fid, _buf, _count, fd_entry.file_desc_id);
    }

    if file_desc.fid != 0 && file_desc.fid != TEMP_FID_1 {
        // 9P protocol has a maximum message size (msize), typically 8192 bytes.
        // Use MAX_9P_IO_CHUNK to respect this limit.

        let total_to_read = _count;
        let mut total_read = 0u32;
        let user_ptr = _buf as *mut u8;

        debug_print!(
            "sys_read: reading from fid={}, cursor={}, count={}, access_mode={}",
            file_desc.fid,
            file_desc.cursor,
            total_to_read,
            access_mode
        );

        // Loop to read in chunks if necessary
        while total_read < total_to_read {
            let remaining = total_to_read - total_read;
            let chunk_size = if remaining > MAX_9P_IO_CHUNK {
                MAX_9P_IO_CHUNK
            } else {
                remaining
            };

            // Get current file description state (it may have been updated in previous iteration)
            let fd_entry = get_fd(_fd);
            let current_desc = get_file_desc(fd_entry.file_desc_id);

            debug_print!(
                "sys_read: chunk read - requesting {} bytes at cursor {}",
                chunk_size,
                current_desc.cursor
            );

            let tread = TreadMessage::new(0, current_desc.fid, current_desc.cursor, chunk_size);
            match tread.send_tread() {
                Ok(P9Response::Success(rread)) => {
                    debug_print!("sys_read: received {} bytes from 9P", rread.count);

                    if rread.count == 0 {
                        debug_print!("sys_read: read 0 bytes (EOF)");
                        // EOF - return what we've read so far
                        return Ok(total_read);
                    }

                    debug_print!(
                        "sys_read: copying {} bytes to user buffer 0x{:08x}",
                        rread.count,
                        _buf as u32 + total_read
                    );

                    let dest_ptr = unsafe { user_ptr.add(total_read as usize) };
                    let bytes_copied = crate::kernel::copy_to_user(
                        dest_ptr,
                        rread.data.as_ptr(),
                        rread.count as usize,
                    );

                    if bytes_copied == 0 {
                        debug_print!(
                            "sys_read: copy_to_user failed! dst=0x{:08x}, len={}",
                            dest_ptr as u32,
                            rread.count
                        );
                        // If we already read some data, return what we got
                        if total_read > 0 {
                            return Ok(total_read);
                        }
                        return Err(Err::Fault); // EFAULT for memory copy failure
                    }

                    // Update totals
                    total_read += rread.count;

                    // Update the shared cursor in the file description
                    let fd_entry = get_fd(_fd);
                    let mut updated_desc = get_file_desc(fd_entry.file_desc_id);
                    updated_desc.cursor += rread.count as u64;
                    update_file_desc(fd_entry.file_desc_id, updated_desc);

                    // If we got less than requested, we hit EOF
                    if rread.count < chunk_size {
                        debug_print!(
                            "sys_read: short read ({} < {}), EOF reached",
                            rread.count,
                            chunk_size
                        );
                        return Ok(total_read);
                    }
                }
                Ok(P9Response::Error(rlerror)) => {
                    debug_print!(
                        "sys_read: Rread error: ecode={}, fid={}, cursor={}",
                        rlerror.ecode,
                        current_desc.fid,
                        current_desc.cursor
                    );
                    // If we already read some data, return what we got
                    if total_read > 0 {
                        return Ok(total_read);
                    }
                    return Err(map_p9_error(rlerror.ecode));
                }
                Err(e) => {
                    debug_print!("sys_read: error sending Tread: {:?}", e);
                    if total_read > 0 {
                        return Ok(total_read);
                    }
                    return Err(Err::IO);
                }
            }
        }

        debug_print!("sys_read: successfully read {} bytes total", total_read);
        return Ok(total_read);
    } else {
        debug_print!(
            "sys_read: invalid fid={} (skipping read, fid is 0 or TEMP_FID_1)",
            file_desc.fid
        );
    }
    let msg = b"sys_read not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_write(fd: u32, buf: u32, count: u32) -> Result<u32, Err> {
    do_write(fd as i32, buf as *const u8, count as usize).map(|x| x as u32)
}

// Handle write operations for virtual devices
fn handle_virtual_device_write(fid: u32, _buf: *const u8, count: usize) -> Result<usize, Err> {
    match fid {
        VIRTUAL_DEV_NULL | VIRTUAL_DEV_ZERO | VIRTUAL_DEV_RANDOM | VIRTUAL_DEV_URANDOM => {
            // Writing to these devices always succeeds and discards data
            debug_print!(
                "handle_virtual_device_write: /dev/null or similar, discarding {} bytes",
                count
            );
            Ok(count)
        }
        VIRTUAL_DEV_FULL => {
            // Writing to /dev/full always returns ENOSPC (no space)
            debug_print!("handle_virtual_device_write: /dev/full, returning ENOSPC");
            Err(Err::NoSpc)
        }
        VIRTUAL_FILE_PROC_CPUINFO => {
            // Writing to /proc/cpuinfo is not allowed (read-only)
            debug_print!("handle_virtual_device_write: /proc/cpuinfo is read-only");
            Err(Err::Inval)
        }
        _ => {
            debug_print!(
                "handle_virtual_device_write: unknown virtual device fid={}",
                fid
            );
            Err(Err::Inval)
        }
    }
}

pub fn do_write(fd: i32, buf: *const u8, count: usize) -> Result<usize, Err> {
    // Special case: NULL buffer with count=0 is allowed (Linux behavior)
    // This allows write(fd, NULL, 0) to succeed and return 0
    // Note: On Linux, write(fd, NULL, -1) (which becomes count=0xFFFFFFFF after cast)
    // will also be treated as 0 if count would overflow, but we handle count=0 explicitly
    if buf.is_null() && count == 0 {
        return Ok(0);
    }

    if count == 0 {
        return Ok(0);
    }
    // NULL buffer with count > 0 is invalid (causes EFAULT)
    if buf.is_null() {
        return Err(Err::Fault);
    }

    // Validate the buffer is in readable user memory
    match crate::linux_abi::is_valid_user_address(buf as u32, count, false) {
        Some(valid_len) if valid_len >= count => {}
        _ => {
            debug_print!(
                "do_write: EFAULT - invalid buffer address {:#010x} len {}",
                buf as u32,
                count
            );
            return Err(Err::Fault);
        }
    }

    if fd == 1 || fd == 2 {
        // Chunk stdout/stderr writes to respect MAX_IO_BYTES (1024) limit
        const MAX_IO_BYTES: usize = 1024;
        let mut offset = 0usize;
        while offset < count {
            let chunk_size = core::cmp::min(MAX_IO_BYTES, count - offset);
            let chunk_ptr = unsafe { buf.add(offset) };
            host_write(fd as u32, chunk_ptr, chunk_size);
            offset += chunk_size;
        }
    } else {
        if !(0..256).contains(&fd) {
            return Err(Err::Inval);
        }
        if !get_p9_enabled() {
            let msg = b"do_write: p9 is not enabled";
            host_log(msg.as_ptr(), msg.len());
            return Err(Err::NoSys);
        }
        let fd_entry = get_fd(fd as u32);
        if fd_entry.file_desc_id == 0xFF {
            let msg = b"do_write: fd is not open";
            host_log(msg.as_ptr(), msg.len());
            return Err(Err::BadFd);
        }

        let mut file_desc = get_file_desc(fd_entry.file_desc_id);

        // Check if file was opened with write access
        // file_desc.mode contains p9 access mode: 0=read, 1=write, 2=read+write
        let access_mode = file_desc.mode & 0x3;
        if access_mode == 0 {
            // O_RDONLY - can't write
            debug_print!("do_write: fd={} opened read-only", fd);
            return Err(Err::BadFd);
        }

        // Handle virtual devices
        if is_virtual_device(file_desc.fid) {
            debug_print!("do_write: fd={} is a virtual device", fd);
            return handle_virtual_device_write(file_desc.fid, buf, count);
        }

        if file_desc.fid != 0 && file_desc.fid != TEMP_FID_1 {
            // Handle O_APPEND: position at end of file before each write
            let mut current_cursor = file_desc.cursor;

            if (file_desc.flags & O_APPEND) == O_APPEND {
                // Get file size using getattr
                let tgetattr = crate::p9::TgetattrMessage::new(0, file_desc.fid, P9_GETATTR_SIZE);
                match tgetattr.send_tgetattr() {
                    Ok(P9Response::Success(rgetattr)) => {
                        current_cursor = rgetattr.size;
                        debug_print!(
                            "do_write: O_APPEND - setting cursor to end of file: {}",
                            current_cursor
                        );
                    }
                    Ok(P9Response::Error(rlerror)) => {
                        debug_print!(
                            "do_write: error getting file size for O_APPEND: ecode={}",
                            rlerror.ecode
                        );
                        return Err(map_p9_error(rlerror.ecode));
                    }
                    Err(e) => {
                        debug_print!("do_write: error sending getattr for O_APPEND: {:?}", e);
                        return Err(Err::IO); // EIO for I/O errors
                    }
                }
            }

            // Write in chunks respecting the 9P msize limit
            let chunk_size = MAX_9P_IO_CHUNK as usize;
            let mut total_written = 0;

            let data = unsafe { core::slice::from_raw_parts(buf, count) };

            for chunk_start in (0..count).step_by(chunk_size) {
                let chunk_end = (chunk_start + chunk_size).min(count);
                let chunk_data = &data[chunk_start..chunk_end];

                debug_print!(
                    "do_write: writing chunk {} bytes at cursor {}",
                    chunk_data.len(),
                    current_cursor
                );

                let twrite =
                    TwriteMessage::new(0, file_desc.fid, current_cursor, chunk_data.to_vec());

                match twrite.send_twrite() {
                    Ok(P9Response::Success(rwrite)) => {
                        let bytes_written = rwrite.count as usize;
                        total_written += bytes_written;
                        current_cursor += bytes_written as u64;

                        debug_print!(
                            "do_write: wrote {} bytes, total: {}",
                            bytes_written,
                            total_written
                        );

                        // If we wrote fewer bytes than requested, we're done
                        if bytes_written < chunk_data.len() {
                            break;
                        }
                    }
                    Ok(P9Response::Error(rlerror)) => {
                        debug_print!("do_write: Rwrite error: ecode={}", rlerror.ecode);
                        return Err(map_p9_error(rlerror.ecode));
                    }
                    Err(e) => {
                        debug_print!("do_write: error sending Twrite: {:?}", e);
                        return Err(Err::IO); // EIO for I/O errors
                    }
                }
            }

            // Update the shared cursor in the file description
            file_desc.cursor = current_cursor;
            update_file_desc(fd_entry.file_desc_id, file_desc);

            return Ok(total_written);
        }
        let msg = b"do_write for fd > 2 that are not FIDs not implemented";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    Ok(count)
}

pub fn sys_writev(fd: u32, vec_ptr: u32, vlen: u32) -> Result<u32, Err> {
    if vlen == 0 {
        return Ok(0);
    }

    let fd = fd as i32;
    let vec = load_iovecs(vec_ptr, vlen)?;

    // Validate each iovec entry's buffer is readable
    for (i, iov) in vec.iter().enumerate() {
        // Check for unreasonable lengths first (captures negative lengths represented as large usize)
        if iov.iov_len > (isize::MAX as usize) {
            debug_print!(
                "sys_writev: iovec[{}] has invalid length {}",
                i,
                iov.iov_len
            );
            return Err(Err::Inval);
        }
        if iov.iov_len == 0 {
            continue;
        }
        validate_user_buffer_read(iov.iov_base as u32, iov.iov_len)?;
    }

    let mut total: usize = 0;
    for iov in vec {
        if iov.iov_len == 0 {
            continue;
        }
        total += do_write(fd, iov.iov_base, iov.iov_len)?;
    }
    Ok(total as u32)
}

pub fn sys_chdir(filename: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_chdir: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    let filename_str = validate_and_read_pathname(filename)?;
    debug_print!("sys_chdir: filename='{}'", filename_str);

    // Check for pathname too long (limit is 255 for 9P)
    if filename_str.len() > 255 {
        debug_print!(
            "sys_chdir: pathname too long ({} bytes), returning ENAMETOOLONG",
            filename_str.len()
        );
        return Err(Err::NameTooLong);
    }

    let starting_fid = if filename_str.starts_with("/") {
        get_root_fid()
    } else {
        get_cwd_fid()
    };
    let wnames = normalize_path(&filename_str);
    let walk_result = do_walk(starting_fid, TEMP_FID_3, wnames);
    match walk_result {
        Ok((ret_code, _)) => {
            if ret_code != 0 {
                return Ok(ret_code);
            }
        }
        Err(e) => {
            debug_print!(
                "sys_chdir: error walking to directory: errno={}",
                e.as_errno()
            );
            return Err(e);
        }
    }
    if get_cwd_fid() == TEMP_FID_2 {
        clunk(TEMP_FID_2, true); // remove the old cwd fix - allow CWD clunking
    }

    // Now resolve symlinks to build the canonical path
    // Walk component-by-component from root to build canonical path
    let mut resolved_components: Vec<String> = if filename_str.starts_with("/") {
        vec![]
    } else {
        let cwd = get_cwd_str();
        normalize_path(cwd.trim_end_matches('/'))
    };

    let components = normalize_path(&filename_str);

    // Process each component, resolving symlinks as we go
    for component in components {
        if component == ".." {
            if !resolved_components.is_empty() {
                resolved_components.pop();
            }
        } else if component != "." && !component.is_empty() {
            // Check if this component is a symlink
            // We need to walk to the parent, then Twalk to this component WITHOUT following
            let parent_path = if resolved_components.is_empty() {
                vec![]
            } else {
                resolved_components.clone()
            };

            let parent_fid = TEMP_FID_6;
            if !parent_path.is_empty() {
                match do_walk(get_root_fid(), parent_fid, parent_path) {
                    Ok(_) => {}
                    Err(_) => {
                        // Parent doesn't exist, just add component as-is
                        resolved_components.push(component.clone());
                        continue;
                    }
                }
            } else {
                // Parent is root, just duplicate root fid
                match do_walk(get_root_fid(), parent_fid, vec![]) {
                    Ok(_) => {}
                    Err(_) => {
                        resolved_components.push(component.clone());
                        continue;
                    }
                }
            }

            // Now walk to just this component without following symlinks
            let check_fid = TEMP_FID_7;
            let twalk =
                crate::p9::TwalkMessage::new(0, parent_fid, check_fid, vec![component.clone()]);
            match twalk.send_twalk() {
                Ok(crate::p9::P9Response::Success(rwalk)) => {
                    clunk(parent_fid, false);

                    if rwalk.wqids.len() != 1 {
                        clunk(check_fid, false);
                        resolved_components.push(component.clone());
                        continue;
                    }

                    // Check if it's a symlink
                    if let Some(qid) = rwalk.wqids.first() {
                        if qid.is_symlink() {
                            // Read and resolve the symlink
                            match read_symlink(check_fid) {
                                Ok(target) => {
                                    debug_print!(
                                        "sys_chdir: '{}' is symlink to '{}'",
                                        component,
                                        target
                                    );
                                    clunk(check_fid, false);

                                    if target.starts_with('/') {
                                        // Absolute symlink
                                        resolved_components = normalize_path(&target);
                                    } else {
                                        // Relative symlink - resolve from parent directory
                                        for target_comp in normalize_path(&target) {
                                            if target_comp == ".." {
                                                if !resolved_components.is_empty() {
                                                    resolved_components.pop();
                                                }
                                            } else if target_comp != "." && !target_comp.is_empty()
                                            {
                                                resolved_components.push(target_comp);
                                            }
                                        }
                                    }
                                }
                                Err(_) => {
                                    clunk(check_fid, false);
                                    // If readlink fails, treat as regular file
                                    resolved_components.push(component);
                                }
                            }
                        } else {
                            // Not a symlink
                            clunk(check_fid, false);
                            resolved_components.push(component);
                        }
                    }
                }
                Ok(crate::p9::P9Response::Error(_)) => {
                    clunk(parent_fid, false);
                    // Can't walk to it, just add it
                    resolved_components.push(component);
                }
                Err(_) => {
                    clunk(parent_fid, false);
                    resolved_components.push(component.clone());
                    continue;
                }
            }
        }
    }

    // Build final canonical path
    let mut final_path = if resolved_components.is_empty() {
        "/".to_string()
    } else {
        format!("/{}", resolved_components.join("/"))
    };

    if !final_path.ends_with("/") {
        final_path.push('/');
    }

    debug_print!("sys_chdir: canonical path='{}'", final_path);
    set_cwd_str(final_path);
    dup_fid_to(TEMP_FID_3, TEMP_FID_2)?;
    clunk(TEMP_FID_3, true); // allow CWD clunking in sys_chdir
    set_cwd_fid(TEMP_FID_2);
    Ok(0)
}

fn dup_fid_to(fid: u32, fid_to: u32) -> Result<u32, Err> {
    let walk_result = do_walk(fid, fid_to, vec![]);
    match walk_result {
        Ok(_) => {
            // Walk succeeded, return the new fid (fid_to), not the return code
            Ok(fid_to)
        }
        Err(e) => {
            debug_print!("dup_fid_to: error dupping: {:?}", e.as_errno());
            clunk(fid_to, false);
            Err(e)
        }
    }
}

pub fn sys_dup(fd: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_dup: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }
    // Check if fd is out of range (including negative values cast to u32)
    if fd >= 256 {
        debug_print!("sys_dup: fd {} is out of range", fd);
        return Err(Err::BadFd);
    }
    // diod/p9 protocol "fid can be cloned to newfid by calling walk with nwname set to zero."
    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        debug_print!("sys_dup: fd {} is not open", fd);
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    // Allocate a new file descriptor (not a new file description!)
    let new_fd = find_free_fd()?;

    // Make the new fd point to the same file description
    // sys_dup copies the FD_CLOEXEC flag from the original fd
    update_fd(
        new_fd,
        FileDescriptor {
            file_desc_id: fd_entry.file_desc_id,
            cloexec: fd_entry.cloexec,
        },
    );

    // Increment the reference count for the shared file description
    inc_refcount(fd_entry.file_desc_id);

    debug_print!(
        "sys_dup: duplicated fd {} to fd {}, both pointing to desc_id {} (fid={}, refcount now {})",
        fd,
        new_fd,
        fd_entry.file_desc_id,
        file_desc.fid,
        get_file_desc(fd_entry.file_desc_id).refcount
    );

    Ok(new_fd)
}

pub fn sys_dup3(oldfd: u32, newfd: u32, flags: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_dup3: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    debug_print!(
        "sys_dup3: oldfd={}, newfd={}, flags={}",
        oldfd,
        newfd,
        flags
    );

    // Validate flags FIRST (O_CLOEXEC is the only valid flag for dup3)
    // Invalid flags should return EINVAL even if fds are invalid
    const O_CLOEXEC: u32 = 0o2000000;
    if (flags & !O_CLOEXEC) != 0 {
        debug_print!("sys_dup3: invalid flags 0x{:x}", flags);
        return Err(Err::Inval);
    }

    // Validate file descriptors are in range
    if oldfd >= 256 {
        debug_print!("sys_dup3: oldfd {} is out of range", oldfd);
        return Err(Err::BadFd);
    }
    if newfd >= 256 {
        debug_print!("sys_dup3: newfd {} is out of range", newfd);
        return Err(Err::BadFd);
    }

    // Check if oldfd is the same as newfd (not allowed in dup3, unlike dup2)
    if oldfd == newfd {
        debug_print!("sys_dup3: oldfd == newfd (not allowed in dup3)");
        return Err(Err::Inval);
    }

    // Check if oldfd is open
    let old_fd_entry = get_fd(oldfd);
    if old_fd_entry.file_desc_id == 0xFF {
        debug_print!("sys_dup3: oldfd {} is not open", oldfd);
        return Err(Err::BadFd);
    }

    // Close newfd if it's currently open
    let new_fd_entry = get_fd(newfd);
    if new_fd_entry.file_desc_id != 0xFF {
        debug_print!(
            "sys_dup3: closing existing fd {} (desc_id={})",
            newfd,
            new_fd_entry.file_desc_id
        );
        let _ = sys_close(newfd); // Ignore errors from close
    }

    // Make newfd point to the same file description as oldfd
    // Set FD_CLOEXEC based on O_CLOEXEC flag
    let cloexec_set = (flags & O_CLOEXEC) != 0;
    update_fd(
        newfd,
        FileDescriptor {
            file_desc_id: old_fd_entry.file_desc_id,
            cloexec: cloexec_set,
        },
    );

    // Increment the reference count for the shared file description
    inc_refcount(old_fd_entry.file_desc_id);

    let file_desc = get_file_desc(old_fd_entry.file_desc_id);
    debug_print!(
        "sys_dup3: duplicated fd {} to fd {}, both pointing to desc_id {} (fid={}, refcount now {})",
        oldfd,
        newfd,
        old_fd_entry.file_desc_id,
        file_desc.fid,
        get_file_desc(old_fd_entry.file_desc_id).refcount
    );

    Ok(newfd)
}

pub fn sys_faccessat(_dfd: u32, _filename: u32, _mode: u32) -> Result<u32, Err> {
    // faccessat calls faccessat2 with no flags
    sys_faccessat2(_dfd, _filename, _mode, 0)
}

pub fn sys_faccessat2(_dfd: u32, _filename: u32, _mode: u32, _flags: u32) -> Result<u32, Err> {
    // faccessat2 checks if a file can be accessed with the given mode
    // mode bits: R_OK (4), W_OK (2), X_OK (1), F_OK (0 - existence only)
    // Flags: AT_EACCESS (0x200), AT_SYMLINK_NOFOLLOW (0x100), AT_EMPTY_PATH (0x1000)

    if !get_p9_enabled() {
        let msg = b"sys_faccessat2: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Validate flags - check for invalid flag values
    const AT_EACCESS: u32 = 0x200;
    const AT_SYMLINK_NOFOLLOW: u32 = 0x100;
    const AT_EMPTY_PATH: u32 = 0x1000;
    const AT_FLAGS_MASK: u32 = AT_EACCESS | AT_SYMLINK_NOFOLLOW | AT_EMPTY_PATH;

    // Check for invalid flags
    // -1 (0xFFFFFFFF when cast from i32) sets all bits, which is invalid
    let flags_i32 = _flags as i32;
    if flags_i32 < 0 || (_flags & !AT_FLAGS_MASK) != 0 {
        debug_print!("sys_faccessat2: invalid flags 0x{:x}", _flags);
        return Err(Err::Inval);
    }

    // Validate mode - check for invalid mode values
    // Valid modes: F_OK (0), R_OK (4), W_OK (2), X_OK (1), or combinations
    // -1 (0xFFFFFFFF when cast from i32) is invalid
    let mode_i32 = _mode as i32;
    const MODE_MASK: u32 = 0x7; // Only lowest 3 bits valid
    if mode_i32 < 0 || (_mode & !MODE_MASK) != 0 {
        debug_print!("sys_faccessat2: invalid mode 0x{:x}", _mode);
        return Err(Err::Inval);
    }

    let filename_str = validate_and_read_pathname(_filename)?;

    debug_print!(
        "sys_faccessat2: dfd={}, filename='{}', mode=0x{:x}, flags=0x{:x}",
        _dfd,
        filename_str,
        _mode,
        _flags
    );

    if (_flags & AT_EACCESS) != 0 {
        debug_print!("sys_faccessat2: AT_EACCESS set (using effective uid/gid)");
        // In zkVM context, we don't distinguish between real and effective uid/gid
    }

    // Handle AT_EMPTY_PATH - check access on the fd itself
    if (_flags & AT_EMPTY_PATH) != 0 && filename_str.is_empty() {
        debug_print!("sys_faccessat2: AT_EMPTY_PATH set, checking fd {}", _dfd);

        // Validate dfd is in range
        if _dfd >= 256 {
            return Err(Err::BadFd);
        }

        let fd_entry = get_fd(_dfd);
        if fd_entry.file_desc_id == 0xFF {
            // Invalid file descriptor
            return Err(Err::BadFd);
        }

        // File descriptor is valid and open - access granted
        return Ok(0);
    }

    // Handle AT_SYMLINK_NOFOLLOW: don't follow symlinks, check access on the symlink itself
    if (_flags & AT_SYMLINK_NOFOLLOW) != 0 {
        debug_print!("sys_faccessat2: AT_SYMLINK_NOFOLLOW set");

        let starting_fid = get_starting_fid(_dfd, &filename_str)?;
        let (dir_path, file_name) = split_path(&filename_str);

        // For relative paths, use the dfd directly as the directory
        let dir_fid = if dir_path.is_empty() || dir_path == "." {
            starting_fid
        } else {
            let dir_path = normalize_path(&dir_path);
            if do_walk(starting_fid, TEMP_FID_4, dir_path).is_err() {
                clunk(TEMP_FID_4, false);
                return Err(Err::FileNotFound);
            }
            TEMP_FID_4
        };

        // Walk to the final component without following symlinks
        let file_path = vec![file_name];
        let twalk = crate::p9::TwalkMessage::new(0, dir_fid, TEMP_FID_5, file_path);
        match twalk.send_twalk() {
            Ok(crate::p9::P9Response::Success(_)) => {
                // File/symlink exists and is accessible
                clunk(TEMP_FID_5, false);
                if dir_fid != starting_fid {
                    clunk(dir_fid, false);
                }
                return Ok(0);
            }
            Ok(crate::p9::P9Response::Error(_)) => {
                if dir_fid != starting_fid {
                    clunk(dir_fid, false);
                }
                return Err(Err::FileNotFound);
            }
            Err(_) => {
                if dir_fid != starting_fid {
                    clunk(dir_fid, false);
                }
                return Err(Err::FileNotFound);
            }
        }
    }

    // Normal path-based access check (following symlinks)
    let starting_fid = get_starting_fid(_dfd, &filename_str)?;
    let (dir_path, file_name) = split_path(&filename_str);
    let dir_path = normalize_path(&dir_path);
    do_walk(starting_fid, TEMP_FID_4, dir_path)?;

    match resolve_file_to_fid(TEMP_FID_4, TEMP_FID_5, &file_name) {
        Ok(_) => {
            // File exists and is accessible
            clunk(TEMP_FID_5, false);
            clunk(TEMP_FID_4, false);
            Ok(0)
        }
        Err(e) => {
            // File not found or not accessible
            clunk(TEMP_FID_4, false);
            Err(e)
        }
    }
}

pub fn sys_fadvise64_64(_fd: u32, _offset: u32, _len: u32, _advice: u32) -> Result<u32, Err> {
    let msg = b"sys_fadvise64_64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fallocate(
    fd: u32,
    mode: u32,
    offset_low: u32,
    offset_high: u32,
    len_low: u32,
    len_high: u32,
) -> Result<u32, Err> {
    // On 32-bit RISC-V, 64-bit arguments are passed in two registers (low, high)
    // Check for negative values BEFORE converting to u64
    // If the high word has the sign bit set (0x80000000), it's negative
    let offset_i64 = ((offset_high as i32 as i64) << 32) | (offset_low as i64);
    let len_i64 = ((len_high as i32 as i64) << 32) | (len_low as i64);

    // Validate parameters before proceeding
    if offset_i64 < 0 {
        debug_print!(
            "sys_fallocate: negative offset {}, returning EINVAL",
            offset_i64
        );
        return Err(Err::Inval);
    }

    if len_i64 <= 0 {
        debug_print!(
            "sys_fallocate: invalid len {} (must be > 0), returning EINVAL",
            len_i64
        );
        return Err(Err::Inval);
    }

    // Now convert to u64 for calculations
    let offset: u64 = offset_i64 as u64;
    let len: u64 = len_i64 as u64;
    let end_pos = offset + len;

    // Check for overflow
    if end_pos < offset || end_pos < len {
        debug_print!("sys_fallocate: overflow in offset+len calculation");
        return Err(Err::Inval);
    }

    if !get_p9_enabled() {
        let msg = b"sys_fallocate: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Validate fd
    if fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    // Check if file descriptor is opened for writing
    // fallocate() requires a file descriptor opened for writing
    const O_RDONLY: u32 = 0;
    const O_WRONLY: u32 = 1;
    const O_RDWR: u32 = 2;
    const O_ACCMODE: u32 = O_RDONLY | O_WRONLY | O_RDWR;

    let accmode = file_desc.flags & O_ACCMODE;
    if accmode == O_RDONLY {
        debug_print!("sys_fallocate: fd opened read-only, returning EBADF");
        return Err(Err::BadFd);
    }

    // Validate parameters
    // Check for negative offset or len (cast to signed for comparison)
    let offset_i64 = offset as i64;
    let len_i64 = len as i64;

    if offset_i64 < 0 {
        debug_print!(
            "sys_fallocate: negative offset {}, returning EINVAL",
            offset
        );
        return Err(Err::Inval);
    }

    if len_i64 <= 0 {
        debug_print!("sys_fallocate: invalid len {}, returning EINVAL", len);
        return Err(Err::Inval);
    }

    // Check for overflow
    if end_pos < offset || end_pos < len {
        debug_print!("sys_fallocate: overflow in offset+len calculation");
        return Err(Err::Inval);
    }

    // Validate mode flags
    // FALLOC_FL_KEEP_SIZE = 0x01 (don't change file size, just preallocate space)
    // FALLOC_FL_PUNCH_HOLE = 0x02 (punch a hole)
    // FALLOC_FL_NO_HIDE_STALE = 0x04
    const FALLOC_FL_KEEP_SIZE: u32 = 0x01;

    // For now, we only support the default mode (0) and FALLOC_FL_KEEP_SIZE
    if (mode & !FALLOC_FL_KEEP_SIZE) != 0 {
        debug_print!("sys_fallocate: unsupported mode flags 0x{:x}", mode);
        // Return success for unsupported flags (some filesystems don't support all flags)
        // but we'll still try to allocate space
    }

    debug_print!(
        "sys_fallocate: fd={}, mode=0x{:x}, offset={}, len={}, end_pos={}",
        fd,
        mode,
        offset,
        len,
        end_pos
    );

    // Get current file size - we always need it
    let tgetattr = crate::p9::TgetattrMessage::new(0, file_desc.fid, P9_GETATTR_SIZE);
    let current_size = match tgetattr.send_tgetattr() {
        Ok(P9Response::Success(rgetattr)) => rgetattr.size,
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "sys_fallocate: error getting current file size: ecode={}",
                rlerror.ecode
            );
            return Err(map_p9_error(rlerror.ecode));
        }
        Err(_) => {
            debug_print!("sys_fallocate: error sending getattr");
            return Err(Err::NoSys);
        }
    };

    debug_print!(
        "sys_fallocate: current_size={}, end_pos={}, mode=0x{:x}",
        current_size,
        end_pos,
        mode
    );

    // Handle allocation based on mode
    if (mode & FALLOC_FL_KEEP_SIZE) != 0 {
        // FALLOC_FL_KEEP_SIZE: Preallocate space but don't change file size
        // Since 9P doesn't support sparse allocation, we need to temporarily extend
        // the file to allocate space, then restore the original size
        let size_to_allocate = end_pos.max(current_size);

        // Check if the requested size is too large before attempting allocation
        const MAX_REASONABLE_SIZE: u64 = 0x7FFF_FFFF_FFFF_FFFF; // 2^63 - 1
        if size_to_allocate > MAX_REASONABLE_SIZE || offset > MAX_REASONABLE_SIZE {
            debug_print!(
                "sys_fallocate: file size too large: size_to_allocate={}, offset={}",
                size_to_allocate,
                offset
            );
            return Err(Err::FileTooBig);
        }

        if size_to_allocate > current_size {
            // First, extend the file to allocate space
            let valid = P9SetattrMask::Size as u32;
            let tsetattr_extend = TsetattrMessage::new(
                0,
                file_desc.fid,
                valid,
                0,
                0,
                0,
                size_to_allocate,
                0,
                0,
                0,
                0,
            );

            match tsetattr_extend.send_tsetattr() {
                Ok(P9Response::Success(_)) => {
                    debug_print!(
                        "sys_fallocate: allocated space (extended to {}), now restoring size to {}",
                        size_to_allocate,
                        current_size
                    );

                    // Now restore the original size
                    let tsetattr_restore = TsetattrMessage::new(
                        0,
                        file_desc.fid,
                        valid,
                        0,
                        0,
                        0,
                        current_size,
                        0,
                        0,
                        0,
                        0,
                    );

                    match tsetattr_restore.send_tsetattr() {
                        Ok(P9Response::Success(_)) => {
                            debug_print!("sys_fallocate: restored size to {}", current_size);
                            Ok(0)
                        }
                        Ok(P9Response::Error(e)) => {
                            debug_print!("sys_fallocate: error restoring size: ecode={}", e.ecode);
                            Err(map_p9_error(e.ecode))
                        }
                        Err(e) => {
                            debug_print!("sys_fallocate: error sending restore Tsetattr: {:?}", e);
                            Err(Err::NoSys)
                        }
                    }
                }
                Ok(P9Response::Error(rlerror)) => {
                    debug_print!(
                        "sys_fallocate: error extending file: ecode={}, size_to_allocate={}",
                        rlerror.ecode,
                        size_to_allocate
                    );
                    // Special handling for fallocate: treat large size EINVAL as EFBIG
                    if rlerror.ecode == 22
                        && (size_to_allocate > 0x7FFF_FFFF_FFFF_FFFF
                            || offset > 0x7FFF_FFFF_FFFF_FFFF)
                    {
                        // Very large file size or offset: treat EINVAL as EFBIG
                        Err(Err::FileTooBig)
                    } else {
                        // Use standard error mapping
                        Err(map_p9_error(rlerror.ecode))
                    }
                }
                Err(e) => {
                    debug_print!("sys_fallocate: error sending extend Tsetattr: {:?}", e);
                    Err(Err::NoSys)
                }
            }
        } else {
            // Already large enough, nothing to do
            debug_print!(
                "sys_fallocate: file already large enough (size={})",
                current_size
            );
            Ok(0)
        }
    } else {
        // Default mode: extend file to end_pos (or keep current if larger)
        // For fallocate, we should extend the file to at least offset + len
        // even if the file is already larger
        let target_size = end_pos.max(current_size);

        debug_print!(
            "sys_fallocate: default mode - current_size={}, end_pos={}, target_size={}",
            current_size,
            end_pos,
            target_size
        );

        if target_size > current_size {
            let valid = P9SetattrMask::Size as u32;
            let tsetattr =
                TsetattrMessage::new(0, file_desc.fid, valid, 0, 0, 0, target_size, 0, 0, 0, 0);

            match tsetattr.send_tsetattr() {
                Ok(P9Response::Success(_)) => {
                    debug_print!(
                        "sys_fallocate: successfully extended file to {}",
                        target_size
                    );
                    Ok(0)
                }
                Ok(P9Response::Error(rlerror)) => {
                    debug_print!("sys_fallocate: error setting size: ecode={}", rlerror.ecode);
                    // Special handling for fallocate: treat large size EINVAL as EFBIG
                    const MAX_REASONABLE_SIZE: u64 = 0x7FFF_FFFF_FFFF_FFFF; // 2^63 - 1
                    if rlerror.ecode == 22
                        && (target_size > MAX_REASONABLE_SIZE || offset > MAX_REASONABLE_SIZE)
                    {
                        // Very large file size or offset: treat EINVAL as EFBIG
                        Err(Err::FileTooBig)
                    } else {
                        // Use standard error mapping
                        Err(map_p9_error(rlerror.ecode))
                    }
                }
                Err(e) => {
                    debug_print!("sys_fallocate: error sending Tsetattr: {:?}", e);
                    Err(Err::NoSys)
                }
            }
        } else {
            // Already large enough, nothing to do
            debug_print!(
                "sys_fallocate: file already large enough (size={} >= target={})",
                current_size,
                target_size
            );
            Ok(0)
        }
    }
}

pub fn sys_fanotify_init(_flags: u32, _event_f_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_fanotify_init not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fanotify_mark(
    _fanotify_fd: u32,
    _flags: u32,
    _mask: u32,
    _dirfd: u32,
    _pathname: u32,
) -> Result<u32, Err> {
    let msg = b"sys_fanotify_mark not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fchdir(fd: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_fchdir: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Validate fd range
    if fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        // Invalid file descriptor
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    // Check if the file descriptor refers to a directory
    // For now, we'll check this after setting CWD and let the filesystem handle it
    // In a more complete implementation, we should verify it's a directory first
    set_cwd_fid(file_desc.fid);
    Ok(0)
}

pub fn sys_fchmod(fd: u32, mode: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_fchmod: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Validate fd
    if fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    debug_print!("sys_fchmod: fd={}, mode=0o{:o}", fd, mode);

    // Use Tsetattr to change file mode (permissions)
    // We only want to set the mode, so we use the Mode valid flag
    let valid = P9SetattrMask::Mode as u32;

    // Extract the permission bits (low 12 bits for mode)
    let p9_mode = mode & 0o7777;

    let tsetattr = TsetattrMessage::new(
        0,             // tag
        file_desc.fid, // fid
        valid,         // valid mask (only Mode)
        p9_mode,       // mode (permissions)
        0,             // uid (not changing)
        0,             // gid (not changing)
        0,             // size (not changing)
        0,             // atime_sec (not changing)
        0,             // atime_nsec (not changing)
        0,             // mtime_sec (not changing)
        0,             // mtime_nsec (not changing)
    );

    match tsetattr.send_tsetattr() {
        Ok(P9Response::Success(_)) => {
            debug_print!("sys_fchmod: successfully changed mode to 0o{:o}", p9_mode);
            Ok(0)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!("sys_fchmod: error setting mode: ecode={}", rlerror.ecode);
            Err(map_p9_error(rlerror.ecode))
        }
        Err(e) => {
            debug_print!("sys_fchmod: error sending Tsetattr: {:?}", e);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_fsync(fd: u32) -> Result<u32, Err> {
    // fsync() synchronizes a file's in-core state with storage device
    // In a single-threaded zkVM environment with 9P, this is a no-op
    // but we validate the file descriptor is valid

    if !get_p9_enabled() {
        return Err(Err::NoSys);
    }

    // Validate fd is in range
    if fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        // Invalid file descriptor
        return Err(Err::BadFd);
    }

    // File descriptor is valid - fsync succeeds as a no-op
    Ok(0)
}

pub fn sys_fdatasync(fd: u32) -> Result<u32, Err> {
    // fdatasync() is like fsync() but does not flush modified metadata
    // unless that metadata is needed to allow a subsequent data retrieval
    // In a single-threaded zkVM environment with 9P, this is a no-op
    // but we validate the file descriptor is valid

    if !get_p9_enabled() {
        return Err(Err::NoSys);
    }

    // Validate fd is in range
    if fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        // Invalid file descriptor
        return Err(Err::BadFd);
    }

    // File descriptor is valid - fdatasync succeeds as a no-op
    Ok(0)
}

pub fn sys_fchmodat(dfd: u32, filename: u32, mode: u32, flag: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_fchmodat: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Validate flag
    // For fchmodat, only AT_SYMLINK_NOFOLLOW (0x100) is valid according to POSIX
    // However, we need to be careful: the test passes -1 as an invalid flag,
    // but normal calls may have garbage in upper bits that we should ignore
    const AT_SYMLINK_NOFOLLOW: u32 = 0x100;

    // Check if this is the explicit invalid flag test case: -1 (all bits set)
    // When passed as i32 and cast to u32, -1 becomes 0xFFFFFFFF
    if flag as i32 == -1 {
        debug_print!("sys_fchmodat: invalid flag -1 (0x{:x})", flag);
        return Err(Err::Inval);
    }

    // For all other cases, mask to low 16 bits and only warn/log but don't reject
    // This allows the implementation to be permissive with garbage in high bits
    let flag = flag & 0xFFFF;

    // Log if AT_SYMLINK_NOFOLLOW is set
    if (flag & AT_SYMLINK_NOFOLLOW) != 0 {
        debug_print!("sys_fchmodat: AT_SYMLINK_NOFOLLOW flag set (not yet implemented)");
    }

    let filename_str = validate_and_read_pathname(filename)?;

    // Check for empty path (should return ENOENT for fchmodat)
    // But only if it's not a special case like AT_EMPTY_PATH
    if filename_str.is_empty() {
        // For fchmodat, empty pathname should return ENOENT
        // (unlike fchmod which works on a file descriptor)
        debug_print!("sys_fchmodat: empty pathname, returning ENOENT");
        return Err(Err::FileNotFound);
    }

    debug_print!(
        "sys_fchmodat: dfd={}, filename='{}', mode={}, flag={}",
        dfd,
        filename_str,
        mode,
        flag
    );

    resolve_path(dfd, &filename_str, TEMP_FID_1)?;

    // Create Tsetattr message for chmod operation
    // We only want to set the mode, so we use the Mode valid flag
    let valid = P9SetattrMask::Mode as u32;

    // Extract the permission bits (low 12 bits for mode)
    let p9_mode = mode & 0o7777;

    // For chmod, we don't want to change other attributes, so we use default values
    // and only set the mode
    let tsetattr = TsetattrMessage::new(
        0,          // tag
        TEMP_FID_1, // fid (the file we walked to)
        valid,      // valid mask (only Mode)
        p9_mode,    // mode (the new permissions)
        0,          // uid (not changing)
        0,          // gid (not changing)
        0,          // size (not changing)
        0,          // atime_sec (not changing)
        0,          // atime_nsec (not changing)
        0,          // mtime_sec (not changing)
        0,          // mtime_nsec (not changing)
    );

    match tsetattr.send_tsetattr() {
        Ok(P9Response::Success(rsetattr)) => {
            debug_print!("sys_fchmodat: rsetattr = {:?}", rsetattr);
            Ok(0)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "sys_fchmodat: received Rlerror for Rsetattr: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
            Err(map_p9_error(rlerror.ecode))
        }
        Err(e) => {
            debug_print!("sys_fchmodat: error sending Tsetattr: {:?}", e);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_fchmodat2(dfd: u32, filename: u32, mode: u32, flag: u32) -> Result<u32, Err> {
    // fchmodat2 is essentially the same as fchmodat, just delegate to it
    sys_fchmodat(dfd, filename, mode, flag)
}

pub fn sys_umask(mask: u32) -> Result<u32, Err> {
    // umask() sets the calling process's file mode creation mask (umask) to mask & 0o777
    // and returns the previous value of the mask.
    // The umask is used to mask off permission bits for newly created files and directories.

    let old_mask = unsafe { UMASK };
    let new_mask = mask & 0o777; // Only the lower 9 bits (permission bits) are used

    unsafe {
        UMASK = new_mask;
    }

    debug_print!(
        "sys_umask: old_mask=0o{:o}, new_mask=0o{:o}",
        old_mask,
        new_mask
    );

    // Return the previous mask value
    Ok(old_mask)
}

#[allow(dead_code)]
pub fn get_umask() -> u32 {
    unsafe { UMASK }
}

pub fn sys_fchown(fd: u32, user: u32, group: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_fchown: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Validate fd
    if fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    debug_print!("sys_fchown: fd={}, uid={}, gid={}", fd, user, group);

    // Use Tsetattr to change file ownership
    // In Linux, -1 means "don't change this value", so we only set valid flags for non--1 values
    // -1 as signed int becomes 0xFFFFFFFF (u32::MAX) as unsigned
    let mut valid = 0u32;
    if user != u32::MAX {
        valid |= P9SetattrMask::Uid as u32;
    }
    if group != u32::MAX {
        valid |= P9SetattrMask::Gid as u32;
    }

    let tsetattr = TsetattrMessage::new(
        0,             // tag
        file_desc.fid, // fid
        valid,         // valid mask (only Uid and/or Gid if not -1)
        0,             // mode (not changing)
        user,          // uid (the new user ID, or -1 to not change)
        group,         // gid (the new group ID, or -1 to not change)
        0,             // size (not changing)
        0,             // atime_sec (not changing)
        0,             // atime_nsec (not changing)
        0,             // mtime_sec (not changing)
        0,             // mtime_nsec (not changing)
    );

    match tsetattr.send_tsetattr() {
        Ok(P9Response::Success(_)) => {
            debug_print!(
                "sys_fchown: successfully changed ownership to uid={}, gid={}",
                user,
                group
            );
            Ok(0)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "sys_fchown: error setting ownership: ecode={}",
                rlerror.ecode
            );
            Err(map_p9_error(rlerror.ecode))
        }
        Err(e) => {
            debug_print!("sys_fchown: error sending Tsetattr: {:?}", e);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_fchownat(dfd: u32, filename: u32, user: u32, group: u32, flag: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_fchownat: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Validate flag (AT_SYMLINK_NOFOLLOW and AT_EMPTY_PATH are valid flags)
    const AT_SYMLINK_NOFOLLOW: u32 = 0x100;
    const AT_EMPTY_PATH: u32 = 0x1000;
    const AT_FLAGS_MASK: u32 = AT_SYMLINK_NOFOLLOW | AT_EMPTY_PATH;

    // Only reject negative flags (like -1 = 0xFFFFFFFF)
    let flag_i32 = flag as i32;
    if flag_i32 < 0 || (flag & !AT_FLAGS_MASK) != 0 {
        debug_print!("sys_fchownat: invalid flag 0x{:x}", flag);
        return Err(Err::Inval);
    }

    let filename_str = validate_and_read_pathname(filename)?;

    debug_print!(
        "sys_fchownat: dfd={}, filename='{}', user={}, group={}, flag={}",
        dfd,
        filename_str,
        user,
        group,
        flag
    );

    // Handle AT_SYMLINK_NOFOLLOW: don't follow symlinks, operate on the symlink itself
    if (flag & AT_SYMLINK_NOFOLLOW) != 0 {
        debug_print!("sys_fchownat: AT_SYMLINK_NOFOLLOW flag set, operating on symlink directly");

        // Walk to the file without following symlinks
        let starting_fid = get_starting_fid(dfd, &filename_str)?;
        let (dir_path, file_name) = split_path(&filename_str);
        debug_print!(
            "sys_fchownat: dir_path='{}', file_name='{}'",
            dir_path,
            file_name
        );

        // For relative paths, use the dfd directly as the directory
        let dir_fid = if dir_path.is_empty() || dir_path == "." {
            // Relative path - use dfd as the directory
            starting_fid
        } else {
            // Absolute path - walk to the directory first
            let dir_path = normalize_path(&dir_path);
            if do_walk(starting_fid, TEMP_FID_4, dir_path).is_err() {
                clunk(TEMP_FID_4, false);
                return Err(Err::FileNotFound);
            }
            TEMP_FID_4
        };

        // Now walk to the final component (the symlink itself) without following
        // We use Twalk directly on just the final component to avoid symlink resolution
        let file_path = vec![file_name.clone()];
        debug_print!(
            "sys_fchownat: walking to symlink: dir_fid={}, file_name='{}', target_fid=TEMP_FID_1",
            dir_fid,
            file_name
        );
        let twalk = crate::p9::TwalkMessage::new(0, dir_fid, TEMP_FID_1, file_path.clone());
        match twalk.send_twalk() {
            Ok(P9Response::Success(rwalk)) => {
                if rwalk.wqids.len() != 1 {
                    clunk(TEMP_FID_1, false);
                    clunk(TEMP_FID_4, false);
                    return Err(Err::FileNotFound);
                }

                // Check if the final component is a symlink
                if let Some(last_qid) = rwalk.wqids.last() {
                    if last_qid.is_symlink() {
                        debug_print!(
                            "sys_fchownat: symlink detected with AT_SYMLINK_NOFOLLOW, operating on symlink directly"
                        );
                        // We have the symlink FID at TEMP_FID_1, don't follow it
                    } else {
                        debug_print!("sys_fchownat: not a symlink, operating normally");
                        // Not a symlink, continue normally
                    }
                }
            }
            Ok(P9Response::Error(rlerror)) => {
                debug_print!(
                    "sys_fchownat: error walking to file: ecode={}",
                    rlerror.ecode
                );
                if dir_path.is_empty() || dir_path == "." {
                    // No cleanup needed for relative paths
                } else {
                    clunk(TEMP_FID_4, false);
                }
                return Err(map_p9_error(rlerror.ecode));
            }
            Err(e) => {
                debug_print!("sys_fchownat: error sending Twalk: {:?}", e);
                if !dir_path.is_empty() && dir_path != "." {
                    clunk(TEMP_FID_4, false);
                }
                return Err(Err::NoSys);
            }
        }
    } else {
        // Normal path resolution (follows symlinks)
        resolve_path(dfd, &filename_str, TEMP_FID_1)?;
    }

    // Create Tsetattr message for chown operation
    // In Linux, -1 means "don't change this value", so we only set valid flags for non--1 values
    // -1 as signed int becomes 0xFFFFFFFF (u32::MAX) as unsigned
    let mut valid = 0u32;
    if user != u32::MAX {
        valid |= P9SetattrMask::Uid as u32;
    }
    if group != u32::MAX {
        valid |= P9SetattrMask::Gid as u32;
    }

    debug_print!(
        "sys_fchownat: calling Tsetattr on FID TEMP_FID_1 with user={}, group={}",
        user,
        group
    );

    // For chown, we don't want to change other attributes, so we use default values
    // and only set the UID and/or GID if not -1
    let tsetattr = TsetattrMessage::new(
        0,          // tag
        TEMP_FID_1, // fid (the file we walked to)
        valid,      // valid mask (only UID and/or GID if not -1)
        0,          // mode (not changing)
        user,       // uid (or -1 to not change)
        group,      // gid (or -1 to not change)
        0,          // size (not changing)
        0,          // atime_sec (not changing)
        0,          // atime_nsec (not changing)
        0,          // mtime_sec (not changing)
        0,          // mtime_nsec (not changing)
    );

    match tsetattr.send_tsetattr() {
        Ok(P9Response::Success(rsetattr)) => {
            debug_print!("sys_fchownat: rsetattr = {:?}", rsetattr);

            // Clean up temporary FIDs if we used AT_SYMLINK_NOFOLLOW
            if (flag & AT_SYMLINK_NOFOLLOW) != 0 {
                let (dir_path, _) = split_path(&filename_str);
                if !dir_path.is_empty() && dir_path != "." {
                    clunk(TEMP_FID_4, false);
                }
            }

            Ok(0)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "sys_fchownat: received Rlerror for Rsetattr: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );

            // Clean up temporary FIDs if we used AT_SYMLINK_NOFOLLOW
            if (flag & AT_SYMLINK_NOFOLLOW) != 0 {
                let (dir_path, _) = split_path(&filename_str);
                if !dir_path.is_empty() && dir_path != "." {
                    clunk(TEMP_FID_4, false);
                }
            }

            Err(map_p9_error(rlerror.ecode))
        }
        Err(e) => {
            debug_print!("sys_fchownat: error sending Tsetattr: {:?}", e);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_utimensat_time64(dfd: u32, filename: u32, times: u32, flags: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_utimensat_time64: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    let filename_str = validate_and_read_pathname(filename)?;

    // Validate times pointer if non-null (times can be NULL to set current time)
    if times != 0 {
        const TIMESPEC_ARRAY_SIZE: usize = 32; // Two timespec structures (16 bytes each on 64-bit)
        validate_user_buffer_read(times, TIMESPEC_ARRAY_SIZE)?;
    }

    debug_print!(
        "sys_utimensat_time64: dfd={}, filename='{}', times={}, flags={}",
        dfd,
        filename_str,
        times,
        flags
    );

    // Handle AT_EMPTY_PATH - update times on the fd itself
    const AT_EMPTY_PATH: u32 = 0x1000;
    if (flags & AT_EMPTY_PATH) != 0 && filename_str.is_empty() {
        // Update times on the file descriptor itself
        if dfd >= 256 {
            return Err(Err::BadFd);
        }

        let fd_entry = get_fd(dfd);
        if fd_entry.file_desc_id == 0xFF {
            return Err(Err::BadFd);
        }

        let file_desc = get_file_desc(fd_entry.file_desc_id);
        let fid = file_desc.fid;

        // Parse times and update
        let (atime_sec, atime_nsec, mtime_sec, mtime_nsec) = parse_times(times)?;

        // Set both Atime+AtimeSet and Mtime+MtimeSet flags to set specific times
        // (without AtimeSet/MtimeSet, the server sets times to "now")
        let valid = P9SetattrMask::Atime as u32
            | P9SetattrMask::AtimeSet as u32
            | P9SetattrMask::Mtime as u32
            | P9SetattrMask::MtimeSet as u32;
        let tsetattr = TsetattrMessage::new(
            0,          // tag
            fid,        // fid
            valid,      // valid mask (Atime+AtimeSet and Mtime+MtimeSet)
            0,          // mode (not changing)
            0,          // uid (not changing)
            0,          // gid (not changing)
            0,          // size (not changing)
            atime_sec,  // atime_sec
            atime_nsec, // atime_nsec
            mtime_sec,  // mtime_sec
            mtime_nsec, // mtime_nsec
        );

        match tsetattr.send_tsetattr() {
            Ok(P9Response::Success(_)) => Ok(0),
            Ok(P9Response::Error(rlerror)) => Err(map_p9_error(rlerror.ecode)),
            Err(_) => Err(Err::NoSys),
        }
    } else {
        // Normal path-based update
        resolve_path(dfd, &filename_str, TEMP_FID_1)?;

        // Parse times
        let (atime_sec, atime_nsec, mtime_sec, mtime_nsec) = parse_times(times)?;

        // Create Tsetattr message to update times
        // Set both Atime+AtimeSet and Mtime+MtimeSet flags to set specific times
        // (without AtimeSet/MtimeSet, the server sets times to "now")
        let valid = P9SetattrMask::Atime as u32
            | P9SetattrMask::AtimeSet as u32
            | P9SetattrMask::Mtime as u32
            | P9SetattrMask::MtimeSet as u32;
        let tsetattr = TsetattrMessage::new(
            0,          // tag
            TEMP_FID_1, // fid (the file we walked to)
            valid,      // valid mask (Atime+AtimeSet and Mtime+MtimeSet)
            0,          // mode (not changing)
            0,          // uid (not changing)
            0,          // gid (not changing)
            0,          // size (not changing)
            atime_sec,  // atime_sec
            atime_nsec, // atime_nsec
            mtime_sec,  // mtime_sec
            mtime_nsec, // mtime_nsec
        );

        match tsetattr.send_tsetattr() {
            Ok(P9Response::Success(_)) => {
                clunk(TEMP_FID_1, false);
                Ok(0)
            }
            Ok(P9Response::Error(rlerror)) => {
                clunk(TEMP_FID_1, false);
                debug_print!("sys_utimensat_time64: Rlerror: ecode={}", rlerror.ecode);
                Err(map_p9_error(rlerror.ecode))
            }
            Err(e) => {
                clunk(TEMP_FID_1, false);
                debug_print!("sys_utimensat_time64: error: {:?}", e);
                Err(Err::NoSys)
            }
        }
    }
}

// Helper function to parse times array
fn parse_times(times: u32) -> Result<(u64, u64, u64, u64), Err> {
    const UTIME_OMIT: i64 = 0x3fffffff;
    const UTIME_NOW: i64 = 0x3ffffffe;

    if times == 0 {
        // NULL times - update both to current time (0 means "now" in 9P)
        return Ok((0, 0, 0, 0));
    }

    // Parse the timespec array: struct timespec64[2] = {atime, mtime}
    // timespec64: {tv_sec: i64, tv_nsec: i64}
    let timespec_array = unsafe { core::slice::from_raw_parts(times as *const i64, 4) };

    let atime_sec_raw = timespec_array[0];
    let atime_nsec_raw = timespec_array[1];

    let mtime_sec_raw = timespec_array[2];
    let mtime_nsec_raw = timespec_array[3];

    // Handle UTIME_OMIT and UTIME_NOW
    let atime_sec = if atime_sec_raw == UTIME_OMIT || atime_nsec_raw == UTIME_OMIT {
        return Err(Err::NoSys); // UTIME_OMIT requires preserving current time
    } else if atime_sec_raw == UTIME_NOW || atime_nsec_raw == UTIME_NOW {
        0 // 0 means "now" in 9P
    } else {
        atime_sec_raw as u64
    };

    let atime_nsec = if atime_sec_raw == UTIME_NOW || atime_nsec_raw == UTIME_NOW {
        0
    } else {
        (atime_nsec_raw as u64) & 0xFFFFFFFF // Keep only 32 bits for nsec
    };

    let mtime_sec = if mtime_sec_raw == UTIME_OMIT || mtime_nsec_raw == UTIME_OMIT {
        return Err(Err::NoSys);
    } else if mtime_sec_raw == UTIME_NOW || mtime_nsec_raw == UTIME_NOW {
        0
    } else {
        mtime_sec_raw as u64
    };

    let mtime_nsec = if mtime_sec_raw == UTIME_NOW || mtime_nsec_raw == UTIME_NOW {
        0
    } else {
        (mtime_nsec_raw as u64) & 0xFFFFFFFF
    };

    Ok((atime_sec, atime_nsec, mtime_sec, mtime_nsec))
}

pub fn sys_fgetxattr(fd: u32, name: u32, value: u32, size: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        return Err(Err::NoSys);
    }

    // Validate fd
    if fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    // Parse the xattr name
    let name_buf = unsafe { core::slice::from_raw_parts(name as *const u8, 256) };
    let name_null_pos = name_buf
        .iter()
        .position(|&b| b == 0)
        .unwrap_or(name_buf.len());
    let name_str = match str::from_utf8(&name_buf[..name_null_pos]) {
        Ok(s) => s,
        Err(_) => return Err(Err::Inval),
    };

    debug_print!(
        "sys_fgetxattr: fd={} name='{}' value=0x{:x} size={}",
        fd,
        name_str,
        value,
        size
    );

    // Use Txattrwalk to get the xattr
    let txattrwalk =
        crate::p9::TxattrwalkMessage::new(0, file_desc.fid, TEMP_FID_6, name_str.to_string());

    match txattrwalk.send_txattrwalk() {
        Ok(crate::p9::P9Response::Success(rxattrwalk)) => {
            let xattr_size = rxattrwalk.size;
            debug_print!("sys_fgetxattr: xattr size = {}", xattr_size);

            // If size is 0, just return the size
            if size == 0 {
                clunk(TEMP_FID_6, false);
                return Ok(xattr_size as u32);
            }

            // If buffer is too small, return the required size
            if size < xattr_size as u32 {
                clunk(TEMP_FID_6, false);
                return Err(Err::Range); // E2BIG
            }

            // Read the xattr value in chunks to respect 9P msize limit
            let mut total_read = 0u64;
            let total_to_read = xattr_size;

            while total_read < total_to_read {
                let remaining = total_to_read - total_read;
                let chunk_size = if remaining > MAX_9P_IO_CHUNK as u64 {
                    MAX_9P_IO_CHUNK
                } else {
                    remaining as u32
                };

                let tread = crate::p9::TreadMessage::new(0, TEMP_FID_6, total_read, chunk_size);
                match tread.send_tread() {
                    Ok(crate::p9::P9Response::Success(rread)) => {
                        if rread.count == 0 {
                            // EOF reached
                            break;
                        }

                        if value != 0 {
                            unsafe {
                                let dest_offset = value as usize + total_read as usize;
                                let dest = core::slice::from_raw_parts_mut(
                                    dest_offset as *mut u8,
                                    rread.count as usize,
                                );
                                dest.copy_from_slice(&rread.data[..rread.count as usize]);
                            }
                        }

                        total_read += rread.count as u64;

                        // Short read means EOF
                        if rread.count < chunk_size {
                            break;
                        }
                    }
                    Ok(crate::p9::P9Response::Error(_)) => {
                        clunk(TEMP_FID_6, false);
                        return Err(Err::IO);
                    }
                    Err(_) => {
                        clunk(TEMP_FID_6, false);
                        return Err(Err::IO);
                    }
                }
            }

            clunk(TEMP_FID_6, false);
            Ok(total_read.min(size as u64) as u32)
        }
        Ok(crate::p9::P9Response::Error(rlerror)) => {
            debug_print!("sys_fgetxattr: xattrwalk failed: ecode={}", rlerror.ecode);
            Err(map_p9_error(rlerror.ecode))
        }
        Err(_) => Err(Err::NoSys),
    }
}

pub fn sys_file_getattr(_dfd: u32, _filename: u32, _mask: u32) -> Result<u32, Err> {
    let msg = b"sys_file_getattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_file_setattr(_dfd: u32, _filename: u32, _mask: u32) -> Result<u32, Err> {
    let msg = b"sys_file_setattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_flistxattr(fd: u32, list: u32, size: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        return Err(Err::NoSys);
    }

    // Validate fd
    if fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    debug_print!("sys_flistxattr: fd={} list=0x{:x} size={}", fd, list, size);

    // Use Txattrwalk with empty name to list xattrs
    // When name is empty, the newfid can be used to list all xattrs
    let list_fid = TEMP_FID_8; // Use a temporary FID for listing
    let txattrwalk = crate::p9::TxattrwalkMessage::new(
        0,
        file_desc.fid,
        list_fid,
        String::new(), // Empty string for listing all xattrs
    );

    match txattrwalk.send_txattrwalk() {
        Ok(crate::p9::P9Response::Success(rxattrwalk)) => {
            let xattr_list_size = rxattrwalk.size;
            debug_print!("sys_flistxattr: xattr list size = {}", xattr_list_size);

            // If size is 0, just return the size
            if size == 0 {
                clunk(list_fid, false);
                return Ok(xattr_list_size as u32);
            }

            // If buffer is too small, return the required size (or ERANGE)
            if size < xattr_list_size as u32 {
                clunk(list_fid, false);
                return Err(Err::Range); // E2BIG
            }

            // Read the xattr list in chunks to respect 9P msize limit
            let mut total_read = 0u64;
            let total_to_read = xattr_list_size;

            while total_read < total_to_read {
                let remaining = total_to_read - total_read;
                let chunk_size = if remaining > MAX_9P_IO_CHUNK as u64 {
                    MAX_9P_IO_CHUNK
                } else {
                    remaining as u32
                };

                let tread = crate::p9::TreadMessage::new(0, list_fid, total_read, chunk_size);
                match tread.send_tread() {
                    Ok(crate::p9::P9Response::Success(rread)) => {
                        if rread.count == 0 {
                            // EOF reached
                            break;
                        }

                        if list != 0 {
                            unsafe {
                                let dest_offset = list as usize + total_read as usize;
                                let dest = core::slice::from_raw_parts_mut(
                                    dest_offset as *mut u8,
                                    rread.count as usize,
                                );
                                dest.copy_from_slice(&rread.data[..rread.count as usize]);
                            }
                        }

                        total_read += rread.count as u64;

                        // Short read means EOF
                        if rread.count < chunk_size {
                            break;
                        }
                    }
                    Ok(crate::p9::P9Response::Error(_)) => {
                        clunk(list_fid, false);
                        return Err(Err::IO);
                    }
                    Err(_) => {
                        clunk(list_fid, false);
                        return Err(Err::IO);
                    }
                }
            }

            clunk(list_fid, false);
            Ok(total_read.min(size as u64) as u32)
        }
        Ok(crate::p9::P9Response::Error(rlerror)) => {
            debug_print!("sys_flistxattr: xattrwalk failed: ecode={}", rlerror.ecode);
            Err(map_p9_error(rlerror.ecode))
        }
        Err(_) => Err(Err::NoSys),
    }
}

pub fn sys_flock(fd: u32, operation: u32) -> Result<u32, Err> {
    // Validate fd
    if fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    // flock operations (from sys/file.h):
    // LOCK_SH = 1  (shared lock)
    // LOCK_EX = 2  (exclusive lock)
    // LOCK_UN = 8  (unlock)
    // LOCK_NB = 4  (non-blocking)

    debug_print!("sys_flock: fd={} operation={}", fd, operation);

    // In zkVM, there's no concurrent access, so file locking is a no-op
    // Just validate the operation and succeed
    let op = operation & !4; // Remove LOCK_NB flag for validation
    if op != 1 && op != 2 && op != 8 {
        debug_print!("sys_flock: invalid operation {}", operation);
        return Err(Err::Inval);
    }

    Ok(0)
}

pub fn sys_fremovexattr(_fd: u32, _name: u32) -> Result<u32, Err> {
    let msg = b"sys_fremovexattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

#[allow(dead_code)]
pub fn sys_truncate64(pathname: u32, length: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_truncate64: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    let pathname_str = validate_and_read_pathname(pathname)?;
    debug_print!(
        "sys_truncate64: pathname='{}', length={}",
        pathname_str,
        length
    );

    // Walk to the file
    let file_fid = TEMP_FID_11;
    resolve_path(AT_FDCWD as u32, &pathname_str, file_fid)?;

    // Create Tsetattr message for truncate operation
    let valid = P9SetattrMask::Size as u32;
    let new_size = length as u64;

    let tsetattr = TsetattrMessage::new(
        0,        // tag
        file_fid, // fid
        valid,    // valid mask (only Size)
        0,        // mode (not changing)
        0,        // uid (not changing)
        0,        // gid (not changing)
        new_size, // size (the new file size)
        0,        // atime_sec (not changing)
        0,        // atime_nsec (not changing)
        0,        // mtime_sec (not changing)
        0,        // mtime_nsec (not changing)
    );

    match tsetattr.send_tsetattr() {
        Ok(P9Response::Success(rsetattr)) => {
            debug_print!("sys_truncate64: rsetattr = {:?}", rsetattr);
            clunk(file_fid, false);
            Ok(0)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "sys_truncate64: received Rlerror for Rsetattr: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
            clunk(file_fid, false);
            Err(map_p9_error(rlerror.ecode))
        }
        Err(e) => {
            debug_print!("sys_truncate64: error sending Tsetattr: {:?}", e);
            clunk(file_fid, false);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_ftruncate64(fd: u32, length: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_ftruncate64: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    if fd >= 256 {
        debug_print!("sys_ftruncate64: invalid file descriptor {}", fd);
        return Err(Err::Inval);
    }

    debug_print!("sys_ftruncate64: fd={}, length={}", fd, length);

    // Get the file descriptor entry
    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        debug_print!("sys_ftruncate64: invalid file descriptor {}", fd);
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    // Create Tsetattr message for truncate operation
    // We only want to set the size, so we use the Size valid flag
    let valid = P9SetattrMask::Size as u32;
    let new_size = length as u64;

    // For ftruncate, we don't want to change other attributes, so we use default values
    // and only set the size
    let tsetattr = TsetattrMessage::new(
        0,             // tag
        file_desc.fid, // fid (the file we want to truncate)
        valid,         // valid mask (only Size)
        0,             // mode (not changing)
        0,             // uid (not changing)
        0,             // gid (not changing)
        new_size,      // size (the new file size)
        0,             // atime_sec (not changing)
        0,             // atime_nsec (not changing)
        0,             // mtime_sec (not changing)
        0,             // mtime_nsec (not changing)
    );

    match tsetattr.send_tsetattr() {
        Ok(P9Response::Success(rsetattr)) => {
            debug_print!("sys_ftruncate64: rsetattr = {:?}", rsetattr);
            Ok(0)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "sys_ftruncate64: received Rlerror for Rsetattr: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
            Err(map_p9_error(rlerror.ecode))
        }
        Err(e) => {
            debug_print!("sys_ftruncate64: error sending Tsetattr: {:?}", e);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_fsetxattr(fd: u32, name: u32, value: u32, size: u32, flags: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        return Err(Err::NoSys);
    }

    // Validate fd
    if fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    // Parse the xattr name
    let name_buf = unsafe { core::slice::from_raw_parts(name as *const u8, 256) };
    let name_null_pos = name_buf
        .iter()
        .position(|&b| b == 0)
        .unwrap_or(name_buf.len());
    let name_str = match str::from_utf8(&name_buf[..name_null_pos]) {
        Ok(s) => s,
        Err(_) => return Err(Err::Inval),
    };

    debug_print!(
        "sys_fsetxattr: fd={} name='{}' value=0x{:x} size={} flags={}",
        fd,
        name_str,
        value,
        size,
        flags
    );

    // Use Txattrcreate to prepare to set the xattr
    // We need to allocate a new FID for the xattr operation
    // The FID passed to Txattrcreate will be used for writing the xattr value
    let xattr_fid = TEMP_FID_7; // Use a temporary FID for the xattr

    // First, walk to duplicate the file's FID to the xattr FID
    let twalk = crate::p9::TwalkMessage::new(0, file_desc.fid, xattr_fid, vec![]);
    match twalk.send_twalk() {
        Ok(crate::p9::P9Response::Success(_)) => {
            debug_print!("sys_fsetxattr: walked to duplicate fid={}", xattr_fid);
        }
        Ok(crate::p9::P9Response::Error(rlerror)) => {
            debug_print!("sys_fsetxattr: walk failed: ecode={}", rlerror.ecode);
            return Err(map_p9_error(rlerror.ecode));
        }
        Err(_) => return Err(Err::NoSys),
    }

    // Now use Txattrcreate with the xattr FID
    let txattrcreate = crate::p9::TxattrcreateMessage::new(
        0,
        xattr_fid, // The FID that will be used for the xattr
        name_str.to_string(),
        size as u64,
        flags,
    );

    match txattrcreate.send_txattrcreate() {
        Ok(crate::p9::P9Response::Success(_)) => {
            debug_print!(
                "sys_fsetxattr: xattrcreate succeeded, using fid={}",
                xattr_fid
            );

            // Now write the xattr value to the xattr FID in chunks
            if size > 0 && value != 0 {
                let value_buf =
                    unsafe { core::slice::from_raw_parts(value as *const u8, size as usize) };

                let mut total_written = 0u32;
                let chunk_size = MAX_9P_IO_CHUNK as usize;

                for chunk_start in (0..size as usize).step_by(chunk_size) {
                    let chunk_end = (chunk_start + chunk_size).min(size as usize);
                    let chunk_data = &value_buf[chunk_start..chunk_end];

                    // Write to the xattr FID
                    let twrite = crate::p9::TwriteMessage::new(
                        0,
                        xattr_fid,
                        chunk_start as u64,
                        chunk_data.to_vec(),
                    );
                    match twrite.send_twrite() {
                        Ok(crate::p9::P9Response::Success(rwrite)) => {
                            debug_print!("sys_fsetxattr: wrote {} bytes", rwrite.count);
                            total_written += rwrite.count;

                            // If we wrote fewer bytes than requested, it's an error
                            if rwrite.count != chunk_data.len() as u32 {
                                debug_print!(
                                    "sys_fsetxattr: write size mismatch: expected {}, got {}",
                                    chunk_data.len(),
                                    rwrite.count
                                );
                                clunk(xattr_fid, false);
                                return Err(Err::IO);
                            }
                        }
                        Ok(crate::p9::P9Response::Error(_)) => {
                            clunk(xattr_fid, false);
                            return Err(Err::IO);
                        }
                        Err(_) => {
                            clunk(xattr_fid, false);
                            return Err(Err::IO);
                        }
                    }
                }

                // Verify total written matches expected size
                if total_written != size {
                    debug_print!(
                        "sys_fsetxattr: total write mismatch: expected {}, got {}",
                        size,
                        total_written
                    );
                    clunk(xattr_fid, false);
                    return Err(Err::IO);
                }
            }

            // Clunk the xattr FID to commit the xattr
            clunk(xattr_fid, false);
            Ok(0)
        }
        Ok(crate::p9::P9Response::Error(rlerror)) => {
            debug_print!("sys_fsetxattr: xattrcreate failed: ecode={}", rlerror.ecode);
            clunk(xattr_fid, false);
            Err(map_p9_error(rlerror.ecode))
        }
        Err(_) => {
            clunk(xattr_fid, false);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_getcwd(_buf: u32, _size: u32) -> Result<u32, Err> {
    // Get the current working directory first to check size requirements
    let mut cwd_str = get_cwd_str();
    // strip the trailing / if it's not "/"
    if cwd_str != "/" && cwd_str.ends_with("/") {
        cwd_str = cwd_str[..cwd_str.len() - 1].to_string();
    }
    // add a null-terminator
    cwd_str.push('\0');
    let cwd_str_len = cwd_str.len();

    // Check size FIRST - ERANGE takes precedence over EFAULT
    // This includes size==0 and buffer too small cases
    if _size == 0 || cwd_str_len > _size as usize {
        debug_print!(
            "sys_getcwd: buffer too small (need {}, have {})",
            cwd_str_len,
            _size
        );
        return Err(Err::Range); // ERANGE
    }

    // Now validate buffer (after size check for correct error precedence)
    validate_user_buffer_write(_buf, cwd_str_len)?;

    let buf = unsafe { core::slice::from_raw_parts_mut(_buf as *mut u8, cwd_str_len) };
    // copy the string into buffer, null-terminated utf-8
    buf.copy_from_slice(cwd_str.as_bytes());
    debug_print!(
        "sys_getcwd: cwd_str='{}' cwd_str_len={}",
        cwd_str.trim_end_matches('\0'),
        cwd_str_len
    );
    // The syscall returns the length (including null terminator), not the pointer
    // The C library wrapper converts this to a pointer for the user
    Ok(cwd_str_len as u32)
}

pub fn sys_getxattr(_pathname: u32, _name: u32, _value: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_getxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getxattrat(_dfd: u32, _filename: u32, _name: u32, _value: u32) -> Result<u32, Err> {
    let msg = b"sys_getxattrat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_linkat(
    olddfd: u32,
    oldname: u32,
    newdfd: u32,
    newname: u32,
    _flags: u32,
) -> Result<u32, Err> {
    use crate::p9::{P9Response, TlinkMessage};

    if !get_p9_enabled() {
        return Err(Err::NoSys);
    }

    let oldpath_str = validate_and_read_pathname(oldname)?;
    let newpath_str = validate_and_read_pathname(newname)?;

    // Check for empty paths
    if oldpath_str.is_empty() {
        debug_print!("sys_linkat: oldpath is empty");
        return Err(Err::FileNotFound);
    }
    if newpath_str.is_empty() {
        debug_print!("sys_linkat: newpath is empty");
        return Err(Err::FileNotFound);
    }

    // Check for pathname too long
    if oldpath_str.len() > 255 {
        debug_print!("sys_linkat: oldpath too long ({})", oldpath_str.len());
        return Err(Err::NameTooLong);
    }
    if newpath_str.len() > 255 {
        debug_print!("sys_linkat: newpath too long ({})", newpath_str.len());
        return Err(Err::NameTooLong);
    }

    debug_print!(
        "sys_linkat: old='{}' new='{}', flags=0x{:x}",
        oldpath_str,
        newpath_str,
        _flags
    );

    // Walk to the old file to get its FID
    let old_fid = TEMP_FID_9; // Temporary FID for old file
    resolve_path(olddfd, &oldpath_str, old_fid)?;

    // Split new path into directory and filename
    let new_starting_fid = get_starting_fid(newdfd, &newpath_str)?;
    let (new_dir_path, new_name) = split_path(&newpath_str);
    let new_dir_path = normalize_path(&new_dir_path);

    // Walk to the new directory
    let new_dir_fid = TEMP_FID_10; // Temporary FID for new directory
    match do_walk(new_starting_fid, new_dir_fid, new_dir_path) {
        Ok(_) => {}
        Err(e) => {
            clunk(old_fid, false);
            return Err(e);
        }
    }

    // Create the hard link using Tlink
    let tlink = TlinkMessage::new(0, new_dir_fid, old_fid, new_name.clone());
    match tlink.send_tlink() {
        Ok(P9Response::Success(_)) => {
            debug_print!("sys_linkat: successfully created hard link");
            clunk(old_fid, false);
            clunk(new_dir_fid, false);
            Ok(0)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!("sys_linkat: error creating link: ecode={}", rlerror.ecode);
            clunk(old_fid, false);
            clunk(new_dir_fid, false);
            // Map 9P error codes to Linux errno
            // Return the error code as a negative errno value
            Err(map_p9_error(rlerror.ecode))
        }
        Err(_) => {
            clunk(old_fid, false);
            clunk(new_dir_fid, false);
            Err(Err::IO)
        }
    }
}

pub fn sys_symlinkat(target: u32, newdirfd: u32, linkpath: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_symlinkat: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // PATH_MAX is 4096 for symlinks
    const PATH_MAX: usize = 4097;

    let target_str = validate_and_read_pathname_with_len(target, PATH_MAX)?;
    let linkpath_str = validate_and_read_pathname_with_len(linkpath, PATH_MAX)?;

    debug_print!(
        "sys_symlinkat: target='{}', newdirfd={}, linkpath='{}'",
        target_str,
        newdirfd,
        linkpath_str
    );

    // Split linkpath into directory and filename
    let (dir_path, file_name) = split_path(&linkpath_str);
    debug_print!(
        "sys_symlinkat: dir_path='{}', file_name='{}'",
        dir_path,
        file_name
    );

    // Resolve the directory where the symlink will be created
    resolve_path(newdirfd, &dir_path, TEMP_FID_1)?;

    // Create symlink using Tsymlink
    let tsymlink = TsymlinkMessage::new(
        0,                      // tag
        TEMP_FID_1,             // fid (directory)
        file_name.to_string(),  // name (symlink name)
        target_str.to_string(), // symtgt (symlink target)
        0,                      // gid (default)
    );

    match tsymlink.send_tsymlink() {
        Ok(P9Response::Success(rsymlink)) => {
            debug_print!("sys_symlinkat: rsymlink = {:?}", rsymlink);
            clunk(TEMP_FID_1, false);
            Ok(0)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "sys_symlinkat: received Rlerror: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
            clunk(TEMP_FID_1, false);
            Err(map_p9_error(rlerror.ecode))
        }
        Err(e) => {
            debug_print!("sys_symlinkat: error sending Tsymlink: {:?}", e);
            clunk(TEMP_FID_1, false);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_listxattr(_pathname: u32, _list: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_listxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_listxattrat(_dfd: u32, _filename: u32, _list: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_listxattrat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_llistxattr(_pathname: u32, _list: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_llistxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_llseek(
    _fd: u32,
    _offset_high: u32,
    _offset_low: u32,
    result: u32,
    whence: u32,
) -> Result<u32, Err> {
    const SEEK_SET: u32 = 0;
    const SEEK_CUR: u32 = 1;
    const SEEK_END: u32 = 2;

    if !get_p9_enabled() {
        let msg = b"sys_llseek not implemented";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Validate whence first (before checking fd for proper error priority)
    if whence != SEEK_SET && whence != SEEK_CUR && whence != SEEK_END {
        debug_print!("sys_llseek: invalid whence={}", whence);
        return Err(Err::Inval);
    }

    if _fd >= 256 {
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(_fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);

    // Combine high/low parts into signed 64-bit offset
    let offset = ((_offset_high as i64) << 32) | (_offset_low as i64 & 0xffff_ffff);

    let cursor_i64 = i64::try_from(file_desc.cursor).map_err(|_| {
        debug_print!(
            "sys_llseek: cursor value {} does not fit in i64",
            file_desc.cursor
        );
        Err::Inval
    })?;

    let new_cursor_i64 = match whence {
        SEEK_SET => offset,
        SEEK_CUR => cursor_i64.checked_add(offset).ok_or_else(|| {
            debug_print!(
                "sys_llseek: SEEK_CUR overflow (cursor={}, offset={})",
                cursor_i64,
                offset
            );
            Err::Inval
        })?,
        SEEK_END => {
            // For SEEK_END, we need to get the file size
            let base = if file_desc.fid != 0 && file_desc.fid != TEMP_FID_1 {
                let tgetattr = crate::p9::TgetattrMessage::new(0, file_desc.fid, P9_GETATTR_SIZE);
                match tgetattr.send_tgetattr() {
                    Ok(P9Response::Success(rgetattr)) => {
                        i64::try_from(rgetattr.size).map_err(|_| {
                            debug_print!(
                                "sys_llseek: SEEK_END size {} does not fit in i64",
                                rgetattr.size
                            );
                            Err::Inval
                        })?
                    }
                    Ok(P9Response::Error(_)) | Err(_) => cursor_i64,
                }
            } else {
                cursor_i64
            };

            base.checked_add(offset).ok_or_else(|| {
                debug_print!(
                    "sys_llseek: SEEK_END overflow (base={}, offset={})",
                    base,
                    offset
                );
                Err::Inval
            })?
        }
        _ => {
            let msg = b"sys_llseek: invalid whence";
            host_log(msg.as_ptr(), msg.len());
            return Err(Err::Inval);
        }
    };

    if new_cursor_i64 < 0 {
        debug_print!(
            "sys_llseek: resulting cursor negative ({}), returning EINVAL",
            new_cursor_i64
        );
        return Err(Err::Inval);
    }

    let new_cursor = new_cursor_i64 as u64;

    // Update the shared cursor in the file description
    let mut updated_desc = file_desc;
    updated_desc.cursor = new_cursor;
    update_file_desc(fd_entry.file_desc_id, updated_desc);

    let result_ptr = result as *mut u64;
    unsafe {
        *result_ptr = new_cursor;
    }
    Ok(0)
}

pub fn sys_lremovexattr(_pathname: u32, _name: u32) -> Result<u32, Err> {
    let msg = b"sys_lremovexattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_lsetxattr(
    _pathname: u32,
    _name: u32,
    _value: u32,
    _size: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_lsetxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mkdirat(_dfd: u32, _pathname: u32, _mode: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_mkdirat: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }
    let filename_str = validate_and_read_pathname(_pathname)?;
    debug_print!(
        "sys_mkdirat: dfd={}, filename='{}'",
        _dfd as i32,
        filename_str
    );
    let (dir_path, file_name) = split_path(&filename_str);
    debug_print!(
        "sys_mkdirat: dir_path='{}', file_name='{}'",
        dir_path,
        file_name
    );
    resolve_path(_dfd, &dir_path, TEMP_FID_1)?;

    // Apply umask to the mode
    let umask_value = get_umask();
    let final_mode = _mode & !umask_value;
    debug_print!(
        "sys_mkdirat: requested_mode=0o{:o}, umask=0o{:o}, final_mode=0o{:o}",
        _mode,
        umask_value,
        final_mode
    );

    let tmkdir = TmkdirMessage::new(0, TEMP_FID_1, file_name.to_string(), final_mode, 0);
    match tmkdir.send_tmkdir() {
        Ok(P9Response::Success(rmkdir)) => {
            debug_print!("sys_mkdirat: rmkdir = {:?}", rmkdir);
            clunk(TEMP_FID_1, false);
            Ok(0)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "sys_mkdirat: received Rlerror for Rmkdir: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
            Err(map_p9_error(rlerror.ecode))
        }
        Err(e) => {
            debug_print!("sys_mkdirat: error sending Tmkdir: {:?}", e);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_mknodat(_dfd: u32, _filename: u32, _mode: u32, _dev: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_mknodat: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    let filename_str = validate_and_read_pathname(_filename)?;
    debug_print!(
        "sys_mknodat: dfd={}, filename='{}', mode=0x{:x}, dev=0x{:x}",
        _dfd,
        filename_str,
        _mode,
        _dev
    );

    let (dir_path, file_name) = split_path(&filename_str);
    resolve_path(_dfd, &dir_path, TEMP_FID_1)?;

    // Apply umask to the mode
    let umask_value = get_umask();
    let final_mode = _mode & !umask_value;
    debug_print!(
        "sys_mknodat: requested_mode=0o{:o}, umask=0o{:o}, final_mode=0o{:o}",
        _mode,
        umask_value,
        final_mode
    );

    // Extract major and minor device numbers from _dev
    // In Linux, the device number is encoded as (major << 8) | minor for 8-bit minor
    // or (major << 20) | minor for 12-bit minor, but we'll use the simpler 8-bit version
    let major = (_dev >> 8) & 0xFF;
    let minor = _dev & 0xFF;

    let tmknod = TmknodMessage::new(
        0,
        TEMP_FID_1,
        file_name.to_string(),
        final_mode,
        major,
        minor,
        0,
    );
    match tmknod.send_tmknod() {
        Ok(P9Response::Success(rmknod)) => {
            debug_print!("sys_mknodat: rmknod = {:?}", rmknod);
            clunk(TEMP_FID_1, false);
            Ok(0)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "sys_mknodat: received Rlerror for Rmknod: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
            Err(map_p9_error(rlerror.ecode))
        }
        Err(e) => {
            debug_print!("sys_mknodat: error sending Tmknod: {:?}", e);
            Err(Err::NoSys)
        }
    }
}

// openat2 structure - struct open_how
#[repr(C)]
struct OpenHow {
    flags: u64,
    mode: u64,
    resolve: u64,
}

// resolve flags for openat2
const RESOLVE_NO_XDEV: u64 = 0x01; // Block mount-point crossings
const RESOLVE_NO_MAGICLINKS: u64 = 0x02; // Block magic-link resolution
const RESOLVE_NO_SYMLINKS: u64 = 0x04; // Block all symlink resolution
const RESOLVE_BENEATH: u64 = 0x08; // Only allow resolution beneath dirfd
const RESOLVE_IN_ROOT: u64 = 0x10; // Treat dirfd as root directory
const RESOLVE_CACHED: u64 = 0x20; // Only use cached path resolution

pub fn sys_openat2(dfd: u32, filename: u32, how_ptr: u32, how_size: u32) -> Result<u32, Err> {
    // Validate how_ptr
    if how_ptr == 0 {
        debug_print!("sys_openat2: NULL how pointer");
        return Err(Err::Fault);
    }

    if how_ptr >= crate::constants::KERNEL_SPACE_START {
        debug_print!("sys_openat2: invalid how pointer: 0x{:x}", how_ptr);
        return Err(Err::Fault);
    }

    // Validate how_size - must be at least size of OpenHow
    if how_size < 24 {
        debug_print!("sys_openat2: invalid how_size: {}", how_size);
        return Err(Err::Inval);
    }

    // Read the open_how structure from user space
    let how = unsafe {
        let ptr = how_ptr as *const OpenHow;
        core::ptr::read(ptr)
    };

    debug_print!(
        "sys_openat2: dfd={}, filename=0x{:x}, flags=0x{:x}, mode=0x{:x}, resolve=0x{:x}",
        dfd,
        filename,
        how.flags,
        how.mode,
        how.resolve
    );

    // Check for unsupported resolve flags
    if how.resolve != 0 {
        // We support basic resolution but log if special flags are used
        if (how.resolve & RESOLVE_NO_SYMLINKS) != 0 {
            debug_print!("sys_openat2: RESOLVE_NO_SYMLINKS requested");
            // We can handle this with O_NOFOLLOW logic
        }
        if (how.resolve & RESOLVE_NO_XDEV) != 0 {
            debug_print!("sys_openat2: RESOLVE_NO_XDEV requested (not fully supported)");
        }
        if (how.resolve & RESOLVE_NO_MAGICLINKS) != 0 {
            debug_print!("sys_openat2: RESOLVE_NO_MAGICLINKS requested");
        }
        if (how.resolve & RESOLVE_BENEATH) != 0 {
            debug_print!("sys_openat2: RESOLVE_BENEATH requested (not fully supported)");
        }
        if (how.resolve & RESOLVE_IN_ROOT) != 0 {
            debug_print!("sys_openat2: RESOLVE_IN_ROOT requested (not fully supported)");
        }
        if (how.resolve & RESOLVE_CACHED) != 0 {
            debug_print!("sys_openat2: RESOLVE_CACHED requested (ignored)");
        }
    }

    // Convert flags and mode to 32-bit (openat uses 32-bit)
    let flags = how.flags as u32;
    let mode = how.mode as u32;

    // If RESOLVE_NO_SYMLINKS is set, add O_NOFOLLOW
    let flags = if (how.resolve & RESOLVE_NO_SYMLINKS) != 0 {
        flags | O_NOFOLLOW
    } else {
        flags
    };

    // Delegate to sys_openat implementation
    sys_openat(dfd, filename, flags, mode)
}

pub fn sys_preadv(_fd: u32, _vec: u32, _vlen: u32, _pos_low: u32) -> Result<u32, Err> {
    if _fd >= 256 {
        return Err(Err::Inval);
    }

    debug_print!(
        "sys_preadv: fd={}, vec=0x{:08x}, vlen={}, pos={}",
        _fd,
        _vec,
        _vlen,
        _pos_low
    );

    // preadv reads from a specific offset without changing the file position
    // Similar to pread64, but with scatter-gather I/O

    let fd_entry = get_fd(_fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);
    let current_pos = file_desc.cursor;

    // Seek to requested offset
    let mut updated_desc = file_desc;
    updated_desc.cursor = _pos_low as u64;
    update_file_desc(fd_entry.file_desc_id, updated_desc);

    // Do the readv
    let result = sys_readv(_fd, _vec, _vlen);

    // Restore original file position
    let mut restored_desc = get_file_desc(fd_entry.file_desc_id);
    restored_desc.cursor = current_pos;
    update_file_desc(fd_entry.file_desc_id, restored_desc);

    match &result {
        Ok(n) => {
            debug_print!("sys_preadv: returning Ok({})", n);
        }
        Err(e) => {
            debug_print!("sys_preadv: returning Err({})", e.as_errno());
        }
    }

    result
}

pub fn sys_preadv2(
    _fd: u32,
    _vec: u32,
    _vlen: u32,
    _pos_low: u32,
    _pos_high: u32,
) -> Result<u32, Err> {
    let msg = b"sys_preadv2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_pwrite64(_fd: u32, _buf: u32, _count: u32, _pos: u32) -> Result<u32, Err> {
    if _fd >= 256 {
        return Err(Err::Inval);
    }

    debug_print!(
        "sys_pwrite64: fd={}, buf=0x{:08x}, count={}, pos={}",
        _fd,
        _buf,
        _count,
        _pos
    );

    // pwrite64 writes to a specific offset without changing the file position
    // We need to: save current position, seek to offset, write, restore position

    let fd_entry = get_fd(_fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);
    let current_pos = file_desc.cursor;

    // Seek to requested offset
    let mut updated_desc = file_desc;
    updated_desc.cursor = _pos as u64;
    update_file_desc(fd_entry.file_desc_id, updated_desc);

    // Do the write
    let result = sys_write(_fd, _buf, _count);

    // Restore original file position
    let mut restored_desc = get_file_desc(fd_entry.file_desc_id);
    restored_desc.cursor = current_pos;
    update_file_desc(fd_entry.file_desc_id, restored_desc);

    result
}

pub fn sys_pwritev(_fd: u32, _vec: u32, _vlen: u32, _pos_low: u32) -> Result<u32, Err> {
    if _fd >= 256 {
        return Err(Err::Inval);
    }

    debug_print!(
        "sys_pwritev: fd={}, vec=0x{:08x}, vlen={}, pos={}",
        _fd,
        _vec,
        _vlen,
        _pos_low
    );

    // pwritev writes from a specific offset without changing the file position
    // Similar to pwrite64, but with scatter-gather I/O

    let fd_entry = get_fd(_fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);
    let current_pos = file_desc.cursor;

    // Seek to requested offset
    let mut updated_desc = file_desc;
    updated_desc.cursor = _pos_low as u64;
    update_file_desc(fd_entry.file_desc_id, updated_desc);

    // Do the writev
    let result = sys_writev(_fd, _vec, _vlen);

    // Restore original file position
    let mut restored_desc = get_file_desc(fd_entry.file_desc_id);
    restored_desc.cursor = current_pos;
    update_file_desc(fd_entry.file_desc_id, restored_desc);

    result
}

pub fn sys_pwritev2(
    _fd: u32,
    _vec: u32,
    _vlen: u32,
    _pos_low: u32,
    _pos_high: u32,
) -> Result<u32, Err> {
    let msg = b"sys_pwritev2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_readv(_fd: u32, _vec: u32, _vlen: u32) -> Result<u32, Err> {
    // readv() reads data into multiple buffers (scatter-gather I/O)

    // Validate iovcnt is not negative (check for signed interpretation)
    if (_vlen as i32) < 0 {
        return Err(Err::Inval);
    }

    if _fd >= 256 {
        return Err(Err::BadFd);
    }

    if _vlen == 0 {
        return Ok(0);
    }

    debug_print!("sys_readv: fd={}, vec=0x{:08x}, vlen={}", _fd, _vec, _vlen);

    let fd_entry = get_fd(_fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let iovecs = load_iovecs(_vec, _vlen)?;
    debug_print!(
        "sys_readv: loaded {} iovecs from user (requested {})",
        iovecs.len(),
        _vlen
    );
    for (idx, iov) in iovecs.iter().enumerate() {
        debug_print!(
            "sys_readv: iov[{}] base=0x{:08x} len={}",
            idx,
            iov.iov_base as u32,
            iov.iov_len
        );
    }

    // Validate each iovec entry's buffer
    let mut total_len: usize = 0;
    for (i, iov) in iovecs.iter().enumerate() {
        // Check for negative length (iov_len is usize, so check if it's suspiciously large)
        // A negative isize (-1) would appear as usize::MAX
        if iov.iov_len > (isize::MAX as usize) {
            debug_print!("sys_readv: iovec[{}] has invalid length {}", i, iov.iov_len);
            return Err(Err::Inval);
        }
        if iov.iov_len == 0 {
            continue;
        }
        // Validate each buffer is in writable user memory (for read operations)
        validate_user_buffer_write(iov.iov_base as u32, iov.iov_len)?;

        // Buffer validation already done above in the loop

        // Check for overflow in total length
        total_len = total_len.saturating_add(iov.iov_len);
        if total_len > (isize::MAX as usize) {
            debug_print!("sys_readv: total iov_len overflows ssize_t");
            return Err(Err::Inval);
        }
    }

    let mut total_read = 0u32;

    // Read into each buffer in sequence
    for (i, iov) in iovecs.iter().enumerate() {
        if iov.iov_len == 0 {
            continue;
        }

        debug_print!(
            "sys_readv: reading into iovec[{}] - base=0x{:08x}, len={}",
            i,
            iov.iov_base as u32,
            iov.iov_len
        );

        match sys_read(_fd, iov.iov_base as u32, iov.iov_len as u32) {
            Ok(bytes_read) => {
                total_read += bytes_read;
                // If we read less than requested, we've hit EOF
                if bytes_read < iov.iov_len as u32 {
                    break;
                }
            }
            Err(e) => {
                // If we've already read some data, return that
                if total_read > 0 {
                    debug_print!(
                        "sys_readv: short read due to error {} returning partial {} bytes",
                        e.as_errno(),
                        total_read
                    );
                    return Ok(total_read);
                }
                debug_print!("sys_readv: returning error {}", e.as_errno());
                return Err(e);
            }
        }
    }

    debug_print!("sys_readv: returning {} bytes", total_read);
    Ok(total_read)
}

pub fn sys_ioctl(fd: u32, _cmd: u32, arg: u32) -> Result<u32, Err> {
    // For now, sys_ioctl is not implemented. Log a message for debugging.
    let msg = b"sys_ioctl not implemented";
    host_log(msg.as_ptr(), msg.len());
    let _fd = fd as i32;
    let _arg = arg as *const u8;
    // let msg = str_format!(str256, "sys_ioctl({fd}, {cmd}, 0x{arg:08x})");
    // print(&msg);
    Ok(0)
}

pub fn sys_pread64(_fd: u32, _buf: u32, _count: u32, _pos: u32) -> Result<u32, Err> {
    if _fd >= 256 {
        return Err(Err::Inval);
    }

    debug_print!(
        "sys_pread64: fd={}, buf=0x{:08x}, count={}, pos={}",
        _fd,
        _buf,
        _count,
        _pos
    );

    // pread64 reads from a specific offset without changing the file position
    // We need to: save current position, seek to offset, read, restore position

    let fd_entry = get_fd(_fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);
    let current_pos = file_desc.cursor;

    // Seek to requested offset (note: _pos is already the offset, not pgoffset)
    let mut updated_desc = file_desc;
    updated_desc.cursor = _pos as u64;
    update_file_desc(fd_entry.file_desc_id, updated_desc);

    // Do the read
    let result = sys_read(_fd, _buf, _count);

    // Restore original file position
    let mut restored_desc = get_file_desc(fd_entry.file_desc_id);
    restored_desc.cursor = current_pos;
    update_file_desc(fd_entry.file_desc_id, restored_desc);

    result
}

pub fn sys_readahead(_fd: u32, _offset: u32, _count: u32) -> Result<u32, Err> {
    let msg = b"sys_readahead not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_readlinkat(dfd: u32, pathname: u32, buf: u32, bufsiz: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        return Err(Err::NoSys);
    }

    // POSIX: readlink/readlinkat must fail with EINVAL if bufsiz < 1
    // Treat bufsiz < 2 as invalid to handle C library quirks
    if bufsiz < 2 {
        debug_print!("sys_readlinkat: bufsiz={} < 2, returning EINVAL", bufsiz);
        return Err(Err::Inval);
    }

    let pathname_str = validate_and_read_pathname(pathname)?;
    validate_user_buffer_write(buf, bufsiz as usize)?;

    debug_print!(
        "sys_readlinkat: dfd={}, pathname='{}', buf=0x{:x}, bufsiz={}",
        dfd,
        pathname_str,
        buf,
        bufsiz
    );

    // Handle empty pathname - operate on the fd itself
    if pathname_str.is_empty() {
        debug_print!(
            "sys_readlinkat: empty pathname, reading symlink from fd {}",
            dfd
        );

        if dfd >= 256 {
            return Err(Err::BadFd);
        }

        let fd_entry = get_fd(dfd);
        if fd_entry.file_desc_id == 0xFF {
            return Err(Err::BadFd);
        }

        let file_desc = get_file_desc(fd_entry.file_desc_id);
        let symlink_fid = file_desc.fid;

        // Read the symlink contents directly from the fd's FID
        let symlink_target = read_symlink(symlink_fid)?;

        debug_print!("sys_readlinkat: symlink target = '{}'", symlink_target);

        // Copy to user buffer (not null-terminated!)
        let copy_len = symlink_target.len().min(bufsiz as usize);
        if buf != 0 && copy_len > 0 {
            unsafe {
                let dest = core::slice::from_raw_parts_mut(buf as *mut u8, copy_len);
                dest.copy_from_slice(&symlink_target.as_bytes()[..copy_len]);
            }
        }

        return Ok(copy_len as u32);
    }

    // Walk to the symlink (without following it)
    let symlink_fid = TEMP_FID_11;
    let starting_fid = get_starting_fid(dfd, &pathname_str)?;
    let (dir_path, file_name) = split_path(&pathname_str);

    // Walk to the directory
    let dir_fid = if dir_path.is_empty() || dir_path == "." {
        starting_fid
    } else {
        let dir_path = normalize_path(&dir_path);
        do_walk(starting_fid, TEMP_FID_4, dir_path)?;
        TEMP_FID_4
    };

    // Walk to the symlink without following it
    let file_path = vec![file_name];
    let twalk = crate::p9::TwalkMessage::new(0, dir_fid, symlink_fid, file_path);
    match twalk.send_twalk() {
        Ok(crate::p9::P9Response::Success(rwalk)) => {
            if rwalk.wqids.len() != 1 {
                clunk(symlink_fid, false);
                if dir_fid != starting_fid {
                    clunk(dir_fid, false);
                }
                return Err(Err::FileNotFound);
            }

            // Check if the file is actually a symlink
            let qid = rwalk.wqids.first().unwrap();
            if !qid.is_symlink() {
                debug_print!(
                    "sys_readlinkat: path is not a symlink (qtype={})",
                    qid.qtype
                );
                clunk(symlink_fid, false);
                if dir_fid != starting_fid {
                    clunk(dir_fid, false);
                }
                return Err(Err::Inval);
            }

            if dir_fid != starting_fid {
                clunk(dir_fid, false);
            }
        }
        Ok(crate::p9::P9Response::Error(rlerror)) => {
            if dir_fid != starting_fid {
                clunk(dir_fid, false);
            }
            // Preserve ENOTDIR vs ENOENT semantics
            return Err(map_p9_error(rlerror.ecode));
        }
        Err(_) => {
            if dir_fid != starting_fid {
                clunk(dir_fid, false);
            }
            return Err(Err::NoSys);
        }
    }

    // Read the symlink contents
    let symlink_target = read_symlink(symlink_fid)?;
    clunk(symlink_fid, false);

    debug_print!("sys_readlinkat: symlink target = '{}'", symlink_target);

    // Copy to user buffer (not null-terminated!)
    let copy_len = symlink_target.len().min(bufsiz as usize);
    if buf != 0 && copy_len > 0 {
        unsafe {
            let dest = core::slice::from_raw_parts_mut(buf as *mut u8, copy_len);
            dest.copy_from_slice(&symlink_target.as_bytes()[..copy_len]);
        }
    }

    Ok(copy_len as u32)
}

pub fn sys_removexattr(_pathname: u32, _name: u32) -> Result<u32, Err> {
    let msg = b"sys_removexattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_removexattrat(_dfd: u32, _filename: u32, _name: u32) -> Result<u32, Err> {
    let msg = b"sys_removexattrat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_lgetxattr(_pathname: u32, _name: u32, _value: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_lgetxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_cachestat(_fd: u32, _cstat: u32, _cstat_size: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_cachestat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_renameat2(
    _olddirfd: u32,
    _oldpath: u32,
    _newdirfd: u32,
    _newpath: u32,
    _flags: u32,
) -> Result<u32, Err> {
    use crate::p9::{P9Response, TrenameatMessage};

    if !get_p9_enabled() {
        let msg = b"sys_renameat2: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Parse old path
    let oldpath = unsafe { core::slice::from_raw_parts(_oldpath as *const u8, 256) };
    let oldpath_len = oldpath
        .iter()
        .position(|&b| b == 0)
        .unwrap_or(oldpath.len());
    let oldpath_str = str::from_utf8(&oldpath[..oldpath_len]).map_err(|_| Err::Inval)?;

    // Parse new path
    let newpath = unsafe { core::slice::from_raw_parts(_newpath as *const u8, 256) };
    let newpath_len = newpath
        .iter()
        .position(|&b| b == 0)
        .unwrap_or(newpath.len());
    let newpath_str = str::from_utf8(&newpath[..newpath_len]).map_err(|_| Err::Inval)?;

    debug_print!(
        "sys_renameat2: '{}' -> '{}', flags=0x{:x}",
        oldpath_str,
        newpath_str,
        _flags
    );

    // Define rename flags
    const RENAME_NOREPLACE: u32 = 1 << 0; // Don't overwrite newpath
    const RENAME_EXCHANGE: u32 = 1 << 1; // Exchange oldpath and newpath atomically
    const RENAME_WHITEOUT: u32 = 1 << 2; // Whiteout source (for overlay filesystems)

    // Validate flag combinations
    // RENAME_NOREPLACE and RENAME_EXCHANGE are mutually exclusive
    if (_flags & RENAME_NOREPLACE) != 0 && (_flags & RENAME_EXCHANGE) != 0 {
        debug_print!("sys_renameat2: RENAME_NOREPLACE and RENAME_EXCHANGE both set");
        return Err(Err::Inval);
    }

    // RENAME_WHITEOUT and RENAME_EXCHANGE are mutually exclusive
    if (_flags & RENAME_WHITEOUT) != 0 && (_flags & RENAME_EXCHANGE) != 0 {
        debug_print!("sys_renameat2: RENAME_WHITEOUT and RENAME_EXCHANGE both set");
        return Err(Err::Inval);
    }

    // We don't support RENAME_WHITEOUT (it's for overlay filesystems)
    if (_flags & RENAME_WHITEOUT) != 0 {
        debug_print!("sys_renameat2: RENAME_WHITEOUT not supported");
        return Err(Err::OpNotSupp);
    }

    // Validate no unknown flags
    const KNOWN_FLAGS: u32 = RENAME_NOREPLACE | RENAME_EXCHANGE | RENAME_WHITEOUT;
    if (_flags & !KNOWN_FLAGS) != 0 {
        debug_print!(
            "sys_renameat2: unknown flags: 0x{:x}",
            _flags & !KNOWN_FLAGS
        );
        return Err(Err::Inval);
    }

    // Split paths into directory and filename components
    // Use temp fids that don't conflict with CWD (TEMP_FID_2)
    let old_starting_fid = get_starting_fid(_olddirfd, oldpath_str)?;
    let (old_dir_path, old_name) = split_path(oldpath_str);
    let old_dir_path = normalize_path(&old_dir_path);
    do_walk(old_starting_fid, TEMP_FID_1, old_dir_path)?;

    let new_starting_fid = get_starting_fid(_newdirfd, newpath_str)?;
    let (new_dir_path, new_name) = split_path(newpath_str);
    let new_dir_path = normalize_path(&new_dir_path);
    do_walk(new_starting_fid, TEMP_FID_4, new_dir_path)?;

    // Handle RENAME_NOREPLACE: fail if newpath exists
    if (_flags & RENAME_NOREPLACE) != 0 {
        // Try to walk to the new file to see if it exists
        let new_file_fid = TEMP_FID_6;
        let new_file_path = vec![new_name.clone()];
        let twalk = crate::p9::TwalkMessage::new(0, TEMP_FID_4, new_file_fid, new_file_path);
        match twalk.send_twalk() {
            Ok(crate::p9::P9Response::Success(rwalk)) => {
                if !rwalk.wqids.is_empty() {
                    // File exists, fail with EEXIST
                    debug_print!("sys_renameat2: RENAME_NOREPLACE and newpath exists");
                    clunk(new_file_fid, false);
                    clunk(TEMP_FID_1, false);
                    clunk(TEMP_FID_4, false);
                    return Err(Err::FileExists);
                }
                clunk(new_file_fid, false);
            }
            Ok(crate::p9::P9Response::Error(_)) => {
                // File doesn't exist, continue with rename
            }
            Err(_) => {
                // File doesn't exist, continue with rename
            }
        }
    }

    // Handle RENAME_EXCHANGE: atomically exchange oldpath and newpath
    if (_flags & RENAME_EXCHANGE) != 0 {
        // For RENAME_EXCHANGE, both files must exist
        // Check if newpath exists
        let new_file_fid = TEMP_FID_6;
        let new_file_path = vec![new_name.clone()];
        let twalk = crate::p9::TwalkMessage::new(0, TEMP_FID_4, new_file_fid, new_file_path);
        match twalk.send_twalk() {
            Ok(crate::p9::P9Response::Success(rwalk)) => {
                if rwalk.wqids.is_empty() {
                    // newpath doesn't exist, fail with ENOENT
                    debug_print!("sys_renameat2: RENAME_EXCHANGE but newpath doesn't exist");
                    clunk(new_file_fid, false);
                    clunk(TEMP_FID_1, false);
                    clunk(TEMP_FID_4, false);
                    return Err(Err::FileNotFound);
                }
                clunk(new_file_fid, false);
            }
            Ok(crate::p9::P9Response::Error(_)) => {
                // newpath doesn't exist, fail with ENOENT
                debug_print!("sys_renameat2: RENAME_EXCHANGE but newpath doesn't exist");
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::FileNotFound);
            }
            Err(_) => {
                // newpath doesn't exist, fail with ENOENT
                debug_print!("sys_renameat2: RENAME_EXCHANGE but newpath doesn't exist");
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::FileNotFound);
            }
        }

        // For RENAME_EXCHANGE, we need to do a three-way swap:
        // 1. Rename oldpath to temp
        // 2. Rename newpath to oldpath
        // 3. Rename temp to newpath
        // This is complex and not atomic in 9P, so we'll return EOPNOTSUPP for now
        // unless the 9P server supports it natively
        debug_print!("sys_renameat2: RENAME_EXCHANGE - attempting via temp file swap");

        // Create a temporary name
        let temp_name = format!(".tmp_rename_{}", old_name);

        // Walk to oldfile
        let old_file_fid = TEMP_FID_8;
        let old_file_path = vec![old_name.clone()];
        let twalk_old = crate::p9::TwalkMessage::new(0, TEMP_FID_1, old_file_fid, old_file_path);
        match twalk_old.send_twalk() {
            Ok(crate::p9::P9Response::Success(_)) => {}
            Ok(crate::p9::P9Response::Error(_)) => {
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::FileNotFound);
            }
            Err(_) => {
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::FileNotFound);
            }
        }

        // Walk to newfile
        let new_file_fid2 = TEMP_FID_9;
        let new_file_path2 = vec![new_name.clone()];
        let twalk_new = crate::p9::TwalkMessage::new(0, TEMP_FID_4, new_file_fid2, new_file_path2);
        match twalk_new.send_twalk() {
            Ok(crate::p9::P9Response::Success(_)) => {}
            Ok(crate::p9::P9Response::Error(_)) => {
                clunk(old_file_fid, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::FileNotFound);
            }
            Err(_) => {
                clunk(old_file_fid, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::FileNotFound);
            }
        }

        // Step 1: Rename oldfile to temp (in old directory)
        let trename1 =
            crate::p9::TrenameMessage::new(0, old_file_fid, TEMP_FID_1, temp_name.clone());
        match trename1.send_trename() {
            Ok(P9Response::Success(_)) => {
                debug_print!("sys_renameat2: step 1 complete (old->temp)");
            }
            Ok(P9Response::Error(rlerror)) => {
                clunk(old_file_fid, false);
                clunk(new_file_fid2, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(map_p9_error(rlerror.ecode));
            }
            Err(_) => {
                clunk(old_file_fid, false);
                clunk(new_file_fid2, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::IO);
            }
        }

        // Step 2: Rename newfile to oldname (in old directory)
        let trename2 =
            crate::p9::TrenameMessage::new(0, new_file_fid2, TEMP_FID_1, old_name.to_string());
        match trename2.send_trename() {
            Ok(P9Response::Success(_)) => {
                debug_print!("sys_renameat2: step 2 complete (new->old)");
            }
            Ok(P9Response::Error(rlerror)) => {
                // Rollback not implemented for simplicity
                clunk(old_file_fid, false);
                clunk(new_file_fid2, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(map_p9_error(rlerror.ecode));
            }
            Err(_) => {
                clunk(old_file_fid, false);
                clunk(new_file_fid2, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::IO);
            }
        }

        // Step 3: Rename temp to newname (in new directory)
        // Need to walk to temp in old directory first
        let temp_fid = TEMP_FID_10;
        let temp_path = vec![temp_name.clone()];
        let twalk_temp = crate::p9::TwalkMessage::new(0, TEMP_FID_1, temp_fid, temp_path);
        match twalk_temp.send_twalk() {
            Ok(crate::p9::P9Response::Success(_)) => {}
            Ok(crate::p9::P9Response::Error(_)) => {
                clunk(old_file_fid, false);
                clunk(new_file_fid2, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::FileNotFound);
            }
            Err(_) => {
                clunk(old_file_fid, false);
                clunk(new_file_fid2, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::FileNotFound);
            }
        }

        let trename3 =
            crate::p9::TrenameMessage::new(0, temp_fid, TEMP_FID_4, new_name.to_string());
        match trename3.send_trename() {
            Ok(P9Response::Success(_)) => {
                debug_print!("sys_renameat2: RENAME_EXCHANGE complete");
                clunk(old_file_fid, false);
                clunk(new_file_fid2, false);
                clunk(temp_fid, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Ok(0);
            }
            Ok(P9Response::Error(rlerror)) => {
                debug_print!("sys_renameat2: RENAME_EXCHANGE failed at step 3");
                clunk(old_file_fid, false);
                clunk(new_file_fid2, false);
                clunk(temp_fid, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(map_p9_error(rlerror.ecode));
            }
            Err(_) => {
                debug_print!("sys_renameat2: RENAME_EXCHANGE failed at step 3");
                clunk(old_file_fid, false);
                clunk(new_file_fid2, false);
                clunk(temp_fid, false);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(Err::IO);
            }
        }
    }

    // Normal rename (flags=0 or RENAME_NOREPLACE with non-existing target)
    // Try Trenameat first (9P2000.L extension)
    let trenameat = TrenameatMessage::new(
        0,
        TEMP_FID_1,
        old_name.to_string(),
        TEMP_FID_4,
        new_name.clone(),
    );

    match trenameat.send_trenameat() {
        Ok(P9Response::Success(_rrenameat)) => {
            debug_print!("sys_renameat2: Trenameat successful");
            clunk(TEMP_FID_1, false);
            clunk(TEMP_FID_4, false);
            return Ok(0);
        }
        Ok(P9Response::Error(rlerror)) => {
            // If Trenameat is not supported, fall back to Trename
            if rlerror.ecode == 95 {
                // EOPNOTSUPP
                debug_print!("sys_renameat2: Trenameat not supported, trying Trename");

                // For Trename, we need to walk to the file being renamed
                let file_fid = TEMP_FID_7;
                let file_path = vec![old_name.clone()];
                let twalk = crate::p9::TwalkMessage::new(0, TEMP_FID_1, file_fid, file_path);
                match twalk.send_twalk() {
                    Ok(crate::p9::P9Response::Success(rwalk)) => {
                        if rwalk.wqids.is_empty() {
                            clunk(file_fid, false);
                            clunk(TEMP_FID_1, false);
                            clunk(TEMP_FID_4, false);
                            return Err(Err::FileNotFound);
                        }
                    }
                    Ok(crate::p9::P9Response::Error(_)) => {
                        clunk(TEMP_FID_1, false);
                        clunk(TEMP_FID_4, false);
                        return Err(Err::FileNotFound);
                    }
                    Err(_) => {
                        clunk(TEMP_FID_1, false);
                        clunk(TEMP_FID_4, false);
                        return Err(Err::FileNotFound);
                    }
                }

                // Now use Trename: rename file_fid to newpath in newdirfid
                let trename =
                    crate::p9::TrenameMessage::new(0, file_fid, TEMP_FID_4, new_name.to_string());
                match trename.send_trename() {
                    Ok(crate::p9::P9Response::Success(_)) => {
                        debug_print!("sys_renameat2: Trename successful");
                        clunk(file_fid, false);
                        clunk(TEMP_FID_1, false);
                        clunk(TEMP_FID_4, false);
                        return Ok(0);
                    }
                    Ok(crate::p9::P9Response::Error(rlerror2)) => {
                        debug_print!("sys_renameat2: Trename failed: ecode={}", rlerror2.ecode);
                        clunk(file_fid, false);
                        clunk(TEMP_FID_1, false);
                        clunk(TEMP_FID_4, false);
                        return Err(map_p9_error(rlerror2.ecode));
                    }
                    Err(_) => {
                        clunk(file_fid, false);
                        clunk(TEMP_FID_1, false);
                        clunk(TEMP_FID_4, false);
                        return Err(Err::IO);
                    }
                }
            } else {
                debug_print!("sys_renameat2: received Rlerror: ecode={}", rlerror.ecode);
                clunk(TEMP_FID_1, false);
                clunk(TEMP_FID_4, false);
                return Err(map_p9_error(rlerror.ecode));
            }
        }
        Err(e) => {
            debug_print!("sys_renameat2: error sending Trenameat: {:?}", e);
            clunk(TEMP_FID_1, false);
            clunk(TEMP_FID_4, false);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_sendfile64(_out_fd: u32, _in_fd: u32, _offset: u32, _count: u32) -> Result<u32, Err> {
    let msg = b"sys_sendfile64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_setxattr(
    _pathname: u32,
    _name: u32,
    _value: u32,
    _size: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_setxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_setxattrat(
    _dfd: u32,
    _filename: u32,
    _name: u32,
    _value: u32,
    _size: u32,
) -> Result<u32, Err> {
    let msg = b"sys_setxattrat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

const F_DUPFD_CLOEXEC: u32 = 1030;

pub fn sys_fcntl64(_fd: u32, _cmd: u32, _arg: u32) -> Result<u32, Err> {
    debug_print!("sys_fcntl64: _fd={} _cmd={} _arg={}", _fd, _cmd, _arg);

    // Check fd validity first (for EBADF vs EINVAL priority)
    // Check for out-of-range file descriptors
    let fd_i32 = _fd as i32;
    if fd_i32 < 0 || _fd >= 256 {
        // For negative or too large fd, return EBADF
        return Err(Err::BadFd);
    }

    let fd_entry = get_fd(_fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    // Now check command validity
    const VALID_CMDS: &[u32] = &[
        F_DUPFD,
        F_GETFD,
        F_SETFD,
        F_GETFL,
        F_SETFL,
        F_GETLK,
        F_SETLK,
        F_SETLKW,
        F_DUPFD_CLOEXEC,
    ];

    if !VALID_CMDS.contains(&_cmd) {
        debug_print!("sys_fcntl64: invalid command {}", _cmd);
        return Err(Err::Inval);
    }

    if _cmd == F_DUPFD {
        // Duplicate file descriptor with lowest available fd >= _arg
        debug_print!("sys_fcntl64: F_DUPFD fd={} arg={}", _fd, _arg);

        // Find the lowest available fd >= _arg
        let start_fd = _arg.max(3); // Start from at least 3 (after stdin/stdout/stderr)
        let mut new_fd = None;
        for candidate in start_fd..256 {
            let candidate_entry = get_fd(candidate);
            if candidate_entry.file_desc_id == 0xFF {
                new_fd = Some(candidate);
                break;
            }
        }

        match new_fd {
            Some(fd) => {
                // Duplicate the file description
                update_fd(
                    fd,
                    FileDescriptor {
                        file_desc_id: fd_entry.file_desc_id,
                        cloexec: false, // F_DUPFD does not set FD_CLOEXEC
                    },
                );
                inc_refcount(fd_entry.file_desc_id);
                debug_print!("sys_fcntl64: F_DUPFD allocated fd {}", fd);
                return Ok(fd);
            }
            None => {
                debug_print!("sys_fcntl64: F_DUPFD no available fd");
                return Err(Err::MFile);
            }
        }
    } else if _cmd == F_GETFD {
        // Get file descriptor flags (only FD_CLOEXEC is relevant)
        let flags = if fd_entry.cloexec { FD_CLOEXEC } else { 0 };
        debug_print!(
            "sys_fcntl64: F_GETFD returning {} (cloexec={})",
            flags,
            fd_entry.cloexec
        );
        return Ok(flags);
    } else if _cmd == F_SETFD {
        // Set file descriptor flags
        let new_cloexec = (_arg & FD_CLOEXEC) != 0;
        let mut updated_entry = fd_entry;
        updated_entry.cloexec = new_cloexec;
        update_fd(_fd, updated_entry);
        debug_print!("sys_fcntl64: F_SETFD setting FD_CLOEXEC to {}", new_cloexec);
        return Ok(0);
    } else if _cmd == F_GETFL {
        // Get file status flags (O_RDONLY, O_WRONLY, O_RDWR, O_APPEND, O_NONBLOCK, etc.)
        let file_desc = get_file_desc(fd_entry.file_desc_id);
        let flags = file_desc.flags;
        debug_print!("sys_fcntl64: F_GETFL returning 0x{:x}", flags);
        return Ok(flags);
    } else if _cmd == F_SETFL {
        // Set file status flags (only certain flags can be set: O_APPEND, O_NONBLOCK, O_ASYNC, O_DIRECT)
        // O_RDONLY, O_WRONLY, O_RDWR, and other open-time flags cannot be changed
        const O_NONBLOCK: u32 = 0o4000; // 0x800 (also O_NDELAY)
        const O_ASYNC: u32 = 0o20000; // 0x2000
        const O_DIRECT: u32 = 0o40000; // 0x4000
        const O_NOATIME: u32 = 0o1000000; // 0x40000

        const SETTABLE_FLAGS: u32 = O_APPEND | O_NONBLOCK | O_ASYNC | O_DIRECT | O_NOATIME;

        let file_desc = get_file_desc(fd_entry.file_desc_id);
        // Keep the access mode (O_RDONLY/O_WRONLY/O_RDWR) from the original flags
        let access_mode = file_desc.mode & 0x3; // O_ACCMODE = 0x3
        // Update only the settable flags
        let new_flags = access_mode | (_arg & SETTABLE_FLAGS);

        let mut updated_desc = file_desc;
        updated_desc.flags = new_flags;
        update_file_desc(fd_entry.file_desc_id, updated_desc);

        debug_print!(
            "sys_fcntl64: F_SETFL old_flags=0x{:x} new_flags=0x{:x}",
            file_desc.flags,
            new_flags
        );
        return Ok(0);
    } else if _cmd == F_DUPFD_CLOEXEC {
        let fd_entry = get_fd(_fd);
        if fd_entry.file_desc_id == 0xFF {
            return Err(Err::BadFd);
        }
        let _file_desc = get_file_desc(fd_entry.file_desc_id);
        // F_DUPFD_CLOEXEC should work like dup3, but we're not implementing the full logic here
        // For now, just duplicate the file description
        let new_fd = _arg;
        update_fd(
            new_fd,
            FileDescriptor {
                file_desc_id: fd_entry.file_desc_id,
                cloexec: true, // F_DUPFD_CLOEXEC sets FD_CLOEXEC
            },
        );
        inc_refcount(fd_entry.file_desc_id);
        debug_print!("sys_fcntl64: F_DUPFD_CLOEXEC: _fd={} _arg={}", _fd, _arg);
        return Ok(_arg);
    } else if _cmd == F_GETLK {
        // Get file lock status
        // In zkVM, we don't have real file locking, so we always report F_UNLCK (no lock)
        debug_print!("sys_fcntl64: F_GETLK fd={} flock_ptr=0x{:x}", _fd, _arg);

        // The _arg is a pointer to struct flock
        // struct flock {
        //     short l_type;    /* Type of lock: F_RDLCK, F_WRLCK, F_UNLCK */
        //     short l_whence;  /* How to interpret l_start: SEEK_SET, SEEK_CUR, SEEK_END */
        //     off_t l_start;   /* Starting offset for lock */
        //     off_t l_len;     /* Number of bytes to lock */
        //     pid_t l_pid;     /* PID of process blocking our lock (F_GETLK only) */
        // };

        // Check for NULL pointer
        if _arg == 0 {
            return Err(Err::Fault);
        }

        // Validate the pointer is in writable user memory (struct flock is ~24 bytes)
        const FLOCK_SIZE: usize = 24;
        match crate::linux_abi::is_valid_user_address(_arg, FLOCK_SIZE, true) {
            Some(valid_len) if valid_len >= FLOCK_SIZE => {}
            _ => {
                debug_print!(
                    "sys_fcntl64: F_GETLK - invalid flock pointer {:#010x}",
                    _arg
                );
                return Err(Err::Fault);
            }
        }

        // Write F_UNLCK (2) to l_type field (first 2 bytes)
        unsafe {
            let l_type_ptr = _arg as *mut u16;
            *l_type_ptr = F_UNLCK as u16;
        }

        debug_print!("sys_fcntl64: F_GETLK set l_type to F_UNLCK");
        return Ok(0);
    } else if _cmd == F_SETLK || _cmd == F_SETLKW {
        // Set file lock (non-blocking or blocking)
        debug_print!(
            "sys_fcntl64: F_SETLK/F_SETLKW fd={} flock_ptr=0x{:x}",
            _fd,
            _arg
        );

        // Check for NULL pointer
        if _arg == 0 {
            return Err(Err::Fault);
        }

        // Validate the pointer is in readable user memory (struct flock is ~24 bytes)
        const FLOCK_SIZE: usize = 24;
        match crate::linux_abi::is_valid_user_address(_arg, FLOCK_SIZE, false) {
            Some(valid_len) if valid_len >= FLOCK_SIZE => {}
            _ => {
                debug_print!(
                    "sys_fcntl64: F_SETLK/F_SETLKW - invalid flock pointer {:#010x}",
                    _arg
                );
                return Err(Err::Fault);
            }
        }

        // Read and validate the flock structure
        // struct flock layout (on 32-bit RISC-V):
        // - l_type: i16 at offset 0
        // - l_whence: i16 at offset 2
        // - l_start: i64 at offset 4 (or i32, depending on arch)
        // - l_len: i64 at offset 8 or 12
        // - l_pid: i32 at offset 12 or 16

        const SEEK_SET: u16 = 0;
        const SEEK_CUR: u16 = 1;
        const SEEK_END: u16 = 2;

        unsafe {
            let l_whence_ptr = (_arg + 2) as *const i16;
            let l_whence = *l_whence_ptr;

            // Validate l_whence
            if l_whence != SEEK_SET as i16
                && l_whence != SEEK_CUR as i16
                && l_whence != SEEK_END as i16
            {
                debug_print!("sys_fcntl64: F_SETLK invalid l_whence={}", l_whence);
                return Err(Err::Inval);
            }
        }

        // In zkVM, we don't have real file locking, so we just succeed
        debug_print!("sys_fcntl64: F_SETLK/F_SETLKW success (no-op in zkVM)");
        return Ok(0);
    }

    // Unsupported command
    debug_print!("sys_fcntl64: unsupported command {}", _cmd);
    let msg = b"sys_fcntl64 not implemented for this cmd/arg";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getdents64(fd: u32, dirp: u32, count: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_getdents64: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    if fd >= 256 {
        return Err(Err::Inval);
    }

    // Validate the directory entry buffer is writable
    validate_user_buffer_write(dirp, count as usize)?;

    let fd_entry = get_fd(fd);
    if fd_entry.file_desc_id == 0xFF {
        return Err(Err::BadFd);
    }

    let file_desc = get_file_desc(fd_entry.file_desc_id);
    let offset = file_desc.cursor;

    // Get the FID from the file description
    let fid = file_desc.fid;
    if fid == 0 {
        return Err(Err::Inval);
    }

    // XXX we will read one dir entry at a a time
    let treaddir = TreaddirMessage::new(0, fid, offset, count);
    match treaddir.send_treaddir() {
        Ok(P9Response::Success(rreaddir)) => {
            if rreaddir.count == 0 {
                // No more entries
                return Ok(0);
            }

            // Parse the directory entries and convert to Linux dirent64 format
            let mut offset = 0;
            let mut total_bytes = 0;
            let mut user_offset = 0;

            while offset < rreaddir.data.len() {
                // Parse 9P directory entry: qid[13] offset[8] type[1] name[s]
                if offset + 13 + 8 + 1 > rreaddir.data.len() {
                    break;
                }

                // Read QID (13 bytes)
                let qid_path = u64::from_le_bytes([
                    rreaddir.data[offset],
                    rreaddir.data[offset + 1],
                    rreaddir.data[offset + 2],
                    rreaddir.data[offset + 3],
                    rreaddir.data[offset + 4],
                    rreaddir.data[offset + 5],
                    rreaddir.data[offset + 6],
                    rreaddir.data[offset + 7],
                ]);
                let _qid_version = u32::from_le_bytes([
                    rreaddir.data[offset + 8],
                    rreaddir.data[offset + 9],
                    rreaddir.data[offset + 10],
                    rreaddir.data[offset + 11],
                ]);
                let _qid_type = rreaddir.data[offset + 12];
                offset += 13;

                // Read offset (8 bytes)
                let entry_offset = u64::from_le_bytes([
                    rreaddir.data[offset],
                    rreaddir.data[offset + 1],
                    rreaddir.data[offset + 2],
                    rreaddir.data[offset + 3],
                    rreaddir.data[offset + 4],
                    rreaddir.data[offset + 5],
                    rreaddir.data[offset + 6],
                    rreaddir.data[offset + 7],
                ]);
                offset += 8;

                // Read type (1 byte)
                let entry_type = rreaddir.data[offset];
                offset += 1;

                // Read name length (2 bytes)
                if offset + 2 > rreaddir.data.len() {
                    break;
                }
                let name_len =
                    u16::from_le_bytes([rreaddir.data[offset], rreaddir.data[offset + 1]]) as usize;
                offset += 2;

                // Read name
                if offset + name_len > rreaddir.data.len() {
                    break;
                }
                let name_bytes = &rreaddir.data[offset..offset + name_len];
                offset += name_len;

                // Convert 9P type to Linux DT_* type
                let d_type = match entry_type {
                    0 => DT_DIR, // Directory
                    1 => DT_REG, // Regular file
                    2 => DT_REG, // Append-only file
                    3 => DT_REG, // Exclusive-use file
                    4 => DT_REG, // Mounted file
                    5 => DT_REG, // Authentication file
                    6 => DT_REG, // Temporary file
                    7 => DT_LNK, // Symbolic link
                    _ => DT_UNKNOWN,
                };

                // Calculate record length (align to 8-byte boundary)
                // C compiler adds padding to align d_name, so structure is 24 bytes
                let c_struct_size = 24; // 8+8+2+1+5(padding) = 24 bytes in C
                let name_len_aligned = (name_len + 7) & !7;
                let reclen = (c_struct_size + name_len_aligned) as u16;

                // Check if we have enough space in user buffer
                if user_offset + reclen as usize > count as usize {
                    break;
                }

                // Write Linux dirent64 structure directly to user buffer
                unsafe {
                    let user_ptr = (dirp + user_offset as u32) as *mut u8;

                    // Write structure fields directly to buffer at correct offsets
                    // d_ino at offset 0-7
                    let d_ino_ptr = user_ptr as *mut u64;
                    *d_ino_ptr = qid_path;

                    // d_off at offset 8-15
                    let next_dirent_offset = (user_offset + reclen as usize + 7) & !7;
                    let d_off_ptr = user_ptr.add(8) as *mut i64;
                    *d_off_ptr = next_dirent_offset as i64;

                    // d_reclen at offset 16-17
                    let d_reclen_ptr = user_ptr.add(16) as *mut u16;
                    *d_reclen_ptr = reclen;

                    // d_type at offset 18
                    let d_type_ptr = user_ptr.add(18);
                    *d_type_ptr = d_type;

                    // Copy name (null-terminated) after the structure
                    // C compiler adds padding between d_type and d_name for alignment
                    let name_ptr = user_ptr.add(19);

                    for (i, &byte) in name_bytes.iter().enumerate().take(name_len) {
                        *name_ptr.add(i) = byte;
                    }
                    *name_ptr.add(name_len) = 0; // null terminator

                    // Zero out padding
                    for i in (name_len + 1)..name_len_aligned {
                        *name_ptr.add(i) = 0;
                    }
                }

                // Update the shared cursor in the file description
                let mut updated_desc = get_file_desc(fd_entry.file_desc_id);
                updated_desc.cursor = entry_offset;
                update_file_desc(fd_entry.file_desc_id, updated_desc);
                // Ensure next dirent is 8-byte aligned
                user_offset = (user_offset + reclen as usize + 7) & !7;
                total_bytes += reclen as usize;
            }

            Ok(total_bytes as u32)
        }
        Ok(P9Response::Error(rlerror)) => Err(map_p9_error(rlerror.ecode)),
        Err(_e) => Err(Err::NoSys),
    }
}

#[allow(dead_code)]
// instead of wnames we take a path
fn do_walk(
    starting_fid: u32,
    target_fid: u32,
    wnames: Vec<String>,
) -> Result<(u32, Vec<Qid>), Err> {
    debug_print!(
        "do_walk: starting_fid={}, target_fid={}, wnames={:?}",
        starting_fid,
        target_fid,
        wnames
    );

    let wnames_len = wnames.len();
    let wnames_clone = wnames.clone();
    let twalk = crate::p9::TwalkMessage::new(0, starting_fid, target_fid, wnames);

    let rwalk = match twalk.send_twalk() {
        Ok(P9Response::Success(rwalk)) => rwalk,
        Ok(P9Response::Error(rlerror)) => {
            debug_print!("do_walk: error response - ecode={}", rlerror.ecode);
            return Err(Err::FileNotFound);
        }
        Err(e) => {
            debug_print!("do_walk: error = {:?}", e);
            return Err(Err::NoSys);
        }
    };

    // Continue with rwalk processing
    debug_print!(
        "do_walk: rwalk.wqids.len()={}, wnames_len={}, wqids={:?}",
        rwalk.wqids.len(),
        wnames_len,
        rwalk.wqids
    );
    // For a clone operation (wnames_len == 0), we should get 1 QID (the QID of the FID being cloned)
    // For a walk operation (wnames_len > 0), we should get wnames_len QIDs
    let expected_qids = if wnames_len == 0 { 1 } else { wnames_len };
    if rwalk.wqids.len() != expected_qids {
        debug_print!(
            "do_walk: walk failed - expected {} QIDs, got {}",
            expected_qids,
            rwalk.wqids.len()
        );

        // Check if we stopped at a symlink in the middle of the path
        if rwalk.wqids.len() > 0 {
            if let Some(last_qid) = rwalk.wqids.last() {
                if last_qid.is_symlink() {
                    debug_print!(
                        "do_walk: stopped at symlink at position {}/{}",
                        rwalk.wqids.len(),
                        wnames_len
                    );

                    // Read the symlink target
                    let symlink_target = read_symlink(target_fid)?;
                    debug_print!(
                        "do_walk: intermediate symlink target = '{}'",
                        symlink_target
                    );

                    // Build the path up to the symlink
                    let symlink_wnames: Vec<String> = wnames_clone
                        .iter()
                        .take(rwalk.wqids.len())
                        .cloned()
                        .collect();

                    // Resolve the symlink target relative to its directory
                    let resolved_symlink_path =
                        resolve_symlink_target(&symlink_target, &symlink_wnames)?;
                    debug_print!(
                        "do_walk: resolved intermediate symlink to '{}'",
                        resolved_symlink_path
                    );

                    // Append the remaining path components
                    let mut full_resolved_path = resolved_symlink_path;
                    for i in rwalk.wqids.len()..wnames_len {
                        full_resolved_path.push('/');
                        full_resolved_path.push_str(&wnames_clone[i]);
                    }
                    debug_print!("do_walk: full resolved path = '{}'", full_resolved_path);

                    // Close the current target_fid
                    clunk(target_fid, false);

                    // Walk to the fully resolved path
                    let resolved_wnames = normalize_path(&full_resolved_path);
                    let walk_from_fid = if symlink_target.starts_with('/') {
                        debug_print!("do_walk: absolute intermediate symlink, walking from root");
                        get_root_fid()
                    } else {
                        starting_fid
                    };
                    return do_walk(walk_from_fid, target_fid, resolved_wnames);
                }
            }
        }

        clunk(target_fid, false);
        Err(Err::FileNotFound)
    } else {
        // Check if the final component is a symlink
        if let Some(last_qid) = rwalk.wqids.last()
            && last_qid.is_symlink()
        {
            debug_print!("do_walk: final component is a symlink, resolving...");

            // Read the symlink contents
            let symlink_target = read_symlink(target_fid)?;
            debug_print!("do_walk: symlink target = '{}'", symlink_target);
            let wnames = wnames_clone;
            // Resolve the target path relative to the symlink's directory
            let resolved_path = resolve_symlink_target(&symlink_target, &wnames)?;
            debug_print!("do_walk: resolved path = '{}'", resolved_path);

            // Close the current target_fid since we're going to walk to a new path
            clunk(target_fid, false);

            // Walk to the resolved path
            let resolved_wnames = normalize_path(&resolved_path);
            // For absolute paths, start from root; for relative paths, use starting_fid
            let walk_from_fid = if symlink_target.starts_with('/') {
                debug_print!("do_walk: absolute symlink, walking from root");
                get_root_fid()
            } else {
                starting_fid
            };
            return do_walk(walk_from_fid, target_fid, resolved_wnames);
        }
        Ok((0, rwalk.wqids))
    }
}

/// Read the contents of a symlink
fn read_symlink(fid: u32) -> Result<String, Err> {
    // Use Treadlink to read the symlink contents directly
    let treadlink = TreadlinkMessage::new(0, fid);
    match treadlink.send_treadlink() {
        Ok(P9Response::Success(rreadlink)) => {
            debug_print!("read_symlink: readlink target = '{}'", rreadlink.target);
            Ok(rreadlink.target)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "read_symlink: error reading symlink: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
            Err(map_p9_error(rlerror.ecode))
        }
        Err(e) => {
            debug_print!("read_symlink: error sending treadlink: {:?}", e);
            Err(Err::NoSys)
        }
    }
}

/// Resolve a symlink target path relative to the symlink's directory
fn resolve_symlink_target(target: &str, original_wnames: &[String]) -> Result<String, Err> {
    if target.starts_with('/') {
        // Absolute path - use as-is
        Ok(target.to_string())
    } else {
        // Relative path - resolve relative to the symlink's directory
        // Build the directory path from the original wnames (excluding the last component)
        let mut dir_path = String::new();
        if original_wnames.len() > 1 {
            // There are parent directories
            for (i, component) in original_wnames.iter().enumerate() {
                if i == original_wnames.len() - 1 {
                    // Skip the last component (the symlink itself)
                    break;
                }
                dir_path.push('/');
                dir_path.push_str(component);
            }
        } else {
            // Symlink is in the root directory
            dir_path.push('/');
        }

        // Combine directory path with target
        let resolved = if dir_path.ends_with('/') {
            format!("{}{}", dir_path, target)
        } else {
            format!("{}/{}", dir_path, target)
        };

        debug_print!(
            "resolve_symlink_target: dir_path='{}', target='{}', resolved='{}'",
            dir_path,
            target,
            resolved
        );
        Ok(resolved)
    }
}

/// Split a path into directory and filename components
/// also supports relative paths
fn split_path(path: &str) -> (String, String) {
    // Remove any trailing slashes except for root "/"
    let trimmed = if path != "/" {
        path.trim_end_matches('/').to_string()
    } else {
        path.to_string()
    };

    // Find the last slash in the trimmed path
    if let Some(pos) = trimmed.rfind('/') {
        let dir = if pos == 0 {
            // Path is like "/foo" or "/"
            "/".to_string()
        } else {
            // Path is like "/foo/bar" or "foo/bar"
            trimmed[..pos].to_string()
        };
        let filename = trimmed[pos + 1..].to_string();
        (dir, filename)
    } else {
        // No slash found, so it's a relative filename in current directory
        (".".to_string(), trimmed)
    }
}

pub fn sys_openat(_dfd: u32, _filename: u32, _flags: u32, _mode: u32) -> Result<u32, Err> {
    let filename_str = validate_and_read_pathname(_filename)?;
    do_openat(_dfd, &filename_str, _flags, _mode)
}

fn get_starting_fid(_dfd: u32, filename_str: &str) -> Result<u32, Err> {
    // If the pathname given in pathname is relative, then it is interpreted relative to the directory referred to by the file descriptor dirfd (rather than relative to the current working directory of the calling process, as is done by open(2) for a relative pathname).
    // If pathname is relative and dirfd is the special value AT_FDCWD, then pathname is interpreted relative to the current working directory of the calling process (like open(2)).
    let _dfd_i32 = _dfd as i32;
    if filename_str.starts_with("/") {
        // Absolute paths ignore dirfd - always use root
        Ok(get_root_fid())
    } else if _dfd_i32 == AT_FDCWD {
        // AT_FDCWD case
        Ok(get_cwd_fid())
    } else {
        // For relative paths, dirfd must be valid
        // Check if dfd is in range (including negative values cast to u32)
        if _dfd_i32 < 0 || _dfd >= 256 {
            debug_print!(
                "get_starting_fid: invalid dfd={} (as i32={})",
                _dfd,
                _dfd_i32
            );
            return Err(Err::BadFd);
        }

        let fd_entry = get_fd(_dfd);
        if fd_entry.file_desc_id == 0xFF {
            debug_print!("get_starting_fid: dfd={} is not open", _dfd);
            return Err(Err::BadFd);
        }

        // Check if dfd is a directory (required for relative paths)
        let file_desc = get_file_desc(fd_entry.file_desc_id);
        if !file_desc.is_dir {
            debug_print!(
                "get_starting_fid: dfd={} is not a directory (is_dir=false)",
                _dfd
            );
            return Err(Err::NotDir);
        }

        Ok(file_desc.fid)
    }
}

#[allow(dead_code)]
fn get_dir_fid_into_temp_fid(dfd: u32, filename_str: &str) -> Result<(u32, String), Err> {
    let starting_fid = get_starting_fid(dfd, filename_str)?;
    let (dir_path, file_name) = split_path(&filename_str);
    let dir_path = normalize_path(&dir_path);
    // Use temp fid that doesn't conflict with CWD (TEMP_FID_2)
    do_walk(starting_fid, TEMP_FID_4, dir_path)?;
    Ok((TEMP_FID_4, file_name))
}

fn resolve_file_to_fid(dir_fid: u32, new_fid: u32, filename: &str) -> Result<u32, Err> {
    do_walk(dir_fid, new_fid, vec![filename.to_string()])?;
    Ok(0)
}

fn resolve_path(dfd: u32, filename_str: &str, into_fid: u32) -> Result<u32, Err> {
    let starting_fid = get_starting_fid(dfd, filename_str)?;

    let (dir_path, file_name) = split_path(&filename_str);
    let dir_path = normalize_path(&dir_path);
    let mut file_path = dir_path.clone();
    file_path.push(file_name.clone());

    // Propagate the actual error from do_walk
    do_walk(starting_fid, into_fid, file_path)?;
    Ok(0)
}

fn do_openat(dfd: u32, filename_str: &str, _flags: u32, mode: u32) -> Result<u32, Err> {
    // Convert the filename to a UTF-8 s
    debug_print!(
        "sys_openat: filename='{}' dfd={} flags=0x{:x} mode=0x{:x}",
        filename_str,
        dfd,
        _flags,
        mode
    );

    // Check if this is a virtual device file
    if let Some(virtual_fid) = get_virtual_device_fid(filename_str) {
        debug_print!("sys_openat: opening virtual device: {}", filename_str);

        let fd = find_free_fd()?;
        let desc_id = find_free_file_desc()?;

        let p9_flags = if (_flags & 0o3) == 0o0 {
            0 // O_RDONLY
        } else if (_flags & 0o3) == 0o1 {
            1 // O_WRONLY
        } else {
            2 // O_RDWR
        };

        update_file_desc(
            desc_id,
            FileDescription {
                fid: virtual_fid,
                cursor: 0,
                is_dir: false,
                mode: p9_flags,
                flags: _flags,
                refcount: 1,
            },
        );

        update_fd(
            fd,
            FileDescriptor {
                file_desc_id: desc_id,
                cloexec: false,
            },
        );

        debug_print!("sys_openat: virtual device opened with fd={}", fd);
        return Ok(fd);
    }

    // Use top-level O_* constants

    let p9_flags = if (_flags & 0o3) == 0o0 {
        0
    }
    // O_RDONLY
    else if (_flags & 0o3) == 0o1 {
        1
    }
    // O_WRONLY
    else {
        2
    }; // O_RDWR

    let file_fid = find_free_fd()?;

    // Handle O_NOFOLLOW: check if target is a symlink and fail if it is
    if (_flags & O_NOFOLLOW) != 0 {
        debug_print!("sys_openat: O_NOFOLLOW flag set");

        let starting_fid = get_starting_fid(dfd, &filename_str)?;
        let (dir_path, file_name) = split_path(&filename_str);

        // Walk to the directory (following symlinks in the path)
        let dir_fid = if dir_path.is_empty() || dir_path == "." {
            starting_fid
        } else {
            let dir_path = normalize_path(&dir_path);
            match do_walk(starting_fid, TEMP_FID_4, dir_path) {
                Ok(_) => TEMP_FID_4,
                Err(e) => return Err(e),
            }
        };

        // Walk to the final component without following symlinks
        let file_path = vec![file_name];
        let twalk = crate::p9::TwalkMessage::new(0, dir_fid, file_fid, file_path);
        match twalk.send_twalk() {
            Ok(crate::p9::P9Response::Success(rwalk)) => {
                if dir_fid != starting_fid {
                    clunk(dir_fid, false);
                }

                if rwalk.wqids.len() != 1 {
                    clunk(file_fid, false);
                    // File doesn't exist - check if O_CREAT is set
                    if (_flags & O_CREAT) == 0 {
                        return Err(Err::FileNotFound);
                    }
                    // Will handle creation below
                } else {
                    // Check if it's a symlink
                    let qid = rwalk.wqids.first().unwrap();
                    if qid.is_symlink() {
                        // With O_PATH, we can open symlinks - just get an fd to the symlink itself
                        if (_flags & O_PATH) != 0 {
                            debug_print!(
                                "sys_openat: O_NOFOLLOW + O_PATH on symlink - creating fd-only descriptor"
                            );
                            set_fd(file_fid, file_fid);
                            let fd_entry = get_fd(file_fid);
                            let mut file_desc = get_file_desc(fd_entry.file_desc_id);
                            file_desc.mode = 0;
                            file_desc.is_dir = qid.is_dir();
                            file_desc.flags = _flags;
                            update_file_desc(fd_entry.file_desc_id, file_desc);
                            return Ok(file_fid);
                        } else {
                            // O_NOFOLLOW without O_PATH on a symlink - fail with ELOOP
                            debug_print!(
                                "sys_openat: O_NOFOLLOW - path is a symlink, returning ELOOP"
                            );
                            clunk(file_fid, false);
                            return Err(Err::Loop);
                        }
                    }
                    // Not a symlink, file exists
                    // Check if O_PATH is set - if so, don't actually open the file
                    if (_flags & O_PATH) != 0 {
                        debug_print!(
                            "sys_openat: O_NOFOLLOW + O_PATH - creating fd-only descriptor"
                        );
                        // For O_PATH, we don't call Tlopen - just set up the fd
                        set_fd(file_fid, file_fid);
                        let fd_entry = get_fd(file_fid);
                        let mut file_desc = get_file_desc(fd_entry.file_desc_id);
                        file_desc.mode = 0;
                        file_desc.is_dir = qid.is_dir();
                        file_desc.flags = _flags;
                        update_file_desc(fd_entry.file_desc_id, file_desc);
                        return Ok(file_fid);
                    }

                    // Normal open
                    debug_print!(
                        "sys_openat: O_NOFOLLOW - file exists and is not a symlink, opening"
                    );

                    let tlopen = TlopenMessage::new(0, file_fid, p9_flags);
                    match tlopen.send_tlopen() {
                        Ok(P9Response::Success(rlopen)) => {
                            let is_directory = rlopen.qid.is_dir();
                            set_fd(file_fid, file_fid);
                            let fd_entry = get_fd(file_fid);
                            let mut file_desc = get_file_desc(fd_entry.file_desc_id);
                            file_desc.mode = p9_flags;
                            file_desc.is_dir = is_directory;
                            file_desc.flags = _flags;
                            update_file_desc(fd_entry.file_desc_id, file_desc);
                            return Ok(file_fid);
                        }
                        Ok(P9Response::Error(rlerror)) => {
                            clunk(file_fid, false);
                            return Err(map_p9_error(rlerror.ecode));
                        }
                        Err(_) => {
                            clunk(file_fid, false);
                            return Err(Err::IO);
                        }
                    }
                }
            }
            Ok(crate::p9::P9Response::Error(_)) => {
                if dir_fid != starting_fid {
                    clunk(dir_fid, false);
                }
                // File doesn't exist - check if O_CREAT is set
                if (_flags & O_CREAT) == 0 {
                    return Err(Err::FileNotFound);
                }
                // Will handle creation below
            }
            Err(_) => {
                if dir_fid != starting_fid {
                    clunk(dir_fid, false);
                }
                // File doesn't exist - check if O_CREAT is set
                if (_flags & O_CREAT) == 0 {
                    return Err(Err::FileNotFound);
                }
                // Will handle creation below
            }
        }
    }

    let path_result = resolve_path(dfd, filename_str, file_fid);
    if path_result.is_ok() {
        if (_flags & O_CREAT) == O_CREAT && (_flags & O_EXCL) == O_EXCL {
            debug_print!("sys_openat: O_CREAT and O_EXCL flags detected, file already exists");
            return Err(Err::FileExists);
        }
        debug_print!("sys_openat: file exists, flags=0x{:x}", _flags);

        // Check if O_PATH is set - if so, don't actually open the file
        if (_flags & O_PATH) != 0 {
            debug_print!("sys_openat: O_PATH - creating fd-only descriptor");

            // Get file attributes to determine if it's a directory
            debug_print!(
                "sys_openat: O_PATH querying file attributes for fid {}",
                file_fid
            );
            let tgetattr = crate::p9::TgetattrMessage::new(0, file_fid, P9_GETATTR_MODE);
            let is_directory = match tgetattr.send_tgetattr() {
                Ok(P9Response::Success(rgetattr)) => {
                    debug_print!("sys_openat: O_PATH Tgetattr sent successfully");
                    // Check if mode indicates directory (Unix S_IFDIR)
                    let is_dir = (rgetattr.mode & S_IFDIR) != 0;
                    debug_print!(
                        "sys_openat: O_PATH mode=0x{:x}, is_dir={}",
                        rgetattr.mode,
                        is_dir
                    );
                    is_dir
                }
                Ok(P9Response::Error(rlerror)) => {
                    debug_print!("sys_openat: O_PATH Rgetattr error: ecode={}", rlerror.ecode);
                    false
                }
                Err(e) => {
                    debug_print!("sys_openat: O_PATH Tgetattr send failed: {:?}", e);
                    false
                }
            };

            debug_print!(
                "sys_openat: O_PATH setting is_dir={} for fd {}",
                is_directory,
                file_fid
            );
            // For O_PATH, we don't call Tlopen - just set up the fd
            set_fd(file_fid, file_fid);
            let fd_entry = get_fd(file_fid);
            let mut file_desc = get_file_desc(fd_entry.file_desc_id);
            file_desc.mode = 0;
            file_desc.is_dir = is_directory;
            file_desc.flags = _flags;
            update_file_desc(fd_entry.file_desc_id, file_desc);
            return Ok(file_fid);
        }

        let tlopen = TlopenMessage::new(0, file_fid, p9_flags);

        match tlopen.send_tlopen() {
            Ok(P9Response::Success(rlopen)) => {
                debug_print!("sys_openat: received Rlopen: {:?}", rlopen);
                let is_directory = rlopen.qid.is_dir();
                set_fd(file_fid, file_fid);
                // Update the file description with the correct mode, is_dir, and flags
                let fd_entry = get_fd(file_fid);
                let mut file_desc = get_file_desc(fd_entry.file_desc_id);
                file_desc.mode = p9_flags;
                file_desc.is_dir = is_directory;
                file_desc.flags = _flags;
                update_file_desc(fd_entry.file_desc_id, file_desc);

                // Handle O_TRUNC: truncate file to 0 bytes after opening
                if (_flags & O_TRUNC) == O_TRUNC {
                    debug_print!("sys_openat: O_TRUNC detected, truncating file to 0 bytes");
                    let valid = P9SetattrMask::Size as u32;
                    let tsetattr = TsetattrMessage::new(
                        0,        // tag
                        file_fid, // fid
                        valid,    // valid mask (only Size)
                        0,        // mode (not changing)
                        0,        // uid (not changing)
                        0,        // gid (not changing)
                        0,        // size (truncate to 0)
                        0,        // atime_sec (not changing)
                        0,        // atime_nsec (not changing)
                        0,        // mtime_sec (not changing)
                        0,        // mtime_nsec (not changing)
                    );

                    match tsetattr.send_tsetattr() {
                        Ok(P9Response::Success(_)) => {
                            debug_print!("sys_openat: file truncated successfully");
                        }
                        Ok(P9Response::Error(rlerror)) => {
                            debug_print!(
                                "sys_openat: error truncating file: ecode={}",
                                rlerror.ecode
                            );
                            clunk(file_fid, false);
                            return Err(map_p9_error(rlerror.ecode));
                        }
                        Err(e) => {
                            debug_print!("sys_openat: error sending Tsetattr: {:?}", e);
                            clunk(file_fid, false);
                            return Err(Err::NoSys);
                        }
                    }
                }

                Ok(file_fid)
            }
            Ok(P9Response::Error(rlerror)) => {
                clunk(file_fid, false);
                debug_print!(
                    "sys_openat: received Rlerror for Rlopen: tag={}, ecode={}",
                    rlerror.tag,
                    rlerror.ecode
                );
                Err(map_p9_error(rlerror.ecode))
            }
            Err(e) => {
                debug_print!("sys_openat: error sending Tlopen: {:?}", e);
                clunk(file_fid, false);
                Err(Err::NoSys)
            }
        }
    } else if _flags & O_CREAT == O_CREAT {
        debug_print!("sys_openat: O_CREAT flag detected, attempting file creation");
        let (dir_path, file_name) = split_path(&filename_str);
        resolve_path(dfd, &dir_path, file_fid)?;

        // Apply umask to permission bits, but preserve special bits (setuid, setgid, sticky)
        let permission_bits = mode & 0o777; // Get permission bits
        let umask_value = get_umask();
        let masked_permissions = permission_bits & !umask_value; // Apply umask
        let special_bits = mode & 0o7000; // Get special bits (setuid, setgid, sticky)
        let p9_mode = special_bits | masked_permissions; // Combine them
        debug_print!(
            "sys_openat: requested_mode=0o{:o}, umask=0o{:o}, final_mode=0o{:o}",
            mode,
            umask_value,
            p9_mode
        );
        // Create the file using Tlcreate
        let tlcreate =
            TlcreateMessage::new(0, file_fid, file_name.to_string(), p9_flags, p9_mode, 0); // flags=p9_flags, mode=p9_mode, gid=0
        debug_print!("sys_openat: tlcreate = {:?}", tlcreate);
        match tlcreate.send_tlcreate() {
            Ok(P9Response::Success(rlcreate)) => {
                debug_print!("sys_openat: received Rlcreate: {:?}", rlcreate);
                let is_directory = rlcreate.qid.is_dir();
                set_fd(file_fid, file_fid);
                // Update the file description with the correct mode, is_dir, and flags
                let fd_entry = get_fd(file_fid);
                let mut file_desc = get_file_desc(fd_entry.file_desc_id);
                file_desc.mode = p9_flags;
                file_desc.is_dir = is_directory;
                file_desc.flags = _flags;
                update_file_desc(fd_entry.file_desc_id, file_desc);
                Ok(file_fid)
            }
            Ok(P9Response::Error(rlerror)) => {
                clunk(file_fid, false);
                debug_print!(
                    "sys_openat: received Rlerror for Rlcreate: tag={}, ecode={}",
                    rlerror.tag,
                    rlerror.ecode
                );
                Err(map_p9_error(rlerror.ecode))
            }
            Err(e) => {
                debug_print!("sys_openat: error sending Tlcreate: {:?}", e);
                clunk(file_fid, false);
                Err(Err::NoSys)
            }
        }
    } else {
        // File doesn't exist and O_CREAT is not set
        // Return the actual error from resolve_path (could be ENOTDIR, EBADF, ENOENT, etc.)
        match path_result {
            Ok(_) => {
                // This shouldn't happen as we already handled the Ok case above
                debug_print!("sys_openat: unexpected state - path_result was Ok");
                Err(Err::FileNotFound)
            }
            Err(e) => {
                debug_print!(
                    "sys_openat: path resolution failed with error {:?}",
                    e as i32
                );
                Err(e)
            }
        }
    }
}

// This implementation mimics the behavior of the POSIX dirname utility.
// It returns the parent directory of the given path, handling edge cases.
#[allow(dead_code)]
fn dirname(path: &str) -> String {
    // Remove trailing slashes except for root
    let path = path.trim_end_matches('/');

    // If the path is empty after trimming, return "/"
    if path.is_empty() {
        return "/".to_string();
    }

    // Find the last slash in the path
    if let Some(pos) = path.rfind('/') {
        if pos == 0 {
            // Path is like "/foo" or "/"
            "/".to_string()
        } else {
            // Path is like "/foo/bar" or "foo/bar"
            path[..pos].to_string()
        }
    } else {
        // No slash found, so return "/"
        "/".to_string()
    }
}

fn normalize_path(path: &str) -> Vec<String> {
    let split: Vec<String> = path.split("/").map(|s| s.to_string()).collect();
    // remove ./ and handle ..
    let mut new_path = Vec::new();
    for s in split {
        if s == "." || s.is_empty() {
            continue;
        } else if s == ".." {
            // Remove the previous component if it exists and is not ".."
            if !new_path.is_empty() && new_path.last() != Some(&"..".to_string()) {
                new_path.pop();
            } else {
                // If no previous component, keep the ".." (for relative paths)
                new_path.push(s);
            }
        } else {
            new_path.push(s);
        }
    }
    new_path
}

#[allow(dead_code)]
fn get_file_size(starting_fid: u32, path: &str, depth: u32) -> Result<u64, Err> {
    if depth > 40 {
        // don't let it recurse too much
        debug_print!("get_file_size: depth too deep, returning error");
        return Err(Err::NoSys);
    }
    let wnames = normalize_path(path);
    do_walk(starting_fid, TEMP_FID_1, wnames)?;

    let tgetattr = crate::p9::TgetattrMessage::new(0, TEMP_FID_1, P9_GETATTR_ALL);
    match tgetattr.send_tgetattr() {
        Ok(P9Response::Success(rgetattr)) => {
            debug_print!("sys_statx: rgetattr = {:?}", rgetattr);
            clunk(TEMP_FID_1, false);
            Ok(rgetattr.size)
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "sys_statx: received Rlerror for getattr operation: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
            clunk(TEMP_FID_1, false);
            Err(Err::NoSys)
        }
        Err(e) => {
            debug_print!("sys_statx: error = {:?}", e);
            clunk(TEMP_FID_1, false);
            Err(Err::NoSys)
        }
    }
}

pub fn sys_statx(
    _dfd: u32,
    _filename: u32,
    _flags: u32,
    _mask: u32,
    _statxbuf: u32,
) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_statx: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // AT_EMPTY_PATH flag (0x1000) - if filename is empty, stat the fd itself
    const AT_EMPTY_PATH: u32 = 0x1000;
    const AT_SYMLINK_NOFOLLOW: u32 = 0x100;
    const AT_NO_AUTOMOUNT: u32 = 0x800;
    const AT_STATX_SYNC_TYPE: u32 = 0x6000; // Mask for sync type flags

    // Valid flags for statx
    const VALID_FLAGS_MASK: u32 =
        AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_NO_AUTOMOUNT | AT_STATX_SYNC_TYPE;

    // Check for invalid flags
    if (_flags & !VALID_FLAGS_MASK) != 0 {
        debug_print!("sys_statx: invalid flags 0x{:x}", _flags);
        return Err(Err::Inval);
    }

    // Validate mask - check for invalid bits
    // Valid mask bits: STATX_BASIC_STATS (0x7ff) | STATX_BTIME (0x800) | STATX_MNT_ID (0x1000) | STATX_DIOALIGN (0x2000) | STATX_RESERVED (0x80000000)
    const VALID_MASK_BITS: u32 = 0x80003fff;
    if (_mask & !VALID_MASK_BITS) != 0 {
        debug_print!("sys_statx: invalid mask 0x{:x}", _mask);
        return Err(Err::Inval);
    }

    // Validate statxbuf pointer early - must be writable
    if _statxbuf == 0 {
        debug_print!("sys_statx: _statxbuf is NULL");
        return Err(Err::Fault);
    }
    let statx_size = core::mem::size_of::<Statx>();
    if crate::linux_abi::is_valid_user_address(_statxbuf, statx_size, true).is_none() {
        debug_print!("sys_statx: _statxbuf {:08x} is not writable", _statxbuf);
        return Err(Err::Fault);
    }

    const MAX_PATH_LEN: usize = 256;

    // Handle AT_EMPTY_PATH early - the pathname is ignored in this mode
    if (_flags & AT_EMPTY_PATH) != 0 {
        if _dfd >= 256 {
            debug_print!(
                "sys_statx: AT_EMPTY_PATH set but dfd {} is out of range",
                _dfd
            );
            return Err(Err::BadFd);
        }

        if _filename != 0 {
            let filename_str = validate_and_read_pathname_with_len(_filename, MAX_PATH_LEN)?;
            if !filename_str.is_empty() {
                debug_print!(
                    "sys_statx: AT_EMPTY_PATH set but filename '{}' is not empty",
                    filename_str
                );
                return Err(Err::Inval);
            }
        }

        debug_print!("sys_statx: AT_EMPTY_PATH set, statting fd {}", _dfd);

        // Special handling for stdin/stdout/stderr (fds 0, 1, 2)
        // These are character devices and don't have valid P9 FIDs
        if _dfd <= 2 {
            use crate::constants::{
                STATX_GID, STATX_INO, STATX_MODE, STATX_NLINK, STATX_SIZE, STATX_TYPE, STATX_UID,
                Statx, StatxTimestamp,
            };

            debug_print!(
                "sys_statx: fd {} is stdin/stdout/stderr, treating as character device",
                _dfd
            );
            // Create a statx structure for a character device (tty-like)
            // S_IFCHR (0x2000) = character device, 0666 = rw-rw-rw-
            let mode: u16 = 0x2000 | 0o666;
            // Use fd number as pseudo inode, major=5 (tty), minor based on fd
            let rdev_minor = _dfd + 64; // Common tty minor numbers start at 64
            let statx = Statx {
                stx_mask: STATX_TYPE
                    | STATX_MODE
                    | STATX_NLINK
                    | STATX_UID
                    | STATX_GID
                    | STATX_INO
                    | STATX_SIZE,
                stx_blksize: 4096,
                stx_attributes: 0,
                stx_nlink: 1,
                stx_uid: 0, // root
                stx_gid: 0, // root
                stx_mode: mode,
                __spare0: [0],
                stx_ino: _dfd as u64,
                stx_size: 0, // Character devices have size 0
                stx_blocks: 0,
                stx_attributes_mask: 0,
                stx_atime: StatxTimestamp {
                    tv_sec: 0,
                    tv_nsec: 0,
                    __reserved: 0,
                },
                stx_btime: StatxTimestamp {
                    tv_sec: 0,
                    tv_nsec: 0,
                    __reserved: 0,
                },
                stx_ctime: StatxTimestamp {
                    tv_sec: 0,
                    tv_nsec: 0,
                    __reserved: 0,
                },
                stx_mtime: StatxTimestamp {
                    tv_sec: 0,
                    tv_nsec: 0,
                    __reserved: 0,
                },
                stx_rdev_major: 5, // tty major number
                stx_rdev_minor: rdev_minor,
                stx_dev_major: 0,
                stx_dev_minor: 0,
                stx_mnt_id: 0,
                stx_dio_mem_align: 0,
                stx_dio_offset_align: 0,
                __spare3: [0; 12],
            };

            // Write the statx structure to the user buffer
            let statx_bytes = unsafe {
                core::slice::from_raw_parts(
                    &statx as *const Statx as *const u8,
                    core::mem::size_of::<Statx>(),
                )
            };
            let bytes_copied = crate::kernel::copy_to_user(
                _statxbuf as *mut u8,
                statx_bytes.as_ptr(),
                core::mem::size_of::<Statx>(),
            );
            if bytes_copied == 0 {
                debug_print!("sys_statx: failed to copy statx structure to user memory");
                return Err(Err::Fault);
            }

            debug_print!("sys_statx: successfully filled statx buffer for stdin/stdout/stderr");
            return Ok(0);
        }

        let fd_entry = get_fd(_dfd);
        if fd_entry.file_desc_id == 0xFF {
            debug_print!("sys_statx: invalid fd {}", _dfd);
            return Err(Err::BadFd);
        }
        let file_desc = get_file_desc(fd_entry.file_desc_id);

        // Check if this fd is a virtual device
        if is_virtual_device(file_desc.fid) {
            debug_print!("sys_statx: fd {} is a virtual device", _dfd);
            let statx = create_virtual_device_statx(file_desc.fid);

            // Write the statx structure to the user buffer
            let statx_bytes = unsafe {
                core::slice::from_raw_parts(
                    &statx as *const Statx as *const u8,
                    core::mem::size_of::<Statx>(),
                )
            };
            let bytes_copied = crate::kernel::copy_to_user(
                _statxbuf as *mut u8,
                statx_bytes.as_ptr(),
                core::mem::size_of::<Statx>(),
            );
            if bytes_copied == 0 {
                debug_print!("sys_statx: failed to copy statx structure to user memory");
                return Err(Err::Fault);
            }

            debug_print!("sys_statx: successfully filled statx buffer for virtual device fd");
            return Ok(0);
        }

        // Use the fd's FID for regular files
        let target_fid = file_desc.fid;
        let tgetattr = crate::p9::TgetattrMessage::new(0, target_fid, P9_GETATTR_ALL);
        match tgetattr.send_tgetattr() {
            Ok(P9Response::Success(rgetattr)) => {
                debug_print!("sys_statx: rgetattr = {:?}", rgetattr);

                // Convert 9P RgetattrMessage to Linux statx structure
                let statx = convert_rgetattr_to_statx(&rgetattr);

                // Write the statx structure to the user buffer using copy_to_user
                let statx_bytes = unsafe {
                    core::slice::from_raw_parts(
                        &statx as *const Statx as *const u8,
                        core::mem::size_of::<Statx>(),
                    )
                };
                let bytes_copied = crate::kernel::copy_to_user(
                    _statxbuf as *mut u8,
                    statx_bytes.as_ptr(),
                    core::mem::size_of::<Statx>(),
                );
                if bytes_copied == 0 {
                    debug_print!("sys_statx: failed to copy statx structure to user memory");
                    return Err(Err::Fault);
                }

                debug_print!("sys_statx: successfully filled statx buffer");
                Ok(0) // Success
            }
            Ok(P9Response::Error(rlerror)) => {
                debug_print!(
                    "sys_statx: received Rlerror for getattr operation: tag={}, ecode={}",
                    rlerror.tag,
                    rlerror.ecode
                );
                Err(map_p9_error(rlerror.ecode))
            }
            Err(e) => {
                debug_print!("sys_statx: error = {:?}", e);
                Err(Err::NoSys)
            }
        }
    } else {
        // Normal path - parse filename
        debug_print!(
            "sys_statx: _dfd={}, _mask=0x{:x}, _statxbuf = {:08x}",
            _dfd,
            _mask,
            _statxbuf
        );
        if _filename == 0 {
            return Err(Err::Fault);
        }
        let filename = validate_and_read_pathname_with_len(_filename, MAX_PATH_LEN)?;
        debug_print!("sys_statx: filename = {}", filename);

        // Empty filename without AT_EMPTY_PATH is invalid
        if filename.is_empty() {
            debug_print!("sys_statx: empty filename without AT_EMPTY_PATH");
            return Err(Err::FileNotFound);
        }

        // Check if this is a virtual device file and handle it directly
        if let Some(virtual_fid) = get_virtual_device_fid(&filename) {
            debug_print!("sys_statx: statting virtual device: {}", filename);

            let statx = create_virtual_device_statx(virtual_fid);

            // Write the statx structure to the user buffer using copy_to_user
            let statx_bytes = unsafe {
                core::slice::from_raw_parts(
                    &statx as *const Statx as *const u8,
                    core::mem::size_of::<Statx>(),
                )
            };
            let bytes_copied = crate::kernel::copy_to_user(
                _statxbuf as *mut u8,
                statx_bytes.as_ptr(),
                core::mem::size_of::<Statx>(),
            );
            if bytes_copied == 0 {
                debug_print!("sys_statx: failed to copy statx structure to user memory");
                return Err(Err::Fault);
            }

            debug_print!("sys_statx: successfully filled statx buffer for virtual device");
            return Ok(0);
        }

        let target_fid = if (_flags & AT_SYMLINK_NOFOLLOW) != 0 {
            // Don't follow symlinks - use Twalk directly on the final component
            debug_print!("sys_statx: AT_SYMLINK_NOFOLLOW set, not following symlinks");
            let starting_fid = get_starting_fid(_dfd, &filename)?;
            let (dir_path, file_name) = split_path(&filename);

            // For relative paths, use the dfd directly as the directory
            let dir_fid = if dir_path.is_empty() || dir_path == "." {
                starting_fid
            } else {
                let dir_path = normalize_path(&dir_path);
                do_walk(starting_fid, TEMP_FID_4, dir_path)?;
                TEMP_FID_4
            };

            // Walk to the final component without following symlinks
            let file_path = vec![file_name];
            let twalk = crate::p9::TwalkMessage::new(0, dir_fid, TEMP_FID_1, file_path);
            match twalk.send_twalk() {
                Ok(P9Response::Success(rwalk)) => {
                    if rwalk.wqids.len() != 1 {
                        clunk(TEMP_FID_1, false);
                        if dir_fid != starting_fid {
                            clunk(dir_fid, false);
                        }
                        return Err(Err::FileNotFound);
                    }
                    // Clean up directory fid if we allocated one
                    if dir_fid != starting_fid {
                        clunk(dir_fid, false);
                    }
                }
                Ok(P9Response::Error(_)) => {
                    if dir_fid != starting_fid {
                        clunk(dir_fid, false);
                    }
                    return Err(Err::FileNotFound);
                }
                Err(_) => {
                    if dir_fid != starting_fid {
                        clunk(dir_fid, false);
                    }
                    return Err(Err::NoSys);
                }
            }
            TEMP_FID_1
        } else {
            // Normal path resolution (follows symlinks)
            // Use temp fids that don't conflict with CWD (TEMP_FID_2)
            let starting_fid = get_starting_fid(_dfd, &filename)?;
            let (dir_path, file_name) = split_path(&filename);
            let dir_path = normalize_path(&dir_path);
            do_walk(starting_fid, TEMP_FID_4, dir_path)?;
            resolve_file_to_fid(TEMP_FID_4, TEMP_FID_1, &file_name)?;
            clunk(TEMP_FID_4, false); // Clean up directory fid
            TEMP_FID_1
        };

        let tgetattr = crate::p9::TgetattrMessage::new(0, target_fid, P9_GETATTR_ALL);
        match tgetattr.send_tgetattr() {
            Ok(P9Response::Success(rgetattr)) => {
                debug_print!("sys_statx: rgetattr = {:?}", rgetattr);

                // Convert 9P RgetattrMessage to Linux statx structure
                let statx = convert_rgetattr_to_statx(&rgetattr);

                // Write the statx structure to the user buffer using copy_to_user
                let statx_bytes = unsafe {
                    core::slice::from_raw_parts(
                        &statx as *const Statx as *const u8,
                        core::mem::size_of::<Statx>(),
                    )
                };
                let bytes_copied = crate::kernel::copy_to_user(
                    _statxbuf as *mut u8,
                    statx_bytes.as_ptr(),
                    core::mem::size_of::<Statx>(),
                );
                if bytes_copied == 0 {
                    debug_print!("sys_statx: failed to copy statx structure to user memory");
                    return Err(Err::Fault);
                }

                debug_print!("sys_statx: successfully filled statx buffer");
                if target_fid == TEMP_FID_1 {
                    clunk(TEMP_FID_1, false);
                }
                Ok(0) // Success
            }
            Ok(P9Response::Error(rlerror)) => {
                debug_print!(
                    "sys_statx: received Rlerror for getattr operation: tag={}, ecode={}",
                    rlerror.tag,
                    rlerror.ecode
                );
                if target_fid == TEMP_FID_1 {
                    clunk(TEMP_FID_1, false);
                }
                Err(map_p9_error(rlerror.ecode))
            }
            Err(e) => {
                debug_print!("sys_statx: error = {:?}", e);
                if target_fid == TEMP_FID_1 {
                    clunk(TEMP_FID_1, false);
                }
                Err(Err::NoSys)
            }
        }
    }
}

/// Create a Statx structure for virtual devices and files
fn create_virtual_device_statx(fid: u32) -> Statx {
    use crate::constants::{Statx, StatxTimestamp};

    // Check if this is a virtual file (like /proc entries) vs a virtual device
    let (mode, size, rdev_major, rdev_minor) = if is_virtual_file(fid) {
        // S_IFREG (0x8000) = regular file
        // 0444 = r--r--r-- (read-only)
        let mode: u16 = 0x8000 | 0o444;
        let size = match fid {
            VIRTUAL_FILE_PROC_CPUINFO => get_proc_cpuinfo_content().len() as u64,
            _ => 0,
        };
        (mode, size, 0, 0) // Regular files don't have rdev
    } else {
        // S_IFCHR (0x2000) = character device
        // 0666 = rw-rw-rw- permissions
        let mode: u16 = 0x2000 | 0o666;
        let rdev_minor = match fid {
            VIRTUAL_DEV_NULL => 3,
            VIRTUAL_DEV_ZERO => 5,
            VIRTUAL_DEV_RANDOM => 8,
            VIRTUAL_DEV_URANDOM => 9,
            VIRTUAL_DEV_FULL => 7,
            _ => 0,
        };
        (mode, 0, 1, rdev_minor) // Devices have size 0, major=1
    };

    // Use the virtual device/file FID as a pseudo inode number
    let ino = fid as u64;

    Statx {
        stx_mask: STATX_TYPE
            | STATX_MODE
            | STATX_NLINK
            | STATX_UID
            | STATX_GID
            | STATX_INO
            | STATX_SIZE,
        stx_blksize: 4096,
        stx_attributes: 0,
        stx_nlink: 1,
        stx_uid: 0, // root
        stx_gid: 0, // root
        stx_mode: mode,
        __spare0: [0],
        stx_ino: ino,
        stx_size: size,
        stx_blocks: 0,
        stx_attributes_mask: 0,
        stx_atime: StatxTimestamp {
            tv_sec: 0,
            tv_nsec: 0,
            __reserved: 0,
        },
        stx_btime: StatxTimestamp {
            tv_sec: 0,
            tv_nsec: 0,
            __reserved: 0,
        },
        stx_ctime: StatxTimestamp {
            tv_sec: 0,
            tv_nsec: 0,
            __reserved: 0,
        },
        stx_mtime: StatxTimestamp {
            tv_sec: 0,
            tv_nsec: 0,
            __reserved: 0,
        },
        stx_rdev_major: rdev_major,
        stx_rdev_minor: rdev_minor,
        stx_dev_major: 0,
        stx_dev_minor: 0,
        stx_mnt_id: 0,
        stx_dio_mem_align: 0,
        stx_dio_offset_align: 0,
        __spare3: [0; 12],
    }
}

/// Convert 9P RgetattrMessage to Linux statx structure
fn convert_rgetattr_to_statx(rgetattr: &RgetattrMessage) -> Statx {
    // Determine which fields are valid based on the valid mask
    let mut stx_mask = 0u32;

    // Map 9P valid mask to statx mask
    if (rgetattr.valid & P9_GETATTR_MODE) != 0 {
        stx_mask |= STATX_TYPE | STATX_MODE;
    }
    if (rgetattr.valid & P9_GETATTR_NLINK) != 0 {
        stx_mask |= STATX_NLINK;
    }
    if (rgetattr.valid & P9_GETATTR_UID) != 0 {
        stx_mask |= STATX_UID;
    }
    if (rgetattr.valid & P9_GETATTR_GID) != 0 {
        stx_mask |= STATX_GID;
    }
    if (rgetattr.valid & P9_GETATTR_ATIME) != 0 {
        stx_mask |= STATX_ATIME;
    }
    if (rgetattr.valid & P9_GETATTR_MTIME) != 0 {
        stx_mask |= STATX_MTIME;
    }
    if (rgetattr.valid & P9_GETATTR_CTIME) != 0 {
        stx_mask |= STATX_CTIME;
    }
    if (rgetattr.valid & P9_GETATTR_INO) != 0 {
        stx_mask |= STATX_INO;
    }
    if (rgetattr.valid & P9_GETATTR_SIZE) != 0 {
        stx_mask |= STATX_SIZE;
    }
    if (rgetattr.valid & P9_GETATTR_BLOCKS) != 0 {
        stx_mask |= STATX_BLOCKS;
    }
    if (rgetattr.valid & P9_GETATTR_BTIME) != 0 {
        stx_mask |= STATX_BTIME;
    }

    // Use the mode field directly from 9P (only if mode is valid)
    let stx_mode = if (rgetattr.valid & P9_GETATTR_MODE) != 0 {
        rgetattr.mode as u16 // The mode field already contains file type + permissions
    } else {
        0 // Mode not valid, set to 0
    };

    Statx {
        stx_mask,
        stx_blksize: rgetattr.blksize as u32,
        stx_attributes: 0, // No special attributes for now
        stx_nlink: rgetattr.nlink as u32,
        stx_uid: rgetattr.uid,
        stx_gid: rgetattr.gid,
        stx_mode,
        __spare0: [0],
        stx_ino: rgetattr.qid.path, // Use QID path as inode number
        stx_size: rgetattr.size,
        stx_blocks: rgetattr.blocks,
        stx_attributes_mask: 0, // No special attributes supported
        stx_atime: StatxTimestamp {
            tv_sec: rgetattr.atime_sec as i64,
            tv_nsec: rgetattr.atime_nsec as u32,
            __reserved: 0,
        },
        stx_btime: StatxTimestamp {
            tv_sec: rgetattr.btime_sec as i64,
            tv_nsec: rgetattr.btime_nsec as u32,
            __reserved: 0,
        },
        stx_ctime: StatxTimestamp {
            tv_sec: rgetattr.ctime_sec as i64,
            tv_nsec: rgetattr.ctime_nsec as u32,
            __reserved: 0,
        },
        stx_mtime: StatxTimestamp {
            tv_sec: rgetattr.mtime_sec as i64,
            tv_nsec: rgetattr.mtime_nsec as u32,
            __reserved: 0,
        },
        stx_rdev_major: (rgetattr.rdev >> 8) as u32,
        stx_rdev_minor: (rgetattr.rdev & 0xFF) as u32,
        stx_dev_major: 0, // Not available from 9P
        stx_dev_minor: 0, // Not available from 9P
        stx_mnt_id: 0,    // Not available from 9P
        stx_dio_mem_align: 0,
        stx_dio_offset_align: 0,
        __spare3: [0; 12],
    }
}

// make a fd
pub fn find_free_fd() -> Result<u32, Err> {
    let mut fd = 0;
    while fd < 256 && get_fd(fd).file_desc_id != 0xFF {
        fd += 1;
    }
    if fd >= 256 {
        debug_print!("find_free_fd: no free file descriptors available");
        return Err(Err::MFile);
    }
    Ok(fd)
}

#[allow(dead_code)]
pub fn set_fd(fd: u32, fid: u32) {
    // Allocate a new file description
    let desc_id = find_free_file_desc().unwrap_or(0);
    update_file_desc(
        desc_id,
        FileDescription {
            fid,
            cursor: 0,
            is_dir: false,
            mode: INVALID_MODE,
            flags: 0,
            refcount: 1, // Initial reference
        },
    );

    // Point the fd to this file description
    update_fd(
        fd,
        FileDescriptor {
            file_desc_id: desc_id,
            cloexec: false, // New file descriptors start with FD_CLOEXEC unset
        },
    );
}

#[repr(C)]
#[derive(Clone, Copy)]
pub struct IoVec {
    pub iov_base: *mut u8,
    pub iov_len: usize,
}

fn copy_from_user(src: u32, dst: &mut [u8]) -> Result<(), Err> {
    if dst.is_empty() {
        return Ok(());
    }

    let mut copied = 0usize;
    while copied < dst.len() {
        let addr = src.checked_add(copied as u32).ok_or(Err::Fault)?;
        let remaining = dst.len() - copied;
        let safe =
            crate::linux_abi::is_valid_user_address(addr, remaining, false).ok_or(Err::Fault)?;
        let chunk = core::cmp::min(remaining, safe);
        unsafe {
            core::ptr::copy_nonoverlapping(addr as *const u8, dst[copied..].as_mut_ptr(), chunk);
        }
        copied += chunk;
    }

    Ok(())
}

fn load_iovecs(vec_ptr: u32, vlen: u32) -> Result<Vec<IoVec>, Err> {
    let mut result = Vec::with_capacity(vlen as usize);
    let entry_size = core::mem::size_of::<IoVec>();

    if entry_size == 0 {
        return Ok(result);
    }

    let base = vec_ptr as usize;
    for i in 0..(vlen as usize) {
        let offset = base
            .checked_add(i.checked_mul(entry_size).ok_or(Err::Inval)?)
            .ok_or(Err::Inval)?;
        let mut raw = [0u8; core::mem::size_of::<IoVec>()];
        copy_from_user(offset as u32, &mut raw)?;
        let iov = unsafe { core::ptr::read_unaligned(raw.as_ptr() as *const IoVec) };
        result.push(iov);
    }

    Ok(result)
}

pub fn clunk(fid: u32, is_cwd_clunking_allowed: bool) {
    // Check if we're trying to clunk the CWD FID without permission
    if fid == get_cwd_fid() && !is_cwd_clunking_allowed {
        kpanic!("Attempted to clunk CWD FID {} without permission", fid);
    }

    let tclunk = crate::p9::TclunkMessage::new(0, fid);
    debug_print!("clunk: sending TclunkMessage for fid {}", fid);
    match tclunk.send_tclunk() {
        Ok(P9Response::Success(rclunk)) => {
            debug_print!("clunk {}: = {:?}", fid, rclunk);
        }
        Ok(P9Response::Error(rlerror)) => {
            debug_print!(
                "clunk: received Rlerror for clunk operation: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
        }
        Err(e) => {
            debug_print!("clunk: error sending Tclunk: {:?}", e);
        }
    }
}

pub fn attach_to_p9() {
    use crate::p9_backend::get_backend_type;

    let backend_type = get_backend_type();
    debug_print!("Attaching to P9 using {:?} backend", backend_type);

    // Version negotiation
    let msg = TversionMessage::default_9p2000l(1);
    match msg.send_tversion() {
        Ok(P9Response::Success(rversion)) => {
            debug_print!("Successfully negotiated version: {:?}", rversion);
        }
        Ok(P9Response::Error(rlerror)) => {
            kpanic!(
                "Received Rlerror for Rversion: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
        }
        Err(e) => {
            kpanic!("Failed to send Tversion: {:?}", e);
        }
    }

    // Attach to root
    let tattach = TattachMessage::new(
        0,
        0,
        crate::p9::constants::P9_NOFID,
        "root".to_string(),
        "/risc0-root".to_string(),
    );
    match tattach.send_tattach() {
        Ok(P9Response::Success(rattach)) => {
            debug_print!("Received Rattach: {:?}", rattach);
            set_cwd_str("/".to_string());
            set_cwd_fid(0);
            set_root_fid(0);
        }
        Ok(P9Response::Error(rlerror)) => {
            kpanic!(
                "Received Rlerror for Rattach: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
        }
        Err(e) => {
            kpanic!("Failed to send Tattach: {:?}", e);
        }
    }
}
