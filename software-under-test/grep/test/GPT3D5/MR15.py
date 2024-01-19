from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test15(self, pattern: str, file: str):
        """Metamorphic Relation 15: If the pattern is changed to its complement with respect to another pattern, the output should reflect the complement of matches."""
        # Get source output for the original pattern
        process_orig = os.popen(f"{GREP_PATH} '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with a complement pattern
        complement_pattern = "another_pattern"
        follow_pattern = f"({pattern})-({complement_pattern})"

        # Get follow-up output for the complement pattern
        process_follow = os.popen(f"{GREP_PATH} '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        combined_out = source_out + follow_out
        self.assertEqual(len(combined_out), len(set(source_out) | set(follow_out)))


if __name__ == "__main__":
    unittest.main()
