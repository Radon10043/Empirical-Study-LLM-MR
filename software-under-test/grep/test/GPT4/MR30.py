import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test30(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 30: Searching with '--color=always' or '--color=never' options should
        not change the number of matches found compared to without these color options.
        """
        # Get output without color option
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        no_color_matches = int(process.read().strip())
        process.close()

        # Get output with '--color=always' option
        process = os.popen(f"{GREP_PATH} --color=always -c -f {pattern} {file}")
        color_always_matches = int(process.read().strip())
        process.close()

        # Get output with '--color=never' option
        process = os.popen(f"{GREP_PATH} --color=never -c -f {pattern} {file}")
        color_never_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(no_color_matches, color_always_matches)
        self.assertEqual(no_color_matches, color_never_matches)


if __name__ == "__main__":
    unittest.main()
