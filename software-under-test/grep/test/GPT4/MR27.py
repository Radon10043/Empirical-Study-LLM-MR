import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test27(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 27: Searching for a word with a boundary '\bWORD\b' should not yield more
        results than searching for the word 'WORD' without word boundaries.
        """
        # Search for the word without word boundaries
        simple_pattern = pattern
        process = os.popen(f"{GREP_PATH} -E -c -f {simple_pattern} {file}")
        simple_matches = int(process.read().strip())
        process.close()

        word_boundary_pattern = os.path.join(os.path.dirname(pattern), "word_boundary_pattern.txt")
        with open(pattern, "r") as f:
            pattern = f.read().strip()
        with open(word_boundary_pattern, "w") as f:
            f.write(f"\\b{pattern}\\b")

        # Search for the word with word boundaries
        process = os.popen(f"{GREP_PATH} -w -c -f {word_boundary_pattern} {file}")
        word_boundary_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertGreaterEqual(simple_matches, word_boundary_matches)


if __name__ == "__main__":
    unittest.main()
