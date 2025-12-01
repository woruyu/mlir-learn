#ifndef LIB_DIALECT_POLY_POLYTYPES_H
#define LIB_DIALECT_POLY_POLYTYPES_H

// Required because the .h.inc file refers to MLIR classes and does not itself
// have any includes.
#include "mlir/include/mlir/IR/DialectImplementation.h"

#define GET_TYPEDEF_CLASSES
#include "lib/Dialect/Poly/PolyTypes.h.inc"

#endif /* LIB_DIALECT_POLY_POLYTYPES_H */
