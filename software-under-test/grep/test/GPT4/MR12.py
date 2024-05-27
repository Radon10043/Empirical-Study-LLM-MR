import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test12(self, pattern: str, file: str):
        """Metamorphic Relation 12: Adding a redundant quantifier '+' to a single character in the pattern
        should not alter the number of matches found.
        """
        # Get source output with the original pattern
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Modify pattern by adding a '+' to the first character
        modified_pattern = pattern[0] + "+" + pattern[1:]

        # Get follow-up output with the modified pattern
        process = os.popen(f"{GREP_PATH} -E -c {modified_pattern} {file}")
        follow_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(source_matches, follow_matches)


if __name__ == "__main__":
    unittest.main()
