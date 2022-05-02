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

use crate::alloc::BumpPointerAlloc;
use crate::gpio::SHADescriptor;

const REGION_SIZE_256KB: usize = 256 * 1024;
// const REGION_SIZE_512KB: usize = 0x0008_0000;
const REGION_SIZE_1MB: usize = 1024 * 1024;

pub(crate) const REGION_HEAP_START: usize = 0x0008_0000;
pub(crate) const REGION_HEAP_LEN: usize = REGION_SIZE_1MB + REGION_SIZE_256KB;
pub(crate) const REGION_HEAP_END: usize = REGION_HEAP_START + REGION_HEAP_LEN;

pub(crate) const REGION_SHA_START: usize = 0x0030_0000;
pub(crate) const REGION_SHA_LEN: usize = REGION_SIZE_256KB;
pub(crate) const REGION_SHA_END: usize = REGION_SHA_START + REGION_SHA_LEN;

pub(crate) const REGION_INPUT_START: usize = 0x0018_0000;
pub(crate) const REGION_INPUT_LEN: usize = REGION_SIZE_256KB;
pub(crate) const REGION_INPUT_END: usize = REGION_INPUT_START + REGION_INPUT_LEN;

pub(crate) const REGION_OUTPUT_START: usize = 0x0034_0000;
pub(crate) const REGION_OUTPUT_LEN: usize = REGION_SIZE_256KB;
pub(crate) const REGION_OUTPUT_END: usize = REGION_OUTPUT_START + REGION_OUTPUT_LEN;

pub(crate) const REGION_COMMIT_START: usize = 0x0038_0000;
pub(crate) const REGION_COMMIT_LEN: usize = REGION_SIZE_256KB;
pub(crate) const REGION_COMMIT_END: usize = REGION_COMMIT_START + REGION_COMMIT_LEN;

pub(crate) static OUTPUT_ZONE: BumpPointerAlloc<u32> =
    BumpPointerAlloc::new("Output", REGION_OUTPUT_START, REGION_OUTPUT_END);

pub(crate) static COMMIT_ZONE: BumpPointerAlloc<u32> =
    BumpPointerAlloc::new("Commit", REGION_COMMIT_START, REGION_COMMIT_END);

pub(crate) static SHA_DESC_ZONE: BumpPointerAlloc<SHADescriptor> =
    BumpPointerAlloc::new("SHA", REGION_SHA_START, REGION_SHA_END);
