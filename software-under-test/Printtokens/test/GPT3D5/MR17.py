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
    def test17(self, tc: str):
        """Metamorphic Relation 17: Concatenating two input texts, the follow-up output should contain tokens from both."""
        # Generate an additional input text
        additional_input = "Additional input text for testing purposes."

        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        follow_tc = tc + "\n" + additional_input

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")
        additional_out = subprocess.check_output(PRINT_TOKENS_PATH, input=additional_input, text=True).split("\n")

        # Remove the last two lines, which is empty lines and "eof"
        for _ in range(2):
            source_out.pop()
            follow_out.pop()
            additional_out.pop()

        # Verification
        self.assertGreaterEqual(len(follow_out), len(source_out) + len(additional_out))


if __name__ == "__main__":
    unittest.main()
