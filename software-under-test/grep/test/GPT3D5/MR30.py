import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test30(self, pattern: str, file: str):
        """Metamorphic Relation 30: If the '-y' option (or --any-dot) is used, the output should match any character including the newline."""
        process_with_y_option = os.popen(f"{GREP_PATH} -y . {file}")
        output_with_y_option = process_with_y_option.readlines()
        process_with_y_option.close()

        process_without_y_option = os.popen(f"{GREP_PATH} . {file}")
        output_without_y_option = process_without_y_option.readlines()
        process_without_y_option.close()

        # Verification
        self.assertEqual(output_with_y_option, output_without_y_option, "Output differs when using the -y option and not using the -y option")


if __name__ == "__main__":
    unittest.main()
