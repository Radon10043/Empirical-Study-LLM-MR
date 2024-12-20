import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test10(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 10: Using the recursive option should result in the same or more matches than 
        just searching the specified file when the file is inside a directory.
        """
        # Get source output for specified file
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        file_matches = int(process.read())
        process.close()

        # Get follow-up output using recursive within the file's directory
        file_dir = os.path.dirname(file)
        process = os.popen(f"{GREP_PATH} -r -c -f {pattern} {file_dir}")
        recursive_matches = [int(line.split(":")[1]) for line in process.readlines()]
        process.close()

        # Verification
        self.assertGreaterEqual(sum(recursive_matches), file_matches)


if __name__ == "__main__":
    unittest.main()
