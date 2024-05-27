import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test18(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 18: A pattern search in a single file versus searching in that file
        combined with '/dev/null' should yield the same results.
        """
        # Single file search
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        single_file_matches = int(process.read().strip())
        process.close()

        # Combined search with /dev/null
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file} /dev/null")
        combined_file_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(single_file_matches, combined_file_matches)


if __name__ == "__main__":
    unittest.main()
