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

#include <mlir/IR/MLIRContext.h>
#include "compiler/extractor/RecordingVal.h"
#include "zirgen/Dialect/ZHLT/IR/ZHLT.h"
// #include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"

#define ZIRGEN

struct RecordingReg;

struct RecordingContext {
    using ValImpl = RecordingVal;
    using ValExtImpl = RecordingValExt;
    using RegImpl = RecordingReg;
    using ArgCountRegImpl = RecordingReg;

    RecordingContext(mlir::MLIRContext* ctx);

    void eqz(RecordingVal val) {
        builder.create<zirgen::Zll::EqualZeroOp>(builder.getUnknownLoc(), val.value);
    }
    void eqz(RecordingValExt val) {
        // TODO
    }

    template<typename T>
    void push(const T& arg) {
        // TODO: implement this
    }

    template<typename T>
    void pull(const T& arg) {
        // TODO: implement this
    }

    template<typename T>
    void addArgument(RecordingVal count, const T& arg) {
        // TODO: implement this
    }

    // Since tables are only used in witgen, we have dummy implementations
    inline void tableAdd(uint32_t entry, uint32_t val) {}
    inline uint32_t tableGet(uint32_t offset) { return 0; }

    void globalSet(uint32_t entry, RecordingVal val) {
      // TODO: Actual do a global set here
    }
    RecordingVal globalGet(uint32_t entry) {
      // TODO: Actually do a global get
      return RecordingVal(uint64_t(0));
    }
    RecordingVal getX() {
      // TODO: Add support for 'x' in zirgen + existing proof system
      return RecordingVal(uint64_t(0));
    }

    mlir::ModuleOp getModuleOp() {
        return moduleOp;
    }

    void enterComponent(std::string name);
    void exitComponent();

    RecordingVal addValParameter();
    RecordingVal getNextRef();

    void materializeLayout(mlir::Type layoutType);

    mlir::MLIRContext* mlirCtx;
    mlir::ModuleOp moduleOp;
    mlir::OpBuilder builder;

    // Metadata used by a visitor can be stored in this member, for example a
    // `LayoutBuilderVisitor` can store a `LayoutBuilder` here which will be
    // accessible in its `apply` methods.
    void* visitorData;

private:
    void unifyRefsIntoLayout(mlir::Value layout, size_t& i);

    mlir::StringAttr componentName;

    // A temporary region on `moduleOp` that holds the body of a component being
    // built until `exitComponent` is called
    mlir::Region* componentBody;

    // A flattened list of all `ref`s that will ultimately be contained in the
    // component's layout
    std::vector<mlir::Value> refs;

    // The index 0 used for load ops
    mlir::Value zero;

    friend struct RecordingVal;
};

struct RecordingReg {
    RecordingVal val;

    RecordingReg() : val(RecordingVal::getContext()->getNextRef()) {}
    explicit RecordingReg(RecordingVal val) : val(val) {}

    void set(RecordingContext& ctx, RecordingVal val) {}
    RecordingVal get() { return val; }

    template<typename T>
    void applyInner(RecordingContext& ctx) {}
    void verify(RecordingContext& ctx) {}
    void addArguments(RecordingContext& ctx) {}
};
