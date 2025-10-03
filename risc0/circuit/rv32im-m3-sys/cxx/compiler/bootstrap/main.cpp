#include "core/log.h"
#include "compiler/extractor/RecordingVal.h"
#include "rv32im/circuit/verify.h"
#include "rv32im/emu/blocks.h"

using namespace mlir;
using namespace zirgen::Zll;

struct TrivialRecordingReg {
  Value val;
  TrivialRecordingReg(Value val) : val(val) {}
  template<typename T, typename C> void applyInner(C& ctx) {}
  template<typename C> void applyInner(C& ctx) {}
  template<typename C> void verify(C& ctx) {}
  template<typename C> void addArguments(C& ctx) {}
  RecordingVal get() { return RecordingVal(val); }
};

static Type getBufType(MLIRContext& ctx, uint32_t deg, uint32_t size, BufferKind kind) {
  return BufferType::get(&ctx, ValType::get(&ctx, kFieldPrimeDefault, deg), size, kind); 
}

static std::vector<TrivialRecordingReg> makeRegs(Value buffer, size_t back) {
  std::vector<TrivialRecordingReg> ret;
  OpBuilder& builder = *BuilderSingleton::get();
  size_t size = mlir::dyn_cast<BufferType>(buffer.getType()).getSize();
  for (size_t i = 0; i < size; i++) {
    Value val = builder.create<GetOp>(builder.getUnknownLoc(), buffer, i, back, IntegerAttr());
    ret.emplace_back(val);
  }
  return ret;
}

template<typename T>
static std::vector<T> makeGlobals(Value buffer) {
  std::vector<T> ret;
  OpBuilder& builder = *BuilderSingleton::get();
  size_t size = mlir::dyn_cast<BufferType>(buffer.getType()).getSize();
  for (size_t i = 0; i < size; i++) {
    Value val = builder.create<GetGlobalOp>(builder.getUnknownLoc(), buffer, i);
    ret.emplace_back(val);
  }
  return ret;
}


int main() {
  MLIRContext mlirCtx;
  mlirCtx.getOrLoadDialect<zirgen::Zll::ZllDialect>();
  OpBuilder builder(&mlirCtx);
  auto loc = builder.getUnknownLoc();
  auto moduleOp = mlir::ModuleOp::create(loc);
  builder.setInsertionPointToEnd(moduleOp.getBody());
  BuilderSingleton::set(&builder);
  std::vector<Type> inTypes;
  std::vector<Type> outTypes;
  uint32_t dataSize = risc0::rv32im::computeMaxDataPerRow();
  uint32_t accumSize = risc0::rv32im::computeTotalAccum();
  inTypes.push_back(getBufType(mlirCtx, 1, dataSize, BufferKind::Constant));
  inTypes.push_back(getBufType(mlirCtx, 1, accumSize, BufferKind::Constant));
  inTypes.push_back(getBufType(mlirCtx, 1, NUM_GLOBALS, BufferKind::Global));
  inTypes.push_back(getBufType(mlirCtx, 4, ACCUM_MIX_SIZE, BufferKind::Global));
  inTypes.push_back(ValType::get(&mlirCtx, kFieldPrimeDefault, 4));
  inTypes.push_back(ValType::get(&mlirCtx, kFieldPrimeDefault, 1));
  outTypes.push_back(ValType::get(&mlirCtx, kFieldPrimeDefault, 4));
  auto funcType = FunctionType::get(&mlirCtx, inTypes, outTypes);
  auto func = builder.create<func::FuncOp>(loc, "verify", funcType);
  builder.setInsertionPointToStart(func.addEntryBlock());
  auto data = makeRegs(func.getArgument(0), 0);
  auto accum = makeRegs(func.getArgument(1), 0);
  auto prevAccum = makeRegs(func.getArgument(1), 1);
  auto globals = makeGlobals<RecordingVal>(func.getArgument(2));
  auto accumMix = makeGlobals<RecordingValExt>(func.getArgument(3));
  auto ecMix = RecordingValExt(func.getArgument(4));
  auto x  = RecordingVal(func.getArgument(5));
  auto ret = verifyCircuit<TrivialRecordingReg, RecordingVal, RecordingValExt>(
      data.data(),
      accum.data(),
      prevAccum.data(),
      globals.data(),
      accumMix.data(),
      ecMix,
      x);
  builder.create<func::ReturnOp>(loc, ret.value);
  moduleOp.print(llvm::errs());
}
