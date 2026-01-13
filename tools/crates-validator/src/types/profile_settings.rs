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

use super::traits::Merge;

// TODO: Is there a way to ensure that skipped fields during serialization are
// always in sync with default values?
// Maybe specifying a new type for each field, and adding a check
// `skip_serializing_if = "is_default"`?
#[derive(
    Debug, Clone, PartialEq, Eq, Hash, PartialOrd, Ord, serde::Serialize, serde::Deserialize,
)]
#[serde(default)]
#[serde(rename_all = "kebab-case")]
pub struct ProfileSettings {
    #[serde(skip_serializing_if = "is_false")]
    pub run_prover: bool,
    #[serde(skip_serializing_if = "is_false")]
    pub should_fail: bool,
    #[serde(skip_serializing_if = "is_false")]
    pub inject_cc_flags: bool,
    #[serde(skip_serializing_if = "is_false")]
    pub std: bool,
    #[serde(skip_serializing_if = "is_true")]
    pub fast_mode: bool,
    #[serde(skip_serializing_if = "is_false")]
    pub skip: bool,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub patch: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub import_str: Option<String>,
    #[serde(skip_serializing_if = "Option::is_none")]
    pub custom_main: Option<String>,
}

impl ProfileSettings {
    pub fn is_customized(&self) -> bool {
        self != &Self::default()
    }
}

impl Default for ProfileSettings {
    fn default() -> Self {
        Self {
            run_prover: false,
            should_fail: false,
            inject_cc_flags: false,
            std: false,
            fast_mode: true,
            skip: false,
            patch: None,
            import_str: None,
            custom_main: None,
        }
    }
}

impl Merge for ProfileSettings {
    fn merge(self, other: Self) -> Self {
        Self {
            run_prover: self.run_prover || other.run_prover,
            should_fail: self.should_fail || other.should_fail,
            inject_cc_flags: self.inject_cc_flags || other.inject_cc_flags,
            std: self.std || other.std,
            fast_mode: self.fast_mode || other.fast_mode,
            skip: self.skip || other.skip,
            patch: self.patch.or(other.patch),
            import_str: self.import_str.or(other.import_str),
            custom_main: self.custom_main.or(other.custom_main),
        }
    }
}

#[inline]
const fn is_true(b: &bool) -> bool {
    *b
}

#[inline]
const fn is_false(b: &bool) -> bool {
    !(*b)
}

#[cfg(test)]
mod tests {
    use super::*;
    use rstest::*;

    #[rstest]
    #[case::default(ProfileSettings::default(), false)]
    #[case::customized(ProfileSettings {
        run_prover: true,
        should_fail: true,
        inject_cc_flags: true,
        std: true,
        fast_mode: false,
        skip: true,
        patch: Some("patch".to_string()),
        import_str: Some("import_str".to_string()),
        custom_main: Some("custom_main".to_string()),
    }, true)]
    fn is_customized(#[case] settings: ProfileSettings, #[case] expected: bool) {
        assert_eq!(settings.is_customized(), expected);
    }
}
