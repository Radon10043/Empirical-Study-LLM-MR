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
    def test4(self, tc: str):   # Fixed
        """Metamorphic Relation 4: Doubling a token, the output's rows equals the source output's rows plus one."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by doubling the first non-whitespace token
        follow_tc = tc
        for val in source_out:
            if not "," in val:
                continue
            token = val.split(",")[1].rstrip(".")
            if val.split(",")[0] != "string":
                token = token.lstrip("\"").rstrip("\"")
            follow_tc += token + "\n"
            break

        if follow_tc == tc:
            self.skipTest("No token to double")

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(len(source_out) + 1, len(follow_out))


if __name__ == "__main__":
    unittest.main()
