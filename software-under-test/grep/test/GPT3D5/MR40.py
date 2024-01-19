from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test40(self, pattern: str, file: str):
        """Metamorphic Relation 40: If the pattern is changed to its negation form and combined with the --null-data option, the output should remain the same."""
        # Get source output with original pattern and --null-data option
        process_orig = os.popen(f"{GREP_PATH} --null-data '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with the negation form of the pattern
        follow_pattern = f"!({pattern})"

        # Get follow-up output with --null-data option
        process_follow = os.popen(f"{GREP_PATH} --null-data '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
