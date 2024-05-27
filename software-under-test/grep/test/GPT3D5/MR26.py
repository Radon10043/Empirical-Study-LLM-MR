import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test26(self, pattern: str, file: str):
        """Metamorphic Relation 26: If the "-q" option is used, the program should produce no output."""
        process = os.popen(f"{GREP_PATH} -q {pattern} {file}")
        output = process.readlines()
        process.close()

        # Verification
        self.assertFalse(output, "Unexpected output when using the -q option")


if __name__ == "__main__":
    unittest.main()
