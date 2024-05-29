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
    def test30(self, tc: str):  # Fixed
        """Metamorphic Relation 30: Replacing a token with a synonym or equivalent representation should not change the number of output tokens."""
        tc += "&& &&\n"

        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by replacing a token with its synonym
        # Example: replacement of '&&' with 'and' assuming the tokenizer treats them as equivalent
        follow_tc = tc.replace("&&", "and")

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(len(source_out), len(follow_out))


if __name__ == "__main__":
    unittest.main()
