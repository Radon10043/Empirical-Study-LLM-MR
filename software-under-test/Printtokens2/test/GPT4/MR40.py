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
    def test40(self, tc: str):
        """Metamorphic Relation 40: Removing all white spaces should not change the sequence or types of tokens extracted."""
        # Get source output tokens sequence
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True)
        source_tokens = source_out.split()

        # Construct follow-up input without white spaces
        follow_tc = ''.join(tc.split())

        # Get follow-up output tokens sequence
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True)
        follow_tokens = follow_out.split()

        # Verification
        self.assertEqual(source_tokens, follow_tokens)


if __name__ == "__main__":
    unittest.main()
