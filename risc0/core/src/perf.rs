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

//! Utilities for gathering performance data.

use core::fmt::Display;

pub use puffin;
pub use tracing;

#[doc(hidden)]
pub struct NvtxRange;

impl NvtxRange {
    #[doc(hidden)]
    #[inline]
    #[must_use]
    pub fn new<M: Display>(msg: M) -> Self {
        nvtx::__private::_range_push(msg);
        Self
    }
}

impl Drop for NvtxRange {
    #[inline]
    fn drop(&mut self) {
        nvtx::__private::_range_pop();
    }
}

/// Opens a scope.
#[macro_export]
macro_rules! scope {
    ($name:expr) => {
        let _nvtx = $crate::perf::NvtxRange::new($name);
        $crate::perf::puffin::profile_scope!($name);
        let _span = $crate::perf::tracing::info_span!($name);
        let _span_entered = _span.enter();
    };

    ($name:expr, $body:block) => {
        $crate::perf::tracing::info_span!($name).in_scope(|| {
            let _nvtx = $crate::perf::NvtxRange::new($name);
            $crate::perf::puffin::profile_scope!($name);
            $body
        })
    };

    ($name:expr, $body:expr) => {
        $crate::perf::tracing::info_span!($name).in_scope(|| {
            let _nvtx = $crate::perf::NvtxRange::new($name);
            $crate::perf::puffin::profile_scope!($name);
            $body
        })
    };
}

/// Opens a scope.
#[macro_export]
macro_rules! scope_with {
    ($name:expr, $data:expr) => {
        let _nvtx = $crate::perf::NvtxRange::new(::core::format_args!($name, $data));
        $crate::perf::puffin::profile_scope!($name, $data);
        let _span = $crate::perf::tracing::info_span!($name, tag = $data);
        let _span_entered = _span.enter();
    };

    ($name:expr, $data:expr, $body:block) => {
        $crate::perf::tracing::info_span!($name, tag = $data).in_scope(|| {
            let _nvtx = $crate::perf::NvtxRange::new(::core::format_args!($name, $data));
            $crate::perf::puffin::profile_scope!($name, $data);
            $body
        })
    };

    ($name:expr, $data:expr, $body:expr) => {
        $crate::perf::tracing::info_span!($name, tag = $data).in_scope(|| {
            let _nvtx = $crate::perf::NvtxRange::new(::core::format_args!($name, $data));
            $crate::perf::puffin::profile_scope!($name, $data);
            $body
        })
    };
}
