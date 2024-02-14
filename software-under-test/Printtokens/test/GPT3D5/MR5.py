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
    def test5(self, tc: str):
        """Metamorphic Relation 5: Swapping the positions of two words, the output should change according to the swapped tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        tokens = tc.split()
        # Swap the first two words
        tokens[0], tokens[1] = tokens[1], tokens[0]
        follow_tc = " ".join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertNotEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
