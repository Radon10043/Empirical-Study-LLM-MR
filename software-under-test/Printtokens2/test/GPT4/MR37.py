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
    def test37(self, tc: str):  # Fixed
        """Metamorphic Relation 37: In a well-formed input, adding valid syntax that does not introduce new tokens should not change the token count."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by adding syntax that does not form a new token
        # For example, adding ';' at the end of the input if it is a well-formed statement
        if tc.strip().endswith(';'):
            follow_tc = f"{tc} ;"
        else:
            follow_tc = f"{tc};"
        follow_tc += "\n"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(len(source_out), len(follow_out))


if __name__ == "__main__":
    unittest.main()
