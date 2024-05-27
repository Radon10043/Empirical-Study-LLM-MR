import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test20(self, pattern: str, file: str):
        """Metamorphic Relation 20: Running grep with and without '--binary-files=text' on a text file
        should not change the number of matches found.
        """
        # Normal pattern search
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        normal_matches = int(process.read().strip())
        process.close()

        # Pattern search treating binary files as text
        process = os.popen(f"{GREP_PATH} --binary-files=text -c {pattern} {file}")
        binary_as_text_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(normal_matches, binary_as_text_matches)


if __name__ == "__main__":
    unittest.main()
