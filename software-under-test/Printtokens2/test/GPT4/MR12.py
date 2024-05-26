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
    def test12(self, tc: str):
        """Metamorphic Relation 12: Concatenating two identifiers with a symbol should only increase the count of tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by concatenating two identifiers with a symbol that separate tokens
        follow_tc = re.sub(r"(\w+)\s+(\w+)", r"\1.\2", tc, count=1)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # Number of tokens should increase by one since we're replacing two tokens (identifiers) with three (identifier, symbol, identifier)
        self.assertEqual(len(source_out) + 1, len(follow_out))


if __name__ == "__main__":
    unittest.main()
