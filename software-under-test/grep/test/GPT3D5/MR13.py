from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test13(self, pattern: str, file: str):
        """Metamorphic Relation 13: If no file is specified, the output should be the same as when searching the standard input."""
        unittest.TestCase.skipTest(self, "This test is not applicable for the current version of grep")

        # Get source output with a file specified
        process = os.popen(f"{GREP_PATH} {pattern} {file}")
        file_out = process.readlines()
        process.close()

        # Get source output without specifying a file
        process = os.popen(f"{GREP_PATH} {pattern}")
        stdin_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(file_out, stdin_out)


if __name__ == "__main__":
    unittest.main()
