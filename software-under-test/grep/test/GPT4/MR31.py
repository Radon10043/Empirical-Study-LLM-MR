import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test31(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 31: Searching with the '--exclude-dir' option should not increase the
        number of matches when searching recursively because excluded directories are skipped.
        """
        # Get output when searching recursively
        process = os.popen(f"{GREP_PATH} -r -c -f {pattern} " + os.path.dirname(file))
        recursive_matches = sum([int(line.split(":")[1]) for line in process.readlines()])
        process.close()

        # Get output when excluding a directory and searching recursively
        process = os.popen(f"{GREP_PATH} -r --exclude-dir=nonexistent --exclude-dir=.git -c -f {pattern} " + os.path.dirname(file))
        exclude_dir_matches = sum([int(line.split(":")[1]) for line in process.readlines()])
        process.close()

        # Verification
        self.assertLessEqual(exclude_dir_matches, recursive_matches)


if __name__ == "__main__":
    unittest.main()
