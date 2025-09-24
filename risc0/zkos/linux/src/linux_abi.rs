use crate::{
    constants::{
        ASCII_TABLE_PTR, MEPC_PTR, PAGE_SIZE, REG_A0, REG_A1, REG_A2, REG_A3, REG_A4, REG_A5,
        REG_A7, REG_SP, USER_HEAP_SIZE, USER_HEAP_START_ADDR, USER_HEAP_START_PTR,
        USER_MEMORY_LENGTH, USER_MEMORY_START_PTR, USER_PHDR_ADDR_PTR, USER_PHDR_NUM_ADDR_PTR,
        USER_PHENT_SIZE, USER_STACK_PTR, USER_START_PTR,
    },
    host_calls::{host_argv, host_log, host_terminate},
    kernel::{get_ureg, mret, print},
    linux_abi_fs::{
        attach_to_p9, get_p9_enabled, load_file_aligned_to_page_size, set_fd, set_p9_enabled,
        sys_statx,
    },
};
use elf::{ElfBytes, abi::PT_INTERP, endian::LittleEndian, file::Class};

use crate::kernel::set_ureg;
use no_std_strings::{str_format, str256};

// Import socket syscalls from the socket module
use crate::linux_abi_sockets::{
    sys_accept, sys_accept4, sys_bind, sys_connect, sys_getpeername, sys_getsockname,
    sys_getsockopt, sys_listen, sys_recvfrom, sys_recvmmsg_time64, sys_recvmsg, sys_sendmmsg,
    sys_sendmsg, sys_sendto, sys_setsockopt, sys_shutdown, sys_socket, sys_socketpair,
};

// Import privileged syscalls from the privileged module
use crate::linux_abi_privileged::{
    sys_acct, sys_add_key, sys_bpf, sys_capget, sys_capset, sys_chroot, sys_clock_adjtime64,
    sys_clock_settime64, sys_delete_module, sys_finit_module, sys_init_module, sys_kexec_file_load,
    sys_kexec_load, sys_keyctl, sys_landlock_add_rule, sys_landlock_create_ruleset,
    sys_landlock_restrict_self, sys_mount, sys_mount_setattr, sys_reboot, sys_setns, sys_swapoff,
    sys_swapon, sys_umount2, sys_vhangup,
};

// Import filesystem syscalls from the filesystem module
use crate::linux_abi_fs::{
    sys_chdir, sys_close, sys_dup, sys_dup3, sys_faccessat, sys_faccessat2, sys_fadvise64_64,
    sys_fallocate, sys_fanotify_init, sys_fanotify_mark, sys_fcntl64, sys_getdents64, sys_openat,
    sys_read, sys_write, sys_writev,
};

static mut BRK: u32 = USER_HEAP_START_ADDR as u32;

#[cfg(target_arch = "riscv32")]
use alloc::string::String;
#[cfg(target_arch = "riscv32")]
use alloc::string::ToString;
#[cfg(target_arch = "riscv32")]
use alloc::vec;
#[cfg(target_arch = "riscv32")]
use alloc::vec::Vec;

use core::{alloc::Layout, ptr::NonNull, str};
use rlsf::Tlsf;

type Heap = Tlsf<'static, usize, usize, { usize::BITS as usize }, { usize::BITS as usize }>;
static mut HEAP: Heap = Heap::new();

pub const SYS_IOCTL: u32 = 29;
pub const SYS_READ: u32 = 63;
pub const SYS_WRITE: u32 = 64;
pub const SYS_WRITEV: u32 = 66;
pub const SYS_EXIT: u32 = 93;
pub const SYS_EXIT_GROUP: u32 = 94;
pub const SYS_SET_TID_ADDRESS: u32 = 96;
pub const SYS_TKILL: u32 = 130;
pub const SYS_SIGALTSTACK: u32 = 132;
pub const SYS_RT_SIGACTION: u32 = 134;
pub const SYS_RT_SIGPROCMASK: u32 = 135;
pub const SYS_BRK: u32 = 214;
pub const SYS_MUNMAP: u32 = 215;
pub const SYS_MMAP: u32 = 222;

// Additional syscalls
pub const SYS_ACCEPT: u32 = 202;
pub const SYS_ACCEPT4: u32 = 242;
pub const SYS_ACCT: u32 = 89;
pub const SYS_ADD_KEY: u32 = 217;
pub const SYS_BIND: u32 = 200;
pub const SYS_BPF: u32 = 280;
pub const SYS_CACHESTAT: u32 = 451;
pub const SYS_CAPGET: u32 = 90;
pub const SYS_CAPSET: u32 = 91;
pub const SYS_CHDIR: u32 = 49;
pub const SYS_CHROOT: u32 = 51;
pub const SYS_CLOCK_ADJTIME64: u32 = 405;
pub const SYS_CLOCK_GETRES_TIME64: u32 = 406;
pub const SYS_CLOCK_GETTIME64: u32 = 403;
pub const SYS_CLOCK_NANOSLEEP_TIME64: u32 = 407;
pub const SYS_CLOCK_SETTIME64: u32 = 404;
pub const SYS_CLONE: u32 = 220;
pub const SYS_CLONE3: u32 = 435;
pub const SYS_CLOSE: u32 = 57;
pub const SYS_CLOSE_RANGE: u32 = 436;
pub const SYS_CONNECT: u32 = 203;
pub const SYS_COPY_FILE_RANGE: u32 = 285;
pub const SYS_DELETE_MODULE: u32 = 106;
pub const SYS_DUP: u32 = 23;
pub const SYS_DUP3: u32 = 24;
pub const SYS_EPOLL_CREATE1: u32 = 20;
pub const SYS_EPOLL_CTL: u32 = 21;
pub const SYS_EPOLL_PWAIT: u32 = 22;
pub const SYS_EPOLL_PWAIT2: u32 = 441;
pub const SYS_EVENTFD2: u32 = 19;
pub const SYS_EXECVE: u32 = 221;
pub const SYS_EXECVEAT: u32 = 281;
pub const SYS_FACCESSAT: u32 = 48;
pub const SYS_FACCESSAT2: u32 = 439;
pub const SYS_FADVISE64_64: u32 = 223;
pub const SYS_FALLOCATE: u32 = 47;
pub const SYS_FANOTIFY_INIT: u32 = 262;
pub const SYS_FANOTIFY_MARK: u32 = 263;
pub const SYS_FCHDIR: u32 = 50;
pub const SYS_FCHMOD: u32 = 52;
pub const SYS_FCHMODAT: u32 = 53;
pub const SYS_FCHMODAT2: u32 = 452;
pub const SYS_FCHOWN: u32 = 55;
pub const SYS_FCHOWNAT: u32 = 54;
pub const SYS_FCNTL64: u32 = 25;
pub const SYS_FDATASYNC: u32 = 83;
pub const SYS_FGETXATTR: u32 = 10;
pub const SYS_FILE_GETATTR: u32 = 468;
pub const SYS_FILE_SETATTR: u32 = 469;
pub const SYS_FINIT_MODULE: u32 = 273;
pub const SYS_FLISTXATTR: u32 = 13;
pub const SYS_FLOCK: u32 = 32;
pub const SYS_FREMOVEXATTR: u32 = 16;
pub const SYS_FSCONFIG: u32 = 431;
pub const SYS_FSETXATTR: u32 = 7;
pub const SYS_FSMOUNT: u32 = 432;
pub const SYS_FSOPEN: u32 = 430;
pub const SYS_FSPICK: u32 = 433;
pub const SYS_FSTATFS64: u32 = 44;
pub const SYS_FSYNC: u32 = 82;
pub const SYS_FTRUNCATE64: u32 = 46;
pub const SYS_FUTEX_REQUEUE: u32 = 456;
pub const SYS_FUTEX_TIME64: u32 = 422;
pub const SYS_FUTEX_WAIT: u32 = 455;
pub const SYS_FUTEX_WAITV: u32 = 449;
pub const SYS_FUTEX_WAKE: u32 = 454;
pub const SYS_GET_MEMPOLICY: u32 = 236;
pub const SYS_GET_ROBUST_LIST: u32 = 100;
pub const SYS_GETCPU: u32 = 168;
pub const SYS_GETCWD: u32 = 17;
pub const SYS_GETDENTS64: u32 = 61;
pub const SYS_GETEGID: u32 = 177;
pub const SYS_GETEUID: u32 = 175;
pub const SYS_GETGID: u32 = 176;
pub const SYS_GETGROUPS: u32 = 158;
pub const SYS_GETITIMER: u32 = 102;
pub const SYS_GETPEERNAME: u32 = 205;
pub const SYS_GETPGID: u32 = 155;
pub const SYS_GETPID: u32 = 172;
pub const SYS_GETPPID: u32 = 173;
pub const SYS_GETPRIORITY: u32 = 141;
pub const SYS_GETRANDOM: u32 = 278;
pub const SYS_GETRESGID: u32 = 150;
pub const SYS_GETRESUID: u32 = 148;
pub const SYS_GETRUSAGE: u32 = 165;
pub const SYS_GETSID: u32 = 156;
pub const SYS_GETSOCKNAME: u32 = 204;
pub const SYS_GETSOCKOPT: u32 = 209;
pub const SYS_GETTID: u32 = 178;
pub const SYS_GETUID: u32 = 174;
pub const SYS_GETXATTR: u32 = 8;
pub const SYS_GETXATTRAT: u32 = 464;
pub const SYS_INIT_MODULE: u32 = 105;
pub const SYS_INOTIFY_ADD_WATCH: u32 = 27;
pub const SYS_INOTIFY_INIT1: u32 = 26;
pub const SYS_INOTIFY_RM_WATCH: u32 = 28;
pub const SYS_IO_CANCEL: u32 = 3;
pub const SYS_IO_DESTROY: u32 = 1;
pub const SYS_IO_PGETEVENTS_TIME64: u32 = 416;
pub const SYS_IO_SETUP: u32 = 0;
pub const SYS_IO_SUBMIT: u32 = 2;
pub const SYS_IO_URING_ENTER: u32 = 426;
pub const SYS_IO_URING_REGISTER: u32 = 427;
pub const SYS_IO_URING_SETUP: u32 = 425;
pub const SYS_IOPRIO_GET: u32 = 31;
pub const SYS_IOPRIO_SET: u32 = 30;
pub const SYS_KCMP: u32 = 272;
pub const SYS_KEXEC_FILE_LOAD: u32 = 294;
pub const SYS_KEXEC_LOAD: u32 = 104;
pub const SYS_KEYCTL: u32 = 219;
pub const SYS_KILL: u32 = 129;
pub const SYS_LANDLOCK_ADD_RULE: u32 = 445;
pub const SYS_LANDLOCK_CREATE_RULESET: u32 = 444;
pub const SYS_LANDLOCK_RESTRICT_SELF: u32 = 446;
pub const SYS_LGETXATTR: u32 = 9;
pub const SYS_LINKAT: u32 = 37;
pub const SYS_LISTEN: u32 = 201;
pub const SYS_LISTMOUNT: u32 = 458;
pub const SYS_LISTXATTR: u32 = 11;
pub const SYS_LISTXATTRAT: u32 = 465;
pub const SYS_LLISTXATTR: u32 = 12;
pub const SYS_LLSEEK: u32 = 62;
pub const SYS_LOOKUP_DCOOKIE: u32 = 18;
pub const SYS_LREMOVEXATTR: u32 = 15;
pub const SYS_LSETXATTR: u32 = 6;
pub const SYS_LSM_GET_SELF_ATTR: u32 = 459;
pub const SYS_LSM_LIST_MODULES: u32 = 461;
pub const SYS_LSM_SET_SELF_ATTR: u32 = 460;
pub const SYS_MADVISE: u32 = 233;
pub const SYS_MAP_SHADOW_STACK: u32 = 453;
pub const SYS_MBIND: u32 = 235;
pub const SYS_MEMBARRIER: u32 = 283;
pub const SYS_MEMFD_CREATE: u32 = 279;
pub const SYS_MEMFD_SECRET: u32 = 447;
pub const SYS_MIGRATE_PAGES: u32 = 238;
pub const SYS_MINCORE: u32 = 232;
pub const SYS_MKDIRAT: u32 = 34;
pub const SYS_MKNODAT: u32 = 33;
pub const SYS_MLOCK: u32 = 228;
pub const SYS_MLOCK2: u32 = 284;
pub const SYS_MLOCKALL: u32 = 230;
pub const SYS_MOUNT: u32 = 40;
pub const SYS_MOUNT_SETATTR: u32 = 442;
pub const SYS_MOVE_MOUNT: u32 = 429;
pub const SYS_MOVE_PAGES: u32 = 239;
pub const SYS_MPROTECT: u32 = 226;
pub const SYS_MQ_GETSETATTR: u32 = 185;
pub const SYS_MQ_NOTIFY: u32 = 184;
pub const SYS_MQ_OPEN: u32 = 180;
pub const SYS_MQ_TIMEDRECEIVE_TIME64: u32 = 419;
pub const SYS_MQ_TIMEDSEND_TIME64: u32 = 418;
pub const SYS_MQ_UNLINK: u32 = 181;
pub const SYS_MREMAP: u32 = 216;
pub const SYS_MSEAL: u32 = 462;
pub const SYS_MSGCTL: u32 = 187;
pub const SYS_MSGGET: u32 = 186;
pub const SYS_MSGRCV: u32 = 188;
pub const SYS_MSGSND: u32 = 189;
pub const SYS_MSYNC: u32 = 227;
pub const SYS_MUNLOCK: u32 = 229;
pub const SYS_MUNLOCKALL: u32 = 231;
pub const SYS_NAME_TO_HANDLE_AT: u32 = 264;
pub const SYS_OPEN_BY_HANDLE_AT: u32 = 265;
pub const SYS_OPEN_TREE: u32 = 428;
pub const SYS_OPEN_TREE_ATTR: u32 = 467;
pub const SYS_OPENAT: u32 = 56;
pub const SYS_OPENAT2: u32 = 437;
pub const SYS_PERF_EVENT_OPEN: u32 = 241;
pub const SYS_PERSONALITY: u32 = 92;
pub const SYS_PIDFD_GETFD: u32 = 438;
pub const SYS_PIDFD_OPEN: u32 = 434;
pub const SYS_PIDFD_SEND_SIGNAL: u32 = 424;
pub const SYS_PIPE2: u32 = 59;
pub const SYS_PIVOT_ROOT: u32 = 41;
pub const SYS_PKEY_ALLOC: u32 = 289;
pub const SYS_PKEY_FREE: u32 = 290;
pub const SYS_PKEY_MPROTECT: u32 = 288;
pub const SYS_PPOLL_TIME64: u32 = 414;
pub const SYS_PRCTL: u32 = 167;
pub const SYS_PREAD64: u32 = 67;
pub const SYS_PREADV: u32 = 69;
pub const SYS_PREADV2: u32 = 286;
pub const SYS_PRLIMIT64: u32 = 261;
pub const SYS_PROCESS_MADVISE: u32 = 440;
pub const SYS_PROCESS_MRELEASE: u32 = 448;
pub const SYS_PROCESS_VM_READV: u32 = 270;
pub const SYS_PROCESS_VM_WRITEV: u32 = 271;
pub const SYS_PSELECT6_TIME64: u32 = 413;
pub const SYS_PTRACE: u32 = 117;
pub const SYS_PWRITE64: u32 = 68;
pub const SYS_PWRITEV: u32 = 70;
pub const SYS_PWRITEV2: u32 = 287;
pub const SYS_QUOTACTL: u32 = 60;
pub const SYS_QUOTACTL_FD: u32 = 443;
pub const SYS_READAHEAD: u32 = 213;
pub const SYS_READLINKAT: u32 = 78;
pub const SYS_READV: u32 = 65;
pub const SYS_REBOOT: u32 = 142;
pub const SYS_RECVFROM: u32 = 207;
pub const SYS_RECVMMSG_TIME64: u32 = 417;
pub const SYS_RECVMSG: u32 = 212;
pub const SYS_REMAP_FILE_PAGES: u32 = 234;
pub const SYS_REMOVEXATTR: u32 = 14;
pub const SYS_REMOVEXATTRAT: u32 = 466;
pub const SYS_RENAMEAT2: u32 = 276;
pub const SYS_REQUEST_KEY: u32 = 218;
pub const SYS_RESTART_SYSCALL: u32 = 128;
pub const SYS_RISCV_FLUSH_ICACHE: u32 = 259;
pub const SYS_RISCV_HWPROBE: u32 = 258;
pub const SYS_RSEQ: u32 = 293;
pub const SYS_RT_SIGPENDING: u32 = 136;
pub const SYS_RT_SIGQUEUEINFO: u32 = 138;
pub const SYS_RT_SIGRETURN: u32 = 139;
pub const SYS_RT_SIGSUSPEND: u32 = 133;
pub const SYS_RT_SIGTIMEDWAIT_TIME64: u32 = 421;
pub const SYS_RT_TGSIGQUEUEINFO: u32 = 240;
pub const SYS_SCHED_GET_PRIORITY_MAX: u32 = 125;
pub const SYS_SCHED_GET_PRIORITY_MIN: u32 = 126;
pub const SYS_SCHED_GETAFFINITY: u32 = 123;
pub const SYS_SCHED_GETATTR: u32 = 275;
pub const SYS_SCHED_GETPARAM: u32 = 121;
pub const SYS_SCHED_GETSCHEDULER: u32 = 120;
pub const SYS_SCHED_RR_GET_INTERVAL_TIME64: u32 = 423;
pub const SYS_SCHED_SETAFFINITY: u32 = 122;
pub const SYS_SCHED_SETATTR: u32 = 274;
pub const SYS_SCHED_SETPARAM: u32 = 118;
pub const SYS_SCHED_SETSCHEDULER: u32 = 119;
pub const SYS_SCHED_YIELD: u32 = 124;
pub const SYS_SECCOMP: u32 = 277;
pub const SYS_SEMCTL: u32 = 191;
pub const SYS_SEMGET: u32 = 190;
pub const SYS_SEMOP: u32 = 193;
pub const SYS_SEMTIMEDOP_TIME64: u32 = 420;
pub const SYS_SENDFILE64: u32 = 71;
pub const SYS_SENDMMSG: u32 = 269;
pub const SYS_SENDMSG: u32 = 211;
pub const SYS_SENDTO: u32 = 206;
pub const SYS_SET_MEMPOLICY: u32 = 237;
pub const SYS_SET_MEMPOLICY_HOME_NODE: u32 = 450;
pub const SYS_SET_ROBUST_LIST: u32 = 99;
pub const SYS_SETDOMAINNAME: u32 = 162;
pub const SYS_SETFSGID: u32 = 152;
pub const SYS_SETFSUID: u32 = 151;
pub const SYS_SETGID: u32 = 144;
pub const SYS_SETGROUPS: u32 = 159;
pub const SYS_SETHOSTNAME: u32 = 161;
pub const SYS_SETITIMER: u32 = 103;
pub const SYS_SETNS: u32 = 268;
pub const SYS_SETPGID: u32 = 154;
pub const SYS_SETPRIORITY: u32 = 140;
pub const SYS_SETREGID: u32 = 143;
pub const SYS_SETRESGID: u32 = 149;
pub const SYS_SETRESUID: u32 = 147;
pub const SYS_SETREUID: u32 = 145;
pub const SYS_SETSID: u32 = 157;
pub const SYS_SETSOCKOPT: u32 = 208;
pub const SYS_SETUID: u32 = 146;
pub const SYS_SETXATTR: u32 = 5;
pub const SYS_SETXATTRAT: u32 = 463;
pub const SYS_SHMAT: u32 = 196;
pub const SYS_SHMCTL: u32 = 195;
pub const SYS_SHDT: u32 = 197;
pub const SYS_SHMGET: u32 = 194;
pub const SYS_SHUTDOWN: u32 = 210;
pub const SYS_SIGNALFD4: u32 = 74;
pub const SYS_SOCKET: u32 = 198;
pub const SYS_SOCKETPAIR: u32 = 199;
pub const SYS_SPLICE: u32 = 76;
pub const SYS_STATFS64: u32 = 43;
pub const SYS_STATMOUNT: u32 = 457;
pub const SYS_STATX: u32 = 291;
pub const SYS_SWAPOFF: u32 = 225;
pub const SYS_SWAPON: u32 = 224;
pub const SYS_SYMLINKAT: u32 = 36;
pub const SYS_SYNC: u32 = 81;
pub const SYS_SYNC_FILE_RANGE: u32 = 84;
pub const SYS_SYNCFS: u32 = 267;
pub const SYS_SYSINFO: u32 = 179;
pub const SYS_SYSLOG: u32 = 116;
pub const SYS_TEE: u32 = 77;
pub const SYS_TGKILL: u32 = 131;
pub const SYS_TIMER_CREATE: u32 = 107;
pub const SYS_TIMER_DELETE: u32 = 111;
pub const SYS_TIMER_GETOVERRUN: u32 = 109;
pub const SYS_TIMER_GETTIME64: u32 = 408;
pub const SYS_TIMER_SETTIME64: u32 = 409;
pub const SYS_TIMERFD_CREATE: u32 = 85;
pub const SYS_TIMERFD_GETTIME64: u32 = 410;
pub const SYS_TIMERFD_SETTIME64: u32 = 411;
pub const SYS_TIMES: u32 = 153;
pub const SYS_TRUNCATE64: u32 = 45;
pub const SYS_UMASK: u32 = 166;
pub const SYS_UMOUNT2: u32 = 39;
pub const SYS_UNAME: u32 = 160;
pub const SYS_UNLINKAT: u32 = 35;
pub const SYS_UNSHARE: u32 = 97;
pub const SYS_USERFAULTFD: u32 = 282;
pub const SYS_UTIMENSAT_TIME64: u32 = 412;
pub const SYS_VHANGUP: u32 = 58;
pub const SYS_VMSPLICE: u32 = 75;
pub const SYS_WAITID: u32 = 95;

#[derive(Clone, Copy)]
pub enum Err {
    NoMem = -12,
    Inval = -22,
    FileNotFound = -2,
    NoSys = -38, // ENOSYS - Function not implemented
}

impl Err {
    pub fn as_errno(&self) -> u32 {
        *self as u32
    }
}

#[allow(unused)]
enum AuxType {
    Null = 0,
    Ignore = 1,
    ExecFd = 2,
    Phdr = 3,
    PhEnt = 4,
    PhNum = 5,
    PageSz = 6,
    Base = 7,
    Flags = 8,
    Entry = 9,
    NotElf = 10,
    Uid = 11,
    EUid = 12,
    Gid = 13,
    EGid = 14,
    Platform = 15,
    HwCap = 16,
    ClkTck = 17,
    Secure = 23,
    BasePlatform = 24,
    Random = 25,
    HwCap2 = 26,
    ExecFn = 31,
    SysInfo = 32,
    SysInfoEhdr = 33,
}

struct UserStack {
    sp: *mut usize,
    strs_ptr: *mut u8,
}

impl UserStack {
    fn new() -> Self {
        Self {
            sp: USER_STACK_PTR as *mut usize,
            strs_ptr: ASCII_TABLE_PTR as *mut u8,
        }
    }

    fn add_word(&mut self, word: usize) {
        unsafe {
            self.sp.write_volatile(word);
            self.sp = self.sp.add(1);
        }
    }

    #[allow(dead_code)]
    fn add_null(&mut self) {
        self.add_word(0);
    }

    #[allow(dead_code)]
    fn add_aux_word(&mut self, atype: AuxType, word: usize) {
        self.add_word(atype as usize);
        self.add_word(word);
    }

    fn add_str(&mut self, str: &[u8]) {
        let strs_ptr = self.strs_ptr;
        unsafe {
            strs_ptr.copy_from(str.as_ptr(), str.len());
            self.strs_ptr = strs_ptr.add(str.len() + 1);
        }
        self.add_word(strs_ptr as usize);
    }
}

pub fn allocate_aligned_to_page_size(file_size: u64) -> *const u8 {
    #[allow(static_mut_refs)]
    let ptr = unsafe {
        let layout = Layout::from_size_align(file_size as usize, PAGE_SIZE).unwrap_unchecked();
        let ptr = HEAP.allocate(layout).unwrap().as_ptr();
        if !ptr.is_null() {
            ptr.write_bytes(0, layout.size());
        }
        ptr
    };
    ptr
}

pub fn start_linux_binary(argc: u32) -> ! {
    set_fd(0, 0xFFFF_FFFE);
    set_fd(1, 0xFFFF_FFFE);
    set_fd(2, 0xFFFF_FFFE);

    let mut stack = UserStack::new();
    stack.add_word(argc as usize);

    // XXX we should review this code from a security perspective
    // Get each argument from host and add to stack
    let mut argv = vec![];
    for i in 0..argc {
        let mut arg_buffer = [0u32; 256]; // 1024 bytes as u32 array for proper alignment
        let arg_len = host_argv(i, arg_buffer.as_mut_ptr() as *mut u8, arg_buffer.len() * 4);
        // we want to make this string null-terminated, so we add 1 to the length
        let arg_len = arg_len + 1;
        if arg_len > 0 && arg_len <= (arg_buffer.len() * 4) as u32 {
            // Create a byte slice with the actual argument length
            let arg_bytes: &[u8] = bytemuck::cast_slice(&arg_buffer);
            let arg_slice = &arg_bytes[..arg_len as usize];
            // Print the argument as a string (not null-terminated, may not be valid UTF-8)
            // Now arg_slice is a null-terminated string; trim at the first null for display.
            let nul_pos = arg_slice
                .iter()
                .position(|&b| b == 0)
                .unwrap_or(arg_slice.len());
            let arg_str = &arg_slice[..nul_pos];
            argv.push(String::from_utf8(arg_str.to_vec()).unwrap());
        }
    }

    if !argv.is_empty() {
        if argv[0].starts_with("opts=p9") {
            set_p9_enabled(true);
        } else {
            set_p9_enabled(false);
        }
        argv.remove(0);
    }

    if get_p9_enabled() {
        attach_to_p9();
    }

    let user_start_addr: usize = unsafe { USER_START_PTR.read_volatile() };

    if user_start_addr == 0 {
        // okay, so we should look for the path
        let arg0 = argv.first();
        if let Some(arg0) = arg0 {
            // entire user memory is free cos ELF there
            let block: &[u8] =
                unsafe { core::slice::from_raw_parts(USER_MEMORY_START_PTR, USER_MEMORY_LENGTH) };
            #[allow(static_mut_refs)]
            unsafe {
                HEAP.insert_free_block_ptr(block.into());
            }
            let path = arg0;
            // let's first get the file size
            let file = load_file_aligned_to_page_size(path);
            let elf = ElfBytes::<LittleEndian>::minimal_parse(file).unwrap();
            kprint!("elf: {:?}", elf);
            // let's find if it's dynamic, the interpreter
            if elf.ehdr.e_type == elf::abi::ET_DYN {
                // For ET_DYN (dynamic) ELF, find the interpreter (PT_INTERP) and print it, no-std style.
                let mut interp_path = None;
                for ph in elf.segments().unwrap() {
                    if ph.p_type == PT_INTERP {
                        // Read the interpreter path from the segment
                        let _offset = ph.p_offset as usize;
                        let filesz = ph.p_filesz as usize;
                        if let Ok(interp_bytes) = elf.segment_data(&ph) {
                            // PT_INTERP is a null-terminated string
                            let nul_pos =
                                interp_bytes.iter().position(|&b| b == 0).unwrap_or(filesz);
                            let path_bytes = &interp_bytes[..nul_pos];
                            // Try to print as UTF-8, fallback to hex if not valid
                            interp_path = match core::str::from_utf8(path_bytes) {
                                Ok(s) => Some(s.to_string()),
                                Err(_) => None,
                            }
                        }
                    }
                }
                if let Some(interp_path) = interp_path {
                    let interp_file = load_file_aligned_to_page_size(&interp_path);
                    let interp_elf = ElfBytes::<LittleEndian>::minimal_parse(interp_file).unwrap();
                    kprint!("interp_elf: {:?}", interp_elf);
                    if elf.ehdr.class != Class::ELF32 {
                        kpanic!("Interpreter not a 32-bit ELF");
                    }
                    if elf.ehdr.e_machine != elf::abi::EM_RISCV {
                        kpanic!("Interpreter has invalid machine type, must be RISC-V");
                    }
                    // Load interpreter ELF segments into memory, similar to ELF loader logic
                    // This is a minimal, in-place version for the Linux ABI loader

                    // We'll use the same logic as in the ELF loader to map PT_LOAD segments
                    let max_mem = USER_MEMORY_LENGTH as u32;
                    let word_size = core::mem::size_of::<usize>() as u32;
                    let input = interp_file;

                    for segment in interp_elf
                        .segments()
                        .unwrap()
                        .iter()
                        .filter(|x| x.p_type == elf::abi::PT_LOAD)
                    {
                        let file_size: u32 = segment.p_filesz.try_into().unwrap();
                        if file_size >= max_mem {
                            kpanic!("Invalid segment file_size");
                        }
                        let mem_size: u32 = segment.p_memsz.try_into().unwrap();
                        if mem_size >= max_mem {
                            kpanic!("Invalid segment mem_size");
                        }
                        let vaddr: u32 = segment.p_vaddr.try_into().unwrap();
                        if vaddr % word_size != 0 {
                            kpanic!("vaddr {:#08x} is unaligned", vaddr);
                        }
                        // allocate the memory for the segment
                        let layout = Layout::from_size_align(mem_size as usize, PAGE_SIZE).unwrap();
                        #[allow(static_mut_refs)]
                        let ptr = unsafe { HEAP.allocate(layout).unwrap().as_ptr() };
                        if ptr.is_null() {
                            kpanic!("Failed to allocate memory for segment");
                        }
                        // copy the segment data to the allocated memory
                        unsafe {
                            ptr.copy_from(input.as_ptr(), mem_size as usize);
                        }
                    }
                } else {
                    kpanic!("No PT_INTERP found in ET_DYN ELF");
                }
            } else {
                kprint!("elf is static");
            }

            kpanic!("USER_START_PTR is 0, path: {}", path);
        }
    }
    for arg in &argv {
        stack.add_str(arg.as_bytes());
    }

    stack.add_null();

    // env
    stack.add_null();

    // aux
    stack.add_aux_word(AuxType::PageSz, PAGE_SIZE);
    // auxv[0]
    stack.add_aux_word(AuxType::Uid, 1);
    // auxv[1]
    stack.add_aux_word(AuxType::EUid, 1);
    // auxv[2]
    stack.add_aux_word(AuxType::Gid, 1);
    // auxv[3]
    stack.add_aux_word(AuxType::EGid, 1);
    // auxv[4]
    // Add AT_PHDR, AT_PHNUM, AT_PHENT
    // Define the AuxType variants if not already defined:
    //     Phdr = ...,
    //     Phnum = ...,
    //     Phent = ...,
    // Use the constants for addresses and sizes
    stack.add_aux_word(AuxType::Phdr, unsafe { USER_PHDR_ADDR_PTR.read_volatile() });
    // auxv[5]
    stack.add_aux_word(AuxType::PhNum, unsafe {
        USER_PHDR_NUM_ADDR_PTR.read_volatile()
    });
    // auxv[6]
    stack.add_aux_word(AuxType::PhEnt, USER_PHENT_SIZE);
    // auxv[7]
    stack.add_aux_word(AuxType::Null, 0);
    // auxv[8]

    set_ureg(REG_SP, USER_STACK_PTR as u32);

    let block: &[u8] = unsafe { core::slice::from_raw_parts(USER_HEAP_START_PTR, USER_HEAP_SIZE) };
    #[allow(static_mut_refs)]
    unsafe {
        HEAP.insert_free_block_ptr(block.into());
    }
    print("starting linux binary");
    let user_start_addr: usize = unsafe { USER_START_PTR.read_volatile() } - 4;
    unsafe {
        MEPC_PTR.write_volatile(user_start_addr);
    }
    mret()
}

pub fn handle_linux_syscall() -> ! {
    let nr = get_ureg(REG_A7);
    match nr {
        SYS_IOCTL => syscall3(sys_ioctl),
        SYS_READ => syscall3(sys_read),
        SYS_WRITE => syscall3(sys_write),
        SYS_WRITEV => syscall3(sys_writev),
        SYS_EXIT => syscall1(sys_exit),
        SYS_EXIT_GROUP => syscall1(sys_exit_group),
        SYS_SET_TID_ADDRESS => syscall1(sys_set_tid_address),
        SYS_TKILL => syscall2(sys_tkill),
        SYS_SIGALTSTACK => syscall2(sys_sigaltstack),
        SYS_RT_SIGACTION => syscall4(sys_rt_sigaction),
        SYS_RT_SIGPROCMASK => syscall4(sys_rt_sigprocmask),
        SYS_BRK => syscall1(sys_brk),
        SYS_MMAP => syscall6(sys_mmap),
        SYS_MUNMAP => syscall2(sys_munmap),
        SYS_ACCEPT => syscall3(sys_accept),
        SYS_ACCEPT4 => syscall4(sys_accept4),
        SYS_ACCT => syscall1(sys_acct),
        SYS_ADD_KEY => syscall5(sys_add_key),
        SYS_BIND => syscall3(sys_bind),
        SYS_BPF => syscall3(sys_bpf),
        SYS_CACHESTAT => syscall4(sys_cachestat),
        SYS_CAPGET => syscall2(sys_capget),
        SYS_CAPSET => syscall2(sys_capset),
        SYS_CHDIR => syscall1(sys_chdir),
        SYS_CHROOT => syscall1(sys_chroot),
        SYS_CLOCK_ADJTIME64 => syscall2(sys_clock_adjtime64),
        SYS_CLOCK_GETRES_TIME64 => syscall2(sys_clock_getres_time64),
        SYS_CLOCK_GETTIME64 => syscall2(sys_clock_gettime64),
        SYS_CLOCK_NANOSLEEP_TIME64 => syscall4(sys_clock_nanosleep_time64),
        SYS_CLOCK_SETTIME64 => syscall2(sys_clock_settime64),
        SYS_CLONE => syscall5(sys_clone),
        SYS_CLONE3 => syscall2(sys_clone3),
        SYS_CLOSE => syscall1(sys_close),
        SYS_CLOSE_RANGE => syscall3(sys_close_range),
        SYS_CONNECT => syscall3(sys_connect),
        SYS_COPY_FILE_RANGE => syscall6(sys_copy_file_range),
        SYS_DELETE_MODULE => syscall2(sys_delete_module),
        SYS_DUP => syscall1(sys_dup),
        SYS_DUP3 => syscall3(sys_dup3),
        SYS_EPOLL_CREATE1 => syscall1(sys_epoll_create1),
        SYS_EPOLL_CTL => syscall4(sys_epoll_ctl),
        SYS_EPOLL_PWAIT => syscall4(sys_epoll_pwait),
        SYS_EPOLL_PWAIT2 => syscall5(sys_epoll_pwait2),
        SYS_EVENTFD2 => syscall2(sys_eventfd2),
        SYS_EXECVE => syscall3(sys_execve),
        SYS_EXECVEAT => syscall5(sys_execveat),
        SYS_FACCESSAT => syscall3(sys_faccessat),
        SYS_FACCESSAT2 => syscall3(sys_faccessat2),
        SYS_FADVISE64_64 => syscall4(sys_fadvise64_64),
        SYS_FALLOCATE => syscall4(sys_fallocate),
        SYS_FANOTIFY_INIT => syscall2(sys_fanotify_init),
        SYS_FANOTIFY_MARK => syscall5(sys_fanotify_mark),
        SYS_FCHDIR => syscall1(sys_fchdir),
        SYS_FCHMOD => syscall2(sys_fchmod),
        SYS_FCHMODAT => syscall4(sys_fchmodat),
        SYS_FCHMODAT2 => syscall4(sys_fchmodat2),
        SYS_FCHOWN => syscall3(sys_fchown),
        SYS_FCHOWNAT => syscall5(sys_fchownat),
        SYS_FCNTL64 => syscall3(sys_fcntl64),
        SYS_FDATASYNC => syscall1(sys_fdatasync),
        SYS_FGETXATTR => syscall4(sys_fgetxattr),
        SYS_FILE_GETATTR => syscall3(sys_file_getattr),
        SYS_FILE_SETATTR => syscall3(sys_file_setattr),
        SYS_FINIT_MODULE => syscall3(sys_finit_module),
        SYS_FLISTXATTR => syscall3(sys_flistxattr),
        SYS_FLOCK => syscall2(sys_flock),
        SYS_FREMOVEXATTR => syscall2(sys_fremovexattr),
        SYS_FSCONFIG => syscall5(sys_fsconfig),
        SYS_FSETXATTR => syscall5(sys_fsetxattr),
        SYS_FSMOUNT => syscall3(sys_fsmount),
        SYS_FSOPEN => syscall2(sys_fsopen),
        SYS_FSPICK => syscall3(sys_fspick),
        SYS_FSTATFS64 => syscall2(sys_fstatfs64),
        SYS_FSYNC => syscall1(sys_fsync),
        SYS_FTRUNCATE64 => syscall2(sys_ftruncate64),
        SYS_FUTEX_REQUEUE => syscall5(sys_futex_requeue),
        SYS_FUTEX_TIME64 => syscall5(sys_futex_time64),
        SYS_FUTEX_WAIT => syscall4(sys_futex_wait),
        SYS_FUTEX_WAITV => syscall5(sys_futex_waitv),
        SYS_FUTEX_WAKE => syscall3(sys_futex_wake),
        SYS_GET_MEMPOLICY => syscall5(sys_get_mempolicy),
        SYS_GET_ROBUST_LIST => syscall3(sys_get_robust_list),
        SYS_GETCPU => syscall3(sys_getcpu),
        SYS_GETCWD => syscall2(sys_getcwd),
        SYS_GETDENTS64 => syscall3(sys_getdents64),
        SYS_GETEGID => syscall0(sys_getegid),
        SYS_GETEUID => syscall0(sys_geteuid),
        SYS_GETGID => syscall0(sys_getgid),
        SYS_GETGROUPS => syscall2(sys_getgroups),
        SYS_GETITIMER => syscall2(sys_getitimer),
        SYS_GETPEERNAME => syscall3(sys_getpeername),
        SYS_GETPGID => syscall1(sys_getpgid),
        SYS_GETPID => syscall0(sys_getpid),
        SYS_GETPPID => syscall0(sys_getppid),
        SYS_GETPRIORITY => syscall2(sys_getpriority),
        SYS_GETRANDOM => syscall3(sys_getrandom),
        SYS_GETRESGID => syscall3(sys_getresgid),
        SYS_GETRESUID => syscall3(sys_getresuid),
        SYS_GETRUSAGE => syscall2(sys_getrusage),
        SYS_GETSID => syscall1(sys_getsid),
        SYS_GETSOCKNAME => syscall3(sys_getsockname),
        SYS_GETSOCKOPT => syscall5(sys_getsockopt),
        SYS_GETTID => syscall0(sys_gettid),
        SYS_GETUID => syscall0(sys_getuid),
        SYS_GETXATTR => syscall4(sys_getxattr),
        SYS_GETXATTRAT => syscall4(sys_getxattrat),
        SYS_INIT_MODULE => syscall3(sys_init_module),
        SYS_INOTIFY_ADD_WATCH => syscall3(sys_inotify_add_watch),
        SYS_INOTIFY_INIT1 => syscall1(sys_inotify_init1),
        SYS_INOTIFY_RM_WATCH => syscall2(sys_inotify_rm_watch),
        SYS_IO_CANCEL => syscall3(sys_io_cancel),
        SYS_IO_DESTROY => syscall1(sys_io_destroy),
        SYS_IO_PGETEVENTS_TIME64 => syscall5(sys_io_pgetevents_time64),
        SYS_IO_SETUP => syscall2(sys_io_setup),
        SYS_IO_SUBMIT => syscall3(sys_io_submit),
        SYS_IO_URING_ENTER => syscall6(sys_io_uring_enter),
        SYS_IO_URING_REGISTER => syscall4(sys_io_uring_register),
        SYS_IO_URING_SETUP => syscall3(sys_io_uring_setup),
        SYS_IOPRIO_GET => syscall2(sys_ioprio_get),
        SYS_IOPRIO_SET => syscall3(sys_ioprio_set),
        SYS_KCMP => syscall5(sys_kcmp),
        SYS_KEXEC_FILE_LOAD => syscall5(sys_kexec_file_load),
        SYS_KEXEC_LOAD => syscall4(sys_kexec_load),
        SYS_KEYCTL => syscall5(sys_keyctl),
        SYS_KILL => syscall2(sys_kill),
        SYS_LANDLOCK_ADD_RULE => syscall4(sys_landlock_add_rule),
        SYS_LANDLOCK_CREATE_RULESET => syscall3(sys_landlock_create_ruleset),
        SYS_LANDLOCK_RESTRICT_SELF => syscall1(sys_landlock_restrict_self),
        SYS_LGETXATTR => syscall4(sys_lgetxattr),
        SYS_LINKAT => syscall5(sys_linkat),
        SYS_LISTEN => syscall2(sys_listen),
        SYS_LISTMOUNT => syscall3(sys_listmount),
        SYS_LISTXATTR => syscall3(sys_listxattr),
        SYS_LISTXATTRAT => syscall4(sys_listxattrat),
        SYS_LLISTXATTR => syscall3(sys_llistxattr),
        SYS_LLSEEK => syscall3(sys_llseek),
        SYS_LOOKUP_DCOOKIE => syscall3(sys_lookup_dcookie),
        SYS_LREMOVEXATTR => syscall2(sys_lremovexattr),
        SYS_LSETXATTR => syscall5(sys_lsetxattr),
        SYS_LSM_GET_SELF_ATTR => syscall3(sys_lsm_get_self_attr),
        SYS_LSM_LIST_MODULES => syscall2(sys_lsm_list_modules),
        SYS_LSM_SET_SELF_ATTR => syscall3(sys_lsm_set_self_attr),
        SYS_MADVISE => syscall3(sys_madvise),
        SYS_MAP_SHADOW_STACK => syscall3(sys_map_shadow_stack),
        SYS_MBIND => syscall6(sys_mbind),
        SYS_MEMBARRIER => syscall2(sys_membarrier),
        SYS_MEMFD_CREATE => syscall2(sys_memfd_create),
        SYS_MEMFD_SECRET => syscall2(sys_memfd_secret),
        SYS_MIGRATE_PAGES => syscall6(sys_migrate_pages),
        SYS_MINCORE => syscall3(sys_mincore),
        SYS_MKDIRAT => syscall3(sys_mkdirat),
        SYS_MKNODAT => syscall4(sys_mknodat),
        SYS_MLOCK => syscall2(sys_mlock),
        SYS_MLOCK2 => syscall3(sys_mlock2),
        SYS_MLOCKALL => syscall1(sys_mlockall),
        SYS_MOUNT => syscall5(sys_mount),
        SYS_MOUNT_SETATTR => syscall5(sys_mount_setattr),
        SYS_MOVE_MOUNT => syscall5(sys_move_mount),
        SYS_MOVE_PAGES => syscall6(sys_move_pages),
        SYS_MPROTECT => syscall3(sys_mprotect),
        SYS_MQ_GETSETATTR => syscall3(sys_mq_getsetattr),
        SYS_MQ_NOTIFY => syscall2(sys_mq_notify),
        SYS_MQ_OPEN => syscall4(sys_mq_open),
        SYS_MQ_TIMEDRECEIVE_TIME64 => syscall5(sys_mq_timedreceive_time64),
        SYS_MQ_TIMEDSEND_TIME64 => syscall5(sys_mq_timedsend_time64),
        SYS_MQ_UNLINK => syscall1(sys_mq_unlink),
        SYS_MREMAP => syscall5(sys_mremap),
        SYS_MSEAL => syscall3(sys_mseal),
        SYS_MSGCTL => syscall4(sys_msgctl),
        SYS_MSGGET => syscall3(sys_msgget),
        SYS_MSGRCV => syscall5(sys_msgrcv),
        SYS_MSGSND => syscall4(sys_msgsnd),
        SYS_MSYNC => syscall3(sys_msync),
        SYS_MUNLOCK => syscall2(sys_munlock),
        SYS_MUNLOCKALL => syscall0(sys_munlockall),
        SYS_NAME_TO_HANDLE_AT => syscall5(sys_name_to_handle_at),
        SYS_OPEN_BY_HANDLE_AT => syscall3(sys_open_by_handle_at),
        SYS_OPEN_TREE => syscall3(sys_open_tree),
        SYS_OPEN_TREE_ATTR => syscall4(sys_open_tree_attr),
        SYS_OPENAT => syscall4(sys_openat),
        SYS_OPENAT2 => syscall3(sys_openat2),
        SYS_PERF_EVENT_OPEN => syscall5(sys_perf_event_open),
        SYS_PERSONALITY => syscall1(sys_personality),
        SYS_PIDFD_GETFD => syscall3(sys_pidfd_getfd),
        SYS_PIDFD_OPEN => syscall2(sys_pidfd_open),
        SYS_PIDFD_SEND_SIGNAL => syscall3(sys_pidfd_send_signal),
        SYS_PIPE2 => syscall2(sys_pipe2),
        SYS_PIVOT_ROOT => syscall2(sys_pivot_root),
        SYS_PKEY_ALLOC => syscall2(sys_pkey_alloc),
        SYS_PKEY_FREE => syscall1(sys_pkey_free),
        SYS_PKEY_MPROTECT => syscall4(sys_pkey_mprotect),
        SYS_PPOLL_TIME64 => syscall5(sys_ppoll_time64),
        SYS_PRCTL => syscall5(sys_prctl),
        SYS_PREAD64 => syscall4(sys_pread64),
        SYS_PREADV => syscall4(sys_preadv),
        SYS_PREADV2 => syscall5(sys_preadv2),
        SYS_PRLIMIT64 => syscall4(sys_prlimit64),
        SYS_PROCESS_MADVISE => syscall5(sys_process_madvise),
        SYS_PROCESS_MRELEASE => syscall2(sys_process_mrelease),
        SYS_PROCESS_VM_READV => syscall6(sys_process_vm_readv),
        SYS_PROCESS_VM_WRITEV => syscall6(sys_process_vm_writev),
        SYS_PSELECT6_TIME64 => syscall6(sys_pselect6_time64),
        SYS_PTRACE => syscall4(sys_ptrace),
        SYS_PWRITE64 => syscall4(sys_pwrite64),
        SYS_PWRITEV => syscall4(sys_pwritev),
        SYS_PWRITEV2 => syscall5(sys_pwritev2),
        SYS_QUOTACTL => syscall4(sys_quotactl),
        SYS_QUOTACTL_FD => syscall4(sys_quotactl_fd),
        SYS_READAHEAD => syscall3(sys_readahead),
        SYS_READLINKAT => syscall3(sys_readlinkat),
        SYS_READV => syscall3(sys_readv),
        SYS_REBOOT => syscall4(sys_reboot),
        SYS_RECVFROM => syscall6(sys_recvfrom),
        SYS_RECVMMSG_TIME64 => syscall5(sys_recvmmsg_time64),
        SYS_RECVMSG => syscall3(sys_recvmsg),
        SYS_REMAP_FILE_PAGES => syscall5(sys_remap_file_pages),
        SYS_REMOVEXATTR => syscall2(sys_removexattr),
        SYS_REMOVEXATTRAT => syscall3(sys_removexattrat),
        SYS_RENAMEAT2 => syscall5(sys_renameat2),
        SYS_REQUEST_KEY => syscall4(sys_request_key),
        SYS_RESTART_SYSCALL => syscall0(sys_restart_syscall),
        SYS_RISCV_FLUSH_ICACHE => syscall2(sys_riscv_flush_icache),
        SYS_RISCV_HWPROBE => syscall4(sys_riscv_hwprobe),
        SYS_RSEQ => syscall4(sys_rseq),
        SYS_RT_SIGPENDING => syscall2(sys_rt_sigpending),
        SYS_RT_SIGQUEUEINFO => syscall3(sys_rt_sigqueueinfo),
        SYS_RT_SIGRETURN => syscall0(sys_rt_sigreturn),
        SYS_RT_SIGSUSPEND => syscall1(sys_rt_sigsuspend),
        SYS_RT_SIGTIMEDWAIT_TIME64 => syscall4(sys_rt_sigtimedwait_time64),
        SYS_RT_TGSIGQUEUEINFO => syscall4(sys_rt_tgsigqueueinfo),
        SYS_SCHED_GET_PRIORITY_MAX => syscall1(sys_sched_get_priority_max),
        SYS_SCHED_GET_PRIORITY_MIN => syscall1(sys_sched_get_priority_min),
        SYS_SCHED_GETAFFINITY => syscall3(sys_sched_getaffinity),
        SYS_SCHED_GETATTR => syscall3(sys_sched_getattr),
        SYS_SCHED_GETPARAM => syscall2(sys_sched_getparam),
        SYS_SCHED_GETSCHEDULER => syscall1(sys_sched_getscheduler),
        SYS_SCHED_RR_GET_INTERVAL_TIME64 => syscall2(sys_sched_rr_get_interval_time64),
        SYS_SCHED_SETAFFINITY => syscall3(sys_sched_setaffinity),
        SYS_SCHED_SETATTR => syscall3(sys_sched_setattr),
        SYS_SCHED_SETPARAM => syscall2(sys_sched_setparam),
        SYS_SCHED_SETSCHEDULER => syscall3(sys_sched_setscheduler),
        SYS_SCHED_YIELD => syscall0(sys_sched_yield),
        SYS_SECCOMP => syscall3(sys_seccomp),
        SYS_SEMCTL => syscall4(sys_semctl),
        SYS_SEMGET => syscall3(sys_semget),
        SYS_SEMOP => syscall3(sys_semop),
        SYS_SEMTIMEDOP_TIME64 => syscall4(sys_semtimedop_time64),
        SYS_SENDFILE64 => syscall4(sys_sendfile64),
        SYS_SENDMMSG => syscall4(sys_sendmmsg),
        SYS_SENDMSG => syscall3(sys_sendmsg),
        SYS_SENDTO => syscall6(sys_sendto),
        SYS_SET_MEMPOLICY => syscall6(sys_set_mempolicy),
        SYS_SET_MEMPOLICY_HOME_NODE => syscall4(sys_set_mempolicy_home_node),
        SYS_SET_ROBUST_LIST => syscall2(sys_set_robust_list),
        SYS_SETDOMAINNAME => syscall1(sys_setdomainname),
        SYS_SETFSGID => syscall1(sys_setfsgid),
        SYS_SETFSUID => syscall1(sys_setfsuid),
        SYS_SETGID => syscall1(sys_setgid),
        SYS_SETGROUPS => syscall2(sys_setgroups),
        SYS_SETHOSTNAME => syscall1(sys_sethostname),
        SYS_SETITIMER => syscall2(sys_setitimer),
        SYS_SETNS => syscall2(sys_setns),
        SYS_SETPGID => syscall2(sys_setpgid),
        SYS_SETPRIORITY => syscall3(sys_setpriority),
        SYS_SETREGID => syscall2(sys_setregid),
        SYS_SETRESGID => syscall3(sys_setresgid),
        SYS_SETRESUID => syscall3(sys_setresuid),
        SYS_SETREUID => syscall2(sys_setreuid),
        SYS_SETSID => syscall0(sys_setsid),
        SYS_SETSOCKOPT => syscall5(sys_setsockopt),
        SYS_SETUID => syscall1(sys_setuid),
        SYS_SETXATTR => syscall5(sys_setxattr),
        SYS_SETXATTRAT => syscall5(sys_setxattrat),
        SYS_SHMAT => syscall3(sys_shmat),
        SYS_SHMCTL => syscall3(sys_shmctl),
        SYS_SHDT => syscall1(sys_shmdt),
        SYS_SHMGET => syscall4(sys_shmget),
        SYS_SHUTDOWN => syscall2(sys_shutdown),
        SYS_SIGNALFD4 => syscall3(sys_signalfd4),
        SYS_SOCKET => syscall3(sys_socket),
        SYS_SOCKETPAIR => syscall4(sys_socketpair),
        SYS_SPLICE => syscall6(sys_splice),
        SYS_STATFS64 => syscall2(sys_statfs64),
        SYS_STATMOUNT => syscall4(sys_statmount),
        SYS_STATX => syscall5(sys_statx),
        SYS_SWAPOFF => syscall1(sys_swapoff),
        SYS_SWAPON => syscall3(sys_swapon),
        SYS_SYMLINKAT => syscall4(sys_symlinkat),
        SYS_SYNC => syscall0(sys_sync),
        SYS_SYNC_FILE_RANGE => syscall4(sys_sync_file_range),
        SYS_SYNCFS => syscall1(sys_syncfs),
        SYS_SYSINFO => syscall1(sys_sysinfo),
        SYS_SYSLOG => syscall3(sys_syslog),
        SYS_TEE => syscall4(sys_tee),
        SYS_TGKILL => syscall3(sys_tgkill),
        SYS_TIMER_CREATE => syscall3(sys_timer_create),
        SYS_TIMER_DELETE => syscall1(sys_timer_delete),
        SYS_TIMER_GETOVERRUN => syscall1(sys_timer_getoverrun),
        SYS_TIMER_GETTIME64 => syscall2(sys_timer_gettime64),
        SYS_TIMER_SETTIME64 => syscall4(sys_timer_settime64),
        SYS_TIMERFD_CREATE => syscall2(sys_timerfd_create),
        SYS_TIMERFD_GETTIME64 => syscall2(sys_timerfd_gettime64),
        SYS_TIMERFD_SETTIME64 => syscall4(sys_timerfd_settime64),
        SYS_TIMES => syscall1(sys_times),
        SYS_TRUNCATE64 => syscall2(sys_truncate64),
        SYS_UMASK => syscall1(sys_umask),
        SYS_UMOUNT2 => syscall2(sys_umount2),
        SYS_UNAME => syscall1(sys_uname),
        SYS_UNLINKAT => syscall3(sys_unlinkat),
        SYS_UNSHARE => syscall1(sys_unshare),
        SYS_USERFAULTFD => syscall1(sys_userfaultfd),
        SYS_UTIMENSAT_TIME64 => syscall4(sys_utimensat_time64),
        SYS_VHANGUP => syscall0(sys_vhangup),
        SYS_VMSPLICE => syscall4(sys_vmsplice),
        SYS_WAITID => syscall5(sys_waitid),
        _ => {
            let msg = str_format!(str256, "syscall: {nr}");
            print(&msg);
            set_ureg(REG_A0, 0);
        }
    }
    mret();
}

fn set_result(result: Result<u32, Err>) {
    set_ureg(REG_A0, result.unwrap_or_else(|e| e.as_errno()));
}

fn syscall0<F: Fn() -> Result<u32, Err>>(inner: F) {
    set_result(inner());
}

fn syscall1<F: Fn(u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(get_ureg(REG_A0)));
}

fn syscall2<F: Fn(u32, u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(get_ureg(REG_A0), get_ureg(REG_A1)));
}

fn syscall3<F: Fn(u32, u32, u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(get_ureg(REG_A0), get_ureg(REG_A1), get_ureg(REG_A2)));
}

fn syscall4<F: Fn(u32, u32, u32, u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(
        get_ureg(REG_A0),
        get_ureg(REG_A1),
        get_ureg(REG_A2),
        get_ureg(REG_A3),
    ));
}

fn syscall5<F: Fn(u32, u32, u32, u32, u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(
        get_ureg(REG_A0),
        get_ureg(REG_A1),
        get_ureg(REG_A2),
        get_ureg(REG_A3),
        get_ureg(REG_A4),
    ));
}

fn syscall6<F: Fn(u32, u32, u32, u32, u32, u32) -> Result<u32, Err>>(inner: F) {
    set_result(inner(
        get_ureg(REG_A0),
        get_ureg(REG_A1),
        get_ureg(REG_A2),
        get_ureg(REG_A3),
        get_ureg(REG_A4),
        get_ureg(REG_A5),
    ));
}

/// change the location of the program break
///
/// https://man7.org/linux/man-pages/man2/brk.2.html
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/mmap.c#L194
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/nommu.c#L381
fn sys_brk(addr: u32) -> Result<u32, Err> {
    let ret = unsafe {
        if addr > USER_HEAP_START_ADDR as u32 {
            BRK = addr;
        }
        BRK
    };

    // let msg = str_format!(str256, "sys_brk(0x{addr:08x}) -> 0x{ret:08x}");
    // print(&msg);

    Ok(ret)
}

/// https://man7.org/linux/man-pages/man2/mmap.2.html
/// https://elixir.bootlin.com/linux/v5.15.5/source/arch/riscv/kernel/sys_riscv.c#L30
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/mmap.c#L1583
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/mmap.c#L1404
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/nommu.c#L1282
/// https://elixir.bootlin.com/linux/v5.15.5/source/mm/nommu.c#L1056
fn sys_mmap(
    _addr: u32,
    len: u32,
    _prot: u32,
    _flags: u32,
    fd: u32,
    _offset: u32,
) -> Result<u32, Err> {
    let _fd = fd as i32;

    // let msg = str_format!(
    //     str256,
    //     "sys_mmap(0x{_addr:08x}, {len}, {_prot}, 0x{_flags:08x}, {_fd}, {_offset})"
    // );
    // print(&msg);

    if len == 0 {
        return Err(Err::Inval);
    }

    #[allow(static_mut_refs)]
    let ptr = unsafe {
        let layout = Layout::from_size_align(len as usize, PAGE_SIZE).unwrap_unchecked();
        let ptr = HEAP.allocate(layout).ok_or(Err::NoMem)?.as_ptr();
        if !ptr.is_null() {
            ptr.write_bytes(0, layout.size());
        }
        ptr
    };

    // let msg = str_format!(str256, "{ptr:?}");
    // print(&msg);

    Ok(ptr as u32)
}

/// https://man7.org/linux/man-pages/man2/mmap.2.html
fn sys_munmap(addr: u32, _len: u32) -> Result<u32, Err> {
    let ptr = addr as *mut u8;

    // let msg = str_format!(str256, "sys_munmap({ptr:?}, {_len})");
    // print(&msg);

    if ptr.is_null() {
        return Err(Err::Inval);
    }

    #[allow(static_mut_refs)]
    unsafe {
        HEAP.deallocate(NonNull::new_unchecked(ptr), PAGE_SIZE)
    };

    Err(Err::NoSys)
}

/// https://man7.org/linux/man-pages/man2/ioctl.2.html
fn sys_ioctl(fd: u32, _cmd: u32, arg: u32) -> Result<u32, Err> {
    // For now, sys_ioctl is not implemented. Log a message for debugging.
    let msg = b"sys_ioctl not implemented";
    host_log(msg.as_ptr(), msg.len());
    let _fd = fd as i32;
    let _arg = arg as *const u8;
    // let msg = str_format!(str256, "sys_ioctl({fd}, {cmd}, 0x{arg:08x})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/_exit.2.html
fn sys_exit(error_code: u32) -> Result<u32, Err> {
    let msg = str_format!(str256, "sys_exit({error_code})");
    print(&msg);
    host_terminate(error_code, 0);
}

/// https://man7.org/linux/man-pages/man2/exit_group.2.html
fn sys_exit_group(_error_code: u32) -> Result<u32, Err> {
    // let msg = str_format!(str256, "sys_exit_group({error_code})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/tkill.2.html
fn sys_tkill(_pid: u32, _sig: u32) -> Result<u32, Err> {
    // let msg = str_format!(str256, "sys_tkill({_pid}, {_sig})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/set_tid_address.2.html
fn sys_set_tid_address(tidptr: u32) -> Result<u32, Err> {
    let _tidptr = tidptr as *const u8;
    let msg = str_format!(str256, "sys_set_tid_address({tidptr:?})");
    print(&msg);
    Ok(1)
}

/// https://man7.org/linux/man-pages/man2/sigaltstack.2.html
fn sys_sigaltstack(uss: u32, uoss: u32) -> Result<u32, Err> {
    let _uss = uss as *const u8;
    let _uoss = uoss as *const u8;
    // let msg = str_format!(str256, "sys_sigaltstack({uss:?}, {uoss:?})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/sigaction.2.html
fn sys_rt_sigaction(_sig: u32, act: u32, oact: u32, _sigsetsize: u32) -> Result<u32, Err> {
    let _act = act as *const u8;
    let _oact = oact as *const u8;
    // let msg = str_format!(
    //     str256,
    //     "sys_rt_sigaction({_sig}, {_act:?}, {_oact:?}, {_sigsetsize})"
    // );
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/sigprocmask.2.html
fn sys_rt_sigprocmask(_how: u32, nset: u32, oset: u32, _sigsetsize: u32) -> Result<u32, Err> {
    let _nset = nset as *const u8;
    let _oset = oset as *const u8;
    // let msg = str_format!(
    //     str256,
    //     "sys_rt_sigprocmask({_how}, {_nset:?}, {_oset:?}, {_sigsetsize})"
    // );
    // print(&msg);
    Ok(0)
}

// Stub implementations for all additional syscalls

fn sys_cachestat(_fd: u32, _cstat: u32, _cstat_size: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_cachestat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_clock_getres_time64(_which_clock: u32, _tp: u32) -> Result<u32, Err> {
    let msg = b"sys_clock_getres_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_clock_gettime64(_which_clock: u32, _tp: u32) -> Result<u32, Err> {
    let msg = b"sys_clock_gettime64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_clock_nanosleep_time64(
    _which_clock: u32,
    _flags: u32,
    _rqtp: u32,
    _rmtp: u32,
) -> Result<u32, Err> {
    let msg = b"sys_clock_nanosleep_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_clone(
    _flags: u32,
    _child_stack: u32,
    _ptid: u32,
    _tls: u32,
    _ctid: u32,
) -> Result<u32, Err> {
    let msg = b"sys_clone not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_clone3(_cl_args: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_clone3 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_close_range(_first: u32, _last: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_close_range not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_copy_file_range(
    _fd_in: u32,
    _off_in: u32,
    _fd_out: u32,
    _off_out: u32,
    _len: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_copy_file_range not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_epoll_create1(_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_epoll_create1 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_epoll_ctl(_epfd: u32, _op: u32, _fd: u32, _event: u32) -> Result<u32, Err> {
    let msg = b"sys_epoll_ctl not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_epoll_pwait(_epfd: u32, _events: u32, _maxevents: u32, _timeout: u32) -> Result<u32, Err> {
    let msg = b"sys_epoll_pwait not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_epoll_pwait2(
    _epfd: u32,
    _events: u32,
    _maxevents: u32,
    _timeout: u32,
    _sigmask: u32,
) -> Result<u32, Err> {
    let msg = b"sys_epoll_pwait2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_eventfd2(_initval: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_eventfd2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_execve(_filename: u32, _argv: u32, _envp: u32) -> Result<u32, Err> {
    let msg = b"sys_execve not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_execveat(
    _dfd: u32,
    _filename: u32,
    _argv: u32,
    _envp: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_execveat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fchdir(_fd: u32) -> Result<u32, Err> {
    let msg = b"sys_fchdir not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fchmod(_fd: u32, _mode: u32) -> Result<u32, Err> {
    let msg = b"sys_fchmod not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fchmodat(_dfd: u32, _filename: u32, _mode: u32, _flag: u32) -> Result<u32, Err> {
    let msg = b"sys_fchmodat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fchmodat2(_dfd: u32, _filename: u32, _mode: u32, _flag: u32) -> Result<u32, Err> {
    let msg = b"sys_fchmodat2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fchown(_fd: u32, _user: u32, _group: u32) -> Result<u32, Err> {
    let msg = b"sys_fchown not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fchownat(
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

fn sys_fdatasync(_fd: u32) -> Result<u32, Err> {
    let msg = b"sys_fdatasync not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fgetxattr(_fd: u32, _name: u32, _value: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_fgetxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_file_getattr(_dfd: u32, _filename: u32, _mask: u32) -> Result<u32, Err> {
    let msg = b"sys_file_getattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_file_setattr(_dfd: u32, _filename: u32, _mask: u32) -> Result<u32, Err> {
    let msg = b"sys_file_setattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_flistxattr(_fd: u32, _list: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_flistxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_flock(_fd: u32, _cmd: u32) -> Result<u32, Err> {
    let msg = b"sys_flock not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fremovexattr(_fd: u32, _name: u32) -> Result<u32, Err> {
    let msg = b"sys_fremovexattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fsconfig(_fs_fd: u32, _cmd: u32, _key: u32, _value: u32, _aux: u32) -> Result<u32, Err> {
    let msg = b"sys_fsconfig not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fsetxattr(_fd: u32, _name: u32, _value: u32, _size: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_fsetxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fsmount(_fs_fd: u32, _flags: u32, _attr_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_fsmount not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fsopen(_fs_name: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_fsopen not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fspick(_dfd: u32, _path: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_fspick not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fstatfs64(_fd: u32, _buf: u32) -> Result<u32, Err> {
    let msg = b"sys_fstatfs64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_fsync(_fd: u32) -> Result<u32, Err> {
    let msg = b"sys_fsync not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_ftruncate64(_fd: u32, _length: u32) -> Result<u32, Err> {
    let msg = b"sys_ftruncate64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_futex_requeue(
    _uaddr1: u32,
    _flags1: u32,
    _uaddr2: u32,
    _val1: u32,
    _val2: u32,
) -> Result<u32, Err> {
    let msg = b"sys_futex_requeue not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_futex_time64(
    _uaddr: u32,
    _futex_op: u32,
    _val: u32,
    _timeout: u32,
    _uaddr2: u32,
) -> Result<u32, Err> {
    let msg = b"sys_futex_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_futex_wait(_uaddr: u32, _val: u32, _flags: u32, _timeout: u32) -> Result<u32, Err> {
    let msg = b"sys_futex_wait not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_futex_waitv(
    _waiters: u32,
    _nr_waiters: u32,
    _flags: u32,
    _timeout: u32,
    _clockid: u32,
) -> Result<u32, Err> {
    let msg = b"sys_futex_waitv not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_futex_wake(_uaddr: u32, _nr_wake: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_futex_wake not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_get_mempolicy(
    _mode: u32,
    _nmask: u32,
    _maxnode: u32,
    _addr: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_get_mempolicy not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_get_robust_list(_pid: u32, _head: u32, _len: u32) -> Result<u32, Err> {
    let msg = b"sys_get_robust_list not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getcpu(_cpu: u32, _node: u32, _cache: u32) -> Result<u32, Err> {
    let msg = b"sys_getcpu not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getcwd(_buf: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_getcwd not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getegid() -> Result<u32, Err> {
    Ok(0)
}

fn sys_geteuid() -> Result<u32, Err> {
    Ok(0)
}

fn sys_getgid() -> Result<u32, Err> {
    Ok(0)
}

fn sys_getgroups(_size: u32, _list: u32) -> Result<u32, Err> {
    let msg = b"sys_getgroups not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getitimer(_which: u32, _value: u32) -> Result<u32, Err> {
    let msg = b"sys_getitimer not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getpgid(_pid: u32) -> Result<u32, Err> {
    let msg = b"sys_getpgid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getpid() -> Result<u32, Err> {
    let msg = b"sys_getpid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getppid() -> Result<u32, Err> {
    let msg = b"sys_getppid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getpriority(_which: u32, _who: u32) -> Result<u32, Err> {
    let msg = b"sys_getpriority not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getrandom(_buf: u32, _buflen: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_getrandom not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getresgid(_rgid: u32, _egid: u32, _sgid: u32) -> Result<u32, Err> {
    let msg = b"sys_getresgid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getresuid(_ruid: u32, _euid: u32, _suid: u32) -> Result<u32, Err> {
    let msg = b"sys_getresuid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getrusage(_who: u32, _usage: u32) -> Result<u32, Err> {
    let msg = b"sys_getrusage not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getsid(_pid: u32) -> Result<u32, Err> {
    let msg = b"sys_getsid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_gettid() -> Result<u32, Err> {
    let msg = b"sys_gettid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getuid() -> Result<u32, Err> {
    Ok(0)
}

fn sys_getxattr(_pathname: u32, _name: u32, _value: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_getxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_getxattrat(_dfd: u32, _filename: u32, _name: u32, _value: u32) -> Result<u32, Err> {
    let msg = b"sys_getxattrat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_inotify_add_watch(_fd: u32, _pathname: u32, _mask: u32) -> Result<u32, Err> {
    let msg = b"sys_inotify_add_watch not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_inotify_init1(_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_inotify_init1 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_inotify_rm_watch(_fd: u32, _wd: u32) -> Result<u32, Err> {
    let msg = b"sys_inotify_rm_watch not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_io_cancel(_ctx_id: u32, _iocb: u32, _result: u32) -> Result<u32, Err> {
    let msg = b"sys_io_cancel not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_io_destroy(_ctx_id: u32) -> Result<u32, Err> {
    let msg = b"sys_io_destroy not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_io_pgetevents_time64(
    _ctx_id: u32,
    _min_nr: u32,
    _nr: u32,
    _events: u32,
    _timeout: u32,
) -> Result<u32, Err> {
    let msg = b"sys_io_pgetevents_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_io_setup(_nr_events: u32, _ctx_idp: u32) -> Result<u32, Err> {
    let msg = b"sys_io_setup not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_io_submit(_ctx_id: u32, _nr: u32, _iocbpp: u32) -> Result<u32, Err> {
    let msg = b"sys_io_submit not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_io_uring_enter(
    _fd: u32,
    _to_submit: u32,
    _min_complete: u32,
    _flags: u32,
    _sig: u32,
    _sz: u32,
) -> Result<u32, Err> {
    let msg = b"sys_io_uring_enter not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_io_uring_register(_fd: u32, _opcode: u32, _arg: u32, _nr_args: u32) -> Result<u32, Err> {
    let msg = b"sys_io_uring_register not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_io_uring_setup(_entries: u32, _params: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_io_uring_setup not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_ioprio_get(_which: u32, _who: u32) -> Result<u32, Err> {
    let msg = b"sys_ioprio_get not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_ioprio_set(_which: u32, _who: u32, _ioprio: u32) -> Result<u32, Err> {
    let msg = b"sys_ioprio_set not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_kcmp(_pid1: u32, _pid2: u32, _type: u32, _idx1: u32, _idx2: u32) -> Result<u32, Err> {
    let msg = b"sys_kcmp not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_kill(_pid: u32, _sig: u32) -> Result<u32, Err> {
    let msg = b"sys_kill not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_lgetxattr(_pathname: u32, _name: u32, _value: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_lgetxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_linkat(
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

fn sys_listmount(_dfd: u32, _filename: u32, _buffer: u32) -> Result<u32, Err> {
    let msg = b"sys_listmount not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_listxattr(_pathname: u32, _list: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_listxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_listxattrat(_dfd: u32, _filename: u32, _list: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_listxattrat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_llistxattr(_pathname: u32, _list: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_llistxattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_llseek(_fd: u32, _offset_high: u32, _offset_low: u32) -> Result<u32, Err> {
    let msg = b"sys_llseek not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_lookup_dcookie(_cookie64: u32, _buf: u32, _len: u32) -> Result<u32, Err> {
    let msg = b"sys_lookup_dcookie not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_lremovexattr(_pathname: u32, _name: u32) -> Result<u32, Err> {
    let msg = b"sys_lremovexattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_lsetxattr(
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

fn sys_lsm_get_self_attr(_attr: u32, _ctx: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_lsm_get_self_attr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_lsm_list_modules(_ids: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_lsm_list_modules not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_lsm_set_self_attr(_attr: u32, _ctx: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_lsm_set_self_attr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_madvise(_start: u32, _len: u32, _advice: u32) -> Result<u32, Err> {
    let msg = b"sys_madvise not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_map_shadow_stack(_addr: u32, _size: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_map_shadow_stack not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mbind(
    _start: u32,
    _len: u32,
    _mode: u32,
    _nodemask: u32,
    _maxnode: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_mbind not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_membarrier(_cmd: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_membarrier not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_memfd_create(_name: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_memfd_create not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_memfd_secret(_flags: u32, _reserved: u32) -> Result<u32, Err> {
    let msg = b"sys_memfd_secret not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_migrate_pages(
    _pid: u32,
    _maxnode: u32,
    _old_nodes: u32,
    _new_nodes: u32,
    _status: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_migrate_pages not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mincore(_start: u32, _len: u32, _vec: u32) -> Result<u32, Err> {
    let msg = b"sys_mincore not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mkdirat(_dfd: u32, _pathname: u32, _mode: u32) -> Result<u32, Err> {
    let msg = b"sys_mkdirat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mknodat(_dfd: u32, _filename: u32, _mode: u32, _dev: u32) -> Result<u32, Err> {
    let msg = b"sys_mknodat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mlock(_addr: u32, _len: u32) -> Result<u32, Err> {
    let msg = b"sys_mlock not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mlock2(_addr: u32, _len: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_mlock2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mlockall(_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_mlockall not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_move_mount(
    _from_dfd: u32,
    _from_pathname: u32,
    _to_dfd: u32,
    _to_pathname: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_move_mount not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_move_pages(
    _pid: u32,
    _nr_pages: u32,
    _pages: u32,
    _nodes: u32,
    _status: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_move_pages not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mprotect(_addr: u32, _len: u32, _prot: u32) -> Result<u32, Err> {
    let msg = b"sys_mprotect not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mq_getsetattr(_mqdes: u32, _mqstat: u32, _omqstat: u32) -> Result<u32, Err> {
    let msg = b"sys_mq_getsetattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mq_notify(_mqdes: u32, _notification: u32) -> Result<u32, Err> {
    let msg = b"sys_mq_notify not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mq_open(_name: u32, _oflag: u32, _mode: u32, _attr: u32) -> Result<u32, Err> {
    let msg = b"sys_mq_open not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mq_timedreceive_time64(
    _mqdes: u32,
    _msg_ptr: u32,
    _msg_len: u32,
    _msg_prio: u32,
    _abs_timeout: u32,
) -> Result<u32, Err> {
    let msg = b"sys_mq_timedreceive_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mq_timedsend_time64(
    _mqdes: u32,
    _msg_ptr: u32,
    _msg_len: u32,
    _msg_prio: u32,
    _abs_timeout: u32,
) -> Result<u32, Err> {
    let msg = b"sys_mq_timedsend_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mq_unlink(_name: u32) -> Result<u32, Err> {
    let msg = b"sys_mq_unlink not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mremap(
    _addr: u32,
    _old_len: u32,
    _new_len: u32,
    _flags: u32,
    _new_addr: u32,
) -> Result<u32, Err> {
    let msg = b"sys_mremap not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_mseal(_addr: u32, _len: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_mseal not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_msgctl(_msqid: u32, _cmd: u32, _buf: u32, _version: u32) -> Result<u32, Err> {
    let msg = b"sys_msgctl not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_msgget(_key: u32, _msgflg: u32, _version: u32) -> Result<u32, Err> {
    let msg = b"sys_msgget not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_msgrcv(
    _msqid: u32,
    _msgp: u32,
    _msgsz: u32,
    _msgtyp: u32,
    _msgflg: u32,
) -> Result<u32, Err> {
    let msg = b"sys_msgrcv not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_msgsnd(_msqid: u32, _msgp: u32, _msgsz: u32, _msgflg: u32) -> Result<u32, Err> {
    let msg = b"sys_msgsnd not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_msync(_addr: u32, _len: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_msync not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_munlock(_addr: u32, _len: u32) -> Result<u32, Err> {
    let msg = b"sys_munlock not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_munlockall() -> Result<u32, Err> {
    let msg = b"sys_munlockall not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_name_to_handle_at(
    _dfd: u32,
    _name: u32,
    _handle: u32,
    _mnt_id: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_name_to_handle_at not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_open_by_handle_at(_mount_fd: u32, _handle: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_open_by_handle_at not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_open_tree(_dfd: u32, _filename: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_open_tree not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_open_tree_attr(_dfd: u32, _filename: u32, _flags: u32, _attr: u32) -> Result<u32, Err> {
    let msg = b"sys_open_tree_attr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_openat2(_dfd: u32, _filename: u32, _how: u32) -> Result<u32, Err> {
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

fn sys_perf_event_open(
    _attr: u32,
    _pid: u32,
    _cpu: u32,
    _group_fd: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_perf_event_open not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_personality(_personality: u32) -> Result<u32, Err> {
    let msg = b"sys_personality not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pidfd_getfd(_pidfd: u32, _targetfd: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_pidfd_getfd not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pidfd_open(_pid: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_pidfd_open not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pidfd_send_signal(_pidfd: u32, _sig: u32, _info: u32) -> Result<u32, Err> {
    let msg = b"sys_pidfd_send_signal not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pipe2(_pipefd: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_pipe2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pivot_root(_new_root: u32, _put_old: u32) -> Result<u32, Err> {
    let msg = b"sys_pivot_root not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pkey_alloc(_flags: u32, _access_rights: u32) -> Result<u32, Err> {
    let msg = b"sys_pkey_alloc not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pkey_free(_pkey: u32) -> Result<u32, Err> {
    let msg = b"sys_pkey_free not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pkey_mprotect(_start: u32, _len: u32, _prot: u32, _pkey: u32) -> Result<u32, Err> {
    let msg = b"sys_pkey_mprotect not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_ppoll_time64(
    _ufds: u32,
    _nfds: u32,
    _tsp: u32,
    _sigmask: u32,
    _sigsetsize: u32,
) -> Result<u32, Err> {
    let msg = b"sys_ppoll_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_prctl(_option: u32, _arg2: u32, _arg3: u32, _arg4: u32, _arg5: u32) -> Result<u32, Err> {
    let msg = b"sys_prctl not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pread64(_fd: u32, _buf: u32, _count: u32, _pos: u32) -> Result<u32, Err> {
    let msg = b"sys_pread64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_preadv(_fd: u32, _vec: u32, _vlen: u32, _pos_low: u32) -> Result<u32, Err> {
    let msg = b"sys_preadv not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_preadv2(_fd: u32, _vec: u32, _vlen: u32, _pos_low: u32, _pos_high: u32) -> Result<u32, Err> {
    let msg = b"sys_preadv2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_prlimit64(_pid: u32, _resource: u32, _new_limit: u32, _old_limit: u32) -> Result<u32, Err> {
    let msg = b"sys_prlimit64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_process_madvise(
    _pidfd: u32,
    _addr: u32,
    _length: u32,
    _advice: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_process_madvise not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_process_mrelease(_pidfd: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_process_mrelease not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_process_vm_readv(
    _pid: u32,
    _lvec: u32,
    _liovcnt: u32,
    _rvec: u32,
    _riovcnt: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_process_vm_readv not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_process_vm_writev(
    _pid: u32,
    _lvec: u32,
    _liovcnt: u32,
    _rvec: u32,
    _riovcnt: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_process_vm_writev not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pselect6_time64(
    _n: u32,
    _inp: u32,
    _outp: u32,
    _exp: u32,
    _tsp: u32,
    _sigmask: u32,
) -> Result<u32, Err> {
    let msg = b"sys_pselect6_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_ptrace(_request: u32, _pid: u32, _addr: u32, _data: u32) -> Result<u32, Err> {
    let msg = b"sys_ptrace not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pwrite64(_fd: u32, _buf: u32, _count: u32, _pos: u32) -> Result<u32, Err> {
    let msg = b"sys_pwrite64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pwritev(_fd: u32, _vec: u32, _vlen: u32, _pos_low: u32) -> Result<u32, Err> {
    let msg = b"sys_pwritev not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_pwritev2(
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

fn sys_quotactl(_cmd: u32, _special: u32, _id: u32, _addr: u32) -> Result<u32, Err> {
    let msg = b"sys_quotactl not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_quotactl_fd(_fd: u32, _cmd: u32, _id: u32, _addr: u32) -> Result<u32, Err> {
    let msg = b"sys_quotactl_fd not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_readahead(_fd: u32, _offset: u32, _count: u32) -> Result<u32, Err> {
    let msg = b"sys_readahead not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_readlinkat(_dfd: u32, _pathname: u32, _buf: u32) -> Result<u32, Err> {
    let msg = b"sys_readlinkat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_readv(_fd: u32, _vec: u32, _vlen: u32) -> Result<u32, Err> {
    let msg = b"sys_readv not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_remap_file_pages(
    _start: u32,
    _size: u32,
    _prot: u32,
    _pgoff: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_remap_file_pages not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_removexattr(_pathname: u32, _name: u32) -> Result<u32, Err> {
    let msg = b"sys_removexattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_removexattrat(_dfd: u32, _filename: u32, _name: u32) -> Result<u32, Err> {
    let msg = b"sys_removexattrat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_renameat2(
    _olddirfd: u32,
    _oldpath: u32,
    _newdirfd: u32,
    _newpath: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_renameat2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_request_key(
    _type: u32,
    _description: u32,
    _callout_info: u32,
    _destringid: u32,
) -> Result<u32, Err> {
    let msg = b"sys_request_key not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_restart_syscall() -> Result<u32, Err> {
    let msg = b"sys_restart_syscall not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_riscv_flush_icache(_start: u32, _end: u32) -> Result<u32, Err> {
    let msg = b"sys_riscv_flush_icache not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_riscv_hwprobe(
    _pairs: u32,
    _pair_count: u32,
    _cpu_set: u32,
    _cpu_set_size: u32,
) -> Result<u32, Err> {
    let msg = b"sys_riscv_hwprobe not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_rseq(_rseq: u32, _rseq_len: u32, _flags: u32, _sig: u32) -> Result<u32, Err> {
    let msg = b"sys_rseq not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_rt_sigpending(_set: u32, _sigsetsize: u32) -> Result<u32, Err> {
    let msg = b"sys_rt_sigpending not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_rt_sigqueueinfo(_pid: u32, _sig: u32, _uinfo: u32) -> Result<u32, Err> {
    let msg = b"sys_rt_sigqueueinfo not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_rt_sigreturn() -> Result<u32, Err> {
    let msg = b"sys_rt_sigreturn not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_rt_sigsuspend(_unewset: u32) -> Result<u32, Err> {
    let msg = b"sys_rt_sigsuspend not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_rt_sigtimedwait_time64(
    _uthese: u32,
    _uinfo: u32,
    _uts: u32,
    _sigsetsize: u32,
) -> Result<u32, Err> {
    let msg = b"sys_rt_sigtimedwait_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_rt_tgsigqueueinfo(_tgid: u32, _tid: u32, _sig: u32, _uinfo: u32) -> Result<u32, Err> {
    let msg = b"sys_rt_tgsigqueueinfo not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_get_priority_max(_policy: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_get_priority_max not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_get_priority_min(_policy: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_get_priority_min not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_getaffinity(_pid: u32, _len: u32, _user_mask_ptr: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_getaffinity not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_getattr(_pid: u32, _attr: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_getattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_getparam(_pid: u32, _param: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_getparam not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_getscheduler(_pid: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_getscheduler not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_rr_get_interval_time64(_pid: u32, _interval: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_rr_get_interval_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_setaffinity(_pid: u32, _len: u32, _user_mask_ptr: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_setaffinity not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_setattr(_pid: u32, _attr: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_setattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_setparam(_pid: u32, _param: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_setparam not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_setscheduler(_pid: u32, _policy: u32, _param: u32) -> Result<u32, Err> {
    let msg = b"sys_sched_setscheduler not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sched_yield() -> Result<u32, Err> {
    let msg = b"sys_sched_yield not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_seccomp(_operation: u32, _flags: u32, _args: u32) -> Result<u32, Err> {
    let msg = b"sys_seccomp not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_semctl(_semid: u32, _semnum: u32, _cmd: u32, _arg: u32) -> Result<u32, Err> {
    let msg = b"sys_semctl not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_semget(_key: u32, _nsems: u32, _semflg: u32) -> Result<u32, Err> {
    let msg = b"sys_semget not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_semop(_semid: u32, _sops: u32, _nsops: u32) -> Result<u32, Err> {
    let msg = b"sys_semop not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_semtimedop_time64(_semid: u32, _sops: u32, _nsops: u32, _timeout: u32) -> Result<u32, Err> {
    let msg = b"sys_semtimedop_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sendfile64(_out_fd: u32, _in_fd: u32, _offset: u32, _count: u32) -> Result<u32, Err> {
    let msg = b"sys_sendfile64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_set_mempolicy(
    _mode: u32,
    _nmask: u32,
    _maxnode: u32,
    _addr: u32,
    _flags: u32,
    _home_node: u32,
) -> Result<u32, Err> {
    let msg = b"sys_set_mempolicy not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_set_mempolicy_home_node(
    _start: u32,
    _len: u32,
    _home_node: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_set_mempolicy_home_node not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_set_robust_list(_head: u32, _len: u32) -> Result<u32, Err> {
    let msg = b"sys_set_robust_list not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setdomainname(_name: u32) -> Result<u32, Err> {
    let msg = b"sys_setdomainname not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setfsgid(_fsgid: u32) -> Result<u32, Err> {
    let msg = b"sys_setfsgid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setfsuid(_fsuid: u32) -> Result<u32, Err> {
    let msg = b"sys_setfsuid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setgid(_gid: u32) -> Result<u32, Err> {
    let msg = b"sys_setgid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setgroups(_size: u32, _list: u32) -> Result<u32, Err> {
    let msg = b"sys_setgroups not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sethostname(_name: u32) -> Result<u32, Err> {
    let msg = b"sys_sethostname not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setitimer(_which: u32, _value: u32) -> Result<u32, Err> {
    let msg = b"sys_setitimer not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setpgid(_pid: u32, _pgid: u32) -> Result<u32, Err> {
    let msg = b"sys_setpgid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setpriority(_which: u32, _who: u32, _niceval: u32) -> Result<u32, Err> {
    let msg = b"sys_setpriority not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setregid(_rgid: u32, _egid: u32) -> Result<u32, Err> {
    let msg = b"sys_setregid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setresgid(_rgid: u32, _egid: u32, _sgid: u32) -> Result<u32, Err> {
    let msg = b"sys_setresgid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setresuid(_ruid: u32, _euid: u32, _suid: u32) -> Result<u32, Err> {
    let msg = b"sys_setresuid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setreuid(_ruid: u32, _euid: u32) -> Result<u32, Err> {
    let msg = b"sys_setreuid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setsid() -> Result<u32, Err> {
    let msg = b"sys_setsid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setuid(_uid: u32) -> Result<u32, Err> {
    let msg = b"sys_setuid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_setxattr(
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

fn sys_setxattrat(
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

fn sys_shmat(_shmid: u32, _shmaddr: u32, _shmflg: u32) -> Result<u32, Err> {
    let msg = b"sys_shmat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_shmctl(_shmid: u32, _cmd: u32, _buf: u32) -> Result<u32, Err> {
    let msg = b"sys_shmctl not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_shmdt(_shmaddr: u32) -> Result<u32, Err> {
    let msg = b"sys_shmdt not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_shmget(_key: u32, _size: u32, _shmflg: u32, _version: u32) -> Result<u32, Err> {
    let msg = b"sys_shmget not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_signalfd4(_fd: u32, _mask: u32, _sizemask: u32) -> Result<u32, Err> {
    let msg = b"sys_signalfd4 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_splice(
    _fd_in: u32,
    _off_in: u32,
    _fd_out: u32,
    _off_out: u32,
    _len: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_splice not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_statfs64(_path: u32, _buf: u32) -> Result<u32, Err> {
    let msg = b"sys_statfs64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_statmount(_dfd: u32, _filename: u32, _buffer: u32, _bufsize: u32) -> Result<u32, Err> {
    let msg = b"sys_statmount not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_symlinkat(_target: u32, _newdirfd: u32, _linkpath: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_symlinkat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sync() -> Result<u32, Err> {
    let msg = b"sys_sync not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sync_file_range(_fd: u32, _offset: u32, _nbytes: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_sync_file_range not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_syncfs(_fd: u32) -> Result<u32, Err> {
    let msg = b"sys_syncfs not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_sysinfo(_info: u32) -> Result<u32, Err> {
    let msg = b"sys_sysinfo not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_syslog(_type: u32, _buf: u32, _len: u32) -> Result<u32, Err> {
    let msg = b"sys_syslog not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_tee(_fd_in: u32, _fd_out: u32, _len: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_tee not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_tgkill(_tgid: u32, _tid: u32, _sig: u32) -> Result<u32, Err> {
    let msg = b"sys_tgkill not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_timer_create(
    _which_clock: u32,
    _timer_event_spec: u32,
    _created_timer_id: u32,
) -> Result<u32, Err> {
    let msg = b"sys_timer_create not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_timer_delete(_timer_id: u32) -> Result<u32, Err> {
    let msg = b"sys_timer_delete not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_timer_getoverrun(_timer_id: u32) -> Result<u32, Err> {
    let msg = b"sys_timer_getoverrun not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_timer_gettime64(_timer_id: u32, _setting: u32) -> Result<u32, Err> {
    let msg = b"sys_timer_gettime64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_timer_settime64(
    _timer_id: u32,
    _flags: u32,
    _new_setting: u32,
    _old_setting: u32,
) -> Result<u32, Err> {
    let msg = b"sys_timer_settime64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_timerfd_create(_clockid: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_timerfd_create not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_timerfd_gettime64(_fd: u32, _curr_value: u32) -> Result<u32, Err> {
    let msg = b"sys_timerfd_gettime64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_timerfd_settime64(
    _fd: u32,
    _flags: u32,
    _new_value: u32,
    _old_value: u32,
) -> Result<u32, Err> {
    let msg = b"sys_timerfd_settime64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_times(_tbuf: u32) -> Result<u32, Err> {
    let msg = b"sys_times not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_truncate64(_path: u32, _length: u32) -> Result<u32, Err> {
    let msg = b"sys_truncate64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_umask(_mask: u32) -> Result<u32, Err> {
    let msg = b"sys_umask not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_uname(_buf: u32) -> Result<u32, Err> {
    let msg = b"sys_uname not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_unlinkat(_dfd: u32, _pathname: u32, _flag: u32) -> Result<u32, Err> {
    let msg = b"sys_unlinkat not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_unshare(_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_unshare not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_userfaultfd(_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_userfaultfd not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_utimensat_time64(_dfd: u32, _filename: u32, _times: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_utimensat_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_vmsplice(_fd: u32, _iov: u32, _nr_segs: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_vmsplice not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

fn sys_waitid(_which: u32, _upid: u32, _infop: u32, _options: u32, _ru: u32) -> Result<u32, Err> {
    let msg = b"sys_waitid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}
