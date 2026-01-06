use crate::{
    host_calls::{host_get_cycle, host_log},
    kernel::print,
    linux_abi::Err,
};
use no_std_strings::{str_format, str256};
// Miscellaneous syscalls - stub implementations

macro_rules! syscall_not_implemented {
    ($name:ident($($param:ident: $type:ty),*)) => {
        pub fn $name($($param: $type),*) -> Result<u32, Err> {
            let msg = concat!(stringify!($name), " not implemented");
            host_log(msg.as_bytes().as_ptr(), msg.as_bytes().len());
            Err(Err::NoSys)
        }
    };
    ($name:ident()) => {
        pub fn $name() -> Result<u32, Err> {
            let msg = concat!(stringify!($name), " not implemented");
            host_log(msg.as_bytes().as_ptr(), msg.as_bytes().len());
            Err(Err::NoSys)
        }
    };
}

// Clock constants
const CLOCK_REALTIME: u32 = 0;
const CLOCK_MONOTONIC: u32 = 1;
const CLOCK_PROCESS_CPUTIME_ID: u32 = 2;
const CLOCK_THREAD_CPUTIME_ID: u32 = 3;
const CLOCK_MONOTONIC_RAW: u32 = 4;
const CLOCK_REALTIME_COARSE: u32 = 5;
const CLOCK_MONOTONIC_COARSE: u32 = 6;

// Timespec structure for 64-bit time
#[repr(C)]
#[derive(Debug, Clone, Copy)]
struct Timespec {
    tv_sec: i64,  // seconds
    tv_nsec: i64, // nanoseconds
}

syscall_not_implemented!(sys_clock_getres_time64(_which_clock: u32, _tp: u32));

pub fn sys_clock_gettime64(which_clock: u32, tp: u32) -> Result<u32, Err> {
    kprint!("sys_clock_gettime64: which_clock={} tp={}", which_clock, tp);

    // Get current host cycle count
    let cycles = host_get_cycle();
    kprint!("sys_clock_gettime64: cycles={}", cycles);

    // Convert cycles to time based on clock type
    let (tv_sec, tv_nsec) = match which_clock {
        CLOCK_REALTIME
        | CLOCK_MONOTONIC
        | CLOCK_MONOTONIC_RAW
        | CLOCK_REALTIME_COARSE
        | CLOCK_MONOTONIC_COARSE => {
            // For now, use a simple conversion: assume 1GHz host frequency
            // This is a placeholder - in a real implementation, you'd need to know the actual host frequency
            const HOST_FREQUENCY_HZ: u64 = 1_000_000_000; // 1GHz
            let seconds = cycles / HOST_FREQUENCY_HZ;
            let nanoseconds = ((cycles % HOST_FREQUENCY_HZ) * 1_000_000_000) / HOST_FREQUENCY_HZ;
            (seconds as i64, nanoseconds as i64)
        }
        CLOCK_PROCESS_CPUTIME_ID | CLOCK_THREAD_CPUTIME_ID => {
            // For process/thread CPU time, we can use the same calculation
            // In a real implementation, you might want to track per-process/thread cycles
            const HOST_FREQUENCY_HZ: u64 = 1_000_000_000; // 1GHz
            let seconds = cycles / HOST_FREQUENCY_HZ;
            let nanoseconds = ((cycles % HOST_FREQUENCY_HZ) * 1_000_000_000) / HOST_FREQUENCY_HZ;
            (seconds as i64, nanoseconds as i64)
        }
        _ => {
            kprint!(
                "sys_clock_gettime64: unsupported clock type {}",
                which_clock
            );
            return Err(Err::NoSys);
        }
    };

    kprint!(
        "sys_clock_gettime64: tv_sec={}, tv_nsec={}",
        tv_sec,
        tv_nsec
    );

    // Create timespec structure
    let timespec = Timespec { tv_sec, tv_nsec };

    // Write timespec to user memory using copy_to_user
    let timespec_bytes = unsafe {
        core::slice::from_raw_parts(
            &timespec as *const Timespec as *const u8,
            core::mem::size_of::<Timespec>(),
        )
    };
    let bytes_copied = crate::kernel::copy_to_user(
        tp as *mut u8,
        timespec_bytes.as_ptr(),
        core::mem::size_of::<Timespec>(),
    );
    if bytes_copied == 0 {
        kprint!("sys_clock_gettime64: failed to copy timespec structure to user memory");
        return Err(Err::NoSys);
    }

    Ok(0)
}

syscall_not_implemented!(sys_clock_nanosleep_time64(
    _which_clock: u32,
    _flags: u32,
    _rqtp: u32,
    _rmtp: u32
));

syscall_not_implemented!(sys_clone(
    _flags: u32,
    _child_stack: u32,
    _ptid: u32,
    _tls: u32,
    _ctid: u32
));
syscall_not_implemented!(sys_clone3(_cl_args: u32, _size: u32));
syscall_not_implemented!(sys_close_range(_first: u32, _last: u32, _flags: u32));
syscall_not_implemented!(sys_copy_file_range(
    _fd_in: u32,
    _off_in: u32,
    _fd_out: u32,
    _off_out: u32,
    _len: u32,
    _flags: u32
));

syscall_not_implemented!(sys_epoll_create1(_flags: u32));
syscall_not_implemented!(sys_epoll_ctl(_epfd: u32, _op: u32, _fd: u32, _event: u32));
syscall_not_implemented!(sys_epoll_pwait(
    _epfd: u32,
    _events: u32,
    _maxevents: u32,
    _timeout: u32
));
syscall_not_implemented!(sys_epoll_pwait2(
    _epfd: u32,
    _events: u32,
    _maxevents: u32,
    _timeout: u32,
    _sigmask: u32
));
syscall_not_implemented!(sys_eventfd2(_initval: u32, _flags: u32));
syscall_not_implemented!(sys_execve(_filename: u32, _argv: u32, _envp: u32));
syscall_not_implemented!(sys_execveat(
    _dfd: u32,
    _filename: u32,
    _argv: u32,
    _envp: u32,
    _flags: u32
));

syscall_not_implemented!(sys_fsconfig(_fs_fd: u32, _cmd: u32, _key: u32, _value: u32, _aux: u32));
syscall_not_implemented!(sys_fsmount(_fs_fd: u32, _flags: u32, _attr_flags: u32));
syscall_not_implemented!(sys_fsopen(_fs_name: u32, _flags: u32));
syscall_not_implemented!(sys_fspick(_dfd: u32, _path: u32, _flags: u32));
syscall_not_implemented!(sys_fstatfs64(_fd: u32, _buf: u32));
syscall_not_implemented!(sys_futex_requeue(
    _uaddr1: u32,
    _flags1: u32,
    _uaddr2: u32,
    _val1: u32,
    _val2: u32
));
syscall_not_implemented!(sys_futex_time64(
    _uaddr: u32,
    _futex_op: u32,
    _val: u32,
    _timeout: u32,
    _uaddr2: u32
));

syscall_not_implemented!(sys_futex_wait(_uaddr: u32, _val: u32, _flags: u32, _timeout: u32));
syscall_not_implemented!(sys_futex_waitv(
    _waiters: u32,
    _nr_waiters: u32,
    _flags: u32,
    _timeout: u32,
    _clockid: u32
));
syscall_not_implemented!(sys_futex_wake(_uaddr: u32, _nr_wake: u32, _flags: u32));
syscall_not_implemented!(sys_get_mempolicy(
    _mode: u32,
    _nmask: u32,
    _maxnode: u32,
    _addr: u32,
    _flags: u32
));
syscall_not_implemented!(sys_get_robust_list(_pid: u32, _head: u32, _len: u32));
syscall_not_implemented!(sys_getcpu(_cpu: u32, _node: u32, _cache: u32));
syscall_not_implemented!(sys_getgroups(_size: u32, _list: u32));
syscall_not_implemented!(sys_getitimer(_which: u32, _curr_value: u32));
syscall_not_implemented!(sys_getpgid(_pid: u32));

syscall_not_implemented!(sys_getppid());
syscall_not_implemented!(sys_getpriority(_which: u32, _who: u32));
syscall_not_implemented!(sys_getrandom(_buf: u32, _buflen: u32, _flags: u32));
syscall_not_implemented!(sys_getresgid(_rgid: u32, _egid: u32, _sgid: u32));
syscall_not_implemented!(sys_getresuid(_ruid: u32, _euid: u32, _suid: u32));
syscall_not_implemented!(sys_getrusage(_who: u32, _usage: u32));
syscall_not_implemented!(sys_getsid(_pid: u32));
syscall_not_implemented!(sys_gettid());
syscall_not_implemented!(sys_inotify_add_watch(_fd: u32, _pathname: u32, _mask: u32));
syscall_not_implemented!(sys_inotify_init1(_flags: u32));
syscall_not_implemented!(sys_inotify_rm_watch(_fd: u32, _wd: u32));

syscall_not_implemented!(sys_io_cancel(_ctx_id: u32, _iocb: u32, _result: u32));
syscall_not_implemented!(sys_io_destroy(_ctx_id: u32));
syscall_not_implemented!(sys_io_pgetevents_time64(
    _ctx_id: u32,
    _min_nr: u32,
    _nr: u32,
    _events: u32,
    _timeout: u32
));
syscall_not_implemented!(sys_io_setup(_nr_events: u32, _ctx_idp: u32));
syscall_not_implemented!(sys_io_submit(_ctx_id: u32, _nr: u32, _iocbpp: u32));
syscall_not_implemented!(sys_io_uring_enter(
    _fd: u32,
    _to_submit: u32,
    _min_complete: u32,
    _flags: u32,
    _sig: u32,
    _sz: u32
));
syscall_not_implemented!(sys_io_uring_register(_fd: u32, _opcode: u32, _arg: u32, _nr_args: u32));
syscall_not_implemented!(sys_io_uring_setup(_entries: u32, _params: u32, _flags: u32));
syscall_not_implemented!(sys_ioprio_get(_which: u32, _who: u32));
syscall_not_implemented!(sys_ioprio_set(_which: u32, _who: u32, _ioprio: u32));
syscall_not_implemented!(sys_kcmp(_pid1: u32, _pid2: u32, _type: u32, _idx1: u32, _idx2: u32));
syscall_not_implemented!(sys_kill(_pid: u32, _sig: u32));
syscall_not_implemented!(sys_listmount(_dfd: u32, _filename: u32, _buffer: u32));
syscall_not_implemented!(sys_lookup_dcookie(_cookie64: u32, _buf: u32, _len: u32));

syscall_not_implemented!(sys_lsm_get_self_attr(_attr: u32, _ctx: u32, _size: u32));
syscall_not_implemented!(sys_lsm_list_modules(_ids: u32, _size: u32));
syscall_not_implemented!(sys_lsm_set_self_attr(_attr: u32, _ctx: u32, _size: u32));
syscall_not_implemented!(sys_madvise(_start: u32, _len: u32, _advice: u32));
syscall_not_implemented!(sys_map_shadow_stack(_addr: u32, _size: u32, _flags: u32));
syscall_not_implemented!(sys_mbind(
    _start: u32,
    _len: u32,
    _mode: u32,
    _nodemask: u32,
    _maxnode: u32,
    _flags: u32
));
syscall_not_implemented!(sys_membarrier(_cmd: u32, _flags: u32));
syscall_not_implemented!(sys_memfd_create(_name: u32, _flags: u32));
syscall_not_implemented!(sys_memfd_secret(_flags: u32, _reserved: u32));
syscall_not_implemented!(sys_migrate_pages(
    _pid: u32,
    _maxnode: u32,
    _old_nodes: u32,
    _new_nodes: u32,
    _status: u32,
    _flags: u32
));
syscall_not_implemented!(sys_mincore(_start: u32, _len: u32, _vec: u32));
syscall_not_implemented!(sys_mlock(_addr: u32, _len: u32));
syscall_not_implemented!(sys_mlock2(_addr: u32, _len: u32, _flags: u32));
syscall_not_implemented!(sys_mlockall(_flags: u32));
syscall_not_implemented!(sys_move_mount(
    _from_dfd: u32,
    _from_pathname: u32,
    _to_dfd: u32,
    _to_pathname: u32,
    _flags: u32
));
syscall_not_implemented!(sys_move_pages(
    _pid: u32,
    _nr_pages: u32,
    _pages: u32,
    _nodes: u32,
    _status: u32,
    _flags: u32
));

pub fn sys_mprotect(_addr: u32, _len: u32, _prot: u32) -> Result<u32, Err> {
    kprint!(
        "sys_mprotect(addr=0x{:08x}, len=0x{:x}, prot={}) -> returning success",
        _addr,
        _len,
        _prot
    );
    Ok(0)
}

syscall_not_implemented!(sys_mq_getsetattr(_mqdes: u32, _mqstat: u32, _omqstat: u32));
syscall_not_implemented!(sys_mq_notify(_mqdes: u32, _notification: u32));
syscall_not_implemented!(sys_mq_open(_name: u32, _oflag: u32, _mode: u32, _attr: u32));
syscall_not_implemented!(sys_mq_timedreceive_time64(
    _mqdes: u32,
    _msg_ptr: u32,
    _msg_len: u32,
    _msg_prio: u32,
    _abs_timeout: u32
));
syscall_not_implemented!(sys_mq_timedsend_time64(
    _mqdes: u32,
    _msg_ptr: u32,
    _msg_len: u32,
    _msg_prio: u32,
    _abs_timeout: u32
));
syscall_not_implemented!(sys_mq_unlink(_name: u32));

syscall_not_implemented!(sys_mremap(
    _addr: u32,
    _old_len: u32,
    _new_len: u32,
    _flags: u32,
    _new_addr: u32
));
syscall_not_implemented!(sys_mseal(_addr: u32, _len: u32, _flags: u32));
syscall_not_implemented!(sys_msgctl(_msqid: u32, _cmd: u32, _buf: u32, _version: u32));
syscall_not_implemented!(sys_msgget(_key: u32, _msgflg: u32, _version: u32));
syscall_not_implemented!(sys_msgrcv(
    _msqid: u32,
    _msgp: u32,
    _msgsz: u32,
    _msgtyp: u32,
    _msgflg: u32
));
syscall_not_implemented!(sys_msgsnd(_msqid: u32, _msgp: u32, _msgsz: u32, _msgflg: u32));

pub fn sys_msync(_addr: u32, _len: u32, _flags: u32) -> Result<u32, Err> {
    // msync() synchronizes a mapped memory region with the underlying file
    // In a zkVM environment without real virtual memory management,
    // this is a no-op that always succeeds
    Ok(0)
}

syscall_not_implemented!(sys_munlock(_addr: u32, _len: u32));
syscall_not_implemented!(sys_munlockall());
syscall_not_implemented!(sys_name_to_handle_at(
    _dfd: u32,
    _name: u32,
    _handle: u32,
    _mnt_id: u32,
    _flags: u32
));
syscall_not_implemented!(sys_open_by_handle_at(_mount_fd: u32, _handle: u32, _flags: u32));
syscall_not_implemented!(sys_open_tree(_dfd: u32, _filename: u32, _flags: u32));
syscall_not_implemented!(sys_open_tree_attr(_dfd: u32, _filename: u32, _flags: u32, _attr: u32));
syscall_not_implemented!(sys_perf_event_open(
    _attr: u32,
    _pid: u32,
    _cpu: u32,
    _group_fd: u32,
    _flags: u32
));
syscall_not_implemented!(sys_personality(_personality: u32));

syscall_not_implemented!(sys_pidfd_getfd(_pidfd: u32, _targetfd: u32, _flags: u32));
syscall_not_implemented!(sys_pidfd_open(_pid: u32, _flags: u32));
syscall_not_implemented!(sys_pidfd_send_signal(_pidfd: u32, _sig: u32, _info: u32));
syscall_not_implemented!(sys_pipe2(_pipefd: u32, _flags: u32));
syscall_not_implemented!(sys_pivot_root(_new_root: u32, _put_old: u32));
syscall_not_implemented!(sys_pkey_alloc(_flags: u32, _access_rights: u32));
syscall_not_implemented!(sys_pkey_free(_pkey: u32));
syscall_not_implemented!(sys_pkey_mprotect(_start: u32, _len: u32, _prot: u32, _pkey: u32));
syscall_not_implemented!(sys_ppoll_time64(
    _ufds: u32,
    _nfds: u32,
    _tsp: u32,
    _sigmask: u32,
    _sigsetsize: u32
));
syscall_not_implemented!(sys_prctl(_option: u32, _arg2: u32, _arg3: u32, _arg4: u32, _arg5: u32));

// rlimit structure for prlimit64
#[repr(C)]
#[derive(Debug, Clone, Copy)]
struct Rlimit64 {
    rlim_cur: u64, // Soft limit
    rlim_max: u64, // Hard limit
}

pub fn sys_prlimit64(
    _pid: u32,
    resource: u32,
    _new_limit: u32,
    old_limit: u32,
) -> Result<u32, Err> {
    const RLIMIT_NOFILE: u32 = 7; // Max number of open file descriptors

    kprint!(
        "sys_prlimit64: pid={}, resource={}, new_limit=0x{:08x}, old_limit=0x{:08x}",
        _pid,
        resource,
        _new_limit,
        old_limit
    );

    // Only handle RLIMIT_NOFILE for now
    if resource != RLIMIT_NOFILE {
        let msg = b"sys_prlimit64: only RLIMIT_NOFILE is supported";
        host_log(msg.as_ptr(), msg.len());
        return Err(Err::NoSys);
    }

    // Return our current fd limit (256)
    if old_limit != 0 {
        let rlimit = Rlimit64 {
            rlim_cur: 256, // Soft limit
            rlim_max: 256, // Hard limit
        };

        let rlimit_bytes = unsafe {
            core::slice::from_raw_parts(
                &rlimit as *const Rlimit64 as *const u8,
                core::mem::size_of::<Rlimit64>(),
            )
        };

        let bytes_copied = crate::kernel::copy_to_user(
            old_limit as *mut u8,
            rlimit_bytes.as_ptr(),
            core::mem::size_of::<Rlimit64>(),
        );

        if bytes_copied == 0 {
            kprint!("sys_prlimit64: failed to copy rlimit to user memory");
            return Err(Err::Fault);
        }

        kprint!("sys_prlimit64: returned rlim_cur=256, rlim_max=256");
    }

    // Ignore new_limit - we don't allow changing the limit
    if _new_limit != 0 {
        kprint!("sys_prlimit64: ignoring new_limit (not supported)");
    }

    Ok(0)
}

syscall_not_implemented!(sys_process_madvise(
    _pidfd: u32,
    _addr: u32,
    _length: u32,
    _advice: u32,
    _flags: u32
));
syscall_not_implemented!(sys_process_mrelease(_pidfd: u32, _flags: u32));
syscall_not_implemented!(sys_process_vm_readv(
    _pid: u32,
    _lvec: u32,
    _liovcnt: u32,
    _rvec: u32,
    _riovcnt: u32,
    _flags: u32
));
syscall_not_implemented!(sys_process_vm_writev(
    _pid: u32,
    _lvec: u32,
    _liovcnt: u32,
    _rvec: u32,
    _riovcnt: u32,
    _flags: u32
));

syscall_not_implemented!(sys_pselect6_time64(
    _n: u32,
    _inp: u32,
    _outp: u32,
    _exp: u32,
    _tsp: u32,
    _sigmask: u32
));
syscall_not_implemented!(sys_ptrace(_request: u32, _pid: u32, _addr: u32, _data: u32));
syscall_not_implemented!(sys_quotactl(_cmd: u32, _special: u32, _id: u32, _addr: u32));
syscall_not_implemented!(sys_quotactl_fd(_fd: u32, _cmd: u32, _id: u32, _addr: u32));
syscall_not_implemented!(sys_remap_file_pages(
    _start: u32,
    _size: u32,
    _prot: u32,
    _pgoff: u32,
    _flags: u32
));
syscall_not_implemented!(sys_request_key(
    _type: u32,
    _description: u32,
    _callout_info: u32,
    _destringid: u32
));
syscall_not_implemented!(sys_restart_syscall());
syscall_not_implemented!(sys_riscv_flush_icache(_start: u32, _end: u32));
syscall_not_implemented!(sys_riscv_hwprobe(
    _pairs: u32,
    _pair_count: u32,
    _cpu_set: u32,
    _cpu_set_size: u32
));
syscall_not_implemented!(sys_rseq(_rseq: u32, _rseq_len: u32, _flags: u32, _sig: u32));
syscall_not_implemented!(sys_rt_sigpending(_set: u32, _sigsetsize: u32));
syscall_not_implemented!(sys_rt_sigqueueinfo(_pid: u32, _sig: u32, _uinfo: u32));
syscall_not_implemented!(sys_rt_sigreturn());
syscall_not_implemented!(sys_rt_sigsuspend(_unewset: u32));
syscall_not_implemented!(sys_rt_sigtimedwait_time64(
    _uthese: u32,
    _uinfo: u32,
    _uts: u32,
    _sigsetsize: u32
));
syscall_not_implemented!(sys_rt_tgsigqueueinfo(_tgid: u32, _tid: u32, _sig: u32, _uinfo: u32));

syscall_not_implemented!(sys_sched_get_priority_max(_policy: u32));
syscall_not_implemented!(sys_sched_get_priority_min(_policy: u32));
syscall_not_implemented!(sys_sched_getaffinity(_pid: u32, _len: u32, _user_mask_ptr: u32));
syscall_not_implemented!(sys_sched_getattr(_pid: u32, _attr: u32, _size: u32));
syscall_not_implemented!(sys_sched_getparam(_pid: u32, _param: u32));
syscall_not_implemented!(sys_sched_getscheduler(_pid: u32));
syscall_not_implemented!(sys_sched_rr_get_interval_time64(_pid: u32, _interval: u32));
syscall_not_implemented!(sys_sched_setaffinity(_pid: u32, _len: u32, _user_mask_ptr: u32));
syscall_not_implemented!(sys_sched_setattr(_pid: u32, _attr: u32, _flags: u32));
syscall_not_implemented!(sys_sched_setparam(_pid: u32, _param: u32));
syscall_not_implemented!(sys_sched_setscheduler(_pid: u32, _policy: u32, _param: u32));
syscall_not_implemented!(sys_sched_yield());
syscall_not_implemented!(sys_seccomp(_operation: u32, _flags: u32, _args: u32));
syscall_not_implemented!(sys_semctl(_semid: u32, _semnum: u32, _cmd: u32, _arg: u32));
syscall_not_implemented!(sys_semget(_key: u32, _nsems: u32, _semflg: u32));
syscall_not_implemented!(sys_semop(_semid: u32, _sops: u32, _nsops: u32));
syscall_not_implemented!(sys_semtimedop_time64(
    _semid: u32,
    _sops: u32,
    _nsops: u32,
    _timeout: u32
));

syscall_not_implemented!(sys_set_mempolicy(
    _mode: u32,
    _nmask: u32,
    _maxnode: u32,
    _addr: u32,
    _flags: u32,
    _home_node: u32
));
syscall_not_implemented!(sys_set_mempolicy_home_node(
    _start: u32,
    _len: u32,
    _home_node: u32,
    _flags: u32
));
syscall_not_implemented!(sys_set_robust_list(_head: u32, _len: u32));
syscall_not_implemented!(sys_setdomainname(_name: u32));
syscall_not_implemented!(sys_setfsgid(_fsgid: u32));
syscall_not_implemented!(sys_setfsuid(_fsuid: u32));
syscall_not_implemented!(sys_setgid(_gid: u32));
syscall_not_implemented!(sys_setgroups(_size: u32, _list: u32));
syscall_not_implemented!(sys_sethostname(_name: u32));
syscall_not_implemented!(sys_setitimer(_which: u32, _value: u32));
syscall_not_implemented!(sys_setpgid(_pid: u32, _pgid: u32));
syscall_not_implemented!(sys_setpriority(_which: u32, _who: u32, _niceval: u32));
syscall_not_implemented!(sys_setregid(_rgid: u32, _egid: u32));
syscall_not_implemented!(sys_setresgid(_rgid: u32, _egid: u32, _sgid: u32));
syscall_not_implemented!(sys_setresuid(_ruid: u32, _euid: u32, _suid: u32));
syscall_not_implemented!(sys_setreuid(_ruid: u32, _euid: u32));
syscall_not_implemented!(sys_setsid());
syscall_not_implemented!(sys_setuid(_uid: u32));
syscall_not_implemented!(sys_shmat(_shmid: u32, _shmaddr: u32, _shmflg: u32));
syscall_not_implemented!(sys_shmctl(_shmid: u32, _cmd: u32, _buf: u32));
syscall_not_implemented!(sys_shmdt(_shmaddr: u32));
syscall_not_implemented!(sys_shmget(_key: u32, _size: u32, _shmflg: u32, _version: u32));
syscall_not_implemented!(sys_signalfd4(_fd: u32, _mask: u32, _sizemask: u32));
syscall_not_implemented!(sys_splice(
    _fd_in: u32,
    _off_in: u32,
    _fd_out: u32,
    _off_out: u32,
    _len: u32,
    _flags: u32
));
syscall_not_implemented!(sys_statmount(_dfd: u32, _filename: u32, _buffer: u32, _bufsize: u32));
syscall_not_implemented!(sys_sync());
syscall_not_implemented!(sys_sync_file_range(_fd: u32, _offset: u32, _nbytes: u32, _flags: u32));
syscall_not_implemented!(sys_syncfs(_fd: u32));
syscall_not_implemented!(sys_sysinfo(_info: u32));
syscall_not_implemented!(sys_syslog(_type: u32, _buf: u32, _len: u32));
syscall_not_implemented!(sys_tee(_fd_in: u32, _fd_out: u32, _len: u32, _flags: u32));
syscall_not_implemented!(sys_tgkill(_tgid: u32, _tid: u32, _sig: u32));
syscall_not_implemented!(sys_timer_create(
    _which_clock: u32,
    _timer_event_spec: u32,
    _created_timer_id: u32
));
syscall_not_implemented!(sys_timer_delete(_timer_id: u32));
syscall_not_implemented!(sys_timer_getoverrun(_timer_id: u32));
syscall_not_implemented!(sys_timer_gettime64(_timer_id: u32, _setting: u32));
syscall_not_implemented!(sys_timer_settime64(
    _timer_id: u32,
    _flags: u32,
    _new_setting: u32,
    _old_setting: u32
));
syscall_not_implemented!(sys_timerfd_create(_clockid: u32, _flags: u32));
syscall_not_implemented!(sys_timerfd_gettime64(_fd: u32, _curr_value: u32));
syscall_not_implemented!(sys_timerfd_settime64(
    _fd: u32,
    _flags: u32,
    _new_value: u32,
    _old_value: u32
));
syscall_not_implemented!(sys_times(_tbuf: u32));

// sys_truncate64 is now implemented in linux_abi_fs.rs
// pub fn sys_truncate64(_path: u32, _length: u32) -> Result<u32, Err> {
//     let msg = b"sys_truncate64 not implemented";
//     host_log(msg.as_ptr(), msg.len());
//     Err(Err::NoSys)
// }

// Linux utsname structure - each field is 65 bytes (64 chars + null terminator)
#[repr(C)]
struct UtsName {
    sysname: [u8; 65],
    nodename: [u8; 65],
    release: [u8; 65],
    version: [u8; 65],
    machine: [u8; 65],
    domainname: [u8; 65],
}

impl UtsName {
    fn new() -> Self {
        let mut utsname = UtsName {
            sysname: [0; 65],
            nodename: [0; 65],
            release: [0; 65],
            version: [0; 65],
            machine: [0; 65],
            domainname: [0; 65],
        };

        // Set sysname to "Linux"
        let sysname = b"Linux";
        utsname.sysname[..sysname.len()].copy_from_slice(sysname);

        // Set nodename to "risc0"
        let nodename = b"risc0";
        utsname.nodename[..nodename.len()].copy_from_slice(nodename);

        // Set release to "6.7.0" (pretend we're Linux 6.7)
        let release = b"6.7.0";
        utsname.release[..release.len()].copy_from_slice(release);

        // Set version to a build string
        let version = b"#1 SMP PREEMPT_DYNAMIC";
        utsname.version[..version.len()].copy_from_slice(version);

        // Set machine to "riscv32"
        let machine = b"riscv32";
        utsname.machine[..machine.len()].copy_from_slice(machine);

        // Set domainname (usually empty or "(none)")
        let domainname = b"(none)";
        utsname.domainname[..domainname.len()].copy_from_slice(domainname);

        utsname
    }
}

pub fn sys_uname(buf: u32) -> Result<u32, Err> {
    // Check for NULL pointer
    if buf == 0 {
        return Err(Err::Fault);
    }

    // Check if address is in user memory range
    if buf >= 0xC0000000 {
        kprint!("sys_uname: invalid buffer address: 0x{:x}", buf);
        return Err(Err::Fault);
    }

    kprint!("sys_uname: buf=0x{:x}", buf);

    // Create utsname structure
    let utsname = UtsName::new();

    // Copy to user space
    unsafe {
        let dest = buf as *mut UtsName;
        core::ptr::write(dest, utsname);
    }

    kprint!("sys_uname: returned Linux 6.7.0 riscv32");

    Ok(0)
}

syscall_not_implemented!(sys_unshare(_flags: u32));
syscall_not_implemented!(sys_userfaultfd(_flags: u32));
syscall_not_implemented!(sys_vmsplice(_fd: u32, _iov: u32, _nr_segs: u32, _flags: u32));
syscall_not_implemented!(sys_waitid(
    _which: u32,
    _upid: u32,
    _infop: u32,
    _options: u32,
    _ru: u32
));
