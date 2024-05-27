import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(10))
    def test9(self, pattern: str, file: str):   # Fixed, illegal
        """Metamorphic Relation 9: Concatenating two patterns with an OR ('|') symbol and using extended
        regular expressions should yield a count of matches that is equal to or higher than the individual
        pattern counts.
        """
        self.fail("Illegal MR")

        file_path = os.path.join(os.path.dirname(pattern), "pattern.tmp.txt")
        gen_pattern_randomly(file_path)
        patterns = [pattern, file_path]

        # Get source output for first pattern
        process = os.popen(f"{GREP_PATH} -E -c {patterns[0]} {file}")
        first_pattern_matches = int(process.read().strip())
        process.close()

        # Get source output for second pattern
        process = os.popen(f"{GREP_PATH} -E -c {patterns[1]} {file}")
        second_pattern_matches = int(process.read().strip())
        process.close()

        # Combine patterns with OR
        combined_pattern = f"{patterns[0]}|{patterns[1]}"

        # Get follow-up output with combined pattern
        process = os.popen(f"{GREP_PATH} -E -c {combined_pattern} {file}")
        combined_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertGreaterEqual(combined_matches, max(first_pattern_matches, second_pattern_matches))


if __name__ == "__main__":
    unittest.main()
