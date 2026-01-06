use crate::{host_calls::host_log, kernel::DEBUG_ENABLED, kernel::print, linux_abi::Err};
use no_std_strings::{str_format, str256};

// Socket-related syscalls

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

syscall_not_implemented!(sys_accept(_sockfd: u32, _addr: u32, _addrlen: u32));
syscall_not_implemented!(sys_accept4(_sockfd: u32, _addr: u32, _addrlen: u32, _flags: u32));
syscall_not_implemented!(sys_bind(_sockfd: u32, _addr: u32, _addrlen: u32));
syscall_not_implemented!(sys_connect(_sockfd: u32, _addr: u32, _addrlen: u32));
syscall_not_implemented!(sys_getpeername(_sockfd: u32, _addr: u32, _addrlen: u32));
syscall_not_implemented!(sys_getsockname(_sockfd: u32, _addr: u32, _addrlen: u32));
syscall_not_implemented!(sys_getsockopt(
    _sockfd: u32,
    _level: u32,
    _optname: u32,
    _optval: u32,
    _optlen: u32
));
syscall_not_implemented!(sys_listen(_sockfd: u32, _backlog: u32));
syscall_not_implemented!(sys_recvfrom(
    _sockfd: u32,
    _buf: u32,
    _len: u32,
    _flags: u32,
    _src_addr: u32,
    _addrlen: u32
));
syscall_not_implemented!(sys_recvmmsg_time64(
    _sockfd: u32,
    _msgvec: u32,
    _vlen: u32,
    _flags: u32,
    _timeout: u32
));
syscall_not_implemented!(sys_recvmsg(_sockfd: u32, _msg: u32, _flags: u32));
syscall_not_implemented!(sys_sendmmsg(_sockfd: u32, _msgvec: u32, _vlen: u32, _flags: u32));
syscall_not_implemented!(sys_sendmsg(_sockfd: u32, _msg: u32, _flags: u32));
syscall_not_implemented!(sys_sendto(
    _sockfd: u32,
    _buf: u32,
    _len: u32,
    _flags: u32,
    _dest_addr: u32,
    _addrlen: u32
));
syscall_not_implemented!(sys_setsockopt(
    _sockfd: u32,
    _level: u32,
    _optname: u32,
    _optval: u32,
    _optlen: u32
));
syscall_not_implemented!(sys_shutdown(_sockfd: u32, _how: u32));

pub fn sys_socket(domain: u32, socket_type: u32, protocol: u32) -> Result<u32, Err> {
    debug_print!(
        "sys_socket: domain={}, type={}, protocol={}",
        domain,
        socket_type,
        protocol
    );

    // Socket domains (address families)
    // AF_UNIX/AF_LOCAL = 1
    // AF_INET = 2
    // AF_INET6 = 10
    // AF_NETLINK = 16

    let msg = b"sys_socket: sockets not supported in zkVM";
    host_log(msg.as_ptr(), msg.len());
    Err(Err::NoSys)
}

syscall_not_implemented!(sys_socketpair(_domain: u32, _type: u32, _protocol: u32, _sv: u32));
