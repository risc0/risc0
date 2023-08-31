// Copyright 2023 RISC Zero, Inc.
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

use anyhow::{Context, Result};

const BAD_JSON_ERR_MSG: &str = r#"
JSON is not properly formatted.
Expected a JSON as follows:
    {
        "<identifier>": [
            "<crate_name_1>",
            "<crate_name_2>",
            ...
        ],
        ...
    }"#;

fn bad_json() -> anyhow::Error {
    anyhow::anyhow!("{}", BAD_JSON_ERR_MSG)
}

pub fn read_crates_selection(path: impl AsRef<str>) -> Result<String> {
    Ok(std::fs::read_to_string(path.as_ref()).context(format!(
        "Failed to read content from file '{}'",
        path.as_ref()
    ))?)
}

pub fn parse_crates_json(raw_json: impl AsRef<str>) -> Result<Vec<String>> {
    let json: serde_json::Value =
        serde_json::from_str(raw_json.as_ref()).context("Failed to parse JSON")?;
    let obj = json.as_object().ok_or_else(bad_json)?;
    let mut crates = Vec::new();
    for (_k, v) in obj {
        let arr = v.as_array().ok_or_else(bad_json)?;
        for i in arr {
            let s = i.as_str().ok_or_else(bad_json)?;
            crates.push(s.to_string());
        }
    }
    Ok(crates)
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_parse_crates_json() {
        let json = r#"{
            "a": [
                "a1",
                "a2"
            ],
            "b": [
                "b1",
                "b2"
            ]
        }"#;
        let crates = parse_crates_json(json).expect("Failed to parse JSON");
        assert_eq!(crates, vec!["a1", "a2", "b1", "b2"])
    }
}
