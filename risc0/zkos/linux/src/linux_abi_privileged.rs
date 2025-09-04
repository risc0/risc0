use crate::{host_calls::host_log, linux_abi::Err};

// Privileged syscalls that require root privileges or special permissions

pub fn sys_acct(_filename: u32) -> Result<u32, Err> {
    let msg = b"sys_acct not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_add_key(
    _type: u32,
    _description: u32,
    _payload: u32,
    _plen: u32,
    _keyring: u32,
) -> Result<u32, Err> {
    let msg = b"sys_add_key not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_bpf(_cmd: u32, _attr: u32, _size: u32) -> Result<u32, Err> {
    let msg = b"sys_bpf not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_capget(_hdrp: u32, _datap: u32) -> Result<u32, Err> {
    let msg = b"sys_capget not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_capset(_hdrp: u32, _datap: u32) -> Result<u32, Err> {
    let msg = b"sys_capset not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_chroot(_filename: u32) -> Result<u32, Err> {
    let msg = b"sys_chroot not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_clock_adjtime64(_which_clock: u32, _tx: u32) -> Result<u32, Err> {
    let msg = b"sys_clock_adjtime64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_clock_settime64(_which_clock: u32, _tp: u32) -> Result<u32, Err> {
    let msg = b"sys_clock_settime64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_delete_module(_name: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_delete_module not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_finit_module(_fd: u32, _param_values: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_finit_module not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_init_module(_module_image: u32, _len: u32, _param_values: u32) -> Result<u32, Err> {
    let msg = b"sys_init_module not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_kexec_file_load(
    _kernel_fd: u32,
    _initrd_fd: u32,
    _cmdline_len: u32,
    _cmdline: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_kexec_file_load not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_kexec_load(
    _entry: u32,
    _nr_segments: u32,
    _segments: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_kexec_load not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_keyctl(
    _operation: u32,
    _arg2: u32,
    _arg3: u32,
    _arg4: u32,
    _arg5: u32,
) -> Result<u32, Err> {
    let msg = b"sys_keyctl not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_landlock_add_rule(
    _ruleset_fd: u32,
    _rule_type: u32,
    _rule_attr: u32,
    _flags: u32,
) -> Result<u32, Err> {
    let msg = b"sys_landlock_add_rule not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_landlock_create_ruleset(_attr: u32, _size: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_landlock_create_ruleset not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_landlock_restrict_self(_ruleset_fd: u32) -> Result<u32, Err> {
    let msg = b"sys_landlock_restrict_self not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mount(
    _source: u32,
    _target: u32,
    _filesystemtype: u32,
    _mountflags: u32,
    _data: u32,
) -> Result<u32, Err> {
    let msg = b"sys_mount not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_mount_setattr(
    _dfd: u32,
    _path: u32,
    _flags: u32,
    _uattr: u32,
    _usize: u32,
) -> Result<u32, Err> {
    let msg = b"sys_mount_setattr not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_reboot(_magic1: u32, _magic2: u32, _cmd: u32, _arg: u32) -> Result<u32, Err> {
    let msg = b"sys_reboot not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_setns(_fd: u32, _nstype: u32) -> Result<u32, Err> {
    let msg = b"sys_setns not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_swapoff(_specialfile: u32) -> Result<u32, Err> {
    let msg = b"sys_swapoff not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_swapon(_specialfile: u32, _swapflags: u32, _version: u32) -> Result<u32, Err> {
    let msg = b"sys_swapon not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_umount2(_target: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_umount2 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_vhangup() -> Result<u32, Err> {
    let msg = b"sys_vhangup not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}
