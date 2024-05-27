import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test28(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 28: Running a search with a repeated pattern using '{m}'
        quantifier should result in the same or fewer matches than the original pattern.
        """
        # Get output with the original pattern
        process = os.popen(f"{GREP_PATH} -E -c -f {pattern} {file}")
        original_matches = int(process.read().strip())
        process.close()

        repeated_pattern = os.path.join(os.path.dirname(pattern), "repeated_pattern.txt")
        tmp = str()
        with open(pattern, "r") as f:
            tmp = f.read().strip()
        with open(repeated_pattern, "w") as f:
            f.write(f"{tmp}{{2}}")

        # Get output with the repeated pattern using '{m}' quantifier
        process = os.popen(f"{GREP_PATH} -E -c -f {repeated_pattern} {file}")
        repeated_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertLessEqual(repeated_matches, original_matches)


if __name__ == "__main__":
    unittest.main()
