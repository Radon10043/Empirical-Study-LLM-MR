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
    def test24(self, tc: str):
        """Metamorphic Relation 24: Sorting numeric values separately should not affect non-numeric token outputs."""
        # Assuming numeric values are independent and can be sorted without affecting other tokens
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")
        source_out_non_numeric = [token for token in source_out if not token.isnumeric()]

        # Extract numeric tokens and sort them
        numeric_tokens = sorted([token for token in tc.split() if token.isnumeric()], key=int)

        # Construct follow-up input by replacing numeric tokens with sorted ones
        non_numeric_tokens = iter([token for token in tc.split() if not token.isnumeric()])
        follow_tc = ' '.join(next(non_numeric_tokens) if not token.isnumeric() else numeric_tokens.pop(0) for token in tc.split())

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")
        follow_out_non_numeric = [token for token in follow_out if not token.isnumeric()]

        # Verification - non-numeric tokens should remain unaffected
        self.assertEqual(source_out_non_numeric, follow_out_non_numeric)


if __name__ == "__main__":
    unittest.main()
