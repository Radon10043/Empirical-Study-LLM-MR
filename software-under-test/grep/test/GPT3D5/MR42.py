from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test42(self, pattern: str, file: str):
        """Metamorphic Relation 42: If the --only-matching option is used, the output should contain only the matching parts of a line, not the entire matched line."""
        process_with_only_matching = os.popen(f"{GREP_PATH} --only-matching -f {pattern} {file}")
        output_with_only_matching = process_with_only_matching.readlines()
        process_with_only_matching.close()

        process_without_only_matching = os.popen(f"{GREP_PATH} -f {pattern} {file}")
        output_without_only_matching = process_without_only_matching.readlines()
        process_without_only_matching.close()

        # Verification
        for line in output_with_only_matching:
            self.assertTrue(pattern in line, "Output with --only-matching option contains unmatched parts of a line")
        self.assertNotEqual(output_with_only_matching, output_without_only_matching, "Output differs when using the --only-matching option")


if __name__ == "__main__":
    unittest.main()
