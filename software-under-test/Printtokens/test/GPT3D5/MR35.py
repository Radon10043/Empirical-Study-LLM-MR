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
    def test35(self, tc: str):
        """Metamorphic Relation 35: Interchanging the positions of two consecutive tokens, the output should change accordingly."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        tokens = tc.split(" ")
        # Swap the positions of two consecutive tokens
        if len(tokens) > 1:
            idx = random.randint(0, len(tokens) - 2)
            tokens[idx], tokens[idx + 1] = tokens[idx + 1], tokens[idx]
            follow_tc = " ".join(tokens)

            # Get follow-up output
            follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

            # Verification
            self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
