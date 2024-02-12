from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test3(self, pattern, file):
        """Metamorphic Relation 3: If regular expression matching is enabled, add an asterisk at
        the end of the search term, the output should be the same.
        """
        # Get source output
        process = os.popen(f'{GREP_PATH} --regexp="{pattern}" {file}')
        source_out = process.readlines()
        process.close()

        # Construct follow-up input
        follow_pattern = f"{pattern}*"

        # Get follow-up output
        process = os.popen(f'{GREP_PATH} --regexp="{follow_pattern}" {file}')
        follow_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
