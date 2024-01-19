from utils import *


class TestingClass(unittest.TestCase):
    # Fix by Radon
    @parameterized.expand(load_test_cases)
    def test30(self, pattern: str, file: str):
        """Metamorphic Relation 30: If the pattern is enclosed in quotes and the context option is used,
        the output should remain the same.
        """
        before_lines, after_lines = 0, 0
        f = open(file, mode="r", encoding="UTF-8")
        sum_line = len(f.readlines())
        f.close()
        before_lines = randint(0, int(sum_line / 2))
        after_lines = randint(int(sum_line / 2), sum_line)

        # Get source output with original pattern and context lines configuration
        process_orig = os.popen(f"{GREP_PATH} -B {before_lines} -A {after_lines} '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Get follow-up output with quoted pattern and context lines
        process_follow = os.popen(f"{GREP_PATH} -B {before_lines} -A {after_lines} '{pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
