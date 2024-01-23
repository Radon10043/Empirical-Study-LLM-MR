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
    def test39(self, tc: str):
        """Metamorphic Relation 39: Randomly replacing tokens with synonyms, the output should remain the same"""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True)

        # Define token synonyms
        token_synonyms = {
            "int": "integer",
            "float": "real",
            "str": "string"
        }

        # Randomly replace tokens with synonyms
        new_tokens = [token_synonyms.get(token, token) for token in tc.split()]
        follow_tc = " ".join(new_tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
