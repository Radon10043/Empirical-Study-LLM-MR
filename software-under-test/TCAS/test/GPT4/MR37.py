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
    def test37(self, vals: list):
        """Metamorphic Relation 37: When the intruder is at the same altitude as the own aircraft, increasing the vertical rate of the own aircraft should not result in the same advisory."""
        vals[INDEX["Other_Tracked_Alt"]] = vals[INDEX["Own_Tracked_Alt"]]  # Same altitude

        # Get source output with zero vertical rate
        vals[INDEX["Own_Tracked_Alt_Rate"]] = 0
        cmd_list = [TCAS_PATH]
        tmp_list = [str(x) for x in vals]
        cmd_list.extend(tmp_list)
        source_out = subprocess.check_output(cmd_list, text=True).strip()

        # Increasing the vertical rate of the own aircraft
        increased_rates = [500, -500]  # Example rates for climbing and descending
        for rate in increased_rates:
            vals[INDEX["Own_Tracked_Alt_Rate"]] = rate  # Apply rate

            cmd_list = [TCAS_PATH]
            tmp_list = [str(x) for x in vals]
            cmd_list.extend(tmp_list)
            follow_out = subprocess.check_output(cmd_list, text=True).strip()

            # Verification
            if source_out == follow_out:  # Advisory should not remain the same when rate changes
                self.fail("Changing the vertical rate of the own aircraft resulted in the same advisory.")


if __name__ == "__main__":
    unittest.main()
