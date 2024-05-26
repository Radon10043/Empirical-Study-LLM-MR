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
    def test22(self, tc: str):
        """Metamorphic Relation 22: Interchanging string literals with character literals should not change their token types."""
        # Assuming the language treats both as TOKEN_STRING
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by replacing strings with characters and vice versa
        is_string_literal = lambda x: x.startswith('"') and x.endswith('"')
        is_char_literal = lambda x: x.startswith("'") and x.endswith("'")
        tokens = tc.split()
        follow_tokens = [token.replace('"', "'") if is_string_literal(token) else token.replace("'", '"') if is_char_literal(token) else token for token in tokens]
        follow_tc = ' '.join(follow_tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - assuming tokenization treats string and char literals similarly, outputs should be comparable
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
