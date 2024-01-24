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
    def test30(self, vals: list):
        """Metamorphic Relation 30: If the Alt_Layer_Value is 0 and the Up_Separation is less than the Down_Separation, then changing the value of Climb_Inhibit should lead to the same output as changing the value of Other_Capability by the same amount."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Alt_Layer_Value"]] == 0 and vals[INDEX["Up_Separation"]] < vals[INDEX["Down_Separation"]]:
            # Construct follow-up input: Change Climb_Inhibit
            follow_climb_inhibit_vals = vals.copy()
            follow_climb_inhibit_vals[INDEX["Climb_Inhibit"]] = 1 - follow_climb_inhibit_vals[INDEX["Climb_Inhibit"]]
            follow_climb_inhibit_out = run_tcas(follow_climb_inhibit_vals)

            # Construct follow-up input: Change Other_Capability
            follow_other_capability_vals = vals.copy()
            follow_other_capability_vals[INDEX["Other_Capability"]] = 1 - follow_other_capability_vals[INDEX["Other_Capability"]]
            follow_other_capability_out = run_tcas(follow_other_capability_vals)

            # Verification
            self.assertEqual(follow_climb_inhibit_out, follow_other_capability_out)


if __name__ == "__main__":
    unittest.main()
