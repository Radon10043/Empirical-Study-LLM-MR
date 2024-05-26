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
    def test33(self, tc: str):
        """Metamorphic Relation 33: Swapping two random lines in the input, the number of follow-up output's rows equals the number of source output's rows."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Swap two random lines in the input
        lines = tc.split("\n")
        if len(lines) <= 1:
            return;
        import random
        idx1, idx2 = random.sample(range(len(lines)), 2)
        lines[idx1], lines[idx2] = lines[idx2], lines[idx1]
        follow_tc = "\n".join(lines)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(len(source_out), len(follow_out))


if __name__ == "__main__":
    unittest.main()
