use crate::{host_calls::host_log, linux_abi::Err};

// Socket-related syscalls

pub fn sys_accept(_sockfd: u32, _addr: u32, _addrlen: u32) -> Result<u32, Err> {
    let msg = b"sys_accept not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_accept4(_sockfd: u32, _addr: u32, _addrlen: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_accept4 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_bind(_sockfd: u32, _addr: u32, _addrlen: u32) -> Result<u32, Err> {
    let msg = b"sys_bind not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_connect(_sockfd: u32, _addr: u32, _addrlen: u32) -> Result<u32, Err> {
    let msg = b"sys_connect not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getpeername(_sockfd: u32, _addr: u32, _addrlen: u32) -> Result<u32, Err> {
    let msg = b"sys_getpeername not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getsockname(_sockfd: u32, _addr: u32, _addrlen: u32) -> Result<u32, Err> {
    let msg = b"sys_getsockname not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_getsockopt(
    _sockfd: u32,
    _level: u32,
    _optname: u32,
    _optval: u32,
    _optlen: u32,
) -> Result<u32, Err> {
    let msg = b"sys_getsockopt not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_listen(_sockfd: u32, _backlog: u32) -> Result<u32, Err> {
    let msg = b"sys_listen not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_recvfrom(
    _sockfd: u32,
    _buf: u32,
    _len: u32,
    _flags: u32,
    _src_addr: u32,
    _addrlen: u32,
) -> Result<u32, Err> {
    let msg = b"sys_recvfrom not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_recvmmsg_time64(
    _sockfd: u32,
    _msgvec: u32,
    _vlen: u32,
    _flags: u32,
    _timeout: u32,
) -> Result<u32, Err> {
    let msg = b"sys_recvmmsg_time64 not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_recvmsg(_sockfd: u32, _msg: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_recvmsg not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_sendmmsg(_sockfd: u32, _msgvec: u32, _vlen: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_sendmmsg not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_sendmsg(_sockfd: u32, _msg: u32, _flags: u32) -> Result<u32, Err> {
    let msg = b"sys_sendmsg not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_sendto(
    _sockfd: u32,
    _buf: u32,
    _len: u32,
    _flags: u32,
    _dest_addr: u32,
    _addrlen: u32,
) -> Result<u32, Err> {
    let msg = b"sys_sendto not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_setsockopt(
    _sockfd: u32,
    _level: u32,
    _optname: u32,
    _optval: u32,
    _optlen: u32,
) -> Result<u32, Err> {
    let msg = b"sys_setsockopt not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_shutdown(_sockfd: u32, _how: u32) -> Result<u32, Err> {
    let msg = b"sys_shutdown not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_socket(_domain: u32, _type: u32, _protocol: u32) -> Result<u32, Err> {
    let msg = b"sys_socket not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

pub fn sys_socketpair(_domain: u32, _type: u32, _protocol: u32, _sv: u32) -> Result<u32, Err> {
    let msg = b"sys_socketpair not implemented";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}
