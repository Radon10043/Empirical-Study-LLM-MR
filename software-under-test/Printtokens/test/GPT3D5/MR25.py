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
    def test25(self, tc: str):
        """Metamorphic Relation 25: Using a synonym of the program input as the follow-up input should yield the same output as the original input."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Replace certain tokens with synonyms
        tokens = tc.split()
        synonyms = {'function': 'operation', 'process': 'procedure', 'input': 'data'}
        for i, token in enumerate(tokens):
            if token.lower() in synonyms:
                tokens[i] = synonyms[token.lower()]
        follow_tc = " ".join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verify that the output remains the same
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
