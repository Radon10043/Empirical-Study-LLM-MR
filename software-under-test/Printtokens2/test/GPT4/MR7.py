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
    def test7(self, tc: str):
        """Metamorphic Relation 7: Swapping two adjacent tokens of the same type, the output's order changes but the content remains the same."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")
        source_out_set = set(source_out)

        # Construct follow-up input
        tokens = re.findall(r'\S+', tc)  # find all non-whitespace tokens
        for i in range(len(tokens) - 1):
            if tokens[i].isdigit() and tokens[i+1].isdigit():  # Example condition for same type (e.g., two numbers)
                # Swap the tokens
                tokens[i], tokens[i+1] = tokens[i+1], tokens[i]
                break

        follow_tc = ' '.join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")
        follow_out_set = set(follow_out)

        # Verification
        self.assertSetEqual(source_out_set, follow_out_set)


if __name__ == "__main__":
    unittest.main()
