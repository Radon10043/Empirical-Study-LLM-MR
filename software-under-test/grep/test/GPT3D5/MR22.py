from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test22(self, pattern: str, file: str):
        """Metamorphic Relation 22: If the pattern is changed by applying zero-width negative lookahead, the output should reflect the absence of the negative lookahead pattern."""
        # Get source output
        process_orig = os.popen(f"{GREP_PATH} '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with the pattern modified by zero-width negative lookahead
        follow_pattern = f"{pattern}(?!{pattern})"

        # Get follow-up output
        process_follow = os.popen(f"{GREP_PATH} '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        combined_out = source_out + follow_out
        self.assertEqual(len(combined_out), len(set(source_out) | set(follow_out)))


if __name__ == "__main__":
    unittest.main()
