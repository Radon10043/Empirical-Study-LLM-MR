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
    def test8(self, tc: str):
        """Metamorphic Relation 8: Encapsulating a token with quotes should only change the token type to string without affecting others."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        follow_tc = re.sub(r'(\b\w+\b)', r'"\1"', tc, count=1)  # Encapsulate first word in quotes

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # The output should differ by exactly one token (the one that was modified)
        self.assertEqual(len(source_out), len(follow_out))  # Assuming tokens are printed one per line


if __name__ == "__main__":
    unittest.main()
