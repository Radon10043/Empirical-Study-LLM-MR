import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases_combinations(1000))
    def test38(self, pattern: str, file1: str, file2: str): # Fixed
        """Metamorphic Relation 38: Searching for a pattern with the '--files-without-match' option should
        yield a set of files that is complementary to the set yielded by '--files-with-matches' option.
        """
        files = [file1, file2]

        # Search for files with matches
        process = os.popen(f"{GREP_PATH} -l -f {pattern} " + " ".join(files))
        files_with_matches = set(process.read().strip().split('\n'))
        process.close()

        # Search for files without matches
        process = os.popen(f"{GREP_PATH} -L -f {pattern} " + " ".join(files))
        files_without_matches = set(process.read().strip().split('\n'))
        process.close()

        # Verification
        all_files = set(files)
        self.assertEqual(files_with_matches.union(files_without_matches), all_files)
        self.assertTrue(files_with_matches.isdisjoint(files_without_matches))


if __name__ == "__main__":
    unittest.main()
