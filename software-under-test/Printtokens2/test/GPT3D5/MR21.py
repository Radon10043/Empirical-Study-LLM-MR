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
    def test21(self, tc: str):
        """Metamorphic Relation 21: Replacing all letters with uppercase, the output should remain unchanged."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Replace all letters with uppercase in the input
        uppercase_tc = tc.upper()

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=uppercase_tc, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
