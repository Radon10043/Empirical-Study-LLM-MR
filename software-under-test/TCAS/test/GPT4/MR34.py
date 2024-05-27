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
    def test34(self, vals: list):
        """Metamorphic Relation 34: If Climb_Inhibit is set to true and the advice is to ascend (UPWARD_RA), then reversing the Climb_Inhibit flag should not change the advisory to descend (DOWNWARD_RA)."""
        # First, check the advisory with Climb_Inhibit set to true
        vals[INDEX["Climb_Inhibit"]] = 1

        # Get the advisory result with Climb_Inhibit set to true
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        climb_inhibit_out = subprocess.check_output(cmd_list, text=True).strip()

        # If the advisory is not to ascend, then this metamorphic relation is not relevant
        if climb_inhibit_out != "1":  # Not UPWARD_RA
            return

        # Now reverse the Climb_Inhibit flag
        follow_vals = vals.copy()
        follow_vals[INDEX["Climb_Inhibit"]] = 0

        # Get the follow-up advisory result
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        no_climb_inhibit_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        if no_climb_inhibit_out == "2":  # The output should not be DOWNWARD_RA
            self.fail("Reversing the Climb_Inhibit when an upward advisory was given resulted in an incorrect downward advisory.")


if __name__ == "__main__":
    unittest.main()
