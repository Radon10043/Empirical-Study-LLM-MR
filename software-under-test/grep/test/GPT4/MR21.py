import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test21(self, pattern: str, file: str):
        """Metamorphic Relation 21: If the pattern includes the beginning-of-line character '^', adding
        any characters before the '^' should not increase the number of matches.
        """
        # Get source output with the original pattern
        process = os.popen(f"{GREP_PATH} -E -c {pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Modify pattern by adding characters before '^'
        modified_pattern = f"foo{pattern}" if pattern.startswith("^") else f"foo{pattern}"

        # Get follow-up output with the modified pattern
        process = os.popen(f"{GREP_PATH} -E -c {modified_pattern} {file}")
        follow_matches = int(process.read().strip())
        process.close()

        # Verification
        if pattern.startswith("^"):
            self.assertGreaterEqual(source_matches, follow_matches)
        else:
            self.assertEqual(source_matches, follow_matches)


if __name__ == "__main__":
    unittest.main()
