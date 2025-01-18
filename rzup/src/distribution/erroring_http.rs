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
