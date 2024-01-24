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
    def test37(self, vals: list):
        """Metamorphic Relation 37: If the Climb_Inhibit is set to 0 and Up_Separation is less than Down_Separation, then changing the value of Other_RAC should lead to the same output as changing the value of Other_Capability."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Climb_Inhibit"]] == 0 and vals[INDEX["Up_Separation"]] < vals[INDEX["Down_Separation"]]:
            # Construct follow-up input 1: Changing Other_RAC
            follow_rac_vals = vals.copy()
            follow_rac_vals[INDEX["Other_RAC"]] = 1 - follow_rac_vals[INDEX["Other_RAC"]]
            follow_rac_out = run_tcas(follow_rac_vals)

            # Construct follow-up input 2: Changing Other_Capability
            follow_capability_vals = vals.copy()
            follow_capability_vals[INDEX["Other_Capability"]] = 1 - follow_capability_vals[INDEX["Other_Capability"]]
            follow_capability_out = run_tcas(follow_capability_vals)

            # Verification
            self.assertEqual(follow_rac_out, follow_capability_out)


if __name__ == "__main__":
    unittest.main()
