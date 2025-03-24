use super::pager::{PageTraceEvent, PagedMemory};
use super::r0vm::Risc0Context;
use crate::execute::{MACHINE_REGS_ADDR, REG_MAX, USER_REGS_ADDR};
use anyhow::Result;
use risc0_binfmt::{ByteAddr, MemoryImage};
//use std::process::{ChildStdin, ChildStdout, Command, Stdio};
use std::os::unix::net::UnixStream;

use memmap2::MmapMut;
use qapi::{Qmp, Stream};
use risc0_zkp::core::digest::Digest;
use serde::{Deserialize, Serialize};
use std::fs::OpenOptions;
use std::io::BufReader;
use std::sync::{
    atomic::{AtomicBool, Ordering},
    Mutex, MutexGuard,
};

#[allow(non_camel_case_types)]
#[allow(deprecated)]
#[allow(dead_code)]
#[allow(non_snake_case)]
mod generated {
    use serde::{Deserialize, Serialize};
    include!(concat!(env!("OUT_DIR"), "/qmp.rs"));
}

use generated::{
    r0vm_mark_page_read, r0vm_mark_page_write, r0vm_reset_pages, r0vm_run_some, R0VMState,
};

pub(crate) struct Qemu {
    //qmp: Qmp<qapi::Stream<BufReader<ChildStdout>, ChildStdin>>,
    qmp: Qmp<qapi::Stream<BufReader<UnixStream>, UnixStream>>,
    _page_buf: MmapMut,
    pub pager: PagedMemory,
    trace_enabled: bool,
    trace_events: Vec<PageTraceEvent>,
    _mu: MutexGuard<'static, ()>,
}

#[derive(Serialize, Deserialize)]
// Track cycles for repeatability
pub struct Tracker {
    pub image_id: Digest,
    pub elems: Vec<Option<u32>>,
}

static DID_QEMU: AtomicBool = AtomicBool::new(false);

impl Tracker {
    pub(crate) fn new(image_id: Digest) -> Self {
        let filename = format!("/tmp/cycles.{image_id}");
        match std::fs::read(filename) {
            Ok(contents) => {
                println!("Loading cycles for {}", image_id);
                serde_json::from_str(std::str::from_utf8(contents.as_slice()).unwrap()).unwrap()
            }
            Err(err) => {
                println!("Nothing saved, so new cycles for {} because of {err}", image_id);

                Tracker {
                    image_id,
                    elems: Vec::new(),
                }
            }
        }
    }

    pub(crate) fn track(&mut self, user_cycles: usize, pc: u32) {
        if true { return }
        if self.elems.len() <= user_cycles {
            self.elems.resize(user_cycles + 1, None);
        }

        let elem = &mut self.elems[user_cycles];
        tracing::trace!("user_cycles: {user_cycles} pc: {pc} expecting {elem:?}");
        if elem.is_some() {
            assert!(elem.unwrap() == pc);
        } else {
            assert!(!DID_QEMU.load(Ordering::Relaxed), "Did not expect a cycle at {user_cycles} pc {pc:#x}");
            *elem = Some(pc);
        }
    }

    pub fn dump(&self) {
        if DID_QEMU.load(Ordering::Relaxed) {
            println!("Skipping cycle dump because we used qemu");
        } else {
            println!("Dumping cycles for {}", self.image_id);
            let filename = format!("/tmp/cycles.{}", self.image_id);
            std::fs::write(filename, serde_json::to_string(&self).unwrap()).unwrap();
        }
    }
}

const MEM_FILE: &str = "/tmp/qemu-guest-mem.dat";

static MU: Mutex<()> = Mutex::new(());
const SOCKET: &str = "/tmp/qemu.sock";

impl<'a> Qemu {
    pub fn new(image: MemoryImage, trace_enabled: bool) -> Self {
        let mut mu = MU.lock();
        if MU.is_poisoned() {
            MU.clear_poison();
            mu = MU.lock();
        }
        let mu = mu.unwrap();
//        std::thread::sleep(std::time::Duration::from_secs(1));

        let mem_file = OpenOptions::new()
            .write(true)
            .read(true)
            .create(true)
            .open(MEM_FILE)
            .unwrap();
        mem_file.set_len(1024 * 1024 * 1024 * 4).unwrap();
        let mut page_buf = unsafe { MmapMut::map_mut(&mem_file) }.unwrap();

        //        let mut cmd = Command::new("/tmp/qemu-build/qemu-system-riscv32");
        //        cmd.args(["-icount", "shift=1"])
        //            .args(["-mem-path", MEM_FILE]);
        // cmd.args(["-qmp", "stdio"]);
        // cmd.stdin(Stdio::piped());
        // cmd.stdout(Stdio::piped());

        //        }
        //        let child = cmd.spawn().unwrap();

        //        let stream = Stream::new(BufReader::new(child.stdout.unwrap()), child.stdin.unwrap());

        let ustream = UnixStream::connect(SOCKET).expect("failed to connect to socket");
        let ustream2 = ustream.try_clone().unwrap();
        let stream = Stream::new(BufReader::new(ustream), ustream2);
        // unix:/tmp/qemu.sock,server

        let mut qmp = Qmp::new(stream);

        let info = qmp.handshake().expect("handshake failed");
        println!("QMP info: {:#?}", info);

        let pager = PagedMemory::new(
            image,
            /* tracing enabled=*/ true,
            page_buf.as_mut_ptr(),
        );
        qmp.execute(&r0vm_reset_pages {}).unwrap();

        Self {
            qmp,
            pager,
            _page_buf: page_buf,
            trace_enabled,
            trace_events: Vec::new(),
            _mu: mu,
        }
    }

    pub fn reset(&mut self) {
        self.qmp.execute(&r0vm_reset_pages {}).unwrap();
    }

    pub(crate) fn trace_events(&self) -> &[PageTraceEvent] {
        &self.trace_events
    }

    pub(crate) fn clear_trace_events(&mut self) {
        self.trace_events.clear();
    }

    pub fn process_trace_events(&mut self) {
        for event in self.pager.trace_events() {
            match *event {
                PageTraceEvent::PageIn { page_idx, .. } => {
                    if page_idx > 0 {
                        self.qmp.execute(&r0vm_mark_page_read { page_idx }).unwrap();
                    }
                }
                PageTraceEvent::PageOut { page_idx, .. } => {
                    if page_idx > 0 {
                        self.qmp
                            .execute(&r0vm_mark_page_write { page_idx })
                            .unwrap();
                    }
                }
            }
        }
        if self.trace_enabled {
            self.trace_events.extend(self.pager.trace_events())
        }
        self.pager.clear_trace_events();
    }

    pub fn step(&mut self, ctx: &mut impl Risc0Context, cycle_budget: usize) -> Result<()> {
        let base = if ctx.get_machine_mode() != 0 {
            MACHINE_REGS_ADDR.waddr()
        } else {
            USER_REGS_ADDR.waddr()
        };
        let mut in_regs = Vec::new();
        for idx in 0..REG_MAX {
            in_regs.push(self.pager.load_register(base, idx));
        }
        DID_QEMU.store(true, Ordering::Relaxed);

        let in_state = R0VMState {
            pc: ctx.get_pc().0,
            registers: in_regs,
            machine_mode: ctx.get_machine_mode() > 0,
            cycle_budget: cycle_budget as u32,
        };

        let out_state = self
            .qmp
            .execute(&r0vm_run_some { state: in_state })
            .unwrap();

        assert!(
            out_state.cycle_budget as usize <= cycle_budget,
            "input budget: {cycle_budget} output budget: {}",
            out_state.cycle_budget
        );

        let cycles_used = cycle_budget - out_state.cycle_budget as usize;
        ctx.inc_user_cycles(cycles_used, /*ecall=*/ None);
        tracing::trace!("qemu cycles used: {cycles_used}");

        // TODO: Do we want qemu to be able to update machine mode?
        assert_eq!(out_state.machine_mode, ctx.get_machine_mode() > 0);
        ctx.set_pc(ByteAddr(out_state.pc));
        for idx in 0..REG_MAX {
            self.pager
                .store_register(base, idx, out_state.registers[idx]);
        }

        Ok(())
    }
}

// xori:
// 2025-03-20T21:53:14.241133Z TRACE risc0_circuit_rv32im::execute::executor: [172:6105:171] 0x07000200> 0x00000073  ecall
// 2025-03-20T21:53:14.241149Z TRACE risc0_circuit_rv32im::execute::r0vm: ecall from machine_mode = true
