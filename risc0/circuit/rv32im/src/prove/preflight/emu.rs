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

use std::collections::BTreeMap;

use anyhow::{Result, bail};

use risc0_binfmt::MemoryImage;
use risc0_circuit_rv32im_sys::{
    DecodeWitness, FetchWitness, InstAuipcOptions, InstAuipcWitness, InstBranchOptions,
    InstBranchWitness, InstEcallOptions, InstEcallWitness, InstImmOptions, InstImmWitness,
    InstJalOptions, InstJalWitness, InstJalrOptions, InstJalrWitness, InstLoadOptions,
    InstLoadWitness, InstLuiOptions, InstLuiWitness, InstMretOptions, InstMretWitness,
    InstRegOptions, InstRegWitness, InstResumeWitness, InstStoreOptions, InstStoreWitness,
    InstSuspendWitness, InstTrapWitness, MakeTableWitness, Opcode, PhysMemReadWitness,
    PhysMemWriteWitness, RegMemReadWitness, RegMemWriteWitness, UnitAddSubWitness, UnitBaseWitness,
    UnitBitWitness, UnitDivWitness, UnitLtWitness, UnitMulWitness, UnitShiftWitness,
    VirtAddrWitness, VirtMemReadWitness, VirtMemWriteWitness,
    opt::{
        AsKind, BitKind, BrKind, DivKind, DivUOptions, LoadKind, MulKind, MulUuOptions, OutKind,
        ShiftKind, StoreKind, UnitKind, UnitOptions,
    },
    visit_rv32im_instr,
};

use crate::execute::{
    HOST_ECALL_BIGINT, HOST_ECALL_POSEIDON2, HOST_ECALL_READ, HOST_ECALL_TERMINATE,
    HOST_ECALL_WRITE, REG_A7,
};
use crate::prove::preflight::{
    constants::{
        BITS_PER_BYTE, BYTES_PER_WORD, COMPRESSED_INST_LOOKUP_WORD, CSR_MEPC, CSR_MNOV2COMPAT,
        CSR_MSMODE, CSR_MSPC, CSR_MTECALL, CSR_MTEXCEPT, CSR_MVERSION, KERNEL_START_WORD,
        MACHINE_REGS_WORD, MEMORY_SIZE_MPAGES, MODE_MACHINE, MODE_USER, MPAGE_MASK_WORDS,
        MPAGE_SIZE_WORDS_PO2, RV32IM_CIRCUIT_VERSION, USER_REGS_WORD, V2_COMPAT_ECALL_DISPATCH,
        V2_COMPAT_MEPC, V2_COMPAT_SMODE, V2_COMPAT_SPC, V2_COMPAT_TRAP_DISPATCH, V2_COMPAT_VERSION,
        VPAGE_MASK_WORDS, VPAGE_SIZE_WORDS_PO2, csr_word,
    },
    decode::{DecodedInst, get_opcode},
    paging::{PageDetails, PagedMemory},
    trace::{Trace, TraceIndex},
};

const CYCLE_TABLE_ROWS: u32 = 24;

pub struct Emulator {
    memory: PagedMemory,
    pages: Vec<Option<PageDetails>>,

    m_inst_cache: BTreeMap<u32, TraceIndex<DecodeWitness>>,
    us_inst_cache: BTreeMap<u32, TraceIndex<DecodeWitness>>,

    // Machine state
    v2_compat: bool,
    done: bool,
    reg_offset: u32,
    user_cycles: u32,
    cur_cycle: u32,
    i_cache_cycle: u32,
    mode: u32,
    pc: u32,
    new_pc: u32,
    dinst: Option<TraceIndex<DecodeWitness>>,
}

impl Emulator {
    pub fn new(image: MemoryImage) -> Result<Self> {
        let mut memory = PagedMemory::new(image);
        let mut pages = vec![None; MEMORY_SIZE_MPAGES as usize];
        pages[(MACHINE_REGS_WORD >> MPAGE_SIZE_WORDS_PO2) as usize] =
            Some(memory.page_in(MACHINE_REGS_WORD >> MPAGE_SIZE_WORDS_PO2)?);

        Ok(Self {
            memory,
            pages,

            m_inst_cache: Default::default(),
            us_inst_cache: Default::default(),

            v2_compat: true,
            done: false,
            reg_offset: 0,
            user_cycles: 0,
            cur_cycle: 1,
            i_cache_cycle: 1,
            mode: 0,
            pc: 0,
            new_pc: 0,
            dinst: None,
        })
    }

    fn reg_page(&self) -> &PageDetails {
        self.pages[(MACHINE_REGS_WORD >> MPAGE_SIZE_WORDS_PO2) as usize]
            .as_ref()
            .unwrap()
    }

    fn reg_page_mut(&mut self) -> &mut PageDetails {
        self.pages[(MACHINE_REGS_WORD >> MPAGE_SIZE_WORDS_PO2) as usize]
            .as_mut()
            .unwrap()
    }

    fn read_phys_memory(&mut self, word_addr: u32) -> Result<(u32, PhysMemReadWitness)> {
        let page_id = word_addr >> MPAGE_SIZE_WORDS_PO2;
        if self.pages[page_id as usize].is_none() {
            self.pages[page_id as usize] = Some(self.memory.page_in(page_id)?);
        }
        let page = self.pages[page_id as usize].as_mut().unwrap();
        let word_num = word_addr & MPAGE_MASK_WORDS as u32;
        let record = PhysMemReadWitness {
            wordAddr: word_addr,
            prevCycle: page.info()[word_num as usize].cycle,
            value: page.info()[word_num as usize].value,
        };
        page.info_mut()[word_num as usize].cycle = self.cur_cycle * 2;
        Ok((record.value, record))
    }

    fn write_phys_memory(&mut self, word_addr: u32, value: u32) -> Result<PhysMemWriteWitness> {
        let page_id = word_addr >> MPAGE_SIZE_WORDS_PO2;
        let page_entry = &mut self.pages[page_id as usize];
        if page_entry.is_none() {
            *page_entry = Some(self.memory.page_in(page_id)?);
        }
        let page = page_entry.as_mut().unwrap();

        let word_num = word_addr & (MPAGE_MASK_WORDS as u32);
        let page = &mut page.info_mut()[word_num as usize];

        let wit = PhysMemWriteWitness {
            wordAddr: word_addr,
            prevCycle: page.cycle,
            prevValue: page.value,
            value,
        };

        page.value = value;
        page.cycle = self.cur_cycle * 2 + 1;

        Ok(wit)
    }

    fn peek_virt_memory(&mut self, word_addr: u32) -> Result<u32> {
        self.peek_phys_memory(word_addr) // TODO
    }

    fn translate_address(&mut self, v_word_addr: u32) -> (u32, VirtAddrWitness) {
        let vpage = v_word_addr >> VPAGE_SIZE_WORDS_PO2;
        let ppage = vpage; // TODO: Translate
        let word_offset = v_word_addr & (VPAGE_MASK_WORDS as u32);

        let value = (ppage << VPAGE_SIZE_WORDS_PO2) | word_offset;
        let record = VirtAddrWitness {
            readCycle: 0,
            vpage,
            ppage,
            wordOffset: v_word_addr & (VPAGE_MASK_WORDS as u32),
        };
        (value, record)
    }

    fn read_virt_memory(&mut self, v_word_addr: u32) -> Result<(u32, VirtMemReadWitness)> {
        let (p_word_addr, addr) = self.translate_address(v_word_addr);
        let (_, phys) = self.read_phys_memory(p_word_addr)?;

        let record = VirtMemReadWitness {
            addr,
            prevCycle: phys.prevCycle,
            value: phys.value,
        };

        Ok((record.value, record))
    }

    fn undo_read_phys_memory(&mut self, record: &PhysMemReadWitness) {
        let page_id = record.wordAddr >> MPAGE_SIZE_WORDS_PO2;
        let page = self.pages[page_id as usize].as_mut().unwrap();
        let word_num = record.wordAddr & (MPAGE_MASK_WORDS as u32);
        page.info_mut()[word_num as usize].cycle = record.prevCycle;
    }

    fn undo_read_virt_memory(&mut self, record: &VirtMemReadWitness) {
        let phys = PhysMemReadWitness {
            value: 0,
            wordAddr: record.addr.vpage << VPAGE_SIZE_WORDS_PO2 | record.addr.wordOffset,
            prevCycle: record.prevCycle,
        };
        self.undo_read_phys_memory(&phys);
    }

    fn write_virt_memory(&mut self, v_word_addr: u32, value: u32) -> Result<VirtMemWriteWitness> {
        let (p_word_addr, record_addr) = self.translate_address(v_word_addr);
        let phys = self.write_phys_memory(p_word_addr, value)?;
        Ok(VirtMemWriteWitness {
            addr: record_addr,
            prevCycle: phys.prevCycle,
            prevValue: phys.prevValue,
            value: phys.value,
        })
    }

    fn do_resume(&mut self, trace: &mut Trace) -> Result<()> {
        let (v2_compat_value, resume_wit_v2_compat) =
            self.read_phys_memory(csr_word(CSR_MNOV2COMPAT))?;
        self.v2_compat = v2_compat_value != 1;

        trace.globals_mut().v2Compat = self.v2_compat as u32;
        let (pc, mode, version) = if self.v2_compat {
            let (new_pc, resume_wit_pc) = self.read_phys_memory(V2_COMPAT_SPC)?;
            self.pc = new_pc;
            let (mode, resume_wit_mode) = self.read_phys_memory(V2_COMPAT_SMODE)?;
            self.set_mode(if mode != 0 { MODE_MACHINE } else { MODE_USER });
            let resume_wit_version =
                self.write_phys_memory(V2_COMPAT_VERSION, RV32IM_CIRCUIT_VERSION)?;

            (resume_wit_pc, resume_wit_mode, resume_wit_version)
        } else {
            let (new_pc, resume_wit_pc) = self.read_phys_memory(V2_COMPAT_SPC)?;
            self.pc = new_pc;
            let (mode, resume_wit_mode) = self.read_phys_memory(csr_word(CSR_MSMODE))?;
            self.set_mode(mode);
            let resume_wit_version =
                self.write_phys_memory(csr_word(CSR_MVERSION), RV32IM_CIRCUIT_VERSION)?;

            (resume_wit_pc, resume_wit_mode, resume_wit_version)
        };

        trace.add_block(InstResumeWitness {
            v2Compat: resume_wit_v2_compat,
            pc,
            mode,
            version,
        });

        self.cur_cycle += 1;

        Ok(())
    }

    fn do_suspend(&mut self, trace: &mut Trace) -> Result<()> {
        let cycle = self.cur_cycle;
        let i_cache_cycle = self.i_cache_cycle;

        let (pc, mode) = if self.v2_compat {
            (
                self.write_phys_memory(V2_COMPAT_SPC, self.pc)?,
                self.write_phys_memory(V2_COMPAT_SMODE, (self.mode == MODE_MACHINE) as u32)?,
            )
        } else {
            (
                self.write_phys_memory(csr_word(CSR_MSPC), self.pc)?,
                self.write_phys_memory(csr_word(CSR_MSMODE), (self.mode == MODE_MACHINE) as u32)?,
            )
        };

        trace.add_block(InstSuspendWitness {
            cycle,
            iCacheCycle: i_cache_cycle,
            pc,
            mode,
        });
        self.cur_cycle += 1;

        Ok(())
    }

    fn is_done(&self, trace: &Trace, row_count: usize, end_cycle: u32) -> bool {
        let used_rows = trace.get_row_count()
            + self.cur_cycle.div_ceil(CYCLE_TABLE_ROWS) as usize
            + self.memory.paging_cost();
        self.done || row_count < used_rows || self.user_cycles == end_cycle
    }

    fn fetch_and_decode(&mut self) -> Result<Option<DecodeWitness>> {
        if self.mode != MODE_MACHINE && self.pc / 4 >= KERNEL_START_WORD {
            return Ok(None);
        }

        // We always read the memory address at pc/4
        let (l0, load0) = self.read_virt_memory(self.pc / 4)?;

        // If pc == 2 (mod 4), shift to lower value
        let tmp_inst = if self.pc % 4 == 2 { l0 >> 16 } else { l0 };

        // Check if low bits are 11 (normal) or anything else (compressed)
        let compressed = tmp_inst & 3 != 3;

        let (inst, load1) = if !compressed {
            // if needed, add in second half to inst
            if self.pc % 4 == 2 {
                // For unaligned addresses, always read next address
                let (l1, load1) = self.read_virt_memory(self.pc / 4 + 1)?;
                (tmp_inst | l1 << 16, load1)
            } else {
                // For aligned addresses, read from a `null` word (and ignore the value)
                let (_, load1) = self.read_virt_memory(COMPRESSED_INST_LOOKUP_WORD)?;
                (tmp_inst, load1)
            }
        } else {
            // Remove any high bits, and then do a lookup to convert
            self.read_virt_memory(COMPRESSED_INST_LOOKUP_WORD + tmp_inst & 0xFFFF)?
        };

        let decoded = DecodedInst::new(inst);
        let opcode = get_opcode(&decoded);

        let fetch = FetchWitness {
            iCacheCycle: self.i_cache_cycle,
            loadCycle: self.cur_cycle,
            mode: self.mode,
            pc: self.pc,
            nextPc: self.pc.wrapping_add(if compressed { 2 } else { 4 }),
        };

        macro_rules! get_imm {
            ($(($name:ident, $idx:expr, $opcode:expr, $imm_type:expr $(, $rest:expr)*)),+) => {
                paste::paste! {
                    match opcode {
                        $(Opcode::$name => {
                            decoded.[<imm_ $imm_type>]()
                        },)*
                        Opcode::Invalid => {
                            self.undo_read_virt_memory(&load1);
                            self.undo_read_virt_memory(&load0);
                            return Ok(None);
                        }
                    }
                }
            };
        }
        let imm = visit_rv32im_instr!(get_imm);

        Ok(Some(DecodeWitness {
            opcode: opcode as u8,
            rd: decoded.rd as u8,
            rs1: decoded.rs1 as u8,
            rs2: decoded.rs2 as u8,
            imm,
            fetch,
            load0,
            load1,
            inst,
            count: 1,
        }))
    }

    fn trap(&mut self, trace: &mut Trace, reason: &str) -> Result<()> {
        if self.mode == MODE_MACHINE {
            bail!("Trap: Double trap: {reason}");
        }
        tracing::debug!("Trap: {reason}");

        // Save PC + jump to dispatch address
        let cycle = self.cur_cycle;
        let i_cache_cycle = self.i_cache_cycle;
        let mepc_word = if self.v2_compat {
            V2_COMPAT_MEPC
        } else {
            csr_word(CSR_MEPC)
        };
        let save_pc = self.write_phys_memory(mepc_word, self.pc)?;
        self.set_mode(MODE_MACHINE);
        let mtvec_word = if self.v2_compat {
            V2_COMPAT_TRAP_DISPATCH
        } else {
            csr_word(CSR_MTEXCEPT)
        };
        let (new_pc, dispatch) = self.read_phys_memory(mtvec_word)?;
        self.new_pc = new_pc;

        trace.add_block(InstTrapWitness {
            cycle,
            iCacheCycle: i_cache_cycle,
            savePc: save_pc,
            dispatch,
        });
        Ok(())
    }

    const REG_PAGE_ADDR: u32 = MACHINE_REGS_WORD & (!MPAGE_MASK_WORDS) as u32;

    fn read_reg(&mut self, reg: u32, same_reg: bool) -> (u32, RegMemReadWitness) {
        let word_num = self.reg_offset + reg + if same_reg { 64 } else { 0 };

        let record = RegMemReadWitness {
            wordAddr: Self::REG_PAGE_ADDR + word_num,
            prevCycle: self.reg_page().info()[word_num as usize].cycle,
            value: self.reg_page().info()[word_num as usize].value,
        };
        self.reg_page_mut().info_mut()[word_num as usize].cycle = self.cur_cycle * 2;

        let value = if same_reg {
            self.reg_page().info()[(self.reg_offset + reg) as usize].value
        } else {
            record.value
        };
        (value, record)
    }

    fn peek_reg(&self, reg: u32) -> u32 {
        self.reg_page().info()[(self.reg_offset + reg) as usize].value
    }

    fn write_reg(&mut self, reg: u32, value: u32) -> RegMemWriteWitness {
        let word_num = self.reg_offset + reg + if reg == 0 { 64 } else { 0 };
        let record = RegMemWriteWitness {
            wordAddr: Self::REG_PAGE_ADDR + word_num,
            prevCycle: self.reg_page().info()[word_num as usize].cycle,
            prevValue: self.reg_page().info()[word_num as usize].value,
            value,
        };
        self.reg_page_mut().info_mut()[word_num as usize].value = value;
        self.reg_page_mut().info_mut()[word_num as usize].cycle = self.cur_cycle * 2 + 1;
        record
    }

    fn peek_phys_memory(&mut self, word_addr: u32) -> Result<u32> {
        let page_id = word_addr >> MPAGE_SIZE_WORDS_PO2;
        let page_entry = &mut self.pages[page_id as usize];
        if page_entry.is_none() {
            *page_entry = Some(self.memory.page_in(page_id)?);
        }
        let page = page_entry.as_ref().unwrap();
        Ok(page.info()[(word_addr & (MPAGE_MASK_WORDS as u32)) as usize].value)
    }

    fn unit_add_sub<Opt: UnitOptions>(
        &mut self,
        trace: &mut Trace,
        a: u32,
        b: u32,
    ) -> TraceIndex<UnitBaseWitness> {
        let mut unit = UnitAddSubWitness {
            count: 1,
            opts: Opt::OPT_VALUE,
            a,
            b,
            out0: 0,
            out1: 0,
        };
        match Opt::AS_KIND.unwrap() {
            AsKind::Add => {
                unit.out0 = a.wrapping_add(b);
            }
            AsKind::Sub => {
                unit.out0 = a.wrapping_sub(b);
            }
        }
        trace.add_block(unit).cast()
    }

    fn unit_bit<Opt: UnitOptions>(
        &mut self,
        trace: &mut Trace,
        a: u32,
        b: u32,
    ) -> TraceIndex<UnitBaseWitness> {
        let mut unit = UnitBitWitness {
            count: 1,
            opts: Opt::OPT_VALUE,
            a,
            b,
            out0: 0,
            out1: 0,
        };
        match Opt::BIT_KIND.unwrap() {
            BitKind::Xor => {
                unit.out0 = a ^ b;
            }
            BitKind::Or => {
                unit.out0 = a | b;
            }
            BitKind::And => {
                unit.out0 = a & b;
            }
        }
        trace.add_block(unit).cast()
    }

    fn unit_lt<Opt: UnitOptions>(
        &mut self,
        trace: &mut Trace,
        a: u32,
        b: u32,
    ) -> TraceIndex<UnitBaseWitness> {
        let unit = UnitLtWitness {
            count: 1,
            opts: Opt::OPT_VALUE,
            a,
            b,
            out0: ((a as i32) < (b as i32)) as u32,
            out1: (a < b) as u32,
        };
        trace.add_block(unit).cast()
    }

    fn unit_mul<Opt: UnitOptions>(
        &mut self,
        trace: &mut Trace,
        a: u32,
        b: u32,
    ) -> TraceIndex<UnitBaseWitness> {
        let mut unit = UnitMulWitness {
            count: 1,
            opts: Opt::OPT_VALUE,
            a,
            b,
            out0: 0,
            out1: 0,
        };
        match Opt::MUL_KIND.unwrap() {
            MulKind::Ss => {
                unit.out0 = ((a as i32) as i64).wrapping_mul((b as i32) as i64) as u32;
            }
            MulKind::Su => {
                unit.out0 = ((a as i32) as i64).wrapping_mul(b as i64) as u32;
            }
            MulKind::Uu => {
                unit.out0 = (a as u64).wrapping_mul(b as u64) as u32;
            }
        }
        trace.add_block(unit).cast()
    }

    fn unit_div<Opt: UnitOptions>(
        &mut self,
        trace: &mut Trace,
        a: u32,
        b: u32,
    ) -> TraceIndex<UnitBaseWitness> {
        let mut unit = UnitDivWitness {
            count: 1,
            opts: Opt::OPT_VALUE,
            a,
            b,
            out0: 0,
            out1: 0,
        };
        if matches!(Opt::DIV_KIND.unwrap(), DivKind::S) {
            // Intel processors actually fault if you do a signed division on MIN_INT
            // by 1/-1
            if a == 0x80000000 && (b as i32).abs() == 1 {
                unit.out0 = 0x80000000;
                unit.out1 = 0;
            } else {
                if b == 0 {
                    unit.out0 = 0xffffffff;
                    unit.out1 = a;
                } else {
                    unit.out0 = (a as i32 / b as i32) as u32;
                    unit.out1 = (a as i32 % b as i32) as u32;
                }
            }
            let abs_quot: u32 = if b == 0 {
                0xffffffff
            } else {
                (unit.out0 as i32).abs() as u32
            };
            self.unit_mul::<MulUuOptions>(trace, abs_quot, (b as i32).abs() as u32);
        } else {
            if b == 0 {
                unit.out0 = 0xffffffff;
                unit.out1 = a;
            } else {
                unit.out0 = a / b;
                unit.out1 = a % b;
            }
            self.unit_mul::<MulUuOptions>(trace, unit.out0, b);
        }
        trace.add_block(unit).cast()
    }

    fn unit_shift<Opt: UnitOptions>(
        &mut self,
        trace: &mut Trace,
        mut a: u32,
        b: u32,
    ) -> TraceIndex<UnitBaseWitness> {
        let mut unit = UnitShiftWitness {
            count: 1,
            opts: Opt::OPT_VALUE,
            a,
            b,
            out0: 0,
            out1: 0,
        };
        let po2 = 1 << (b & 0x1f);
        if matches!(Opt::SHIFT_KIND.unwrap(), ShiftKind::Ll) {
            self.unit_mul::<MulUuOptions>(trace, a, po2);
            unit.out0 = a << (b & 0x1f);
        } else {
            let neg = matches!(Opt::SHIFT_KIND.unwrap(), ShiftKind::Ra) && (a & 0x80000000) != 0;
            if neg {
                a = !a;
            }
            self.unit_div::<DivUOptions>(trace, a, po2);
            unit.out0 = a >> (b & 0x1f);
            if neg {
                unit.out0 = !unit.out0;
            }
        }
        trace.add_block(unit).cast()
    }

    fn do_unit<Opt: UnitOptions>(
        &mut self,
        trace: &mut Trace,
        a: u32,
        b: u32,
    ) -> TraceIndex<UnitBaseWitness> {
        match Opt::UNIT_KIND.unwrap() {
            UnitKind::Addsub => self.unit_add_sub::<Opt>(trace, a, b),
            UnitKind::Bit => self.unit_bit::<Opt>(trace, a, b),
            UnitKind::Lt => self.unit_lt::<Opt>(trace, a, b),
            UnitKind::Mul => self.unit_mul::<Opt>(trace, a, b),
            UnitKind::Div => self.unit_div::<Opt>(trace, a, b),
            UnitKind::Shift => self.unit_shift::<Opt>(trace, a, b),
        }
    }

    fn set_mode(&mut self, new_mode: u32) {
        self.mode = new_mode;
        self.reg_offset = if self.mode == MODE_MACHINE {
            MACHINE_REGS_WORD & MPAGE_MASK_WORDS as u32
        } else {
            USER_REGS_WORD & MPAGE_MASK_WORDS as u32
        };
    }

    fn do_inst_reg<Opt: InstRegOptions + UnitOptions>(&mut self, trace: &mut Trace) -> Result<()> {
        let ok = Opt::OUT_KIND.unwrap();
        let dinst = trace.get_block(self.dinst.unwrap());
        let (rs1_val, rs1) = self.read_reg(dinst.rs1 as u32, false);
        let (rs2_val, rs2) = self.read_reg(dinst.rs2 as u32, false);
        let fetch = dinst.fetch;
        let rd = dinst.rd as u32;

        let unit_index = self.do_unit::<Opt>(trace, rs1_val, rs2_val);
        let unit = trace.get_block(unit_index);
        let rd_val = if ok == OutKind::Out0 {
            unit.out0
        } else {
            unit.out1
        };

        trace.add_block(InstRegWitness {
            cycle: self.cur_cycle,
            fetch,
            rs1,
            rs2,
            rd: self.write_reg(rd, rd_val),
            options: <Opt as InstRegOptions>::OPT_VALUE,
            out0: unit.out0,
            out1: unit.out1,
        });
        tracing::trace!("  rs1Val = {rs1_val}, rs2Val = {rs2_val}");
        tracing::trace!("  rdVal = {rd_val}");
        Ok(())
    }

    fn do_inst_imm<Opt: InstImmOptions + UnitOptions>(&mut self, trace: &mut Trace) -> Result<()> {
        let ok = Opt::OUT_KIND.unwrap();
        let dinst = trace.get_block(self.dinst.unwrap());
        let (rs1_val, rs1) = self.read_reg(dinst.rs1 as u32, false);
        let fetch = dinst.fetch;
        let rd = dinst.rd as u32;
        let rs2 = dinst.rs2 as u32;
        let imm = dinst.imm;

        let unit_index = self.do_unit::<Opt>(trace, rs1_val, dinst.imm);
        let unit = trace.get_block(unit_index);
        let rd_val = if ok == OutKind::Out0 {
            unit.out0
        } else {
            unit.out1
        };

        trace.add_block(InstImmWitness {
            cycle: self.cur_cycle,
            fetch,
            rs1,
            rs2,
            rd: self.write_reg(rd, rd_val),
            imm,
            options: <Opt as InstImmOptions>::OPT_VALUE,
            out0: unit.out0,
            out1: unit.out1,
        });
        tracing::trace!("  rs1Val = {rs1_val}, imm = {imm}");
        tracing::trace!("  rdVal = {rd_val}");
        Ok(())
    }

    fn do_inst_load<Opt: InstLoadOptions>(&mut self, trace: &mut Trace) -> Result<()> {
        let kind = Opt::LOAD_KIND.unwrap();
        let dinst = trace.get_block_mut(self.dinst.unwrap());

        // Check alignement + access
        let addr = self.peek_reg(dinst.rs1 as u32) + dinst.imm;
        let alignment_req = match kind {
            LoadKind::Lh | LoadKind::Lhu => 2,
            LoadKind::Lw => 4,
            _ => 1,
        };
        if !addr.is_multiple_of(alignment_req) {
            dinst.count -= 1;
            return self.trap(trace, "Alignement error on load");
        }
        if self.mode != MODE_MACHINE && ((addr / 4) >= KERNEL_START_WORD) {
            dinst.count -= 1;
            return self.trap(trace, "Out of bounds error on load");
        }

        let cycle = self.cur_cycle;
        let fetch = dinst.fetch;
        let (_, rs1) = self.read_reg(dinst.rs1 as u32, false);
        let rs2 = dinst.rs2;
        let imm = dinst.imm;
        let shift = BITS_PER_BYTE * (addr % BYTES_PER_WORD);
        let (in_, mem) = self.read_virt_memory(addr / BYTES_PER_WORD)?;

        let out = match kind {
            LoadKind::Lb => ((((in_ >> shift) & 0xFF) as i8) as i32) as u32,
            LoadKind::Lh => ((((in_ >> shift) & 0xFFFF) as i16) as i32) as u32,
            LoadKind::Lw => in_,
            LoadKind::Lbu => (in_ >> shift) & 0xFF,
            LoadKind::Lhu => (in_ >> shift) & 0xFFFF,
        };
        let rd = self.write_reg(dinst.rd as u32, out);

        tracing::trace!("  RS1 = {}, value = {:x}", dinst.rs1, rs1.value);
        tracing::trace!("  IMM = {imm:x}");
        tracing::trace!("  RD = {}, value = {:x}", dinst.rd, rd.value);

        trace.add_block(InstLoadWitness {
            mem,
            cycle,
            fetch,
            rs1,
            rs2: rs2 as u32,
            imm,
            options: Opt::OPT_VALUE,
            rd,
        });
        Ok(())
    }

    fn do_inst_store<Opt: InstStoreOptions>(&mut self, trace: &mut Trace) -> Result<()> {
        let kind = Opt::STORE_KIND.unwrap();
        let dinst = trace.get_block_mut(self.dinst.unwrap());
        // Check alignement + access
        let addr = self.peek_reg(dinst.rs1 as u32).wrapping_add(dinst.imm);

        let alignment_req = match kind {
            StoreKind::Sh => 2,
            StoreKind::Sw => 4,
            _ => 1,
        };
        if !addr.is_multiple_of(alignment_req) {
            dinst.count -= 1;
            return self.trap(trace, "Alignement error on store");
        }
        if self.mode != MODE_MACHINE && ((addr / 4) >= KERNEL_START_WORD) {
            dinst.count -= 1;
            return self.trap(trace, "Out of bounds error on store");
        }

        let cycle = self.cur_cycle;
        let fetch = dinst.fetch;
        let (_, rs1) = self.read_reg(dinst.rs1 as u32, false);
        let (data, rs2) = self.read_reg(dinst.rs2 as u32, dinst.rs1 == dinst.rs2);
        let rd = dinst.rd;
        let imm = dinst.imm;

        let shift = BITS_PER_BYTE * (addr % BYTES_PER_WORD);
        let in_ = self.peek_virt_memory(addr / BYTES_PER_WORD)?;
        let out = match kind {
            StoreKind::Sb => (in_ & !(0xFF << shift)) | ((data & 0xFF) << shift),
            StoreKind::Sh => (in_ & !(0xFFFF << shift)) | ((data & 0xFFFF) << shift),
            StoreKind::Sw => data,
        };

        let mem = self.write_virt_memory(addr / BYTES_PER_WORD, out)?;

        tracing::trace!("  RS1 = {}, value = {:x}", dinst.rs1, rs1.value);
        tracing::trace!("  RS2 = {}, value = {:x}", dinst.rs2, rs2.value);
        tracing::trace!("  IMM = {imm:x}");
        tracing::trace!("  MEM addr = {addr:x}, value = {out}");

        trace.add_block(InstStoreWitness {
            cycle,
            fetch,
            rs1,
            rs2,
            rd: rd as u32,
            imm,
            options: Opt::OPT_VALUE,
            mem,
        });

        Ok(())
    }

    fn do_inst_branch<Opt: InstBranchOptions + UnitOptions>(
        &mut self,
        trace: &mut Trace,
    ) -> Result<()> {
        let br = Opt::BR_KIND.unwrap();
        let ok = Opt::OUT_KIND.unwrap();

        let dinst = trace.get_block(self.dinst.unwrap());
        let fetch = dinst.fetch;
        let (rs1_val, rs1) = self.read_reg(dinst.rs1 as u32, false);
        let (rs2_val, rs2) = self.read_reg(dinst.rs2 as u32, dinst.rs1 == dinst.rs2);
        let rd = dinst.rd as u32;
        let imm = dinst.imm;

        let unit_index = self.do_unit::<Opt>(trace, rs1_val, rs2_val);
        let unit = trace.get_block(unit_index);

        let ret = if ok == OutKind::Out0 {
            unit.out0
        } else {
            unit.out1
        };
        let did_branch = if br == BrKind::Z { ret == 0 } else { ret != 0 };
        trace.add_block(InstBranchWitness {
            cycle: self.cur_cycle,
            fetch,
            rs1,
            rs2,
            rd,
            imm,
            options: <Opt as InstBranchOptions>::OPT_VALUE,
            out0: unit.out0,
            out1: unit.out1,
            didBranch: did_branch as u32,
        });
        if did_branch {
            self.new_pc = self.pc.wrapping_add(imm);
        }
        tracing::trace!("  rs1Val = {rs1_val}, rs2Val = {rs2_val}");
        tracing::trace!("  PC = {:x}", self.pc);
        Ok(())
    }

    fn do_inst_jal<Opt: InstJalOptions>(&mut self, trace: &mut Trace) -> Result<()> {
        let dinst = trace.get_block(self.dinst.unwrap());
        let imm = dinst.imm;
        let dinst_rd = dinst.rd as u32;
        let rd = self.write_reg(dinst_rd, self.new_pc);
        trace.add_block(InstJalWitness {
            cycle: self.cur_cycle,
            fetch: dinst.fetch,
            rs1: dinst.rs1 as u32,
            rs2: dinst.rs2 as u32,
            rd,
            imm: dinst.imm,
        });
        self.new_pc = self.pc.wrapping_add(imm);
        tracing::trace!("  RD = {dinst_rd}, value = {:x}", rd.value as u32);
        tracing::trace!("  PC = {:x}", self.pc);
        Ok(())
    }

    fn do_inst_jalr<Opt: InstJalrOptions>(&mut self, trace: &mut Trace) -> Result<()> {
        let dinst = trace.get_block(self.dinst.unwrap());
        let imm = dinst.imm;
        let dinst_rd = dinst.rd as u32;
        let dinst_rs1 = dinst.rs1 as u32;
        let (rs1_val, rs1) = self.read_reg(dinst_rs1, false);
        let rd = self.write_reg(dinst_rd, self.new_pc);
        trace.add_block(InstJalrWitness {
            cycle: self.cur_cycle,
            fetch: dinst.fetch,
            rs1,
            rs2: dinst.rs2 as u32,
            rd,
            imm: dinst.imm,
        });
        self.new_pc = rs1_val.wrapping_add(imm);
        tracing::trace!("  RS1 = {dinst_rs1}, value = {:x}", rs1.value);
        tracing::trace!("  RD = {dinst_rd}, value = {:x}", rd.value);
        tracing::trace!("  PC = {:x}", self.pc);
        Ok(())
    }

    fn do_inst_lui<Opt: InstLuiOptions>(&mut self, trace: &mut Trace) -> Result<()> {
        let dinst = trace.get_block(self.dinst.unwrap());
        trace.add_block(InstLuiWitness {
            cycle: self.cur_cycle,
            fetch: dinst.fetch,
            rs1: dinst.rs1 as u32,
            rs2: dinst.rs2 as u32,
            rd: self.write_reg(dinst.rd as u32, dinst.imm),
        });
        Ok(())
    }

    fn do_inst_auipc<Opt: InstAuipcOptions>(&mut self, trace: &mut Trace) -> Result<()> {
        let dinst = trace.get_block(self.dinst.unwrap());
        trace.add_block(InstAuipcWitness {
            cycle: self.cur_cycle,
            fetch: dinst.fetch,
            rs1: dinst.rs1 as u32,
            rs2: dinst.rs2 as u32,
            rd: self.write_reg(dinst.rd as u32, self.pc.wrapping_add(dinst.imm)),
            imm: dinst.imm,
        });
        Ok(())
    }

    fn do_ecall_terminate(&mut self) {
        todo!("ecall_terminate")
    }

    fn do_ecall_read(&mut self) {
        todo!("ecall_read")
    }

    fn do_ecall_write(&mut self) {
        todo!("ecall_write")
    }

    fn do_ecall_p2(&mut self) {
        todo!("ecall_p2")
    }

    fn do_ecall_big_int(&mut self) {
        todo!("ecall_big_int")
    }

    fn do_inst_ecall<Opt: InstEcallOptions>(&mut self, trace: &mut Trace) -> Result<()> {
        let dinst = trace.get_block(self.dinst.unwrap());

        if self.mode == MODE_USER {
            let cycle = self.cur_cycle;
            let fetch = dinst.fetch;
            let mepc_word = if self.v2_compat {
                V2_COMPAT_MEPC
            } else {
                csr_word(CSR_MEPC)
            };
            let save_pc = self.write_phys_memory(mepc_word, self.pc)?;
            self.set_mode(MODE_MACHINE);
            let mtvec_word = if self.v2_compat {
                V2_COMPAT_ECALL_DISPATCH
            } else {
                csr_word(CSR_MTECALL)
            };
            let (new_pc, dispatch) = self.read_phys_memory(mtvec_word)?;
            self.new_pc = new_pc;
            trace.add_block(InstEcallWitness {
                cycle,
                fetch,
                savePc: save_pc,
                dispatch,
            });

            return Ok(());
        }

        let which = self.peek_reg(REG_A7 as u32);
        match which {
            HOST_ECALL_TERMINATE => self.do_ecall_terminate(),
            HOST_ECALL_READ => self.do_ecall_read(),
            HOST_ECALL_WRITE => self.do_ecall_write(),
            HOST_ECALL_POSEIDON2 => self.do_ecall_p2(),
            HOST_ECALL_BIGINT => self.do_ecall_big_int(),
            _ => {
                tracing::error!("Invalid ECALL in machine mode: {which}");
                bail!("Invalid ECALL in machine mode");
            }
        }
        Ok(())
    }

    fn do_inst_mret<Opt: InstMretOptions>(&mut self, trace: &mut Trace) -> Result<()> {
        let dinst = trace.get_block_mut(self.dinst.unwrap());
        if self.mode != MODE_MACHINE {
            dinst.count -= 1;
            return self.trap(trace, "MRET not in machine mode");
        }

        self.set_mode(MODE_USER);
        let mempc_word = if self.v2_compat {
            V2_COMPAT_MEPC
        } else {
            csr_word(CSR_MEPC)
        };
        let (mut new_pc, read_pc) = self.read_phys_memory(mempc_word)?;
        if self.v2_compat {
            new_pc = new_pc.wrapping_add(4);
        }

        let wit = InstMretWitness {
            cycle: self.cur_cycle,
            fetch: dinst.fetch,
            readPc: read_pc,
        };
        trace.add_block(wit);
        self.new_pc = new_pc;

        Ok(())
    }

    pub fn run(&mut self, trace: &mut Trace, row_count: usize, end_cycle: u32) -> Result<bool> {
        self.do_resume(trace)?;

        while !self.is_done(trace, row_count, end_cycle) {
            let mut decode_wit_index = if self.mode == MODE_MACHINE {
                self.m_inst_cache.get(&self.pc).cloned()
            } else {
                self.us_inst_cache.get(&self.pc).cloned()
            };
            if decode_wit_index.is_none() {
                decode_wit_index = self.fetch_and_decode()?.map(|b| trace.add_block(b));
            }

            let Some(decode_wit_index) = decode_wit_index else {
                self.trap(trace, "Invalid PC or instruction in user mode")?;
                self.cur_cycle += 1;
                self.user_cycles += 1;
                self.pc = self.new_pc;
                continue;
            };

            let decode_wit = trace.get_block_mut(decode_wit_index);
            decode_wit.count += 1;

            self.dinst = Some(decode_wit_index);
            self.new_pc = decode_wit.fetch.nextPc;

            tracing::trace!(
                "cycle: {}, pc: {:x}, inst: {}",
                self.user_cycles,
                self.pc,
                Opcode::from(decode_wit.opcode)
            );

            macro_rules! inst_visitor {
                ($(($name:ident, $idx:expr, $opcode:expr, $imm_type:expr, $func3:expr, $func7:expr,
                    $itype_name:ident $(, $rest:expr)*)),+) => {
                    paste::paste! {
                        use risc0_circuit_rv32im_sys::*;

                        match Opcode::from(decode_wit.opcode) {
                            $(Opcode::$name => {
                                self.[<do_ $itype_name>]::<[<$name Options>]>(trace)?;
                            },)*
                            Opcode::Invalid => self.trap(trace, "Invalid opcode")?,
                        }
                    }
                };
            }

            visit_rv32im_instr!(inst_visitor);

            self.cur_cycle += 1;
            self.user_cycles += 1;
            self.pc = self.new_pc;
        }

        if !self.done {
            self.do_suspend(trace)?;
        }

        trace.globals_mut().finalCycle = self.cur_cycle;
        let cycle_count = (self.cur_cycle * 2).div_ceil(16) * 16;
        for _ in (0..cycle_count).step_by(16) {
            trace.add_block(MakeTableWitness { table: 2, start: 1 });
        }

        trace.set_user_cycles(self.user_cycles);

        Ok(self.done)
    }

    fn add_tables(&self, trace: &mut Trace) {
        for _ in (0..256).step_by(16) {
            trace.add_block(MakeTableWitness { table: 0, start: 1 });
        }

        for _ in (0..65536).step_by(16) {
            trace.add_block(MakeTableWitness { table: 1, start: 1 });
        }
    }

    fn commit(&mut self, trace: &mut Trace) -> Result<()> {
        self.memory.commit(trace, &self.pages)?;
        Ok(())
    }
}

pub fn emulate(
    trace: &mut Trace,
    image: &MemoryImage,
    row_count: usize,
    end_cycle: u32,
) -> Result<bool> {
    let mut emu = Emulator::new(image.clone())?;
    emu.add_tables(trace);

    let done = emu.run(trace, row_count, end_cycle)?;
    tracing::trace!("Cycle = {}", emu.cur_cycle);
    emu.commit(trace)?;

    Ok(done)
}
