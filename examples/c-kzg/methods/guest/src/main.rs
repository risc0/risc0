// Copyright 2025 RISC Zero, Inc.
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
use c_kzg::{Bytes32, Bytes48, KzgCommitment, KzgProof, KzgSettings};
use c_kzg_core::Proof;
use risc0_zkvm::guest::env;
use sha2::{Digest as _, Sha256};
use std::alloc::{alloc, handle_alloc_error};
use std::{alloc::Layout, ffi::c_void};

pub const VERSIONED_HASH_VERSION_KZG: u8 = 0x01;

pub fn kzg_to_versioned_hash(commitment: &KzgCommitment) -> [u8; 32] {
    let mut res = Sha256::digest(commitment.as_slice());
    res[0] = VERSIONED_HASH_VERSION_KZG;
    res.into()
}

#[unsafe(no_mangle)]
// TODO ideally this is c_size_t, but not stabilized (not guaranteed to be usize on all archs)
unsafe extern "C" fn malloc(size: usize) -> *mut c_void {
    let layout = Layout::from_size_align(size, 4).expect("unable to allocate more memory");
    let ptr = unsafe { alloc(layout) };

    if ptr.is_null() {
        handle_alloc_error(layout);
    }

    ptr as *mut c_void
}

#[unsafe(no_mangle)]
// TODO shouldn't need to zero allocated bytes since the zkvm memory is zeroed, might want to zero anyway
unsafe extern "C" fn calloc(nobj: usize, size: usize) -> *mut c_void {
    unsafe { malloc(nobj * size) }
}

#[unsafe(no_mangle)]
unsafe extern "C" fn free(_size: *const c_void) {
    // Intentionally a no-op, since the zkvm allocator is a bump allocator
}

const KZG_DATA: &[u8] = include_bytes!(env!("KZG_FILE_PATH"));

fn main() {
    let proof: Proof = env::read();
    println!("size: {}", KZG_DATA.len());
    let mut data = Vec::from(KZG_DATA);
    let kzg_settings = KzgSettings::from_u8_slice(&mut data);
    println!("kzg_settings: {:?}", kzg_settings);
    let input = [0; 4096 * 32];
    let before_cycle = env::cycle_count();
    let kzg_commit = KzgCommitment::blob_to_kzg_commitment(&input.into(), &kzg_settings).unwrap();
    let after_cycle = env::cycle_count();
    println!(
        "KzgCommitment::blob_to_kzg_commitment took roughly {} cycles",
        after_cycle - before_cycle
    );
    let _versioned_hash = kzg_to_versioned_hash(&kzg_commit);
    let before_cycle = env::cycle_count();
    KzgProof::verify_kzg_proof(
        &Bytes48::from_bytes(&proof.commitment).unwrap(),
        &Bytes32::from_bytes(&proof.z).unwrap(),
        &Bytes32::from_bytes(&proof.y).unwrap(),
        &Bytes48::from_bytes(&proof.proof).unwrap(),
        &kzg_settings,
    )
    .unwrap();
    let after_cycle = env::cycle_count();
    println!(
        "KzgProof::verify_kzg_proof took roughly {} cycles",
        after_cycle - before_cycle
    );
}
