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
    def test40(self, tc: str):
        """Metamorphic Relation 40: Reversing the order of tokens within each line, the output should contain the same tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Reverse the order of tokens within each line
        reversed_tokens = [ " ".join(line.split()[::-1]) for line in tc.strip().split("\n")]
        follow_tc = "\n".join(reversed_tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(set(source_out), set(follow_out))


if __name__ == "__main__":
    unittest.main()
