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
    def test21(self, vals: list):
        """Metamorphic Relation 21: If Two_of_Three_Reports_Valid is set to 0, and the Up_Separation is less than 300, then changing the value of Climb_Inhibit should not change the output."""
        # Get source output
        source_out = run_tcas(vals)

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Two_of_Three_Reports_Valid"]] = 0
        if vals[INDEX["Up_Separation"]] < 300:
            follow_vals[INDEX["Climb_Inhibit"]] = (follow_vals[INDEX["Climb_Inhibit"]] + 1) % 2  # Change Climb_Inhibit

        # Get follow-up output
        follow_out = run_tcas(follow_vals)

        # Verification
        self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
