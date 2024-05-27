import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test25(self, pattern: str, file1: str, file2: str):
        """Metamorphic Relation 25: Searching for a pattern in two files separately and then in both
        together with '--no-filename' should yield a total number of matches that is the sum of the
        two separate searches.
        """
        # Get source output from searching the first file
        process = os.popen(f"{GREP_PATH} -c {pattern} {file1}")
        file1_matches = int(process.read().strip())
        process.close()

        # Get source output from searching the second file
        process = os.popen(f"{GREP_PATH} -c {pattern} {file2}")
        file2_matches = int(process.read().strip())
        process.close()

        # Search in both files together without printing filenames
        process = os.popen(f"{GREP_PATH} --no-filename -c {pattern} {file1} {file2}")
        combined_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(combined_matches, file1_matches + file2_matches)


if __name__ == "__main__":
    unittest.main()
