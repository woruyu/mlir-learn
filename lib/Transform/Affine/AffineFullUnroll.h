#ifndef LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLL_H
#define LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLL_H

#include "mlir/Pass/Pass.h"

namespace mlir {
namespace tutorial {

#define GEN_PASS_DECL_AFFINEFULLUNROLL
#include "lib/Transform/Affine/Passes.h.inc"

} // namespace tutorial
} // namespace mlir

#endif /* LIB_TRANSFORM_AFFINE_AFFINEFULLUNROLL_H */
