from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test9(self, pattern: str, file: str):
        """Metamorphic Relation 9: If a different context or surrounding lines are displayed, the output should be based on the new context or surrounding lines."""
        start_line, end_line = 0, 0
        f = open(file, mode="r", encoding="UTF-8")
        sum_line = len(f.readlines())
        f.close()
        start_line = randint(0, int(sum_line / 2))
        end_line = randint(int(sum_line / 2), sum_line)

        # Get source output with original context or surrounding lines
        process_orig = os.popen(f"{GREP_PATH} -A 2 -B 1 '{pattern}' {file} | sed -n '{start_line},{end_line}p'")
        source_out = process_orig.readlines()
        process_orig.close()

        # Adjust follow-up input with new context or surrounding lines
        new_context_start = start_line - 1
        new_context_end = end_line + 2
        # Get follow-up output with adjusted context or surrounding lines
        process_follow = os.popen(f"{GREP_PATH} -A 2 -B 1 '{pattern}' {file} | sed -n '{new_context_start},{new_context_end}p'")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
