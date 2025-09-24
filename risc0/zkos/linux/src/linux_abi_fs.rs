use crate::{
    constants::*,
    host_calls::host_write,
    host_calls::{host_log, host_terminate},
    kernel::print,
    linux_abi::Err,
    p9::{
        P9Response, Qid, RattachMessage, RclunkMessage, ReadableMessage, RgetattrMessage,
        RlcreateMessage, RlopenMessage, RreadMessage, RreaddirMessage, RreadlinkMessage,
        RversionMessage, RwalkMessage, RwriteMessage, TattachMessage, TlcreateMessage,
        TlopenMessage, TreadMessage, TreaddirMessage, TversionMessage, TwriteMessage, constants::*,
    },
};

#[cfg(target_arch = "riscv32")]
use alloc::string::String;
#[cfg(target_arch = "riscv32")]
use alloc::string::ToString;
#[cfg(target_arch = "riscv32")]
use alloc::vec;
#[cfg(target_arch = "riscv32")]
use alloc::vec::Vec;

use no_std_strings::{str_format, str256};
// Filesystem-related syscalls

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

pub static mut ROOT_FID: u32 = 0;
pub static mut CWD_FID: u32 = 0;

#[derive(Copy, Clone)]
pub struct FileDescriptor {
    pub fid: u32,
    pub cursor: u64,
    #[allow(dead_code)]
    pub is_dir: bool,
}

pub static mut FD_TABLE: [FileDescriptor; 256] = [FileDescriptor {
    fid: 0,
    cursor: 0,
    is_dir: false,
}; 256];

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

pub fn sys_close(_fd: u32) -> Result<u32, Err> {
    unsafe {
        if FD_TABLE[_fd as usize].fid != 0xFFFF_FFFE && FD_TABLE[_fd as usize].fid != 0 {
            clunk(FD_TABLE[_fd as usize].fid);
            FD_TABLE[_fd as usize] = FileDescriptor {
                fid: 0,
                cursor: 0,
                is_dir: false,
            };
            Ok(0)
        } else {
            Err(Err::NoSys)
        }
    }
}

pub fn sys_read(_fd: u32, _buf: u32, _count: u32) -> Result<u32, Err> {
    if !get_p9_enabled() {
        let msg = b"sys_read: p9 is not enabled";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }
    unsafe {
        if FD_TABLE[_fd as usize].fid != 0 {
            // read with Tread and Rread from the fid using 9p protocol and update .cursor in FD_TABLE
            let tread = TreadMessage::new(
                0,
                FD_TABLE[_fd as usize].fid,
                FD_TABLE[_fd as usize].cursor,
                _count,
            );
            match tread.send_tread() {
                Ok(_bytes_written) => {
                    // Success
                }
                Err(_e) => {
                    return Err(Err::NoSys);
                }
            }
            match RreadMessage::read_response() {
                P9Response::Success(rread) => {
                    let user_ptr = _buf as *mut u8;
                    let data = rread.data;
                    core::ptr::copy_nonoverlapping(data.as_ptr(), user_ptr, rread.count as usize);
                    FD_TABLE[_fd as usize].cursor += rread.count as u64;
                    return Ok(rread.count);
                }
                P9Response::Error(_rlerror) => {
                    return Err(Err::NoSys);
                }
            }
        }
    }
    let msg = b"sys_read not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_write(fd: u32, buf: u32, count: u32) -> Result<u32, Err> {
    do_write(fd as i32, buf as *const u8, count as usize).map(|x| x as u32)
}

pub fn do_write(fd: i32, buf: *const u8, count: usize) -> Result<usize, Err> {
    if fd == 1 || fd == 2 {
        host_write(fd as u32, buf, count);
    } else {
        if !get_p9_enabled() {
            let msg = b"do_write: p9 is not enabled";
            host_log(msg.as_ptr(), msg.len());
            return Err(Err::NoSys);
        }
        unsafe {
            if FD_TABLE[fd as usize].fid != 0 {
                // write with Twrite and Rwrite to the fid using 9p protocol and update .cursor in FD_TABLE
                let twrite = TwriteMessage::new(
                    0,
                    FD_TABLE[fd as usize].fid,
                    FD_TABLE[fd as usize].cursor,
                    core::slice::from_raw_parts(buf, count).to_vec(),
                );
                match twrite.send_twrite() {
                    Ok(_bytes_written) => {
                        // Success
                    }
                    Err(_e) => {
                        return Err(Err::NoSys);
                    }
                }
                match RwriteMessage::read_response() {
                    P9Response::Success(rwrite) => {
                        FD_TABLE[fd as usize].cursor += rwrite.count as u64;
                        return Ok(rwrite.count as usize);
                    }
                    P9Response::Error(_rlerror) => {
                        return Err(Err::NoSys);
                    }
                }
            }
        }
        let msg = b"do_write for fd > 2 that are not FIDs not implemented";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    Ok(count)
}

pub fn sys_writev(fd: u32, vec_ptr: u32, vlen: u32) -> Result<u32, Err> {
    let fd = fd as i32;
    let vec_ptr = vec_ptr as *const IoVec;
    let vec = unsafe { core::slice::from_raw_parts(vec_ptr, vlen as usize) };
    if fd > 2 {
        // For file descriptors > 2 (not stdout/stderr), return not implemented for now.
        let msg = b"sys_writev for fd > 2 not implemented";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    let mut total: usize = 0;
    for iov in vec {
        total += do_write(fd, iov.iov_base, iov.iov_len)?;
    }
    Ok(total as u32)
}

pub fn sys_chdir(_filename: u32) -> Result<u32, Err> {
    let msg = b"sys_chdir not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_dup(_fd: u32) -> Result<u32, Err> {
    let msg = b"sys_dup not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_dup3(_oldfd: u32, _newfd: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_dup3 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_faccessat(_dfd: u32, _filename: u32, _mode: u32) -> Result<u32, Err> {
    let msg = b"sys_faccessat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_faccessat2(_dfd: u32, _filename: u32, _mode: u32) -> Result<u32, Err> {
    let msg = b"sys_faccessat2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fadvise64_64(_fd: u32, _offset: u32, _len: u32, _advice: u32) -> Result<u32, Err> {
    let msg = b"sys_fadvise64_64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fallocate(_fd: u32, _mode: u32, _offset: u32, _len: u32) -> Result<u32, Err> {
    let msg = b"sys_fallocate not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
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

pub fn sys_fchdir(_fd: u32) -> Result<u32, Err> {
    let msg = b"sys_fchdir not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fchmod(_fd: u32, _mode: u32) -> Result<u32, Err> {
    let msg = b"sys_fchmod not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fchmodat(_dfd: u32, _filename: u32, _mode: u32, _flag: u32) -> Result<u32, Err> {
    let msg = b"sys_fchmodat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fchmodat2(_dfd: u32, _filename: u32, _mode: u32, _flag: u32) -> Result<u32, Err> {
    let msg = b"sys_fchmodat2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fchown(_fd: u32, _user: u32, _group: u32) -> Result<u32, Err> {
    let msg = b"sys_fchown not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fchownat(
    _dfd: u32,
    _filename: u32,
    _user: u32,
    _group: u32,
    _flag: u32,
) -> Result<u32, Err> {
    let msg = b"sys_fchownat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fdatasync(_fd: u32) -> Result<u32, Err> {
    let msg = b"sys_fdatasync not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fgetxattr(_fd: u32, _name: u32, _value: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_fgetxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
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

pub fn sys_flistxattr(_fd: u32, _list: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_flistxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_flock(_fd: u32, _cmd: u32) -> Result<u32, Err> {
    let msg = b"sys_flock not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fremovexattr(_fd: u32, _name: u32) -> Result<u32, Err> {
    let msg = b"sys_fremovexattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_ftruncate64(_fd: u32, _length: u32) -> Result<u32, Err> {
    let msg = b"sys_ftruncate64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fsync(_fd: u32) -> Result<u32, Err> {
    let msg = b"sys_fsync not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fsetxattr(
    _fd: u32,
    _name: u32,
    _value: u32,
    _size: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_fsetxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getcwd(_buf: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_getcwd not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
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
    _olddirfd: u32,
    _oldpath: u32,
    _newdirfd: u32,
    _newpath: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_linkat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
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

pub fn sys_llseek(_fd: u32, _offset_high: u32, _offset_low: u32) -> Result<u32, Err> {
    let msg = b"sys_llseek not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
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
    let msg = b"sys_mkdirat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mknodat(_dfd: u32, _filename: u32, _mode: u32, _dev: u32) -> Result<u32, Err> {
    let msg = b"sys_mknodat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_openat2(_dfd: u32, _filename: u32, _how: u32) -> Result<u32, Err> {
    // Extract and print the filename
    let filename = unsafe { core::slice::from_raw_parts(_filename as *const u8, 256) };
    let null_pos = filename
        .iter()
        .position(|&b| b == 0)
        .unwrap_or(filename.len());
    let filename = &filename[..null_pos];

    // Convert the filename to a UTF-8 string
    let filename_str = match str::from_utf8(filename) {
        Ok(s) => s,
        Err(_) => {
            kprint!("sys_openat2: invalid UTF-8 filename");
            return Err(Err::NoSys);
        }
    };

    kprint!(
        "sys_openat2: dfd={}, filename='{}', how=0x{:x}",
        _dfd,
        filename_str,
        _how
    );

    // TODO: Implement actual file opening with 9P operations
    // For now, just return not implemented
    let msg = b"sys_openat2 not fully implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_preadv(_fd: u32, _vec: u32, _vlen: u32, _pos_low: u32) -> Result<u32, Err> {
    let msg = b"sys_preadv not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
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
    let msg = b"sys_pwrite64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_pwritev(_fd: u32, _vec: u32, _vlen: u32, _pos_low: u32) -> Result<u32, Err> {
    let msg = b"sys_pwritev not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
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
    let msg = b"sys_readv not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
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
    let msg = b"sys_pread64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_readahead(_fd: u32, _offset: u32, _count: u32) -> Result<u32, Err> {
    let msg = b"sys_readahead not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_readlinkat(_dfd: u32, _pathname: u32, _buf: u32) -> Result<u32, Err> {
    let msg = b"sys_readlinkat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
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

pub fn sys_fcntl64(_fd: u32, _cmd: u32, _arg: u32) -> Result<u32, Err> {
    if _cmd == F_SETFD && _arg & FD_CLOEXEC == FD_CLOEXEC {
        // mock and return ok
        return Ok(0);
    }
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

    let offset = unsafe { FD_TABLE[fd as usize].cursor };

    // Get the FID from the FD table
    let fid = unsafe { FD_TABLE[fd as usize].fid };
    if fid == 0 {
        return Err(Err::Inval);
    }

    // XXX we will read one dir entry at a a time
    let treaddir = TreaddirMessage::new(0, fid, offset, count);
    match treaddir.send_treaddir() {
        Ok(_bytes_written) => {
            // Success
        }
        Err(_e) => {
            return Err(Err::NoSys);
        }
    }

    // Read the Rreaddir response
    match RreaddirMessage::read_response() {
        P9Response::Success(rreaddir) => {
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

                unsafe {
                    FD_TABLE[fd as usize].cursor = entry_offset;
                }
                // Ensure next dirent is 8-byte aligned
                user_offset = (user_offset + reclen as usize + 7) & !7;
                total_bytes += reclen as usize;
            }

            Ok(total_bytes as u32)
        }
        P9Response::Error(_rlerror) => Err(Err::NoSys),
    }
}

#[allow(dead_code)]
// instead of wnames we take a path
fn do_walk(starting_fid: u32, target_fid: u32, path: String) -> Result<(u32, Vec<Qid>), Err> {
    let wnames: Vec<String> = path.split("/").skip(1).map(|s| s.to_string()).collect();
    let wnames_len = wnames.len();
    let twalk = crate::p9::TwalkMessage::new(0, starting_fid, target_fid, wnames);
    match twalk.send_twalk() {
        Ok(bytes_written) => {
            kprint!("do_walk: bytes_written = {}", bytes_written);
        }
        Err(e) => {
            kprint!("do_walk: error = {:?}", e);
            return Err(Err::NoSys);
        }
    }
    match RwalkMessage::read_response() {
        P9Response::Success(rwalk) => {
            if rwalk.wqids.len() != wnames_len {
                clunk(target_fid);
                Err(Err::FileNotFound)
            } else {
                Ok((0, rwalk.wqids))
            }
        }
        P9Response::Error(rlerror) => {
            kprint!(
                "do_walk: received Rlerror for walk operation: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
            Err(Err::NoSys)
        }
    }
}

/// Split a path into directory and filename components
fn split_path(path: &str) -> (String, String) {
    if let Some(last_slash) = path.rfind('/') {
        if last_slash == 0 {
            // Path is "/filename" - directory is "/"
            ("/".to_string(), path[1..].to_string())
        } else {
            // Path is "/dir/filename" - directory is "/dir", filename is "filename"
            (
                path[..last_slash].to_string(),
                path[last_slash + 1..].to_string(),
            )
        }
    } else {
        // No slash found - this shouldn't happen for absolute paths
        ("/".to_string(), path.to_string())
    }
}

pub fn sys_openat(_dfd: u32, _filename: u32, _flags: u32, _mode: u32) -> Result<u32, Err> {
    // Extract and print the filename
    let filename = unsafe { core::slice::from_raw_parts(_filename as *const u8, 256) };
    let null_pos = filename
        .iter()
        .position(|&b| b == 0)
        .unwrap_or(filename.len());
    let filename = &filename[..null_pos];

    let filename_str = match str::from_utf8(filename) {
        Ok(s) => s,
        Err(_) => {
            kprint!("sys_openat: invalid UTF-8 filename");
            return Err(Err::NoSys);
        }
    };
    do_openat(_dfd, filename_str, _flags, _mode)
}

fn do_openat(_dfd: u32, filename_str: &str, _flags: u32, _mode: u32) -> Result<u32, Err> {
    // Convert the filename to a UTF-8 s
    kprint!("sys_openat: filename='{}'", filename_str);
    // lets check if its an absolute path and panic otherwise
    if !filename_str.starts_with("/") {
        kpanic!("sys_openat: relative paths are not supported");
    }

    // Check if O_CREAT flag is set
    const O_CREAT: u32 = 0o100;
    // const O_EXCL: u32 = 0o200; // TODO: Implement O_EXCL logic

    let should_create = (_flags & O_CREAT) != 0;
    // let should_fail_if_exists = (_flags & O_EXCL) != 0; // TODO: Implement O_EXCL logic

    if should_create {
        kprint!("sys_openat: O_CREAT flag detected, attempting file creation");

        // Split path into directory and filename
        let (dir_path, file_name) = split_path(filename_str);
        kprint!(
            "sys_openat: directory='{}', filename='{}'",
            dir_path,
            file_name
        );

        // Walk to the directory
        // Get a FID for the new file
        let file_fid = find_free_fd();

        let dir_walk_result = do_walk(0, file_fid, dir_path.clone());
        match dir_walk_result {
            Ok((ret_code, _)) => {
                if ret_code != 0 {
                    kprint!(
                        "sys_openat: failed to walk to directory, error: {}",
                        ret_code
                    );
                    return Ok(ret_code);
                }
            }
            Err(e) => {
                kprint!("sys_openat: error walking to directory");
                return Err(e);
            }
        }

        // Convert mode to 9P permissions (simplified)
        let p9_mode = _mode & 0o777; // Basic permission bits

        // Convert Linux open flags to 9P flags (same logic as Tlopen)
        let p9_flags = if (_flags & 0o3) == 0o0 {
            0 // O_RDONLY
        } else if (_flags & 0o3) == 0o1 {
            1 // O_WRONLY
        } else {
            2 // O_RDWR
        };

        // Create the file using Tlcreate
        let tlcreate =
            TlcreateMessage::new(0, file_fid, file_name.to_string(), p9_flags, p9_mode, 0); // flags=p9_flags, mode=p9_mode, gid=0
        kprint!("sys_openat: tlcreate = {:?}", tlcreate);
        match tlcreate.send_tlcreate() {
            Ok(bytes_written) => {
                kprint!("sys_openat: sent {} bytes for Tlcreate", bytes_written);

                // Read the response
                match RlcreateMessage::read_response() {
                    P9Response::Success(rlcreate) => {
                        kprint!("sys_openat: received Rlcreate: {:?}", rlcreate);
                        set_fd(file_fid, file_fid);
                        return Ok(file_fid);
                    }
                    P9Response::Error(rlerror) => {
                        clunk(file_fid);
                        kprint!(
                            "sys_openat: received Rlerror for Rlcreate: tag={}, ecode={}",
                            rlerror.tag,
                            rlerror.ecode
                        );
                        return Ok(-(rlerror.ecode as i32) as u32);
                    }
                }
            }
            Err(e) => {
                kprint!("sys_openat: error sending Tlcreate: {:?}", e);
                clunk(file_fid);
                return Err(Err::NoSys);
            }
        }
    }

    // Original logic for opening existing files
    let fid = find_free_fd();
    let resolve_result = resolve_path(filename_str, 0, fid);
    if resolve_result.is_err() {
        return Err(resolve_result.unwrap_err());
    } else {
        kprint!(
            "sys_openat: dfd={}, filename='{}', real_filename='{}' flags=0x{:x}, mode=0x{:x}",
            _dfd,
            filename_str,
            resolve_result.unwrap_or("".to_string()),
            _flags,
            _mode
        );
    }

    // Convert Linux open flags to 9P open flags
    // This is a simplified mapping - in reality, we'd need more sophisticated flag conversion
    kprint!("sys_openat: flags=0x{:x}", _flags);
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

    let tlopen = TlopenMessage::new(0, fid, p9_flags);

    match tlopen.send_tlopen() {
        Ok(bytes_written) => {
            kprint!("sys_openat: sent {} bytes for Tlopen", bytes_written);

            // Read the response
            match RlopenMessage::read_response() {
                P9Response::Success(rlopen) => {
                    kprint!("sys_openat: received Rlopen: {:?}", rlopen);
                    set_fd(fid, fid);
                    Ok(fid)
                }
                P9Response::Error(rlerror) => {
                    clunk(fid);
                    kprint!(
                        "sys_openat: received Rlerror for Rlopen: tag={}, ecode={}",
                        rlerror.tag,
                        rlerror.ecode
                    );
                    Ok(-(rlerror.ecode as i32) as u32)
                }
            }
        }
        Err(e) => {
            kprint!("sys_openat: error sending Tlopen: {:?}", e);
            Err(Err::NoSys)
        }
    }
}

// This implementation mimics the behavior of the POSIX dirname utility.
// It returns the parent directory of the given path, handling edge cases.
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

fn resolve_relative_path_to_absolute(relative_path: &str, relative_to: &str) -> String {
    if relative_path.starts_with("/") {
        relative_path.to_string()
    } else {
        // handle .. and . properly
        let relative_path = relative_path.split("/").collect::<Vec<&str>>();
        let relative_to = relative_to.split("/").collect::<Vec<&str>>();
        let mut new_path = relative_to.clone();
        for path in relative_path {
            if path == ".." {
                new_path.pop();
            } else if path == "." {
                continue;
            } else {
                new_path.push(path);
            }
        }
        new_path.join("/")
    }
}

// resolves path and fid 0xFFFF_FFFE points to it after
fn resolve_path(path: &str, depth: u32, fid: u32) -> Result<String, Err> {
    if depth > 40 {
        // don't let it recurse too much
        kprint!("resolve_path: depth too deep, returning error");
        return Err(Err::NoSys);
    }
    let walk_result = unsafe { do_walk(ROOT_FID, fid, path.to_string()) };

    match walk_result {
        Ok((ret_code, qid)) => {
            if ret_code != 0 {
                return Err(Err::Inval);
            }
            if qid[qid.len() - 1].is_symlink() {
                let dirname = dirname(path);

                let treadlink = crate::p9::TreadlinkMessage::new(0, fid);
                match treadlink.send_treadlink() {
                    Ok(bytes_written) => {
                        kprint!("resolve_path: bytes_written = {}", bytes_written);
                    }
                    Err(e) => {
                        kprint!("resolve_path: error = {:?}", e);
                    }
                }
                match RreadlinkMessage::read_response() {
                    P9Response::Success(rreadlink) => {
                        kprint!("resolve_path: rreadlink = {:?}", rreadlink);
                        clunk(fid);
                        let target = rreadlink.target;
                        // now we need to resolve the symlink to an absolute path
                        let target =
                            resolve_relative_path_to_absolute(target.as_str(), dirname.as_str());
                        kprint!("resolve_path: resolved target = {}", target);
                        resolve_path(&target, depth + 1, fid)
                    }
                    P9Response::Error(rlerror) => {
                        kprint!(
                            "resolv_path: received Rlerror for readlink operation: tag={}, ecode={}",
                            rlerror.tag,
                            rlerror.ecode
                        );
                        Err(Err::NoSys)
                    }
                }
            } else {
                Ok(path.to_string())
            }
        }
        Err(e) => Err(e),
    }
}

fn get_file_size(path: &str, depth: u32) -> Result<u64, Err> {
    if depth > 40 {
        // don't let it recurse too much
        kprint!("get_file_size: depth too deep, returning error");
        return Err(Err::NoSys);
    }

    let resolve_result = resolve_path(path, depth, 0xFFFF_FFFE);
    match resolve_result {
        Ok(_) => {}
        Err(e) => {
            return Err(e);
        }
    }

    let tgetattr = crate::p9::TgetattrMessage::new(0, 0xFFFF_FFFE, P9_GETATTR_ALL);
    match tgetattr.send_tgetattr() {
        Ok(bytes_written) => {
            kprint!("sys_statx: bytes_written = {}", bytes_written);
        }
        Err(e) => {
            kprint!("sys_statx: error = {:?}", e);
        }
    }
    match RgetattrMessage::read_response() {
        P9Response::Success(rgetattr) => {
            kprint!("sys_statx: rgetattr = {:?}", rgetattr);
            clunk(0xFFFF_FFFE);
            Ok(rgetattr.size)
        }
        P9Response::Error(rlerror) => {
            kprint!(
                "sys_statx: received Rlerror for getattr operation: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
            clunk(0xFFFF_FFFE);
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

    // let's print the filename we're trying to stat, it's a u32 pointer
    // we need to search for the null-terminator
    // XXX this is ugly
    kprint!("sys_statx: _statxbuf = {:08x}", _statxbuf);
    let filename = unsafe { core::slice::from_raw_parts(_filename as *const u8, 256) };
    let null_pos = filename.iter().position(|&b| b == 0).unwrap();
    let filename = &filename[..null_pos];
    // convert the filename, it's a 0-terminated utf-8 string
    let filename = str::from_utf8(filename).unwrap();
    kprint!("sys_statx: filename = {}", filename);
    // if the first character is / it's a absolute path, otherwise it's a relative path
    let start_fid;
    let is_absolute_path = filename.starts_with("/");
    if is_absolute_path {
        unsafe {
            start_fid = ROOT_FID;
        }
    } else {
        kpanic!("sys_statx: relative paths are not supported");
    }
    // skip the first element of the vector
    let walk_result = do_walk(start_fid, 0xFFFF_FFFE, filename.to_string());
    match walk_result {
        Ok((ret_code, _)) => {
            if ret_code != 0 {
                return Ok(ret_code);
            }
            let tgetattr = crate::p9::TgetattrMessage::new(0, 0xFFFF_FFFE, P9_GETATTR_ALL);
            match tgetattr.send_tgetattr() {
                Ok(bytes_written) => {
                    kprint!("sys_statx: bytes_written = {}", bytes_written);
                }
                Err(e) => {
                    kprint!("sys_statx: error = {:?}", e);
                }
            }
            match RgetattrMessage::read_response() {
                P9Response::Success(rgetattr) => {
                    kprint!("sys_statx: rgetattr = {:?}", rgetattr);

                    // Convert 9P RgetattrMessage to Linux statx structure
                    let statx = convert_rgetattr_to_statx(&rgetattr);

                    // Write the statx structure to the user buffer
                    unsafe {
                        let statx_ptr = _statxbuf as *mut Statx;
                        *statx_ptr = statx;
                    }

                    kprint!("sys_statx: successfully filled statx buffer");
                    clunk(0xFFFF_FFFE);
                    Ok(0) // Success
                }
                P9Response::Error(rlerror) => {
                    kprint!(
                        "sys_statx: received Rlerror for getattr operation: tag={}, ecode={}",
                        rlerror.tag,
                        rlerror.ecode
                    );
                    clunk(0xFFFF_FFFE);
                    Ok(-(rlerror.ecode as i32) as u32)
                }
            }
        }
        Err(e) => Err(e),
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
pub fn find_free_fd() -> u32 {
    unsafe {
        let mut fd = 0;
        while FD_TABLE[fd].fid != 0 {
            fd += 1;
        }
        fd as u32
    }
}

#[allow(dead_code)]
pub fn set_fd(fd: u32, fid: u32) {
    unsafe {
        FD_TABLE[fd as usize] = FileDescriptor {
            fid,
            cursor: 0,
            is_dir: false,
        };
    }
}

pub fn load_file_aligned_to_page_size(path: &String) -> &[u8] {
    let file_size = get_file_size(path, 0);
    if let Ok(file_size) = file_size {
        kprint!("elf_loader: file_size = {}", file_size);
        let ptr = crate::linux_abi::allocate_aligned_to_page_size(file_size);
        const O_RDONLY: u32 = 0;
        let result = do_openat(-1i32 as u32, path, O_RDONLY, 0);

        if let Ok(_fd) = result {
            let mut file_ptr = ptr as u32;
            let mut read_so_far = 0u64;

            while read_so_far < file_size {
                let read_this_much = if (file_size - read_so_far) > 128 {
                    128
                } else {
                    file_size - read_so_far
                };
                kprint!("sys_read: read_this_much = {}", read_this_much);
                let read_result = sys_read(_fd, file_ptr, read_this_much as u32);
                if let Ok(read_count) = read_result {
                    read_so_far += read_count as u64;
                    file_ptr += read_count;
                } else {
                    kpanic!("Failed to read file: {}", path);
                }
            }
            let _ = sys_close(_fd);
            // turn ptr into a slice
            unsafe { core::slice::from_raw_parts(ptr, file_size as usize) }
        } else {
            kpanic!("Failed to open path: {}", path);
        }
    } else {
        kpanic!("Failed to get file size: {}", path);
    }
}

#[repr(C)]
pub struct IoVec {
    pub iov_base: *mut u8,
    pub iov_len: usize,
}

pub fn clunk(fid: u32) {
    let tclunk = crate::p9::TclunkMessage::new(0, fid);
    tclunk.send_tclunk().unwrap();
    let rclunk = RclunkMessage::read_response();
    match rclunk {
        P9Response::Success(rclunk) => {
            kprint!("clunk {}: = {:?}", fid, rclunk);
        }
        P9Response::Error(rlerror) => {
            kprint!(
                "clunk: received Rlerror for clunk operation: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
        }
    }
}

pub fn attach_to_p9() {
    let msg = TversionMessage::default_9p2000l(1);

    // Send the message via host_write to file descriptor 1
    match msg.send_tversion() {
        Ok(bytes_written) => {
            kprint!("Sent {} bytes", bytes_written);
        }
        Err(_e) => {
            kprint!("Failed to send Tversion");
        }
    }
    match RversionMessage::read_response() {
        P9Response::Success(rversion) => {
            kprint!("Successfully read Rversion: {:?}", rversion);
            // Process the message
        }
        P9Response::Error(rlerror) => {
            kpanic!(
                "Received Rlerror for Rversion: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
        }
    }
    // now we attach with Tattach, P9_NOFID as afid, to /risc0-root
    let tattach = TattachMessage::new(
        0,
        0,
        crate::p9::constants::P9_NOFID,
        "root".to_string(),
        "/risc0-root".to_string(),
    );
    match tattach.send_tattach() {
        Ok(bytes_written) => {
            kprint!("Sent {} bytes", bytes_written);
        }
        Err(e) => {
            kpanic!("Failed to send Tattach: {:?}", e);
        }
    }
    // and wait for Rattach
    match RattachMessage::read_response() {
        P9Response::Success(rattach) => {
            kprint!("Received Rattach: {:?}", rattach);
            unsafe {
                ROOT_FID = 0;
                CWD_FID = 0;
            };
        }
        P9Response::Error(rlerror) => {
            kpanic!(
                "Received Rlerror for Rattach: tag={}, ecode={}",
                rlerror.tag,
                rlerror.ecode
            );
        }
    }
}
