import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test4(self, pattern: str, file: str):
        """Metamorphic Relation 4: If the invert-match option is used, the sum of the counts of matching 
        and non-matching lines should be equal to the total number of lines in the file.
        """
        # Get source output
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        source_count = int(process.read().strip())
        process.close()

        # Get follow-up output with invert-match
        process = os.popen(f"{GREP_PATH} -v -c {pattern} {file}")
        follow_count = int(process.read().strip())
        process.close()

        # Get total number of lines in the file
        with open(file) as f:
            total_lines = len(f.readlines())

        # Verification
        self.assertEqual(source_count + follow_count, total_lines)


if __name__ == "__main__":
    unittest.main()
