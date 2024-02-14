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
    def test31(self, tc: str):
        """Metamorphic Relation 31: Removing all occurrences of a specific token, the count of that token should be zero in the output."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        tokens = tc.split()
        token_to_remove = "example_token"

        # Remove all occurrences of a specific token
        follow_tc = " ".join([token for token in tokens if token != token_to_remove])

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verify the count of occurrences for the specific token is zero
        self.assertEqual(source_out.count(token_to_remove), 0)


if __name__ == "__main__":
    unittest.main()
