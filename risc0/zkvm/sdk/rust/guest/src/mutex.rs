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

use core::cell::{RefCell, RefMut};
use core::result::Result;

// zkvm is a single threaded environment, so mutexes aren't necessary.
// However, rust is unaware of this, so we provide a fake mutex that
// just wraps a RefCell without doing any fancy locking or unlocking.
//
// The API is meant to be roughly compatible with std::sync::Mutex to
// ease in porting.
pub struct Mutex<T>(RefCell<T>);

unsafe impl<T> Sync for Mutex<T> {}

type LockResult<Guard> = Result<Guard, ()>;

pub type MutexGuard<'a, T> = RefMut<'a, T>;

impl<T> Mutex<T> {
    pub const fn new(val: T) -> Self {
        Self(RefCell::new(val))
    }

    pub fn lock(&self) -> LockResult<MutexGuard<'_, T>> {
        LockResult::Ok(self.0.borrow_mut())
    }
}
