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

use std::fmt;

pub(crate) mod api;
pub(crate) mod base;
pub(crate) mod core;

impl fmt::Debug for api::asset::Kind {
    fn fmt(&self, f: &mut ::core::fmt::Formatter<'_>) -> ::core::fmt::Result {
        match self {
            Self::Inline(_) => f.debug_tuple("Inline").field(&"..").finish(),
            Self::Path(arg0) => f.debug_tuple("Path").field(arg0).finish(),
            Self::Redis(arg0) => f.debug_tuple("Redis").field(arg0).finish(),
        }
    }
}

impl fmt::Debug for api::Asset {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_struct("Asset").field("kind", &self.kind).finish()
    }
}

impl fmt::Debug for api::on_io_reply::Kind {
    fn fmt(&self, f: &mut ::core::fmt::Formatter<'_>) -> ::core::fmt::Result {
        match self {
            Self::Ok(_) => f.debug_tuple("Ok").field(&"..").finish(),
            Self::Error(arg0) => f.debug_tuple("Error").field(arg0).finish(),
        }
    }
}

impl fmt::Debug for api::OnIoReply {
    fn fmt(&self, f: &mut ::core::fmt::Formatter<'_>) -> ::core::fmt::Result {
        f.debug_struct("OnIoReply")
            .field("kind", &self.kind)
            .finish()
    }
}

impl fmt::Debug for api::SliceIo {
    fn fmt(&self, f: &mut ::core::fmt::Formatter<'_>) -> ::core::fmt::Result {
        f.debug_struct("SliceIo")
            .field("name", &self.name)
            .field("from_guest", &"..")
            .finish()
    }
}

impl fmt::Debug for api::posix_cmd::Kind {
    fn fmt(&self, f: &mut ::core::fmt::Formatter<'_>) -> ::core::fmt::Result {
        match self {
            Self::Read(arg0) => f.debug_tuple("Read").field(arg0).finish(),
            Self::Write(_) => f.debug_tuple("Write").field(&"..").finish(),
        }
    }
}

impl fmt::Debug for api::PosixCmd {
    fn fmt(&self, f: &mut ::core::fmt::Formatter<'_>) -> ::core::fmt::Result {
        f.debug_struct("PosixCmd")
            .field("kind", &self.kind)
            .finish()
    }
}
