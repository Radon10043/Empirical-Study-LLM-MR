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
    def test13(self, tc: str):
        """Metamorphic Relation 13: Splitting and merging input lines, the output should be the same."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Split the input lines into smaller segments and merge them back
        segments = [line.split() for line in tc.strip().split("\n")]
        merged_lines = [" ".join(segment) for segment in segments]
        merged_tc = "\n".join(merged_lines)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=merged_tc, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
