import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test1(self, pattern: str, file: str):
        """Metamorphic Relation 1: If a character is added to the end of the search term,
        the length of the output length should be the same as or less than the original.
        """
        # Get source output
        process = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Construct follow-up input
        follow_pattern = os.path.join(os.path.dirname(pattern), "follow_pattern.txt")
        with open(follow_pattern, mode="w") as ff:
            with open(pattern) as sf:
                ff.write(sf.read() + "a")

        # Get follow-up output
        process = os.popen(f"{GREP_PATH} -f {follow_pattern} {file}")
        follow_out = process.readlines()
        process.close()

        # Verification
        self.assertLessEqual(len(follow_out), len(source_out))


if __name__ == "__main__":
    unittest.main()
