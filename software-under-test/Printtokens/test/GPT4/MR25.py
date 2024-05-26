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
    def test25(self, tc: str):
        """Metamorphic Relation 25: Adding escaped newline characters within literals or comments should not affect the output."""
        # Assuming escaped newlines are supported within literals and comments and do not affect tokenization
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by adding escaped newlines to comments and string literals
        is_literal_or_comment = lambda x: x.startswith('"') and x.endswith('"') or x.startswith('//')
        follow_tc = ' '.join(token + '\\n' if is_literal_or_comment(token) else token for token in tc.split())

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - outputs should be comparable ignoring the added escaped newlines
        adjusted_follow_out = [token.replace('\\n', '') for token in follow_out]
        self.assertEqual(source_out, adjusted_follow_out)


if __name__ == "__main__":
    unittest.main()
