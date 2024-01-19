from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test5(self, pattern: str, file: str):
        """Metamorphic Relation 5: If the pattern is replaced with its negation,
        the output should be complementary.
        """
        # Get source output
        process_orig = os.popen(f"{GREP_PATH} {pattern} {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with negation of the pattern
        follow_pattern = f"!{pattern}"

        # Get follow-up output
        process_follow = os.popen(f"{GREP_PATH} '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification - Ensure the combined output length is equal to the sum of individual output lengths
        combined_out = source_out + follow_out
        self.assertEqual(len(combined_out), len(set(source_out) | set(follow_out)))


if __name__ == "__main__":
    unittest.main()
