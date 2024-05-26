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
    def test34(self, tc: str):
        """Metamorphic Relation 34: Swapping the order of independent function calls should not change the set of tokens."""
        # Get source output
        source_out = set(subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n"))

        # Example of swapping function calls, assuming function calls are on separate lines and are independent
        lines = tc.split("\n")
        lines_with_function_calls = [line for line in lines if line.endswith('();')]  # Naive detection of function calls
        if len(lines_with_function_calls) > 1:
            lines_with_function_calls[0], lines_with_function_calls[1] = lines_with_function_calls[1], lines_with_function_calls[0]

        follow_tc = "\n".join(lines_with_function_calls if line.endswith('();') else line for line in lines)

        # Get follow-up output
        follow_out = set(subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n"))

        # Verification - Check whether the set of tokens remains unchanged
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
