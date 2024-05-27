import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test35(self, pattern: str, file: str):
        """Metamorphic Relation 35: If inverted match is performed on an empty pattern, the entire file should be output."""
        process_inverted_match = os.popen(f"{GREP_PATH} -v '' {file}")
        output_inverted_match = process_inverted_match.readlines()
        process_inverted_match.close()

        process_entire_file = os.popen(f"cat {file}")
        output_entire_file = process_entire_file.readlines()
        process_entire_file.close()

        # Verification
        self.assertEqual(output_inverted_match, output_entire_file, "Inverted match with empty pattern does not output the entire file")


if __name__ == "__main__":
    unittest.main()
