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
    def test20(self, tc: str):
        """Metamorphic Relation 20: Inserting a character in a token that makes it an illegal token should cause an error."""
        # Get source output
        try:
            source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")
            source_contains_error = False
        except subprocess.CalledProcessError:
            source_contains_error = True

        # Construct follow-up input by inserting an illegal character into a valid token
        follow_tc = re.sub(r'\b(\w+)\b', r'\1$', tc, count=1)

        # Verify if follow-up input causes an error
        try:
            follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")
            follow_contains_error = False
        except subprocess.CalledProcessError:
            follow_contains_error = True

        # Verification
        # If the source output did not contain an error, the follow-up output should
        if not source_contains_error:
            self.assertTrue(follow_contains_error)


if __name__ == "__main__":
    unittest.main()
