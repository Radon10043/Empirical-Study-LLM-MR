from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test20(self, pattern: str, file: str):
        """Metamorphic Relation 20: If the pattern is changed to its atomic grouping form, the output should remain the same."""
        # Get source output
        process_orig = os.popen(f"{GREP_PATH} '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Construct follow-up input with the pattern in atomic grouping form
        follow_pattern = f"(?>{pattern})"

        # Get follow-up output
        process_follow = os.popen(f"{GREP_PATH} '{follow_pattern}' {file}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
