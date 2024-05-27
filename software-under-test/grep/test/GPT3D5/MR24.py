import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test24(self, pattern: str, file: str):
        """Metamorphic Relation 24: If the recursive search option is used with a specific file type, the output should be the same as when filtering the file type in a single recursive search."""
        file_type = "*.txt"  # Example file type
        # Get source output with recursive search filtered by file type
        process = os.popen(f"{GREP_PATH} --include={file_type} -f {pattern} {os.path.dirname(file)}")
        filtered_out = process.readlines()
        process.close()

        # Get source output with single recursive search and filtering by file type
        process = os.popen(f"{GREP_PATH} -r -f {pattern} --include={file_type} {os.path.dirname(file)}")
        recursive_filtered_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(filtered_out, recursive_filtered_out)


if __name__ == "__main__":
    unittest.main()
