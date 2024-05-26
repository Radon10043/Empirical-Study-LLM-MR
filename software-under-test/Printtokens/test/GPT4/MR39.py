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
    def test39(self, tc: str):
        """Metamorphic Relation 39: Duplicating lines while preserving the order of tokens should duplicate tokens."""
        # Get source output
        source_output = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        # Duplicate each line to see if token order is preserved
        follow_up_input = "\n".join(line for line in tc.split("\n") for _ in range(2))

        # Get follow-up output and extract tokens
        follow_up_output = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_up_input, text=True).split("\n")

        # Verification
        # Compare the doubled source output to the follow-up output
        self.assertEqual(source_output * 2, follow_up_output)


if __name__ == "__main__":
    unittest.main()
