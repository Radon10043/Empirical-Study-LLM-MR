from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test29(self, pattern: str, file: str):
        """Metamorphic Relation 29: If the pattern is changed to its atomic grouping form and the ignore-case option is used,
        the output should remain the same.
        """
        # Get source output with original pattern and ignore-case option
        process_orig = os.popen(f"{GREP_PATH} --ignore-case '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with the pattern in atomic grouping form
        follow_pattern = f"(?<={pattern})"

        # Get follow-up output with ignore-case option
        process_follow = os.popen(f"{GREP_PATH} --ignore-case '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
