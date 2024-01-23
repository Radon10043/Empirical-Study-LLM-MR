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
    def test8(self, tc: str):
        """Metamorphic Relation 8: Reordering the tokens while preserving categories, the output should remain the same"""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Process tokens and categories
        tokens_categories = [token.split(":") for token in tc.split()]
        tokens_categories.sort(key=lambda x: x[1])  # Sort by category while preserving token order
        reordered_tokens = [":".join(pair) for pair in tokens_categories]

        # Construct follow-up input
        follow_tc = " ".join(reordered_tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
