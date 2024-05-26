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
    def test27(self, tc: str):
        """Metamorphic Relation 27: Changing single-line comments to block comments should not affect the parsed tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Convert all single-line comments to block comments
        follow_tc = re.sub(r'//(.*)', r'/*\1 */', tc)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # Assuming both single-line and block comments are ignored by the tokenizer
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
