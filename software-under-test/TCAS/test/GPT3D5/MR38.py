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
    def test38(self, vals: list):
        """Metamorphic Relation 38: If the Other_Tracked_Alt is greater than Own_Tracked_Alt, then changing the value of High_Confidence should lead to the same output as changing the value of Two_of_Three_Reports_Valid."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Other_Tracked_Alt"]] > vals[INDEX["Own_Tracked_Alt"]]:
            # Construct follow-up input 1: Changing High_Confidence
            follow_confidence_vals = vals.copy()
            follow_confidence_vals[INDEX["High_Confidence"]] = 1 - follow_confidence_vals[INDEX["High_Confidence"]]
            follow_confidence_out = run_tcas(follow_confidence_vals)

            # Construct follow-up input 2: Changing Two_of_Three_Reports_Valid
            follow_report_vals = vals.copy()
            follow_report_vals[INDEX["Two_of_Three_Reports_Valid"]] = 1 - follow_report_vals[INDEX["Two_of_Three_Reports_Valid"]]
            follow_report_out = run_tcas(follow_report_vals)

            # Verification
            self.assertEqual(follow_confidence_out, follow_report_out)


if __name__ == "__main__":
    unittest.main()
