from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test14(self, pattern: str, file: str):
        """Metamorphic Relation 14: If an invalid regex pattern is used, the output should indicate a syntax error."""
        invalid_pattern = "*"  # Example invalid regex pattern

        # Get source output
        process = os.popen(f"{GREP_PATH} {invalid_pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Verification
        self.assertTrue(any("invalid" in line.lower() for line in source_out))  # Ensure error message related to invalid pattern is present in the output


if __name__ == "__main__":
    unittest.main()
