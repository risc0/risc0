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

#include "zirgen/dsl/Analysis/LayoutDAGAnalysis.h"
#include "mlir/Analysis/CallGraph.h"
#include "zirgen/Dialect/ZHLT/IR/TypeUtils.h"
#include "llvm/ADT/SCCIterator.h"
#include "llvm/ADT/TypeSwitch.h"

namespace zirgen {
namespace dsl {

using namespace mlir;
using namespace dataflow;
using namespace Zhlt;
using namespace ZStruct;

// LayoutDAG

raw_ostream& operator<<(raw_ostream& os, const LayoutDAG& layout) {
  return os << "<LayoutDAG at " << &layout << ">";
}

const LayoutDAG& LayoutDAG::resolve() const {
  const LayoutDAG* layout = this;
  while (const auto* ptr = std::get_if<LayoutDAG::Ptr>(layout))
    layout = ptr->get();
  return *layout;
}

Type LayoutDAG::getType() const {
  if (auto* reg = std::get_if<AbstractRegister>(this)) {
    return reg->type;
  } else if (auto* arr = std::get_if<AbstractArray>(this)) {
    return arr->type;
  } else if (auto* str = std::get_if<AbstractStructure>(this)) {
    return str->type;
  } else if (auto* ref = std::get_if<LayoutDAG::Ptr>(this)) {
    return (*ref)->getType();
  } else {
    llvm_unreachable("unhandled case");
    return Type();
  }
}

LayoutDAG::Ptr LayoutDAG::lookup(StringAttr member) {
  const LayoutDAG& layout = resolve();
  const auto& base = std::get<AbstractStructure>(layout);
  for (auto field : base.fields) {
    if (field.first == member)
      return field.second;
  }
  llvm_unreachable("missing member of abstract struct");
  return nullptr;
}

LayoutDAG::Ptr LayoutDAG::subscript(size_t index) {
  const LayoutDAG& layout = resolve();
  const auto& base = std::get<AbstractArray>(layout);
  return base.elements[index];
}

LayoutDAG::Ptr LayoutDAG::generateNaiveAbstractLayout(Type type) {
  LayoutDAG result =
      TypeSwitch<Type, LayoutDAG>(type)
          .Case<RefType>([&](auto type) { return AbstractRegister{type}; })
          .Case<LayoutArrayType>([&](auto type) {
            SmallVector<Ptr> elements;
            for (size_t i = 0; i < type.getSize(); i++) {
              elements.push_back(generateNaiveAbstractLayout(type.getElement()));
            }
            return AbstractArray{type, elements};
          })
          .Case<LayoutType>([&](auto type) {
            SmallVector<std::pair<StringAttr, Ptr>> fields;
            for (FieldInfo field : type.getFields()) {
              fields.emplace_back(field.name, generateNaiveAbstractLayout(field.type));
            }
            return AbstractStructure{type, fields};
          });
  return std::make_shared<LayoutDAG>(result);
}

LogicalResult LayoutDAG::unify(Ptr lhs, Ptr rhs) {
  auto& lhsResolved = lhs->resolve();
  auto& rhsResolved = rhs->resolve();
  assert(lhsResolved.getType() == rhsResolved.getType());

  // A layout trivially unifies with itself
  if (&lhsResolved == &rhsResolved)
    return success();

  // Different kinds of layouts cannot unify
  if (lhsResolved.index() != rhsResolved.index())
    return failure();

  if (std::holds_alternative<AbstractRegister>(lhsResolved) &&
      std::holds_alternative<AbstractRegister>(rhsResolved)) {
    rhsResolved = LayoutDAG(lhs);
  } else if (auto* lhsArr = std::get_if<AbstractArray>(&lhsResolved);
             auto* rhsArr = std::get_if<AbstractArray>(&rhsResolved)) {
    for (size_t i = 0; i < lhsArr->elements.size(); i++) {
      if (failed(unify(lhsArr->elements[i], rhsArr->elements[i])))
        return failure();
    }
  } else if (auto* lhsStr = std::get_if<AbstractStructure>(&lhsResolved);
             auto* rhsStr = std::get_if<AbstractStructure>(&rhsResolved)) {
    for (size_t i = 0; i < lhsStr->fields.size(); i++) {
      assert(lhsStr->fields[i].first == rhsStr->fields[i].first);
      if (failed(unify(lhsStr->fields[i].second, rhsStr->fields[i].second)))
        return failure();
    }
  } else {
    llvm_unreachable("unhandled case");
    return failure();
  }
  return success();
}

namespace {

using Memo = std::map<LayoutDAG::Ptr, LayoutDAG::Ptr>;

LayoutDAG::Ptr clone_helper(LayoutDAG::Ptr layout, Memo& memo) {
  if (memo.count(layout))
    return memo.at(layout);

  LayoutDAG::Ptr result;
  if (auto* reg = std::get_if<AbstractRegister>(layout.get())) {
    result = std::make_shared<LayoutDAG>(*reg);
  } else if (auto* arr = std::get_if<AbstractArray>(layout.get())) {
    SmallVector<LayoutDAG::Ptr> elements;
    for (auto element : arr->elements)
      elements.push_back(clone_helper(element, memo));
    result = std::make_shared<LayoutDAG>(AbstractArray{arr->type, elements});
  } else if (auto* str = std::get_if<AbstractStructure>(layout.get())) {
    SmallVector<std::pair<StringAttr, LayoutDAG::Ptr>> fields;
    for (auto field : str->fields)
      fields.emplace_back(field.first, clone_helper(field.second, memo));
    result = std::make_shared<LayoutDAG>(AbstractStructure{str->type, fields});
  } else if (auto* ref = std::get_if<LayoutDAG::Ptr>(layout.get())) {
    result = std::make_shared<LayoutDAG>(clone_helper(*ref, memo));
  } else {
    llvm_unreachable("unhandled case");
    return nullptr;
  }
  memo[layout] = result;
  return result;
}

} // namespace

LayoutDAG::Ptr LayoutDAG::clone(Ptr layout) {
  Memo memo;
  return clone_helper(layout, memo);
}

// LayoutDAGAnalysis

void LayoutDAGAnalysis::visitOperation(Operation* op) {
  TypeSwitch<Operation*>(op)
      .Case<AliasLayoutOp, LookupOp, SubscriptOp, LayoutArrayOp, CheckLayoutFuncOp>(
          [&](auto op) { visitOp(op); });
}

void LayoutDAGAnalysis::visitOp(AliasLayoutOp op) {
  // AliasLayoutOp has no results, so we need to add an explicit dependence on
  // op so that we revisit once lhs and rhs both have their lattice points
  const auto& lhs = getOrCreateFor<Element>(op, op.getLhs())->getValue();
  const auto& rhs = getOrCreateFor<Element>(op, op.getRhs())->getValue();
  if (lhs.isDefined() && rhs.isDefined()) {
    assert(succeeded(LayoutDAG::unify(lhs.get(), rhs.get())));
  } else {
    auto diag = op.emitWarning() << "Failed to make layouts properly alias";
    diag.attachNote(op.getLhs().getLoc()) << "first aliased layout:";
    diag.attachNote(op.getRhs().getLoc()) << "second aliased layout:";
  }
}

void LayoutDAGAnalysis::visitOp(LookupOp op) {
  // [[ base.member ]] := [[ base ]].member
  if (isa<LayoutType>(op.getBase().getType())) {
    const auto* baseLayout = getOrCreateFor<Element>(op.getOut(), op.getBase());
    if (baseLayout->getValue().isDefined()) {
      LayoutDAG::Ptr sublayout = baseLayout->getValue().get()->lookup(op.getMemberAttr());
      auto* lattice = getOrCreate<Element>(op.getOut());
      propagateIfChanged(lattice, lattice->join(sublayout));
    }
  }
}

void LayoutDAGAnalysis::visitOp(SubscriptOp op) {
  // [[ base[index] ]] := [[ layout(base) ]][index]
  if (isa<LayoutArrayType>(op.getBase().getType())) {
    const auto* baseLayout = getOrCreateFor<Element>(op.getOut(), op.getBase());
    ConstantValue indexValue =
        getOrCreateFor<Lattice<ConstantValue>>(op.getOut(), op.getIndex())->getValue();
    if (baseLayout->getValue().isDefined() && !indexValue.isUninitialized()) {
      Attribute indexAttr = indexValue.getConstantValue();
      if (!indexAttr)
        return;
      size_t index = extractIntAttr(indexAttr);
      LayoutDAG::Ptr sublayout = baseLayout->getValue().get()->subscript(index);
      auto* lattice = getOrCreate<Element>(op.getOut());
      propagateIfChanged(lattice, lattice->join(sublayout));
    }
  }
}

void LayoutDAGAnalysis::visitOp(LayoutArrayOp op) {
  // [[ [a, ..., z] ]] := [[[ a ]], ..., [[ z ]]]
  SmallVector<LayoutDAG::Ptr> elements;
  for (Value element : op.getElements()) {
    auto subLattice = getOrCreateFor<Element>(op.getOut(), element)->getValue();
    if (!subLattice.isDefined())
      return;
    elements.push_back(subLattice.get());
  }
  auto updated = std::make_shared<LayoutDAG>(AbstractArray{op.getResult().getType(), elements});
  auto* lattice = getOrCreate<Element>(op.getOut());
  propagateIfChanged(lattice, lattice->join(updated));
}

void LayoutDAGAnalysis::visitOp(CheckLayoutFuncOp op) {
  // Generate the DAG for the layout parameter naively from the type. It will be
  // refined by subsequent analysis to include the appropriate aliases.
  if (op.getLayout()) {
    auto* lattice = getOrCreate<Element>(op.getLayout());
    // There's no point in generating the naive layout more than once
    if (!lattice->getValue().isDefined()) {
      auto naiveLayout = LayoutDAG::generateNaiveAbstractLayout(op.getLayoutType());
      propagateIfChanged(lattice, lattice->join(naiveLayout));
    }
  }
}

} // namespace dsl
} // namespace zirgen
