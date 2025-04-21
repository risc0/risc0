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

//! Module containing functions for using dev mode. See [self::is_dev_mode].
//!
//! Use the [`dev_mode_enabled`] attribute macro to enable dev mode for a block or function.

use core::marker::PhantomData;

thread_local! {
    /// Counter that is determine when the code is in a dev mode context.
    ///
    /// NOTE: This is a thread-local except in the zkVM.
    #[cfg(not(feature = "disable-dev-mode"))]
    static DEV_MODE_CONTEXT_DEPTH: core::cell::RefCell<u32> = core::cell::RefCell::new(0);
}

// PhantomData<*cont ()> prevents Rust from automatically implementing Send.
/// When a [DevModeContext] exists on a the stack, dev mode will be enabled.
pub struct DevModeContext(PhantomData<*const ()>);

impl DevModeContext {
    /// Enter a dev mode context. While this value is held, dev mode will be enabled.
    #[must_use]
    pub fn enter() -> Self {
        #[cfg(not(feature = "disable-dev-mode"))]
        {
            DEV_MODE_CONTEXT_DEPTH.with_borrow_mut(|x| *x += 1);
        }
        Self(PhantomData)
    }

    /// Exit a dev mode context. When the last [DevModeContext] is exited, dev mode will be
    /// disabled.
    pub fn exit(self) {
        drop(self);
    }
}

#[cfg(not(feature = "disable-dev-mode"))]
impl Drop for DevModeContext {
    /// Exit the dev mode context on drop.
    fn drop(&mut self) {
        DEV_MODE_CONTEXT_DEPTH.with_borrow_mut(|x| {
            x.checked_sub(1)
                .expect("underflow of DEV_MODE_CONTEXT_DEPTH occurred")
        });
    }
}

/// Returns `true` if dev mode is enabled.
///
/// When dev mode is enabled, [FakeReceipt][crate::FakeReceipt] can be used to test applications.
/// In particular, the verifier will accept fake receipts as a valid proof of
/// execution, even though it provides no cryptographic guarantees. Additionally, the prover will
/// produce a fake receipt instead of spending computation resources to produce a full receipt.
///
/// Dev mode can be enabled in one of two ways:
/// 1. By setting the `RISC0_DEV_MODE` environment variable to "1", "true", or "yes". This does not
///    work when building for the guest (i.e. `target_os = zkvm`).
/// 2. By calling [DevModeContext::enter()] and holding the returned value.
///
/// Dev mode can be fully disabled by setting thte `dev-mode-disabled` feature flag on this crate.
pub fn is_dev_mode() -> bool {
    let is_env_set = std::env::var("RISC0_DEV_MODE")
        .ok()
        .map(|x| x.to_lowercase())
        .filter(|x| x == "1" || x == "true" || x == "yes")
        .is_some();

    let in_context = {
        #[cfg(not(feature = "disable-dev-mode"))]
        {
            DEV_MODE_CONTEXT_DEPTH.with_borrow(|x| *x > 0)
        }
        #[cfg(feature = "disable-dev-mode")]
        {
            false
        }
    };

    let enabled = is_env_set || in_context;

    if cfg!(feature = "disable-dev-mode") && enabled {
        panic!("zkVM: Inconsistent settings -- please resolve. \
            The RISC0_DEV_MODE environment variable is set but dev mode has been disabled by feature flag.");
    }

    cfg!(not(feature = "disable-dev-mode")) && enabled
}

/// Macro for enabling dev mode for a function or block of code.
///
/// This macro creates a [`DevModeContext`] that exists for the duration of the
/// function or block. When the function returns or block ends, the context is
/// automatically dropped and dev mode is disabled (unless another context exists).
///
/// # Examples
///
/// ```no_run
/// # use risc0_zkvm::{default_prover, dev_mode_enabled, ExecutorEnv};
/// # const EXMAPLE_ELF: &'static [u8] = b"";
/// # const EXMAPLE_ID: [u8; 32] = [0u8; 32];
/// // Enable dev mode for a block
/// dev_mode_enabled! {
///     let receipt = default_prover().prove(ExecutorEnv::default(), EXMAPLE_ELF).unwrap().receipt;
///     receipt.verify(EXMAPLE_ID)
/// };
/// ```
#[macro_export]
macro_rules! dev_mode_enabled {
    {$($body:tt)*} => {
        {
            let _dev_mode_ctx = $crate::DevModeContext::enter();
            $($body)*
        }
    };
}

/// ```compile_fail
/// trait AssertSend: Send {}
/// impl AssertSend for risc0_zkvm::DevModeContext {}
/// ```
#[allow(unused)]
const TEST_DEV_MODE_CONTEXT_IS_NOT_SEND: () = ();
