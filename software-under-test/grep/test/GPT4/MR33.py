import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test33(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 33: Running 'grep' with a pattern in a file that has been duplicated
        line by line should result in exactly double the number of matches.
        """
        # Get output from the original file
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        original_matches = int(process.read().strip())
        process.close()

        # Duplicate file content
        double_pattern = os.path.join(os.path.dirname(file), "double_pattern.txt")
        tmp = str()
        with open(pattern, mode="r") as f:
            tmp = f.read()
        with open(double_pattern, "w") as f:
            f.write(tmp)
            f.write(tmp)

        # Get output from the duplicated file
        process = os.popen(f"{GREP_PATH} -c {pattern} {double_pattern}")
        duplicated_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(duplicated_matches, 2 * original_matches)


if __name__ == "__main__":
    unittest.main()
