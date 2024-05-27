import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test16(self, pattern: str, file: str):
        """Metamorphic Relation 16: If a different version of grep is used, the output should be consistent with the initial version."""
        other_grep_path = "/usr/local/bin/grep"  # Example different grep path

        # Get source output with original grep path
        process = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Get source output with different grep path
        process = os.popen(f"{other_grep_path} -f {pattern} {file}")
        other_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(source_out, other_out)


if __name__ == "__main__":
    unittest.main()
