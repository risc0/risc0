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

/// Metadata about buffers.
#[derive(Copy, Clone, PartialEq, Eq, Debug)]
pub struct BufferSpec {
    /// Identifying name of this buffer
    pub name: &'static str,

    /// Register group ID in taps and in eval_check "groups" arg.  None if this buffer is not used in taps.
    pub reg_group_id: Option<usize>,

    /// Width of this buffer per row
    pub size: usize,

    /// True if this is a global buffer, false if there's a separate row for each cycle.
    pub global: bool,
}

/// A collection of buffers.  Two types of buffers are available:
/// per-row buffers and global buffers.  This structure is agnostic as
/// to the number and type of buffers.
#[derive(Clone)]
pub struct Buffers<T, G, W> {
    pub rows: Vec<Option<T>>,
    pub globals: Vec<Option<G>>,

    /// A wrapped context.  This structure implements Deref<Target=W>,
    /// so we can easily call any methods defined on the wrapped object.
    pub wrapped: W,
}

impl<T: Clone, G: Clone> Buffers<T, G, ()> {
    pub fn new(rows: &[T], globals: &[G]) -> Self {
        Self {
            rows: rows.iter().cloned().map(Some).collect(),
            globals: globals.iter().cloned().map(Some).collect(),
            wrapped: (),
        }
    }
}

impl<T, G, W> Buffers<T, G, W> {
    pub fn map_rows<NewT>(self, f: impl Fn(T) -> NewT) -> Buffers<NewT, G, W> {
        let f = &f;
        Buffers {
            rows: self.rows.into_iter().map(move |elem| elem.map(f)).collect(),
            globals: self.globals,
            wrapped: self.wrapped,
        }
    }
    pub fn map_globals<NewG>(self, f: impl Fn(G) -> NewG) -> Buffers<T, NewG, W> {
        let f = &f;
        Buffers {
            rows: self.rows,
            globals: self
                .globals
                .into_iter()
                .map(move |elem| elem.map(f))
                .collect(),
            wrapped: self.wrapped,
        }
    }

    pub fn wrap<NewW>(self, wrapped: NewW) -> Buffers<T, G, NewW> {
        Buffers {
            rows: self.rows,
            globals: self.globals,
            wrapped,
        }
    }
}

impl<T, G, W: Copy> Buffers<T, G, W> {
    pub fn as_ref(&self) -> Buffers<&T, &G, W> {
        Buffers {
            rows: self.rows.iter().map(Option::as_ref).collect(),
            globals: self.globals.iter().map(Option::as_ref).collect(),
            wrapped: self.wrapped,
        }
    }
}

impl<T: Clone, G: Clone, W> core::ops::Deref for Buffers<T, G, W> {
    type Target = W;

    fn deref(&self) -> &W {
        &self.wrapped
    }
}
