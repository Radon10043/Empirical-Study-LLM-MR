from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test42(self, pattern: str, file: str):
        """Metamorphic Relation 42: If the pattern is changed by adding a positive lookbehind assertion, the output should remain the same."""
        # Get source output with original pattern
        process_orig = os.popen(f"{GREP_PATH} '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with the pattern and positive lookbehind assertion
        follow_pattern = f"(?<={pattern})"

        # Get follow-up output for the modified pattern
        process_follow = os.popen(f"{GREP_PATH} '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
