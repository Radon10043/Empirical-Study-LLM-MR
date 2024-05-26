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
        """Metamorphic Relation 25: Replacing the order of character and string tokens should not affect the number of tokens, but may change the order."""
        # Get source output tokens
        source_tokens = [line for line in subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n") if line]

        # Find all character and string literals to swap
        char_and_str_literals = re.findall(r'\'.\'|".*?"', tc)

        # If there are at least two literals, swap them
        if len(char_and_str_literals) >= 2:
            follow_tc = tc.replace(char_and_str_literals[0], 'PLACEHOLDER').replace(char_and_str_literals[1], char_and_str_literals[0]).replace('PLACEHOLDER', char_and_str_literals[1])

            # Get follow-up output tokens
            follow_tokens = [line for line in subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n") if line]

            # Verification
            # The number of tokens should remain the same, though the order may differ
            self.assertEqual(len(source_tokens), len(follow_tokens))
        else:
            # No verification needed if there are not enough literals to swap
            self.skipTest("Not enough character or string literals to swap.")


if __name__ == "__main__":
    unittest.main()
