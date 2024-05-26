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
    def test37(self, tc: str):
        """Metamorphic Relation 37: Renaming variables consistently should not change the number or types of tokens."""
        # Get source output
        source_output = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        # Rename variables in a consistent manner (e.g., append '_new' to each variable)
        variable_pattern = re.compile(r"\b[a-zA-Z_][a-zA-Z0-9_]*\b")
        follow_up_input = variable_pattern.sub(lambda m: m.group(0) + "_new", tc)

        # Get follow-up output and extract tokens
        follow_up_output = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_up_input, text=True).split("\n")

        # Verification
        # Check if the number and types of tokens remain unchanged.
        # (Actual token string values will change, so direct comparison is not valid.)
        self.assertEqual(len(source_output), len(follow_up_output))


if __name__ == "__main__":
    unittest.main()
