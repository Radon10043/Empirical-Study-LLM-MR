from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases_combinations)
    def test28(self, pattern: str, file1: str, file2: str):
        """Metamorphic Relation 28: If the order of the input files is reversed and the pattern is enclosed in quotes,
        the output should remain unchanged.
        """
        # Get source output with original input file order and quoted pattern
        process_orig = os.popen(f"{GREP_PATH} '{pattern}' {file1} {file2}")
        source_out = process_orig.readlines()
        process_orig.close()

        # Get follow-up output with reversed input file order and quoted pattern
        process_follow = os.popen(f"{GREP_PATH} '{pattern}' {file2} {file1}")
        follow_out = process_follow.readlines()
        process_follow.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
