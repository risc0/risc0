// Copyright 2024 RISC Zero, Inc.
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

#[macro_use]
pub mod codegen;

mod buffers;
pub use buffers::{BufferSpec, Buffers};
use risc0_core::{field::Elem, field::ExtElem};
use risc0_zkp::{hal::cpu::SyncSlice, layout::Reg};

/// This trait represents the set of registers available for a
/// specific cycle.  For instance, this can either be a row in the
/// execution trace or a set of global registers that are common to
/// all cycles.
pub trait BufferRow: Clone {
    type ValType: Clone + Copy + Default;

    fn load(&self, ctx: &impl CycleContext, offset: usize, back: usize) -> Self::ValType;
    fn store(&self, ctx: &impl CycleContext, offset: usize, val: Self::ValType);
}

pub trait CycleContext {
    fn cycle(&self) -> usize;
    fn tot_cycles(&self) -> usize;

    fn offset_this_cycle(&self, offset: usize, back: usize) -> usize {
        let tot_cycles = self.tot_cycles();
        let cycle = (self.cycle() + tot_cycles - back) % tot_cycles;
        offset * tot_cycles + cycle
    }
}

#[derive(Clone)]
pub struct GlobalRow<'a, E: Default + Clone + Copy> {
    pub buf: &'a SyncSlice<'a, E>,
}

impl<'a, E: Copy + Clone + Default + Elem> BufferRow for GlobalRow<'a, E> {
    type ValType = E;

    fn load(&self, _ctx: &impl CycleContext, offset: usize, back: usize) -> E {
        assert_eq!(back, 0);
        let val = self.buf.get(offset);
        tracing::trace!("Load {val:?} from global offset {offset}");
        debug_assert!(val.is_valid(), "Global offset {offset}");
        val
    }
    fn store(&self, _ctx: &impl CycleContext, offset: usize, val: E) {
        if cfg!(debug_assertions) {
            let old_val = self.buf.get(offset);
            assert!(
                !old_val.is_valid() || old_val == val,
                "Global offset {offset}, Old value: {old_val:?}, New value: {val:?}"
            );
        }
        tracing::trace!("Store {val:?} to global offset {offset}");
        self.buf.set(offset, val)
    }
}

#[derive(Clone)]
pub struct CycleRow<'a, E: Default + Clone + Copy> {
    pub buf: &'a SyncSlice<'a, E>,
}

impl<'a, E: Copy + Clone + Default + Elem> BufferRow for CycleRow<'a, E> {
    type ValType = E;

    fn load(&self, ctx: &impl CycleContext, offset: usize, back: usize) -> E {
        let adj_offset = ctx.offset_this_cycle(offset, back);
        let val = self.buf.get(adj_offset);
        tracing::trace!("Load {val:?} from offset {offset} back {back}");
        val
    }
    fn store(&self, ctx: &impl CycleContext, offset: usize, val: E) {
        if cfg!(debug_assertions) {
            let old_val = self.buf.get(ctx.offset_this_cycle(offset, 0));
            assert!(
                !old_val.is_valid() || old_val == val,
                "Old value: {old_val:?}, New value: {val:?}, offset: {offset}"
            );
        }
        tracing::trace!("Store {val:?} to offset {offset}");
        self.buf.set(ctx.offset_this_cycle(offset, 0), val)
    }
}

/// This represents a layout bound to a buffer.
#[derive(Clone, Copy)]
pub struct BoundLayout<'a, L: 'static, B: BufferRow> {
    pub layout: &'static L,
    pub buf: &'a B,
}

impl<'a, L: PartialEq, B: BufferRow> PartialEq for BoundLayout<'a, L, B> {
    fn eq(&self, other: &BoundLayout<L, B>) -> bool {
        // We only need to compare the layout values
        self.layout == other.layout
    }
}

impl<'a, L, B: BufferRow> BoundLayout<'a, L, B> {
    pub fn new(layout: &'static L, buf: &'a B) -> Self {
        Self { layout, buf }
    }
    pub fn map<NewL, F: FnOnce(&'static L) -> &'static NewL>(
        &self,
        f: F,
    ) -> BoundLayout<'a, NewL, B> {
        BoundLayout {
            layout: f(self.layout),
            buf: self.buf,
        }
    }

    pub fn layout(&self) -> &'static L {
        self.layout
    }
    pub fn buf(&self) -> &B {
        &self.buf
    }
}

impl<'a, B: BufferRow> BoundLayout<'a, Reg, B>
where
    B::ValType: Elem,
{
    pub fn load_ext<E: ExtElem<SubElem = B::ValType>>(
        &self,
        ctx: &impl CycleContext,
        back: usize,
    ) -> E {
        let subelems =
            (0..E::EXT_SIZE).map(|idx| self.buf.load(ctx, self.layout.offset + idx, back));

        if subelems.clone().any(|elem: E::SubElem| !elem.is_valid()) {
            E::INVALID
        } else {
            E::from_subelems(subelems)
        }
    }
    pub fn load_unchecked_ext<E: ExtElem<SubElem = B::ValType>>(
        &self,
        ctx: &impl CycleContext,
        back: usize,
    ) -> E {
        self.load_ext::<E>(ctx, back).valid_or_zero()
    }
    pub fn store_ext<E: ExtElem<SubElem = B::ValType>>(&self, ctx: &impl CycleContext, val: E) {
        for (idx, elem) in val.subelems().into_iter().enumerate() {
            self.buf.store(ctx, self.layout.offset + idx, *elem)
        }
    }
}

impl<'a, E: Elem, B: BufferRow<ValType = E>> BoundLayout<'a, Reg, B> {
    pub fn load(&self, ctx: &impl CycleContext, back: usize) -> E {
        self.buf.load(ctx, self.layout.offset, back)
    }
    pub fn load_unchecked(&self, ctx: &impl CycleContext, back: usize) -> E {
        self.load(ctx, back).valid_or_zero()
    }
    pub fn store(&self, ctx: &impl CycleContext, val: E) {
        self.buf.store(ctx, self.layout.offset, val);
    }
}
