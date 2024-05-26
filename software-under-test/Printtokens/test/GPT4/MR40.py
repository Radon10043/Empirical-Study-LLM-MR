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
    def test40(self, tc: str):
        """Metamorphic Relation 40: Shuffling lines of independent code should not change the set of tokens."""
        # Get source output and tokens
        source_output = set(subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n"))

        # Construct follow-up input
        # Shuffle lines assuming they are independent
        lines = tc.split("\n")
        random.shuffle(lines)
        follow_up_input = "\n".join(lines)

        # Get follow-up output and tokens
        follow_up_output = set(subprocess.check_output(PRINT_TOKENS_PATH, input=follow_up_input, text=True).split("\n"))

        # Verification
        # The sets of tokens should be equal
        self.assertEqual(source_output, follow_up_output)


if __name__ == "__main__":
    unittest.main()
