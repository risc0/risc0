// Copyright 2024 RISC Zero, Inc.
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

use std::{
    error::Error as StdError,
    fmt::{self, Debug},
    num::TryFromIntError,
    sync::PoisonError,
};

use axum::{http::StatusCode, response};
use tokio::task::JoinError;

#[derive(thiserror::Error, Debug)]
pub(crate) enum Error {
    #[error("ImageIdExists")]
    ImageIdExists,
    #[error("Bincode error")]
    Bincode(#[from] bincode::Error),
    #[error("Hex decode error")]
    Hex(#[from] hex::FromHexError),
    #[error("IO error")]
    IO(#[from] std::io::Error),
    #[error("Serde JSON error")]
    SerdeJson(#[from] serde_json::Error),
    #[error("JoinHandle error")]
    Join(#[from] JoinError),
    #[error("Unspecified error")]
    Unspecified(#[from] anyhow::Error),
    #[error("Poisoned lock")]
    Poisoned,
}

impl<T> From<PoisonError<T>> for Error {
    fn from(_: PoisonError<T>) -> Self {
        Self::Poisoned
    }
}

impl Error {
    pub fn status_code(&self) -> StatusCode {
        match self {
            Error::ImageIdExists { .. } => StatusCode::NO_CONTENT,
            Error::Poisoned
            | Error::Bincode { .. }
            | Error::Unspecified { .. }
            | Error::Hex { .. }
            | Error::IO { .. }
            | Error::SerdeJson { .. }
            | Error::Join { .. } => StatusCode::INTERNAL_SERVER_ERROR,
        }
    }
}

impl From<TryFromIntError> for Error {
    fn from(err: TryFromIntError) -> Self {
        Self::Unspecified(err.into())
    }
}

/// Convert [`Error`] into an HTTP response.
impl response::IntoResponse for Error {
    fn into_response(self) -> response::Response {
        let status = self.status_code();
        // log errors as one line with all its causes
        if status.is_client_error() || status.is_server_error() {
            tracing::error!(
                "Error response: {} ({:?})",
                DisplayErrorCauses(&self),
                &self
            );
        }
        // prepare an error message
        let message = match status {
            // for 500 Internal Server Error, we only return the error name, e.g.:
            // "IO Error"
            StatusCode::INTERNAL_SERVER_ERROR => self.to_string(),
            // otherwise, use the alternative anyhow formatting: colon-separated chain, e.g.:
            // "IO error: broken pipe"
            _ => format!("{}", DisplayErrorCauses(&self)),
        };

        // return the message as simple text
        (status, message).into_response()
    }
}

/// Provides a `Display` impl for `Error` that outputs the full chain of errors.
#[derive(Debug)]
pub(crate) struct DisplayErrorCauses<E: StdError>(pub E);

impl<E: StdError> fmt::Display for DisplayErrorCauses<E> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write_err(f, &self.0)
    }
}

fn write_err(f: &mut fmt::Formatter<'_>, err: &dyn StdError) -> fmt::Result {
    write!(f, "{}", err)?;
    if let Some(source) = err.source() {
        write!(f, ": ")?;
        write_err(f, source)?;
    }
    Ok(())
}

#[cfg(test)]
mod tests {
    use std::io;

    use anyhow::{anyhow, Context};

    use super::*;

    #[test]
    fn test_errors() {
        fn propagate_error() -> Result<(), Error> {
            Err(anyhow!("inner error"))?
        }

        let option: Option<String> = None;
        // use context to consume an option or a Result. The returned error will be of
        // type anyhow i.e., 500 error status code
        assert!(option.clone().context("option is none").is_err());
        assert!(propagate_error().context("caller").is_err());
    }

    fn io_err<E: Into<Box<dyn std::error::Error + Send + Sync>>>(error: E) -> Error {
        let io_err = io::Error::new(io::ErrorKind::Other, error);
        io_err.into()
    }

    #[test]
    fn test_display() {
        let err = io_err(io_err("mocked"));
        assert_eq!(format!("{}", &err), "IO error");
        assert_eq!(
            format!("{}", DisplayErrorCauses(&err)),
            "IO error: IO error: mocked"
        );
    }
}
