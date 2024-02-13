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
    def test1(self, tc: str):
        """Metamorphic Relation 1: Changing all the characters from lower case to upper case, the keyword will disappear."""
        # Get source output
        source_out = subprocess.check_output(PRINT_TOKENS_PATH, input=tc, text=True).split("\n")

        # Construct follow-up input
        follow_tc = tc.upper()

        # Get follow-up output
        follow_out = subprocess.check_output(PRINT_TOKENS_PATH, input=follow_tc, text=True).split("\n")

        # Verification
        type_list = list()
        for line in follow_out:
            type_list.append(line.split(",")[0])
        self.assertNotIn("keyword", type_list)


if __name__ == "__main__":
    unittest.main()
