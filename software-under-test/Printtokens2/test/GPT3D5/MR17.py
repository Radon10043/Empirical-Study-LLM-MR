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
    def test17(self, tc: str):
        """Metamorphic Relation 17: Adding newlines between every character of the input, the token counts should be greater than the original input."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by adding newlines between every character
        follow_tc = "\n".join(" ".join(list(line)) for line in tc.split("\n"))

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertGreater(len(follow_out), len(source_out))


if __name__ == "__main__":
    unittest.main()
