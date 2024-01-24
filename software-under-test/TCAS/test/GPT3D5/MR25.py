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
    def test25(self, vals: list):
        """Metamorphic Relation 25: If the value of Alt_Layer_Value is 1 or 2 and Own_Tracked_Alt is greater than Other_Tracked_Alt, changing the value of Own_Tracked_Alt should lead to the same output as changing the value of Other_Tracked_Alt by the same amount."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Alt_Layer_Value"]] in [1, 2] and vals[INDEX["Own_Tracked_Alt"]] > vals[INDEX["Other_Tracked_Alt"]]:
            # Construct follow-up input: Change Own_Tracked_Alt
            follow_own_vals = vals.copy()
            follow_own_vals[INDEX["Own_Tracked_Alt"]] += 100
            follow_own_out = run_tcas(follow_own_vals)

            # Construct follow-up input: Change Other_Tracked_Alt
            follow_other_vals = vals.copy()
            follow_other_vals[INDEX["Other_Tracked_Alt"]] += 100
            follow_other_out = run_tcas(follow_other_vals)

            # Verification
            self.assertEqual(follow_own_out, follow_other_out)


if __name__ == "__main__":
    unittest.main()
