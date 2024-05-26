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
    def test28(self, tc: str):
        """Metamorphic Relation 28: Renaming variables should not affect the number of tokens, only their content."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")
        unique_identifiers = set(re.findall(r'\b[a-zA-Z_][a-zA-Z0-9_]*\b', tc))

        # Construct follow-up input by renaming variables
        follow_tc = tc
        for identifier in unique_identifiers:
            if not identifier.iskeyword():  # Replace only if it's not a Python keyword
                follow_tc = re.sub(rf'\b{identifier}\b', f'{identifier}_renamed', follow_tc)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # The number of tokens should remain constant
        self.assertEqual(len(source_out), len(follow_out))


if __name__ == "__main__":
    unittest.main()
