from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test29(self, pattern: str, file: str):
        """Metamorphic Relation 29: If the '-A' option is used to specify the number of lines after the match, the output should contain the specified number of lines after the matching line."""
        num_lines = 2  # Example number of lines after the match
        # Get source output with the specified number of lines after the match
        process = os.popen(f"{GREP_PATH} -A {num_lines} {pattern} {file}")
        after_out = process.readlines()
        process.close()

        # Get expected output
        process = os.popen(f"grep -n {pattern} {file}")
        matched_lines = process.readlines()
        process.close()

        expected_output = []
        for line in matched_lines:
            line_number = int(line.split(':')[0])
            end_line = line_number + num_lines
            process = os.popen(f"sed -n '{line_number},{end_line}p' {file}")
            context = process.readlines()
            process.close()
            expected_output.extend(context)

        # Verification
        self.assertEqual(after_out, expected_output)


if __name__ == "__main__":
    unittest.main()
