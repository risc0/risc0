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

#pragma once

#include "compiler/extractor/RecordingVal.h"
#include "zirgen/Dialect/ZHLT/IR/ZHLT.h"

#include <mlir/IR/MLIRContext.h>
#include <string>

#define ZIRGEN

struct RecordingReg;

struct ComponentIRMap {
  ComponentIRMap() {}

  template <typename Component> void insert(Component* component, mlir::Value irValue) {
    map.insert({{component, Component::NAME}, irValue});
  }

  template <typename Component> mlir::Value get(Component* component) {
    return map.at({component, Component::NAME});
  }

private:
  using Key = std::pair<void*, const char*>;

  std::map<Key, mlir::Value> map;
};

struct RecordingContext {
  using ValImpl = RecordingVal;
  using ValExtImpl = RecordingValExt;
  using RegImpl = RecordingReg;
  using ArgCountRegImpl = RecordingReg;

  RecordingContext(mlir::MLIRContext* ctx);

  void eqz(RecordingVal val) {
    builder.create<zirgen::Zll::EqualZeroOp>(builder.getUnknownLoc(), val.value);
  }
  void eqz(RecordingValExt val) { throw std::runtime_error("Not implemented"); }

  template <typename T> void push(const T& arg) {
    // no-op
  }

  template <typename T> void pull(const T& arg) {
    // no-op
  }

  template <typename T> void addArgument(RecordingVal count, const T& arg) {
    // no-op
  }

  // Since tables are only used in witgen, we have dummy implementations
  inline void tableAdd(uint32_t entry, uint32_t val) {}
  inline uint32_t tableGet(uint32_t offset) { return 0; }

  void globalSet(uint32_t entry, RecordingVal val) {}
  RecordingVal globalGet(uint32_t entry);
  RecordingVal getX();

  mlir::ModuleOp getModuleOp() { return moduleOp; }

  void enterComponent(const char* name, mlir::Type layoutType);
  void exitComponent();

  RecordingVal addValParameter();

  template <typename Component> mlir::Value get(Component& component) {
    return componentIRMap.get<Component>(&component);
  }

  mlir::Value get(RecordingVal component) { return component.value; }

  mlir::MLIRContext* mlirCtx;
  mlir::ModuleOp moduleOp;
  mlir::OpBuilder builder;

  const char* componentName;

  // private:
  // A temporary region on `moduleOp` that holds the body of a component being
  // built until `exitComponent` is called
  mlir::Region* componentBody;

  // The index 0 used for load ops
  mlir::Value zero;

  // A map from component instances to their IR values
  ComponentIRMap componentIRMap;

  // A cache of values representing global variables
  std::map<uint32_t, RecordingVal> globalsCache;

  // A cached value representing global variable 'x'
  RecordingVal x = RecordingVal(nullptr);

  friend struct RecordingVal;
};

struct RecordingReg {
  static constexpr char NAME[] = "Reg";

  RecordingVal val;

  RecordingReg() : val(mlir::Value{}) {}
  explicit RecordingReg(RecordingVal val) : val(val) {}

  void set(RecordingContext& ctx, RecordingVal val) {}
  RecordingVal get() { return val; }

  template <typename T> void applyInner(RecordingContext& ctx) {}
  void verify(RecordingContext& ctx) {}
  void addArguments(RecordingContext& ctx) {}

  static void setContext(RecordingContext* value) { ctx = value; }

private:
  static RecordingContext* ctx;
};
