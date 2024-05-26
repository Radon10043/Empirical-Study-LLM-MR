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
    def test18(self, tc: str):
        """Metamorphic Relation 18: Extending lines with the backslash character should not alter the set of extracted tokens."""
        # Assuming that the language supports line continuation with backslash
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")
    
        # Construct follow-up input by adding a line extension backslash to the end of each line
        follow_tc = "\\\n".join(tc.splitlines())

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - tokens should still be the same
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
