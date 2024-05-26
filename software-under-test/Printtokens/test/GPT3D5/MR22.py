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
    def test22(self, tc: str):
        """Metamorphic Relation 22: Replacing each instance of a token with synonyms, the count of occurrences should remain the same in the output."""
        from collections import Counter

        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        tokens = tc.split()
        # Replace some tokens with synonyms
        synonym_replacements = {
            'big': ['large', 'huge'],
            'small': ['tiny', 'little'],
            'old': ['aged', 'ancient'],
            'new': ['fresh', 'modern']
        }
        counter = Counter(tokens)
        for i, token in enumerate(tokens):
            if token in synonym_replacements:
                replacement = random.choice(synonym_replacements[token])
                tokens[i] = replacement
                counter[replacement] += 1
                counter[token] -= 1
        follow_tc = " ".join(tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verify the count of occurrences for each token remains the same
        follow_counter = Counter(follow_out)
        self.assertEqual(counter, follow_counter)


if __name__ == "__main__":
    unittest.main()
