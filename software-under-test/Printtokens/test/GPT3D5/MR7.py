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
    def test7(self, tc: str):
        """Metamorphic Relation 7: Adding or removing duplicate tokens, the output should remain the same"""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        tokens = tc.split()
        tokens_set = set(tokens)  # Remove duplicates
        follow_tc = " ".join(tokens_set)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
