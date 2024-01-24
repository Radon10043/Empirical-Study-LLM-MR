from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build tcas.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases)
    def test42(self, vals: list):
        """Metamorphic Relation 42: If the value of Cur_Vertical_Sep is greater than 300, and the Own_Tracked_Alt_Rate is negative, changing the value of Two_of_Three_Reports_Valid should lead to the same output as changing the value of Other_Tracked_Alt_Rate by the same amount."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Cur_Vertical_Sep"]] > 300 and vals[INDEX["Own_Tracked_Alt_Rate"]] < 0:
            # Construct follow-up input 1: Changing Two_of_Three_Reports_Valid
            follow_report_vals = vals.copy()
            follow_report_vals[INDEX["Two_of_Three_Reports_Valid"]] = 1 - follow_report_vals[INDEX["Two_of_Three_Reports_Valid"]]
            follow_report_out = run_tcas(follow_report_vals)

            # Construct follow-up input 2: Changing Other_Tracked_Alt_Rate
            follow_alt_rate_vals = vals.copy()
            follow_alt_rate_vals[INDEX["Other_Tracked_Alt_Rate"]] *= -1
            follow_alt_rate_out = run_tcas(follow_alt_rate_vals)

            # Verification
            self.assertEqual(follow_report_out, follow_alt_rate_out)


if __name__ == "__main__":
    unittest.main()
