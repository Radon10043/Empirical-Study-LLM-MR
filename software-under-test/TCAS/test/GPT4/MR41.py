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
    def test41(self, vals: list):
        """Metamorphic Relation 41: If the initial advisory is for the own aircraft to descend (DOWNWARD_RA) due to close proximity to an intruder above, then increasing Down_Separation should maintain or nullify the advisory, not lead to an UPWARD_RA."""
        close_proximity = 600  # Arbitrary close vertical separation distance
        increased_separation = 1200  # Arbitrary increased downward separation

        # Initial conditions: Intruding aircraft is close and above the own aircraft
        vals[INDEX["Cur_Vertical_Sep"]] = close_proximity
        vals[INDEX["Other_Tracked_Alt"]] = vals[INDEX["Own_Tracked_Alt"]] + close_proximity
        vals[INDEX["Own_Tracked_Alt_Rate"]] = 0  # Own aircraft maintains level flight

        # Get the baseline output advisory
        base_cmd = [TCAS_PATH] + [str(x) for x in vals]
        base_out = subprocess.check_output(base_cmd, text=True).strip()

        # Ensure the initial advisory was DOWNWARD_RA
        if base_out != "2":
            return

        # Increase Down_Separation
        vals[INDEX["Down_Separation"]] += increased_separation

        # Get output after increasing Down_Separation
        follow_up_cmd = [TCAS_PATH] + [str(x) for x in vals]
        follow_up_out = subprocess.check_output(follow_up_cmd, text=True).strip()

        # Verify the advisory is maintained or nullified, but not UPWARD_RA
        self.assertTrue(follow_up_out in ["0", "2"], "Increasing Down_Separation led to an unexpected UPWARD_RA advisory.")


if __name__ == "__main__":
    unittest.main()
