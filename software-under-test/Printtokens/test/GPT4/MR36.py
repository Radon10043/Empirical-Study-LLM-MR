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
    def test36(self, tc: str):
        """Metamorphic Relation 36: Appending unrelated code should introduce new tokens
        corresponding to the added code without changing the previous tokens."""
        unrelated_code = "\nprint('Hello, World!');"

        # Get source output and extract tokens
        source_output = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input with the unrelated code appended
        follow_up_input = tc + unrelated_code

        # Get follow-up output and extract tokens
        follow_up_output = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_up_input, text=True).split("\n")

        # Verification
        # Check if the previous tokens remain the same
        # and if the new tokens are only from the appended unrelated code.
        self.assertEqual(source_output + ["print", "(", "'Hello, World!'", ")", ";"], follow_up_output)


if __name__ == "__main__":
    unittest.main()
