import os
from pathlib import Path
from lit.formats import ShTest

config.name = "mlir_learn"
config.test_format = ShTest()
config.suffixes = [".mlir"]

config.test_source_root = os.path.dirname(os.path.abspath(__file__))

config.test_exec_root = config.test_source_root

build_bin = "/home/asus/github/mlir-learn/build/tools"
fileCheck_bin = "/home/asus/github/llvm-project/build_tutor/bin"
config.environment["PATH"] = fileCheck_bin + ":" + build_bin + ":" + os.environ.get("PATH", "")

# 替换 %project_source_dir -> 仓库根目录（tests 的上一级）
project_root = Path(config.test_source_root).parent
substitutions = {
    "%project_source_dir": str(project_root),
}
config.substitutions.extend(substitutions.items())
