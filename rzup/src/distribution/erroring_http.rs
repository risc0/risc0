// Copyright 2025 RISC Zero, Inc.
//
// This project is dual-licensed under either:
// - Apache License, Version 2.0 (LICENSE-APACHE or https://www.apache.org/licenses/LICENSE-2.0)
// - MIT License (LICENSE-MIT or https://opensource.org/licenses/MIT)
// at your option.
//
// SPDX-License-Identifier: Apache-2.0 OR MIT

use crate::error::{Result, RzupError};
use std::io;

pub enum Response {}

impl Response {
    pub fn content_length(&self) -> Option<u64> {
        unreachable!()
    }

    pub fn copy_to(&mut self, _writer: impl io::Write) -> Result<()> {
        unreachable!()
    }
}

pub trait IntoUrl {}
impl<T> IntoUrl for T {}

pub fn check_for_not_found(_url: impl IntoUrl, _bearer_token: &Option<String>) -> Result<bool> {
    Err(RzupError::Other("not built with install support".into()))
}

pub fn download_json<RetT: serde::de::DeserializeOwned>(
    _url: impl IntoUrl,
    _bearer_token: &Option<String>,
) -> Result<RetT> {
    Err(RzupError::Other("not built with install support".into()))
}

pub fn download_text(_url: impl IntoUrl, _bearer_token: &Option<String>) -> Result<String> {
    Err(RzupError::Other("not built with install support".into()))
}

pub fn download_bytes(_url: impl IntoUrl, _bearer_token: &Option<String>) -> Result<Response> {
    Err(RzupError::Other("not built with install support".into()))
}
