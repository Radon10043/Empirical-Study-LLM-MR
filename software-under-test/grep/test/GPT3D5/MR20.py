from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test20(self, pattern: str, file: str):
        """Metamorphic Relation 20: If the recursive search option is used, and the search pattern is applied separately in each subdirectory, the output should be the same as when performing a single recursive search."""
        # Get source output with recursive search
        process = os.popen(f"{GREP_PATH} -h -r -f {pattern} {os.path.dirname(file)}")
        recursive_out = process.readlines()
        process.close()

        # Get separate file outputs
        combined_out = []
        for root, dirs, files in os.walk(os.path.dirname(file)):
            for f in files:
                process = os.popen(f"{GREP_PATH} -f {pattern} {os.path.join(root, f)}")
                file_out = process.readlines()
                process.close()
                combined_out.extend(file_out)

        # Verification
        self.assertEqual(recursive_out, combined_out)


if __name__ == "__main__":
    unittest.main()
