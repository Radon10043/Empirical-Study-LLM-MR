from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test39(self, pattern: str, file: str):
        group_num = randint(1, 5)

        """Metamorphic Relation 39: If the pattern is changed by using a different regex match quantifier, the output may vary based on the specific pattern and file."""
        # Get source output for the original pattern and numeric subgroup
        process_orig = os.popen(f"{GREP_PATH} -E '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with a different quantifier
        follow_pattern = f"{pattern}{group_num}?"

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
