import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test26(self, pattern: str, file: str):
        """Metamorphic Relation 26: Appending an optional character in the search pattern with '?'
        should yield at least the same number of matches as the original pattern or more.
        """
        # Get source output with the original pattern
        process = os.popen(f"{GREP_PATH} -E -c {pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Append an optional character with '?'
        modified_pattern = f"{pattern}a?"

        # Get follow-up output with the modified pattern
        process = os.popen(f"{GREP_PATH} -E -c {modified_pattern} {file}")
        follow_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertGreaterEqual(follow_matches, source_matches)


if __name__ == "__main__":
    unittest.main()
