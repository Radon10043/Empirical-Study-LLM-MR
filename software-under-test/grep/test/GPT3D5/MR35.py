from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test35(self, pattern: str, file: str):
        """Metamorphic Relation 35: If the pattern is changed by appending a back-reference and a numeric subgroup, the output may change based on the specific input files and patterns."""
        group_num = randint(1, 5)

        # Get source output for the original pattern and numeric subgroup
        process_orig = os.popen(f"{GREP_PATH} -E '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with the back-reference and numeric subgroup
        follow_pattern = f"{pattern}\\{group_num}"

        # Get follow-up output
        process_follow = os.popen(f"{GREP_PATH} -E '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        combined_out = source_out + follow_out
        # Ensure that the combined output length is equal to the sum of individual output lengths
        self.assertEqual(len(combined_out), len(set(source_out) | set(follow_out)))


if __name__ == "__main__":
    unittest.main()
