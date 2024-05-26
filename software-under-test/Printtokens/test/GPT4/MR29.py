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
        """Metamorphic Relation 29: Refactoring code without changing behavior should not change the set of extracted tokens."""
        # This is assuming refactoring does not introduce new tokens or remove existing ones
        # Get source output
        source_out = set(subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n"))

        # Construct follow-up input by refactoring
        # For example: replacing for loop with while loop (assuming it does not change the token set)
        follow_tc = tc.replace('for(', 'i=0; while(')

        # Get follow-up output
        follow_out = set(subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n"))

        # Verification - Verify that the token set remains unchanged
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
