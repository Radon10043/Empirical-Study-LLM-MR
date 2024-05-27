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
    def test20(self, vals: list):
        """Metamorphic Relation 20: If the Climb_Inhibit flag is set or cleared and the Own_Tracked_Alt is well below the maximum altitude, the UPWARD_RA advisory should change appropriately, provided all other input parameters favor such an advisory."""
        # Select a safe margin from the max altitude for the test
        max_altitude = 35000  # Example max altitude
        safe_margin = 5000

        if vals[INDEX["Own_Tracked_Alt"]] >= max_altitude - safe_margin:
            return

        # Get source output with Climb_Inhibit cleared
        vals[INDEX["Climb_Inhibit"]] = 0
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out_clear = subprocess.check_output(cmd_list, text=True).strip()

        # Get follow-up output with Climb_Inhibit set
        follow_vals = vals.copy()
        follow_vals[INDEX["Climb_Inhibit"]] = 1
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out_set = subprocess.check_output(cmd_list, text=True).strip()

        # If Climb_Inhibit affects the advisory, expect source_out_clear to be "1" (UPWARD_RA) and follow_out_set to be "0" (UNRESOLVED) or "2" (DOWNWARD_RA)
        if source_out_clear == "1" and follow_out_set not in ("0", "2"):
            self.fail(f"Setting Climb_Inhibit did not remove UPWARD_RA advisory as expected when Own_Tracked_Alt is below max altitude safety margin.\nSource: {source_out_clear}\nFollow-up: {follow_out_set}")


if __name__ == "__main__":
    unittest.main()
