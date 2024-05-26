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
        """Metamorphic Relation 33: Interspersing tokens with comments should not change the output, assuming comments are ignored."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by adding comments between tokens
        follow_tc = re.sub(r' ', ' /* comment */ ', tc)  # Insert block comment between spaces as an example

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification, assuming that the added comments are ignored in tokenizing process
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
