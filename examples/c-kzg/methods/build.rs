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

use c_kzg::KzgSettings;
use std::env;
use std::path::Path;

fn main() {
    let out_dir_env = env::var_os("OUT_DIR").unwrap();
    let out_dir = Path::new(&out_dir_env);
    let kzg_raw_path = out_dir.join("kzg_settings_raw.bin");
    let kzg_trusted_setup = Path::new("./trusted_setup.txt");
    let kzg_settings = KzgSettings::load_trusted_setup_file(kzg_trusted_setup).unwrap();
    let kzg_setup_data = kzg_settings.to_bytes().to_vec();
    std::fs::write(&kzg_raw_path, kzg_setup_data).unwrap();
    unsafe {
        env::set_var("KZG_FILE_PATH", kzg_raw_path.to_string_lossy().to_string());
    }

    risc0_build::embed_methods();
}
