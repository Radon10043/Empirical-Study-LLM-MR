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
    def test22(self, tc: str):
        """Metamorphic Relation 22: Joining two tokens with an underscore should be treated as a single identifier token."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by joining the first two tokens with an underscore
        follow_tc = re.sub(r'(\b\w+\b)\s+(\b\w+\b)', r'\1_\2', tc, count=1)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # The token count should decrease by one since two tokens are joined into one
        self.assertEqual(len(source_out) - 1, len(follow_out))


if __name__ == "__main__":
    unittest.main()
