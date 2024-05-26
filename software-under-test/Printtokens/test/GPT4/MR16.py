import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build print_tokens.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases(1000))
    def test16(self, tc: str):
        """Metamorphic Relation 16: Duplicating a special character that is already present should not change the set of tokens if the tokenization rule for that character does not depend on duplication (requires knowledge of tokenization rules)."""
        # Assuming the tokenization rule for semicolon doesn't count duplicates differently
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input with duplicated semicolons
        follow_tc = tc.replace(';', ';;')

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - check if the set of tokens remains the same
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
