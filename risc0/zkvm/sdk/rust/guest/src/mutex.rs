// zkvm is a single threaded environment, so mutexes aren't necessary.
// However, rust doesn't understand this so this is a fake mutex that
// just wraps a RefCell.
//
// The API is roughly compatible with std::sync::Mutex.

use core::cell::{RefCell, RefMut};
use core::result::Result;

pub struct Mutex<T>(RefCell<T>);

unsafe impl<T> Sync for Mutex<T> {}

impl<T> Mutex<T> {
    pub const fn new(val: T) -> Self {
        Self(RefCell::new(val))
    }

    pub fn lock(&self) -> LockResult<RefMut<'_, T>> {
        LockResult::Ok(self.0.borrow_mut())
    }
}

pub type LockResult<Guard> = Result<Guard, ()>;
