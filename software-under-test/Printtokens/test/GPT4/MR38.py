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
    def test38(self, tc: str):
        """Metamorphic Relation 38: Inverting boolean literals should change the respective tokens but not alter the overall number or types of tokens."""
        # Get source output
        source_output = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        # Invert boolean literals (true to false, false to true)
        follow_up_input = tc.replace("true", "xTEMPx").replace("false", "true").replace("xTEMPx", "false")

        # Get follow-up output and extract tokens
        follow_up_output = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_up_input, text=True).split("\n")

        # Verification
        # Check if the number of tokens remain the same
        self.assertEqual(len(source_output), len(follow_up_output))


if __name__ == "__main__":
    unittest.main()
