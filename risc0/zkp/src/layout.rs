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

//! Utilities for accessing buffers of circuits symbolically.

use alloc::{collections::BTreeMap, string::String, vec::Vec};
#[cfg(not(feature = "std"))]
use alloc::{format, string::ToString};
use core::fmt::{Debug, Formatter, Write};

use anyhow::Result;
pub use paste::paste;

#[macro_export]
/// Defines a buffer in a circuit that could have layout information.  $ident
/// should be the camelcase name of the buffer, and $elem should be the type of
/// element in the buffer, e.g. BabyBearElem.  $elem must implement Debug, and
/// must be comparable to $elem::ZERO.
macro_rules! layout_buffer {
    ($ident:ident, $elem:ty) => {
        $crate::layout::paste! {
            pub struct [<$ident:camel Reg>] {
                pub offset: usize,
            }

            impl core::convert::From<usize> for [<$ident:camel Reg>] {
                fn from(offset: usize) -> Self { Self{offset} }
            }

           impl $crate::layout::Component for [<$ident:camel Reg>] {
               fn walk<V: $crate::layout::Visitor>(&self, v: &mut V) -> core::fmt::Result {
                   v.visit_reg(stringify!($ident), self.offset)
               }
               fn ty_name(&self) -> &'static str { "reg" }
           }

            #[derive(Clone, Copy)]
            pub struct [<$ident:camel Buffer>]<'a> (
                pub &'a[$elem],
           );

           impl<'a> core::convert::From<&'a [$elem]> for [<$ident:camel Buffer>]<'a> {
               fn from(buf: &'a [$elem]) -> Self {
                   Self(buf)
               }
           }

           impl<'a> $crate::layout::Buffer for [<$ident:camel Buffer>]<'a> {
               type Reg = [<$ident:camel Reg>];
               type Elem = $elem;

               fn tree<'b, C: $crate::layout::Component>(&'b self, component: &'b C) -> $crate::layout::Tree<Self, C> {
                   $crate::layout::Tree{buf: self, component}
               }

               fn name(&self) -> &'static str {
                   stringify!($ident)
               }

               fn get(&self, reg: &Self::Reg) -> core::option::Option<&$elem> {
                   if reg.offset > self.0.len() {
                       None
                   } else {
                       let val = &self.0[reg.offset];
                       if *val == $elem::ZERO {
                           None
                       } else {
                           Some(val)
                       }
                   }
               }

               fn get_u64(&self, reg: &Self::Reg) -> u64 {
                   u64::from(self.0[reg.offset])
               }
           }
        }};
}

/// A circuit execution trace buffer, which we can read laid out components
/// from.
pub trait Buffer: Sized {
    /// The type of element stored in this buffer.
    type Elem: Debug;

    /// A register in this buffer, convertable from an offset.
    type Reg: From<usize>;

    /// Returns the component tree rooted at the given component.
    fn tree<'a, C: Component>(&'a self, component: &'a C) -> Tree<'a, Self, C>;

    /// Returns the argument name of this buffer.
    fn name(&self) -> &'static str;

    /// Retrieve an element from this buffer.
    fn get(&self, reg: &Self::Reg) -> Option<&Self::Elem>;

    /// Retrieve an element from this buffer and convert it to a u64
    fn get_u64(&self, reg: &Self::Reg) -> u64;

    /// Retrieve an element from this buffer and convert it to a u32
    fn get_u32(&self, reg: &Self::Reg) -> u32 {
        self.get_u64(reg) as u32
    }
}

/// A component within a circuit execution trace buffer.  Users should
/// not use this directly; it is only "pub" so it can be used by the
/// layout_buffer macro.
#[doc(hidden)]
pub trait Component {
    fn walk<V: Visitor>(&self, v: &mut V) -> core::fmt::Result;
    fn ty_name(&self) -> &'static str {
        "array"
    }
}

impl<C: Component, const N: usize> Component for [&C; N] {
    fn walk<V: Visitor>(&self, v: &mut V) -> core::fmt::Result {
        for (n, elem) in self.iter().enumerate() {
            let name = alloc::format!("[{n}]");
            v.visit_component(&name, *elem)?;
        }
        Ok(())
    }
}

/// A visitor that visits components in a component tree.  Users
/// should not use this directly; it is only "pub" so it can be used
/// by the layout_buffer macro.
#[doc(hidden)]
pub trait Visitor {
    fn visit_component(&mut self, name: &str, component: &impl Component) -> core::fmt::Result;
    fn visit_reg(&mut self, buf_name: &'static str, offset: usize) -> core::fmt::Result;
}

/// Represents the section of a component tree that's present in a buffer.
pub struct Tree<'a, B: Buffer, C: Component> {
    // Fields only marked "pub" so they can be used by the layout_buffer! macro.
    #[doc(hidden)]
    pub buf: &'a B,
    #[doc(hidden)]
    pub component: &'a C,
}

impl<'a, B: Buffer, C: Component> Tree<'a, B, C> {
    /// Interprets the contents of this tree as a list of u64s.
    pub fn get_u64s(&self) -> Result<Vec<u64>> {
        let mut gather = TreeGather::new(self.buf);
        self.component
            .walk(&mut gather)
            .map_err(anyhow::Error::msg)?;
        Ok(gather.vals)
    }

    /// Interprets the contents of this tree as a list of bytes.
    pub fn get_bytes(&self) -> Result<Vec<u8>> {
        self.get_u64s()?
            .into_iter()
            .map(|val| u8::try_from(val).map_err(anyhow::Error::msg))
            .collect()
    }

    /// Returns the contents of this tree as a u32; elements are expected to be
    /// 4 bytes.
    pub fn get_u32(&self) -> Result<u32> {
        Ok(u32::from_le_bytes(
            self.get_bytes()?
                .as_slice()
                .try_into()
                .map_err(anyhow::Error::msg)?,
        ))
    }
}

impl<'a, B: Buffer, C: Component> Debug for Tree<'a, B, C> {
    fn fmt(&self, f: &mut Formatter<'_>) -> core::fmt::Result {
        let mut p = TreePrinter::new(self.buf, Vec::new(), "top");
        self.component.walk(&mut p)?;
        for line in p.lines {
            writeln!(f, "{line}")?;
        }
        Ok(())
    }
}

// Collects a tree dump as a set of lines.  Lists identical sections as a
// reference to the first one seen.
struct TreePrinter<'a, B: Buffer> {
    buf: &'a B,
    lines: Vec<String>,
    item_count: usize,
    seen: BTreeMap<Vec<String>, String>,
    path: Vec<&'a str>,
}

impl<'a, B: Buffer> TreePrinter<'a, B> {
    fn new(buf: &'a B, mut path: Vec<&'a str>, name: &'a str) -> Self {
        path.push(name);
        TreePrinter {
            buf,
            lines: Vec::new(),
            item_count: 0,
            seen: BTreeMap::new(),
            path,
        }
    }
}

impl<'a, B: Buffer> Visitor for TreePrinter<'a, B> {
    fn visit_component(&mut self, name: &str, component: &impl Component) -> core::fmt::Result {
        match component.ty_name() {
            "U32Reg" => {
                // U32regs print as hexadecimal.
                let mut subtree = TreeGather::new(self.buf);
                component.walk(&mut subtree)?;
                if subtree.vals.iter().any(|&x| x != 0) {
                    let mut msg = format!("{name}: ");
                    write!(msg, " 0x")?;
                    for val in subtree.vals {
                        if val > 255 {
                            // Unexpected non-byte in u32reg
                            write!(msg, "[{:#x}?]", val)?;
                        } else {
                            write!(msg, "{:02x}", val)?;
                        }
                    }
                    self.lines.push(msg);
                    self.item_count += 1;
                }
            }
            _ => {
                // Generic subtree
                let mut subtree = TreePrinter::new(self.buf, self.path.clone(), name);
                component.walk(&mut subtree)?;
                match subtree.item_count {
                    0 => {}
                    1 => {
                        // Single item inside; build up path on a
                        // single line to save vertical space for
                        // structures like a{b{c{x: y}}}.
                        self.item_count += 1;
                        let mut lines = subtree.lines;
                        lines[0] = format!("{name}: {{{}", lines[0]);
                        lines.last_mut().as_mut().unwrap().push_str(" }");
                        self.lines.extend(lines);
                    }
                    _ => {
                        // Multi-line structure; if we've seen this before, just emit a reference.
                        // Otherwise, save it.
                        self.item_count += 1;
                        match self.seen.get(&subtree.lines) {
                            Some(path) => {
                                self.lines.push(format!("{name}: duplicate of {path}"));
                            }
                            None => {
                                self.seen.extend(subtree.seen);
                                self.lines.push(format!("{name}: {{"));
                                self.lines
                                    .extend(subtree.lines.iter().map(|s| format!("  {s}")));
                                self.lines.push("}".to_string());
                                self.seen.insert(subtree.lines, subtree.path.join("."));
                            }
                        }
                    }
                }
            }
        }
        Ok(())
    }

    fn visit_reg(&mut self, buf_name: &'static str, offset: usize) -> core::fmt::Result {
        if buf_name == self.buf.name() {
            if let Some(val) = self.buf.get(&B::Reg::from(offset)) {
                self.lines.push(format!("{:?}", val));
                self.item_count += 1;
            }
        }
        Ok(())
    }
}

// Gathers all the registers in a tree as u64s.
struct TreeGather<'a, B: Buffer> {
    buf: &'a B,
    vals: Vec<u64>,
}

impl<'a, B: Buffer> TreeGather<'a, B> {
    fn new(buf: &'a B) -> Self {
        Self {
            buf,
            vals: Vec::new(),
        }
    }
}

impl<'a, B: Buffer> Visitor for TreeGather<'a, B> {
    fn visit_component(&mut self, _name: &str, component: &impl Component) -> core::fmt::Result {
        component.walk(self)
    }
    fn visit_reg(&mut self, buf_name: &'static str, offset: usize) -> core::fmt::Result {
        if buf_name == self.buf.name() {
            self.vals.push(self.buf.get_u64(&B::Reg::from(offset)))
        }
        Ok(())
    }
}
