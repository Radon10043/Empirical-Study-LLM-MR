from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test1(self, pattern: str, file: str):
        """Metamorphic Relation 1: If a character is added to the end of the search term,
        the length of the output length should be the same as or less than the original.
        """
        # Get source output
        process = os.popen(f"{GREP_PATH} {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Construct follow-up input
        follow_pattern = pattern + "a"

        # Get follow-up output
        process = os.popen(f"{GREP_PATH} {follow_pattern} {file}")
        follow_out = process.readlines()
        process.close()

        # Verification
        self.assertLessEqual(len(follow_out), len(source_out))


if __name__ == "__main__":
    unittest.main()
