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

// TODO: WIP

struct IoHandler {}

struct MemoryHandler {
    //   IoHandler* io;
}

struct MemoryState {
    // std::map<uint32_t, uint32_t> data;
    // std::set<MemoryEvent> history;
}

struct MemoryEvent {
    // uint32_t addr;
    // uint32_t cycle;
    // bool isWrite;
    // uint32_t data;
}
