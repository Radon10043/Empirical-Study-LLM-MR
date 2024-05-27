import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test41(self, pattern: str, file: str):
        """Metamorphic Relation 41: Searching with a pattern containing a group '(PATTERN)' should yield the
        same number of matches as searching with the pattern without the group.
        """
        # Search with the original pattern
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        original_matches = int(process.read().strip())
        process.close()

        grouped_pattern = os.path.join(os.path.dirname(pattern), "grouped_pattern.txt")
        tmp = str()
        with open(pattern, "r") as f:
            tmp = f.read()
        with open(grouped_pattern, "w") as f:
            f.write(f"({tmp})")

        # Search with the grouped pattern
        process = os.popen(f"{GREP_PATH} -E -c -f {grouped_pattern} {file}")
        grouped_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(original_matches, grouped_matches)


if __name__ == "__main__":
    unittest.main()
