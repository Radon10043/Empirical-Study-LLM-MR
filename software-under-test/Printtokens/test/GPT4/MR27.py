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
        """Metamorphic Relation 27: Swapping a keyword with an identifier should not affect other token outputs except the swapped tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # For simplicity, let's assume 'if' is a keyword and 'foo' is an identifier in the code
        if_keyword_count = source_out.count('if')
        foo_identifier_count = source_out.count('foo')

        # Construct follow-up input by swapping 'if' with 'foo'
        follow_tc = tc.replace('if', 'foo').replace('foo', 'if')

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(follow_out.count('if'), foo_identifier_count)
        self.assertEqual(follow_out.count('foo'), if_keyword_count)


if __name__ == "__main__":
    unittest.main()
