from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test11(self, pattern: str, file: str):
        """Metamorphic Relation 11: If the 'files-with-matches' option is used, the output should only contain the names of files with selected lines."""
        # Get source output
        process = os.popen(f"{GREP_PATH} -l {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Verification
        for line in source_out:
            self.assertTrue(os.path.isfile(line.strip()))  # Ensure output contains only file names


if __name__ == "__main__":
    unittest.main()
