use crate::kernel::{DEBUG_ENABLED, print};
use no_std_strings::{str_format, str256};

#[cfg(target_arch = "riscv32")]
use crate::constants::*;
#[cfg(target_arch = "riscv32")]
use risc0_zkos_common::{get_ureg, set_ureg};

pub fn host_terminate(_a0: u32, _a1: u32) -> ! {
    #[cfg(target_arch = "riscv32")]
    unsafe {
        const HOST_ECALL_TERMINATE: u32 = 0;
        core::arch::asm!("ecall",
            in("a7") HOST_ECALL_TERMINATE,
            in("a0") _a0,
            in("a1") _a1,
            options(noreturn)
        )
    };
    #[cfg(not(target_arch = "riscv32"))]
    unimplemented!()
}

pub fn host_log(_msg_ptr: *const u8, _msg_len: usize) {
    const NEWLINE: &[u8] = b"\n";
    host_write(1, _msg_ptr, _msg_len);
    host_write(1, NEWLINE.as_ptr(), NEWLINE.len());
}

#[allow(dead_code)]
#[allow(unused_variables)]
pub fn host_write(fd: u32, msg_ptr: *const u8, msg_len: usize) -> u32 {
    #[cfg(target_arch = "riscv32")]
    unsafe {
        const HOST_ECALL_READ: u32 = 1;
        const MAX_IO_BYTES: u32 = 1024;

        if msg_len > MAX_IO_BYTES as usize {
            kpanic!(
                "host_write: msg_len {} exceeds MAX_IO_BYTES ({})",
                msg_len,
                MAX_IO_BYTES
            );
        }

        let syscall_name = b"risc0_zkvm_platform::syscall::nr::SYS_WRITE\0";
        let syscall_name_ptr = syscall_name.as_ptr() as u32;
        let _rlen: u32;
        let tmp = get_ureg(REG_A3);
        set_ureg(REG_A3, fd);
        let tmp2 = get_ureg(REG_A4);
        set_ureg(REG_A4, msg_ptr as u32);
        let tmp3 = get_ureg(REG_A5);
        set_ureg(REG_A5, msg_len as u32);
        unsafe {
            core::arch::asm!("ecall",
                in("a7") HOST_ECALL_READ,
                inout("a0") syscall_name_ptr => _rlen,  // fd = syscall name pointer
                in("a1") core::ptr::null_mut::<u8>(),
                in("a2") 0u32,
            )
        };
        // Read the result from registers a0, a1 (like read_a0_a1)
        let mut buf = [0u32, 0u32];
        let _rlen2: u32;
        unsafe {
            core::arch::asm!("ecall",
                in("a7") HOST_ECALL_READ,
                inout("a0") 0u32 => _rlen2,  // fd=0 to read cached values
                in("a1") buf.as_mut_ptr() as *mut u8,
                in("a2") core::mem::size_of_val(&buf) as u32,
            )
        };
        set_ureg(REG_A3, tmp);
        set_ureg(REG_A4, tmp2);
        set_ureg(REG_A5, tmp3);
        buf[0] // Return written length from a0
    }
    #[cfg(not(target_arch = "riscv32"))]
    {
        0
    }
}

#[allow(dead_code)]
pub fn host_argc() -> u32 {
    #[cfg(target_arch = "riscv32")]
    {
        const HOST_ECALL_READ: u32 = 1;

        // Create the syscall name string
        let syscall_name = b"risc0_zkvm_platform::syscall::nr::SYS_ARGC\0";
        let syscall_name_ptr = syscall_name.as_ptr() as u32;

        // First do the syscall to get argc (like host_syscall)
        let _rlen: u32;
        unsafe {
            core::arch::asm!("ecall",
                in("a7") HOST_ECALL_READ,
                inout("a0") syscall_name_ptr => _rlen,  // fd = syscall name pointer
                in("a1") core::ptr::null_mut::<u8>(),
                in("a2") 0u32,
            )
        };

        // Read the result from registers a0, a1 (like read_a0_a1)
        let mut buf = [0u32, 0u32];
        let _rlen2: u32;
        unsafe {
            core::arch::asm!("ecall",
                in("a7") HOST_ECALL_READ,
                inout("a0") 0u32 => _rlen2,  // fd=0 to read cached values
                in("a1") buf.as_mut_ptr() as *mut u8,
                in("a2") core::mem::size_of_val(&buf) as u32,
            )
        };

        buf[0] // Return argc from a0
    }
    #[cfg(not(target_arch = "riscv32"))]
    {
        0
    }
}

#[allow(dead_code)]
#[allow(unused_variables)]
pub fn host_get_cycle() -> u64 {
    #[cfg(target_arch = "riscv32")]
    {
        const HOST_ECALL_READ: u32 = 1;

        // Create the syscall name string
        let syscall_name = b"risc0_zkvm_platform::syscall::nr::SYS_CYCLE_COUNT\0";
        let syscall_name_ptr = syscall_name.as_ptr() as u32;

        // First do the syscall to get cycle count (like host_syscall)
        let _rlen: u32;
        unsafe {
            core::arch::asm!("ecall",
                in("a7") HOST_ECALL_READ,
                inout("a0") syscall_name_ptr => _rlen,  // fd = syscall name pointer
                in("a1") core::ptr::null_mut::<u8>(),
                in("a2") 0u32,
            )
        };

        // Read the result from registers a0, a1 (like read_a0_a1)
        let mut buf = [0u32, 0u32];
        let _rlen2: u32;
        unsafe {
            core::arch::asm!("ecall",
                in("a7") HOST_ECALL_READ,
                inout("a0") 0u32 => _rlen2,  // fd=0 to read cached values
                in("a1") buf.as_mut_ptr() as *mut u8,
                in("a2") core::mem::size_of_val(&buf) as u32,
            )
        };

        // Combine high (a0) and low (a1) parts into u64
        ((buf[0] as u64) << 32) | (buf[1] as u64)
    }
    #[cfg(not(target_arch = "riscv32"))]
    {
        0
    }
}

// XXX this needs review
#[allow(dead_code)]
pub fn host_read(fd: u32, buf: *mut u8, buf_len: usize) -> u32 {
    debug_print!("read {fd} {buf:?} {buf_len}");
    #[cfg(target_arch = "riscv32")]
    {
        const HOST_ECALL_READ: u32 = 1;
        const MAX_IO_BYTES: u32 = 1024;
        const WORD_SIZE: u32 = 4;

        if buf_len > MAX_IO_BYTES as usize {
            kpanic!(
                "host_read: buf_len {} exceeds MAX_IO_BYTES ({})",
                buf_len,
                MAX_IO_BYTES
            );
        }

        // Create the syscall name string
        let syscall_name = b"risc0_zkvm_platform::syscall::nr::SYS_READ\0";
        let syscall_name_ptr = syscall_name.as_ptr() as u32;

        let nbytes = buf_len as u32;
        let nwords = nbytes / WORD_SIZE;

        // First do the syscall to get argv (like host_syscall)
        let _rlen: u32;
        // XXX workaround for the risc0 bug
        let tmp: u32 = get_ureg(REG_A3);
        set_ureg(REG_A3, fd);
        let tmp2 = get_ureg(REG_A4);
        set_ureg(REG_A4, nbytes);
        let nbytes_main = (nbytes / WORD_SIZE) * WORD_SIZE;

        unsafe {
            core::arch::asm!("ecall",
                in("a7") HOST_ECALL_READ,
                inout("a0") syscall_name_ptr => _rlen,  // fd = syscall name pointer
                in("a1") buf,
                in("a2") nbytes_main,
                in("a3") fd,  // fd in a3; XXX: bug, the kernel side reads user reg
            )
        };
        set_ureg(REG_A3, tmp);
        set_ureg(REG_A4, tmp2);

        // Read the argument data into the buffer (like host_ecall_read_trunc)
        let mut retbuf = [0u32, 0u32];
        unsafe {
            core::arch::asm!("ecall",
                in("a7") HOST_ECALL_READ,
                in("a0") 0u32,  // fd=0 to read cached values
                in("a1") retbuf.as_mut_ptr() as *mut u8,
                in("a2") core::mem::size_of_val(&retbuf) as u32,
            )
        };
        // Handle unaligned bytes at the end
        if retbuf[0] > nbytes_main {
            let pos = nbytes_main as usize;
            let bytes_remain = ((buf_len as u32) - nbytes_main) as usize;
            let final_bytes = retbuf[1].to_le_bytes();
            // SAFETY: We are constructing a slice from the raw pointer `buf` with length `buf_len`.
            // The caller is responsible for ensuring that `buf` is valid for writes of `buf_len` bytes.
            let buf_slice = unsafe { core::slice::from_raw_parts_mut(buf, buf_len) };
            buf_slice[pos..pos + bytes_remain].copy_from_slice(&final_bytes[..bytes_remain]);
        }

        // Return the actual number of bytes read, not the buffer length
        retbuf[0] as u32
    }
    #[cfg(not(target_arch = "riscv32"))]
    {
        0
    }
}

#[allow(dead_code)]
pub fn host_argv(arg_index: u32, buf: *mut u8, buf_len: usize) -> u32 {
    debug_print!("host_argv {arg_index} {buf:?} {buf_len}");
    #[cfg(target_arch = "riscv32")]
    {
        const HOST_ECALL_READ: u32 = 1;
        const MAX_IO_BYTES: u32 = 1024;
        const WORD_SIZE: u32 = 4;

        if buf_len > MAX_IO_BYTES as usize {
            kpanic!(
                "host_argv: buf_len {} exceeds MAX_IO_BYTES ({})",
                buf_len,
                MAX_IO_BYTES
            );
        }

        // Create the syscall name string
        let syscall_name = b"risc0_zkvm_platform::syscall::nr::SYS_ARGV\0";
        let syscall_name_ptr = syscall_name.as_ptr() as u32;

        let nbytes = buf_len as u32;
        let nwords = nbytes / WORD_SIZE;

        // First do the syscall to get argv (like host_syscall)
        let _rlen: u32;
        // XXX workaround for the risc0 bug
        let tmp: u32 = get_ureg(REG_A3);
        set_ureg(REG_A3, arg_index);
        unsafe {
            core::arch::asm!("ecall",
                in("a7") HOST_ECALL_READ,
                inout("a0") syscall_name_ptr => _rlen,  // fd = syscall name pointer
                in("a1") buf,
                in("a2") nwords * WORD_SIZE,
                in("a3") arg_index,  // arg_index in a3; XXX: bug, the kernel side reads user reg
            )
        };
        set_ureg(REG_A3, tmp);

        // Read the argument data into the buffer (like host_ecall_read_trunc)
        let mut buf = [0u32, 0u32];
        unsafe {
            core::arch::asm!("ecall",
                in("a7") HOST_ECALL_READ,
                in("a0") 0u32,  // fd=0 to read cached values
                in("a1") buf.as_mut_ptr() as *mut u8,
                in("a2") core::mem::size_of_val(&buf) as u32,
            )
        };

        buf[0] // Return the length read
    }
    #[cfg(not(target_arch = "riscv32"))]
    {
        0
    }
}
