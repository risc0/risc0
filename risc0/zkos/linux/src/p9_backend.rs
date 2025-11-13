//! P9 Backend Trait
//!
//! This module defines the abstraction layer between the P9 protocol implementation
//! and the actual transport/storage backend.
//!
//! Backends can be:
//! - zkVM host calls (p9_zkvm.rs)
//! - In-memory filesystem (p9_in_memory.rs)
//! - Mock/test implementations
//! - Network sockets, etc.

#![allow(dead_code)] // Trait will be used when we refactor message sending

use crate::p9::{
    P9Response, // Re-use the existing P9Response type from p9.rs (includes RlerrorMessage)
    RattachMessage,
    RauthMessage,
    RclunkMessage,
    RflushMessage,
    RfsyncMessage,
    RgetattrMessage,
    RgetlockMessage,
    RlcreateMessage,
    RlinkMessage,
    RlockMessage,
    RlopenMessage,
    RmkdirMessage,
    RmknodMessage,
    RreadMessage,
    RreaddirMessage,
    RreadlinkMessage,
    RremoveMessage,
    RrenameMessage,
    RrenameatMessage,
    RsetattrMessage,
    RstatfsMessage,
    RsymlinkMessage,
    RunlinkatMessage,
    RversionMessage,
    RwalkMessage,
    RwriteMessage,
    RxattrcreateMessage,
    RxattrwalkMessage,
    TattachError,
    TattachMessage,
    TauthError,
    TauthMessage,
    TclunkError,
    TclunkMessage,
    TflushError,
    TflushMessage,
    TfsyncError,
    TfsyncMessage,
    TgetattrError,
    TgetattrMessage,
    TgetlockError,
    TgetlockMessage,
    TlcreateError,
    TlcreateMessage,
    TlinkError,
    TlinkMessage,
    TlockError,
    TlockMessage,
    TlopenError,
    TlopenMessage,
    TmkdirError,
    TmkdirMessage,
    TmknodError,
    TmknodMessage,
    TreadError,
    TreadMessage,
    TreaddirError,
    TreaddirMessage,
    TreadlinkError,
    TreadlinkMessage,
    TremoveError,
    TremoveMessage,
    TrenameError,
    TrenameMessage,
    TrenameatError,
    TrenameatMessage,
    TsetattrError,
    TsetattrMessage,
    TstatfsError,
    TstatfsMessage,
    TsymlinkError,
    TsymlinkMessage,
    TunlinkatError,
    TunlinkatMessage,
    TversionError,
    TversionMessage,
    TwalkError,
    TwalkMessage,
    TwriteError,
    TwriteMessage,
    TxattrcreateError,
    TxattrcreateMessage,
    TxattrwalkError,
    TxattrwalkMessage,
};

/// Trait for P9 backend implementations
///
/// Each backend (zkVM, in-memory, network, etc.) implements this trait
/// to handle P9 message sending and receiving.
pub trait P9Backend {
    /// Send Tversion and receive Rversion
    fn send_tversion(
        &mut self,
        msg: &TversionMessage,
    ) -> Result<P9Response<RversionMessage>, TversionError>;

    /// Send Tattach and receive Rattach
    fn send_tattach(
        &mut self,
        msg: &TattachMessage,
    ) -> Result<P9Response<RattachMessage>, TattachError>;

    /// Send Twalk and receive Rwalk
    fn send_twalk(&mut self, msg: &TwalkMessage) -> Result<P9Response<RwalkMessage>, TwalkError>;

    /// Send Tread and receive Rread
    fn send_tread(&mut self, msg: &TreadMessage) -> Result<P9Response<RreadMessage>, TreadError>;

    /// Send Twrite and receive Rwrite
    fn send_twrite(
        &mut self,
        msg: &TwriteMessage,
    ) -> Result<P9Response<RwriteMessage>, TwriteError>;

    /// Send Tlopen and receive Rlopen
    fn send_tlopen(
        &mut self,
        msg: &TlopenMessage,
    ) -> Result<P9Response<RlopenMessage>, TlopenError>;

    /// Send Tlcreate and receive Rlcreate
    fn send_tlcreate(
        &mut self,
        msg: &TlcreateMessage,
    ) -> Result<P9Response<RlcreateMessage>, TlcreateError>;

    /// Send Tgetattr and receive Rgetattr
    fn send_tgetattr(
        &mut self,
        msg: &TgetattrMessage,
    ) -> Result<P9Response<RgetattrMessage>, TgetattrError>;

    /// Send Tsetattr and receive Rsetattr
    fn send_tsetattr(
        &mut self,
        msg: &TsetattrMessage,
    ) -> Result<P9Response<RsetattrMessage>, TsetattrError>;

    /// Send Treaddir and receive Rreaddir
    fn send_treaddir(
        &mut self,
        msg: &TreaddirMessage,
    ) -> Result<P9Response<RreaddirMessage>, TreaddirError>;

    /// Send Treadlink and receive Rreadlink
    fn send_treadlink(
        &mut self,
        msg: &TreadlinkMessage,
    ) -> Result<P9Response<RreadlinkMessage>, TreadlinkError>;

    /// Send Tsymlink and receive Rsymlink
    fn send_tsymlink(
        &mut self,
        msg: &TsymlinkMessage,
    ) -> Result<P9Response<RsymlinkMessage>, TsymlinkError>;

    /// Send Tmknod and receive Rmknod
    fn send_tmknod(
        &mut self,
        msg: &TmknodMessage,
    ) -> Result<P9Response<RmknodMessage>, TmknodError>;

    /// Send Tmkdir and receive Rmkdir
    fn send_tmkdir(
        &mut self,
        msg: &TmkdirMessage,
    ) -> Result<P9Response<RmkdirMessage>, TmkdirError>;

    /// Send Tunlinkat and receive Runlinkat
    fn send_tunlinkat(
        &mut self,
        msg: &TunlinkatMessage,
    ) -> Result<P9Response<RunlinkatMessage>, TunlinkatError>;

    /// Send Trenameat and receive Rrenameat
    fn send_trenameat(
        &mut self,
        msg: &TrenameatMessage,
    ) -> Result<P9Response<RrenameatMessage>, TrenameatError>;

    /// Send Tclunk and receive Rclunk
    fn send_tclunk(
        &mut self,
        msg: &TclunkMessage,
    ) -> Result<P9Response<RclunkMessage>, TclunkError>;

    /// Send Tremove and receive Rremove
    fn send_tremove(
        &mut self,
        msg: &TremoveMessage,
    ) -> Result<P9Response<RremoveMessage>, TremoveError>;

    /// Send Tfsync and receive Rfsync
    fn send_tfsync(
        &mut self,
        msg: &TfsyncMessage,
    ) -> Result<P9Response<RfsyncMessage>, TfsyncError>;

    /// Send Tlink and receive Rlink
    fn send_tlink(&mut self, msg: &TlinkMessage) -> Result<P9Response<RlinkMessage>, TlinkError>;

    /// Send Trename and receive Rrename
    fn send_trename(
        &mut self,
        msg: &TrenameMessage,
    ) -> Result<P9Response<RrenameMessage>, TrenameError>;

    /// Send Txattrwalk and receive Rxattrwalk
    fn send_txattrwalk(
        &mut self,
        msg: &TxattrwalkMessage,
    ) -> Result<P9Response<RxattrwalkMessage>, TxattrwalkError>;

    /// Send Txattrcreate and receive Rxattrcreate
    fn send_txattrcreate(
        &mut self,
        msg: &TxattrcreateMessage,
    ) -> Result<P9Response<RxattrcreateMessage>, TxattrcreateError>;

    /// Send Tflush and receive Rflush
    fn send_tflush(
        &mut self,
        msg: &TflushMessage,
    ) -> Result<P9Response<RflushMessage>, TflushError>;

    /// Send Tauth and receive Rauth
    fn send_tauth(&mut self, msg: &TauthMessage) -> Result<P9Response<RauthMessage>, TauthError>;

    /// Send Tstatfs and receive Rstatfs
    fn send_tstatfs(
        &mut self,
        msg: &TstatfsMessage,
    ) -> Result<P9Response<RstatfsMessage>, TstatfsError>;

    /// Send Tlock and receive Rlock
    fn send_tlock(&mut self, msg: &TlockMessage) -> Result<P9Response<RlockMessage>, TlockError>;

    /// Send Tgetlock and receive Rgetlock
    fn send_tgetlock(
        &mut self,
        msg: &TgetlockMessage,
    ) -> Result<P9Response<RgetlockMessage>, TgetlockError>;
}

// Separate statics for each backend type
static mut ZKVM_BACKEND: Option<crate::p9_zkvm::ZkvmBackend> = None;
static mut INMEMORY_BACKEND: Option<crate::p9_in_memory::InMemoryBackend> = None;
static mut ZEROCOPY_BACKEND: Option<crate::p9_in_memory::ZeroCopyBackend> = None;

/// Get the active backend as a trait object
///
/// Priority: ZeroCopy > InMemory > Zkvm (default)
/// Since we only initialize once, we just check which one is Some().
#[allow(static_mut_refs)]
pub fn get_backend() -> &'static mut dyn P9Backend {
    unsafe {
        // Check in priority order
        if let Some(ref mut b) = ZEROCOPY_BACKEND {
            return b as &mut dyn P9Backend;
        }
        if let Some(ref mut b) = INMEMORY_BACKEND {
            return b as &mut dyn P9Backend;
        }
        // Default to zkVM backend (lazy init)
        if ZKVM_BACKEND.is_none() {
            ZKVM_BACKEND = Some(crate::p9_zkvm::ZkvmBackend::new());
        }
        ZKVM_BACKEND.as_mut().unwrap() as &mut dyn P9Backend
    }
}

/// Initialize with in-memory backend
pub fn init_in_memory_backend() {
    unsafe {
        INMEMORY_BACKEND = Some(crate::p9_in_memory::InMemoryBackend::new());
    }
}

/// Initialize the zero-copy backend from an embedded filesystem image
///
/// # Safety
/// Must be called before any P9 operations if using ZeroCopy backend.
/// The address must point to a valid FilesystemImage.
pub unsafe fn init_zerocopy_backend(addr: usize, max_size: usize) -> Result<usize, u32> {
    unsafe {
        let backend = crate::p9_in_memory::ZeroCopyBackend::from_address(addr, max_size)?;
        let fs_size = backend.image_size();
        ZEROCOPY_BACKEND = Some(backend);
        Ok(fs_size)
    }
}

// Deprecated compatibility functions
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum BackendType {
    Zkvm,
    InMemory,
    ZeroCopy,
}

pub fn get_backend_type() -> BackendType {
    unsafe {
        match (&raw const ZEROCOPY_BACKEND as *const Option<_>)
            .read()
            .is_some()
        {
            true => BackendType::ZeroCopy,
            false => match (&raw const INMEMORY_BACKEND as *const Option<_>)
                .read()
                .is_some()
            {
                true => BackendType::InMemory,
                false => BackendType::Zkvm,
            },
        }
    }
}

pub fn set_backend_type(_backend: BackendType) {
    // Deprecated - backends are set by calling init_*_backend()
}

pub fn get_zkvm_backend() -> crate::p9_zkvm::ZkvmBackend {
    crate::p9_zkvm::ZkvmBackend::new()
}

#[allow(static_mut_refs)]
pub fn get_in_memory_backend() -> &'static mut crate::p9_in_memory::InMemoryBackend {
    unsafe {
        if INMEMORY_BACKEND.is_none() {
            INMEMORY_BACKEND = Some(crate::p9_in_memory::InMemoryBackend::new());
        }
        INMEMORY_BACKEND.as_mut().unwrap()
    }
}

#[allow(static_mut_refs)]
pub fn get_zerocopy_backend() -> &'static mut crate::p9_in_memory::ZeroCopyBackend {
    unsafe {
        ZEROCOPY_BACKEND
            .as_mut()
            .expect("ZeroCopy backend not initialized")
    }
}
