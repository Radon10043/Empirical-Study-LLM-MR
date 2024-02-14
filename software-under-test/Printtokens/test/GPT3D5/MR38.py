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
    def test38(self, tc: str):
        """Metamorphic Relation 38: Shuffling the order of words within a sentence, the general structure of the output should remain the same."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        tokens = tc.split()
        # Randomly shuffle the order of words within a sentence
        random.shuffle(tokens)
        follow_tc = " ".join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verify that the general structure of the output is similar
        self.assertGreaterEqual(len(follow_out), len(source_out) * 0.9)


if __name__ == "__main__":
    unittest.main()
