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

use std::{
    collections::HashMap,
    env,
    fmt::{self, Write},
    fs,
    path::{Path, PathBuf},
};

use glob::glob;
use regex::Regex;

#[derive(Debug)]
struct Level {
    nested: HashMap<String, Level>,
    files: Vec<PathBuf>,
}

fn main() {
    let home = env::var("CARGO_MANIFEST_DIR").unwrap();

    let mut level = Level::new();

    for root_dir in ["docs", "api"] {
        let pattern = format!("{home}/../../{root_dir}/**/*.md");
        let base = format!("{home}/../../{root_dir}",);
        let base = Path::new(&base).canonicalize().unwrap();

        for entry in glob(&pattern).unwrap() {
            let path = entry.unwrap();
            let path = Path::new(&path).canonicalize().unwrap();
            println!("cargo:rerun-if-changed={}", path.display());
            let rel = path.strip_prefix(&base).unwrap();

            let mut parts = vec![];
            for part in rel {
                parts.push(part.to_str().unwrap());
            }

            level.insert(path.clone(), &parts[..]);
        }
    }

    let out = format!("{}/doctests.rs", env::var("OUT_DIR").unwrap());

    fs::write(out, level.to_string()).unwrap();
}

impl fmt::Display for Level {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let mut dst = String::new();
        self.write_inner(&mut dst, 0)?;
        f.write_str(&dst)?;
        Ok(())
    }
}

impl Level {
    fn new() -> Level {
        Level {
            nested: HashMap::new(),
            files: vec![],
        }
    }

    fn insert(&mut self, path: PathBuf, rel: &[&str]) {
        if rel.len() == 1 {
            self.files.push(path);
        } else {
            let nested = self
                .nested
                .entry(rel[0].to_string())
                .or_insert(Level::new());
            nested.insert(path, &rel[1..]);
        }
    }

    fn write_into(&self, dst: &mut String, name: &str, level: usize) -> fmt::Result {
        self.write_space(dst, level);
        let name = name.replace(['-', '.'], "_");
        writeln!(dst, "pub mod {name} {{",)?;
        self.write_inner(dst, level + 1)?;
        self.write_space(dst, level);
        writeln!(dst, "}}")?;

        Ok(())
    }

    fn write_inner(&self, dst: &mut String, level: usize) -> fmt::Result {
        for (name, nested) in &self.nested {
            nested.write_into(dst, name, level)?;
        }

        self.write_space(dst, level);

        for file in &self.files {
            let stem = Path::new(file)
                .file_stem()
                .unwrap()
                .to_str()
                .unwrap()
                .replace('-', "_");

            let content = fs::read_to_string(file).expect("Failed to read file");
            let processed_content = self.remove_footnotes(&content);

            self.write_space(dst, level);
            writeln!(dst, "#[doc = r#\"{processed_content}\"#]")?;
            self.write_space(dst, level);
            writeln!(dst, "pub fn {stem}_md() {{}}")?;
        }

        Ok(())
    }

    fn remove_footnotes(&self, content: &str) -> String {
        // Remove footnote references
        let reference_regex = Regex::new(r"\[\^.+?\]").unwrap();
        let without_references = reference_regex.replace_all(content, "");

        // Remove footnote definitions and their content
        let definition_regex = Regex::new(r"(?ms)^\[\^.+?\]:.+?(?:\n\n|\z)").unwrap();
        let without_definitions = definition_regex.replace_all(&without_references, "");

        // Remove any remaining numbered list items that start with "It"
        let numbered_list_regex = Regex::new(r"(?m)^\s*\d+\.\s+It.+$(\n(?:\s+.+$)*)*").unwrap();
        let without_numbered_lists = numbered_list_regex.replace_all(&without_definitions, "");

        // Remove any consecutive blank lines
        let blank_lines_regex = Regex::new(r"\n{3,}").unwrap();
        blank_lines_regex
            .replace_all(&without_numbered_lists, "\n\n")
            .into_owned()
    }

    fn write_space(&self, dst: &mut String, level: usize) {
        for _ in 0..level {
            dst.push_str("    ");
        }
    }
}
