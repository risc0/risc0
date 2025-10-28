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

#include "compiler/extractor/NopVal.h"
#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"

namespace layoutbuilder {

class LayoutBuilder;

struct Context {
  using ValImpl = NopVal;
  using ValExtImpl = NopVal;
  using RegImpl = NopReg;
  using ArgCountRegImpl = NopReg;

  Context(mlir::MLIRContext* mlirCtx, LayoutBuilder* builder) : mlirCtx(mlirCtx), builder(builder) {}

  mlir::MLIRContext* mlirCtx;
  LayoutBuilder* builder;
};

/// A helper class for collecting the members of a `LayoutType`
class LayoutBuilder {
public:
  LayoutBuilder(std::string name) : name(name) {}

  void addMember(mlir::StringAttr name, mlir::Type type) { members.push_back({name, type}); }

  mlir::Type getType(mlir::MLIRContext* ctx) {
    return zirgen::ZStruct::LayoutType::get(ctx, name, members);
  }

  std::string name;
  std::vector<zirgen::ZStruct::FieldInfo> members;
};

/// A visitor class for building ZStruct layouts for components.
/// See also: `getLayoutType`
class Visitor {
public:
  template <typename T, typename... Args>
  static void apply(Context& ctx, const char* memberName, T& t, Args... args) {
    LayoutBuilder* builder = ctx.builder;
    LayoutBuilder subBuilder(T::NAME);
    ctx.builder = &subBuilder;
    t.template applyInner<Visitor>(ctx, args...);
    builder->addMember(mlir::StringAttr::get(ctx.mlirCtx, memberName),
                       subBuilder.getType(ctx.mlirCtx));
    ctx.builder = builder;
  }

  template <typename T, size_t N, typename... Args> static void apply(Context& ctx, const char* memberName, T (&t)[N], Args... args) {
    LayoutBuilder* builder = ctx.builder;

    // Get the layout type of an element. Note that we still need to visit every
    // element to ensure there are the right number of refs in the context.
    LayoutBuilder container("$tmp");
    ctx.builder = &container;
    for (size_t i = 0; i < N; i++) {
      std::string name = "elem" + std::to_string(i);
      Visitor::apply(ctx, name.c_str(), t[i], args...);
    }
    mlir::Type elementType = container.members.front().type;
    ctx.builder = builder;

    builder->addMember(mlir::StringAttr::get(ctx.mlirCtx, memberName),
                       zirgen::ZStruct::LayoutArrayType::get(ctx.mlirCtx, elementType, N));
  }

  static void apply(Context& ctx, const char* memberName, NopReg&) {
    mlir::Type ref = zirgen::Zhlt::getRefType(ctx.mlirCtx);
    ctx.builder->addMember(mlir::StringAttr::get(ctx.mlirCtx, memberName), ref);
  }

  static void apply(Context& ctx, const char* memberName, NopVal&) {
    // Vals have no layout, so do nothing and stop recursion
  }
};

} // end namespace layoutbuilder

template <template <typename Ctx> typename Component, typename... Args>
mlir::Type getLayoutType(mlir::MLIRContext* mlirCtx) {
  using namespace layoutbuilder;
  LayoutBuilder layoutBuilder(Component<Context>::NAME);
  Context ctx(mlirCtx, &layoutBuilder);
  Component<Context> component;
  component.template applyInner<Visitor>(ctx, Args{}...);
  return layoutBuilder.getType(mlirCtx);
}
