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

#include "compiler/extractor/RecordingContext.h"
#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"

/// A helper class for collecting the members of a `LayoutType`
class LayoutBuilder {
public:
    LayoutBuilder(std::string name) : name(name) {}

    void addMember(mlir::StringAttr name, mlir::Type type) {
        members.push_back({name, type});
    }

    mlir::Type getType(mlir::MLIRContext* ctx) {
        return zirgen::ZStruct::LayoutType::get(ctx, name, members);
    }

    std::string name;
    std::vector<zirgen::ZStruct::FieldInfo> members;
};

// TODO: replace this with member name metadata from the circuit definition
inline std::string freshMemberName() {
    static unsigned i = 0;
    return "x" + std::to_string(i++);
}

/// A visitor class for building ZStruct layouts for components.
/// See also: `getLayoutType`
class LayoutBuilderVisitor {
public:
    template <typename T, typename... Args>
    static void apply(RecordingContext& ctx, T& t, Args... args) {
        auto builder = static_cast<LayoutBuilder*>(ctx.visitorData);
        LayoutBuilder subBuilder(T::NAME);
        ctx.visitorData = &subBuilder;
        t.template applyInner<LayoutBuilderVisitor>(ctx, args...);
        builder->addMember(ctx.builder.getStringAttr(freshMemberName()), subBuilder.getType(ctx.mlirCtx));
        ctx.visitorData = builder;
    }

    template <typename T, size_t N>
    static void apply(RecordingContext& ctx, T (&t)[N]) {
      auto builder = static_cast<LayoutBuilder*>(ctx.visitorData);

      // Get the layout type of an element. Note that we still need to visit every
      // element to ensure there are the right number of refs in the context.
      LayoutBuilder container("$tmp");
      ctx.visitorData = &container;
      for (size_t i = 0; i < N; i++) {
          LayoutBuilderVisitor::apply(ctx, t[i]);
      }
      mlir::Type elementType = container.members.front().type;
      ctx.visitorData = builder;

      builder->addMember(
          ctx.builder.getStringAttr(freshMemberName()),
          zirgen::ZStruct::LayoutArrayType::get(ctx.mlirCtx, elementType, N));
    }

    static void apply(RecordingContext& ctx, RecordingReg&) {
        mlir::Type ref = zirgen::Zhlt::getRefType(ctx.mlirCtx);
        auto builder = static_cast<LayoutBuilder*>(ctx.visitorData);
        builder->addMember(ctx.builder.getStringAttr(freshMemberName()), ref);
    }

    static void apply(RecordingContext& ctx, RecordingVal&) {
        // Vals have no layout, so do nothing and stop recursion
    }
};

template <typename T, typename... Args>
mlir::Type getLayoutType(RecordingContext& ctx, T& t, Args... args) {
    LayoutBuilder layoutBuilder(T::NAME);
    ctx.visitorData = &layoutBuilder;
    t.template applyInner<LayoutBuilderVisitor>(ctx, args...);
    return layoutBuilder.getType(ctx.mlirCtx);
}
