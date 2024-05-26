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
    def test32(self, tc: str):
        """Metamorphic Relation 32: Inserting a valid new token in white space should increase the number of tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by inserting a new token in white space
        # For example, inserting a numeric token '42' in the first whitespace occurrence
        first_whitespace_index = tc.find(' ')
        if first_whitespace_index != -1:
            follow_tc = f"{tc[:first_whitespace_index]} 42 {tc[first_whitespace_index+1:]}"

            # Get follow-up output
            follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

            # Verification
            self.assertEqual(len(source_out) + 1, len(follow_out))
        else:
            self.skipTest("No whitespace found to insert a new token.")


if __name__ == "__main__":
    unittest.main()
