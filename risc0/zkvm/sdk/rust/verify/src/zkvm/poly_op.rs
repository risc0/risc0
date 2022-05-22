// Copyright 2022 Risc0, Inc.
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

use risc0_zkp_core::fp::Fp;

pub enum PolyOp {
    Const {
        out: usize,
        val: Fp,
    },
    Get {
        out: usize,
        idx: usize,
    },
    GetGlobal {
        out: usize,
        idx: usize,
    },
    Begin {
        out: usize,
    },
    AssertZero {
        out: usize,
        orig: usize,
        val: usize,
    },
    Combine {
        out: usize,
        orig: usize,
        cond: usize,
        inner: usize,
    },
    Add {
        out: usize,
        a: usize,
        b: usize,
    },
    Sub {
        out: usize,
        a: usize,
        b: usize,
    },
    Mul {
        out: usize,
        a: usize,
        b: usize,
    },
    Result {
        val: usize,
    },
}
