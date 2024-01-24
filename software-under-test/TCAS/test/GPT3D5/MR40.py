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
    def test40(self, vals: list):
        """Metamorphic Relation 40: If the Up_Separation is less than Down_Separation and high confidence is set to 1, then changing the value of Climb_Inhibit should lead to the same output as changing the value of Other_Capability."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Up_Separation"]] < vals[INDEX["Down_Separation"]] and vals[INDEX["High_Confidence"]] == 1:
            # Construct follow-up input 1: Changing Climb_Inhibit
            follow_climb_inhibit_vals = vals.copy()
            follow_climb_inhibit_vals[INDEX["Climb_Inhibit"]] = 1 - follow_climb_inhibit_vals[INDEX["Climb_Inhibit"]]
            follow_climb_inhibit_out = run_tcas(follow_climb_inhibit_vals)

            # Construct follow-up input 2: Changing Other_Capability
            follow_capability_vals = vals.copy()
            follow_capability_vals[INDEX["Other_Capability"]] = 1 - follow_capability_vals[INDEX["Other_Capability"]]
            follow_capability_out = run_tcas(follow_capability_vals)

            # Verification
            self.assertEqual(follow_climb_inhibit_out, follow_capability_out)


if __name__ == "__main__":
    unittest.main()
