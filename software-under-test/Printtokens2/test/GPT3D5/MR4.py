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
    def test4(self, tc: str):
        """Metamorphic Relation 4: Removing duplicate tokens from the input, the output's token counts should be less or equal to the source output's token counts."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input with removed duplicate tokens
        unique_tokens = set(tc.split("\n"))  # Convert to set to remove duplicates
        follow_tc = "\n".join(unique_tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertLessEqual(len(follow_out), len(source_out))


if __name__ == "__main__":
    unittest.main()
