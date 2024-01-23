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
    def test11(self, tc: str):
        """Metamorphic Relation 11: Applying a random permutation to the input lines, the output should still contain the same tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Apply a random permutation to the input lines
        permuted_lines = random.sample(tc.strip().split("\n"), len(tc.strip().split("\n")))
        permuted_tc = "\n".join(permuted_lines)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=permuted_tc, text=True).split("\n")

        # Verification
        source_tokens = [token.split()[0] for token in source_out if token]  # Extract tokens from source output
        follow_tokens = [token.split()[0] for token in follow_out if token]  # Extract tokens from follow-up output
        self.assertCountEqual(source_tokens, follow_tokens)


if __name__ == "__main__":
    unittest.main()
