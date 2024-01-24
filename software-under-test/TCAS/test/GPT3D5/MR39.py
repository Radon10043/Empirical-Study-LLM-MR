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
    def test39(self, vals: list):
        """Metamorphic Relation 39: If the value of Own_Tracked_Alt is less than Other_Tracked_Alt, and the Other_Tracked_Alt_Rate is positive, then changing the value of Up_Separation should lead to the same output as changing the value of Down_Separation."""
        # Get source output
        source_out = run_tcas(vals)

        if vals[INDEX["Own_Tracked_Alt"]] < vals[INDEX["Other_Tracked_Alt"]] and vals[INDEX["Other_Tracked_Alt_Rate"]] > 0:
            # Construct follow-up input 1: Changing Up_Separation
            follow_up_vals = vals.copy()
            follow_up_vals[INDEX["Up_Separation"]] += 100  # Or any other suitable amount
            follow_up_out = run_tcas(follow_up_vals)

            # Construct follow-up input 2: Changing Down_Separation
            follow_down_vals = vals.copy()
            follow_down_vals[INDEX["Down_Separation"]] += 100  # Or any other suitable amount
            follow_down_out = run_tcas(follow_down_vals)

            # Verification
            self.assertEqual(follow_up_out, follow_down_out)


if __name__ == "__main__":
    unittest.main()
