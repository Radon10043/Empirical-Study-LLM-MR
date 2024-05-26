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
    def test26(self, tc: str):
        """Metamorphic Relation 26: Adding white spaces inside string literals should change the literal output but not the number of tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by adding spaces into string literals
        follow_tc = re.sub(r'(".*?")', lambda m: m.group(1).replace("", " ").strip(), tc)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - number of tokens should remain same, but string literal tokens should be altered
        self.assertEqual(len(source_out), len(follow_out))
        altered_string_literals = [out for out in follow_out if " " in out and '"' in out]
        self.assertTrue(len(altered_string_literals) > 0)


if __name__ == "__main__":
    unittest.main()
