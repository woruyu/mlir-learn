include "mlir/Pass/PassBase.td"

def MulToAdd : Pass<"mul-to-add"> {
  let summary = "Convert multiplications to repeated additions";
  let description = [{
    Convert multiplications to repeated additions.
  }];
}
