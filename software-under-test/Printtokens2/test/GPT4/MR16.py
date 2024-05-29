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
    def test16(self, tc: str):  # Fixed
        """Metamorphic Relation 16: Enclosing the entire input within a comment block should result in no tokens being output."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by enclosing the entire input within a comment block
        follow_tc = f";{tc}"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # Assuming comment blocks are not tokenized and are handled properly by the tokenizer
        self.assertEqual([''] * len(source_out), follow_out)


if __name__ == "__main__":
    unittest.main()
