from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test14(self, pattern: str, file: str):
        """Metamorphic Relation 14: If the pattern is changed to its intersection with another pattern, the output should reflect the intersection of matches."""
        # Get source output for the original pattern
        process_orig = os.popen(f"{GREP_PATH} '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with an intersection pattern
        intersecting_pattern = "another_pattern"
        follow_pattern = f"({pattern})&({intersecting_pattern})"

        # Get follow-up output for the intersection pattern
        process_follow = os.popen(f"{GREP_PATH} '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        combined_out = source_out + follow_out
        self.assertEqual(len(combined_out), len(set(source_out) | set(follow_out)))


if __name__ == "__main__":
    unittest.main()
