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
    def test32(self, tc: str):
        """Metamorphic Relation 32: Mixing the input lines, the output token counts should be greater than or equal to the source output token counts."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Mix the input lines
        lines = tc.strip().split("\n")
        mixed_lines = random.sample(lines, len(lines))
        mixed_tc = "\n".join(mixed_lines)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=mixed_tc, text=True).split("\n")

        # Verification
        source_tokens = [token.split()[0] for token in source_out if token]  # Extract tokens from source output
        follow_tokens = [token.split()[0] for token in follow_out if token]  # Extract tokens from follow-up output
        self.assertGreaterEqual(len(follow_tokens), len(source_tokens))


if __name__ == "__main__":
    unittest.main()
