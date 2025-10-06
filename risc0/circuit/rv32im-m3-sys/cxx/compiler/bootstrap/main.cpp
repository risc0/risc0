#include "core/log.h"
#include "compiler/extractor/RecordingVal.h"
#include "rv32im/circuit/verify.h"
#include "rv32im/emu/blocks.h"

#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/Passes.h"

void emitTaps(const std::string path);
void emitPolyExt(const std::string path);

int main(int argc, char* argv[]) {
  if (argc != 2) {
    LOG(0, "usage: " << argv[0] << " <output_path>");
    return 1;
  }
  std::string path = argv[1];
  try {
    emitTaps(path + "/taps.rs");
    emitPolyExt(path + "/poly_ext.rs");
  } catch (const std::exception& err) {
    LOG(0, "Caught exception: " << err.what());
    return 1;
  }
  return 0;
}

