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
    def test15(self, tc: str):
        """Metamorphic Relation 15: Appending code that does not introduce new tokens or affect state (e.g., comments or non-executed lines like those after a return in the main function) should not change the token output."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by appending non-affecting comments or code
        follow_tc = tc + "\n" + "// This is a comment line\nreturn;"  # Using return to simulate unreachable code

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - the output should remain the same
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
