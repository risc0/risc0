#![allow(dead_code)]

pub const REG_SP: usize = 2;
pub const REG_A0: usize = 10;
pub const REG_A1: usize = 11;
pub const REG_A2: usize = 12;
pub const REG_A3: usize = 13;
pub const REG_A4: usize = 14;
pub const REG_A5: usize = 15;
pub const REG_A6: usize = 16;
pub const REG_A7: usize = 17;

// Floating point register pub constants
pub const NUM_FP_REGS: usize = 32;
#[allow(dead_code)]
pub const FP_REG_SIZE: usize = 8; // 64-bit registers
#[allow(dead_code)]
pub const FP_REGS_SIZE: usize = NUM_FP_REGS * FP_REG_SIZE; // 256 bytes total

pub const USER_REGS_PTR: *mut u32 = 0xffff_0080 as *mut u32;
pub const MEPC_PTR: *mut usize = 0xffff_0200 as *mut usize;
// Floating point register storage area (32 x 64-bit registers = 256 bytes)
pub const FP_REGS_PTR: *mut u64 = 0xffff_a000 as *mut u64;
// Floating point control and status register (FCSR) storage
#[allow(dead_code)]
pub const FCSR_PTR: *mut u32 = 0xffff_a100 as *mut u32;
// Memory layout constants for RISC-V RV32 in zkOS
// The address space is divided into:
// - User space: 0x00000000 - 0xBFFFFFFF (3GB)
// - Kernel space: 0xC0000000 - 0xFFFFFFFF (1GB)

/// Start of kernel memory space (3GB boundary)
pub const KERNEL_SPACE_START: u32 = 0xC000_0000;

/// End of user memory space (just before kernel space)
pub const USER_SPACE_END: u32 = 0xC000_0000;

pub const USER_MEMORY_START_PTR: *const u8 = 0x0001_1100 as *const u8;
pub const USER_MEMORY_LENGTH: usize = 0x4000_0000;
pub const USER_START_PTR: *const usize = 0x0001_0000 as *const usize;
pub const USER_STACK_ADDR: usize = 0x9c7ffe00;
pub const USER_STACK_PTR: *const usize = USER_STACK_ADDR as *const usize;
pub const USER_FIXUP_ADDR: usize = 0xbfff_0000;
pub const USER_FIXUP_PTR: *mut u32 = USER_FIXUP_ADDR as *mut u32;
#[allow(dead_code)]
pub const USER_STACK_SIZE: usize = 2 * 1024 * 1024;

#[allow(dead_code)]
pub const USER_PHENT_SIZE: usize = 32; // ELF32_Phdr size in bytes

pub const PAGE_SIZE: usize = 4096;
// pub const AT_VECTOR_SIZE_BASE: usize = 20;
// pub const AT_VECTOR_SIZE_ARCH: usize = 7;
// pub const AT_VECTOR_SIZE: usize = 2 * (AT_VECTOR_SIZE_ARCH + AT_VECTOR_SIZE_BASE + 1);
pub const ASCII_TABLE_PTR: *const u8 = 0xbf00_0200 as *const u8;

/// Program header table address (stored in memory)
#[allow(dead_code)]
pub const USER_PHDR_ADDR_PTR: *const usize = 0xffff_3000 as *const usize;
/// Program header count address (stored in memory)
#[allow(dead_code)]
pub const USER_PHDR_NUM_ADDR_PTR: *const usize = 0xffff_3008 as *const usize;

/// Interpreter base address (stored in memory)
pub const USER_INTERP_BASE_ADDR: *const usize = 0xffff_3010 as *const usize;

/// Interpreter address (stored in memory)
pub const USER_INTERP_ADDR: *const usize = 0xffff_3018 as *const usize;

/// Brk address (stored in memory)
pub const USER_BRK_ADDR: *const usize = 0xffff_3020 as *const usize;

/// Filesystem image address (set by elf-to-bin tool)
pub const FILESYSTEM_IMAGE_ADDR_PTR: *const u32 = 0xffff_3030 as *const u32;

// Shadow register storage area for supervisor CSRs (starting at 0xffff_b000)
pub const SHADOW_REGS_PTR: *mut u32 = 0xffff_b000 as *mut u32;

// Supervisor CSR offsets within shadow register area
pub const STVEC_OFFSET: usize = 0; // Supervisor trap vector base address
pub const SSCRATCH_OFFSET: usize = 1; // Supervisor scratch register
pub const SDELEG_OFFSET: usize = 2; // Supervisor delegation register
pub const SIE_OFFSET: usize = 3; // Supervisor interrupt enable
pub const SIP_OFFSET: usize = 4; // Supervisor interrupt pending
pub const SCOUNTEREN_OFFSET: usize = 5; // Supervisor counter enable
pub const SSTATUS_OFFSET: usize = 6; // Supervisor status register
pub const SEPC_OFFSET: usize = 7; // Supervisor exception program counter
pub const STVAL_OFFSET: usize = 8; // Supervisor trap value
pub const SCAUSE_OFFSET: usize = 9; // Supervisor cause register
pub const SENVCFG_OFFSET: usize = 10; // Supervisor environment configuration
pub const ILRSC_OFFSET: usize = 11; // Instruction LR/SC register
pub const ILRSC_SET_OFFSET: usize = 12; // Instruction LR/SC set register
pub const VM_MACHINE_MODE: usize = 13; // 0 = linux abi, 1 = emulated s-mode 2 = emulated u-mode
pub const MEPC_FIXUP_OFFSET: usize = 14; // MEPC fixup offset
pub const VM_MACHINE_MODE_LINUX_ABI: u32 = 0;
pub const VM_MACHINE_MODE_EMULATED_S_MODE: u32 = 1;
pub const VM_MACHINE_MODE_EMULATED_U_MODE: u32 = 2;

// Kernel heap constants
// Memory layout: Stack (0xfff00000, grows DOWN) → Gap → Heap (16MB fixed) → FS (variable) → User Space
// Stack needs room to grow down, so heap must end BEFORE stack top
pub const KERNEL_STACK_TOP: usize = 0xfff00000;
pub const KERNEL_STACK_MAX_SIZE: usize = 1024 * 1024; // Assume max 1MB stack growth
pub const KERNEL_HEAP_STACK_GAP: usize = 1024 * 1024; // 1MB safety gap between heap and stack
pub const KERNEL_HEAP_SIZE: usize = 16 * 1024 * 1024; // 16MB heap (fixed)
// Heap ends before stack bottom to leave room for stack growth
pub const KERNEL_HEAP_END_ADDR: usize =
    KERNEL_STACK_TOP - KERNEL_STACK_MAX_SIZE - KERNEL_HEAP_STACK_GAP;
pub const KERNEL_HEAP_START_ADDR: usize = KERNEL_HEAP_END_ADDR - KERNEL_HEAP_SIZE; // 0xfed00000

/// Timestamp structure for the timestamps in struct statx
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct StatxTimestamp {
    pub tv_sec: i64,     // Number of seconds before/after 00:00:00 1st January 1970 UTC
    pub tv_nsec: u32,    // Number of nanoseconds (0..999,999,999) after tv_sec
    pub __reserved: i32, // Reserved for future use
}

/// Extended file attribute structure for statx() system call
/// Based on Linux stat.h structure
#[repr(C)]
#[derive(Debug, Clone, Copy, PartialEq, Eq)]
pub struct Statx {
    // 0x00
    pub stx_mask: u32,       // What results were written [uncond]
    pub stx_blksize: u32,    // Preferred general I/O size [uncond]
    pub stx_attributes: u64, // Flags conveying information about the file [uncond]
    // 0x10
    pub stx_nlink: u32,     // Number of hard links
    pub stx_uid: u32,       // User ID of owner
    pub stx_gid: u32,       // Group ID of owner
    pub stx_mode: u16,      // File mode
    pub __spare0: [u16; 1], // Spare space
    // 0x20
    pub stx_ino: u64,             // Inode number
    pub stx_size: u64,            // File size
    pub stx_blocks: u64,          // Number of 512-byte blocks allocated
    pub stx_attributes_mask: u64, // Mask to show what's supported in stx_attributes
    // 0x40
    pub stx_atime: StatxTimestamp, // Last access time
    pub stx_btime: StatxTimestamp, // File creation time
    pub stx_ctime: StatxTimestamp, // Last attribute change time
    pub stx_mtime: StatxTimestamp, // Last data modification time
    // 0x80
    pub stx_rdev_major: u32, // Device ID of special file [if bdev/cdev]
    pub stx_rdev_minor: u32,
    pub stx_dev_major: u32, // ID of device containing file [uncond]
    pub stx_dev_minor: u32,
    // 0x90
    pub stx_mnt_id: u64,
    pub stx_dio_mem_align: u32, // Memory buffer alignment for direct I/O
    pub stx_dio_offset_align: u32, // File offset alignment for direct I/O
    // 0xa0
    pub __spare3: [u64; 12], // Spare space for future expansion
                             // 0x100
}

// STATX mask flags
pub const STATX_TYPE: u32 = 0x00000001; // Want/got stx_mode & S_IFMT
pub const STATX_MODE: u32 = 0x00000002; // Want/got stx_mode & ~S_IFMT
pub const STATX_NLINK: u32 = 0x00000004; // Want/got stx_nlink
pub const STATX_UID: u32 = 0x00000008; // Want/got stx_uid
pub const STATX_GID: u32 = 0x00000010; // Want/got stx_gid
pub const STATX_ATIME: u32 = 0x00000020; // Want/got stx_atime
pub const STATX_MTIME: u32 = 0x00000040; // Want/got stx_mtime
pub const STATX_CTIME: u32 = 0x00000080; // Want/got stx_ctime
pub const STATX_INO: u32 = 0x00000100; // Want/got stx_ino
pub const STATX_SIZE: u32 = 0x00000200; // Want/got stx_size
pub const STATX_BLOCKS: u32 = 0x00000400; // Want/got stx_blocks
pub const STATX_BASIC_STATS: u32 = 0x000007ff; // The stuff in the normal stat struct
pub const STATX_BTIME: u32 = 0x00000800; // Want/got stx_btime
pub const STATX_MNT_ID: u32 = 0x00001000; // Got stx_mnt_id
pub const STATX_DIOALIGN: u32 = 0x00002000; // Want/got direct I/O alignment info
pub const STATX_RESERVED: u32 = 0x80000000; // Reserved for future struct statx expansion
pub const STATX_ALL: u32 = 0x00000fff; // All basic stats + btime

// File type flags (S_IFMT)
pub const S_IFMT: u32 = 0o170000; // File type mask
pub const S_IFSOCK: u32 = 0o140000; // Socket
pub const S_IFLNK: u32 = 0o120000; // Symbolic link
pub const S_IFREG: u32 = 0o100000; // Regular file
pub const S_IFBLK: u32 = 0o060000; // Block device
pub const S_IFDIR: u32 = 0o040000; // Directory
pub const S_IFCHR: u32 = 0o020000; // Character device
pub const S_IFIFO: u32 = 0o010000; // FIFO/pipe
