import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test33(self, pattern: str, file: str):
        """Metamorphic Relation 33: Running 'grep' with a pattern in a file that has been duplicated
        line by line should result in exactly double the number of matches.
        """
        # Get output from the original file
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        original_matches = int(process.read().strip())
        process.close()

        # Duplicate file content line by line
        doubled_file = f"{file}_doubled"
        with open(file, "r") as original, open(doubled_file, "w") as doubled:
            for line in original:
                doubled.write(line)
                doubled.write(line)

        # Get output from the duplicated file
        process = os.popen(f"{GREP_PATH} -c {pattern} {doubled_file}")
        duplicated_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(duplicated_matches, 2 * original_matches)


if __name__ == "__main__":
    unittest.main()
