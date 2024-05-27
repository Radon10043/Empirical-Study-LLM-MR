import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test5(self, pattern: str, file: str):
        """Metamorphic Relation 5: If the pattern is extended in length, the output should be a subset of the original output."""
        # Get source output
        process = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Construct follow-up input
        follow_pattern = os.path.join(os.path.dirname(pattern), "follow_pattern.txt")
        with open(follow_pattern, mode="w") as ff:
            with open(pattern) as sf:
                ff.write(sf.read() + "extended")

        # Get follow-up output
        process = os.popen(f"{GREP_PATH} -f {follow_pattern} {file}")
        follow_out = process.readlines()
        process.close()

        # Verification
        self.assertTrue(set(follow_out).issubset(set(source_out)))


if __name__ == "__main__":
    unittest.main()
