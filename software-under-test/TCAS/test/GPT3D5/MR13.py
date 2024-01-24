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
    def test13(self, vals: list):
        """Metamorphic Relation 13: If the Climb_Inhibit is changed from 0 to 1, the output should change accordingly only if the Vertical Separation is less than 300."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Climb_Inhibit"]] = 1 - vals[INDEX["Climb_Inhibit"]]  # Change Climb_Inhibit

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        if vals[INDEX["Cur_Vertical_Sep"]] < 300:
            self.assertNotEqual(source_out, follow_out)
        else:
            self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
