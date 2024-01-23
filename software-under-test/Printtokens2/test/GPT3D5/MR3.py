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
    def test3(self, tc: str):
        """Metamorphic Relation 3: Adding duplicate tokens in the input, the output's token counts should be greater or equal to the source output's token counts."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input with added duplicate tokens
        follow_tc = tc + "\n" + tc

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        self.assertGreaterEqual(len(follow_out), len(source_out))


if __name__ == "__main__":
    unittest.main()
