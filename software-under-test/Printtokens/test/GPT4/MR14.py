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
    def test14(self, tc: str):
        """Metamorphic Relation 14: Adding redundant code blocks should not change the set of extracted tokens, assuming duplicated blocks do not contain variable declarations or other context-altering content."""
        # Get source output
        source_out = set(subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n"))

        # Construct follow-up input by duplicating a block of code in the input
        block_start = tc.find('{')
        block_end = tc.rfind('}')
        if block_start != -1 and block_end != -1:
            code_block = tc[block_start:block_end+1]
            follow_tc = tc + code_block  # append the same block at the end
        else:
            follow_tc = tc

        # Get follow-up output
        follow_out = set(subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n"))

        # Verification - check if the set of tokens remains the same
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
