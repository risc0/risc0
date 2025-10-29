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

#pragma once

#include "RecordingVal.h"
#include "compiler/extractor/NopVal.h"
#include "compiler/extractor/RecordingContext.h"
#include <mlir/Dialect/Arith/IR/Arith.h>

namespace populate_component {

struct Populator {
  Populator(RecordingContext& ctx);

  mlir::Value lookup(const char* memberName);
  mlir::Value subscript(size_t index);
  mlir::Value load();

  void pop() { path.pop_back(); }

  ComponentIRMap map;

private:
  mlir::OpBuilder builder;
  std::vector<mlir::Value> path;
  mlir::Value zero;
};

struct PopulatorSingleton {
  static void set(Populator* value) { populator = value; }
  static Populator* get() { return populator; }

protected:
  static Populator* populator;
};

class Visitor {
public:
  template <typename T, typename... Args>
  static void apply(RecordingContext& ctx, const char* memberName, T& t, Args... args) {
    Populator* populator = PopulatorSingleton::get();
    mlir::Value sublayout = populator->lookup(memberName);
    populator->map.insert(&t, sublayout);
    t.template applyInner<Visitor>(ctx, args...);
    populator->pop();
  }

  template <typename T, size_t N, typename... Args>
  static void apply(RecordingContext& ctx, const char* memberName, T (&t)[N], Args... args) {
    Populator* populator = PopulatorSingleton::get();
    populator->lookup(memberName);
    for (size_t i = 0; i < N; i++) {
      mlir::Value element = populator->subscript(i);
      populator->map.insert(&(t[i]), element);
      t[i].template applyInner<Visitor>(ctx, args...);
      populator->pop();
    }
    populator->pop();
  }

  static void apply(RecordingContext& ctx, const char* memberName, RecordingReg& r) {
    Populator* populator = PopulatorSingleton::get();
    mlir::Value reg = populator->lookup(memberName);
    mlir::Value val = populator->load();
    r.val = val;
    populator->map.insert(&r, reg);
    populator->pop();
  }

  static void apply(RecordingContext& ctx, const char* memberName, RecordingVal&) {
    // Vals have no layout, so do nothing and stop recursion
  }
};

} // end namespace populate_component

// Walks over the component, generating subscript, lookup, and load operations
// in the IR that traverse its structure, and populating registers with the
// corresponding loads in the IR. The return value is a mapping from components
// to their corresponding values in the IR, which otherwise is only possible for
// registers since RecordingReg directly contains its MLIR value.
template <template <typename Ctx> typename Component, typename... Args>
ComponentIRMap populateComponent(RecordingContext& ctx, Component<RecordingContext>& component) {
  using namespace populate_component;
  Populator populator(ctx);
  RecordingVal::stopRecording();
  PopulatorSingleton::set(&populator);
  component.template applyInner<Visitor>(ctx, Args{}...);
  PopulatorSingleton::set(nullptr);
  RecordingVal::startRecording();
  return populator.map;
}
