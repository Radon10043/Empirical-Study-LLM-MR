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
    def test16(self, tc: str):
        """Metamorphic Relation 16: Replacing specific tokens with null, the output should still contain the same tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Replace specific tokens with null in the input
        tokens = tc.strip().split("\n")
        tokens[random.randint(0, len(tokens) - 1)] = ""
        replaced_tc = "\n".join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=replaced_tc, text=True).split("\n")

        # Verification
        source_tokens = set([token.split()[0] for token in source_out if token])  # Extract tokens from source output
        follow_tokens = set([token.split()[0] for token in follow_out if token])  # Extract tokens from follow-up output
        self.assertEqual(source_tokens, follow_tokens)


if __name__ == "__main__":
    unittest.main()
