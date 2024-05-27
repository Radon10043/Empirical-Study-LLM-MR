import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test40(self, pattern: str, file: str):
        """Metamorphic Relation 40: Searching for a pattern and its reverse should yield identical results
        if the file searched is symmetrical around its midpoint.
        """
        # Search with the original pattern
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        original_matches = int(process.read().strip())
        process.close()

        reversed_pattern = os.path.join(os.path.dirname(pattern), "reversed_pattern.txt")
        tmp = str()
        with open(pattern, "r") as f:
            tmp = f.read()
        with open(reversed_pattern, "w") as f:
            f.write(tmp[::-1])

        # Search with the reversed pattern
        process = os.popen(f"{GREP_PATH} -c -f {reversed_pattern} {file}")
        reversed_matches = int(process.read().strip())
        process.close()

        # Verification - Check if file's content is symmetrical
        with open(file, 'r') as content:
            lines = content.readlines()
        if lines == lines[::-1]:   # If the file is symmetrical
            self.assertEqual(original_matches, reversed_matches)


if __name__ == "__main__":
    unittest.main()
