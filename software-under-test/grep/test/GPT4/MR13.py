import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test13(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 13: A pattern search that matches the entire line should return the same
        results as using the fixed-strings option if the pattern contains no regular expressions.
        """
        entire_line_pattern = os.path.join(os.path.dirname(pattern), "entire_line_pattern.txt")
        with open(entire_line_pattern, mode="w") as f:
            with open(pattern, mode="r") as f1:
                f.write("^" + f1.read().rstrip() + "$")

        # Get source output by matching the entire line
        process = os.popen(f"{GREP_PATH} -c -f {entire_line_pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Get follow-up output with the fixed-strings option
        process = os.popen(f"{GREP_PATH} -F -c -f {pattern} {file}")
        follow_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(source_matches, follow_matches)


if __name__ == "__main__":
    unittest.main()
