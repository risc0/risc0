// Copyright 2026 RISC Zero, Inc.
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

use serde_valid::validation::Errors as ValidationErrors;

use super::aliases::GroupedProfiles;

pub trait Group {
    fn group(self) -> GroupedProfiles;
}

pub trait Merge {
    fn merge(self, other: Self) -> Self;
}

pub trait Reduce {
    fn reduce(self) -> Self;
}

pub trait Exclude {
    fn exclude(self, other: Self) -> Self;
}

pub trait GetVersions {
    fn get_versions(&self) -> Vec<semver::Version>;
}

pub trait IsValid {
    fn is_valid(&self) -> Result<(), ValidationErrors>;
}
