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
    def test9(self, tc: str):
        """Metamorphic Relation 9: Applying a rotating transformation to the input, the token categories should maintain the same relative order."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Apply rotating transformation to the input
        tokens = tc.strip().split('\n')
        rotated_tokens = tokens[-1:] + tokens[:-1]
        follow_tc = '\n'.join(rotated_tokens)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        for i, line in enumerate(source_out):
            self.assertEqual(line.split()[1], follow_out[i].split()[1])


if __name__ == "__main__":
    unittest.main()
