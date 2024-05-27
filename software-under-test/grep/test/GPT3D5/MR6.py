import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test6(self, pattern: str, file: str):
        """Metamorphic Relation 6: If the fixed strings option is used, the output should be the same as the original output."""
        # Get source output
        process = os.popen(f"{GREP_PATH} -F -f {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Verification
        process = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        follow_out = process.readlines()
        process.close()
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
