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

#ifndef ZIRGEN_PASSES
#define ZIRGEN_PASSES

include "mlir/Pass/PassBase.td"
include "mlir/Rewrite/PassUtil.td"

def EraseUnusedAspects : Pass<"erase-unused-aspects", "mlir::ModuleOp"> {
  let summary = "Removes aspects that aren't necessary for tests or codegen";
  let constructor = "zirgen::dsl::createEraseUnusedAspectsPass()";
  let dependentDialects = ["zirgen::Zhlt::ZhltDialect"];
  let options = [
    Option<"forTests", "for-tests", "bool", /*default=*/"false", "leave only aspects for tests (rather than codegen)">
  ];
}

def GenerateExec : Pass<"generate-exec", "mlir::ModuleOp"> {
  let summary = "Lowers the ZHLT dialect to produce circuit execution functions";
  let description = [{
    Generates execution functions for all components present and adds them to the module.
    Each generated function takes two arguments:
     * A Value specifying how many cycles back the component should be retrieved at
     * The component's layout.
    This function returns the component's value at the given number of cycles in the past.
  }];

  let constructor = "zirgen::dsl::createGenerateExecPass()";
  let dependentDialects = ["zirgen::ZStruct::ZStructDialect"];
}

def GenerateBack : Pass<"generate-back", "mlir::ModuleOp"> {
  let summary = "Lowers the ZHLT dialect to produce functions to evaluate `back' operations";
  let description = [{
    Generates back retrieval functions for all components present and adds them to the module.
    Each generated function has the same function type as the zhlt.component operation:
    Constructor inputs and its layout.

    It populates any registers in the layout, and returns the value of the component.
  }];
  let constructor = "zirgen::dsl::createGenerateBackPass()";
  let dependentDialects = ["zirgen::ZStruct::ZStructDialect"];
}

def GenerateCheckLayout : Pass<"generate-check-layout", "mlir::ModuleOp"> {
  let summary = "Lowers the ZHLT dialect to produce functions to check layout constraints";
  let description = [{
    Generates layout constraint checks (zstruct.alias_layout) for all circuit entry points and adds
    them to the module. Each generated function takes the same layout type as the entry point and
    returns nothing.

    The generated function has all of its callees inlined.
  }];
  let constructor = "zirgen::dsl::createGenerateCheckLayoutPass()";
  let dependentDialects = ["zirgen::ZStruct::ZStructDialect"];
}

def GenerateCheck : Pass<"generate-check", "mlir::ModuleOp"> {
  let summary = "Lowers the ZHLT dialect to produce functions to check constraints";
  let description = [{
    Generates constraint checks (zirgen.eqz) for all components present and adds them to the module.
    Each generated function takes the same arguments and has the same return type as the "exec"
    function, but only checks constraints without storing values in any registers.

    The generated function has all of its callees inlined.
  }];
  let constructor = "zirgen::dsl::createGenerateCheckPass()";
  let dependentDialects = ["zirgen::ZStruct::ZStructDialect"];
}

def GenerateTaps : Pass<"generate-taps", "mlir::ModuleOp"> {
  let summary = "Generates a list of taps as register references.";
  let description = [{
    Analyzes the check function and generates an array of the taps needed.
  }];
  let constructor = "zirgen::dsl::createGenerateTapsPass()";
  let dependentDialects = ["zirgen::ZStruct::ZStructDialect"];
}

def GenerateLayout : Pass<"generate-layout", "mlir::ModuleOp"> {
  let summary = "Generates layout constructors for all zstruct components";
  let description = [{
    Generates layout creation functions for all components present and adds them to the module.
    Each generated function returns the component's layout type, and uses zirgen.alloc_reg to
    generate values for any "Ref" types needed to construct the layout.
  }];
  let constructor = "zirgen::dsl::createGenerateLayoutPass()";
  let dependentDialects = ["zirgen::ZStruct::ZStructDialect"];
}

def GenerateValidityRegs : Pass<"generate-validity-regs", "mlir::ModuleOp"> {
  let summary = "Generates validity polynomial evaluation functions on reigsters";
  let description = [{
    Generates validity polynomial evaluation functions for all
    components present and adds them to the module.  Each generated
    function takes an initial mix state as input and a layout, and
    mixes in all constraints present.
  }];
  let constructor = "zirgen::dsl::createGenerateValidityRegsPass()";
  let dependentDialects = ["zirgen::ZStruct::ZStructDialect"];
}

def GenerateValidityTaps : Pass<"generate-validity-taps", "mlir::ModuleOp"> {
  let summary = "Generates validity polynomial evaluation functions on taps";
  let description = [{
    Generates validity polynomial evaluation functions for all
    components present and adds them to the module.  Each generated
    function takes an initial mix state as input and a buffer of taps,
    and mixes in all constraints present.
  }];
  let constructor = "zirgen::dsl::createGenerateValidityTapsPass()";
  let dependentDialects = ["zirgen::ZStruct::ZStructDialect"];
}

def GenerateAccum : Pass<"generate-accum", "mlir::ModuleOp"> {
  let summary = "Generates code that evaluates all accum columns for a module";
  let description = [{
    Identifies the major mux of a circuit (if any), collects all of
    the arguments it contains, allocates accum registers for them, and
    generates an evaluation function to compute a LogUp-style grand sum.
  }];
  let constructor = "zirgen::dsl::createGenerateAccumPass()";
  let dependentDialects = ["zirgen::ZStruct::ZStructDialect"];
}

def GenerateGlobals : Pass<"generate-globals", "mlir::ModuleOp"> {
  let summary = "Generates a component for all globals referenced in the module";
  let constructor = "zirgen::dsl::createGenerateGlobalsPass()";
  let dependentDialects = ["zirgen::Zhlt::ZhltDialect"];
}

def ElideTrivialStructs : Pass<"elide-trivial-structs", "mlir::ModuleOp"> {
  let summary = "Removes trivial structures with just a @super member";
  let constructor = "zirgen::dsl::createElideTrivialStructsPass()";
  let dependentDialects = ["zirgen::ZStruct::ZStructDialect"];
}

def InlinePure : Pass<"inline-pure", "mlir::ModuleOp"> {
  let summary = "Inline pure functions and operations without layouts";
  let constructor = "zirgen::dsl::createInlinePurePass()";
}

def FieldDCE : Pass<"field-dce", "mlir::ModuleOp"> {
  let summary = "Remove unused structure fields";
  let constructor = "zirgen::dsl::createFieldDCEPass()";
}

def HoistInvariants : Pass<"hoist-invariants", "mlir::ModuleOp"> {
  let summary = "Hoist invariants outside of control structures like if, switch, map, etc.";
  let constructor = "zirgen::dsl::createHoistInvariantsPass()";
}

def TopologicalShuffle : Pass<"topological-shuffle"> {
  let summary = "Reverse blocks, then topologically sort";
  let constructor = "zirgen::dsl::createTopologicalShufflePass()";
}

#endif // ZIRGEN_PASSES
