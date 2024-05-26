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
    def test11(self, tc: str):
        """Metamorphic Relation 11: Changing the value of numeric tokens should not affect non-numeric tokens in the output."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")
        source_non_numeric_tokens = [token for token in source_out if not token.isdigit()]

        # Construct follow-up input by changing all numeric values to a fixed number
        follow_tc = re.sub(r'(\b\d+\b)', '42', tc)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")
        follow_non_numeric_tokens = [token for token in follow_out if not token.isdigit()]

        # Verification
        self.assertEqual(source_non_numeric_tokens, follow_non_numeric_tokens)


if __name__ == "__main__":
    unittest.main()
