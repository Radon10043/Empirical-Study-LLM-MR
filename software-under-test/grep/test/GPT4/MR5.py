import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test5(self, pattern: str, file1: str, file2: str):  # Fixed
        """Metamorphic Relation 5: If the files-with-matches option is used, the files listed
        should be a subset of the files in which the pattern can be found without using the option.
        """
        files = [file1, file2]

        # Get source output
        process = os.popen(f"{GREP_PATH} {pattern} " + " ".join(files))
        source_out = set(process.readlines())
        process.close()

        # Get follow-up output with files-with-matches
        process = os.popen(f"{GREP_PATH} -l {pattern} " + " ".join(files))
        follow_out = set(process.readlines())
        process.close()

        # Verification
        self.assertTrue(follow_out.issubset(source_out))


if __name__ == "__main__":
    unittest.main()
