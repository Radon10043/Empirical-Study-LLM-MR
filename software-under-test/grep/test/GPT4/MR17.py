import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test17(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 17: A pattern search with the '--extended-regexp' option
        followed by disabling it should yield fewer or the same matches.
        """
        # Extended regexp search
        process = os.popen(f"{GREP_PATH} -E -c -f {pattern} {file}")
        extended_regexp_matches = int(process.read().strip())
        process.close()

        # Basic regexp search
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        basic_regexp_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertLessEqual(basic_regexp_matches, extended_regexp_matches)


if __name__ == "__main__":
    unittest.main()
