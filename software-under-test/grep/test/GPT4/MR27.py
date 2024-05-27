import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test27(self, pattern: str, file: str):
        """Metamorphic Relation 27: Searching for a word with a boundary '\bWORD\b' should not yield more
        results than searching for the word 'WORD' without word boundaries.
        """
        # Search for the word without word boundaries
        simple_pattern = f"{pattern}"
        process = os.popen(f"{GREP_PATH} -E -c {simple_pattern} {file}")
        simple_matches = int(process.read().strip())
        process.close()

        # Search for the word with word boundaries
        word_boundary_pattern = f"\\b{pattern}\\b"
        process = os.popen(f"{GREP_PATH} -w -c {word_boundary_pattern} {file}")
        word_boundary_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertGreaterEqual(simple_matches, word_boundary_matches)


if __name__ == "__main__":
    unittest.main()
