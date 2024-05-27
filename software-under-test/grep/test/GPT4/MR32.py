import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases_combinations(1000))
    def test32(self, pattern: str, file: str, file_extension: str): # Fixed
        """Metamorphic Relation 32: When searching recursively, using '--include' to specify a file
        extension should yield fewer or the same number of matches as a search without the option.
        """
        # Get output when searching recursively without include
        process = os.popen(f"{GREP_PATH} -r -c -f {pattern} " + os.path.dirname(file))
        no_include_matches = sum([int(line.split(":")[1]) for line in process.readlines()])
        process.close()

        # Get output when including only files with the specified extension
        process = os.popen(f"{GREP_PATH} -r --include=*.{file_extension} -c -f {pattern} " + os.path.dirname(file))
        include_matches = sum([int(line.split(":")[1]) for line in process.readlines()])
        process.close()

        # Verification
        self.assertLessEqual(include_matches, no_include_matches)


if __name__ == "__main__":
    unittest.main()
