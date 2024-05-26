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
    def test5(self, tc: str):
        """Metamorphic Relation 5: Reordering independent lines, the output should not change."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by reordering independent lines (lines without context such as block starts or ends)
        lines = tc.split("\n")
        random.shuffle(lines)  # Note: You would need to ensure that the shuffle doesn't introduce syntactical errors.

        follow_tc = "\n".join(lines)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        new_source_out = sorted([line for line in source_out if line.strip() != ''])
        new_follow_out = sorted([line for line in follow_out if line.strip() != ''])
        self.assertEqual(new_source_out, new_follow_out)


if __name__ == "__main__":
    unittest.main()
