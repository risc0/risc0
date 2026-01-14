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

//! This crate contains a type which a compile-time encoding of a set of enum variants.
//! It is a mirror of the code found in risc0/circuit/rv32im-sys/cxx/rv32im/base/opt.h

use num_enum::{IntoPrimitive, TryFromPrimitive};
use strum::EnumCount;

include!(concat!(env!("OUT_DIR"), "/preflight_opt_gen.rs"));

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum InstKind {
    Reg,
    Imm,
    Load,
    Store,
    Branch,
    Jal,
    Jalr,
    Lui,
    Auipc,
    Ecall,
    Mret,
}

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum UnitKind {
    Addsub,
    Bit,
    Lt,
    Mul,
    Div,
    Shift,
}

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum OutKind {
    Out0,
    Out1,
}

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum AsKind {
    Add,
    Sub,
}

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum BrKind {
    Z,
    Nz,
}

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum LoadKind {
    Lb,
    Lh,
    Lw,
    Lbu,
    Lhu,
}

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum StoreKind {
    Sb,
    Sh,
    Sw,
}

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum BitKind {
    Xor,
    Or,
    And,
}

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum MulKind {
    Ss,
    Su,
    Uu,
}

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum DivKind {
    U,
    S,
}

#[derive(Copy, Clone, PartialEq, Eq, Debug, EnumCount, IntoPrimitive, TryFromPrimitive)]
#[repr(u32)]
pub enum ShiftKind {
    Ll,
    Rl,
    Ra,
}

pub trait UnitOptions {
    const UNIT_KIND: Option<UnitKind> = None;
    const AS_KIND: Option<AsKind> = None;
    const BIT_KIND: Option<BitKind> = None;
    const MUL_KIND: Option<MulKind> = None;
    const DIV_KIND: Option<DivKind> = None;
    const SHIFT_KIND: Option<ShiftKind> = None;

    const OPT_VALUE: u32;
}

pub struct MulUuOptions;

impl UnitOptions for MulUuOptions {
    const UNIT_KIND: Option<UnitKind> = Some(UnitKind::Mul);
    const MUL_KIND: Option<MulKind> = Some(MulKind::Uu);
    const OPT_VALUE: u32 = opt![UnitKind::Mul, MulKind::Uu].val();
}

pub struct DivUOptions;

impl UnitOptions for DivUOptions {
    const UNIT_KIND: Option<UnitKind> = Some(UnitKind::Div);
    const DIV_KIND: Option<DivKind> = Some(DivKind::U);
    const OPT_VALUE: u32 = opt![UnitKind::Div, DivKind::U].val();
}

pub trait OptValue: Copy + Into<u32> + TryFrom<u32> + EnumCount {
    const VALUE: u32 = <Self as EnumCount>::COUNT as u32;

    fn as_u32(&self) -> u32 {
        (*self).into()
    }

    fn from_u32(v: u32) -> Option<Self> {
        Self::try_from(v).ok()
    }
}

impl<T: Copy + Into<u32> + TryFrom<u32> + EnumCount> OptValue for T {}

#[derive(Default)]
pub struct Opt(u32);

impl Opt {
    pub const fn from_u32(v: u32) -> Self {
        Self(v)
    }

    pub const fn val(&self) -> u32 {
        self.0
    }

    pub fn peek<T: OptValue>(&self) -> T {
        T::from_u32(self.0 % T::VALUE).expect("invalid encoding")
    }

    pub fn pop<T: OptValue>(&mut self) -> T {
        let ret = self.peek::<T>();
        self.0 /= T::VALUE;
        ret
    }

    pub const fn pop_ret<T: OptValue>(&self) -> Self {
        Self(self.0 / T::VALUE)
    }

    pub fn push<T: OptValue>(&mut self, t: T) {
        self.0 *= T::VALUE;
        self.0 += t.as_u32();
    }

    pub const fn _push_const<T: OptValue>(&mut self, _t: T, v: u32) {
        self.0 *= T::VALUE;
        self.0 += v;
    }
}

#[macro_export]
macro_rules! opt {
    [] => {
        $crate::prove::preflight::opt::Opt::from_u32(0)
    };

    [$e:expr] => {
        $crate::prove::preflight::opt::Opt::from_u32($e as u32)
    };

    [$e:expr, $($es:expr),+] => {{
        let mut o = $crate::prove::preflight::opt::opt![$($es),+];
        let e = $e;
        o._push_const(e, e as u32);
        o
    }};
}

pub use opt;

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn push_peek_and_pop() {
        let mut opt = Opt::default();
        opt.push(InstKind::Reg);
        opt.push(UnitKind::Addsub);

        assert_eq!(opt.peek::<UnitKind>(), UnitKind::Addsub);
        assert_eq!(opt.pop::<UnitKind>(), UnitKind::Addsub);

        assert_eq!(opt.peek::<InstKind>(), InstKind::Reg);
    }

    #[test]
    fn const_create_and_pop_ret() {
        const O: Opt = opt![InstKind::Reg, UnitKind::Addsub];
        const O1: Opt = O.pop_ret::<UnitKind>();

        assert_eq!(O.peek::<UnitKind>(), UnitKind::Addsub);
        assert_eq!(O1.peek::<InstKind>(), InstKind::Reg);
    }
}
