import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test23(self, pattern: str, file: str):
        """Metamorphic Relation 23: Inverting a match and then inverting it again should result in the
        same number of matches as the original query.
        """
        # Get source output by searching with the original pattern
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Invert match of the original pattern
        process = os.popen(f"{GREP_PATH} -v -c {pattern} {file}")
        invert_match1 = int(process.read().strip())
        process.close()

        # Invert match again
        process = os.popen(f"{GREP_PATH} -v -c {pattern} {file} | {GREP_PATH} -v -c")
        invert_match2 = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(source_matches, invert_match2)


if __name__ == "__main__":
    unittest.main()
