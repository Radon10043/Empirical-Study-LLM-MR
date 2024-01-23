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
    def test34(self, tc: str):
        """Metamorphic Relation 34: Adding a token with a different category, the new token should appear in the output with the appropriate category"""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True)

        # Construct follow-up input by adding a new token with a different category
        follow_tc = tc + " lambda"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True)

        # Verify the new token and its category in the follow-up output
        self.assertIn("lambda", follow_out)
        self.assertIn("keyword,\t\"lambda\"", follow_out)


if __name__ == "__main__":
    unittest.main()
