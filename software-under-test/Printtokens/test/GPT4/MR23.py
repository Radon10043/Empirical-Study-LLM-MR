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
    def test23(self, tc: str):
        """Metamorphic Relation 23: Adding unused variable declarations should not change the set of tokens related to the original functionality."""
        # This assumes adding variables that are not used anywhere does not affect how other tokens are tokenized
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input with additional unused variable declarations
        extra_vars = "\nint unusedVar1;\ndouble unusedVar2;\n"
        follow_tc = tc + extra_vars

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - the number of tokens related to the original content should remain the same
        self.assertEqual(source_out, [token for token in follow_out if "unusedVar" not in token])


if __name__ == "__main__":
    unittest.main()
