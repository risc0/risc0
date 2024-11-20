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

#include "mlir/Analysis/DataFlow/ConstantPropagationAnalysis.h"
#include "mlir/Analysis/DataFlow/DeadCodeAnalysis.h"
#include "mlir/Analysis/DataFlow/SparseAnalysis.h"
#include "zirgen/Dialect/ZHLT/IR/ZHLT.h"
#include "zirgen/Utilities/DataFlow.h"

// This analysis assigns an abstract representation of layout to values in the
// IR with layout types. These values are abstract in the sense that they do not
// contain actual buffer offsets, but they capture the nesting structure of the
// various layouts in a DAG. Note that these structures must be acyclic, because
// layout types cannot (recursively) contain themselves.

namespace zirgen {
namespace dsl {

// Define an abstract directed acyclic graph representing a layout. Each node in
// the graph represents a particular layout value within the IR, and there is an
// edge between two nodes if the second one is a direct sublayout of the first.
// Thus, each node knows the type of layout that it represents and has pointers
// to its sublayouts that can be traversed with subscripts and lookups just like
// concrete layouts. This data type uses reference semantics extensively; for
// example, all AbstractRegisters that contain base field elements are
// structurally equal, but are only guarunteed to refer to the same concrete
// register (i.e. have the same buffer offset) if they are the same object in
// memory.
struct LayoutDAG;

struct AbstractRegister {
  ZStruct::RefType type;
};

struct AbstractArray {
  ZStruct::LayoutArrayType type;
  SmallVector<std::shared_ptr<LayoutDAG>> elements;
};

struct AbstractStructure {
  ZStruct::LayoutType type;
  SmallVector<std::pair<StringAttr, std::shared_ptr<LayoutDAG>>> fields;
};

using LayoutDAGBase =
    std::variant<AbstractRegister, AbstractArray, AbstractStructure, std::shared_ptr<LayoutDAG>>;

struct LayoutDAG : public LayoutDAGBase {
  using Ptr = std::shared_ptr<LayoutDAG>;
  using LayoutDAGBase::LayoutDAGBase;

  // Follows a chain of references until reaching a reg, array, or structure
  const LayoutDAG& resolve() const;
  LayoutDAG& resolve() {
    return const_cast<LayoutDAG&>(const_cast<const LayoutDAG*>(this)->resolve());
  }

  // Returns the MLIR type of the layout this DAG represents
  Type getType() const;

  // Looks up the given member, assuming this holds an AbstractStructure
  Ptr lookup(StringAttr member);

  // Looks up the given subscript index, assuming this holds an AbstractArray
  Ptr subscript(size_t index);

  // generate an abstract (i.e. without offsets) representation of the given
  // layout type, ignoring aliases
  static Ptr generateNaiveAbstractLayout(Type type);

  // Perform logic programming-esque unification on the two given dags
  static LogicalResult unify(Ptr lhs, Ptr rhs);

  // Constructs a deep copy of this DAG, such that the result is structurally
  // equal but contains none of the same pointers (recursively)
  static Ptr clone(Ptr layout);
};

raw_ostream& operator<<(raw_ostream& os, const LayoutDAG& layout);

struct LayoutDAGValue : public LatticeValue<LayoutDAG::Ptr, LayoutDAGValue> {
  using LatticeValue::LatticeValue;
  explicit LayoutDAGValue(LayoutDAG layout) : LatticeValue(std::make_shared<LayoutDAG>(layout)) {}

  static LayoutDAGValue join(const LayoutDAGValue& lhs, const LayoutDAGValue& rhs) {
    if (lhs.isUninitialized()) {
      return rhs;
    } else if (rhs.isUninitialized()) {
      return lhs;
    } else if (lhs == rhs) {
      return lhs;
    } else {
      if (failed(LayoutDAG::unify(lhs.get(), rhs.get())))
        return Overdefined{};
      else
        return lhs;
    }
  }
};

// A data flow analysis that assigns values in the IR with LayoutDAGs
// representing their layouts. Note that constructor calls get
// layouts relative to the enclosing component's layout parameter, if possible.
class LayoutDAGAnalysis : public OperationDataflowAnalysis {
public:
  using Element = mlir::dataflow::Lattice<LayoutDAGValue>;

  LayoutDAGAnalysis(DataFlowSolver& solver) : OperationDataflowAnalysis(solver) {
    // In order to resolve subscript indices, this analysis uses sparse constant
    // propagation, which in turn depends on dead code analysis.
    solver.load<mlir::dataflow::DeadCodeAnalysis>();
    solver.load<mlir::dataflow::SparseConstantPropagation>();
  }

private:
  void visitOperation(Operation* op) override;
  void visitOp(ZStruct::AliasLayoutOp op);
  void visitOp(ZStruct::LookupOp op);
  void visitOp(ZStruct::SubscriptOp op);
  void visitOp(ZStruct::LayoutArrayOp op);
  void visitOp(Zhlt::CheckLayoutFuncOp op);
};

} // namespace dsl
} // namespace zirgen
