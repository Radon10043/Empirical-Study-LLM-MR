from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test33(self, pattern: str, file: str):
        """Metamorphic Relation 33: If the user specifies a file type and then uses the recursive option, the output should be the same as when applying the file type filter in a single search."""
        file_type = "*.txt"  # Example file type
        # Get source output with file type filter in a single search
        process = os.popen(f"{GREP_PATH} --include={file_type} -f {pattern} {file}")
        single_search_out = process.readlines()
        process.close()

        # Get source output with file type specified and then using the recursive option
        process = os.popen(f"{GREP_PATH} -r -h --include={file_type} -f {pattern} {os.path.dirname(file)}")
        recursive_search_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(single_search_out, recursive_search_out, "Output differs when using file type filter in a single search versus using it with the recursive option")


if __name__ == "__main__":
    unittest.main()
