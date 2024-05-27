import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test18(self, pattern: str, file: str):
        """Metamorphic Relation 18: If the search pattern is a subset of another pattern, the output should contain at least the same lines as the output of the larger pattern."""
        # Get source output with original pattern
        process = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        source_out = process.readlines()
        process.close()

        follow_pattern = os.path.join(os.path.dirname(pattern), "follow_pattern.txt")
        with open(follow_pattern, mode="w") as ff:
            with open(pattern, mode="r") as sf:
                ff.write(f"{sf.read()}.*") # Example larger pattern

        # Get source output with larger pattern
        process = os.popen(f"{GREP_PATH} -f {follow_pattern} {file}")
        follow_out = process.readlines()
        process.close()

        # Verification
        self.assertTrue(set(source_out).issubset(set(follow_out)))


if __name__ == "__main__":
    unittest.main()
