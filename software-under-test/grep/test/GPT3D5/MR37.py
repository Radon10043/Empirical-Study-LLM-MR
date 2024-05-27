import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test37(self, pattern: str, file: str):
        """Metamorphic Relation 37: If the extended-regexp option is used, the output should be consistent with the original output."""
        process_with_ere = os.popen(f"{GREP_PATH} -E -f {pattern} {file}")
        output_with_ere = process_with_ere.readlines()
        process_with_ere.close()

        process_without_ere = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        output_without_ere = process_without_ere.readlines()
        process_without_ere.close()

        # Verification
        self.assertEqual(output_with_ere, output_without_ere, "Output differs when using the extended-regexp option")


if __name__ == "__main__":
    unittest.main()
