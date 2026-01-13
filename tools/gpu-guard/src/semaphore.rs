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
    fs::{File, OpenOptions},
    path::Path,
    thread::sleep,
    time::Duration,
};

use fs2::FileExt;
use once_cell::sync::Lazy;

static SEMAPHORE_DIR: Lazy<String> = Lazy::new(|| {
    std::env::var("GPU_SEMAPHORE_PATH").unwrap_or_else(|_| "/tmp/gpu_semaphore".to_string())
});

fn semaphore_size() -> usize {
    std::env::var("GPU_SEMAPHORE_SIZE")
        .ok()
        .and_then(|s| s.parse().ok())
        .unwrap_or(1)
}

pub fn acquire_gpu_semaphore() -> std::io::Result<File> {
    let path = Path::new(&*SEMAPHORE_DIR);
    std::fs::create_dir_all(path)?;

    for attempt in 0.. {
        for i in 0..semaphore_size() {
            let lock_path = path.join(format!("{i}.lock"));
            let file = OpenOptions::new()
                .read(true)
                .write(true)
                .create(true)
                .truncate(true)
                .open(&lock_path)?;

            match file.try_lock_exclusive() {
                Ok(_) => {
                    println!("[gpu-guard] Acquired slot {i} (attempt {attempt})");
                    return Ok(file);
                }
                Err(error) => {
                    if error.kind() == fs2::lock_contended_error().kind() {
                        continue;
                    } else {
                        return Err(error);
                    }
                }
            }
        }

        sleep(Duration::from_millis(50));
    }

    unreachable!()
}

#[cfg(target_os = "linux")]
fn gpu_semaphore_is_held() -> std::io::Result<bool> {
    for entry in std::fs::read_dir("/proc/self/fd")? {
        if let Ok(file_path) = entry?.path().canonicalize()
            && file_path.starts_with(&*SEMAPHORE_DIR)
        {
            return Ok(true);
        }
    }
    Ok(false)
}

pub fn assert_gpu_semaphore_held() {
    #[cfg(target_os = "linux")]
    match gpu_semaphore_is_held() {
        Ok(held) => {
            assert!(
                held,
                "GPU semaphore not held. Annotate test with `#[gpu_guard::gpu_guard]`"
            );
        }
        Err(error) => {
            panic!("failed to inspect if GPU semaphore was held: {error}");
        }
    }
}
