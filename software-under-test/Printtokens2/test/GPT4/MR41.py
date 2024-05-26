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
    def test41(self, tc: str):
        """Metamorphic Relation 41: Adding new tokens enclosed in parentheses should increase the number of tokens accordingly."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Find a spot to insert new tokens enclosed in parentheses
        # Assuming 'insert_point' is a valid index where this can be done
        insert_point = tc.find(';') + 1
        new_tokens = '(new_token)'
        if insert_point > 0:
            follow_tc = f"{tc[:insert_point]} {new_tokens} {tc[insert_point:]}"
        else:
            follow_tc = f"{new_tokens} {tc}"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # Should be two additional tokens: the new identifier and the parentheses
        self.assertEqual(len(source_out) + 2, len(follow_out))


if __name__ == "__main__":
    unittest.main()
