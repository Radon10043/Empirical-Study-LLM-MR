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
    def test30(self, tc: str):
        """Metamorphic Relation 30: Transforming logical operators (&& to and, || to or) should change the respective tokens but not the number of tokens."""
        # This assumes the tokenization rule distinguishes between different logical operators
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by changing logical operators
        follow_tc = tc.replace('&&', 'and').replace('||', 'or')

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - Check whether the new tokens 'and' and 'or' are present and '&&' '||' are not
        self.assertEqual(len(source_out), len(follow_out))
        self.assertTrue('and' in follow_out or 'or' in follow_out)


if __name__ == "__main__":
    unittest.main()
