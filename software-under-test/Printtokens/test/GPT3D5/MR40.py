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
        """Metamorphic Relation 40: Replacing names and addresses with placeholders, the general structure of the output should remain the same."""
        import re

        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Replace names and addresses with placeholders
        follow_tc = re.sub(r'\b[A-Z][a-z]+(?:\s[A-Z][a-z]+)*\b', 'John Doe', tc)
        follow_tc = re.sub(r'\b\d+\s\w+.*\b', '123 Main St', follow_tc)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verify that the general structure of the output is similar
        self.assertGreaterEqual(len(follow_out), len(source_out) * 0.9)


if __name__ == "__main__":
    unittest.main()
