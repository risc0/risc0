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

#include "zirgen/dsl/passes/CommonRewrites.h"

namespace zirgen {

/// Remap locations from the inlined blocks with CallSiteLoc locations with the
/// provided caller location.  Copied from mlir's InliningUtils.
void remapInlinedLocations(iterator_range<Region::iterator> inlinedBlocks, Location callerLoc) {
  DenseMap<Location, Location> mappedLocations;
  auto remapOpLoc = [&](Operation* op) {
    auto it = mappedLocations.find(op->getLoc());
    if (it == mappedLocations.end()) {
      Location newLoc = op->getLoc();
      if (newLoc != callerLoc) {
        newLoc = CallSiteLoc::get(op->getLoc(), callerLoc);
      }
      it = mappedLocations.try_emplace(op->getLoc(), newLoc).first;
    }
    op->setLoc(it->second);
  };
  for (auto& block : inlinedBlocks)
    block.walk(remapOpLoc);
}

LogicalResult InlineCalls::matchAndRewrite(CallOpInterface callOp,
                                           PatternRewriter& rewriter) const {
  auto callable = callOp.getCallableForCallee();
  if (!callable)
    return rewriter.notifyMatchFailure(callOp, "Not a callable");
  if (!llvm::isa<SymbolRefAttr>(callable))
    return rewriter.notifyMatchFailure(callOp, "Callable isn't a symbol");
  auto callee = SymbolTable::lookupNearestSymbolFrom<CallableOpInterface>(
      callOp, llvm::cast<SymbolRefAttr>(callable));
  if (!callee)
    return rewriter.notifyMatchFailure(callOp, "Can't find callee with Callable interface");

  if (callOp.getArgOperands().getTypes() != callee.getArgumentTypes()) {
    return rewriter.notifyMatchFailure(callOp, "Argument type mismatch");
  }

  IRMapping mapping;
  Region clonedBody;
  callee.getCallableRegion()->cloneInto(&clonedBody, mapping);
  remapInlinedLocations(clonedBody.getBlocks(), callOp.getLoc());
  Block* block = &clonedBody.front();
  auto returnOp = block->getTerminator();
  if (!returnOp->hasTrait<OpTrait::ReturnLike>())
    return rewriter.notifyMatchFailure(callOp, "Callee missing return operation");

  rewriter.inlineBlockBefore(block, callOp, callOp.getArgOperands());
  rewriter.replaceOp(callOp, returnOp->getOperands());
  rewriter.eraseOp(returnOp);

  return success();
}

} // namespace zirgen
