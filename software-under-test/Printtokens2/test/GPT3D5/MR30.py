from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build print_tokens.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases)
    def test30(self, tc: str):
        """Metamorphic Relation 30: Replacing specific tokens with their synonyms, the token counts in the output should remain the same."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Replace specific tokens with their synonyms in the input
        synonym_mapping = {"int": "integer", "float": "decimal", "string": "text"}
        replaced_tc = ""
        for line in tc.split("\n"):
            tokens = line.split()
            replaced_tokens = [synonym_mapping.get(token, token) for token in tokens]
            replaced_line = " ".join(replaced_tokens)
            replaced_tc += replaced_line + "\n"

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=replaced_tc, text=True).split("\n")

        # Verification
        self.assertEqual(len(source_out), len(follow_out))


if __name__ == "__main__":
    unittest.main()
