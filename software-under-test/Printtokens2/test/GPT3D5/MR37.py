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
    def test37(self, tc: str):
        """Metamorphic Relation 37: Adding special characters to the input, the number of tokens in the output should increase."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Add special characters to the input
        special_characters = '!@#$%^&*()_+'
        follow_tc = tc + special_characters

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertGreater(len(follow_out), len(source_out))


if __name__ == "__main__":
    unittest.main()
