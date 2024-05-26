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
    def test13(self, tc: str):  # Fixed
        """Metamorphic Relation 13: Shuffling the order of only the keyword tokens should not affect the appearance count of each keyword in the output."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True)

        # Extract keyword tokens based on predefined rules (assuming a list of known keywords)
        keywords = ["lambda", "and", "or", "if", "xor"]  # example keyword list
        keyword_pattern = r'\b(' + '|'.join(keywords) + r')\b'
        keyword_matches = re.findall(keyword_pattern, source_out)

        # Shuffle keywords in the source output
        random.shuffle(keyword_matches)
        follow_tc = re.sub(keyword_pattern, lambda _: keyword_matches.pop(), tc)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True)

        # Verification - comparing keyword counts
        source_keyword_counts = {kw: source_out.count(kw) for kw in keywords}
        follow_keyword_counts = {kw: follow_out.count(kw) for kw in keywords}
        self.assertEqual(source_keyword_counts, follow_keyword_counts)


if __name__ == "__main__":
    unittest.main()
