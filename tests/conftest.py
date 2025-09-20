# tests/conftest.py
import pytest
import subprocess
import os

# 定义可执行文件的路径（与 Makefile 中保持一致）
EXECUTABLE_PATH = "./bin/app"

@pytest.fixture(scope="session", autouse=True)
def compile_c_program_with_make():
    """
    一个在测试会话开始时运行 `make`，在结束时运行 `make clean` 的 Fixture。
    """
    # 1. 设置：运行 make 命令
    print("\nRunning 'make'...")
    make_process = subprocess.run(["make"], capture_output=True, text=True)
    if make_process.returncode != 0:
        pytest.fail(f"'make' command failed:\n{make_process.stderr}", pytrace=False)

    # 检查可执行文件是否存在
    if not os.path.exists(EXECUTABLE_PATH):
        pytest.fail(f"Executable '{EXECUTABLE_PATH}' not found after running make.", pytrace=False)
        
    yield # 运行测试
    
    # 2. 清理：运行 make clean 命令
    print(f"\nRunning 'make clean'...")
    subprocess.run(["make", "clean"])