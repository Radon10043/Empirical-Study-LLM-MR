from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test36(self, pattern: str, file: str):
        """Metamorphic Relation 36: If a different regular expression engine is used, the output should be consistent with the original regular expression engine."""
        other_grep_path = "/usr/bin/grep"  # Example path to a different grep utility

        # Get source output with original regular expression engine
        process = os.popen(f"{GREP_PATH} {pattern} {file}")
        source_out = process.readlines()
        process.close()

        # Get source output with different regular expression engine
        process = os.popen(f"{other_grep_path} {pattern} {file}")
        other_out = process.readlines()
        process.close()

        # Verification
        self.assertEqual(source_out, other_out, "Output differs when using a different regular expression engine")


if __name__ == "__main__":
    unittest.main()
