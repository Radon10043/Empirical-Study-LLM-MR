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
    def test36(self, tc: str):
        """Metamorphic Relation 36: Changing the sequence of characters in a token should result in different tokens, but same count if no new tokens are formed."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by scrambling characters in a single token
        tokens = re.findall(r'\b\w+\b', tc)
        if tokens:
            token_to_scramble = random.choice(tokens)
            scrambled = ''.join(random.sample(token_to_scramble, len(token_to_scramble)))
            follow_tc = tc.replace(token_to_scramble, scrambled, 1)

            # Get follow-up output
            follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

            # Verification
            self.assertEqual(len(source_out), len(follow_out))
        else:
            self.skipTest("No tokens found to scramble.")


if __name__ == "__main__":
    unittest.main()
