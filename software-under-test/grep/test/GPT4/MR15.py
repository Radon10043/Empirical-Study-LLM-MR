import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test15(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 15: Using the count option with and without the line-number option
        should yield the same count of matched lines.
        """
        # Get source output with the count option
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        source_count = int(process.read().strip())
        process.close()

        # Get follow-up output with both count and line-number options
        process = os.popen(f"{GREP_PATH} -c -n -f {pattern} {file}")
        follow_count = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(source_count, follow_count)


if __name__ == "__main__":
    unittest.main()
