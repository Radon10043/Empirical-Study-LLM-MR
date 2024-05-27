import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test43(self, pattern: str, file: str):
        """Metamorphic Relation 43: Searching with a pattern prefixed with the context control 'A' for 'after context'
        should yield the same number of matches as without using context control, since this affects the output
        format rather than the match count.
        """
        # Search with the original pattern
        process = os.popen(f"{GREP_PATH} -c {pattern} {file}")
        original_matches = int(process.read().strip())
        process.close()

        # Search with the pattern using after context control 'A'
        process = os.popen(f"{GREP_PATH} -A 1 -c {pattern} {file}")
        with_after_context_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(original_matches, with_after_context_matches)


if __name__ == "__main__":
    unittest.main()
