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
    def test31(self, tc: str):
        """Metamorphic Relation 31: Repeating the input multiple times, the output should be the concatenation of source outputs."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input by repeating the source input
        repeat_factor = 3
        follow_tc = "\n".join([tc]*repeat_factor)

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS2_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        combined_source_out = source_out * repeat_factor
        self.assertEqual(combined_source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
