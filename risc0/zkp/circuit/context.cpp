#include "risc0/zkp/circuit/context.h"

namespace risc0 {

namespace {
Context* gContext;
}

void setGlobalContext(Context* context) {
  gContext = context;
}

Context* getGlobalContext() {
  return gContext;
}

} // namespace risc0
