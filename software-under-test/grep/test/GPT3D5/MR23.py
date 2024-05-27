import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test23(self, pattern: str, file: str):
        """Metamorphic Relation 23: If the '-m' option is used to limit the number of matching lines, the output should contain at most the specified number of lines."""
        num_lines = 5  # Example number of lines
        # Get source output with limited number of matching lines
        process = os.popen(f"{GREP_PATH} -m {num_lines} {pattern} {file}")
        limited_out = process.readlines()
        process.close()

        # Verification
        self.assertLessEqual(len(limited_out), num_lines)


if __name__ == "__main__":
    unittest.main()
