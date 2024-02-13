from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases_combinations(1000))
    def test8(self, pattern: str, file1: str, file2: str):
        """Metamorphic Relation 8: If multiple files are provided, the output should be the combined output of each individual file search."""
        # Get source output
        process = os.popen(f"{GREP_PATH} -h -f {pattern} {file1} {file2}")
        source_out = process.readlines()
        process.close()

        # Get separate file outputs
        process = os.popen(f"{GREP_PATH} -f {pattern} {file1}")
        file_out1 = process.readlines()
        process.close()
        process = os.popen(f"{GREP_PATH} -f {pattern} {file2}")
        file_out2 = process.readlines()
        process.close()

        # Verification
        combined_output = file_out1 + file_out2
        self.assertEqual(source_out, combined_output)


if __name__ == "__main__":
    unittest.main()
