use _alloc::{alloc::alloc, boxed::Box};
use core::{alloc::Layout, mem, ptr::null_mut};

use crate::{
    gpio::{IoDescriptor, GPIO_DESC_IO, GPIO_LOG, GPIO_READ, GPIO_WRITE},
    sha::{self, Digest, SHA256},
};

struct Env {
    message: SHA256,
}

static mut ENV: *mut Env = null_mut();

fn env() -> &'static Env {
    unsafe { &*ENV }
}

fn env_mut() -> &'static mut Env {
    unsafe { &mut *ENV }
}

pub(crate) fn init() {
    let mut env = Env::new();
    unsafe { ENV = &mut env };
}

pub(crate) fn finalize(result: *mut usize) {
    env_mut().finalize(result);
}

pub fn read<T>() -> T {
    env().read()
}

pub fn write<T>(data: &T) {
    env().write(data);
}

pub fn commit<T>(data: &T) {
    env_mut().commit(data);
}

pub fn commit_digest(data: &Box<Digest>) {
    env_mut().commit_digest(data);
}

pub fn read_slice<T>() -> &'static [T] {
    env().read_slice()
}

pub fn write_slice<T>(slice: &[T]) {
    env().write_slice(slice);
}

pub fn log(msg: &str) {
    unsafe {
        GPIO_DESC_IO.write_volatile(IoDescriptor {
            size: msg.len(),
            addr: msg.as_ptr() as usize,
        });
        GPIO_LOG.write_volatile(GPIO_DESC_IO);
    }
}

impl Env {
    fn new() -> Self {
        Env {
            message: SHA256::with_capacity(256 * 1024),
        }
    }

    fn read<T>(&self) -> T {
        let layout = Layout::new::<T>();
        unsafe {
            let buf = alloc(layout);
            GPIO_DESC_IO.write_volatile(IoDescriptor {
                size: layout.size(),
                addr: buf as usize,
            });
            GPIO_READ.write_volatile(GPIO_DESC_IO);
            let ptr: *const T = buf.cast();
            ptr.read_volatile()
        }
    }

    fn write<T>(&self, data: &T) {
        let ptr: *const T = data;
        unsafe {
            GPIO_DESC_IO.write_volatile(IoDescriptor {
                size: mem::size_of::<T>(),
                addr: ptr as usize,
            });
            GPIO_WRITE.write_volatile(GPIO_DESC_IO);
        }
    }

    fn commit<T>(&mut self, data: &T) {
        self.write(data);
        self.message.update(data);
    }

    fn read_slice<T>(&self) -> &[T] {
        let size: usize = self.read();
        unsafe {
            let layout = Layout::from_size_align_unchecked(size, mem::align_of::<u8>());
            let buf = alloc(layout);
            GPIO_DESC_IO.write_volatile(IoDescriptor {
                size,
                addr: buf as usize,
            });
            GPIO_READ.write_volatile(GPIO_DESC_IO);
            core::slice::from_raw_parts(buf.cast(), size / mem::size_of::<T>())
        }
    }

    fn write_slice<T>(&self, slice: &[T]) {
        unsafe {
            GPIO_DESC_IO.write_volatile(IoDescriptor {
                size: slice.len() * mem::size_of::<T>(),
                addr: slice.as_ptr() as usize,
            });
            GPIO_WRITE.write_volatile(GPIO_DESC_IO);
        }
    }

    fn commit_digest(&mut self, digest: &Box<Digest>) {
        self.write_slice(&digest.words);
        self.message.update_slice(&digest.words);
    }

    fn finalize(&mut self, result: *mut usize) {
        let (slice_ptr, len_bytes) = {
            let slice = self.message.storage.as_slice();
            // Write the full data out to the host
            self.write_slice(slice);
            (slice.as_ptr(), slice.len())
        };

        // If the total proof message is small (<= 32 bytes), return it directly
        // from the proof, otherwise SHA it and return the hash.
        if len_bytes <= 32 {
            let ptr = result as *mut u8;
            unsafe { ptr.copy_from_nonoverlapping(slice_ptr, len_bytes) };
        } else {
            let digest = self.message.finalize();
            let src = digest.words.as_ptr();
            let len = digest.words.len();
            unsafe { result.copy_from_nonoverlapping(src, len) };
        }
        unsafe { result.add(8).write_volatile(len_bytes) };
        sha::finalize();
    }
}
