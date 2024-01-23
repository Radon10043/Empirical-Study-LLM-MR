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
    def test12(self, tc: str):
        """Metamorphic Relation 12: Duplicating all lines of input, the number of tokens in each category should double"""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        follow_tc = "\n".join([line + "\n" + line for line in tc.split("\n")])

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verify the doubling of tokens in each category
        for category in set(source_out):
            source_count = source_out.count(category)
            follow_count = follow_out.count(category)
            self.assertEqual(source_count * 2, follow_count)


if __name__ == "__main__":
    unittest.main()
