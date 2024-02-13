from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test12(self, pattern: str, file: str):
        """Metamorphic Relation 12: If a different file is used instead of a regular file, the output should be an error message indicating the file does not exist."""
        invalid_file = "invalid_file.txt"  # Example non-existent file

        # Get source output
        process = os.popen(f"{GREP_PATH} {pattern} {invalid_file}")
        source_out = process.readlines()
        process.close()

        # Verification
        self.assertTrue(any("No such file or directory" in line for line in source_out))  # Ensure the error message is present in the output


if __name__ == "__main__":
    unittest.main()
