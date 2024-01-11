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

use self::error::Error;

pub(crate) mod auth;
pub(crate) mod callback_request;
pub(crate) mod error;
pub(crate) mod request_extractor;
pub(crate) mod server;
pub(crate) mod state;

/// The routes for the API.
pub mod routes {
    /// Route for `Callback` related APIs.
    pub const CALLBACK_ROUTE: &str = "/v1/callbacks";
}

pub(crate) type Result<T, E = Error> = ::std::result::Result<T, E>;
