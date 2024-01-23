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

    @parameterized.expand(load_test_cases)
    def test32(self, tc: str):
        """Metamorphic Relation 32: Removing a token from the input, the removed token should not appear in the output"""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True)

        # Construct follow-up input by removing a token
        tokens = tc.split()
        if tokens:
            tokens.pop()
        follow_tc = " ".join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True)

        # Verify the removed token in the follow-up output
        self.assertNotIn(tokens[-1], follow_out)


if __name__ == "__main__":
    unittest.main()
