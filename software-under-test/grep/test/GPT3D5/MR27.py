from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test27(self, pattern: str, file: str):
        """Metamorphic Relation 27: If the "ignore case" option is used twice, the output should be the same as when using the "ignore case" option once."""
        process_single_ignore = os.popen(f"{GREP_PATH} -i -f {pattern} {file}")
        single_ignore_output = process_single_ignore.readlines()
        process_single_ignore.close()

        process_double_ignore = os.popen(f"{GREP_PATH} -i -i -f {pattern} {file}")
        double_ignore_output = process_double_ignore.readlines()
        process_double_ignore.close()

        # Verification
        self.assertEqual(single_ignore_output, double_ignore_output, "Output differs when using the ignore case option once versus twice")


if __name__ == "__main__":
    unittest.main()
