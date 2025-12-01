#include "lib/Transform/Affine/AffineFullUnroll.h"
#include "mlir/Dialect/Affine/IR/AffineOps.h"
#include "mlir/Dialect/Affine/LoopUtils.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/Transforms/GreedyPatternRewriteDriver.h"
#include "mlir/include/mlir/Pass/Pass.h"
#include "llvm/Support/LogicalResult.h"

namespace mlir {
namespace tutorial {

#define GEN_PASS_DEF_AFFINEFULLUNROLL
#include "lib/Transform/Affine/Passes.h.inc"

using mlir::affine::AffineForOp;
using mlir::affine::loopUnrollFull;

struct AffineFullUnroll : impl::AffineFullUnrollBase<AffineFullUnroll>{
  using AffineFullUnrollBase::AffineFullUnrollBase;

  void runOnOperation() {
    getOperation()->walk([&](AffineForOp op) {
      if (failed(loopUnrollFull(op))) {
        op.emitError("unrolling failed");
        signalPassFailure();
      }
    });
  }
};

} // namespace tutorial
} // namespace mlir
