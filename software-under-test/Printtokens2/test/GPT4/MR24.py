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
    def test24(self, tc: str):  # Fixed
        """Metamorphic Relation 24: Duplicate the input file content should double the number of output tokens, preserving the order."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")
        for _ in range(2):
            source_out.pop()

        # Construct follow-up input by duplicating the entire content
        follow_tc = f"{tc}\n{tc}\n"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")
        for _ in range(2):
            follow_out.pop()

        # Verification
        # The number of tokens in the follow-up output should be twice the number of source output
        self.assertEqual(len(source_out) * 2, len(follow_out))


if __name__ == "__main__":
    unittest.main()
