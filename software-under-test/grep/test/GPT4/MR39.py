import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test39(self, pattern: str, file: str):
        """Metamorphic Relation 39: Searching with a pattern contained within another should yield fewer or
        the same number of matches when comparing the smaller pattern vs. the larger pattern.
        """
        # Search with the smaller contained pattern
        smaller_pattern = pattern[1:-1]  # Assuming pattern is at least 3 characters long
        process = os.popen(f"{GREP_PATH} -c {smaller_pattern} {file}")
        smaller_pattern_matches = int(process.read().strip())
        process.close()

        # Search with the larger pattern
        larger_pattern = pattern
        process = os.popen(f"{GREP_PATH} -c {larger_pattern} {file}")
        larger_pattern_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertGreaterEqual(larger_pattern_matches, smaller_pattern_matches)


if __name__ == "__main__":
    unittest.main()
