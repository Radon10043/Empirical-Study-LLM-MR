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
    def test35(self, tc: str):
        """Metamorphic Relation 35: Replacing a token with an equivalent set of tokens (such as expanding abbreviations) should change the token count appropriately."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by replacing a found abbreviation with its expanded form
        # Example: Assume 'func' could be expanded to 'function', both considered as identifiers
        follow_tc = tc.replace('func', 'function')

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # For every occurrence of 'func', the number of tokens should increase by one
        num_occurrences = tc.count('func')
        self.assertEqual(len(source_out) + num_occurrences, len(follow_out))


if __name__ == "__main__":
    unittest.main()
