import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test32(self, pattern: str, file: str, file_extension: str):
        """Metamorphic Relation 32: When searching recursively, using '--include' to specify a file
        extension should yield fewer or the same number of matches as a search without the option.
        """
        # Get output when searching recursively without include
        process = os.popen(f"{GREP_PATH} -r -c {pattern} .")
        no_include_matches = int(process.read().strip())
        process.close()

        # Get output when including only files with the specified extension
        process = os.popen(f"{GREP_PATH} -r --include=*.{file_extension} -c {pattern} .")
        include_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertLessEqual(include_matches, no_include_matches)


if __name__ == "__main__":
    unittest.main()
