import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test41(self, pattern: str, file: str):
        """Metamorphic Relation 41: If the --file option is used, the output should be consistent with the original output."""
        process_with_file_option = os.popen(f"{GREP_PATH} --file={pattern} {file}")
        output_with_file_option = process_with_file_option.readlines()
        process_with_file_option.close()

        process_without_file_option = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        output_without_file_option = process_without_file_option.readlines()
        process_without_file_option.close()

        # Verification
        self.assertEqual(output_with_file_option, output_without_file_option, "Output differs when using the --file option")


if __name__ == "__main__":
    unittest.main()
