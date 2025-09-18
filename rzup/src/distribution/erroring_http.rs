// Copyright 2025 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0, <LICENSE-APACHE or
// http://apache.org/licenses/LICENSE-2.0> or the MIT license <LICENSE-MIT or
// http://opensource.org/licenses/MIT>, at your option. This file may not be
// copied, modified, or distributed except according to those terms.
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
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
