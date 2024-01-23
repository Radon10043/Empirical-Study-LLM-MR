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
    def test15(self, tc: str):
        """Metamorphic Relation 15: Shuffling the tokens within each line of the input, the output should remain unchanged."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Shuffle the tokens within each line of the input
        shuffled_tokens = []
        for line in tc.strip().split("\n"):
            tokens = line.split()
            random.shuffle(tokens)
            shuffled_tokens.append(" ".join(tokens))
        shuffled_tc = "\n".join(shuffled_tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=shuffled_tc, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
