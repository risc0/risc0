use super::pager::{PageTraceEvent, PagedMemory};
use super::r0vm::Risc0Context;
use anyhow::Result;
use num_derive::FromPrimitive;
use risc0_binfmt::{ByteAddr, MemoryImage};
use std::sync::{Mutex, Once};

#[derive(Debug, FromPrimitive)]
#[repr(i32)]
#[allow(non_camel_case_types)]
enum QException {
    RISCV_EXCP_NONE = -1, /* sentinel value */
    RISCV_EXCP_INST_ADDR_MIS = 0x0,
    RISCV_EXCP_INST_ACCESS_FAULT = 0x1,
    RISCV_EXCP_ILLEGAL_INST = 0x2,
    RISCV_EXCP_BREAKPOINT = 0x3,
    RISCV_EXCP_LOAD_ADDR_MIS = 0x4,
    RISCV_EXCP_LOAD_ACCESS_FAULT = 0x5,
    RISCV_EXCP_STORE_AMO_ADDR_MIS = 0x6,
    RISCV_EXCP_STORE_AMO_ACCESS_FAULT = 0x7,
    RISCV_EXCP_U_ECALL = 0x8,
    RISCV_EXCP_S_ECALL = 0x9,
    RISCV_EXCP_VS_ECALL = 0xa,
    RISCV_EXCP_M_ECALL = 0xb,
    RISCV_EXCP_INST_PAGE_FAULT = 0xc,  /* since: priv-1.10.0 */
    RISCV_EXCP_LOAD_PAGE_FAULT = 0xd,  /* since: priv-1.10.0 */
    RISCV_EXCP_STORE_PAGE_FAULT = 0xf, /* since: priv-1.10.0 */
    RISCV_EXCP_DOUBLE_TRAP = 0x10,
    RISCV_EXCP_SW_CHECK = 0x12, /* since: priv-1.13.0 */
    RISCV_EXCP_HW_ERR = 0x13,   /* since: priv-1.13.0 */
    RISCV_EXCP_INST_GUEST_PAGE_FAULT = 0x14,
    RISCV_EXCP_LOAD_GUEST_ACCESS_FAULT = 0x15,
    RISCV_EXCP_VIRT_INSTRUCTION_FAULT = 0x16,
    RISCV_EXCP_STORE_GUEST_AMO_ACCESS_FAULT = 0x17,
    RISCV_EXCP_SEMIHOST = 0x3f,

    EXCP_INTERRUPT = 0x10000, /* async interruption */
    EXCP_HLT = 0x10001,       /* hlt instruction reached */
    EXCP_DEBUG = 0x10002,     /* cpu stopped after a breakpoint or singlestep */
    EXCP_HALTED = 0x10003,    /* cpu is halted (waiting for external event) */
    EXCP_YIELD = 0x10004,     /* cpu wants to yield timeslice to another */
    EXCP_ATOMIC = 0x10005,    /* stop-the-world and emulate atomic */
}

#[repr(C)]
struct TaskState {
    pc: u32,
    machine_mode: u32,
    cycle_budget: u32,
    badaddr: u32,
}

extern "C" {
    fn r0vm_init();

    fn r0vm_run_some(state: *mut TaskState) -> u32;

    fn r0vm_reset_pages();
    fn r0vm_set_page_readable(idx: u32);
    fn r0vm_set_page_writable(idx: u32);

    static guest_base: usize;
}

pub(crate) struct Qemu {
    pub pager: PagedMemory,
    trace_enabled: bool,
    trace_events: Vec<PageTraceEvent>,
}

static START: Once = Once::new();
static INSTANCE_COUNT: Mutex<usize> = Mutex::new(0);

impl Drop for Qemu {
    fn drop(&mut self) {
        let mut mu = INSTANCE_COUNT.lock().unwrap();

        assert!(*mu > 0);
        *mu -= 1;
    }
}

impl Qemu {
    pub fn new(image: MemoryImage, trace_enabled: bool) -> Self {
        START.call_once(|| {
            unsafe { r0vm_init() };
        });

        let mut mu = INSTANCE_COUNT.lock().unwrap();
        assert_eq!(*mu, 0);
        *mu += 1;

        unsafe {
            r0vm_reset_pages();
            assert!(guest_base != 0);
            println!("guest base: {:#X}", guest_base);
            Qemu {
                pager: PagedMemory::new(
                    image,
                    /*tracing enabled=*/ true,
                    guest_base as *mut u8,
                ),
                trace_events: Vec::new(),
                trace_enabled,
            }
        }
    }

    pub fn reset(&mut self) {
        unsafe { r0vm_reset_pages() };
        self.pager.reset();
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
                PageTraceEvent::PageIn { page_idx, .. } => unsafe {
                    if page_idx > 0 {
                        r0vm_set_page_readable(page_idx)
                    }
                },
                PageTraceEvent::PageOut { page_idx, .. } => unsafe {
                    if page_idx > 0 {
                        r0vm_set_page_writable(page_idx)
                    }
                },
            }
        }
        if self.trace_enabled {
            self.trace_events.extend(self.pager.trace_events())
        }
        self.pager.clear_trace_events();
    }

    pub fn step(&mut self, ctx: &mut impl Risc0Context, cycle_budget: usize) -> Result<()> {
        self.pager.write_registers();

        let mut task_state = TaskState {
            pc: ctx.get_pc().0,
            machine_mode: ctx.get_machine_mode(),
            cycle_budget: cycle_budget as u32,
            badaddr: 0,
        };

        let _task_exception = unsafe { r0vm_run_some(&mut task_state) };

        assert!(
            task_state.cycle_budget as usize <= cycle_budget,
            "input budget: {cycle_budget} output budget: {}",
            task_state.cycle_budget
        );

        let cycles_used = cycle_budget - task_state.cycle_budget as usize;
        ctx.inc_user_cycles(cycles_used, /*ecall=*/ None);
        println!("qemu cycles used: {cycles_used}");

        // TODO: Do we want qemu to be able to update machine mode?
        assert_eq!(task_state.machine_mode, ctx.get_machine_mode());
        ctx.set_pc(ByteAddr(task_state.pc));
        self.pager.read_registers();
        Ok(())
    }
}


// xori:
// 2025-03-20T21:53:14.241133Z TRACE risc0_circuit_rv32im::execute::executor: [172:6105:171] 0x07000200> 0x00000073  ecall
// 2025-03-20T21:53:14.241149Z TRACE risc0_circuit_rv32im::execute::r0vm: ecall from machine_mode = true
