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
    def test9(self, tc: str):
        """Metamorphic Relation 9: Replacing a token by a synonym, the output should remain the same"""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Replace a token by a synonym
        token_synonyms = {
            "int": "integer",
            "float": "real",
            "str": "string"
        }
        tokens = tc.split()
        for i in range(len(tokens)):
            if tokens[i] in token_synonyms:
                tokens[i] = token_synonyms[tokens[i]]

        # Construct follow-up input
        follow_tc = " ".join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
