from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build tcas.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases(1000))
    def test27(self, vals: list):
        """Metamorphic Relation 27: If the Own_Tracked_Alt_Rate and Other_Tracked_Alt parameters are unchanged, and the state indicating the presence of valid altitude reports changes, the output should not change."""
        # Get source output
        source_out = run_TCAS(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Two_of_Three_Reports_Valid"]] = not follow_vals[INDEX["Two_of_Three_Reports_Valid"]]  # Changing the state indicating the presence of valid altitude reports

        # Get follow-up output
        follow_out = run_TCAS(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
