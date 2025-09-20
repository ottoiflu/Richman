# tests/test_calculator_integration.py
import subprocess
import pytest
from conftest import EXECUTABLE_PATH # 导入路径


def run_c_program(input_data):
    process = subprocess.Popen(
        [EXECUTABLE_PATH],
        stdin=subprocess.PIPE,
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True
    )
    stdout, stderr = process.communicate(input=input_data)
    return stdout, stderr, process.returncode

@pytest.mark.parametrize("num1, num2, expected", [
    (5, 10, 15),
    (-5, 5, 0),
    (0, 0, 0)
])
def test_addition(num1, num2, expected):
    input_str = f"{num1}\n{num2}\n"
    stdout, stderr, exit_code = run_c_program(input_str)
    
    assert f"Result: {expected}" in stdout
    assert stderr == ""
    assert exit_code == 0