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
    def test6(self, tc: str):
        """Metamorphic Relation 6: Removing a token from the input, the output's token counts should be less than the source output's token counts."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Remove a token from the input
        tokens = tc.strip().split("\n")
        tokens_to_remove = random.choice(tokens)
        tokens.remove(tokens_to_remove)
        follow_tc = "\n".join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertLess(len(follow_out), len(source_out))


if __name__ == "__main__":
    unittest.main()
