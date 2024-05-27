import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @parameterized.expand(load_test_cases(1000))
    def test6(self, pattern: str, file: str):   # Fixed
        """Metamorphic Relation 6: Searching with the pattern as a fixed string should yield the same
        or fewer matches than searching with the pattern as a basic regular expression when the pattern
        does not contain any regular expression metacharacters.
        """
        with open(pattern, mode="a") as f:
            f.write(gen_str_randomly(randint(1, 5)))

        # Get source output with fixed strings
        process = os.popen(f"{GREP_PATH} -F -c -f {pattern} {file}")
        fixed_string_matches = int(process.read().strip())
        process.close()

        # Get follow-up output with basic regex
        process = os.popen(f"{GREP_PATH} -c -f {pattern} {file}")
        regex_matches = int(process.read().strip())
        process.close()

        # Verification
        self.assertGreaterEqual(regex_matches, fixed_string_matches)


if __name__ == "__main__":
    unittest.main()
