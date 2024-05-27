import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test39(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 39: Searching with a pattern contained within another should yield fewer or
        the same number of matches when comparing the smaller pattern vs. the larger pattern.
        """
        tmp = str()
        with open(pattern, "r") as f:
            tmp = f.read()

        if len(tmp) < 3:
            self.skipTest("Pattern is too short to be contained within another pattern.")

        smaller_pattern = os.path.join(os.path.dirname(pattern), "smaller_pattern.txt")
        with open(smaller_pattern, "w") as f:
            f.write(tmp[1:-1])

        # Search with the smaller contained pattern
        process = os.popen(f"{GREP_PATH} -c -f {smaller_pattern} {file}")
        smaller_pattern_matches = int(process.read().strip())
        process.close()

        # Search with the larger pattern
        larger_pattern = pattern
        process = os.popen(f"{GREP_PATH} -c -f {larger_pattern} {file}")
        larger_pattern_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertGreaterEqual(larger_pattern_matches, smaller_pattern_matches)


if __name__ == "__main__":
    unittest.main()
