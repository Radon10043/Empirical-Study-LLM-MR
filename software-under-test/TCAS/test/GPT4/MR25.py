import os, sys

sys.path.append(os.path.join(os.path.dirname(__file__), ".."))
from utils import *


class TestingClass(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        """Build tcas.out before starting testing."""
        cmd = "cd " + os.path.join(os.path.dirname(__file__), "..", "..", "src") + " && make clean all"
        proc = os.popen(cmd)
        proc.readlines()
        proc.close()

    @parameterized.expand(load_test_cases(1000))
    def test25(self, vals: list):
        """Metamorphic Relation 25: If the Other_RAC is NO_INTENT, the resolution advisory should not vary when Own_Tracked_Alt_Rate is moderately increased or decreased, provided the current vertical separation is significant."""
        vertical_separation_threshold = 850  # An arbitrary vertical separation threshold for "significant"
        if vals[INDEX["Cur_Vertical_Sep"]] < vertical_separation_threshold:
            return

        rate_change = 200  # An arbitrary rate change considered "moderate"

        # Construct list of follow-up Own_Tracked_Alt_Rate values to test
        follow_up_rates = [vals[INDEX["Own_Tracked_Alt_Rate"]] + rate_change, vals[INDEX["Own_Tracked_Alt_Rate"]] - rate_change]

        # Iterate over rate change scenarios
        for rate in follow_up_rates:
            # Get source output
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in vals]
            cmd_list.extend(tmp_list)
            source_out = subprocess.check_output(cmd_list, text=True).strip()

            # Construct follow-up input with new Own_Tracked_Alt_Rate
            follow_vals = vals.copy()
            follow_vals[INDEX["Own_Tracked_Alt_Rate"]] = rate

            # Get follow-up output
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in follow_vals]
            cmd_list.extend(tmp_list)
            follow_out = subprocess.check_output(cmd_list, text=True).strip()

            # Verification
            self.assertEqual(source_out, follow_out, "Change in Own_Tracked_Alt_Rate altered resolution advisory in a scenario where vertical separation is significant.")


if __name__ == "__main__":
    unittest.main()
