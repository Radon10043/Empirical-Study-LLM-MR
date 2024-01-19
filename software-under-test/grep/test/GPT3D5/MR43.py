from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test43(self, pattern: str, file: str):
        """Metamorphic Relation 43: If the pattern is changed to its lookbehind assertion form and the '-v' option is used,
        the output should remain the same.
        """
        # Get source output with original pattern and '-v' option
        process_orig = os.popen(f"{GREP_PATH} -v '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with the pattern in lookbehind assertion form
        follow_pattern = f"(?<={pattern})"

        # Get follow-up output with '-v' option
        process_follow = os.popen(f"{GREP_PATH} -v '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
