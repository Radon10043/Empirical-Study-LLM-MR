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
    def test19(self, tc: str):
        """Metamorphic Relation 19: Replacing tokens with their synonyms should not affect the output, assuming the tokenization rule identifies synonyms as the same token."""
        # This transformation would depend on having a mapping of synonym tokens
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Define a mapping of synonyms (assuming synonym substitution applies to specific types of tokens)
        synonyms = {"while": "loop", "if": "cond"}  # example synonym list
        synonym_pattern = re.compile("|".join(map(re.escape, synonyms.keys())))

        # Construct follow-up input by replacing tokens with synonyms
        follow_tc = synonym_pattern.sub(lambda match: synonyms[match.group(0)], tc)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - assuming that the tokenization treats synonyms as the same token, the output should not change
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
