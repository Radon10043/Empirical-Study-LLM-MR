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
    def test36(self, tc: str):
        """Metamorphic Relation 36: Generating the input with numerical sequence, the output token counts should be the same."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        numerical_sequence = "\n".join(map(str, range(1, len(tc.strip().split("\n")) + 1)))

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=numerical_sequence, text=True).split("\n")

        # Verification
        self.assertEqual(len(source_out), len(follow_out))


if __name__ == "__main__":
    unittest.main()
