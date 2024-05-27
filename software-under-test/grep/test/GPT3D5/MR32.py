import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test32(self, pattern: str, file: str):
        """Metamorphic Relation 32: If the '-v' option is used to select non-matching lines, the output should not contain any line that matches the pattern."""
        process_with_v_option = os.popen(f"{GREP_PATH} -v -f {pattern} {file}")
        output_with_v_option = process_with_v_option.readlines()
        process_with_v_option.close()

        process_without_v_option = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        output_without_v_option = process_without_v_option.readlines()
        process_without_v_option.close()

        # Verification
        for line in output_with_v_option:
            self.assertNotIn(pattern, line, "Output with -v option contains matching lines")
        self.assertNotEqual(output_with_v_option, output_without_v_option, "Output differs when using the -v option")


if __name__ == "__main__":
    unittest.main()
