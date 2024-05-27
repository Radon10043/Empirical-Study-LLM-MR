import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases_combinations(1000))
    def test42(self, pattern: str, file1: str, file2: str):
        """Metamorphic Relation 42: Searching for a pattern in one file and redirecting another file's content
        to standard input should yield the same results as searching in both files separately.
        """
        # Search in the first file
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file1}")
        file1_matches = int(process.read().strip())
        process.close()

        # Search in the second file redirected to stdin
        process = os.popen(f"cat {file2} | {GREP_PATH} -c -f {pattern}")
        file2_stdin_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(file1_matches, file2_stdin_matches)


if __name__ == "__main__":
    unittest.main()
