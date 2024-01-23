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
    def test22(self, tc: str):
        """Metamorphic Relation 22: Inserting a new token in each line of the input, the count of tokens in the output should increase."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Insert a new token in each line of the input
        tokens = tc.strip().split("\n")
        follow_tokens = [token + " newtoken" for token in tokens]
        follow_tc = "\n".join(follow_tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertGreater(len(follow_out), len(source_out))


if __name__ == "__main__":
    unittest.main()
