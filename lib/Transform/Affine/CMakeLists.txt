add_mlir_library(AffineFullUnroll
    AffineFullUnroll.cpp
    AffineFullUnrollPatternRewrite.cpp

    DEPENDS
    MLIRAffineFullUnrollPasses
)

set(LLVM_TARGET_DEFINITIONS Passes.td)
mlir_tablegen(Passes.h.inc -gen-pass-decls -name Affine)
add_public_tablegen_target(MLIRAffineFullUnrollPasses)
add_mlir_doc(Passes AffinePasses ./ -gen-pass-doc)
