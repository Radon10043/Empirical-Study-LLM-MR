import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test19(self, pattern: str, file: str):
        """Metamorphic Relation 19: Negating a pattern with '^' in front and using '--invert-match'
        should result in complementing line counts, summing up to the total number of lines.
        """
        # Get the count with a negated pattern
        negated_pattern = f"^{pattern}"
        process = os.popen(f"{GREP_PATH} -E -c {negated_pattern} {file}")
        negated_pattern_matches = int(process.read().strip())
        process.close()

        # Use the 'invert-match' option for the original pattern
        process = os.popen(f"{GREP_PATH} -v -c {pattern} {file}")
        invert_match_pattern_matches = int(process.read().strip())
        process.close()

        # Count total lines
        with open(file) as f:
            total_lines = sum(1 for line in f)

        # Verification
        self.assertEqual(negated_pattern_matches, invert_match_pattern_matches)
        self.assertEqual(negated_pattern_matches + invert_match_pattern_matches, total_lines)


if __name__ == "__main__":
    unittest.main()
