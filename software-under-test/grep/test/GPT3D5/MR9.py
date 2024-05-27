import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test9(self, pattern: str, file: str):
        """Metamorphic Relation 9: If the count option is used, the output should only contain the count of matching lines and no actual matches."""
        # Get source output
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        count_out = process.readlines()
        process.close()

        # Verification
        for line in count_out:
            self.assertTrue(line.isdigit())  # Ensure output only contains counts and no actual matches


if __name__ == "__main__":
    unittest.main()
