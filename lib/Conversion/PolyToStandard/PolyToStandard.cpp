#include "lib/Conversion/PolyToStandard/PolyToStandard.h"

#include "lib/Dialect/Poly/PolyDialect.h"
#include "lib/Dialect/Poly/PolyOps.h"
#include "lib/Dialect/Poly/PolyTypes.h"
#include "mlir/Dialect/Arith/IR/Arith.h"
#include "mlir/Dialect/SCF/IR/SCF.h" // from @llvm-project
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/PatternMatch.h"
#include "mlir/include/mlir/Dialect/Func/IR/FuncOps.h" // from @llvm-project
#include "mlir/include/mlir/Dialect/Func/Transforms/FuncConversions.h" // from @llvm-project
#include "mlir/include/mlir/IR/ImplicitLocOpBuilder.h" // from @llvm-project
#include "mlir/include/mlir/Transforms/DialectConversion.h" // from @llvm-project
#include "llvm/Support/LogicalResult.h"
#include "llvm/include/llvm/ADT/SmallVector.h" // from @llvm-project

namespace mlir {
namespace tutorial {
namespace poly {

#define GEN_PASS_DEF_POLYTOSTANDARD
#include "lib/Conversion/PolyToStandard/PolyToStandard.h.inc"

class PolyToStandardTypeConvert : public TypeConverter {
public:
  PolyToStandardTypeConvert(MLIRContext *ctx) {
    addConversion([](Type type) { return type; });
    addConversion([ctx](PolynomialType type) -> Type {
      int degreeBound = type.getDegreeBound();
      IntegerType elementTy =
          IntegerType::get(ctx, 32, IntegerType::SignednessSemantics::Signless);
      return RankedTensorType::get({degreeBound}, elementTy);
    });
  }
};

struct ConvertAdd : public OpConversionPattern<AddOp> {
  ConvertAdd(mlir::MLIRContext *context)
      : OpConversionPattern<AddOp>(context) {}

  using OpConversionPattern::OpConversionPattern;

  LogicalResult
  matchAndRewrite(AddOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    arith::AddIOp addOp = rewriter.create<arith::AddIOp>(
        op.getLoc(), adaptor.getLhs(), adaptor.getRhs());
    rewriter.replaceOp(op, addOp);
    return success();
  }
};

struct ConvertSub : public OpConversionPattern<SubOp> {
  ConvertSub(mlir::MLIRContext *context)
      : OpConversionPattern<SubOp>(context) {}

  using OpConversionPattern::OpConversionPattern;

  LogicalResult
  matchAndRewrite(SubOp op, OpAdaptor adaptor,
                  ConversionPatternRewriter &rewriter) const override {
    arith::SubIOp subOp = rewriter.create<arith::SubIOp>(
        op.getLoc(), adaptor.getLhs(), adaptor.getRhs());
    rewriter.replaceOp(op.getOperation(), subOp);
    return success();
  }
};

struct PolyToStandard : impl::PolyToStandardBase<PolyToStandard> {
  using PolyToStandardBase::PolyToStandardBase;

  void runOnOperation() override {
    MLIRContext *context = &getContext();
    auto *module = getOperation();

    // TODO: implement pass
    ConversionTarget target(*context);
    target.addLegalDialect<arith::ArithDialect>();
    target.addIllegalDialect<PolyDialect>();

    RewritePatternSet patterns(context);
    PolyToStandardTypeConvert typeConverter(context);
    patterns.add<ConvertAdd, ConvertSub>(typeConverter, context);

    populateFunctionOpInterfaceTypeConversionPattern<func::FuncOp>(
        patterns, typeConverter);
    target.addDynamicallyLegalOp<func::FuncOp>([&](func::FuncOp op) {
      return typeConverter.isSignatureLegal(op.getFunctionType()) &&
             typeConverter.isLegal(&op.getBody());
    });

    if (failed(applyPartialConversion(module, target, std::move(patterns)))) {
      signalPassFailure();
    }
  }
};

} // namespace poly
} // namespace tutorial
} // namespace mlir