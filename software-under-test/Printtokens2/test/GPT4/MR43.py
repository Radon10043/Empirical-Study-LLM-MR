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
    def test43(self, tc: str):
        """Metamorphic Relation 43: Duplicate a code block should double the number of output tokens, while preserving code syntax."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Assuming the code block is surrounded by curly braces '{ }'
        code_blocks = re.findall(r"{[^}]*}", tc)
        if code_blocks:
            block_to_duplicate = code_blocks[0]
            follow_tc = tc.replace(block_to_duplicate, block_to_duplicate + block_to_duplicate)

            # Get follow-up output
            follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

            # Verification
            # The number of output tokens should exactly double the count of the duplicated block
            block_token_count = block_to_duplicate.count("\n") + 1
            self.assertEqual(len(source_out) + block_token_count, len(follow_out))
        else:
            self.skipTest("No code blocks found to duplicate.")


if __name__ == "__main__":
    unittest.main()
