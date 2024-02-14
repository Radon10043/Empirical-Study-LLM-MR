import re
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
    def test20(self, tc: str):
        """Metamorphic Relation 20: Reordering certain tokens according to specific rules, the general structure of the output should not change."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        tokens = tc.split()
        # Reorder tokens representing a date in the format DD/MM/YYYY to YYYY/MM/DD
        for i, token in enumerate(tokens):
            if re.match(r'\d{2}/\d{2}/\d{4}', token):
                date_parts = token.split('/')
                tokens[i] = "/".join([date_parts[2], date_parts[1], date_parts[0]])
        follow_tc = " ".join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verify that the general structure of the output is similar
        self.assertGreaterEqual(len(follow_out), len(source_out) * 0.9)


if __name__ == "__main__":
    unittest.main()
