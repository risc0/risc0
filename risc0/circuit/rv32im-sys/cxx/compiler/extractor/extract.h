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

#include "compiler/extractor/LayoutBuilderVisitor.h"
#include "compiler/extractor/RecordingContext.h"

struct VerifyFwd {
  template <typename T, typename... Args>
  static void apply(RecordingContext& ctx, const char*, T& obj, Args... args) {
    VerifyFwd::apply(ctx, obj, args...);
  }

  template <typename T,
            typename... Args,
            std::enable_if_t<!std::is_same<std::remove_cv_t<T>, char>::value, int> = 0>
  static void apply(RecordingContext& ctx, T& obj, Args... args) {
    obj.template applyInner<VerifyFwd>(ctx, args...);
    obj.verify(ctx, args...);
  }

  template <typename T,
            size_t N,
            typename... Args,
            std::enable_if_t<!std::is_same<std::remove_cv_t<T>, char>::value, int> = 0>
  static void apply(RecordingContext& ctx, T (&t)[N], Args... args) {
    for (size_t i = 0; i < N; i++) {
      VerifyFwd::apply(ctx, t[i], args...);
    }
  }
};

struct AddArgumentsFwd {
  template <typename T, typename... Args>
  static void apply(RecordingContext& ctx, const char*, T& obj, Args... args) {
    AddArgumentsFwd::apply(ctx, obj, args...);
  }

  template <typename T,
            typename... Args,
            std::enable_if_t<!std::is_same<std::remove_cv_t<T>, char>::value, int> = 0>
  static void apply(RecordingContext& ctx, T& obj, Args... args) {
    obj.template applyInner<AddArgumentsFwd>(ctx, args...);
    obj.addArguments(ctx, args...);
  }

  template <typename T,
            size_t N,
            typename... Args,
            std::enable_if_t<!std::is_same<std::remove_cv_t<T>, char>::value, int> = 0>
  static void apply(RecordingContext& ctx, T (&t)[N], Args... args) {
    for (size_t i = 0; i < N; i++) {
      AddArgumentsFwd::apply(ctx, t[i], args...);
    }
  }
};

template <template <typename Ctx> typename Component> void extract(RecordingContext& ctx) {
  mlir::Type layoutType = getLayoutType<Component>(ctx.mlirCtx);
  ctx.enterComponent(Component<RecordingContext>::NAME, layoutType);
  Component<RecordingContext> component;
  ctx.componentIRMap = populateComponent<Component>(ctx, component);
  AddArgumentsFwd::apply(ctx, component);
  VerifyFwd::apply(ctx, component);
  ctx.exitComponent();
}

template <template <typename Ctx> typename Component>
void extractWithValArg(RecordingContext& ctx) {
  mlir::Type layoutType = getLayoutType<Component, NopVal>(ctx.mlirCtx);
  ctx.enterComponent(Component<RecordingContext>::NAME, layoutType);
  auto arg1 = ctx.addValParameter();
  Component<RecordingContext> component;
  ctx.componentIRMap = populateComponent<Component, RecordingVal>(ctx, component);
  AddArgumentsFwd::apply(ctx, component, arg1);
  VerifyFwd::apply(ctx, component, arg1);
  ctx.exitComponent();
}

template <template <typename Ctx> typename Component>
void extractWithU32Arg(RecordingContext& ctx) {
  mlir::Type layoutType = getLayoutType<Component, ValU32<layoutbuilder::Context>>(ctx.mlirCtx);
  ctx.enterComponent(Component<RecordingContext>::NAME, layoutType);
  auto low = ctx.addValParameter();
  auto high = ctx.addValParameter();
  Component<RecordingContext> component;
  ctx.componentIRMap = populateComponent<Component, ValU32<RecordingContext>>(ctx, component);
  AddArgumentsFwd::apply(ctx, component, ValU32<RecordingContext>(low, high));
  VerifyFwd::apply(ctx, component, ValU32<RecordingContext>(low, high));
  ctx.exitComponent();
}

template <typename F, F f, size_t N>
void extractMutableArrayFunction(RecordingContext& ctx, const char* name) {
  ctx.enterComponent(name, nullptr);
  auto loc = ctx.builder.getUnknownLoc();
  Val<RecordingContext> arg[N];
  for (size_t i = 0; i < N; i++) {
    arg[i] = ctx.addValParameter();
  }
  f(ctx, arg);
  auto resultVals = llvm::map_to_vector(arg, [](const auto& v) { return v.value; });
  auto resultVal = ctx.builder.create<zirgen::ZStruct::ArrayOp>(loc, resultVals);
  ctx.builder.create<zirgen::Zhlt::ReturnOp>(loc, resultVal);
  ctx.exitComponent();
}

#define EXTRACT(Comp) extract<Comp>(ctx)

#define EXTRACT_MUTABLE_ARRAY_FUNCTION(f, N)                                                       \
  extractMutableArrayFunction<decltype(f<RecordingContext>), f<RecordingContext>, N>(ctx, #f);
