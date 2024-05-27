import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test8(self, pattern: str, file: str):
        """Metamorphic Relation 8: When using the line-number option, the number of distinct line numbers
        in the output should be equal to the number of lines returned without using the line-number option.
        """
        # Get source output
        process = os.popen(f"{GREP_PATH} {pattern} {file}")
        source_lines = process.readlines()
        process.close()

        # Get follow-up output with line-number
        process = os.popen(f"{GREP_PATH} -n {pattern} {file}")
        follow_lines = process.readlines()
        follow_line_numbers = {int(line.split(":", 1)[0]) for line in follow_lines}
        process.close()

        # Verification
        self.assertEqual(len(source_lines), len(follow_line_numbers))


if __name__ == "__main__":
    unittest.main()
