// Copyright 2024 RISC Zero, Inc.
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

#include "mlir/Transforms/DialectConversion.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/TypeSwitch.h"

#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"
#include "zirgen/Dialect/ZHLT/IR/ZHLT.h"
#include "zirgen/Dialect/ZStruct/IR/ZStruct.h"
#include "zirgen/dsl/Analysis/LayoutDAGAnalysis.h"
#include "zirgen/dsl/passes/PassDetail.h"

using namespace mlir;
using namespace zirgen::Zhlt;
using namespace zirgen::ZStruct;

/*
 * Fundamentally, a layout is a mapping between the registers of a component and
 * the columns of the underlying STARK trace. The goal of GenerateLayoutPass is
 * to create such mapping that respects all of the layout constraints implied by
 * the semantics of Zirgen, while using as few total columns as possible. This
 * is guided by a few simple rules:
 *   1. LayoutAliasOp operands must be assigned to the same columns
 *   2. A column may be reused by registers on different arms of the same mux
 *   3. Registers otherwise must be assigned different columns
 *
 * We use LayoutDAGAnalysis to take care of the first rule: this data flow
 * analysis constructs a DAG with a vertex for each layout in the program,
 * merging layouts that alias, and edges representing "structural inclusion."
 * Generating the layout becomes a walk over this DAG, using a memo to ensure
 * that if a vertex is visited twice (i.e. aliased) that it is assigned to the
 * same columns.
 *
 * Additionally, to allow depth first traversal to allocate via a 'bump allocator'
 * type of approach, we precompute for each aliases component, it's innermost
 * 'common' component, i.e. the deepest component which all aliased copies live
 * inside of.  When we reach this component, we allocate space for any aliased
 * descendants prior to continuing our normal depth first traversal, knowing that
 * the 'memo' will resolve the descendents when the traversal reaches them.
 *
 * The reuse of muxing is handled by tracking the largest column allocated in
 * the "current scope." We push a new scope when
 * visiting the arms of a mux, such that we can "pop" it and reuse those columns
 * on the next arm. Afterwards, we mark any columns used by any mux arm as used,
 * pursuant to the third rule. Thus, a mux typically needs as many columns as
 * its largest arm.
 */

namespace zirgen {
namespace dsl {
namespace {

// For components that are aliased into multiple locations, finds the most
// specific parent element and records it.  Then, when generating concrete
// layout, we can 'preallocate' any such decendents.  Note, we need to give
// every component a unique ID (by order they appear in depth first traversal)
// rather than only use maps, since otherwise pointers cause non-deterministic
// ordering.
class FindPreallocs {
  using Ptr = std::shared_ptr<LayoutDAG>;
  using Vec = std::vector<uint32_t>;
  using MapToVec = std::map<uint32_t, Vec>;
  // Result: for each abstract type, things I need to 'prealloc'
  using Result = std::map<Ptr, std::vector<Ptr>>;

public:
  Result run(const std::shared_ptr<LayoutDAG>& abstract) {
    Vec prefix;
    computeSharedPrefixes(abstract, prefix, Ptr());
    for (const auto& kvp : prefixes) {
      // Check if final value matches key, in which case there is a unique parent
      if (kvp.first == kvp.second.back()) {
        continue;
      }
      // Other, add ret
      ret[idToPtr[kvp.second.back()]].push_back(idToPtr[kvp.first]);
    }
    return ret;
  }

private:
  // Give ID's to each entry
  std::vector<Ptr> idToPtr;
  std::map<Ptr, uint32_t> ptrToId;
  // For an entry, what is the longest unique prefix
  MapToVec prefixes;
  Result ret;

  static Vec sharedPrefix(const Vec& lhs, const Vec& rhs) {
    if (lhs.size() == 0) { // Handle initialization case
      return rhs;
    }
    assert(lhs.size() > 0 && rhs.size() > 0);
    assert(lhs[0] == rhs[0]);
    size_t i = 0;
    while (i < std::min(lhs.size(), rhs.size())) {
      if (lhs[i] != rhs[i]) {
        break;
      }
      i++;
    }
    return Vec(lhs.begin(), lhs.begin() + i);
  }

  void computeSharedPrefixes(Ptr abstract, Vec& prefix, Ptr arm) {
    // Compute ID for element
    uint32_t id;
    if (ptrToId.count(abstract)) {
      id = ptrToId[abstract];
    } else {
      ptrToId[abstract] = idToPtr.size();
      id = idToPtr.size();
      idToPtr.push_back(abstract);
    }
    // Add to current prefix path compute shared prefix
    prefix.push_back(id);
    prefixes[id] = sharedPrefix(prefixes[id], prefix);
    // Descend for recursive types
    if (const auto* arr = std::get_if<AbstractArray>(abstract.get())) {
      for (auto element : arr->elements) {
        computeSharedPrefixes(element, prefix, arm);
      }
    } else if (const auto* str = std::get_if<AbstractStructure>(abstract.get())) {
      auto kind = str->type.getKind();
      bool isMux = (kind == LayoutKind::Mux || kind == LayoutKind::MajorMux);
      for (auto field : str->fields) {
        if (isMux && field.first == "@super" && arm) {
          ret[arm].push_back(field.second);
        }
        if (isMux && StringRef(field.first.str()).starts_with("arm")) {
          computeSharedPrefixes(field.second, prefix, field.second);
        } else {
          computeSharedPrefixes(field.second, prefix, arm);
        }
      }
    } else if (const auto* ref = std::get_if<std::shared_ptr<LayoutDAG>>(abstract.get())) {
      computeSharedPrefixes(*ref, prefix, arm);
    }
    // Pop from path
    prefix.pop_back();
  }
};

struct LayoutGenerator {
  LayoutGenerator(StringAttr bufferName, DataFlowSolver& solver)
      : bufferName(bufferName), solver(solver) {}

  Attribute generate(CheckLayoutFuncOp component) {
    // Empty layout -> empty attribute
    if (!component.getLayout())
      return Attribute();

    // llvm::errs() << component << "\n";
    Memo memo;
    auto layout = solver.lookupState<LayoutDAGAnalysis::Element>(component.getLayout());
    FindPreallocs findPreallocs;
    Preallocs preallocs = findPreallocs.run(layout->getValue().get());
    size_t allocator = 0;
    return materialize(layout->getValue().get(), memo, allocator, preallocs);
  }

private:
  // A memo of previously generated abstract layouts
  using Preallocs = std::map<std::shared_ptr<LayoutDAG>, std::vector<std::shared_ptr<LayoutDAG>>>;
  using Memo = DenseMap<LayoutDAG*, Attribute>;

  // Materialize a concrete layout attribute from an abstract layout
  Attribute materialize(const std::shared_ptr<LayoutDAG>& abstract,
                        Memo& memo,
                        size_t& allocator,
                        const Preallocs& preallocs) {
    if (memo.contains(abstract.get())) {
      return memo.at(abstract.get());
    }
    auto it = preallocs.find(abstract);
    if (it != preallocs.end()) {
      for (auto ptr : it->second) {
        // Allocate + memoize 'preallocs'
        materialize(ptr, memo, allocator, preallocs);
      }
    }

    Attribute attr;
    if (const auto* reg = std::get_if<AbstractRegister>(abstract.get())) {
      // Allocate multiple columns for extension field elements
      size_t index = allocator;
      allocator += reg->type.getElement().getFieldK();
      attr = RefAttr::get(reg->type.getContext(), index, reg->type);
    } else if (const auto* arr = std::get_if<AbstractArray>(abstract.get())) {
      SmallVector<Attribute, 4> elements;
      for (auto element : arr->elements) {
        elements.push_back(materialize(element, memo, allocator, preallocs));
      }
      attr = ArrayAttr::get(arr->type.getContext(), elements);
    } else if (const auto* str = std::get_if<AbstractStructure>(abstract.get())) {
      SmallVector<NamedAttribute> fields;
      if (str->type.getKind() == LayoutKind::Mux || str->type.getKind() == LayoutKind::MajorMux) {
        size_t finalAllocator = allocator;
        for (auto field : str->fields) {
          size_t armAllocator = allocator;
          fields.emplace_back(field.first,
                              materialize(field.second, memo, armAllocator, preallocs));
          finalAllocator = std::max(finalAllocator, armAllocator);
        }
        allocator = finalAllocator;
      } else {
        for (auto field : str->fields) {
          fields.emplace_back(field.first, materialize(field.second, memo, allocator, preallocs));
        }
      }
      auto members = DictionaryAttr::get(str->type.getContext(), fields);
      attr = StructAttr::get(str->type.getContext(), members, str->type);
    } else if (const auto* ref = std::get_if<std::shared_ptr<LayoutDAG>>(abstract.get())) {
      attr = materialize(*ref, memo, allocator, preallocs);
    } else {
      llvm_unreachable("bad variant");
    }
    memo[abstract.get()] = attr;
    return attr;
  }

  // Name of buffer to allocate registers in
  StringAttr bufferName;

  // The solver used to query data flow analysis results
  DataFlowSolver& solver;
};

struct GenerateLayoutPass : public GenerateLayoutBase<GenerateLayoutPass> {
  void runOnOperation() override {
    auto module = getOperation();
    auto ctx = module.getContext();
    OpBuilder builder(ctx);
    Location loc = builder.getUnknownLoc();

    DataFlowSolver solver;
    solver.load<LayoutDAGAnalysis>();

    module.walk([&](ComponentOp component) {
      builder.setInsertionPointToStart(module.getBody());
      StringAttr bufferName = getBufferName(component);
      if (!bufferName)
        return;

      auto checkLayoutFunc = component.getAspect<CheckLayoutFuncOp>();
      if (failed(solver.initializeAndRun(checkLayoutFunc)))
        assert(false && "an unexpected error occurred while solving the layout");
      LayoutGenerator layout(bufferName, solver);
      Attribute layoutAttr = layout.generate(checkLayoutFunc);

      // Only generate layout symbol for components which contain registers.
      if (layoutAttr) {
        StringAttr symName = builder.getStringAttr(getLayoutConstName(component.getName()));
        Type layoutType = component.getLayoutType();
        builder.create<GlobalConstOp>(loc, symName, layoutType, layoutAttr);
      }

      if (component.getName() == "@global") {
        assert(layoutAttr && "Unable to generate layout for globals");
      }
    });
  }

private:
  StringAttr getBufferName(ComponentOp component) {
    // TODO: Is there a better way to keep track of which components
    // get layouts and from which buffers?  Ideally these wouldn't
    // be hardcoded here.
    MLIRContext* ctx = getOperation().getContext();
    if (component.getName() == "@global")
      return StringAttr::get(ctx, "global");
    else if (component.getName().ends_with("$accum"))
      return StringAttr::get(ctx, "accum");
    else if (component.getName() == "@mix")
      return StringAttr::get(ctx, "mix");
    else if (component.getName().starts_with("test$"))
      return StringAttr::get(ctx, "test");
    else if (component.getName() == "Top")
      return StringAttr::get(ctx, "data");
    else
      assert(!Zhlt::isBufferComponent(component));
    return {};
  }
};

} // namespace

std::unique_ptr<mlir::OperationPass<mlir::ModuleOp>> createGenerateLayoutPass() {
  return std::make_unique<GenerateLayoutPass>();
}

} // namespace dsl
} // namespace zirgen
