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
    def test23(self, tc: str):
        """Metamorphic Relation 23: Replacing each instance of a token with its base form (lemma), the output should remain the same."""
        import spacy

        # load pre-trained English NLP model
        nlp = spacy.load("en_core_web_sm")

        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Tokenize the input using spaCy
        source_tokens = [token.text for token in nlp(tc)]

        # Replace each token with its base form (lemma) using spaCy
        follow_tokens = [token.lemma_ if token.lemma_ != "-PRON-" else token.text for token in nlp(tc)]
        follow_tc = " ".join(follow_tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
