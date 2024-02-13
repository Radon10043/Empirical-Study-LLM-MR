from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test43(self, pattern: str, file: str):
        """Metamorphic Relation 43: If the --quiet option is used, the program should produce no output."""
        process_with_quiet = os.popen(f"{GREP_PATH} --quiet {pattern} {file}")
        output_with_quiet = process_with_quiet.readlines()
        process_with_quiet.close()

        # Verification
        self.assertFalse(output_with_quiet, "Unexpected output when using the --quiet option")


if __name__ == "__main__":
    unittest.main()
