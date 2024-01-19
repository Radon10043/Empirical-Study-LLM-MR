from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test36(self, pattern: str, file: str):
        """Metamorphic Relation 36: If the pattern is changed by adding a word boundary assertion, the output should reflect the matches with the added word boundary."""
        # Get source output for the original pattern
        process_orig = os.popen(f"{GREP_PATH} '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with word boundary assertion added to the pattern
        follow_pattern = r"\b" + pattern + r"\b"

        # Get follow-up output for the modified pattern with word boundary assertion
        process_follow = os.popen(f"{GREP_PATH} '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        combined_out = source_out + follow_out
        # Ensure that the combined output length is equal to the sum of individual output lengths
        self.assertEqual(len(combined_out), len(set(source_out) | set(follow_out)))


if __name__ == "__main__":
    unittest.main()
