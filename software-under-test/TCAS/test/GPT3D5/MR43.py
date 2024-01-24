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
    def test43(self, vals: list):
        """Metamorphic Relation 43: If the altitude of the own aircraft is equal to the altitude of the other tracked aircraft, reversing the Climb_Inhibit decision should not change the output."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Own_Tracked_Alt"]] == vals[INDEX["Other_Tracked_Alt"]]:
            # Construct follow-up input: Reverse Climb_Inhibit decision
            follow_climb_inhibit_vals = vals.copy()
            follow_climb_inhibit_vals[INDEX["Climb_Inhibit"]] = 1 - follow_climb_inhibit_vals[INDEX["Climb_Inhibit"]]
            follow_climb_inhibit_out = run_tcas(follow_climb_inhibit_vals)

            # Verification
            self.assertEqual(source_out, follow_climb_inhibit_out)


if __name__ == "__main__":
    unittest.main()
