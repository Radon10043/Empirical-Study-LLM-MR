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
        """Metamorphic Relation 31: Prepending a special identifier to each token in the input, the follow-up output should contain tokens with the identifier"""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True)
        source_tokens = source_out.split()

        # Construct follow-up input
        special_identifier = "TOKEN:"
        follow_tc = " ".join([special_identifier + token for token in tc.split()])

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True)
        follow_tokens = follow_out.split()

        # Verification
        for token in source_tokens:
            self.assertIn(special_identifier + token, follow_tokens)


if __name__ == "__main__":
    unittest.main()
