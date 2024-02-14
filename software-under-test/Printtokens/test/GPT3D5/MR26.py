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
    def test26(self, tc: str):
        """Metamorphic Relation 26: Replacing certain tokens with truncated versions, the general structure of the output should not change."""
        import re

        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Replace certain tokens with truncated versions
        tokens = tc.split()
        for i, token in enumerate(tokens):
            if re.match(r'^[A-Za-z0-9_]+$', token):
                tokens[i] = token[:3]
        follow_tc = " ".join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verify that the general structure of the output is similar
        self.assertGreaterEqual(len(follow_out), len(source_out) * 0.9)


if __name__ == "__main__":
    unittest.main()
