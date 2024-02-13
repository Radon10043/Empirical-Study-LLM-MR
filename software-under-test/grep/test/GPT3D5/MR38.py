from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test38(self, pattern: str, file: str):
        """Metamorphic Relation 38: If the fixed-strings option is used, the output should be consistent with the original output."""
        with open(pattern, "a") as f:
            f.write("\na")

        process_with_fixed_strings = os.popen(f"{GREP_PATH} -F -f {pattern} {file}")
        output_with_fixed_strings = process_with_fixed_strings.readlines()
        process_with_fixed_strings.close()

        process_without_fixed_strings = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        output_without_fixed_strings = process_without_fixed_strings.readlines()
        process_without_fixed_strings.close()

        # Verification
        self.assertEqual(output_with_fixed_strings, output_without_fixed_strings, "Output differs when using the fixed-strings option")


if __name__ == "__main__":
    unittest.main()
