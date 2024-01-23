import unittest
import os, subprocess, time

from parameterized import parameterized
from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build print_tokens.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test31(self, tc: str):
        """Metamorphic Relation 31: Adding a new token into the input, the new token should appear in the output with the appropriate category"""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True)

        # Construct follow-up input by adding a new token
        follow_tc = tc + "lambda"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True)

        # Verify the new token in the follow-up output
        self.assertTrue(follow_out.endswith("keyword,\t\"lambda\".\neof.\n"))


if __name__ == "__main__":
    unittest.main()
