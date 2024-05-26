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
    def test33(self, tc: str):
        """Metamorphic Relation 33: Explicating operator precedence with parentheses should not change the output."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by inserting parentheses to make operator precedence explicit
        # Example transformation: `a + b * c` becomes `a + (b * c)`
        # Note: This is a naive transformation and may not be appropriate for all expression formats.
        follow_tc = tc.replace(' * ', ' * (' ).replace(' + ', ' + (').replace(' - ', ' - (') + ')'*tc.count(' * ')

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - Check whether the output remains unchanged
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
