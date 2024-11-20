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

#include <fstream>
#include <iostream>

#include "risc0/core/elf.h"
#include "risc0/core/util.h"

#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"
#include "zirgen/Conversions/Typing/BuiltinComponents.h"
#include "zirgen/Conversions/Typing/ComponentManager.h"
#include "zirgen/Dialect/ZHLT/IR/Codegen.h"
#include "zirgen/Dialect/ZHLT/Transforms/Passes.h"
#include "zirgen/Dialect/ZStruct/IR/ZStruct.h"
#include "zirgen/Dialect/ZStruct/Transforms/Passes.h"
#include "zirgen/Dialect/Zll/IR/IR.h"
#include "zirgen/Dialect/Zll/IR/Interpreter.h"
#include "zirgen/Main/Main.h"
#include "zirgen/Main/RunTests.h"
#include "zirgen/compiler/codegen/codegen.h"
#include "zirgen/compiler/layout/viz.h"
#include "zirgen/dsl/lower.h"
#include "zirgen/dsl/parser.h"
#include "zirgen/dsl/passes/Passes.h"
#include "zirgen/dsl/stats.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/SourceMgr.h"

namespace cl = llvm::cl;
namespace codegen = zirgen::codegen;
namespace ZStruct = zirgen::ZStruct;

static cl::opt<std::string> inputFilename(cl::Positional,
                                          cl::desc("<input zirgen file>"),
                                          cl::value_desc("filename"),
                                          cl::Required);

namespace {
enum Action {
  None,
  PrintAST,
  PrintZHL,
  PrintZHLT,
  OptimizeZHLT,
  PrintZStruct,
  PrintStepFuncs,
  PrintLayoutType,
  PrintLayoutAttr,
  PrintRust,
  PrintCpp,
  PrintStats,
};
} // namespace

static cl::opt<enum Action> emitAction(
    "emit",
    cl::desc("The kind of output desired"),
    cl::values(
        clEnumValN(PrintAST, "ast", "output the AST"),
        clEnumValN(PrintZHL, "zhl", "output untyped high level Zirgen IR"),
        clEnumValN(PrintZHLT, "zhlt", "output typed high level Zirgen IR"),
        clEnumValN(OptimizeZHLT, "zhltopt", "output optimized high level IR"),
        clEnumValN(PrintZStruct, "zstruct", "output Zirgen IR after semantic lowering"),
        clEnumValN(PrintStepFuncs, "stepfuncs", "output IR after lowering to StepFuncOps"),
        clEnumValN(PrintLayoutType, "layouttype", "structure of circuit layout types as HTML"),
        clEnumValN(PrintLayoutAttr, "layoutattr", "content of generated layout attributes as text"),
        clEnumValN(PrintRust, "rust", "Output generated rust code"),
        clEnumValN(PrintCpp, "cpp", "Output generated cpp code"),
        clEnumValN(PrintStats, "stats", "Display statistics on generated circuit")));

static cl::list<std::string> includeDirs("I", cl::desc("Add include path"), cl::value_desc("path"));
static cl::opt<bool> doTest("test", cl::desc("Run tests for the main module"));
static cl::opt<bool> genValidity("validity",
                                 cl::desc("Generate validity polynomial evaluation functions"),
                                 cl::init(true));
static cl::opt<bool> inlineLayout("inline-layout",
                                  cl::desc("Inline layout into validity and check functions"),
                                  cl::init(false));
static cl::opt<size_t>
    maxDegree("max-degree", cl::desc("Maximum degree of validity polynomial"), cl::init(5));

void openMainFile(llvm::SourceMgr& sourceManager, std::string filename) {
  auto fileOrErr = llvm::MemoryBuffer::getFileOrSTDIN(filename);
  if (std::error_code error = fileOrErr.getError())
    sourceManager.PrintMessage(llvm::SMLoc(),
                               llvm::SourceMgr::DiagKind::DK_Error,
                               "could not open input file " + filename);
  sourceManager.AddNewSourceBuffer(std::move(*fileOrErr), mlir::SMLoc());
}

int main(int argc, char* argv[]) {
  llvm::InitLLVM y(argc, argv);

  zirgen::registerZirgenCommon();
  zirgen::registerRunTestsCLOptions();

  cl::ParseCommandLineOptions(argc, argv, "zirgen compiler\n");

  mlir::DialectRegistry registry;
  zirgen::registerZirgenDialects(registry);

  mlir::MLIRContext context(registry);
  context.loadAllAvailableDialects();

  llvm::SourceMgr sourceManager;
  sourceManager.setIncludeDirs(includeDirs);
  mlir::SourceMgrDiagnosticHandler sourceMgrHandler(sourceManager, &context);
  openMainFile(sourceManager, inputFilename);

  zirgen::dsl::Parser parser(sourceManager);
  parser.addPreamble(zirgen::Typing::getBuiltinPreamble());

  auto ast = parser.parseModule();
  if (!ast) {
    const auto& errors = parser.getErrors();
    for (const auto& error : errors) {
      sourceManager.PrintMessage(llvm::errs(), error);
    }
    llvm::errs() << "parsing failed with " << errors.size() << " errors\n";
    return 1;
  }

  if (emitAction == Action::PrintAST) {
    ast->print(llvm::outs());
    return 0;
  }

  std::optional<mlir::ModuleOp> zhlModule = zirgen::dsl::lower(context, sourceManager, ast.get());
  if (!zhlModule) {
    return 1;
  }

  if (emitAction == Action::PrintZHL) {
    zhlModule->print(llvm::outs());
    return 0;
  }

  std::optional<mlir::ModuleOp> typedModule = zirgen::Typing::typeCheck(context, zhlModule.value());
  if (!typedModule) {
    return 1;
  }

  mlir::PassManager pm(&context);
  applyDefaultTimingPassManagerCLOptions(pm);
  if (failed(applyPassManagerCLOptions(pm))) {
    llvm::errs() << "Pass manager does not agree with command line options.\n";
    return 1;
  }
  pm.enableVerifier(true);
  zirgen::addAccumAndGlobalPasses(pm);

  if (failed(pm.run(typedModule.value()))) {
    llvm::errs() << "an internal compiler error ocurred while type checking this module:\n";
    typedModule->print(llvm::errs());
    return 1;
  }

  if (emitAction == Action::PrintZHLT) {
    typedModule->print(llvm::outs());
    return 0;
  }

  pm.clear();
  // TODO: HoistAllocs is failing
  // pm.addPass(zirgen::Zhlt::createHoistAllocsPass());
  // TODO: Optimize layout is currently disabled to make layout of components
  // contigious for preflight, consider re-adding once preflight correctly uses
  // layout output.
  // pm.addPass(zirgen::ZStruct::createOptimizeLayoutPass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createCSEPass());
  if (failed(pm.run(typedModule.value()))) {
    llvm::errs() << "an internal error occurred while optimizing this module:\n";
    typedModule->print(llvm::errs());
    return 1;
  }

  if (emitAction == Action::OptimizeZHLT) {
    typedModule->print(llvm::outs());
    return 0;
  }

  pm.clear();
  if (!doTest)
    pm.addPass(zirgen::Zhlt::createStripTestsPass());
  zirgen::addTypingPasses(pm);

  pm.addPass(zirgen::dsl::createGenerateCheckPass());
  if (genValidity) {
    pm.addPass(zirgen::dsl::createGenerateTapsPass());
    pm.addPass(zirgen::dsl::createGenerateValidityRegsPass());
    pm.addPass(zirgen::dsl::createGenerateValidityTapsPass());
  }
  pm.addPass(zirgen::dsl::createElideTrivialStructsPass());
  pm.addPass(zirgen::ZStruct::createExpandLayoutPass());

  if (inlineLayout) {
    pm.nest<zirgen::Zhlt::CheckFuncOp>().addPass(zirgen::ZStruct::createInlineLayoutPass());
    if (genValidity) {
      pm.nest<zirgen::Zhlt::ValidityRegsFuncOp>().addPass(
          zirgen::ZStruct::createInlineLayoutPass());
      pm.nest<zirgen::Zhlt::ValidityTapsFuncOp>().addPass(
          zirgen::ZStruct::createInlineLayoutPass());
    }
  }

  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createSymbolDCEPass());

  if (genValidity && !doTest) {
    // TODO: Convert test framework to pass buffers as arguments
    pm.nest<zirgen::Zhlt::ValidityRegsFuncOp>().addPass(zirgen::ZStruct::createBuffersToArgsPass());
    pm.nest<zirgen::Zhlt::ValidityTapsFuncOp>().addPass(zirgen::ZStruct::createBuffersToArgsPass());
  }
  if (failed(pm.run(typedModule.value()))) {
    llvm::errs() << "an internal compiler error occurred while lowering this module:\n";
    typedModule->print(llvm::errs());
    return 1;
  }

  if (failed(zirgen::checkDegreeExceeded(*typedModule, maxDegree))) {
    llvm::errs() << "Degree exceeded; aborting\n";
    return 1;
  }

  if (emitAction == Action::PrintLayoutType) {
    if (auto topFunc = typedModule->lookupSymbol<zirgen::Zhlt::ExecFuncOp>("exec$Top")) {
      std::stringstream ss;
      mlir::Type lt = topFunc.getLayoutType();
      zirgen::layout::viz::layoutSizes(lt, ss);
      llvm::outs() << ss.str();
      return 0;
    } else {
      llvm::errs() << "error: circuit contains no component named `Top`\n";
      return 1;
    }
  } else if (emitAction == Action::PrintLayoutAttr) {
    std::stringstream ss;
    zirgen::layout::viz::layoutAttrs(*typedModule, ss);
    llvm::outs() << ss.str();
    return 0;
  } else if (emitAction == Action::PrintZStruct) {
    typedModule->print(llvm::outs());
    return 0;
  }

  if (emitAction == Action::PrintStats) {
    zirgen::dsl::printStats(*typedModule);
    return 0;
  }

  if (doTest) {
    return zirgen::runTests(*typedModule);
  }

  // To generate code for step functions, we copy our module, flatten step functions and move the
  // buffers to arguments.
  pm.clear();
  mlir::ModuleOp stepFuncs = typedModule->clone();
  // Privatize everything that we don't need, and make everything into step functions.
  pm.addPass(zirgen::Zhlt::createLowerStepFuncsPass());
  pm.addPass(zirgen::ZStruct::createBuffersToArgsPass());
  pm.addPass(mlir::createCanonicalizerPass());
  pm.addPass(mlir::createSymbolPrivatizePass(/*excludeSymbols=*/{"step$Top", "step$Top$accum"}));
  pm.addPass(mlir::createSymbolDCEPass());

  if (failed(pm.run(stepFuncs))) {
    llvm::errs() << "an internal compiler error occurred while lowering this module:\n";
    stepFuncs.print(llvm::errs());
    return 1;
  }

  if (emitAction == Action::PrintStepFuncs) {
    stepFuncs.print(llvm::outs());
    return 0;
  }

  if (emitAction == Action::PrintRust || emitAction == Action::PrintCpp) {
    codegen::CodegenOptions codegenOpts = (emitAction == Action::PrintRust)
                                              ? codegen::getRustCodegenOpts()
                                              : codegen::getCppCodegenOpts();
    zirgen::codegen::CodegenEmitter emitter(codegenOpts, &llvm::outs(), &context);
    if (zirgen::Zhlt::emitModule(stepFuncs, emitter).failed()) {
      llvm::errs() << "Failed to emit step functions\n";
      return 1;
    }

    for (auto& op : *typedModule) {
      if (llvm::isa<zirgen::Zhlt::ValidityRegsFuncOp, zirgen::Zhlt::ValidityTapsFuncOp>(op))
        emitter.emitTopLevel(&op);
    }
  }

  return 0;
}
