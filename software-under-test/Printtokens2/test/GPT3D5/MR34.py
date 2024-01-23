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
    def test34(self, tc: str):
        """Metamorphic Relation 34: Removing certain tokens from the input, the output token counts should be less than or equal to the source output token counts."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        tokens = tc.strip().split("\n")
        tokens_to_remove = tokens[:len(tokens)//2]

        # Remove certain tokens from the input
        follow_tc = '\n'.join([token for token in tokens if token not in tokens_to_remove])

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertLessEqual(len(follow_out), len(source_out))


if __name__ == "__main__":
    unittest.main()
