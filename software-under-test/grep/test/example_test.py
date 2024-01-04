"""
Author: Radon
Date: 2023-12-21 16:15:08
LastEditors: Radon
LastEditTime: 2023-12-21 18:01:48
Description: Hi, say something
"""
import unittest
import os

from parameterized import parameterized

# GLOBAL VARIABLES
GREP_PATH = os.path.join(os.path.dirname(__file__), "..", "src", "grep-3.11", "obj-temp", "src", "grep")


def load_test_cases() -> list:
    tc_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")  # 文件系统中存储所有测试用例的根目录
    dirs = [os.path.join(tc_dir, dir) for dir in os.listdir(tc_dir)]  # 存储了测试用例文件路径的列表
    testcases = list()  # 用于存储所有测试用例的列表

    # 遍历存储了测试用例的文件夹, 读取测试用例的内容
    for dir in dirs:
        pattern_path = os.path.join(dir, "pattern.txt")

        # 获取要进行搜索的文本路径
        text_path = os.path.join(dir, "text.txt")

        # 读取搜索项的内容
        with open(pattern_path) as f:
            pattern = f.readline().rstrip("\n")

        testcases.append((pattern, text_path))

    return testcases


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test1(self, pattern: str, file: str):
        """Metamorphic Relation 1: If a character is added to the end of the search term,
        the length of the output length should be the same as or less than the original.
        """
        # Get source output
        process = os.popen(f"{GREP_PATH} {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Construct follow-up input
        follow_pattern = pattern + "a"

        # Get follow-up output
        process = os.popen(f"{GREP_PATH} {follow_pattern} {file}")
        follow_out = process.readlines()
        process.close()

        # Verification
        self.assertLessEqual(len(follow_out), len(source_out))

    @parameterized.expand(load_test_cases)
    def test2(self, pattern: str, file: str):
        """Metamorphic Relation 2: If case distinctions are ignored, swap the case of search term,
        the output should be the same.
        """
        # Get source output
        process = os.popen(f"{GREP_PATH} --ignore-case {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Construct follow-up input
        follow_pattern = pattern.swapcase()

        # Get follow-up output
        process = os.popen(f"{GREP_PATH} --ignore-case {follow_pattern} {file}")
        follow_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test3(self, pattern, file):
        """Metamorphic Relation 3: If regular expression matching is enabled, add an asterisk at
        the end of the search term, the output should be the same.
        """
        # Get source output
        process = os.popen(f'{GREP_PATH} --regexp="{pattern}" {file}')
        source_out = process.readlines()
        process.close()

        # Construct follow-up input
        follow_pattern = f"{pattern}*"

        # Get follow-up output
        process = os.popen(f'{GREP_PATH} --regexp="{follow_pattern}" {file}')
        follow_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
