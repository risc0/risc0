use crate::kernel::{DEBUG_ENABLED, print};
use no_std_strings::{str_format, str256};

#[cfg(target_arch = "riscv32")]
use crate::constants::REG_A3;
#[cfg(target_arch = "riscv32")]
use crate::kernel::{get_ureg, set_ureg};

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
    #[cfg(target_arch = "riscv32")]
    unsafe {
        const HOST_ECALL_WRITE: u32 = 2;
        core::arch::asm!("ecall",
            in("a7") HOST_ECALL_WRITE,
            in("a0") 0,
            in("a1") _msg_ptr,
            in("a2") _msg_len,
        )
    };
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

#[allow(unused_variables)]
pub fn host_get_cycle() -> u64 {
    // Simple time counter implementation
    // In a real implementation, this would read from a hardware cycle counter
    // For now, we'll use a simple incrementing counter
    static mut CYCLE_COUNTER: u64 = 0;
    unsafe {
        CYCLE_COUNTER = CYCLE_COUNTER.wrapping_add(10000);
        CYCLE_COUNTER
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

        // Create the syscall name string
        let syscall_name = b"risc0_zkvm_platform::syscall::nr::SYS_ARGV\0";
        let syscall_name_ptr = syscall_name.as_ptr() as u32;

        // Truncate buffer size to MAX_IO_BYTES
        let nbytes = core::cmp::min(buf_len as u32, MAX_IO_BYTES);
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
