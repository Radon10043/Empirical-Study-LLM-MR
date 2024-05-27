import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test11(self, pattern: str, file: str):
        """Metamorphic Relation 11: Doubling the pattern using an OR operator in extended mode
        should not change the number of matches.
        """
        # Get source output with the original pattern in extended mode
        process = os.popen(f"{GREP_PATH} -E -c {pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Double the pattern using an OR operator
        doubled_pattern = f"({pattern})|({pattern})"

        # Get follow-up output with the doubled pattern in extended mode
        process = os.popen(f"{GREP_PATH} -E -c {doubled_pattern} {file}")
        follow_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(source_matches, follow_matches)


if __name__ == "__main__":
    unittest.main()
