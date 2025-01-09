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
use crate::components::Component;

#[derive(Debug)]
pub(crate) struct CppToolchain;

impl Component for CppToolchain {
    fn id(&self) -> &'static str {
        "cpp"
    }
}

#[cfg(test)]
mod tests {
    use semver::Version;

    use super::*;
    use crate::env::Environment;

    #[test]
    #[ignore = "requires GitHub API access"]
    fn test_cpp_toolchain_install() {
        let tmp_dir = tempfile::tempdir().unwrap();
        let env = Environment::with_root(tmp_dir.path()).unwrap();
        let component = CppToolchain;

        let version = Version::new(2024, 1, 5);

        let base_urls = Default::default();

        // Test installation
        component
            .install(&env, &base_urls, Some(&version), true)
            .unwrap();

        // Clean up
        component.uninstall(&env, &version).unwrap();
    }
}
