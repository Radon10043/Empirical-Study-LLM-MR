from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test10(self, pattern: str, file: str):
        """Metamorphic Relation 10: If the pattern is changed to its logical NOT form, the output should be complementary to the original output."""
        # Get source output
        process_orig = os.popen(f"{GREP_PATH} {pattern} {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with logical NOT of the pattern
        follow_pattern = f"!( {pattern} )"

        # Get follow-up output
        process_follow = os.popen(f"{GREP_PATH} -v '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        combined_out = source_out + follow_out
        self.assertEqual(len(combined_out), len(set(source_out) | set(follow_out)))


if __name__ == "__main__":
    unittest.main()
