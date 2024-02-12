from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test2(self, pattern: str, file: str):
        """Metamorphic Relation 2: If case distinctions are ignored, swap the case of search term,
        the output should be the same.
        """
        # Get source output
        process = os.popen(f"{GREP_PATH} --ignore-case {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Construct follow-up input
        follow_pattern = pattern.swapcase()

        # Get follow-up output
        process = os.popen(f"{GREP_PATH} --ignore-case {follow_pattern} {file}")
        follow_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
