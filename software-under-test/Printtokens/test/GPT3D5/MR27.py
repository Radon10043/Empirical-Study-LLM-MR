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
    def test27(self, tc: str):
        """Metamorphic Relation 27: Reverse the order of occurrence of tokens, the output should remain the same but ordered differently."""
        from itertools import permutations

        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        tokens = tc.split(" ")

        # Reverse
        tokens.reverse()

        # Randomly select a permutation
        follow_tc = ' '.join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verify the content is the same regardless of the order
        self.assertCountEqual(source_out, follow_out)
        # Verify the order is different
        self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
