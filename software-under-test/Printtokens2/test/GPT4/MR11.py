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
    def test11(self, tc: str):
        """Metamorphic Relation 11: Introducing a new line with a token that has already been used should increase token count."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Find a token that has already been used in the text
        tokens = re.findall(r"\b\w+\b", tc)

        if tokens:  # Ensure there is at least one token to duplicate
            # Construct follow-up input by adding a newline with a duplicated token
            follow_tc = f"{tc}\n{tokens[0]}\n"

            # Get follow-up output
            follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

            # Verification
            self.assertEqual(len(source_out) + 1, len(follow_out))
        else:
            # No verification needed if no tokens are found
            self.skipTest("No tokens found to duplicate.")


if __name__ == "__main__":
    unittest.main()
