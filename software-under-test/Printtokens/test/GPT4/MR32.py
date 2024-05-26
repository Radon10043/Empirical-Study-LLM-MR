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
    def test32(self, tc: str):
        """Metamorphic Relation 32: Inserting format specifiers into string literals should change corresponding tokens but not the overall number of tokens."""
        # Get source output and token count
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")
        token_count = len(source_out)

        # Construct follow-up input by inserting format specifiers like %d into string literals
        follow_tc = re.sub(r'(".*?")', lambda m: m.group(1).replace('string', 'string %d'), tc)

        # Get follow-up output and token count
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")
        follow_token_count = len(follow_out)

        # Verification - Check whether token count remains the same
        self.assertEqual(token_count, follow_token_count)


if __name__ == "__main__":
    unittest.main()
