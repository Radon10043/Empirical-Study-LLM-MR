import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test7(self, pattern: str, file: str):
        """Metamorphic Relation 7: If the search is performed on a specific line number, the output should contain only that line."""
        line_number = 5  # Example line number
        # Get source output
        process = os.popen(f"{GREP_PATH} -n {pattern} {file} | grep :{line_number}:")
        source_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(len(source_out), 1)  # Ensure only the specified line is in the output


if __name__ == "__main__":
    unittest.main()
