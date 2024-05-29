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
    def test38(self, tc: str):  # Fixed
        """Metamorphic Relation 38: Splitting an identifier using a legal separator should increase the token count."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")
        tmp = [x for x in source_out if x.startswith("identifier")]
        if len(tmp) == 0:
            self.skipTest("No identifier found in the input")

        # Construct follow-up input by splitting the first found identifier using an underscore
        follow_tc = re.sub(r'\b([a-zA-Z_]\w*)\b', r'\1_\1', tc, count=1)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # The token count should increase by one if the identifier is split
        self.assertGreater(len(follow_out), len(source_out))


if __name__ == "__main__":
    unittest.main()
