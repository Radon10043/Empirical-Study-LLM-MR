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
    def test42(self, tc: str):
        """Metamorphic Relation 42: Swapping order of two independent tokens should not change the overall number of tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Find two independent tokens (tokens that are not within quotes or comments)
        independent_tokens = re.findall(r'\b\s+(\S+)\s+(\S+)\s+\b', tc)

        if independent_tokens:
            token1, token2 = independent_tokens[0]

            # Construct follow-up input by swapping two independent tokens
            follow_tc_pattern = rf'\b\s+({token1})\s+({token2})\s+\b'
            follow_tc = re.sub(follow_tc_pattern, rf' \2 \1 ', tc, count=1)

            # Get follow-up output
            follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

            # Verification
            self.assertEqual(len(source_out), len(follow_out))


if __name__ == "__main__":
    unittest.main()
