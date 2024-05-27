import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test22(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 22: If the pattern includes the end-of-line character '$', adding
        any characters after the '$' should not increase the number of matches.
        """
        # Get source output with the original pattern
        process = os.popen(f"{GREP_PATH} -E -c -f {pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Modify pattern by adding characters after '$'
        follow_pattern = os.path.join(os.path.dirname(pattern), "follow_pattern.txt")
        tmp = str()
        with open(follow_pattern, mode="w") as f:
            with open(pattern, mode="r") as f1:
                tmp = f1.read().rstrip()
                f.write(tmp + "bar")

        # Get follow-up output with the modified pattern
        process = os.popen(f"{GREP_PATH} -E -c -f {follow_pattern} {file}")
        follow_matches = int(process.read().strip())
        process.close()

        # Verification
        if tmp.endswith("$"):
            self.assertGreaterEqual(source_matches, follow_matches)
        else:
            self.assertEqual(source_matches, follow_matches)


if __name__ == "__main__":
    unittest.main()
