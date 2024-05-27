import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test28(self, pattern: str, file: str):
        """Metamorphic Relation 28: Running a search with a repeated pattern using '{m}'
        quantifier should result in the same or fewer matches than the original pattern.
        """
        # Get output with the original pattern
        process = os.popen(f"{GREP_PATH} -E -c {pattern} {file}")
        original_matches = int(process.read().strip())
        process.close()

        # Get output with the repeated pattern using '{m}' quantifier
        repeated_pattern = f"({pattern}){{2}}"
        process = os.popen(f"{GREP_PATH} -E -c {repeated_pattern} {file}")
        repeated_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertLessEqual(repeated_matches, original_matches)


if __name__ == "__main__":
    unittest.main()
