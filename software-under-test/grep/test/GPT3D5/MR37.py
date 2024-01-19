from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test37(self, pattern: str, file: str):
        """Metamorphic Relation 37: If the pattern is changed to its atomic grouping form and combined with the --line-buffered option, the output should remain the same."""
        # Get source output with original pattern and --line-buffered option
        process_orig = os.popen(f"{GREP_PATH} --line-buffered '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with the pattern in atomic grouping form
        follow_pattern = f"(?<={pattern})"

        # Get follow-up output with --line-buffered option
        process_follow = os.popen(f"{GREP_PATH} --line-buffered '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
