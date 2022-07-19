// Copyright 2022 Risc0, Inc.
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

pub trait Log {
    fn log(&self, msg: &str);
}

static mut LOGGER: &dyn Log = &NopLogger;

struct NopLogger;

impl Log for NopLogger {
    fn log(&self, _msg: &str) {}
}

pub fn set_logger(logger: &'static dyn Log) {
    unsafe { LOGGER = logger };
}

pub fn logger() -> &'static dyn Log {
    unsafe { LOGGER }
}

pub fn log(msg: &str) {
    logger().log(msg);
}
