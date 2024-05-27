import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test39(self, pattern: str, file: str):
        """Metamorphic Relation 39: If the sort option is used, the output should be sorted and consistent with the original output."""
        process_with_sort = os.popen(f"{GREP_PATH} -s -f {pattern} {file}")
        output_with_sort = process_with_sort.readlines()
        process_with_sort.close()

        process_without_sort = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        output_without_sort = process_without_sort.readlines()
        process_without_sort.close()

        # Verification
        self.assertEqual(sorted(output_with_sort), sorted(output_without_sort), "Output differs when using the sort option")


if __name__ == "__main__":
    unittest.main()
