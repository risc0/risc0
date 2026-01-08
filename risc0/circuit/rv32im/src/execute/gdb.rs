// Copyright 2026 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use anyhow::Result;
use gdbstub::{
    common::Signal,
    conn::ConnectionExt,
    stub::{SingleThreadStopReason, run_blocking},
    target::{
        Target,
        ext::{
            base::{
                BaseOps,
                singlethread::{SingleThreadBase, SingleThreadResume},
            },
            breakpoints::{Breakpoints, SwBreakpoint},
        },
    },
};
use risc0_binfmt::ByteAddr;

use crate::TerminateState;

use super::{
    Syscall,
    executor::Executor,
    platform::*,
    r0vm::{LoadOp, Risc0Context as _, Risc0Machine},
    rv32im::Emulator,
};

pub enum ExecState {
    Step(u32),
    Continue,
}

pub struct Debugger<'a, 'b, S: Syscall> {
    exec: &'b mut Executor<'a, S>,
    emu: Emulator,
    exec_state: ExecState,
    breakpoints: Vec<u32>,
}

impl<'a, 'b, S: Syscall> Debugger<'a, 'b, S> {
    pub fn new(exec: &'b mut Executor<'a, S>) -> Self {
        let s = Self {
            exec,
            emu: Emulator::new(),
            breakpoints: vec![],
            exec_state: ExecState::Continue,
        };

        Risc0Machine::resume(s.exec).unwrap();
        s
    }

    fn run(
        &mut self,
        conn: &mut Box<dyn ConnectionExt<Error = std::io::Error>>,
    ) -> Result<GdbStatus> {
        match self.exec_state {
            ExecState::Continue => self.run_continue(conn),
            ExecState::Step(n) => self.run_n_steps(n),
        }
    }

    fn run_n_steps(&mut self, steps: u32) -> Result<GdbStatus> {
        for _ in 0..steps {
            if let GdbStatus::Event(e @ GdbEvent::ExecHalted(_)) = self.step()? {
                return Ok(GdbStatus::Event(e));
            }
        }
        Ok(GdbStatus::Event(GdbEvent::DoneStep))
    }

    fn step(&mut self) -> Result<GdbStatus> {
        use GdbEvent::*;
        use GdbStatus::*;

        Risc0Machine::step(&mut self.emu, self.exec).unwrap();

        if let Some(TerminateState { a0, .. }) = self.exec.terminate_state() {
            return Ok(Event(ExecHalted(u32::from(*a0))));
        }

        Ok(Event(DoneStep))
    }

    fn run_continue(
        &mut self,
        conn: &mut Box<dyn ConnectionExt<Error = std::io::Error>>,
    ) -> Result<GdbStatus> {
        use GdbEvent::*;
        use GdbStatus::*;

        loop {
            if conn.peek().map(|r| r.is_some()).unwrap_or(true) {
                return Ok(InComingData);
            }
            if self.breakpoints.contains(&self.exec.get_pc().0) {
                return Ok(Event(BreakpointHit));
            }
            if let Event(e @ ExecHalted(_)) = self.step()? {
                return Ok(Event(e));
            }
        }
    }
}

impl<S: Syscall> Target for Debugger<'_, '_, S> {
    type Error = anyhow::Error;
    type Arch = gdbstub_arch::riscv::Riscv32;

    fn base_ops(&mut self) -> gdbstub::target::ext::base::BaseOps<'_, Self::Arch, Self::Error> {
        BaseOps::SingleThread(self)
    }

    fn support_breakpoints(
        &mut self,
    ) -> Option<gdbstub::target::ext::breakpoints::BreakpointsOps<'_, Self>> {
        Some(self)
    }
}

impl<S: Syscall> Breakpoints for Debugger<'_, '_, S> {
    fn support_sw_breakpoint(
        &mut self,
    ) -> Option<gdbstub::target::ext::breakpoints::SwBreakpointOps<'_, Self>> {
        Some(self)
    }
}

impl<S: Syscall> SwBreakpoint for Debugger<'_, '_, S> {
    fn add_sw_breakpoint(
        &mut self,
        addr: <Self::Arch as gdbstub::arch::Arch>::Usize,
        _kind: <Self::Arch as gdbstub::arch::Arch>::BreakpointKind,
    ) -> gdbstub::target::TargetResult<bool, Self> {
        eprintln!("setting breakpoint at {addr:X}");
        self.breakpoints.push(addr);
        Ok(true)
    }
    fn remove_sw_breakpoint(
        &mut self,
        addr: <Self::Arch as gdbstub::arch::Arch>::Usize,
        _kind: <Self::Arch as gdbstub::arch::Arch>::BreakpointKind,
    ) -> gdbstub::target::TargetResult<bool, Self> {
        match self.breakpoints.iter().position(|b| *b == addr) {
            None => Ok(false),
            Some(index) => {
                self.breakpoints.remove(index);
                Ok(true)
            }
        }
    }
}

impl<S: Syscall> SingleThreadBase for Debugger<'_, '_, S> {
    fn read_registers(
        &mut self,
        regs: &mut <Self::Arch as gdbstub::arch::Arch>::Registers,
    ) -> gdbstub::target::TargetResult<(), Self> {
        let base = if self.exec.get_machine_mode() != 0 {
            MACHINE_REGS_ADDR.waddr()
        } else {
            USER_REGS_ADDR.waddr()
        };
        for i in 0..REG_MAX {
            regs.x[i] = self.exec.load_register(LoadOp::Peek, base, i).unwrap();
        }
        regs.pc = self.exec.get_pc().0;
        Ok(())
    }

    fn write_registers(
        &mut self,
        regs: &<Self::Arch as gdbstub::arch::Arch>::Registers,
    ) -> gdbstub::target::TargetResult<(), Self> {
        let base = if self.exec.get_machine_mode() != 0 {
            MACHINE_REGS_ADDR.waddr()
        } else {
            USER_REGS_ADDR.waddr()
        };
        for i in 0..REG_MAX {
            self.exec.store_register(base, i, regs.x[i]).unwrap();
        }
        self.exec.set_pc(ByteAddr(regs.pc));
        Ok(())
    }

    fn read_addrs(
        &mut self,
        start_addr: <Self::Arch as gdbstub::arch::Arch>::Usize,
        data: &mut [u8],
    ) -> gdbstub::target::TargetResult<usize, Self> {
        data.copy_from_slice(
            &self
                .exec
                .load_region(LoadOp::Peek, ByteAddr(start_addr), data.len())
                .unwrap()[..],
        );
        Ok(data.len())
    }

    fn write_addrs(
        &mut self,
        start_addr: <Self::Arch as gdbstub::arch::Arch>::Usize,
        data: &[u8],
    ) -> gdbstub::target::TargetResult<(), Self> {
        self.exec.store_region(ByteAddr(start_addr), data).unwrap();
        Ok(())
    }

    #[inline(always)]
    fn support_resume(
        &mut self,
    ) -> Option<gdbstub::target::ext::base::singlethread::SingleThreadResumeOps<'_, Self>> {
        Some(self)
    }
}

impl<S: Syscall> SingleThreadResume for Debugger<'_, '_, S> {
    fn resume(&mut self, _signal: Option<gdbstub::common::Signal>) -> Result<(), Self::Error> {
        Ok(())
    }
}

pub enum GdbStatus {
    InComingData,
    Event(GdbEvent),
}

#[derive(Debug)]
pub enum GdbEvent {
    DoneStep,
    ExecHalted(u32),
    BreakpointHit,
}

impl<S: Syscall> run_blocking::BlockingEventLoop for Debugger<'_, '_, S> {
    type Target = Self;
    type Connection = Box<dyn ConnectionExt<Error = std::io::Error>>;
    type StopReason = SingleThreadStopReason<u32>;

    fn wait_for_stop_reason(
        target: &mut Self,
        conn: &mut Self::Connection,
    ) -> core::result::Result<
        run_blocking::Event<Self::StopReason>,
        run_blocking::WaitForStopReasonError<
            <Self::Target as Target>::Error,
            <Self::Connection as gdbstub::conn::Connection>::Error,
        >,
    > {
        match target.run(conn) {
            Ok(GdbStatus::InComingData) => {
                let byte = conn
                    .read()
                    .map_err(run_blocking::WaitForStopReasonError::Connection)?;
                Ok(run_blocking::Event::IncomingData(byte))
            }
            Ok(GdbStatus::Event(event)) => {
                let stop_event = match event {
                    GdbEvent::ExecHalted(e) => SingleThreadStopReason::Exited(e as u8),
                    GdbEvent::DoneStep => SingleThreadStopReason::DoneStep,
                    GdbEvent::BreakpointHit => SingleThreadStopReason::SwBreak(()),
                };
                Ok(run_blocking::Event::TargetStopped(stop_event))
            }
            Err(e) => Err(run_blocking::WaitForStopReasonError::Target(e)),
        }
    }

    fn on_interrupt(
        _target: &mut Self,
    ) -> core::result::Result<Option<Self::StopReason>, <Self::Target as Target>::Error> {
        eprintln!("interrupt received from debugger");
        Ok(Some(SingleThreadStopReason::Signal(Signal::SIGINT)))
    }
}
