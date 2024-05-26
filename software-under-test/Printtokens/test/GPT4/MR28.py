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
    def test28(self, tc: str):
        """Metamorphic Relation 28: Duplicating code blocks with distinct variable names should introduce new tokens but not alter the existing ones."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # For this test, we assume that code blocks can be duplicated as long as variable names are changed
        # Duplicate the first block of code and change the variable names
        first_block_end_index = tc.find('}')
        if first_block_end_index != -1:
            first_block = tc[:first_block_end_index+1]
            duplicated_block = re.sub(r'\b(\w+)\b', r'\1_2', first_block)  # Add suffix to variables
            follow_tc = tc + duplicated_block
        else:
            follow_tc = tc

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification - Verify that new tokens are introduced for the duplicated block, but existing tokens are not altered
        existing_token_set = set(source_out)
        additional_token_set = set(follow_out) - existing_token_set
        self.assertTrue(all(token.endswith('_2') for token in additional_token_set))


if __name__ == "__main__":
    unittest.main()
