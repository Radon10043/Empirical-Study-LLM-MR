import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test29(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 29: Searching for any line with '.' should always yield a count equal
        to or greater than any specific pattern search.
        """
        # Get output with the specific pattern
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        specific_matches = int(process.read().strip())
        process.close()

        # Get output when searching for any line with '.'
        any_line_pattern = "."
        process = os.popen(f"{GREP_PATH} -c {any_line_pattern} {file}")
        any_line_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertGreaterEqual(any_line_matches, specific_matches)


if __name__ == "__main__":
    unittest.main()
