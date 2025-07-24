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

use crate::Result;

use sha2::Digest as _;

use std::fs::File;
use std::{
    fmt,
    io::{self, Read as _},
};

pub struct Sha256Writer<WriteT> {
    hasher: sha2::Sha256,
    writer: WriteT,
}

impl<WriterT> Sha256Writer<WriterT> {
    pub fn new(writer: WriterT) -> Self {
        Self {
            hasher: sha2::Sha256::new(),
            writer,
        }
    }

    pub fn finish(self) -> Sha256Digest {
        self.hasher.finalize().into()
    }
}

impl<WriterT: io::Write> io::Write for Sha256Writer<WriterT> {
    fn write(&mut self, buf: &[u8]) -> io::Result<usize> {
        let written = self.writer.write(buf)?;
        self.hasher.update(&buf[..written]);

        Ok(written)
    }

    fn flush(&mut self) -> io::Result<()> {
        self.writer.flush()
    }
}

type Sha256DigestGenericArray = sha2::digest::generic_array::GenericArray<
    u8,
    <sha2::Sha256 as sha2::digest::OutputSizeUser>::OutputSize,
>;

#[derive(PartialEq, Eq, Debug)]
pub struct Sha256Digest(Sha256DigestGenericArray);

impl std::str::FromStr for Sha256Digest {
    type Err = String;

    fn from_str(s: &str) -> std::result::Result<Self, Self::Err> {
        let artifact_sha256 =
            hex::decode(s).map_err(|e| format!("invalid SHA256 sum: {s:?}: {e}"))?;
        Ok(Self(
            <[u8; 32]>::try_from(artifact_sha256)
                .map_err(|_| format!("invalid SHA256 sum: {s:?}"))?
                .into(),
        ))
    }
}

impl fmt::Display for Sha256Digest {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{:x}", &self.0)
    }
}

impl From<Sha256DigestGenericArray> for Sha256Digest {
    fn from(d: Sha256DigestGenericArray) -> Self {
        Self(d)
    }
}

impl Sha256Digest {
    #[cfg_attr(not(feature = "publish"), allow(dead_code))]
    pub fn calculate_for_file(file: &mut File) -> Result<Sha256Digest> {
        let mut hasher = sha2::Sha256::new();

        let mut chunk = vec![0u8; 1024 * 1024];
        loop {
            let bytes_read = file.read(&mut chunk)?;
            if bytes_read == 0 {
                break;
            }
            hasher.update(&chunk[..bytes_read]);
        }
        Ok(hasher.finalize().into())
    }
}

#[test]
fn sha256_digest_display_from_str() {
    let mut hasher = sha2::Sha256::new();
    hasher.update([1, 2, 3, 4]);
    let s: Sha256Digest = hasher.finalize().into();

    let s_str = s.to_string();
    assert_eq!(s_str.parse::<Sha256Digest>().unwrap(), s);
}
