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
    def test29(self, tc: str):
        """Metamorphic Relation 29: Applying a transformation to the entire input while maintaining token lengths, the token counts in the output should remain the same."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Applying a transformation to the entire input while maintaining token lengths
        transformed_tc = ""
        for line in tc.split("\n"):
            tokens = line.split()
            transformed_tokens = [token[::-1] if len(token) % 2 == 0 else token for token in tokens]
            transformed_line = " ".join(transformed_tokens)
            transformed_tc += transformed_line + "\n"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=transformed_tc, text=True).split("\n")

        # Verification
        self.assertEqual(len(source_out), len(follow_out))


if __name__ == "__main__":
    unittest.main()
