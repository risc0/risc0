use crate::{host_calls::host_log, linux_abi::Err};

// Miscellaneous syscalls - stub implementations

pub fn sys_clock_getres_time64(_which_clock: u32, _tp: u32) -> Result<u32, Err> {
    let msg = b"sys_clock_getres_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_clock_gettime64(_which_clock: u32, _tp: u32) -> Result<u32, Err> {
    let msg = b"sys_clock_gettime64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_clock_nanosleep_time64(
    _which_clock: u32,
    _flags: u32,
    _rqtp: u32,
    _rmtp: u32,
) -> Result<u32, Err> {
    let msg = b"sys_clock_nanosleep_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_clone(
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

pub fn sys_clone3(_cl_args: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_clone3 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_close_range(_first: u32, _last: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_close_range not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_copy_file_range(
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

pub fn sys_epoll_create1(_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_epoll_create1 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_epoll_ctl(_epfd: u32, _op: u32, _fd: u32, _event: u32) -> Result<u32, Err> {
    let msg = b"sys_epoll_ctl not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_epoll_pwait(
    _epfd: u32,
    _events: u32,
    _maxevents: u32,
    _timeout: u32,
) -> Result<u32, Err> {
    let msg = b"sys_epoll_pwait not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_epoll_pwait2(
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

pub fn sys_eventfd2(_initval: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_eventfd2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_execve(_filename: u32, _argv: u32, _envp: u32) -> Result<u32, Err> {
    let msg = b"sys_execve not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_execveat(
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

pub fn sys_fsconfig(_fs_fd: u32, _cmd: u32, _key: u32, _value: u32, _aux: u32) -> Result<u32, Err> {
    let msg = b"sys_fsconfig not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fsmount(_fs_fd: u32, _flags: u32, _attr_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_fsmount not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fsopen(_fs_name: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_fsopen not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fspick(_dfd: u32, _path: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_fspick not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_fstatfs64(_fd: u32, _buf: u32) -> Result<u32, Err> {
    let msg = b"sys_fstatfs64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_futex_requeue(
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

pub fn sys_futex_time64(
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

pub fn sys_futex_wait(_uaddr: u32, _val: u32, _flags: u32, _timeout: u32) -> Result<u32, Err> {
    let msg = b"sys_futex_wait not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_futex_waitv(
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

pub fn sys_futex_wake(_uaddr: u32, _nr_wake: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_futex_wake not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_get_mempolicy(
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

pub fn sys_get_robust_list(_pid: u32, _head: u32, _len: u32) -> Result<u32, Err> {
    let msg = b"sys_get_robust_list not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getcpu(_cpu: u32, _node: u32, _cache: u32) -> Result<u32, Err> {
    let msg = b"sys_getcpu not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getgroups(_size: u32, _list: u32) -> Result<u32, Err> {
    let msg = b"sys_getgroups not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getitimer(_which: u32, _curr_value: u32) -> Result<u32, Err> {
    let msg = b"sys_getitimer not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getpgid(_pid: u32) -> Result<u32, Err> {
    let msg = b"sys_getpgid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getpid() -> Result<u32, Err> {
    let msg = b"sys_getpid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getppid() -> Result<u32, Err> {
    let msg = b"sys_getppid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getpriority(_which: u32, _who: u32) -> Result<u32, Err> {
    let msg = b"sys_getpriority not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getrandom(_buf: u32, _buflen: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_getrandom not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getresgid(_rgid: u32, _egid: u32, _sgid: u32) -> Result<u32, Err> {
    let msg = b"sys_getresgid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getresuid(_ruid: u32, _euid: u32, _suid: u32) -> Result<u32, Err> {
    let msg = b"sys_getresuid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getrusage(_who: u32, _usage: u32) -> Result<u32, Err> {
    let msg = b"sys_getrusage not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getsid(_pid: u32) -> Result<u32, Err> {
    let msg = b"sys_getsid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_gettid() -> Result<u32, Err> {
    let msg = b"sys_gettid not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_inotify_add_watch(_fd: u32, _pathname: u32, _mask: u32) -> Result<u32, Err> {
    let msg = b"sys_inotify_add_watch not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_inotify_init1(_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_inotify_init1 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_inotify_rm_watch(_fd: u32, _wd: u32) -> Result<u32, Err> {
    let msg = b"sys_inotify_rm_watch not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_io_cancel(_ctx_id: u32, _iocb: u32, _result: u32) -> Result<u32, Err> {
    let msg = b"sys_io_cancel not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_io_destroy(_ctx_id: u32) -> Result<u32, Err> {
    let msg = b"sys_io_destroy not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_io_pgetevents_time64(
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

pub fn sys_io_setup(_nr_events: u32, _ctx_idp: u32) -> Result<u32, Err> {
    let msg = b"sys_io_setup not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_io_submit(_ctx_id: u32, _nr: u32, _iocbpp: u32) -> Result<u32, Err> {
    let msg = b"sys_io_submit not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_io_uring_enter(
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

pub fn sys_io_uring_register(_fd: u32, _opcode: u32, _arg: u32, _nr_args: u32) -> Result<u32, Err> {
    let msg = b"sys_io_uring_register not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_io_uring_setup(_entries: u32, _params: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_io_uring_setup not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_ioprio_get(_which: u32, _who: u32) -> Result<u32, Err> {
    let msg = b"sys_ioprio_get not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_ioprio_set(_which: u32, _who: u32, _ioprio: u32) -> Result<u32, Err> {
    let msg = b"sys_ioprio_set not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_kcmp(_pid1: u32, _pid2: u32, _type: u32, _idx1: u32, _idx2: u32) -> Result<u32, Err> {
    let msg = b"sys_kcmp not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_kill(_pid: u32, _sig: u32) -> Result<u32, Err> {
    let msg = b"sys_kill not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_listmount(_dfd: u32, _filename: u32, _buffer: u32) -> Result<u32, Err> {
    let msg = b"sys_listmount not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_lookup_dcookie(_cookie64: u32, _buf: u32, _len: u32) -> Result<u32, Err> {
    let msg = b"sys_lookup_dcookie not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_lsm_get_self_attr(_attr: u32, _ctx: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_lsm_get_self_attr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_lsm_list_modules(_ids: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_lsm_list_modules not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_lsm_set_self_attr(_attr: u32, _ctx: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_lsm_set_self_attr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_madvise(_start: u32, _len: u32, _advice: u32) -> Result<u32, Err> {
    let msg = b"sys_madvise not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_map_shadow_stack(_addr: u32, _size: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_map_shadow_stack not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mbind(
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

pub fn sys_membarrier(_cmd: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_membarrier not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_memfd_create(_name: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_memfd_create not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_memfd_secret(_flags: u32, _reserved: u32) -> Result<u32, Err> {
    let msg = b"sys_memfd_secret not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_migrate_pages(
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

pub fn sys_mincore(_start: u32, _len: u32, _vec: u32) -> Result<u32, Err> {
    let msg = b"sys_mincore not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mlock(_addr: u32, _len: u32) -> Result<u32, Err> {
    let msg = b"sys_mlock not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mlock2(_addr: u32, _len: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_mlock2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mlockall(_flags: u32) -> Result<u32, Err> {
    let msg = b"sys_mlockall not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_move_mount(
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

pub fn sys_move_pages(
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

pub fn sys_mprotect(_addr: u32, _len: u32, _prot: u32) -> Result<u32, Err> {
    let msg = b"sys_mprotect not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mq_getsetattr(_mqdes: u32, _mqstat: u32, _omqstat: u32) -> Result<u32, Err> {
    let msg = b"sys_mq_getsetattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mq_notify(_mqdes: u32, _notification: u32) -> Result<u32, Err> {
    let msg = b"sys_mq_notify not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mq_open(_name: u32, _oflag: u32, _mode: u32, _attr: u32) -> Result<u32, Err> {
    let msg = b"sys_mq_open not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mq_timedreceive_time64(
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
