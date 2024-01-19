from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases)
    def test41(self, pattern: str, file: str):
        """Metamorphic Relation 41: If the file path is changed to an absolute path, the output should remain the same."""
        absolute_path = os.path.abspath(file)

        # Get source output with original file path
        process_orig = os.popen(f"{GREP_PATH} '{pattern}' {file}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Get follow-up output with absolute file path
        process_follow = os.popen(f"{GREP_PATH} '{pattern}' {absolute_path}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
