from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test17(self, pattern: str, file: str):
        """Metamorphic Relation 17: If the input file is empty, the output should also be empty."""
        empty_file = "empty_file.txt"  # Example empty file

        # Create an empty file
        open(empty_file, "w").close()

        # Get source output
        process = os.popen(f"{GREP_PATH} {pattern} {empty_file}")
        source_out = process.readlines()
        process.close()

        # Verification
        self.assertFalse(source_out)  # Ensure the output is empty


if __name__ == "__main__":
    unittest.main()
