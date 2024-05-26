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
    def test1(self, tc: str):
        """Metamorphic Relation 1: Duplicating numeric values, the number of follow-up output's rows should equal the number of source output's rows plus the number of numeric values."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Count numeric values in source input
        numeric_count = sum(token.isdigit() for token in tc.split())

        # Construct follow-up input
        follow_tc = re.sub(r"(\b\d+\b)", r"\1 \1", tc)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(len(source_out) + numeric_count, len(follow_out))


if __name__ == "__main__":
    unittest.main()
