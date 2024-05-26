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
    def test29(self, tc: str):
        """Metamorphic Relation 29: Adding a valid syntax structure (like a function declaration) should increase the number of tokens."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by adding a function declaration at the end
        function_declaration = "void newFunction() {}"
        follow_tc = f"{tc}\n{function_declaration}"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        # Assuming that the function declaration introduces a fixed number of new tokens
        # For the sake of simplicity, we assume it introduces 4 new tokens: return type, function name, parentheses, and body
        self.assertEqual(len(source_out) + 4, len(follow_out))


if __name__ == "__main__":
    unittest.main()
