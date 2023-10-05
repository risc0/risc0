// Copyright 2023 RISC Zero, Inc.
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

//! Manages formatted binaries used by the RISC Zero zkVM

#![cfg_attr(all(not(feature = "std"), not(test)), no_std)]

mod elf;
mod image;
mod sys_state;

pub use crate::{
    elf::Program,
    image::{compute_image_id, MemoryImage, PageTableInfo},
    sys_state::{read_sha_halfs, tagged_struct, write_sha_halfs, SystemState},
};
