from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build print_tokens.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    # TODO
    @parameterized.expand(load_test_cases)
    def test8(self, tc: str):
        """Metamorphic Relation 8: Concatenating two input sequences, the output should be the concatenation of source and follow-up outputs."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Initialize a new set of test cases and get the source and follow-up outputs separately
        follow_tc = random.choice(load_test_cases())
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Construct combined input and combined output
        combined_tc = tc + follow_tc
        combined_out = source_out + follow_out

        # Get combined output using subprocess
        combined_sub_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=combined_tc, text=True).split("\n")

        # Verification
        self.assertEqual(combined_out, combined_sub_out)


if __name__ == "__main__":
    unittest.main()
