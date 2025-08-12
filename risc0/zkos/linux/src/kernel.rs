// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

use core::{alloc::Layout, ptr::NonNull};

use no_std_strings::{str256, str_format};
use rlsf::Tlsf;

const REG_SP: usize = 2;
const REG_A0: usize = 10;
const REG_A1: usize = 11;
const REG_A2: usize = 12;
const REG_A3: usize = 13;
const REG_A4: usize = 14;
const REG_A5: usize = 15;
// const REG_A6: usize = 16;
const REG_A7: usize = 17;

const USER_REGS_PTR: *mut u32 = 0xffff_0080 as *mut u32;
const MEPC_PTR: *mut usize = 0xffff_0200 as *mut usize;
const USER_START_PTR: *const usize = 0x0001_0000 as *const usize;
const USER_STACK_ADDR: usize = 0xbfff_0000;
const USER_STACK_PTR: *const usize = USER_STACK_ADDR as *const usize;
const USER_STACK_SIZE: usize = 2 * 1024 * 1024;
const USER_HEAP_START_ADDR: usize = 0x0800_0000; // TODO: figure out where data ends in user program
const USER_HEAP_START_PTR: *const u8 = USER_HEAP_START_ADDR as *const u8;
const USER_HEAP_END_ADDR: usize = USER_STACK_ADDR - USER_STACK_SIZE;
const USER_HEAP_SIZE: usize = USER_HEAP_END_ADDR - USER_HEAP_START_ADDR;

const ARGC: usize = 1;
const PROGRAM_NAME: &[u8] = b"r0vm";
const PAGE_SIZE: usize = 4096;
// const AT_VECTOR_SIZE_BASE: usize = 20;
// const AT_VECTOR_SIZE_ARCH: usize = 7;
// const AT_VECTOR_SIZE: usize = 2 * (AT_VECTOR_SIZE_ARCH + AT_VECTOR_SIZE_BASE + 1);
const ASCII_TABLE_PTR: *const u8 = 0xbfff_0200 as *const u8;

const SYS_IOCTL: u32 = 29;
const SYS_READ: u32 = 63;
const SYS_WRITE: u32 = 64;
const SYS_WRITEV: u32 = 66;
const SYS_EXIT: u32 = 93;
const SYS_EXIT_GROUP: u32 = 94;
const SYS_SET_TID_ADDRESS: u32 = 96;
const SYS_TKILL: u32 = 130;
const SYS_SIGALTSTACK: u32 = 132;
const SYS_RT_SIGACTION: u32 = 134;
const SYS_RT_SIGPROCMASK: u32 = 135;
const SYS_BRK: u32 = 214;
const SYS_MUNMAP: u32 = 215;
const SYS_MMAP: u32 = 222;
const SYS_PPOLL: u32 = 414;

#[derive(Clone, Copy)]
enum Err {
    NoMem = -12,
    Inval = -22,
}

static mut BRK: u32 = USER_HEAP_START_ADDR as u32;

type Heap = Tlsf<'static, usize, usize, { usize::BITS as usize }, { usize::BITS as usize }>;
static mut HEAP: Heap = Heap::new();

#[cfg(target_arch = "riscv32")]
core::arch::global_asm!(include_str!("kernel.s"));

#[cfg(target_arch = "riscv32")]
#[panic_handler]
fn panic(_info: &core::panic::PanicInfo) -> ! {
    unsafe { core::arch::asm!("unimp", options(noreturn)) }
}

fn get_ureg(idx: usize) -> u32 {
    unsafe { USER_REGS_PTR.add(idx).read() }
}

fn set_ureg(idx: usize, word: u32) {
    unsafe { USER_REGS_PTR.add(idx).write_volatile(word) };
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

    fn add_null(&mut self) {
        self.add_word(0);
    }

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

impl Err {
    pub fn as_errno(&self) -> u32 {
        *self as u32
    }
}

#[no_mangle]
unsafe extern "C" fn kstart() -> ! {
    let user_start_addr = USER_START_PTR.read_volatile();
    MEPC_PTR.write_volatile(user_start_addr);

    let mut stack = UserStack::new();

    // args
    stack.add_word(ARGC);
    stack.add_str(PROGRAM_NAME);
    stack.add_null();

    // env
    stack.add_null();

    // aux
    stack.add_aux_word(AuxType::PageSz, PAGE_SIZE); // auxv[0]
    stack.add_aux_word(AuxType::Uid, 1); // auxv[1]
    stack.add_aux_word(AuxType::EUid, 1); // auxv[2]
    stack.add_aux_word(AuxType::Gid, 1); // auxv[3]
    stack.add_aux_word(AuxType::EGid, 1); // auxv[4]
    stack.add_aux_word(AuxType::Null, 0); // auxv[5]

    set_ureg(REG_SP, USER_STACK_PTR as u32);

    let block: &[u8] = core::slice::from_raw_parts(USER_HEAP_START_PTR, USER_HEAP_SIZE);
    #[allow(static_mut_refs)]
    HEAP.insert_free_block_ptr(block.into());

    mret()
}

fn mret() -> ! {
    #[cfg(target_arch = "riscv32")]
    unsafe {
        core::arch::asm!("mret", options(noreturn))
    }
    #[cfg(not(target_arch = "riscv32"))]
    unimplemented!()
}

#[no_mangle]
unsafe extern "C" fn ecall_dispatch() -> ! {
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
        SYS_PPOLL => syscall5(sys_ppoll),
        _ => {
            let msg = str_format!(str256, "syscall: {nr}");
            print(&msg);
            set_ureg(REG_A0, 0);
        }
    }

    mret()
}

fn print(msg: &str) {
    let msg = msg.as_bytes();
    host_log(msg.as_ptr(), msg.len());
}

fn host_terminate(_a0: u32, _a1: u32) -> ! {
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

fn host_log(_msg_ptr: *const u8, _msg_len: usize) {
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

fn set_result(result: Result<u32, Err>) {
    set_ureg(REG_A0, result.unwrap_or_else(|e| e.as_errno()));
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

    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/read.2.html
fn sys_read(_fd: u32, _buf: u32, _count: u32) -> Result<u32, Err> {
    // const HOST_ECALL_READ: u32 = 1;
    // let msg = str_format!(str256, "sys_read({fd}, {buf:?}, {count})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/write.2.html
fn sys_write(fd: u32, buf: u32, count: u32) -> Result<u32, Err> {
    do_write(fd as i32, buf as *const u8, count as usize).map(|x| x as u32)
}

fn do_write(fd: i32, buf: *const u8, count: usize) -> Result<usize, Err> {
    // let msg = str_format!(str256, "do_write({fd}, {buf:?}, {count})");
    // print(&msg);

    if fd == 1 || fd == 2 {
        host_log(buf, count);
    }

    Ok(count)
}

#[repr(C)]
struct IoVec {
    iov_base: *mut u8,
    iov_len: usize,
}

/// https://man7.org/linux/man-pages/man2/writev.2.html
fn sys_writev(fd: u32, vec_ptr: u32, vlen: u32) -> Result<u32, Err> {
    let fd = fd as i32;
    let vec_ptr = vec_ptr as *const IoVec;
    let vec = unsafe { core::slice::from_raw_parts(vec_ptr, vlen as usize) };

    // let msg = str_format!(str256, "sys_writev({fd}, {vec_ptr:?}, {vlen})");
    // print(&msg);

    let mut total: usize = 0;
    for iov in vec {
        total += do_write(fd, iov.iov_base, iov.iov_len)?;
    }
    Ok(total as u32)
}

/// https://man7.org/linux/man-pages/man2/ioctl.2.html
fn sys_ioctl(fd: u32, _cmd: u32, arg: u32) -> Result<u32, Err> {
    let _fd = fd as i32;
    let _arg = arg as *const u8;
    // let msg = str_format!(str256, "sys_ioctl({fd}, {cmd}, 0x{arg:08x})");
    // print(&msg);
    Ok(0)
}

/// https://man7.org/linux/man-pages/man2/_exit.2.html
fn sys_exit(error_code: u32) -> Result<u32, Err> {
    // let msg = str_format!(str256, "sys_exit({error_code})");
    // print(&msg);
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
    // let msg = str_format!(str256, "sys_set_tid_address({tidptr:?})");
    // print(&msg);
    Ok(0)
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

/// https://man7.org/linux/man-pages/man2/poll.2.html
fn sys_ppoll(ufds: u32, _nfds: u32, tsp: u32, sigmask: u32, _sigsetsize: u32) -> Result<u32, Err> {
    let _ufds = ufds as *const u8;
    let _tsp = tsp as *const u8;
    let _sigmask = sigmask as *const u8;
    // let msg = str_format!(
    //     str256,
    //     "sys_ppoll({ufds:?}, {nfds}, {tsp:?}, {sigmask:?}, {sigsetsize})"
    // );
    // print(&msg);
    Ok(0)
}
