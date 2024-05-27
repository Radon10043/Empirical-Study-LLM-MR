import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test10(self, pattern: str, file: str):
        """Metamorphic Relation 10: If recursive search is performed, the output should be the combined output of all files in the directory tree."""
        # Get source output
        process = os.popen(f"{GREP_PATH} -h -r -f {pattern} {os.path.dirname(file)}")
        source_out = process.readlines()
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
        self.assertEqual(source_out, combined_out)


if __name__ == "__main__":
    unittest.main()
