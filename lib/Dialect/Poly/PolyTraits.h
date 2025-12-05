#ifndef LIB_DIALECT_POLY_POLYTRAITS_H
#define LIB_DIALECT_POLY_POLYTRAITS_H

#include "mlir/include/mlir/IR/OpDefinition.h"

namespace mlir::tutorial::poly {

template <typename ConcreteType>
class Has32BitArguments
    : public OpTrait::TraitBase<ConcreteType, Has32BitArguments> {
public:
  static LogicalResult verifyTrait(Operation *op) {
    for (auto type : op->getOperandTypes()) {
      // skip non-integer types
      if (!type.isIntOrIndex())
        continue;

      if (!type.isInteger(32)) {
        return op->emitError()
               << "requires each numeric operand to be a 32-bit integer";
      }
    }

    return success();
  }
};

} // namespace mlir::tutorial::poly

#endif /* LIB_DIALECT_POLY_POLYTRAITS_H */
