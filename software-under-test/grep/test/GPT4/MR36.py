import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases_combinations(1000))
    def test36(self, pattern: str, file1: str, file2: str):
        """Metamorphic Relation 36: Searching for a pattern in the concatenation of two files should yield
        the number of matches equal to the sum of matches from each file when searched separately.
        """
        # Search in the first file
        process = os.popen(f"{GREP_PATH} -c {pattern} {file1}")
        file1_matches = int(process.read().strip())
        process.close()

        # Search in the second file
        process = os.popen(f"{GREP_PATH} -c {pattern} {file2}")
        file2_matches = int(process.read().strip())
        process.close()

        # Concatenate files
        concatenated_file = f"{file1}{file2}"
        with open(concatenated_file, "w") as outfile:
            with open(file1, "r") as file1_content:
                outfile.write(file1_content.read())
            with open(file2, "r") as file2_content:
                outfile.write(file2_content.read())

        # Search in the concatenated file
        process = os.popen(f"{GREP_PATH} -c {pattern} {concatenated_file}")
        concatenated_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(file1_matches + file2_matches, concatenated_matches)
        os.remove(concatenated_file)


if __name__ == "__main__":
    unittest.main()
