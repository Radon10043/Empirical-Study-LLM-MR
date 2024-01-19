from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test8(self, pattern: str, file: str):
        """Metamorphic Relation 8: If a different line number range is used, the output should be based on the new line number range."""
        start_line, end_line = 0, 0
        f = open(file, mode="r", encoding="UTF-8")
        sum_line = len(f.readlines())
        f.close()
        start_line = randint(0, int(sum_line / 2))
        end_line = randint(int(sum_line / 2), sum_line)

        # Get source output with original line number range
        process_orig = os.popen(f"{GREP_PATH} -n '{pattern}' {file} | sed -n '{start_line},{end_line}p'")
        source_out = process_orig.readlines()
        process_orig.close()

        # Adjust follow-up input with new line number range
        new_start_line = start_line + 1
        new_end_line = end_line + 1
        # Get follow-up output with adjusted line number range
        process_follow = os.popen(f"{GREP_PATH} -n '{pattern}' {file} | sed -n '{new_start_line},{new_end_line}p'")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
