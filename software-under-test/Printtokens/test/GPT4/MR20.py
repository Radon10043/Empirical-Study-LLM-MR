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
    def test1(self, tc: str):
        """Metamorphic Relation 20: Adding quotes around keywords should change the tokens that represent those keywords if quoting is part of the tokenization rules."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Get all tokens from the source input
        original_tokens = tc.split()

        # Construct follow-up input by adding quotes around each non-numeric, non-special token
        follow_tc = ' '.join(['"' + token + '"' if token.isalpha() else token for token in original_tokens])

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verify that the original keywords are not in the follow-up output and that the follow-up output contains new quoted tokens
        original_keywords = [token for token in original_tokens if token.isalpha()]
        follow_keywords = [line for line in follow_out if line.strip('"') in original_keywords]
        new_quoted_tokens = ['"' + keyword + '"' for keyword in original_keywords]

        self.assertTrue(all(keyword not in follow_keywords for keyword in original_keywords))
        self.assertTrue(all(new_token in follow_out for new_token in new_quoted_tokens))


if __name__ == "__main__":
    unittest.main()
