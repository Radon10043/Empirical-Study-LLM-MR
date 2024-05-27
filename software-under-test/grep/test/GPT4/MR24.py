import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test24(self, pattern: str, file: str):
        """Metamorphic Relation 24: When searching with a fixed string which is also a valid regular
        expression (e.g., no special characters), using fixed-strings or basic regular expression
        options should yield the same results.
        """
        # Get source output with the fixed-strings option
        process = os.popen(f"{GREP_PATH} -F -c {pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Get follow-up output with a basic regular expression
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        follow_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(source_matches, follow_matches)


if __name__ == "__main__":
    unittest.main()
