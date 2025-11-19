use crate::{
    constants::{
        ASCII_TABLE_PTR, FILESYSTEM_IMAGE_ADDR_PTR, KERNEL_HEAP_START_ADDR, MEPC_PTR, PAGE_SIZE,
        REG_A0, REG_A1, REG_A2, REG_A3, REG_A4, REG_A5, REG_A7, REG_SP, USER_BRK_ADDR,
        USER_INTERP_ADDR, USER_INTERP_BASE_ADDR, USER_PHDR_ADDR_PTR, USER_PHDR_NUM_ADDR_PTR,
        USER_PHENT_SIZE, USER_STACK_ADDR, USER_STACK_PTR, USER_STACK_SIZE, USER_START_PTR,
    },
    host_calls::{host_argv, host_terminate},
    kernel::{get_ureg, mret, print},
    linux_abi_fs::{
        attach_to_p9, get_fd, get_file_desc, get_p9_enabled, init_fs, read_file_to_user_memory,
        set_p9_enabled, sys_statx,
    },
    p9::get_p9_traffic_hash,
    p9_backend::init_zerocopy_backend,
};

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
    sys_cachestat, sys_chdir, sys_close, sys_dup, sys_dup3, sys_faccessat, sys_faccessat2,
    sys_fadvise64_64, sys_fallocate, sys_fanotify_init, sys_fanotify_mark, sys_fchdir, sys_fchmod,
    sys_fchmodat, sys_fchmodat2, sys_fchown, sys_fchownat, sys_fcntl64, sys_fdatasync,
    sys_fgetxattr, sys_file_getattr, sys_file_setattr, sys_flistxattr, sys_flock, sys_fremovexattr,
    sys_fsetxattr, sys_fsync, sys_ftruncate64, sys_getcwd, sys_getdents64, sys_getxattr,
    sys_getxattrat, sys_ioctl, sys_lgetxattr, sys_linkat, sys_listxattr, sys_listxattrat,
    sys_llistxattr, sys_llseek, sys_lremovexattr, sys_lsetxattr, sys_mkdirat, sys_mknodat,
    sys_openat, sys_openat2, sys_pread64, sys_preadv, sys_preadv2, sys_pwrite64, sys_pwritev,
    sys_pwritev2, sys_read, sys_readahead, sys_readlinkat, sys_readv, sys_removexattr,
    sys_removexattrat, sys_renameat2, sys_sendfile64, sys_setxattr, sys_setxattrat, sys_statfs64,
    sys_symlinkat, sys_truncate64, sys_umask, sys_unlinkat, sys_utimensat_time64, sys_write,
    sys_writev,
};

// Import miscellaneous syscalls from the misc module
use crate::linux_abi_misc::{
    sys_clock_getres_time64, sys_clock_gettime64, sys_clock_nanosleep_time64, sys_clone,
    sys_clone3, sys_close_range, sys_copy_file_range, sys_epoll_create1, sys_epoll_ctl,
    sys_epoll_pwait, sys_epoll_pwait2, sys_eventfd2, sys_execve, sys_execveat, sys_fsconfig,
    sys_fsmount, sys_fsopen, sys_fspick, sys_fstatfs64, sys_futex_requeue, sys_futex_time64,
    sys_futex_wait, sys_futex_waitv, sys_futex_wake, sys_get_mempolicy, sys_get_robust_list,
    sys_getcpu, sys_getgroups, sys_getitimer, sys_getpgid, sys_getppid, sys_getpriority,
    sys_getrandom, sys_getresgid, sys_getresuid, sys_getrusage, sys_getsid, sys_gettid,
    sys_inotify_add_watch, sys_inotify_init1, sys_inotify_rm_watch, sys_io_cancel, sys_io_destroy,
    sys_io_pgetevents_time64, sys_io_setup, sys_io_submit, sys_io_uring_enter,
    sys_io_uring_register, sys_io_uring_setup, sys_ioprio_get, sys_ioprio_set, sys_kcmp, sys_kill,
    sys_listmount, sys_lookup_dcookie, sys_lsm_get_self_attr, sys_lsm_list_modules,
    sys_lsm_set_self_attr, sys_madvise, sys_map_shadow_stack, sys_mbind, sys_membarrier,
    sys_memfd_create, sys_memfd_secret, sys_migrate_pages, sys_mincore, sys_mlock, sys_mlock2,
    sys_mlockall, sys_move_mount, sys_move_pages, sys_mprotect, sys_mq_getsetattr, sys_mq_notify,
    sys_mq_open, sys_mq_timedreceive_time64, sys_mq_timedsend_time64, sys_mq_unlink, sys_mremap,
    sys_mseal, sys_msgctl, sys_msgget, sys_msgrcv, sys_msgsnd, sys_msync, sys_munlock,
    sys_munlockall, sys_name_to_handle_at, sys_open_by_handle_at, sys_open_tree,
    sys_open_tree_attr, sys_perf_event_open, sys_personality, sys_pidfd_getfd, sys_pidfd_open,
    sys_pidfd_send_signal, sys_pipe2, sys_pivot_root, sys_pkey_alloc, sys_pkey_free,
    sys_pkey_mprotect, sys_ppoll_time64, sys_prctl, sys_prlimit64, sys_process_madvise,
    sys_process_mrelease, sys_process_vm_readv, sys_process_vm_writev, sys_pselect6_time64,
    sys_ptrace, sys_quotactl, sys_quotactl_fd, sys_remap_file_pages, sys_request_key,
    sys_restart_syscall, sys_riscv_flush_icache, sys_riscv_hwprobe, sys_rseq, sys_rt_sigpending,
    sys_rt_sigqueueinfo, sys_rt_sigreturn, sys_rt_sigsuspend, sys_rt_sigtimedwait_time64,
    sys_rt_tgsigqueueinfo, sys_sched_get_priority_max, sys_sched_get_priority_min,
    sys_sched_getaffinity, sys_sched_getattr, sys_sched_getparam, sys_sched_getscheduler,
    sys_sched_rr_get_interval_time64, sys_sched_setaffinity, sys_sched_setattr, sys_sched_setparam,
    sys_sched_setscheduler, sys_sched_yield, sys_seccomp, sys_semctl, sys_semget, sys_semop,
    sys_semtimedop_time64, sys_set_mempolicy, sys_set_mempolicy_home_node, sys_set_robust_list,
    sys_setdomainname, sys_setfsgid, sys_setfsuid, sys_setgid, sys_setgroups, sys_sethostname,
    sys_setitimer, sys_setpgid, sys_setpriority, sys_setregid, sys_setresgid, sys_setresuid,
    sys_setreuid, sys_setsid, sys_setuid, sys_shmat, sys_shmctl, sys_shmdt, sys_shmget,
    sys_signalfd4, sys_splice, sys_statmount, sys_sync, sys_sync_file_range, sys_syncfs,
    sys_sysinfo, sys_syslog, sys_tee, sys_tgkill, sys_timer_create, sys_timer_delete,
    sys_timer_getoverrun, sys_timer_gettime64, sys_timer_settime64, sys_timerfd_create,
    sys_timerfd_gettime64, sys_timerfd_settime64, sys_times, sys_uname, sys_unshare,
    sys_userfaultfd, sys_vmsplice, sys_waitid,
};

static mut BRK: u32 = 0u32;

#[cfg(target_arch = "riscv32")]
use alloc::string::String;
#[cfg(target_arch = "riscv32")]
use alloc::string::ToString;
#[cfg(target_arch = "riscv32")]
use alloc::vec;
#[cfg(target_arch = "riscv32")]
use alloc::vec::Vec;

static mut MMAP_BASE: u32 = 0x94800000;

fn get_mmap_base() -> u32 {
    unsafe { MMAP_BASE }
}

fn set_mmap_base(base: u32) {
    unsafe { MMAP_BASE = base }
}

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
    FileNotFound = -2, // ENOENT
    IO = -5,           // EIO - I/O error
    BadFd = -9,        // EBADF - Bad file descriptor
    #[allow(dead_code)]
    NoMem = -12, // ENOMEM
    Access = -13,      // EACCES - Permission denied
    Fault = -14,       // EFAULT - Bad address
    FileExists = -17,  // EEXIST
    NotDir = -20,      // ENOTDIR - Not a directory
    IsDir = -21,       // EISDIR - Is a directory
    Inval = -22,       // EINVAL
    MFile = -24,       // EMFILE - Too many open files
    FileTooBig = -27,  // EFBIG - File too large
    NoSpc = -28,       // ENOSPC - No space left on device
    NameTooLong = -36, // ENAMETOOLONG - File name too long
    NoSys = -38,       // ENOSYS - Function not implemented
    Loop = -40,        // ELOOP - Too many symbolic links encountered
    Range = -34,       // ERANGE - Result too large / Math result not representable
    NoData = -61,      // ENODATA - No data available
    OpNotSupp = -95,   // EOPNOTSUPP - Operation not supported
}

impl Err {
    pub fn as_errno(&self) -> u32 {
        *self as u32
    }
}

// Memory region tracking for EFAULT validation
#[derive(Clone, Copy, Debug)]
#[allow(dead_code)]
pub struct MemoryRegion {
    pub start: u32,
    pub end: u32, // Exclusive end address
    pub readable: bool,
    pub writable: bool,
    pub executable: bool,
    pub name: &'static str,
}

#[allow(dead_code)]
impl MemoryRegion {
    const fn new_empty() -> Self {
        Self {
            start: 0,
            end: 0,
            readable: false,
            writable: false,
            executable: false,
            name: "",
        }
    }

    fn is_empty(&self) -> bool {
        self.start == 0 && self.end == 0
    }

    fn contains(&self, addr: u32) -> bool {
        !self.is_empty() && addr >= self.start && addr < self.end
    }

    fn contains_range(&self, addr: u32, len: usize) -> bool {
        if self.is_empty() || len == 0 {
            return false;
        }
        let end_addr = addr.saturating_add(len as u32);
        addr >= self.start && end_addr <= self.end && end_addr >= addr
    }
}

/// Register ELF program memory region
/// This registers a large region from load_base to heap start, covering all ELF-loaded memory.
/// Also registers the interpreter region if present.
/// This is simpler and more robust than parsing individual segments.
fn register_elf_segments() {
    use crate::constants::{USER_BRK_ADDR, USER_INTERP_BASE_ADDR};

    // Use the same hardcoded load_base as the ELF loader
    // ELF_ET_DYN_BASE = (2/3) * TASK_SIZE = (2/3) * 0x9c800000 ≈ 0x68555555
    // → page-align → 0x68555000
    let load_base = 0x68555000u32;

    // Get heap start (brk) from stored value
    let heap_start = unsafe { USER_BRK_ADDR.read_volatile() as u32 };

    if heap_start == 0 {
        kprint!("register_elf_segments: No heap start (brk=0), skipping ELF region registration");
        return;
    }

    if heap_start <= load_base {
        kprint!(
            "register_elf_segments: Invalid range (load_base=0x{:08x} >= heap_start=0x{:08x}), skipping",
            load_base,
            heap_start
        );
        return;
    }

    kprint!(
        "register_elf_segments: Registering main ELF region [0x{:08x}-0x{:08x}) (load_base to heap start)",
        load_base,
        heap_start
    );

    // Register the entire region from load_base to heap_start as readable, writable, and executable
    // This covers all ELF-loaded segments (code, data, BSS, etc.)
    register_memory_region(
        load_base,
        heap_start,
        true, // readable
        true, // writable (data segments need this)
        true, // executable (code segments need this)
        "elf-loaded-memory",
    );

    // Register interpreter region if present
    // The interpreter is loaded with load_bias (stored as interp_base_addr) and ends at the initial mmap_base
    let interp_base_addr = unsafe { USER_INTERP_BASE_ADDR.read_volatile() };
    if interp_base_addr != 0 {
        // The interpreter is placed so its top ends at the initial mmap_base
        // Use the same hardcoded mmap_base calculation as the ELF loader
        const TASK_SIZE: u32 = 0x9C80_0000; // User VA ceiling (STACK_TOP / FIXADDR_START)
        const STACK_GAP: u32 = 0x0800_0000; // 128 MiB
        const BIG_ALIGN: u32 = 0x0080_0000; // 8 MiB alignment for mmap_base
        let initial_mmap_base = (TASK_SIZE - STACK_GAP) & !(BIG_ALIGN - 1); // → 0x94800000
        let interp_end = initial_mmap_base;

        if interp_end <= interp_base_addr as u32 {
            kprint!(
                "register_elf_segments: Invalid interpreter range (base=0x{:08x} >= end=0x{:08x}), skipping",
                interp_base_addr,
                interp_end
            );
        } else {
            kprint!(
                "register_elf_segments: Registering interpreter region [0x{:08x}-0x{:08x})",
                interp_base_addr,
                interp_end
            );

            // Register interpreter region as readable, writable, and executable
            register_memory_region(
                interp_base_addr as u32,
                interp_end,
                true, // readable
                true, // writable
                true, // executable
                "interpreter-memory",
            );
        }
    }
}

// Global memory map (fixed-size array for no_std compatibility)
const MAX_MEMORY_REGIONS: usize = 128;
static mut MEMORY_REGIONS: [MemoryRegion; MAX_MEMORY_REGIONS] =
    [MemoryRegion::new_empty(); MAX_MEMORY_REGIONS];
static mut MEMORY_REGION_COUNT: usize = 0;

// Memory map functions
pub fn register_memory_region(
    start: u32,
    end: u32,
    readable: bool,
    writable: bool,
    executable: bool,
    name: &'static str,
) {
    use crate::constants::{KERNEL_SPACE_START, USER_MEMORY_START_PTR};

    if start == 0 || end == 0 || start >= end {
        kprint!(
            "register_memory_region: rejecting invalid range [{:08x}-{:08x}) {}",
            start,
            end,
            name
        );
        return;
    }

    if start < USER_MEMORY_START_PTR as u32 {
        kprint!(
            "register_memory_region: rejecting range below user memory [{:08x}-{:08x}) {}",
            start,
            end,
            name
        );
        return;
    }

    if end > KERNEL_SPACE_START {
        kprint!(
            "register_memory_region: rejecting range crossing kernel space [{:08x}-{:08x}) {}",
            start,
            end,
            name
        );
        return;
    }

    let range_overlaps =
        |a_start: u32, a_end: u32, b_start: u32, b_end: u32| a_start < b_end && b_start < a_end;

    // Check if the new region is completely contained within an existing region
    let is_contained_in = |new_start: u32, new_end: u32, existing_start: u32, existing_end: u32| {
        new_start >= existing_start && new_end <= existing_end
    };

    unsafe {
        let mut idx = 0;
        while idx < MEMORY_REGION_COUNT {
            let existing = &MEMORY_REGIONS[idx];
            if existing.is_empty() {
                idx += 1;
                continue;
            }

            // If the new region is completely contained within an existing region,
            // it's already covered - allow it (no need to register again)
            if is_contained_in(start, end, existing.start, existing.end) {
                kprint!(
                    "register_memory_region: [{:08x}-{:08x}) {} is already covered by {} [{:08x}-{:08x}), skipping registration",
                    start,
                    end,
                    name,
                    existing.name,
                    existing.start,
                    existing.end
                );
                return;
            }

            // If there's an overlap but the new region is not contained, reject it
            if range_overlaps(start, end, existing.start, existing.end) {
                kprint!(
                    "register_memory_region: rejecting [{:08x}-{:08x}) {} due to overlap with {} [{:08x}-{:08x})",
                    start,
                    end,
                    name,
                    existing.name,
                    existing.start,
                    existing.end
                );
                return;
            }
            idx += 1;
        }

        if MEMORY_REGION_COUNT < MAX_MEMORY_REGIONS {
            kprint!(
                "register_memory_region: [{:08x}-{:08x}) {} r:{} w:{} x:{}",
                start,
                end,
                name,
                readable,
                writable,
                executable
            );
            MEMORY_REGIONS[MEMORY_REGION_COUNT] = MemoryRegion {
                start,
                end,
                readable,
                writable,
                executable,
                name,
            };
            MEMORY_REGION_COUNT += 1;
        } else {
            kprint!("register_memory_region: WARNING - MAX_MEMORY_REGIONS reached!");
        }
    }
}

pub fn unregister_memory_region(start: u32, end: u32) {
    unsafe {
        let mut idx = 0;
        while idx < MEMORY_REGION_COUNT {
            if MEMORY_REGIONS[idx].start == start && MEMORY_REGIONS[idx].end == end {
                kprint!(
                    "unregister_memory_region: [{:08x}-{:08x}) {}",
                    start,
                    end,
                    MEMORY_REGIONS[idx].name
                );
                let slice = &mut MEMORY_REGIONS[..MEMORY_REGION_COUNT];
                if idx + 1 < slice.len() {
                    slice.copy_within(idx + 1.., idx);
                }
                MEMORY_REGIONS[MEMORY_REGION_COUNT - 1] = MemoryRegion::new_empty();
                MEMORY_REGION_COUNT -= 1;
                break;
            }
            idx += 1;
        }
    }
}

/// Check if a user address range is valid and return the maximum safe length
/// Returns Some(max_len) if valid, where max_len is the maximum number of bytes
/// that can be safely accessed from addr. Returns None if invalid.
/// If the range is fully contained, max_len will be the requested len.
/// If the range extends beyond a region, max_len will be the available bytes in that region.
#[allow(dead_code)]
pub fn is_valid_user_address(addr: u32, len: usize, require_write: bool) -> Option<usize> {
    use crate::constants::{KERNEL_SPACE_START, USER_MEMORY_START_PTR, USER_SPACE_END};

    if len == 0 {
        return Some(0);
    }

    if addr < USER_MEMORY_START_PTR as u32 {
        kprint!(
            "is_valid_user_address: addr={:08x} len={} below USER_MEMORY_START ({:08x})",
            addr,
            len,
            USER_MEMORY_START_PTR as u32
        );
        return None;
    }

    let end_addr = match addr.checked_add(len as u32) {
        Some(val) => val,
        None => {
            kprint!(
                "is_valid_user_address: addr={:08x} len={} overflow",
                addr,
                len
            );
            return None;
        }
    };

    if end_addr > USER_SPACE_END {
        kprint!(
            "is_valid_user_address: addr={:08x} len={} end={:08x} exceeds USER_SPACE_END ({:08x})",
            addr,
            len,
            end_addr,
            USER_SPACE_END
        );
        return None;
    }

    if addr >= KERNEL_SPACE_START || end_addr > KERNEL_SPACE_START {
        kprint!(
            "is_valid_user_address: addr={:08x} len={} end={:08x} in kernel space (>= {:08x})",
            addr,
            len,
            end_addr,
            KERNEL_SPACE_START
        );
        return None;
    }

    unsafe {
        // Dump all registered regions for debugging
        let region_count = MEMORY_REGION_COUNT;
        kprint!(
            "is_valid_user_address: checking addr={:08x} len={} end={:08x} require_write={}, {} regions registered:",
            addr,
            len,
            end_addr,
            require_write,
            region_count
        );
        let mut idx = 0;
        while idx < region_count {
            let region = &MEMORY_REGIONS[idx];
            if !region.is_empty() {
                let contains = region.contains_range(addr, len);
                // Also check if the start address is in the region (for cases where range extends slightly beyond)
                let start_in_region = region.contains(addr);
                kprint!(
                    "  [{:08x}-{:08x}) {} r:{} w:{} x:{} {}",
                    region.start,
                    region.end,
                    region.name,
                    region.readable,
                    region.writable,
                    region.executable,
                    if contains {
                        "<- FULLY CONTAINS"
                    } else if start_in_region {
                        "<- START IN REGION"
                    } else {
                        ""
                    }
                );
                // Accept if fully contained, or if start is in region (allows slight overflow for stack/heap)
                if contains || start_in_region {
                    let valid = if require_write {
                        region.writable
                    } else {
                        region.readable
                    };
                    if !valid {
                        kprint!(
                            "is_valid_user_address: INVALID (require_write={}, region.writable={}, region.readable={})",
                            require_write,
                            region.writable,
                            region.readable
                        );
                        return None;
                    }

                    // Calculate maximum safe length
                    let max_len = if contains {
                        // Fully contained - can use full requested length
                        len
                    } else {
                        // Start in region but extends beyond - calculate available bytes
                        let available_bytes = (region.end - addr) as usize;
                        core::cmp::min(len, available_bytes)
                    };

                    kprint!(
                        "is_valid_user_address: VALID up to {} bytes (requested={}, fully_contained={})",
                        max_len,
                        len,
                        contains
                    );
                    return Some(max_len);
                }
            }
            idx += 1;
        }

        if MEMORY_REGION_COUNT == 0 {
            kprint!("is_valid_user_address: no regions registered, allowing access");
            return Some(len);
        }
    }

    kprint!(
        "is_valid_user_address: addr={:08x} len={} not found in any region",
        addr,
        len
    );
    None
}

#[allow(dead_code)]
pub fn dump_memory_regions() {
    kprint!("=== Memory Regions ({} total) ===", unsafe {
        MEMORY_REGION_COUNT
    });
    unsafe {
        let mut idx = 0;
        while idx < MEMORY_REGION_COUNT {
            let r = &MEMORY_REGIONS[idx];
            kprint!(
                "  [{:08x}-{:08x}) {} r:{} w:{} x:{}",
                r.start,
                r.end,
                r.name,
                r.readable,
                r.writable,
                r.executable
            );
            idx += 1;
        }
    }
}

#[allow(unused)]
#[derive(Clone, Copy)]
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
        kprint!(
            "UserStack::add_aux_word: atype={:?}, word={:08x}",
            atype as usize,
            word
        );
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

/// Initialize zero-copy P9 backend from embedded filesystem image
fn init_p9_zerocopy_backend() {
    use crate::host_calls::host_terminate;

    unsafe {
        // Read filesystem image address from memory
        print(&str_format!(
            str256,
            "Reading FS address from ptr: 0x{:08x}",
            FILESYSTEM_IMAGE_ADDR_PTR as u32
        ));
        let fs_addr = *FILESYSTEM_IMAGE_ADDR_PTR;
        print(&str_format!(str256, "Read FS address: 0x{:08x}", fs_addr));

        if fs_addr == 0 {
            print("FATAL: opts=p9mem specified but no filesystem embedded!");
            print("Use: elf-to-bin --root <dir> to embed a filesystem");
            host_terminate(1, 0);
        }

        print(&str_format!(
            str256,
            "Initializing zero-copy filesystem at 0x{:08x}",
            fs_addr
        ));

        // Note: Large filesystems may be placed in user space, which is fine
        // as they're read-only and won't conflict with user programs
        if fs_addr < 0xC0000000 {
            print("  Note: Large FS placed in upper user space (read-only, safe)");
        }

        // Initialize the zero-copy backend
        // Use very large max size - the header's total_size will be the actual limit
        const MAX_FS_SIZE: usize = 1024 * 1024 * 1024; // 1GB max
        print(&str_format!(
            str256,
            "  Max allowed FS size: {} MB",
            MAX_FS_SIZE / (1024 * 1024)
        ));

        match init_zerocopy_backend(fs_addr as usize, MAX_FS_SIZE) {
            Ok(fs_size) => {
                print(&str_format!(
                    str256,
                    "Filesystem loaded: {} bytes ({:.2} MB)",
                    fs_size,
                    fs_size as f64 / (1024.0 * 1024.0)
                ));

                // Verify filesystem fits below heap
                let fs_end = fs_addr as usize + fs_size;
                if fs_end > KERNEL_HEAP_START_ADDR {
                    print("FATAL: Filesystem extends into kernel heap!");
                    print(&str_format!(str256, "  FS end:    0x{:08x}", fs_end));
                    print(&str_format!(
                        str256,
                        "  Heap start: 0x{:08x}",
                        KERNEL_HEAP_START_ADDR
                    ));
                    print("  Reduce filesystem size or increase heap start address");
                    host_terminate(1, 0);
                }

                print(&str_format!(str256, "  FS ends at: 0x{:08x}", fs_end));
                print(&str_format!(
                    str256,
                    "  Heap starts: 0x{:08x} (fixed)",
                    KERNEL_HEAP_START_ADDR
                ));
                print("Zero-copy P9 backend activated");
            }
            Err(errno) => {
                print(&str_format!(
                    str256,
                    "FATAL: Failed to initialize filesystem: error {}",
                    errno
                ));
                print(&str_format!(
                    str256,
                    "  Filesystem address: 0x{:08x}",
                    fs_addr
                ));
                print("  Check that filesystem was properly embedded with elf-to-bin --root");
                host_terminate(1, 0);
            }
        }
    }
}

pub fn start_linux_binary(argc: u32) -> ! {
    init_fs();

    // Register ELF program segments first (before stack, so they take priority)
    register_elf_segments();

    // Track the user stack region so pointer validation accepts stack addresses
    let stack_top = USER_STACK_ADDR as u32;
    let stack_start = stack_top - USER_STACK_SIZE as u32;
    register_memory_region(stack_start, stack_top, true, true, false, "user-stack");

    // Track the ASCII table region (used for pathname helper data near the top of user VA space)
    let ascii_table_start = ASCII_TABLE_PTR as u32;
    let ascii_table_end = ascii_table_start.saturating_add(PAGE_SIZE as u32);
    register_memory_region(
        ascii_table_start,
        ascii_table_end,
        true,
        false,
        false,
        "ascii-table",
    );

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
            let opt = &argv[0];

            if opt == "opts=p9mem" {
                // Zero-copy in-memory filesystem (set as active backend)
                set_p9_enabled(true);
                init_p9_zerocopy_backend();
                print("doneeee");
            } else if opt == "opts=p9zc" {
                // Initialize zero-copy filesystem but use zkVM backend for operations
                set_p9_enabled(true);
            } else if opt.starts_with("opts=p9") {
                // Traditional P9 over host calls (zkVM backend)
                set_p9_enabled(true);
                // Backend defaults to Zkvm, no action needed
            }

            argv.remove(0);
        } else {
            set_p9_enabled(false);
        }
    }
    let mut stack = UserStack::new();
    stack.add_word(argv.len());

    if get_p9_enabled() {
        attach_to_p9();
    }

    let _user_start_addr: usize = unsafe { USER_START_PTR.read_volatile() };
    let interp_base_addr = unsafe { USER_INTERP_BASE_ADDR.read_volatile() };
    let interp_addr = unsafe { USER_INTERP_ADDR.read_volatile() };

    // Set mmap_base to start of interpreter (for top-down allocation below it)
    // The interpreter was placed to end at the initial mmap_base (0x94800000),
    // so we need to set mmap_base to its start address to avoid overlap with
    // future mmap allocations (which grow downward from mmap_base)
    if interp_base_addr != 0 {
        // 0x3000 is vvar, vdso, to align with memory offsets in real rv32
        let _mmap_base = interp_base_addr as u32 - 0x3000;
        set_mmap_base(interp_base_addr as u32);
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

    let user_start_addr: usize = unsafe { USER_START_PTR.read_volatile() };

    if interp_base_addr != 0 {
        stack.add_aux_word(AuxType::Entry, user_start_addr);
        stack.add_aux_word(AuxType::Base, interp_base_addr);
        unsafe { BRK = USER_BRK_ADDR.read_volatile() as u32 };
    }
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

    if interp_addr != 0 {
        kprint!(
            "starting linux binary with interpreter at 0x{:08x}",
            interp_addr,
        );
        kprint!("AT_BASE (interp load addr) = 0x{:08x}", interp_base_addr);
        kprint!("AT_ENTRY (main entry) = 0x{:08x}", user_start_addr);
        kprint!("AT_PHDR (main phdr) = 0x{:08x}", unsafe {
            USER_PHDR_ADDR_PTR.read_volatile()
        });
        unsafe {
            MEPC_PTR.write_volatile(interp_addr - 4);
        }
    } else {
        print("starting linux binary");
        unsafe {
            // Apply -4 adjustment for MEPC circuit bug
            MEPC_PTR.write_volatile(user_start_addr - 4);
        }
    }
    mret()
}

pub fn handle_linux_syscall() -> ! {
    let nr = get_ureg(REG_A7);
    kprint!("handle_linux_syscall: nr={}", nr);
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
        SYS_FACCESSAT2 => syscall4(sys_faccessat2),
        SYS_FADVISE64_64 => syscall4(sys_fadvise64_64),
        SYS_FALLOCATE => syscall6(sys_fallocate),
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
        SYS_LLSEEK => syscall5(sys_llseek),
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
        SYS_OPENAT2 => syscall4(sys_openat2),
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
        SYS_READLINKAT => syscall4(sys_readlinkat),
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
        SYS_STATFS64 => syscall3(sys_statfs64),
        SYS_STATMOUNT => syscall4(sys_statmount),
        SYS_STATX => syscall5(sys_statx),
        SYS_SWAPOFF => syscall1(sys_swapoff),
        SYS_SWAPON => syscall3(sys_swapon),
        SYS_SYMLINKAT => syscall3(sys_symlinkat),
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
    kprint!("sys_brk: addr = {:08x}", addr);

    unsafe {
        // Get current BRK value
        let current_brk = core::ptr::addr_of!(BRK).read_volatile();

        // Initialize BRK to the original break address if it's not set
        if current_brk == 0 {
            let original_brk = USER_BRK_ADDR.read_volatile() as u32;
            core::ptr::addr_of_mut!(BRK).write_volatile(original_brk);
            kprint!("sys_brk: initialized BRK to {:08x}", original_brk);

            // If addr is 0, return the initialized break
            if addr == 0 {
                return Ok(original_brk);
            }
        } else {
            // If addr is 0, return the current break
            if addr == 0 {
                kprint!("sys_brk: returning current BRK = {:08x}", current_brk);
                return Ok(current_brk);
            }
        }

        let original_brk = USER_BRK_ADDR.read_volatile() as u32;
        let current_brk = core::ptr::addr_of!(BRK).read_volatile();

        // Validate the new address
        // Don't allow setting it below the original break
        if addr < original_brk {
            kprint!(
                "sys_brk: addr {:08x} < original_brk {:08x}, returning current BRK",
                addr,
                original_brk
            );
            return Ok(current_brk);
        }

        // Don't allow setting it too high (arbitrary limit to prevent abuse)
        const MAX_BRK_SIZE: u32 = 64 * 1024 * 1024; // 64 MB
        if addr > original_brk + MAX_BRK_SIZE {
            kprint!("sys_brk: addr {:08x} too high, returning current BRK", addr);
            return Ok(current_brk);
        }

        // Update the break
        let old_brk = current_brk;
        core::ptr::addr_of_mut!(BRK).write_volatile(addr);
        kprint!("sys_brk: updated BRK from {:08x} to {:08x}", old_brk, addr);

        // Update memory region tracking
        // Unregister old heap region if it exists
        if old_brk != original_brk {
            unregister_memory_region(original_brk, old_brk);
        }
        // Register new heap region
        register_memory_region(original_brk, addr, true, true, false, "heap");

        Ok(addr)
    }
}

fn align_up(addr: usize, align: usize) -> usize {
    (addr + align - 1) & !(align - 1)
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
    pgoffset: u32,
) -> Result<u32, Err> {
    let _fd = fd as i32;
    kprint!("sys_mmap(0x{_addr:08x}, {len}, {_prot}, 0x{_flags:08x}, {_fd}, {pgoffset})");

    // Check file descriptor validity for file-backed mappings first
    // (EBADF has priority over EINVAL for length/flags)
    // Note: fd=-1 is only valid if MAP_ANONYMOUS flag is set
    let has_anon_flag = (_flags & 0x20) == 0x20; // MAP_ANONYMOUS
    let is_file_backed = !has_anon_flag; // File-backed if no MAP_ANONYMOUS flag

    if is_file_backed {
        // For file-backed mappings, validate fd first (before length/flags)
        // fd=-1 without MAP_ANONYMOUS is invalid
        if _fd == -1 || fd >= 256 {
            kprint!(
                "sys_mmap: EBADF - invalid fd {} for file-backed mapping",
                _fd
            );
            return Err(Err::BadFd);
        }
        let fd_entry = get_fd(fd);
        if fd_entry.file_desc_id == 0xFF {
            kprint!("sys_mmap: EBADF - fd {} is not open", fd);
            return Err(Err::BadFd);
        }
    }

    // Validate length
    if len == 0 {
        return Err(Err::Inval);
    }

    // Validate flags - must contain one of MAP_PRIVATE, MAP_SHARED, or MAP_SHARED_VALIDATE
    const MAP_PRIVATE: u32 = 0x02;
    const MAP_SHARED: u32 = 0x01;
    const MAP_SHARED_VALIDATE: u32 = 0x03;

    let has_valid_sharing = (_flags & MAP_PRIVATE) != 0
        || (_flags & MAP_SHARED) != 0
        || (_flags & MAP_SHARED_VALIDATE) != 0;

    if !has_valid_sharing {
        kprint!("sys_mmap: invalid flags - missing MAP_PRIVATE/MAP_SHARED");
        return Err(Err::Inval);
    }

    // Check file descriptor permissions for file-backed mappings
    if is_file_backed {
        // For file-backed mappings, check fd permissions
        if fd < 256 {
            let fd_entry = get_fd(fd);
            // We already checked fd is valid above, so this should always succeed
            if fd_entry.file_desc_id != 0xFF {
                let file_desc = get_file_desc(fd_entry.file_desc_id);
                let open_mode = file_desc.flags & 0x3; // O_RDONLY=0, O_WRONLY=1, O_RDWR=2

                kprint!(
                    "sys_mmap: checking permissions - open_mode={}, prot=0x{:x}, flags=0x{:x}",
                    open_mode,
                    _prot,
                    _flags
                );

                // Check if fd has read permission when PROT_READ or PROT_WRITE is requested
                // (even PROT_WRITE requires read permission for private mappings)
                if ((_prot & 0x1) != 0 || (_prot & 0x2) != 0) && open_mode == 1 {
                    // File opened write-only but read/write access requested
                    kprint!(
                        "sys_mmap: EACCES - fd opened write-only but PROT_READ/WRITE requested"
                    );
                    return Err(Err::Access);
                }

                // Check if fd has write permission when PROT_WRITE with MAP_SHARED is requested
                if (_prot & 0x2) != 0 && (_flags & MAP_SHARED) != 0 && open_mode == 0 {
                    // PROT_WRITE=0x2
                    // File opened read-only but write with MAP_SHARED is requested
                    kprint!(
                        "sys_mmap: EACCES - fd opened read-only but PROT_WRITE+MAP_SHARED requested"
                    );
                    return Err(Err::Access);
                }
            }
        }
    }

    kprint!("user_brk_start = {:08x}", unsafe {
        USER_BRK_ADDR.read_volatile() as u32
    });
    kprint!("brk = {:08x}", unsafe { BRK });
    if _addr >= unsafe { USER_BRK_ADDR.read_volatile() as u32 }
        && _addr + len <= unsafe { BRK }
        && _flags & MAP_FIXED == MAP_FIXED
        && _prot == 0
    {
        // musl wants to make this unavailable, we just happily comply
        kprint!(
            "sys_mmap: musl wants to make {:08x}-{:08x} unavailable with PROT_NONE, we just OK(0)",
            _addr,
            _addr + len
        );
        return Ok(0);
    }

    let offset = pgoffset as u64 * PAGE_SIZE as u64;
    const MAP_FIXED: u32 = 0x10;
    // MAP_ANONYMOUS already defined above
    if _flags & MAP_FIXED == MAP_FIXED {
        kprint!("sys_mmap: MAP_FIXED is set");
    }

    // Check for address overflow and invalid high memory regions
    // Reject any attempt to map into kernel space (>= 0xC0000000)
    if _addr != 0 {
        // Check if starting address is in kernel space
        if _addr >= 0xc000_0000 {
            kprint!(
                "sys_mmap: address in kernel space - addr=0x{:08x}, returning EINVAL",
                _addr
            );
            return Err(Err::Inval);
        }
        // Check for overflow when adding length to address
        let end_addr = _addr.wrapping_add(len);
        if end_addr < _addr {
            // Overflow occurred - address wraps around
            kprint!(
                "sys_mmap: address overflow - addr=0x{:08x} len={}, returning EINVAL",
                _addr,
                len
            );
            return Err(Err::Inval);
        }
        // Check if address range extends into kernel space
        if end_addr > 0xc000_0000 {
            kprint!(
                "sys_mmap: addr outside mmap space - end=0x{:08x}, returning EINVAL",
                end_addr
            );
            return Err(Err::Inval);
        }
    }

    // Use the is_file_backed variable we computed earlier
    // is_file_backed = true means not anonymous
    let is_anonymous = !is_file_backed;

    if is_anonymous && _flags & MAP_FIXED != MAP_FIXED {
        let mmap_base = get_mmap_base();
        let aligned_length = align_up(len as usize, PAGE_SIZE);
        // mmap grows down
        let new_mmap_base = (mmap_base as usize - aligned_length) as u32;

        if new_mmap_base
            != align_up(new_mmap_base as usize, PAGE_SIZE)
                .try_into()
                .unwrap()
        {
            kpanic!("sys_mmap: mmap base is not aligned to page size anymore");
        }
        let ptr: *mut u8 = new_mmap_base as *mut u8;
        unsafe {
            ptr.write_bytes(0, aligned_length);
        }
        kprint!("sys_mmap: new mmap base = {:08x}", new_mmap_base);
        set_mmap_base(new_mmap_base);

        // Track the allocated region
        let readable = (_prot & 0x1) != 0; // PROT_READ
        let writable = (_prot & 0x2) != 0; // PROT_WRITE
        let executable = (_prot & 0x4) != 0; // PROT_EXEC
        register_memory_region(
            new_mmap_base,
            new_mmap_base + aligned_length as u32,
            readable,
            writable,
            executable,
            "mmap-anon",
        );

        Ok(ptr as u32)
    } else if !is_anonymous && _flags & MAP_FIXED != MAP_FIXED {
        let mmap_base = get_mmap_base();
        let aligned_length = align_up(len as usize, PAGE_SIZE);
        // mmap grows down
        let new_mmap_base = (mmap_base as usize - aligned_length) as u32;

        if new_mmap_base
            != align_up(new_mmap_base as usize, PAGE_SIZE)
                .try_into()
                .unwrap()
        {
            kpanic!("sys_mmap: mmap base is not aligned to page size anymore");
        }
        kprint!("sys_mmap: new mmap base = {:08x}", new_mmap_base);
        set_mmap_base(new_mmap_base);
        let ptr: *mut u8 = new_mmap_base as *mut u8;
        let bytes_read = read_file_to_user_memory(fd, ptr as u32, len, offset)?;
        // Zero-fill beyond EOF up to aligned length (Linux behavior)
        if bytes_read < aligned_length as u32 {
            let zero_len = aligned_length - bytes_read as usize;
            unsafe {
                let zero_start = ptr.add(bytes_read as usize);
                zero_start.write_bytes(0, zero_len);
            }
            kprint!(
                "sys_mmap: zero-filled from {:08x} to {:08x} ({} bytes beyond EOF)",
                ptr as u32 + bytes_read,
                ptr as u32 + aligned_length as u32,
                zero_len
            );
        }

        // Track the allocated region
        let readable = (_prot & 0x1) != 0; // PROT_READ
        let writable = (_prot & 0x2) != 0; // PROT_WRITE
        let executable = (_prot & 0x4) != 0; // PROT_EXEC
        register_memory_region(
            new_mmap_base,
            new_mmap_base + aligned_length as u32,
            readable,
            writable,
            executable,
            "mmap-file",
        );

        Ok(ptr as u32)
    } else if !is_anonymous && _flags & MAP_FIXED == MAP_FIXED && _addr != 0 {
        kprint!(
            "sys_mmap: wishing {:08x}-{:08x} to be mapped, and our mmap base is {:08x}",
            _addr,
            _addr + len,
            get_mmap_base()
        );
        let ptr: *mut u8 = _addr as *mut u8;
        let aligned_length = align_up(len as usize, PAGE_SIZE);
        let bytes_read = read_file_to_user_memory(fd, _addr, len, offset)?;
        // Zero-fill beyond EOF up to aligned length (Linux behavior)
        if bytes_read < aligned_length as u32 {
            let zero_len = aligned_length - bytes_read as usize;
            unsafe {
                let zero_start = ptr.add(bytes_read as usize);
                zero_start.write_bytes(0, zero_len);
            }
            kprint!(
                "sys_mmap: zero-filled from {:08x} to {:08x} ({} bytes beyond EOF)",
                _addr + bytes_read,
                _addr + aligned_length as u32,
                zero_len
            );
        }
        if _addr + len < get_mmap_base() {
            kpanic!("sys_mmap: mmap base + len < get_mmap_base()");
        }

        // Track the allocated region
        let readable = (_prot & 0x1) != 0; // PROT_READ
        let writable = (_prot & 0x2) != 0; // PROT_WRITE
        let executable = (_prot & 0x4) != 0; // PROT_EXEC
        register_memory_region(
            _addr,
            _addr + aligned_length as u32,
            readable,
            writable,
            executable,
            "mmap-file-fixed",
        );

        kprint!("sys_mmap: returning {:08x}", ptr as u32);
        Ok(ptr as u32)
    } else if is_anonymous && _flags & MAP_FIXED == MAP_FIXED && _addr != 0 {
        let ptr: *mut u8 = _addr as *mut u8;
        let aligned_length = align_up(len as usize, PAGE_SIZE);
        unsafe {
            ptr.write_bytes(0, aligned_length);
        }

        // Track the allocated region
        let readable = (_prot & 0x1) != 0; // PROT_READ
        let writable = (_prot & 0x2) != 0; // PROT_WRITE
        let executable = (_prot & 0x4) != 0; // PROT_EXEC
        register_memory_region(
            _addr,
            _addr + aligned_length as u32,
            readable,
            writable,
            executable,
            "mmap-anon-fixed",
        );

        kprint!("sys_mmap: returning {:08x}", ptr as u32);
        Ok(ptr as u32)
    } else {
        kpanic!("sys_mmap: unsupported scenario");
    }
}

/// https://man7.org/linux/man-pages/man2/mmap.2.html
fn sys_munmap(addr: u32, _len: u32) -> Result<u32, Err> {
    // munmap() unmaps the specified address range
    // In a zkVM environment without real virtual memory management,
    // we implement this as a validated no-op

    kprint!("sys_munmap: addr=0x{:08x}, len={}", addr, _len);

    // Validate address is not NULL
    if addr == 0 {
        kprint!("sys_munmap: addr is NULL");
        return Err(Err::Inval);
    }

    // Validate address is page-aligned
    if !addr.is_multiple_of(PAGE_SIZE as u32) {
        kprint!("sys_munmap: addr is not page-aligned");
        return Err(Err::Inval);
    }

    // munmap succeeds as a no-op in zkVM
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/ioctl.2.html
/// https://man7.org/linux/man-pages/man2/_exit.2.html
fn sys_exit(error_code: u32) -> Result<u32, Err> {
    if get_p9_enabled() {
        let traffic_hash = get_p9_traffic_hash();
        // Commit to journal in future
        kprint!("sys_exit: p9_traffic_hash = {:?}", traffic_hash);
    }
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

fn sys_getegid() -> Result<u32, Err> {
    Ok(0)
}

fn sys_geteuid() -> Result<u32, Err> {
    Ok(0)
}

fn sys_getgid() -> Result<u32, Err> {
    Ok(0)
}

fn sys_getuid() -> Result<u32, Err> {
    Ok(0)
}

fn sys_getpid() -> Result<u32, Err> {
    kprint!("sys_getpid: returning 1");
    Ok(1)
}
