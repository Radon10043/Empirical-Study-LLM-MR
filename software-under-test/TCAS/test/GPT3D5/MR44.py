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
    def test44(self, vals: list):
        """Metamorphic Relation 44: Given that the Own_Tracked_Alt and Other_Tracked_Alt_Rate have different sign, if we swap the values of Cur_Vertical_Sep and Alt_Layer_Value, the output should not change."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Own_Tracked_Alt"]] * vals[INDEX["Other_Tracked_Alt_Rate"]] < 0:
            # Construct follow-up input: Swap Cur_Vertical_Sep and Alt_Layer_Value
            follow_vals = vals.copy()
            follow_vals[INDEX["Cur_Vertical_Sep"]], follow_vals[INDEX["Alt_Layer_Value"]] = follow_vals[INDEX["Alt_Layer_Value"]], follow_vals[INDEX["Cur_Vertical_Sep"]]
            follow_out = run_tcas(follow_vals)

            # Verification
            self.assertEqual(source_out, follow_out)


if __name__ == "__main__":
    unittest.main()
