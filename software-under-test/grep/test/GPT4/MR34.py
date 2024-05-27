import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases_combinations(1000))
    def test34(self, pattern: str, file1: str, file2: str):
        """Metamorphic Relation 34: Searching for a pattern in two files with '--no-messages' should not
        report errors for non-existing files, and the number of matches should only count from existing
        files.
        """
        # Search in the existing file
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file1}")
        existing_file_matches = int(process.read().strip())
        process.close()

        # Search in both existing and non-existing files with no error messages
        process = os.popen(f"{GREP_PATH} --no-messages -c -f {pattern} {file1} nonexistent_file {file2}")
        combined_matches = process.read().strip()
        process.close()

        # Verify that non-existing files don't contribute to the match count
        # If file2 exists, combined_matches should be the sum of matches in file1 and file2.
        # If file2 does not exist, combined_matches should be equal to existing_file_matches.
        if os.path.exists(file2):
            process = os.popen(f"{GREP_PATH} -c -f {pattern} {file2}")
            file2_matches = int(process.read().strip())
            process.close()
            combined_expected = existing_file_matches + file2_matches
        else:
            combined_expected = existing_file_matches

        # Verification
        combined_matches = int(combined_matches) if combined_matches != "" else 0
        self.assertEqual(combined_matches, combined_expected)


if __name__ == "__main__":
    unittest.main()
