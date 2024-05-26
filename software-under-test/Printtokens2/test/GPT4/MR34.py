import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build print_tokens.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases(1000))
    def test34(self, tc: str):
        """Metamorphic Relation 34: Concatenation of two strings should reduce the output token count by one."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by concatenating the first two string literals found
        string_literals = re.findall(r'"[^"]*"', tc)
        if len(string_literals) > 1:
            concatenated_string = string_literals[0].strip('"') + string_literals[1].strip('"')
            follow_tc = tc.replace(string_literals[0], "").replace(string_literals[1], f'"{concatenated_string}"', 1)

            # Get follow-up output
            follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

            # Verification
            self.assertEqual(len(source_out) - 1, len(follow_out))
        else:
            self.skipTest("Insufficient number of string literals to perform concatenation.")


if __name__ == "__main__":
    unittest.main()
