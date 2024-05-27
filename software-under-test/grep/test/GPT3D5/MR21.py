import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test21(self, pattern: str, file: str):
        """Metamorphic Relation 21: If the context option is used, the output should contain the matched lines along with specified context around them."""
        context_lines = 2  # Number of lines of context
        # Get source output with context option
        process = os.popen(f"{GREP_PATH} -C {context_lines} -f {pattern} {file}")
        context_out = process.readlines()
        process.close()

        # Get separate file outputs to construct expected output with context
        process = os.popen(f"grep -n -f {pattern} {file}")
        matched_lines = process.readlines()
        process.close()

        expected_output = []
        for line in matched_lines:
            line_number = int(line.split(':')[0])
            start_line = max(1, line_number - context_lines)
            end_line = line_number + context_lines + 1
            process = os.popen(f"sed -n '{start_line},{end_line}p' {file}")
            context = process.readlines()
            process.close()
            expected_output.extend(context)

        # Verification
        self.assertEqual(context_out, expected_output)


if __name__ == "__main__":
    unittest.main()
