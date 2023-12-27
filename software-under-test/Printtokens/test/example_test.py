import unittest
import os, subprocess, time

from parameterized import parameterized


# GLOBAL VRAIABLES
PRINT_TOKENS_PATH = os.path.join(os.path.dirname(__file__), "..", "src", "print_tokens.out")


def load_test_cases() -> list:
    """读取所有测试用例

    Returns
    -------
    list
        存储测试用例的列表
    """
    tcs_dir = os.path.join(os.path.dirname(__file__), "..", "testcases")
    tcs = list()

    # 遍历存储测试用例的根目录, 依次读取文件
    for file in os.listdir(tcs_dir):
        with open(os.path.join(tcs_dir, file), "r") as f:
            tcs.append(f.read())

    return tcs


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build print_tokens.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases)
    def test1(self, tc: str):
        """Metamorphic Relation 1: Adding a new line that only includes a comma, the follow-up output's rows equals the source output's rows plus one.

        Parameters
        ----------
        tc : str
            _description_
        """
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        follow_tc = tc + "\n,"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(len(source_out) + 1, len(follow_out))

    @parameterized.expand(load_test_cases)
    def test2(self, tc: str):
        """Metamorphic Relation 2: Deleting the comments, the output should not change

        Parameters
        ----------
        tc : str
            _description_
        """
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        follow_tc = tc.split("\n")
        for i in range(len(follow_tc)):
            follow_tc[i] = follow_tc[i].split(";")[0]
        follow_tc = "\n".join(follow_tc)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)

    @parameterized.expand(load_test_cases)
    def test3(self, tc: str):
        """Metamorphic Relation 3: Adding the comment, the output should not change

        Parameters
        ----------
        tc : str
            _description_
        """
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        follow_tc = tc + "; Comment!"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
