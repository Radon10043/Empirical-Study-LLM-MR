import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test9(self, pattern: str, file: str):   # Fixed
        """Metamorphic Relation 9: Concatenating two patterns with an OR ('|') symbol and using extended
        regular expressions should yield a count of matches that is equal to or higher than the individual
        pattern counts.
        """
        another_pattern = os.path.join(os.path.dirname(pattern), "pattern.tmp.txt")
        gen_pattern_randomly(another_pattern)
        patterns = [pattern, another_pattern]

        # Get source output for first pattern
        process = os.popen(f"{GREP_PATH} -E -c -f {patterns[0]} {file}")
        first_pattern_matches = int(process.read().strip())
        process.close()

        # Get source output for second pattern
        process = os.popen(f"{GREP_PATH} -E -c -f {patterns[1]} {file}")
        second_pattern_matches = int(process.read().strip())
        process.close()

        # Combine patterns with OR
        combined_pattern = os.path.join(os.path.dirname(pattern), "combined_pattern.txt")
        with open(combined_pattern, mode="w") as f:
            with open(patterns[0], mode="r") as f1:
                f.write(f1.read().rstrip())
            f.write("|")
            with open(patterns[1], mode="r") as f2:
                f.write(f2.read().rstrip())

        # Get follow-up output with combined pattern
        process = os.popen(f"{GREP_PATH} -E -c -f {combined_pattern} {file}")
        combined_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertGreaterEqual(combined_matches, max(first_pattern_matches, second_pattern_matches))


if __name__ == "__main__":
    unittest.main()
