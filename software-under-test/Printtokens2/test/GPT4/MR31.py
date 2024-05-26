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
    def test31(self, tc: str):
        """Metamorphic Relation 31: Escaping characters that are tokens should not produce additional tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by escaping characters that normally act as tokens
        follow_tc = tc.replace('"', '\\"')  # Escaping double quotes as an example

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # The token count should remain the same, assuming the tokenizer supports escape sequences
        self.assertEqual(len(source_out), len(follow_out))


if __name__ == "__main__":
    unittest.main()
