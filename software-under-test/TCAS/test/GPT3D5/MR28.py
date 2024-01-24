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
    def test28(self, vals: list):
        """Metamorphic Relation 28: If Own_Tracked_Alt is less than Other_Tracked_Alt and the TCAS system of the other aircraft is active, then changing the value of Other_RAC should lead to the same output as changing the value of Two_of_Three_Reports_Valid by the same amount."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Own_Tracked_Alt"]] < vals[INDEX["Other_Tracked_Alt"]] and vals[INDEX["Other_Capability"]] == 1:
            # Construct follow-up input: Change Other_RAC
            follow_other_rac_vals = vals.copy()
            follow_other_rac_vals[INDEX["Other_RAC"]] = 1 - follow_other_rac_vals[INDEX["Other_RAC"]]
            follow_other_rac_out = run_tcas(follow_other_rac_vals)

            # Construct follow-up input: Change Two_of_Three_Reports_Valid
            follow_two_of_three_vals = vals.copy()
            follow_two_of_three_vals[INDEX["Two_of_Three_Reports_Valid"]] = 1 - follow_two_of_three_vals[INDEX["Two_of_Three_Reports_Valid"]]
            follow_two_of_three_out = run_tcas(follow_two_of_three_vals)

            # Verification
            self.assertEqual(follow_other_rac_out, follow_two_of_three_out)


if __name__ == "__main__":
    unittest.main()
