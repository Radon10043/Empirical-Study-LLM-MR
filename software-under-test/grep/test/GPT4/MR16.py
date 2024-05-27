import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test16(self, pattern: str, file1: str, file2: str):
        """Metamorphic Relation 16: A pattern search in a file concatenated with another should yield
        the sum of matches found in each file individually.
        """
        # Get source output from the first file
        process = os.popen(f"{GREP_PATH} -c {pattern} {file1}")
        file1_matches = int(process.read().strip())
        process.close()

        # Get source output from the second file
        process = os.popen(f"{GREP_PATH} -c {pattern} {file2}")
        file2_matches = int(process.read().strip())
        process.close()

        # Concatenate files and search
        concatenated_file = f"{file1} {file2}"
        process = os.popen(f"{GREP_PATH} -c {pattern} {concatenated_file}")
        concatenated_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(file1_matches + file2_matches, concatenated_matches)


if __name__ == "__main__":
    unittest.main()
