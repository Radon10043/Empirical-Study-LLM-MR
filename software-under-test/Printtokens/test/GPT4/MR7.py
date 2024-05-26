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
        """Metamorphic Relation 7: Permuting the order of statements should not change the set of extracted tokens."""
        # Get source output and tokenize
        source_out = set(subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n"))

        # Construct follow-up input by shuffling the statements in the program
        statements = tc.split("\n")
        random.shuffle(statements)
        follow_tc = "\n".join(statements)

        # Get follow-up output and tokenize
        follow_out = set(subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n"))

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
