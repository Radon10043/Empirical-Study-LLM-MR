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
    def test27(self, vals: list):
        """Metamorphic Relation 27: If the TCAS system of the other aircraft is active and the RAC is DO_NOT_DESCEND with high confidence, then changing the value of Two_of_Three_Reports_Valid should lead to the same output as changing the value of Climb_Inhibit by the same amount."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Other_Capability"]] == 1 and vals[INDEX["Other_RAC"]] == 2 and vals[INDEX["High_Confidence"]] == 1:
            # Construct follow-up input: Change Two_of_Three_Reports_Valid
            follow_two_of_three_vals = vals.copy()
            follow_two_of_three_vals[INDEX["Two_of_Three_Reports_Valid"]] = 1 - follow_two_of_three_vals[INDEX["Two_of_Three_Reports_Valid"]]
            follow_two_of_three_out = run_tcas(follow_two_of_three_vals)

            # Construct follow-up input: Change Climb_Inhibit
            follow_climb_inhibit_vals = vals.copy()
            follow_climb_inhibit_vals[INDEX["Climb_Inhibit"]] = 1 - follow_climb_inhibit_vals[INDEX["Climb_Inhibit"]]
            follow_climb_inhibit_out = run_tcas(follow_climb_inhibit_vals)

            # Verification
            self.assertEqual(follow_two_of_three_out, follow_climb_inhibit_out)


if __name__ == "__main__":
    unittest.main()
