import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test40(self, pattern: str, file: str):
        """Metamorphic Relation 40: If the --regexp option is used, the output should be consistent with the original output."""
        with open(pattern, "r") as f:
            content = f.read()
        process_with_regexp = os.popen(f"{GREP_PATH} --regexp={content} {file}")
        output_with_regexp = process_with_regexp.readlines()
        process_with_regexp.close()

        process_without_regexp = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        output_without_regexp = process_without_regexp.readlines()
        process_without_regexp.close()

        # Verification
        self.assertEqual(output_with_regexp, output_without_regexp, "Output differs when using the --regexp option")


if __name__ == "__main__":
    unittest.main()
