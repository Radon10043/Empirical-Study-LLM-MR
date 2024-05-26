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
    def test29(self, tc: str):
        """Metamorphic Relation 29: Doubling the lines in the input, the output should display the token stream of each line doubled"""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        follow_tc = tc + "\n" + tc

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        for _ in range(2):
            source_out.pop()
            follow_out.pop()
        expected_follow_out = source_out + source_out
        self.assertEqual(expected_follow_out, follow_out)


if __name__ == "__main__":
    unittest.main()
