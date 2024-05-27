import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test7(self, pattern: str, file: str):   # Fixed
        """Metamorphic Relation 7: Searching with and without the ignore-case option should yield the
        same number of matches if the file and search pattern contain only one case (either all upper
        case or all lower case).
        """
        # Convert search pattern to upper case
        uppercase_pattern = os.path.join(os.path.dirname(pattern), "uppercase_pattern.txt")
        tmp = str()
        with open(pattern) as f:
            tmp = f.read().upper()
        with open(uppercase_pattern, mode="w") as f:
            f.write(tmp)

        # Get source output
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Get follow-up output with ignore-case
        process = os.popen(f"{GREP_PATH} -i -c -f {uppercase_pattern} {file}")
        ignore_case_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(source_matches, ignore_case_matches)


if __name__ == "__main__":
    unittest.main()
