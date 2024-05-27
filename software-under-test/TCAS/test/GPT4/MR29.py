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
    def test29(self, vals: list):
        """Metamorphic Relation 29: If the vertical separation between aircrafts is beyond a safe threshold, changing the Own_Tracked_Alt_Rate slightly should not change the advisory."""
        safe_vertical_separation = 2000  # An arbitrary but safe separation distance
        rate_variation = 100  # A slight change in altitude rate

        if vals[INDEX["Cur_Vertical_Sep"]] < safe_vertical_separation:
            return

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        for rate_delta in [-rate_variation, rate_variation]:
            # Construct follow-up input with modified Own_Tracked_Alt_Rate
            follow_vals = vals.copy()
            follow_vals[INDEX["Own_Tracked_Alt_Rate"]] = vals[INDEX["Own_Tracked_Alt_Rate"]] + rate_delta

            # Get follow-up output
            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in follow_vals]
            cmd_list.extend(tmp_list)
            follow_out = subprocess.check_output(cmd_list, text=True).strip()

            # Verification
            self.assertEqual(source_out, follow_out, "Slight changes in Own_Tracked_Alt_Rate altered the advisory unexpectedly.")


if __name__ == "__main__":
    unittest.main()
