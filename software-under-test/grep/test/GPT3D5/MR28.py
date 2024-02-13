from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test28(self, pattern: str, file: str):
        """Metamorphic Relation 28: If the '-B' option is used to specify the number of lines before the match, the output should contain the specified number of lines before the matching line."""
        num_lines = 2  # Example number of lines before the match
        # Get source output with the specified number of lines before the match
        process = os.popen(f"{GREP_PATH} -B {num_lines} {pattern} {file}")
        before_out = process.readlines()
        process.close()

        # Get expected output
        process = os.popen(f"grep -n {pattern} {file}")
        matched_lines = process.readlines()
        process.close()

        expected_output = []
        for line in matched_lines:
            line_number = int(line.split(':')[0])
            start_line = max(1, line_number - num_lines)
            end_line = line_number
            process = os.popen(f"sed -n '{start_line},{end_line}p' {file}")
            context = process.readlines()
            process.close()
            expected_output.extend(context)

        # Verification
        self.assertEqual(before_out, expected_output)


if __name__ == "__main__":
    unittest.main()
