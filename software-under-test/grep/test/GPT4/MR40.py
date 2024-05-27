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
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        original_matches = int(process.read().strip())
        process.close()

        # Create a reversed pattern by reversing the order of characters in the original pattern
        reversed_pattern = pattern[::-1]

        # Search with the reversed pattern
        process = os.popen(f"{GREP_PATH} -c {reversed_pattern} {file}")
        reversed_matches = int(process.read().strip())
        process.close()

        # Verification - Check if file's content is symmetrical
        with open(file, 'r') as content:
            lines = content.readlines()
        if lines == lines[::-1]:   # If the file is symmetrical
            self.assertEqual(original_matches, reversed_matches)


if __name__ == "__main__":
    unittest.main()
