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
    def test26(self, vals: list):
        """Metamorphic Relation 26: If the value of Up_Separation is less than Down_Separation and high confidence is set to 1, reversing the Climb_Inhibit decision should lead to the same output as reversing the decisions of the Other_RAC."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Up_Separation"]] < vals[INDEX["Down_Separation"]] and vals[INDEX["High_Confidence"]] == 1:
            # Construct follow-up input: Reverse Climb_Inhibit decision
            follow_climb_inhibit_vals = vals.copy()
            follow_climb_inhibit_vals[INDEX["Climb_Inhibit"]] = 1 - follow_climb_inhibit_vals[INDEX["Climb_Inhibit"]]
            follow_climb_inhibit_out = run_tcas(follow_climb_inhibit_vals)

            # Construct follow-up input: Reverse Other_RAC decision
            follow_other_rac_vals = vals.copy()
            follow_other_rac_vals[INDEX["Other_RAC"]] = 2 if follow_other_rac_vals[INDEX["Other_RAC"]] == 1 else 1
            follow_other_rac_out = run_tcas(follow_other_rac_vals)

            # Verification
            self.assertEqual(follow_climb_inhibit_out, follow_other_rac_out)


if __name__ == "__main__":
    unittest.main()
