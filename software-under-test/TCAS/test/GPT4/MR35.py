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
    def test35(self, vals: list):
        """Metamorphic Relation 35: If the intruder is not equipped with TCAS and the own aircraft climbs, an increased vertical separation should not result in a DOWNWARD_RA."""
        if vals[INDEX["Other_Capability"]] == OTHER_CAPABILITY_VALUES["TCAS_TA"]:
            return  # Not applicable if intruder has TCAS

        # Assume the own aircraft is initially climbing
        vals[INDEX["Own_Tracked_Alt_Rate"]] = 500  # Example positive rate indicating a climb

        # Get source output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Construct follow-up input with increased vertical separation
        follow_vals = vals.copy()
        follow_vals[INDEX["Cur_Vertical_Sep"]] += 1000  # Example vertical separation increase

        # Get follow-up output
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in follow_vals]
        cmd_list.extend(tmp_list)
        follow_out = subprocess.check_output(cmd_list, text=True).strip()

        # Verification
        if follow_out == "2":  # DOWNWARD_RA should not be issued after increasing separation while climbing
            self.fail("Increased vertical separation while climbing resulted in a DOWNWARD_RA advisory.")


if __name__ == "__main__":
    unittest.main()
