// Copyright Supranational LLC
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

#![allow(unexpected_cfgs)]

// Declare C/C++ counterpart as following:
// extern "C" { fn foobar(...) -> sppark::Error; }
#[repr(C)]
pub struct Error {
    pub code: i32,
    str: Option<core::ptr::NonNull<i8>>, // just strdup("string") from C/C++
}

impl Drop for Error {
    fn drop(&mut self) {
        extern "C" {
            fn free(str: Option<core::ptr::NonNull<i8>>);
        }
        unsafe { free(self.str) };
        self.str = None;
    }
}

impl From<&Error> for String {
    fn from(status: &Error) -> Self {
        if let Some(str) = status.str {
            let c_str = unsafe { std::ffi::CStr::from_ptr(str.as_ptr() as *const _) };
            String::from(c_str.to_str().unwrap_or("unintelligible"))
        } else {
            format!("sppark::Error #{}", status.code)
        }
    }
}

impl From<Error> for String {
    fn from(status: Error) -> Self {
        String::from(&status)
    }
}

impl std::fmt::Display for Error {
    fn fmt(&self, f: &mut std::fmt::Formatter) -> std::fmt::Result {
        write!(f, "{}", String::from(self))
    }
}

#[macro_export]
macro_rules! cuda_error {
    // legacy macro, deprecated
    () => {
        mod cuda {
            pub type Error = sppark::Error;
        }
    };
}

use core::ffi::c_void;
#[cfg(any(feature = "cuda", feature = "rocm"))]
use core::mem::transmute;

#[repr(C)]
pub struct Gpu_Ptr<T> {
    ptr: *const c_void,
    phantom: core::marker::PhantomData<T>,
}

#[cfg(any(feature = "cuda", feature = "rocm"))]
impl<T> Default for Gpu_Ptr<T> {
    fn default() -> Self {
        Self {
            ptr: core::ptr::null(),
            phantom: core::marker::PhantomData,
        }
    }
}

#[cfg(any(feature = "cuda", feature = "rocm"))]
impl<T> Drop for Gpu_Ptr<T> {
    fn drop(&mut self) {
        extern "C" {
            fn drop_gpu_ptr_t(by_ref: &Gpu_Ptr<c_void>);
        }
        unsafe { drop_gpu_ptr_t(transmute::<&_, &_>(self)) };
        self.ptr = core::ptr::null();
    }
}

#[cfg(any(feature = "cuda", feature = "rocm"))]
impl<T> Clone for Gpu_Ptr<T> {
    fn clone(&self) -> Self {
        extern "C" {
            fn clone_gpu_ptr_t(by_ref: &Gpu_Ptr<c_void>) -> Gpu_Ptr<c_void>;
        }
        unsafe { transmute::<_, _>(clone_gpu_ptr_t(transmute::<&_, &_>(self))) }
    }
}

#[repr(C)]
pub enum NTTInputOutputOrder {
    NN = 0,
    NR = 1,
    RN = 2,
    RR = 3,
}

#[repr(C)]
pub enum NTTDirection {
    Forward = 0,
    Inverse = 1,
}

#[repr(C)]
pub enum NTTType {
    Standard = 0,
    Coset = 1,
}

// Given `slice_t<U>` value argument on the C++ side, one declares
// corresponding argument as `sppark::Slice<U>` on the Rust side and
// passes Rust slice as `foo.into()`. Recall that `U` has to be concrete
// on the FFI boundary. This can be tricky if the Rust side is generic.
// If the concrete type is not readily available in Rust, use a stand-in
// such as `sppark::Slice<[u64; N]>` with N chosen to match the size of
// the object. Note that all below methods use raw pointer casts, yet
// there are no `unsafe` blocks. Rationale is that one would invoke them
// as one passes arguments to an FFI interface, which has to be in an
// unsafe block already.

#[repr(C)]
pub struct Slice<U> {
    ptr: *const U,
    len: usize,
}

use core::mem::size_of;

impl<T, U> From<&mut [T]> for Slice<U> {
    #[inline]
    fn from(slice: &mut [T]) -> Self {
        // const _: () = // I wish this worked with generics:-(
        assert!(size_of::<T>() == size_of::<U>());
        Self {
            ptr: slice.as_mut_ptr() as *mut _,
            len: slice.len(),
        }
    }
}

impl<T, U> From<&[T]> for Slice<U> {
    #[inline]
    fn from(slice: &[T]) -> Self {
        // const _: () = // I wish this worked with generics:-(
        assert!(size_of::<T>() == size_of::<U>());
        Self {
            ptr: slice.as_ptr() as *const _,
            len: slice.len(),
        }
    }
}

impl<U> Slice<U> {
    #[inline]
    pub fn new<T>(p: *const T, n: usize) -> Self {
        // const _: () = // I wish this worked with generics:-(
        assert!(size_of::<T>() == size_of::<U>());
        Self {
            ptr: p as *const _,
            len: n,
        }
    }
}

#[cfg(feature = "build")]
pub mod build;
