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
    def test17(self, tc: str):  # Fixed
        """Metamorphic Relation 17: Inserting comments between tokens should not change the output."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input with comments inserted between tokens
        follow_tc = tc.replace(" ", " ;comment ")

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - the output without comments should be the same as source output
        self.assertEqual(source_out, [token for token in follow_out if not token.startswith('//comment//')])


if __name__ == "__main__":
    unittest.main()
