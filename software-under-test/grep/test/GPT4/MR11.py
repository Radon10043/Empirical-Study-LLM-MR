import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test11(self, pattern: str, file: str):  # Fixed
        """Metamorphic Relation 11: Doubling the pattern using an OR operator in extended mode
        should not change the number of matches.
        """
        # Get source output with the original pattern in extended mode
        process = os.popen(f"{GREP_PATH} -E -c -f {pattern} {file}")
        source_matches = int(process.read().strip())
        process.close()

        # Double the pattern using an OR operator
        follow_pattern = os.path.join(os.path.dirname(pattern), "follow_pattern.txt")
        tmp = str()
        with open(pattern) as f:
            tmp = f.read().rstrip()
        with open(follow_pattern, mode="w") as f:
            f.write(tmp + "|" + tmp)

        # Get follow-up output with the doubled pattern in extended mode
        process = os.popen(f"{GREP_PATH} -E -c -f {follow_pattern} {file}")
        follow_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertEqual(source_matches, follow_matches)


if __name__ == "__main__":
    unittest.main()
