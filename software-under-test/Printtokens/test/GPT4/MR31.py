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
        """Metamorphic Relation 31: Converting integer literals to hexadecimal should not change non-numeric tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True)

        # Construct follow-up input by converting all integer literals to hexadecimal
        follow_tc = re.sub(r'\b(\d+)\b', lambda m: hex(int(m.group(1))), tc)

        # Extract non-numeric tokens for comparison
        source_out_non_numeric = re.sub(r'\b\d+\b', '', source_out)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True)

        # Extract non-numeric tokens for comparison
        follow_out_non_numeric = re.sub(r'\b\d+\b', '', follow_out)

        # Verification - Check whether the non-numeric tokens remain unchanged
        self.assertEqual(source_out_non_numeric, follow_out_non_numeric)


if __name__ == "__main__":
    unittest.main()
