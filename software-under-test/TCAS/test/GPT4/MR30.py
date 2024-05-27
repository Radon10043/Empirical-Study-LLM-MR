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
    def test30(self, vals: list):
        """Metamorphic Relation 30: For a descending or level-flight own aircraft, increasing Up_Separation while keeping Down_Separation constant should not result in an advisory to climb."""
        if vals[INDEX["Own_Tracked_Alt_Rate"]] > 0:  # Exclude climbing scenarios
            return

        up_separation_increase = 500  # Arbitrary increase in upward separation

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Construct follow-up input
        follow_vals = vals.copy()
        follow_vals[INDEX["Up_Separation"]] += up_separation_increase

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        if follow_out == "1":  # UPWARD_RA should not be issued when only Up_Separation has increased
            self.fail("Increased Up_Separation resulted in an unexpected UPWARD_RA advisory.")


if __name__ == "__main__":
    unittest.main()
