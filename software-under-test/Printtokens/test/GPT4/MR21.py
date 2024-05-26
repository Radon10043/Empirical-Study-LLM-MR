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
    def test21(self, tc: str):
        """Metamorphic Relation 21: Removing redundant semicolons should not change the output."""
        # Assuming semicolons are not used for empty statements
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by removing redundant semicolons
        follow_tc = tc.replace(";;", ";")

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - the output should be the same as there should be no tokenization change for semicolons
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
