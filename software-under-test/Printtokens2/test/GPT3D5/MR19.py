from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build print_tokens.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases)
    def test19(self, tc: str):
        """Metamorphic Relation 19: Duplicating a specific token in the input, the count of that token in the output should increase."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Duplicate a specific token in the input
        tokens = tc.strip().split("\n")
        target_token = random.choice(tokens).split()[0]
        duplicated_tokens = tokens + [token for token in tokens if token.startswith(target_token)]
        duplicated_tc = "\n".join(duplicated_tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=duplicated_tc, text=True).split("\n")

        source_token_count = sum(1 for token in source_out if token.startswith(target_token))
        follow_token_count = sum(1 for token in follow_out if token.startswith(target_token))

        # Verification
        self.assertGreaterEqual(follow_token_count, source_token_count)


if __name__ == "__main__":
    unittest.main()
