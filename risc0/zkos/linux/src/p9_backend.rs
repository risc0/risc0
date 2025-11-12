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
    RclunkMessage,
    RfsyncMessage,
    RgetattrMessage,
    RlcreateMessage,
    RlopenMessage,
    RmkdirMessage,
    RmknodMessage,
    RreadMessage,
    RreaddirMessage,
    RreadlinkMessage,
    RremoveMessage,
    RrenameatMessage,
    RsetattrMessage,
    RsymlinkMessage,
    RunlinkatMessage,
    RversionMessage,
    RwalkMessage,
    RwriteMessage,
    TattachError,
    TattachMessage,
    TclunkError,
    TclunkMessage,
    TfsyncError,
    TfsyncMessage,
    TgetattrError,
    TgetattrMessage,
    TlcreateError,
    TlcreateMessage,
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
    TrenameatError,
    TrenameatMessage,
    TsetattrError,
    TsetattrMessage,
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
}

/// Global backend selector
static mut BACKEND_TYPE: BackendType = BackendType::Zkvm;

#[derive(Clone, Copy, Debug, PartialEq)]
pub enum BackendType {
    Zkvm,
    InMemory,
}

/// Set the active backend type
pub fn set_backend_type(backend: BackendType) {
    unsafe {
        BACKEND_TYPE = backend;
    }
}

/// Get the current backend type
pub fn get_backend_type() -> BackendType {
    unsafe { BACKEND_TYPE }
}

/// Get a ZkvmBackend instance (always available)
pub fn get_zkvm_backend() -> crate::p9_zkvm::ZkvmBackend {
    crate::p9_zkvm::ZkvmBackend::new()
}

/// Get InMemoryBackend instance if available
///
/// Note: For now this panics if called before initialization.
/// In a real implementation, you'd initialize this at startup with a snapshot.
#[allow(static_mut_refs)]
pub fn get_in_memory_backend() -> &'static mut crate::p9_in_memory::InMemoryBackend {
    static mut BACKEND: Option<crate::p9_in_memory::InMemoryBackend> = None;

    unsafe {
        if let None = &BACKEND {
            // Initialize with empty filesystem for now
            // In production, load from snapshot here
            BACKEND = Some(crate::p9_in_memory::InMemoryBackend::new());
        }
        BACKEND.as_mut().unwrap()
    }
}
