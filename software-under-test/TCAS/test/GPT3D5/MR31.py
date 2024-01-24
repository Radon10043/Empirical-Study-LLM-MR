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
    def test31(self, vals: list):
        """Metamorphic Relation 31: If Own_Tracked_Alt_Rate is positive and Other_Tracked_Alt_Rate is negative, switching the values of Up_Separation and Down_Separation should result in the same output."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Own_Tracked_Alt_Rate"]] > 0 and vals[INDEX["Other_Tracked_Alt_Rate"]] < 0:
            # Construct follow-up input: Switch Up_Separation and Down_Separation
            follow_vals = vals.copy()
            follow_vals[INDEX["Up_Separation"]], follow_vals[INDEX["Down_Separation"]] = follow_vals[INDEX["Down_Separation"]], follow_vals[INDEX["Up_Separation"]]
            follow_out = run_tcas(follow_vals)

            # Verification
            self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
